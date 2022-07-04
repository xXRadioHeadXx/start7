#include "../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x41.h"


uint8_t SWPSSOISDBLIPType0x41::mask() const
{
    return _mask;
}

SWPSSOISDBLIPType0x41::SWPSSOISDBLIPType0x41(const StateWord &stateWord, int numSD) :
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
    case 9:
        _mask = 0x00;
        break;
    default:
        _mask = 0x00;
        break;
    }
}

SWPSSOISDBLIPType0x41::~SWPSSOISDBLIPType0x41() {

}

int SWPSSOISDBLIPType0x41::isAlarm() const
{
    return ((1 == isInAlarm() && 1 == isWasAlarm()) ? 1 : (-1 == isInAlarm() || -1 == isWasAlarm()) ? -1 : 0);
}

int SWPSSOISDBLIPType0x41::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(0x00 == mask())
        return 0;
    if(static_cast<uint8_t>(byteWord().at(0)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}


int SWPSSOISDBLIPType0x41::isNorm() const
{
    int isalarm = isAlarm();
    int isopened = isOpened();
    isopened = 0x00 != mask() ? 0 : isopened;
    return ((-1 == isalarm || -1 == isopened) ? -1 : ((1 == isalarm || 1 == isopened) ? 0 : 1));
}

int SWPSSOISDBLIPType0x41::isInNorm() const
{
    int isinalarm = isInAlarm();
    return ((-1 == isinalarm) ? -1 : ((1 == isinalarm) ? 0 : 1));
}

int SWPSSOISDBLIPType0x41::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(0x00 == mask())
        return 0;
    if(static_cast<uint8_t>(byteWord().at(2)) & mask())
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSSOISDBLIPType0x41::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(0x00 == mask())
        return 1;
    if(static_cast<uint8_t>(0) == (static_cast<uint8_t>(byteWord().at(3)) & mask()))
        return 0; //Status::Off;
    else
        return 1; //
}

int SWPSSOISDBLIPType0x41::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPSSOISDBLIPType0x41::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(0x00 != mask())
        return 0;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x10)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int SWPSSOISDBLIPType0x41::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(0x00 != mask())
        return 0;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x20)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSSOISDBLIPType0x41::isOpened() const
{
    return ((1 == isInOpened() || 1 == isWasOpened()) ? 1 : (-1 == isInOpened() || -1 == isWasOpened()) ? -1 : 0);
}
