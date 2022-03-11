#include "SWPSOTABODType0x32.h"
#include "SWPSOTAY4Type0x32.h"

SWPSOTABODType0x32::SWPSOTABODType0x32(const StateWord &stateWord) :
    SWP(stateWord)
{

}

SWPSOTABODType0x32::~SWPSOTABODType0x32() {

}

SWPSOTAY4Type0x32 SWPSOTABODType0x32::y(int num) const
{
    return SWPSOTAY4Type0x32(getStateWord(), num);
}

SWPSOTAY4Type0x32 SWPSOTABODType0x32::y1() const {
    return y(1);
}

SWPSOTAY4Type0x32 SWPSOTABODType0x32::y2() const {
    return y(2);
}

SWPSOTAY4Type0x32 SWPSOTABODType0x32::y3() const {
    return y(3);
}

SWPSOTAY4Type0x32 SWPSOTABODType0x32::y4() const {
    return y(4);
}

int SWPSOTABODType0x32::isReady() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Ready;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x32::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x10))
        return 1; //Status::On;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x32::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x32::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Opened;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x32::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}
