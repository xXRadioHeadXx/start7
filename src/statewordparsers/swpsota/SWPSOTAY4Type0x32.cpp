#include "SWPSOTADDType0x32.h"
#include "SWPSOTAY4Type0x32.h"

SWPSOTAY4Type0x32::SWPSOTAY4Type0x32(const StateWord &stateWord, const int y4) :
    SWP(stateWord)
  , y4(y4)
{

}

SWPSOTAY4Type0x32::~SWPSOTAY4Type0x32() {

}

int SWPSOTAY4Type0x32::getY4() const
{
    return y4;
}

int SWPSOTAY4Type0x32::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = 0x00;
    switch (getY4()) {
    case 1:
        mask = 0x01;
        break;
    case 2:
        mask = 0x02;
        break;
    case 3:
        mask = 0x04;
        break;
    case 4:
        mask = 0x08;
        break;
    default:
        mask = 0x00;
        break;
    }

    if(static_cast<uint8_t>(byteWord().at(0)) & mask)
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPSOTAY4Type0x32::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    uint8_t mask = 0x00;
    switch (getY4()) {
    case 1:
        mask = 0x10;
        break;
    case 2:
        mask = 0x20;
        break;
    case 3:
        mask = 0x40;
        break;
    case 4:
        mask = 0x80;
        break;
    default:
        mask = 0x00;
        break;
    }

    if(static_cast<uint8_t>(byteWord().at(0)) & mask)
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

SWPSOTADDType0x32 SWPSOTAY4Type0x32::dd(int num) const
{
    return SWPSOTADDType0x32(getStateWord(), getY4(), num);
}