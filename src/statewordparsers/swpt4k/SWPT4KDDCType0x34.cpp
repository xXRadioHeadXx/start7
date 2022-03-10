#include "SWPT4KDDCFType0x34.h"
#include "SWPT4KDDCType0x34.h"

int SWPT4KDDCType0x34::getY4() const
{
    return y4;
}

int SWPT4KDDCType0x34::getDd() const
{
    return dd;
}

int SWPT4KDDCType0x34::getC() const
{
    return c;
}

int SWPT4KDDCType0x34::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPT4KDDCType0x34::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == getC()) {
        return static_cast<uint16_t>(byteWord().at(1)) & 0b10000000;
    } else if(2 == getC()) {
        return static_cast<uint16_t>(byteWord().at(1)) & 0b01000000;
    }
    return -1;
}

SWPT4KDDCFType0x34 SWPT4KDDCType0x34::f(int num)
{
    return SWPT4KDDCFType0x34(getStateWord(), getY4(), getDd(), getC(), num);
}

SWPT4KDDCType0x34::SWPT4KDDCType0x34(const StateWord &stateWord, const int y4, const int dd, const int c) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , c(c)
{

}

SWPT4KDDCType0x34::~SWPT4KDDCType0x34()
{

}
