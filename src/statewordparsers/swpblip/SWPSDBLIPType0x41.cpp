#include "../src/statewordparsers/swpblip/SWPSDBLIPType0x41.h"

uint8_t SWPSDBLIPType0x41::mask() const
{
    return _mask;
}

SWPSDBLIPType0x41::SWPSDBLIPType0x41(const StateWord &stateWord, int numSD) :
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

SWPSDBLIPType0x41::~SWPSDBLIPType0x41() {

}

int SWPSDBLIPType0x41::isAlarm() const
{
    return isInAlarm();
}

int SWPSDBLIPType0x41::isInAlarm() const
{
    if(byteWord().isEmpty() || 0x00 == mask())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}


int SWPSDBLIPType0x41::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPSDBLIPType0x41::isWasAlarm() const
{
    if(byteWord().isEmpty() || 0x00 == mask())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & mask())
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSDBLIPType0x41::isOn() const
{
    if(byteWord().isEmpty() || 0x00 == mask())
        return -1;
    if(static_cast<uint8_t>(0) == (static_cast<uint8_t>(byteWord().at(3)) & mask()))
        return 0; //Status::Off;
    else
        return 1; //
}

int SWPSDBLIPType0x41::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}
