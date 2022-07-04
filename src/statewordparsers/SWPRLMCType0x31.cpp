#include "../src/statewordparsers/SWPRLMCType0x31.h"

#include <QtMath>

SWPRLMCType0x31::SWPRLMCType0x31(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPRLMCType0x31::~SWPRLMCType0x31() {

}


int SWPRLMCType0x31::isAlarm() const
{
    return isInAlarm();
}

int SWPRLMCType0x31::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPRLMCType0x31::isOutAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMCType0x31::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPRLMCType0x31::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMCType0x31::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLMCType0x31::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMCType0x31::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}
//b5fe6304312c011600d9
int SWPRLMCType0x31::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

double SWPRLMCType0x31::voltage() const
{
    if(byteWord().isEmpty())
        return -1.0;
    return 5.0 - 5.0 * ((double)(0x00FF&byteWord().at(0)) / 255.0);
}

int SWPRLMCType0x31::synchronization() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //External);
    else
        return 0; //Internal;
}

int SWPRLMCType0x31::isExternalSynchronization() const
{
    return synchronization();
}

int SWPRLMCType0x31::isInternalSynchronization() const
{
    int ises = isExternalSynchronization();
    return ((0 == ises) ? 1 : ((1 == ises) ? 0 : ises));
}

float SWPRLMCType0x31::threshold() const
{
    if(byteWord().isEmpty())
        return -1.0;
    switch (static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x0F)) {
    case static_cast<quint8>(0):  return 10.0;
    case static_cast<quint8>(1):  return 09.0;
    case static_cast<quint8>(2):  return 08.0;
    case static_cast<quint8>(3):  return 07.0;
    case static_cast<quint8>(4):  return 06.0;
    case static_cast<quint8>(5):  return 05.0;
    case static_cast<quint8>(6):  return 04.0;
    case static_cast<quint8>(7):  return 03.0;
    case static_cast<quint8>(8):  return 02.0;
    case static_cast<quint8>(9):  return 01.0;
    case static_cast<quint8>(10): return 00.6;
    case static_cast<quint8>(11): return 00.5;
    case static_cast<quint8>(12): return 00.4;
    case static_cast<quint8>(13): return 00.3;
    case static_cast<quint8>(14): return 00.2;
    case static_cast<quint8>(15): return 00.1;
    default: return -1.0;
    }
}

int SWPRLMCType0x31::clockPeriod() const
{
    if(byteWord().isEmpty())
        return -1;
    return (static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x70)) >> 4;
}

int SWPRLMCType0x31::modeProcessing() const
{
    if(byteWord().isEmpty())
        return -1;
    return static_cast<quint8>(byteWord().at(3)) & static_cast<quint8>(0x03);
}

int SWPRLMCType0x31::isFault() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Error);
    else
        return 0; //Status::Not;
}
