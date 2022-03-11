#ifndef SWPSOTADDTYPE0X32_H
#define SWPSOTADDTYPE0X32_H

#include "SWP.h"
#include "SWPWasAlarm.h"
#include "SWPFault.h"
#include "SWPInCommunicationBreak.h"
#include "SWPWasCommunicationBreak.h"

class SWPSOTADDCType0x32;
class SWPSOTADDType0x32 :
        public SWP
      , public SWPWasAlarm
      , public SWPFault
      , public SWPInCommunicationBreak
      , public SWPWasCommunicationBreak
{
    int y4;
    int dd;

    int index() const;
public:
    SWPSOTADDType0x32(const StateWord &stateWord,const int y4, const int dd);

    SWPSOTADDType0x32(const SWPSOTADDType0x32&) = default;
    SWPSOTADDType0x32(SWPSOTADDType0x32&&) = default;
    SWPSOTADDType0x32 & operator=(const SWPSOTADDType0x32&) = default;
    SWPSOTADDType0x32& operator=(SWPSOTADDType0x32&&) = default;

    virtual ~SWPSOTADDType0x32();

    int getY4() const;
    int getDd() const;

    int isInCommunicationBreak() const override;
    int isWasCommunicationBreak() const override;
    int isWasAlarm() const override;
    int isFault() const override;

};

#endif // SWPSOTADDTYPE0X32_H
