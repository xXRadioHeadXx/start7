#include "../src/statewordparsers/swpssoiblip/SWPSSOIIUBLIPType0x41.h"

uint8_t SWPSSOIIUBLIPType0x41::mask() const
{
    return _mask;
}

SWPSSOIIUBLIPType0x41::SWPSSOIIUBLIPType0x41(const StateWord &stateWord, int numIU) :
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

SWPSSOIIUBLIPType0x41::~SWPSSOIIUBLIPType0x41() {

}

int SWPSSOIIUBLIPType0x41::isOutAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & mask())
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPSSOIIUBLIPType0x41::isOn() const
{
    return isOutAlarm();
}

int SWPSSOIIUBLIPType0x41::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}
