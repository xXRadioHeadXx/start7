#include "SWPIUBLIPType0x41.h"

quint8 SWPIUBLIPType0x41::mask() const
{
    return _mask;
}

SWPIUBLIPType0x41::SWPIUBLIPType0x41(const StateWord &stateWord, int numIU) :
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

//SWPIUBLIP::SWPIUBLIP(const QByteArray &byteWord, int numIU) :
//    SWP(byteWord)
//{
//    switch (numIU) {
//    case 1:
//        _mask = 0x01;
//        break;
//    case 2:
//        _mask = 0x02;
//        break;
//    case 3:
//        _mask = 0x04;
//        break;
//    case 4:
//        _mask = 0x08;
//        break;
//    case 5:
//        _mask = 0x10;
//        break;
//    case 6:
//        _mask = 0x20;
//        break;
//    case 7:
//        _mask = 0x40;
//        break;
//    case 8:
//        _mask = 0x80;
//        break;
//    default:
//        _mask = 0x00;
//        break;
//    }
//}

SWPIUBLIPType0x41::SWPIUBLIPType0x41(const SWPIUBLIPType0x41 &parent) :
    SWP(parent),
    _mask(parent.mask())
{
}

SWPIUBLIPType0x41::~SWPIUBLIPType0x41() {

}

int SWPIUBLIPType0x41::isOutAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & mask())
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPIUBLIPType0x41::isOn() const
{
    return isOutAlarm();
}

int SWPIUBLIPType0x41::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}
