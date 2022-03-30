#include "SWPSOTADDFType0x34.h"

int SWPSOTADDFType0x34::getY4() const
{
    return y4;
}

int SWPSOTADDFType0x34::getDd() const
{
    return dd;
}

int SWPSOTADDFType0x34::getF() const
{
    return f;
}

int SWPSOTADDFType0x34::threshold() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 2;
    if(1 == getF()) {
        index = 2;
    } else if(2 == getF()) {
        index = 4;
    } else {
        return -1;
    }
    return (static_cast<uint16_t>(byteWord().at(index)) << 8) | (static_cast<uint16_t>(byteWord().at(index + 1)) & 0x00FF);
}

float SWPSOTADDFType0x34::timeImpact() const
{
    if(byteWord().isEmpty())
        return -1.0f;
    uint8_t index = 6;
    if(1 == getF()) {
        index = 6;
    } else if(2 == getF()) {
        index = 7;
    } else {
        return -1.0f;
    }
    return (float)(byteWord().at(index)) *  0.1f;
}

int SWPSOTADDFType0x34::countImpact() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 8;
    if(1 == getF()) {
        index = 8;
    } else if(2 == getF()) {
        index = 9;
    } else {
        return -1;
    }
    return static_cast<uint8_t>(byteWord().at(index));
}

int SWPSOTADDFType0x34::durationOvercoming() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 10;
    if(1 == getF()) {
        index = 10;
    } else if(2 == getF()) {
        index = 11;
    } else {
        return -1;
    }
    return static_cast<uint8_t>(byteWord().at(index));
}

int SWPSOTADDFType0x34::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPSOTADDFType0x34::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == getF()) {
        return (static_cast<uint16_t>(byteWord().at(1)) & 0b10000000) ? 1 : 0;
    } else if(2 == getF()) {
        return (static_cast<uint16_t>(byteWord().at(1)) & 0b01000000) ? 1 : 0;
    }
    return -1;
}

SWPSOTADDFType0x34::SWPSOTADDFType0x34(const StateWord &stateWord, const int y4, const int dd, const int f) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , f(f)
{

}

SWPSOTADDFType0x34::~SWPSOTADDFType0x34()
{

}

