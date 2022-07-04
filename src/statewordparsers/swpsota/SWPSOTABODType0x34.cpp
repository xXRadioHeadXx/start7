#include "../src/statewordparsers/swpsota/SWPSOTABODType0x34.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDType0x34.h"

SWPSOTABODType0x34::SWPSOTABODType0x34(const StateWord &stateWord) :
    SWP(stateWord)
{

}

SWPSOTABODType0x34::~SWPSOTABODType0x34()
{

}

int SWPSOTABODType0x34::getDd() const
{
    if(byteWord().isEmpty())
        return -1;
    return static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0b01111111);
}

int SWPSOTABODType0x34::getY4() const
{
    if(byteWord().isEmpty())
        return -1;
    return 0x00 == (static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x80)) ? 0 : 1;
}

SWPSOTADDType0x34 SWPSOTABODType0x34::dd() const
{
    return SWPSOTADDType0x34(getStateWord(), getY4(), getDd());
}

