#include "../src/statewordparsers/swpt4k/SWPT4KBODType0x32.h"
#include "../src/statewordparsers/swpt4k/SWPT4KY4Type0x32.h"

SWPT4KBODType0x32::SWPT4KBODType0x32(const StateWord &stateWord) :
    SWP(stateWord)
{

}

SWPT4KBODType0x32::~SWPT4KBODType0x32() {

}

SWPT4KY4Type0x32 SWPT4KBODType0x32::y(int num) const
{
    return SWPT4KY4Type0x32(getStateWord(), num);
}

SWPT4KY4Type0x32 SWPT4KBODType0x32::y1() const {
    return y(1);
}

SWPT4KY4Type0x32 SWPT4KBODType0x32::y2() const {
    return y(2);
}

SWPT4KY4Type0x32 SWPT4KBODType0x32::y3() const {
    return y(3);
}

SWPT4KY4Type0x32 SWPT4KBODType0x32::y4() const {
    return y(4);
}

int SWPT4KBODType0x32::isReady() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Ready;
    else
        return 0; //Status::Not;
}

int SWPT4KBODType0x32::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x10))
        return 1; //Status::On;
    else
        return 0; //Status::Not;
}

int SWPT4KBODType0x32::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPT4KBODType0x32::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Opened;
    else
        return 0; //Status::Not;
}

int SWPT4KBODType0x32::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}
