#ifndef SWPSOTADDCTYPE0X32_H
#define SWPSOTADDCTYPE0X32_H

#include "SWP.h"
#include "SWPFault.h"
#include "SWPWasAlarm.h"

class SWPSOTADDCType0x32 :
        public SWP
      , public SWPWasAlarm
      , public SWPFault
{
    int y4;
    int dd;
    int c;

    int index() const;
public:
    SWPSOTADDCType0x32(const StateWord &stateWord,const int y4, const int dd, const int c);

    SWPSOTADDCType0x32(const SWPSOTADDCType0x32&) = default;
    SWPSOTADDCType0x32(SWPSOTADDCType0x32&&) = default;
    SWPSOTADDCType0x32 & operator=(const SWPSOTADDCType0x32&) = default;
    SWPSOTADDCType0x32& operator=(SWPSOTADDCType0x32&&) = default;

    virtual ~SWPSOTADDCType0x32();
    int getY4() const;
    int getDd() const;
    int getC() const;

    virtual int isWasAlarm() const final;
    virtual int isFault() const final;
};

#endif // SWPSOTADDCTYPE0X32_H
