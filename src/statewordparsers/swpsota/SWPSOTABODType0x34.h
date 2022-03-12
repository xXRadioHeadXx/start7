#ifndef SWPSOTABODTYPE0X34_H
#define SWPSOTABODTYPE0X34_H

#include <SWP.h>

class SWPSOTADDType0x34;
class SWPSOTABODType0x34 : public SWP
{
public:
    SWPSOTABODType0x34(const StateWord &stateWord);

    SWPSOTABODType0x34(const SWPSOTABODType0x34&) = default;
    SWPSOTABODType0x34(SWPSOTABODType0x34&&) = default;
    SWPSOTABODType0x34 & operator=(const SWPSOTABODType0x34&) = default;
    SWPSOTABODType0x34& operator=(SWPSOTABODType0x34&&) = default;

    virtual ~SWPSOTABODType0x34();

    int getDd() const;
    int getY4() const;

    SWPSOTADDType0x34 dd() const;

};

#endif // SWPSOTABODTYPE0X34_H
