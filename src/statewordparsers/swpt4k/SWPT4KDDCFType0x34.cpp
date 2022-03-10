#include "SWPT4KDDCFType0x34.h"

int SWPT4KDDCFType0x34::getY4() const
{
    return y4;
}

int SWPT4KDDCFType0x34::getDd() const
{
    return dd;
}

int SWPT4KDDCFType0x34::getC() const
{
    return c;
}

int SWPT4KDDCFType0x34::getF() const
{
    return f;
}

int SWPT4KDDCFType0x34::threshold() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 2;
    if(1 == getC() && 1 == getF()) {
        index = 2;
    } else if(1 == getC() && 2 == getF()) {
        index = 4;
    } else if(2 == getC() && 1 == getF()) {
        index = 13;
    } else if(2 == getC() && 2 == getF()) {
        index = 15;
    } else {
        return -1;
    }
    return (static_cast<uint16_t>(byteWord().at(index)) << 8) & (static_cast<uint16_t>(byteWord().at(index + 1)) & 0x00FF);
}

float SWPT4KDDCFType0x34::timeImpact() const
{
    if(byteWord().isEmpty())
        return -1.0f;
    uint8_t index = 2;
    if(1 == getC() && 1 == getF()) {
        index = 6;
    } else if(1 == getC() && 2 == getF()) {
        index = 7;
    } else if(2 == getC() && 1 == getF()) {
        index = 17;
    } else if(2 == getC() && 2 == getF()) {
        index = 18;
    } else {
        return -1.0f;
    }
    return (float)(byteWord().at(index)) *  0.1f;
}

int SWPT4KDDCFType0x34::countImpact() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 2;
    if(1 == getC() && 1 == getF()) {
        index = 8;
    } else if(1 == getC() && 2 == getF()) {
        index = 9;
    } else if(2 == getC() && 1 == getF()) {
        index = 19;
    } else if(2 == getC() && 2 == getF()) {
        index = 20;
    } else {
        return -1;
    }
    return static_cast<uint8_t>(byteWord().at(index));
}

int SWPT4KDDCFType0x34::durationOvercoming() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = 2;
    if(1 == getC() && 1 == getF()) {
        index = 10;
    } else if(1 == getC() && 2 == getF()) {
        index = 11;
    } else if(2 == getC() && 1 == getF()) {
        index = 21;
    } else if(2 == getC() && 2 == getF()) {
        index = 22;
    } else {
        return -1;
    }
    return static_cast<uint8_t>(byteWord().at(index));
}

SWPT4KDDCFType0x34::SWPT4KDDCFType0x34(const StateWord &stateWord, const int y4, const int dd, const int c, const int f) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , c(c)
  , f(f)
{

}

SWPT4KDDCFType0x34::~SWPT4KDDCFType0x34()
{

}

