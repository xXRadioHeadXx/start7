#include "SWPSDBLIP.h"

quint8 SWPSDBLIP::mask() const
{
    return _mask;
}

SWPSDBLIP::SWPSDBLIP(const StateWord &stateWord, int numSD) :
    SWP(stateWord)
{
    switch (numSD) {
    case 1:
        _mask = 0x01;
        break;
    case 2:
        _mask = 0x02;
        break;
    case 3:
        _mask = 0x04;
        break;
    case 4:
        _mask = 0x08;
        break;
    case 5:
        _mask = 0x10;
        break;
    case 6:
        _mask = 0x20;
        break;
    case 7:
        _mask = 0x40;
        break;
    case 8:
        _mask = 0x80;
        break;
    default:
        _mask = 0x00;
        break;
    }
}

SWPSDBLIP::SWPSDBLIP(const QByteArray &byteWord, int numSD) :
    SWP(byteWord)
{
    switch (numSD) {
    case 1:
        _mask = 0x01;
        break;
    case 2:
        _mask = 0x02;
        break;
    case 3:
        _mask = 0x04;
        break;
    case 4:
        _mask = 0x08;
        break;
    case 5:
        _mask = 0x10;
        break;
    case 6:
        _mask = 0x20;
        break;
    case 7:
        _mask = 0x40;
        break;
    case 8:
        _mask = 0x80;
        break;
    default:
        _mask = 0x00;
        break;
    }
}

SWPSDBLIP::SWPSDBLIP(const SWPSDBLIP &parent) :
    SWP(parent),
    _mask(parent.mask())
{
}

SWPSDBLIP::~SWPSDBLIP() {

}

int SWPSDBLIP::isAlarm() const
{
    return isInAlarm();
}

int SWPSDBLIP::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(0)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}


int SWPSDBLIP::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPSDBLIP::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & mask())
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSDBLIP::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(0) == (static_cast<quint8>(byteWord().at(3)) & mask()))
        return 0; //Status::Off;
    else
        return 1; //
}

int SWPSDBLIP::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}
