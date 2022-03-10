#include "SWPT4KDDCType0x34.h"
#include "SWPT4KDDType0x34.h"

int SWPT4KDDType0x34::getY4() const
{
    return y4;
}

int SWPT4KDDType0x34::getDd() const
{
    return dd;
}

SWPT4KDDType0x34::SWPT4KDDType0x34(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPT4KDDType0x34::~SWPT4KDDType0x34()
{

}

int SWPT4KDDType0x34::weakening() const
{
    if(byteWord().isEmpty())
        return -1;
    return static_cast<uint16_t>(byteWord().at(1)) & static_cast<uint16_t>(0x0F);
}

SWPT4KDDCType0x34 SWPT4KDDType0x34::c(int num)
{
    return SWPT4KDDCType0x34(getStateWord(), getY4(), getDd(), num);
}
