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

int SWPT4KDDCType0x34::weakening() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == getC()) {
        return static_cast<uint16_t>(byteWord().at(1)) & static_cast<uint16_t>(0x0F);
    } else if(2 == getC()) {
        return static_cast<uint16_t>(byteWord().at(12)) & static_cast<uint16_t>(0x0F);
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
