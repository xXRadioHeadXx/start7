#include "../src/statewordparsers/swpt4k/SWPT4KDDCType0x32.h"

int SWPT4KDDCType0x32::getY4() const
{
    return y4;
}

int SWPT4KDDCType0x32::getDd() const
{
    return dd;
}

int SWPT4KDDCType0x32::getC() const
{
    return c;
}

int SWPT4KDDCType0x32::index() const
{
    int index = 1;
    if(2 < getY4()) {
        index += 26;
    }
    index += getDd();
    return index;
}

SWPT4KDDCType0x32::SWPT4KDDCType0x32(const StateWord &stateWord, const int y4, const int dd, const int c) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , c(c)
{

}

SWPT4KDDCType0x32::~SWPT4KDDCType0x32()
{

}

int SWPT4KDDCType0x32::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = (1 < getC()) ? static_cast<uint8_t>(0x02) : static_cast<uint8_t>(0x01);
    if(static_cast<uint8_t>(byteWord().at(index())) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDCType0x32::isFault() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = (1 < getC()) ? static_cast<uint8_t>(0x08) : static_cast<uint8_t>(0x04);
    if(static_cast<uint8_t>(byteWord().at(index())) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}
