#include "../src/statewordparsers/SWPSDBLIPType0x42.h"

quint8 SWPSDBLIPType0x42::mask() const
{
    return _mask;
}

SWPSDBLIPType0x42::SWPSDBLIPType0x42(const StateWord &stateWord, int numSD) :
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

SWPSDBLIPType0x42::~SWPSDBLIPType0x42() {

}

int SWPSDBLIPType0x42::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(0)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}

int SWPSDBLIPType0x42::isShortCircuit() const
{
    int lineBreak = isLineBreak();
    return ((0 == lineBreak) ? 1 : ((1 == lineBreak) ? 0 : lineBreak));
}

int SWPSDBLIPType0x42::isLineBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}
