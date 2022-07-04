#ifndef SWPSOTADDTYPE0X34_H
#define SWPSOTADDTYPE0X34_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/SWPWeakening.h"

class SWPSOTADDFType0x34;
class SWPSOTADDType0x34 :
        public SWP
{
    int y4;
    int dd;
public:
    SWPSOTADDType0x34(const StateWord &stateWord, const int y4, const int dd);

    SWPSOTADDType0x34(const SWPSOTADDType0x34&) = default;
    SWPSOTADDType0x34(SWPSOTADDType0x34&&) = default;
    SWPSOTADDType0x34 & operator=(const SWPSOTADDType0x34&) = default;
    SWPSOTADDType0x34& operator=(SWPSOTADDType0x34&&) = default;

    virtual ~SWPSOTADDType0x34();
    int getY4() const;
    int getDd() const;

    SWPSOTADDFType0x34 f(int num);
};

#endif // SWPSOTADDTYPE0X34_H
