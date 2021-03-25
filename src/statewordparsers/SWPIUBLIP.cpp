#include "SWPIUBLIP.h"

quint8 SWPIUBLIP::mask() const
{
    return _mask;
}

SWPIUBLIP::SWPIUBLIP(const QByteArray &stateWord, int numIU) :
    SWP(stateWord)
{
    switch (numIU) {
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

SWPIUBLIP::SWPIUBLIP(const SWPIUBLIP &parent) :
    SWP(parent),
    _mask(parent.mask())
{
}

SWPIUBLIP::~SWPIUBLIP() {

}

int SWPIUBLIP::isOutAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & mask())
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPIUBLIP::isOn() const
{
    return isOutAlarm();
}

int SWPIUBLIP::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}
