#ifndef SWPT4KDDCTYPE0X32_H
#define SWPT4KDDCTYPE0X32_H

#include "SWP.h"
#include "SWPFault.h"
#include "SWPWasAlarm.h"

class SWPT4KDDCType0x32 :
        public SWP
      , public SWPWasAlarm
      , public SWPFault
{
    int y4;
    int dd;
    int c;

    int index() const;
public:
    SWPT4KDDCType0x32(const StateWord &stateWord,const int y4, const int dd, const int c);

    SWPT4KDDCType0x32(const SWPT4KDDCType0x32&) = default;
    SWPT4KDDCType0x32(SWPT4KDDCType0x32&&) = default;
    SWPT4KDDCType0x32 & operator=(const SWPT4KDDCType0x32&) = default;
    SWPT4KDDCType0x32& operator=(SWPT4KDDCType0x32&&) = default;

    virtual ~SWPT4KDDCType0x32();
    int getY4() const;
    int getDd() const;
    int getC() const;

    virtual int isWasAlarm() const final;
    virtual int isFault() const final;
};

#endif // SWPT4KDDCTYPE0X32_H
