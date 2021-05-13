#include "SWPRLMC.h"

#include <QtMath>

SWPRLMC::SWPRLMC(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPRLMC::SWPRLMC(const SWPRLMC &parent) :
    SWP(parent)
{
}

SWPRLMC::~SWPRLMC() {

}


int SWPRLMC::isAlarm() const
{
    return isInAlarm();
}

int SWPRLMC::isInAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPRLMC::isOutAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMC::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPRLMC::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMC::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPRLMC::isWasAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPRLMC::isOn() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}
//b5fe6304312c011600d9
int SWPRLMC::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

double SWPRLMC::voltage() const
{
    if(getStateWord().isEmpty())
        return -1.0;
    return 5.0 - 5.0 * ((double)(0x00FF&getStateWord().at(0)) / 255.0);
}

int SWPRLMC::synchronization() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //External);
    else
        return 0; //Internal;
}

int SWPRLMC::isExternalSynchronization() const
{
    return synchronization();
}

int SWPRLMC::isInternalSynchronization() const
{
    int ises = isExternalSynchronization();
    return ((0 == ises) ? 1 : ((1 == ises) ? 0 : ises));
}

float SWPRLMC::threshold() const
{
    if(getStateWord().isEmpty())
        return -1.0;
    switch (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x0F)) {
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

int SWPRLMC::clockPeriod() const
{
    if(getStateWord().isEmpty())
        return -1;
    return (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x70)) >> 4;
}

int SWPRLMC::modeProcessing() const
{
    if(getStateWord().isEmpty())
        return -1;
    return static_cast<quint8>(getStateWord().at(3)) & static_cast<quint8>(0x03);
}

int SWPRLMC::isFault() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Error);
    else
        return 0; //Status::Not;
}
