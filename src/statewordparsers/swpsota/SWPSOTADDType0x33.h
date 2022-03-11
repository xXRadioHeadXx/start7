#ifndef SWPSOTADDTYPE0X33_H
#define SWPSOTADDTYPE0X33_H

#include <SWP.h>
#include "SWPWasOpened.h"
#include "SWPInCommunicationBreak.h"
#include "SWPWasCommunicationBreak.h"
#include "SWPFault.h"
#include "SWPInterrogation.h"
#include "SWPFault.h"
#include "SWPWasAlarm.h"
#include "SWPLevel.h"


class SWPSOTADDFType0x33;
class SWPSOTADDType0x33 :
        public SWP
      , public SWPWasOpened
      , public SWPInCommunicationBreak
      , public SWPWasCommunicationBreak
      , public SWPFault
      , public SWPInterrogation
      , public SWPWasAlarm
      , public SWPLevel<int>
{
    int y4;
    int dd;

public:
    SWPSOTADDType0x33(const StateWord &stateWord,const int y4, const int dd);

    SWPSOTADDType0x33(const SWPSOTADDType0x33&) = default;
    SWPSOTADDType0x33(SWPSOTADDType0x33&&) = default;
    SWPSOTADDType0x33 & operator=(const SWPSOTADDType0x33&) = default;
    SWPSOTADDType0x33& operator=(SWPSOTADDType0x33&&) = default;

    virtual ~SWPSOTADDType0x33();

    int getY4() const;
    int getDd() const;

    virtual int isFault() const final;
    virtual int isInCommunicationBreak() const final;
    virtual int isWasCommunicationBreak() const final;
    virtual int isWasOpened() const final;
    virtual int isInterrogation() const final;
    virtual int isWasAlarm() const final;
    virtual int level() const final;

    SWPSOTADDFType0x33 f(int num);
    SWPSOTADDFType0x33 f1();
    SWPSOTADDFType0x33 f2();
};

#endif // SWPSOTADDTYPE0X33_H
