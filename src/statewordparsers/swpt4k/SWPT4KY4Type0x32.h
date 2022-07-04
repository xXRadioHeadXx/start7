#ifndef SWPT4KY4TYPE0X32_H
#define SWPT4KY4TYPE0X32_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/SWPInAlarm.h"
#include "../src/statewordparsers/SWPWasAlarm.h"

class SWPT4KDDType0x32;
class SWPT4KY4Type0x32 :
        public SWP
      , public SWPInAlarm
      , public SWPWasAlarm
{
    int y4;
public:
    SWPT4KY4Type0x32(const StateWord &stateWord, const int y4);

    SWPT4KY4Type0x32(const SWPT4KY4Type0x32&) = default;
    SWPT4KY4Type0x32(SWPT4KY4Type0x32&&) = default;
    SWPT4KY4Type0x32 & operator=(const SWPT4KY4Type0x32&) = default;
    SWPT4KY4Type0x32& operator=(SWPT4KY4Type0x32&&) = default;

    virtual ~SWPT4KY4Type0x32();
    int getY4() const;

    virtual int isInAlarm() const final;
    virtual int isWasAlarm() const final;

    SWPT4KDDType0x32 dd(int num) const;
};

#endif // SWPT4KY4TYPE0X32_H
