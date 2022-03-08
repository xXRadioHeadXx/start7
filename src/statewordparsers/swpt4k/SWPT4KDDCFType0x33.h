#ifndef SWPT4KDDCFTYPE0X33_H
#define SWPT4KDDCFTYPE0X33_H

#include <SWP.h>
#include <SWPWasAlarm.h>

class SWPT4KDDCFType0x33 :
        public SWP
      , public SWPWasAlarm
{
    int y4;
    int dd;
    int c;
    int f;
public:
    SWPT4KDDCFType0x33(const StateWord &stateWord, const int y4, const int dd, const int c, const int f);

    SWPT4KDDCFType0x33(const SWPT4KDDCFType0x33&) = default;
    SWPT4KDDCFType0x33(SWPT4KDDCFType0x33&&) = default;
    SWPT4KDDCFType0x33 & operator=(const SWPT4KDDCFType0x33&) = default;
    SWPT4KDDCFType0x33& operator=(SWPT4KDDCFType0x33&&) = default;

    virtual ~SWPT4KDDCFType0x33();
    int getY4() const;
    int getDd() const;
    int getC() const;
    int getF() const;

    virtual int isWasAlarm() const final;

};

#endif // SWPT4KDDCFTYPE0X33_H
