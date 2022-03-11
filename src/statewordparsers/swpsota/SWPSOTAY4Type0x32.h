#ifndef SWPSOTAY4TYPE0X32_H
#define SWPSOTAY4TYPE0X32_H

#include "SWP.h"
#include "SWPInAlarm.h"
#include "SWPWasAlarm.h"

class SWPSOTADDType0x32;
class SWPSOTAY4Type0x32 :
        public SWP
      , public SWPInAlarm
      , public SWPWasAlarm
{
    int y4;
public:
    SWPSOTAY4Type0x32(const StateWord &stateWord, const int y4);

    SWPSOTAY4Type0x32(const SWPSOTAY4Type0x32&) = default;
    SWPSOTAY4Type0x32(SWPSOTAY4Type0x32&&) = default;
    SWPSOTAY4Type0x32 & operator=(const SWPSOTAY4Type0x32&) = default;
    SWPSOTAY4Type0x32& operator=(SWPSOTAY4Type0x32&&) = default;

    virtual ~SWPSOTAY4Type0x32();
    int getY4() const;

    virtual int isInAlarm() const final;
    virtual int isWasAlarm() const final;

    SWPSOTADDType0x32 dd(int num) const;
};

#endif // SWPSOTAY4TYPE0X32_H
