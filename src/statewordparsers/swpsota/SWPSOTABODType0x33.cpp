#include "../src/statewordparsers/swpsota/SWPSOTABODType0x33.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDType0x33.h"
#include "../src/statewordparsers/swpsota/SWPSOTAY4Type0x33.h"

SWPSOTABODType0x33::SWPSOTABODType0x33(const StateWord &stateWord) :
    SWP(stateWord)
{

}

SWPSOTABODType0x33::~SWPSOTABODType0x33() {

}

int SWPSOTABODType0x33::getDd() const
{
    if(byteWord().isEmpty())
        return -1;
    return static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0b01111111);
}

int SWPSOTABODType0x33::getY4() const
{
    if(byteWord().isEmpty())
        return -1;
    return 0x00 == (static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x80)) ? 0 : 1;
}

SWPSOTAY4Type0x33 SWPSOTABODType0x33::y(int num) const
{
    return SWPSOTAY4Type0x33(getStateWord(), num);
}

SWPSOTAY4Type0x33 SWPSOTABODType0x33::y1() const {
    return y(1);
}

SWPSOTAY4Type0x33 SWPSOTABODType0x33::y2() const {
    return y(2);
}

SWPSOTAY4Type0x33 SWPSOTABODType0x33::y3() const {
    return y(3);
}

SWPSOTAY4Type0x33 SWPSOTABODType0x33::y4() const {
    return y(4);
}

SWPSOTADDType0x33 SWPSOTABODType0x33::dd() const
{
    return SWPSOTADDType0x33(getStateWord(), getY4(), getDd());
}

int SWPSOTABODType0x33::isReady() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Ready;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x33::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x10))
        return 1; //Status::On;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x33::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x33::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Opened;
    else
        return 0; //Status::Not;
}

int SWPSOTABODType0x33::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was;
    else
        return 0; //Status::Not;
}
