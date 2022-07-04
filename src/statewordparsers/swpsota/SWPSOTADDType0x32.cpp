#include "../src/statewordparsers/swpsota/SWPSOTADDCType0x32.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDType0x32.h"

int SWPSOTADDType0x32::getY4() const
{
    return y4;
}

int SWPSOTADDType0x32::getDd() const
{
    return dd;
}



int SWPSOTADDType0x32::index() const
{
    int index = 1;
    if(2 < getY4()) {
        index += 50;
    }
    index += ((getDd() / 2) + (getDd() % 2));
    return index;
}

SWPSOTADDType0x32::SWPSOTADDType0x32(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPSOTADDType0x32::~SWPSOTADDType0x32() {

}

int SWPSOTADDType0x32::isInCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x02))
            return 1; //Status::Exist;
        else
            return 0; //Status::Not;
    } else if(0 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x20))
            return 1; //Status::Exist;
        else
            return 0; //Status::Not;
    }
    return -1;
}

int SWPSOTADDType0x32::isWasCommunicationBreak() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x04))
            return 1; //Status::Was;
        else
            return 0; //Status::Not;
    } else if(0 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x40))
            return 1; //Status::Was;
        else
            return 0; //Status::Not;
    }
    return -1;
}

int SWPSOTADDType0x32::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x01))
            return 1; //Status::Was;
        else
            return 0; //Status::Not;
    } else if(0 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x10))
            return 1; //Status::Was;
        else
            return 0; //Status::Not;
    }
    return -1;
}

int SWPSOTADDType0x32::isFault() const
{
    if(byteWord().isEmpty())
        return -1;
    if(1 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x08))
            return 1; //Status::Fault;
        else
            return 0; //Status::Not;
    } else if(0 == (getDd() % 2)) {
        if(static_cast<uint8_t>(byteWord().at(index())) & static_cast<uint8_t>(0x80))
            return 1; //Status::Fault;
        else
            return 0; //Status::Not;
    }
    return -1;
}


