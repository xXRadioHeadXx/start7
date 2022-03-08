#ifndef SWPT4KY4TYPE0X33_H
#define SWPT4KY4TYPE0X33_H

#include <SWP.h>
#include "SWPInAlarm.h"
#include "SWPWasAlarm.h"

class SWPT4KY4Type0x33 :
        public SWP
      , public SWPInAlarm
      , public SWPWasAlarm
{
    int y4;
public:
    SWPT4KY4Type0x33(const StateWord &stateWord, const int y4);

    SWPT4KY4Type0x33(const SWPT4KY4Type0x33&) = default;
    SWPT4KY4Type0x33(SWPT4KY4Type0x33&&) = default;
    SWPT4KY4Type0x33 & operator=(const SWPT4KY4Type0x33&) = default;
    SWPT4KY4Type0x33& operator=(SWPT4KY4Type0x33&&) = default;

    virtual ~SWPT4KY4Type0x33();
    int getY4() const;

    virtual int isInAlarm() const final;
    virtual int isWasAlarm() const final;
};

#endif // SWPT4KY4TYPE0X33_H
