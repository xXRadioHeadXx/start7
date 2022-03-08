#include "SWPT4KDDType0x33.h"
#include "SWPT4KDDCType0x33.h"

int SWPT4KDDType0x33::getY4() const
{
    return y4;
}

int SWPT4KDDType0x33::getDd() const
{
    return dd;
}


SWPT4KDDType0x33::SWPT4KDDType0x33(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPT4KDDType0x33::~SWPT4KDDType0x33()
{

}

SWPT4KDDCType0x33 SWPT4KDDType0x33::c(int num) const
{
    return SWPT4KDDCType0x33(getStateWord(), getY4(), getDd(), num);
}

SWPT4KDDCType0x33 SWPT4KDDType0x33::c1() const
{
    return c(1);
}

SWPT4KDDCType0x33 SWPT4KDDType0x33::c2() const
{
    return c(2);
}

int SWPT4KDDType0x33::isFault() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(7)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x33::isInCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(8)) & static_cast<uint8_t>(0x10))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x33::isWasCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(8)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x33::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(8)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x33::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(8)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x33::isInterrogation() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(7)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}
