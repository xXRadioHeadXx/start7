#ifndef SWPT4KDDCFTYPE0X34_H
#define SWPT4KDDCFTYPE0X34_H

#include "../src/statewordparsers/SWPCountImpact.h"
#include "../src/statewordparsers/SWPDurationOvercoming.h"
#include "../src/statewordparsers/SWPTimeImpact.h"
#include "../src/statewordparsers/SWPThreshold.h"
#include "../src/statewordparsers/SWPOff.h"
#include "../src/statewordparsers/SWPOn.h"
#include "../src/statewordparsers/SWP.h"

class SWPT4KDDCFType0x34 :
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
    int c;
    int f;
public:
    SWPT4KDDCFType0x34(const StateWord &stateWord, const int y4, const int dd, const int c, const int f);

    SWPT4KDDCFType0x34(const SWPT4KDDCFType0x34&) = default;
    SWPT4KDDCFType0x34(SWPT4KDDCFType0x34&&) = default;
    SWPT4KDDCFType0x34 & operator=(const SWPT4KDDCFType0x34&) = default;
    SWPT4KDDCFType0x34& operator=(SWPT4KDDCFType0x34&&) = default;

    virtual ~SWPT4KDDCFType0x34();
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

#endif // SWPT4KDDCFTYPE0X34_H
