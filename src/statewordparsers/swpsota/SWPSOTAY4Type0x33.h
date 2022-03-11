#ifndef SWPSOTAY4TYPE0X33_H
#define SWPSOTAY4TYPE0X33_H

#include <SWP.h>
#include "SWPInAlarm.h"
#include "SWPWasAlarm.h"

class SWPSOTAY4Type0x33 :
        public SWP
      , public SWPInAlarm
      , public SWPWasAlarm
{
    int y4;
public:
    SWPSOTAY4Type0x33(const StateWord &stateWord, const int y4);

    SWPSOTAY4Type0x33(const SWPSOTAY4Type0x33&) = default;
    SWPSOTAY4Type0x33(SWPSOTAY4Type0x33&&) = default;
    SWPSOTAY4Type0x33 & operator=(const SWPSOTAY4Type0x33&) = default;
    SWPSOTAY4Type0x33& operator=(SWPSOTAY4Type0x33&&) = default;

    virtual ~SWPSOTAY4Type0x33();
    int getY4() const;

    virtual int isInAlarm() const final;
    virtual int isWasAlarm() const final;
};

#endif // SWPSOTAY4TYPE0X33_H
