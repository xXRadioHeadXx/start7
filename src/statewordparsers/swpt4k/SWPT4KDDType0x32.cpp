#include "SWPT4KDDCType0x32.h"
#include "SWPT4KDDType0x32.h"

int SWPT4KDDType0x32::getY4() const
{
    return y4;
}

int SWPT4KDDType0x32::getDd() const
{
    return dd;
}



int SWPT4KDDType0x32::index() const
{
    int index = 1;
    if(2 < getY4()) {
        index += 26;
    }
    index += getDd();
    return index;
}

SWPT4KDDType0x32::SWPT4KDDType0x32(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPT4KDDType0x32::~SWPT4KDDType0x32() {

}

int SWPT4KDDType0x32::isInCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x10))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x32::isWasCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x32::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x40))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPT4KDDType0x32::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

SWPT4KDDCType0x32 SWPT4KDDType0x32::c(int num) const
{
    return SWPT4KDDCType0x32(getStateWord(), getY4(), getDd(), num);
}

SWPT4KDDCType0x32 SWPT4KDDType0x32::c1() const
{
    return c(1);
}

SWPT4KDDCType0x32 SWPT4KDDType0x32::c2() const
{
    return c(2);
}


