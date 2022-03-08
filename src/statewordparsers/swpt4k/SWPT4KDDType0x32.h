#ifndef SWPT4KDDTYPE0X32_H
#define SWPT4KDDTYPE0X32_H

#include "SWP.h"
#include "SWPInOpened.h"
#include "SWPWasOpened.h"
#include "SWPInCommunicationBreak.h"
#include "SWPWasCommunicationBreak.h"

class SWPT4KDDCType0x32;
class SWPT4KDDType0x32 :
        public SWP
      , public SWPInOpened
      , public SWPWasOpened
      , public SWPInCommunicationBreak
      , public SWPWasCommunicationBreak
{
    int y4;
    int dd;

    int index() const;
public:
    SWPT4KDDType0x32(const StateWord &stateWord,const int y4, const int dd);

    SWPT4KDDType0x32(const SWPT4KDDType0x32&) = default;
    SWPT4KDDType0x32(SWPT4KDDType0x32&&) = default;
    SWPT4KDDType0x32 & operator=(const SWPT4KDDType0x32&) = default;
    SWPT4KDDType0x32& operator=(SWPT4KDDType0x32&&) = default;

    virtual ~SWPT4KDDType0x32();

    int getY4() const;
    int getDd() const;

    virtual int isInCommunicationBreak() const final;
    virtual int isWasCommunicationBreak() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;

    SWPT4KDDCType0x32 c(int num) const;
    SWPT4KDDCType0x32 c1() const;
    SWPT4KDDCType0x32 c2() const;

};

#endif // SWPT4KDDTYPE0X32_H
