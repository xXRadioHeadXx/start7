#ifndef SWPSOTADDFTYPE0X33_H
#define SWPSOTADDFTYPE0X33_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/SWPWasAlarm.h"

class SWPSOTADDFType0x33 :
        public SWP
      , public SWPWasAlarm
{
    int y4;
    int dd;
    int f;
public:
    SWPSOTADDFType0x33(const StateWord &stateWord, const int y4, const int dd, const int f);

    SWPSOTADDFType0x33(const SWPSOTADDFType0x33&) = default;
    SWPSOTADDFType0x33(SWPSOTADDFType0x33&&) = default;
    SWPSOTADDFType0x33 & operator=(const SWPSOTADDFType0x33&) = default;
    SWPSOTADDFType0x33& operator=(SWPSOTADDFType0x33&&) = default;

    virtual ~SWPSOTADDFType0x33();
    int getY4() const;
    int getDd() const;
    int getF() const;

    virtual int isWasAlarm() const final;

};

#endif // SWPSOTADDFTYPE0X33_H
