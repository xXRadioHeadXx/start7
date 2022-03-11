#include "SWPSOTADDFType0x33.h"

int SWPSOTADDFType0x33::getY4() const
{
    return y4;
}

int SWPSOTADDFType0x33::getDd() const
{
    return dd;
}

int SWPSOTADDFType0x33::getF() const
{
    return f;
}

int SWPSOTADDFType0x33::isWasAlarm() const
{

    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = 0x00;
    if(1 == getF()) {
        mask = static_cast<uint8_t>(0x20);
    } else if(2 == getF()) {
        mask = static_cast<uint8_t>(0x40);
    }

    if(static_cast<uint8_t>(byteWord().at(5)) & mask)
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

SWPSOTADDFType0x33::SWPSOTADDFType0x33(const StateWord &stateWord, const int y4, const int dd, const int f) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
  , f(f)
{
}

SWPSOTADDFType0x33::~SWPSOTADDFType0x33()
{

}
