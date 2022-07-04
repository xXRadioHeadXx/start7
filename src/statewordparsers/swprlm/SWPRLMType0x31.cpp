#include "../src/statewordparsers/swprlm/SWPRLMType0x31.h"

#include "../src/utils/Utils.h"
#include "../src/global.h"

SWPRLMType0x31::SWPRLMType0x31(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPRLMType0x31::~SWPRLMType0x31() {

}


float SWPRLMType0x31::threshold() const
{
    if(byteWord().isEmpty())
        return -1.0;
    switch (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x0F)) {
    case static_cast<uint8_t>(0):  return 10.0;
    case static_cast<uint8_t>(1):  return 09.0;
    case static_cast<uint8_t>(2):  return 08.0;
    case static_cast<uint8_t>(3):  return 07.0;
    case static_cast<uint8_t>(4):  return 06.0;
    case static_cast<uint8_t>(5):  return 05.0;
    case static_cast<uint8_t>(6):  return 04.0;
    case static_cast<uint8_t>(7):  return 03.0;
    case static_cast<uint8_t>(8):  return 02.0;
    case static_cast<uint8_t>(9):  return 01.0;
    case static_cast<uint8_t>(10): return 00.6;
    case static_cast<uint8_t>(11): return 00.5;
    case static_cast<uint8_t>(12): return 00.4;
    case static_cast<uint8_t>(13): return 00.3;
    case static_cast<uint8_t>(14): return 00.2;
    case static_cast<uint8_t>(15): return 00.1;
    default: return -1.0;
    }
}

int SWPRLMType0x31::modeProcessing() const
{
    if(byteWord().isEmpty())
        return -1;
    return (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x10)) >> 4;
}

int SWPRLMType0x31::clockPeriod() const
{
    if(byteWord().isEmpty())
        return -1;

    uint8_t cp = (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x60)) >> 5;
    cp = Utils::reverseBits(cp);
    cp = cp >> 6;
    return cp;

    return (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x60)) >> 5;
}

double SWPRLMType0x31::voltage() const
{
    if(byteWord().isEmpty())
        return -1.0;

    return 5.0 - 5.0 * ((double)(0x00FF&byteWord().at(1)) / 255.0);
}

int SWPRLMType0x31::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPRLMType0x31::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPRLMType0x31::isAlarm() const
{
    return isInAlarm();
}

int SWPRLMType0x31::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isOutAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPRLMType0x31::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::synchronization() const
{
    return isExistDK();
}

int SWPRLMType0x31::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isOpened() const
{
    return isInOpened();
}

int SWPRLMType0x31::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMType0x31::isFault() const
{
    if(1 == isOn() &&
       0 == isOutAlarm() &&
       1 == isInAlarm() &&
       1 == isWasAlarm() &&
       0 == isWasDK() &&
       0 == isWasOpened()) {
        return 1;
    } else if (-1 == isOn() ||
               -1 == isOutAlarm() ||
               -1 == isInAlarm() ||
               -1 == isWasAlarm() ||
               -1 == isWasDK() ||
               -1 == isWasOpened()) {
        return -1;
    }
    return 0;
}
