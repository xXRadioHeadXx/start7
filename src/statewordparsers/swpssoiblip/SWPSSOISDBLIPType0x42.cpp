#include "../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x42.h"


uint8_t SWPSSOISDBLIPType0x42::mask() const
{
    return _mask;
}

SWPSSOISDBLIPType0x42::SWPSSOISDBLIPType0x42(const StateWord &stateWord, int numSD) :
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
    default:
        _mask = 0x00;
        break;
    }
}

SWPSSOISDBLIPType0x42::~SWPSSOISDBLIPType0x42() {

}

int SWPSSOISDBLIPType0x42::isInAlarm() const
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

int SWPSSOISDBLIPType0x42::isShortCircuit() const
{
    int lineBreak = isLineBreak();
    return ((0 == lineBreak) ? 1 : ((1 == lineBreak) ? 0 : lineBreak));
}

int SWPSSOISDBLIPType0x42::isLineBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}
