#include "SWPRLM.h"

#include <Utils.h>
#include <global.h>

SWPRLM::SWPRLM(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPRLM::SWPRLM(const SWPRLM &parent) :
    SWP(parent)
{
}

SWPRLM::~SWPRLM() {

}


float SWPRLM::threshold() const
{
    if(getStateWord().isEmpty())
        return -1.0;
    switch (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x0F)) {
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

int SWPRLM::modeProcessing() const
{
    if(getStateWord().isEmpty())
        return -1;
    return (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10)) >> 4;
}

int SWPRLM::clockPeriod() const
{
    if(getStateWord().isEmpty())
        return -1;

    quint8 cp = (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x60)) >> 5;
    cp = Utils::reverseBits(cp);
    cp = cp >> 6;
    return cp;

    return (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x60)) >> 5;
}

double SWPRLM::voltage() const
{
    if(getStateWord().isEmpty())
        return -1.0;

    return 5.0 - 5.0 * ((double)(0x00FF&getStateWord().at(1)) / 255.0);
}

int SWPRLM::isOn() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPRLM::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPRLM::isAlarm() const
{
    return isInAlarm();
}

int SWPRLM::isInAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPRLM::isOutAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLM::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPRLM::isWasAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLM::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLM::synchronization() const
{
    return isExistDK();
}

int SWPRLM::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLM::isOpened() const
{
    return isInOpened();
}

int SWPRLM::isInOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLM::isWasOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLM::isFault() const
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
