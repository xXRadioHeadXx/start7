#ifndef SWPT4KDDTYPE0X33_H
#define SWPT4KDDTYPE0X33_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/SWPInOpened.h"
#include "../src/statewordparsers/SWPWasOpened.h"
#include "../src/statewordparsers/SWPInCommunicationBreak.h"
#include "../src/statewordparsers/SWPWasCommunicationBreak.h"
#include "../src/statewordparsers/SWPFault.h"
#include "../src/statewordparsers/SWPInterrogation.h"


class SWPT4KDDCType0x33;
class SWPT4KDDType0x33 :
        public SWP
      , public SWPInOpened
      , public SWPWasOpened
      , public SWPInCommunicationBreak
      , public SWPWasCommunicationBreak
      , public SWPFault
      , public SWPInterrogation
{
    int y4;
    int dd;

public:
    SWPT4KDDType0x33(const StateWord &stateWord,const int y4, const int dd);

    SWPT4KDDType0x33(const SWPT4KDDType0x33&) = default;
    SWPT4KDDType0x33(SWPT4KDDType0x33&&) = default;
    SWPT4KDDType0x33 & operator=(const SWPT4KDDType0x33&) = default;
    SWPT4KDDType0x33& operator=(SWPT4KDDType0x33&&) = default;

    virtual ~SWPT4KDDType0x33();

    int getY4() const;
    int getDd() const;

    virtual int isFault() const final;
    virtual int isInCommunicationBreak() const final;
    virtual int isWasCommunicationBreak() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;
    virtual int isInterrogation() const final;

    SWPT4KDDCType0x33 c(int num) const;
    SWPT4KDDCType0x33 c1() const;
    SWPT4KDDCType0x33 c2() const;

};

#endif // SWPT4KDDTYPE0X33_H
