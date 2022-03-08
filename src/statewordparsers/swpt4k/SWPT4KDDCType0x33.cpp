#include "SWPT4KDDCFType0x33.h"
#include "SWPT4KDDCType0x33.h"

int SWPT4KDDCType0x33::getY4() const
{
    return y4;
}

int SWPT4KDDCType0x33::getDd() const
{
    return dd;
}

int SWPT4KDDCType0x33::getC() const
{
    return c;
}

SWPT4KDDCType0x33::SWPT4KDDCType0x33(const StateWord &stateWord, const int y4, const int dd, const int c) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , c(c)
{

}

SWPT4KDDCType0x33::~SWPT4KDDCType0x33()
{

}

int SWPT4KDDCType0x33::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = (1 < getC()) ? static_cast<uint8_t>(0x02) : static_cast<uint8_t>(0x01);
    if(static_cast<uint8_t>(byteWord().at(7)) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDCType0x33::isClosure() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = (1 < getC()) ? static_cast<uint8_t>(0x20) : static_cast<uint8_t>(0x04);
    if(static_cast<uint8_t>(byteWord().at(7)) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDCType0x33::isCliff() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = (1 < getC()) ? static_cast<uint8_t>(0x10) : static_cast<uint8_t>(0x02);
    if(static_cast<uint8_t>(byteWord().at(7)) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDCType0x33::level() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t index = (1 < getC()) ? 5 : 3;
    int level = (static_cast<uint16_t>(byteWord().at(index)) << 8) & (static_cast<uint16_t>(byteWord().at(index + 1)) & 0x00FF);
    return level;
}

SWPT4KDDCFType0x33 SWPT4KDDCType0x33::f(int num)
{
    return SWPT4KDDCFType0x33(getStateWord(), getY4(), getDd(), getC(), num);
}

SWPT4KDDCFType0x33 SWPT4KDDCType0x33::f1()
{
    return f(1);
}

SWPT4KDDCFType0x33 SWPT4KDDCType0x33::f2()
{
    return f(2);
}
