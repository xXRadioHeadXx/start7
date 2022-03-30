#include "SWPSOTADDFType0x33.h"
#include "SWPSOTADDType0x33.h"
#include "SWPSOTADDType0x33.h"

int SWPSOTADDType0x33::getY4() const
{
    return y4;
}

int SWPSOTADDType0x33::getDd() const
{
    return dd;
}


SWPSOTADDType0x33::SWPSOTADDType0x33(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPSOTADDType0x33::~SWPSOTADDType0x33()
{

}

int SWPSOTADDType0x33::isFault() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x10))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::isInCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x02))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::isWasCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::isInterrogation() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(5)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Exist;
    else
        return 0; //Status::Not;
}

int SWPSOTADDType0x33::level() const
{
    if(byteWord().isEmpty())
        return -1;
    return (static_cast<uint16_t>(byteWord().at(3)) << 8) | (static_cast<uint16_t>(byteWord().at(4)) & 0x00FF);
}

SWPSOTADDFType0x33 SWPSOTADDType0x33::f(int num)
{
    return SWPSOTADDFType0x33(getStateWord(), getY4(), getDd(), num);
}

SWPSOTADDFType0x33 SWPSOTADDType0x33::f1()
{
    return f(1);
}

SWPSOTADDFType0x33 SWPSOTADDType0x33::f2()
{
    return f(2);
}
