#include "../src/statewordparsers/swpt4k/SWPT4KBODType0x34.h"
#include "../src/statewordparsers/swpt4k/SWPT4KDDType0x34.h"

SWPT4KBODType0x34::SWPT4KBODType0x34(const StateWord &stateWord) :
    SWP(stateWord)
{

}

SWPT4KBODType0x34::~SWPT4KBODType0x34()
{

}

int SWPT4KBODType0x34::getDd() const
{
    if(byteWord().isEmpty())
        return -1;
    return static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0b01111111);
}

int SWPT4KBODType0x34::getY4() const
{
    if(byteWord().isEmpty())
        return -1;
    return 0x00 == (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x80)) ? 0 : 1;
}

SWPT4KDDType0x34 SWPT4KBODType0x34::dd() const
{
    return SWPT4KDDType0x34(getStateWord(), getY4(), getDd());
}

