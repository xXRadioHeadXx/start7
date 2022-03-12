#ifndef SWPSOTADDFTYPE0X34_H
#define SWPSOTADDFTYPE0X34_H

#include "SWPCountImpact.h"
#include "SWPDurationOvercoming.h"
#include "SWPTimeImpact.h"
#include "SWPThreshold.h"
#include <SWPOff.h>
#include <SWPOn.h>
#include "SWP.h"

class SWPSOTADDFType0x34 :
        public SWP
      , public SWPOff
      , public SWPOn
      , public SWPThreshold<int>
      , public SWPTimeImpact<float>
      , public SWPCountImpact<int>
      , public SWPDurationOvercoming<int>
{
    int y4;
    int dd;
    int f;
public:
    SWPSOTADDFType0x34(const StateWord &stateWord, const int y4, const int dd, const int f);

    SWPSOTADDFType0x34(const SWPSOTADDFType0x34&) = default;
    SWPSOTADDFType0x34(SWPSOTADDFType0x34&&) = default;
    SWPSOTADDFType0x34 & operator=(const SWPSOTADDFType0x34&) = default;
    SWPSOTADDFType0x34& operator=(SWPSOTADDFType0x34&&) = default;

    virtual ~SWPSOTADDFType0x34();
    int getY4() const;
    int getDd() const;
    int getC() const;
    int getF() const;

    int threshold() const override;
    float timeImpact() const override;
    int countImpact() const override;
    int durationOvercoming() const override;
    int isOff() const override;
    int isOn() const override;
};

#endif // SWPSOTADDFTYPE0X34_H
