#include "SWPT4KDDCFType0x33.h"

int SWPT4KDDCFType0x33::getY4() const
{
    return y4;
}

int SWPT4KDDCFType0x33::getDd() const
{
    return dd;
}

int SWPT4KDDCFType0x33::getC() const
{
    return c;
}

int SWPT4KDDCFType0x33::getF() const
{
    return f;
}

int SWPT4KDDCFType0x33::isWasAlarm() const
{

    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = 0x00;
    if(1 == getC() && 1 == getF()) {
        mask = static_cast<uint8_t>(0x01);
    } else if(1 == getC() && 2 == getF()) {
        mask = static_cast<uint8_t>(0x02);
    } else if(2 == getC() && 1 == getF()) {
        mask = static_cast<uint8_t>(0x04);
    } else if(2 == getC() && 2 == getF()) {
        mask = static_cast<uint8_t>(0x08);
    }

    if(static_cast<uint8_t>(byteWord().at(8)) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

SWPT4KDDCFType0x33::SWPT4KDDCFType0x33(const StateWord &stateWord, const int y4, const int dd, const int c, const int f) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , c(c)
  , f(f)
{
}

SWPT4KDDCFType0x33::~SWPT4KDDCFType0x33()
{

}
