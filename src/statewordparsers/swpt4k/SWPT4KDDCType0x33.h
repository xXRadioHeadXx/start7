#ifndef SWPT4KDDCTYPE0X33_H
#define SWPT4KDDCTYPE0X33_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/SWPFault.h"
#include "../src/statewordparsers/SWPWasAlarm.h"
#include "../src/statewordparsers/SWPLevel.h"
#include "../src/statewordparsers/SWPCliff.h"
#include "../src/statewordparsers/SWPClosure.h"

class SWPT4KDDCFType0x33;
class SWPT4KDDCType0x33 :
        public SWP
      , public SWPWasAlarm
      , public SWPClosure
      , public SWPCliff
      , public SWPLevel<int>
{
    int y4;
    int dd;
    int c;

public:
    SWPT4KDDCType0x33(const StateWord &stateWord,const int y4, const int dd, const int c);

    SWPT4KDDCType0x33(const SWPT4KDDCType0x33&) = default;
    SWPT4KDDCType0x33(SWPT4KDDCType0x33&&) = default;
    SWPT4KDDCType0x33 & operator=(const SWPT4KDDCType0x33&) = default;
    SWPT4KDDCType0x33& operator=(SWPT4KDDCType0x33&&) = default;

    virtual ~SWPT4KDDCType0x33();
    int getY4() const;
    int getDd() const;
    int getC() const;

    virtual int isWasAlarm() const final;
    virtual int isClosure() const final;
    virtual int isCliff() const final;
    virtual int level() const final;

    SWPT4KDDCFType0x33 f(int num);
    SWPT4KDDCFType0x33 f1();
    SWPT4KDDCFType0x33 f2();

};

#endif // SWPT4KDDCTYPE0X33_H
