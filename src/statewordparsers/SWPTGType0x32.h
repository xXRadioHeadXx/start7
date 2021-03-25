#ifndef SWPTGTYPE0X32_H
#define SWPTGTYPE0X32_H

#include "SWP.h"

class SWPTGType0x32 : public SWP
{
public:
    SWPTGType0x32(const QByteArray &stateWord);
    SWPTGType0x32(const SWPTGType0x32 & parent);
    virtual ~SWPTGType0x32();

    int isInAlarmC1() const;
    int isOutAlarmC1() const;

    int isInAlarmC2() const;
    int isOutAlarmC2() const;

    int isExistDK() const;
    int isWasDK() const;

    int isInOpened() const;
    int isWasOpened() const;

    int isFaultC1() const;
    int isFaultC2() const;
    int isFaultC3() const;
    int isFaultC4() const;

    int isInAlarmC3() const;
    int isOutAlarmC3() const;

    int isInAlarmC4() const;
    int isOutAlarmC4() const;

    int isSideAlarmC1() const;
    int isSideAlarmC2() const;
    int isSideAlarmC3() const;
    int isSideAlarmC4() const;

    int isOpened() const;

    int isAlarmC1() const;
    int isNormC1() const;

    int isAlarmC2() const;
    int isNormC2() const;

    int isAlarmC3() const;
    int isNormC3() const;

    int isAlarmC4() const;
    int isNormC4() const;

    int thresholdIn1() const;
    int thresholdIn2() const;
    int thresholdIn3() const;
    int thresholdIn4() const;

    int isInAlarmIn1Flt1() const;
    int isInAlarmIn1Flt2() const;
    int isInAlarmIn1Flt3() const;

    int isInAlarmIn2Flt1() const;
    int isInAlarmIn2Flt2() const;
    int isInAlarmIn2Flt3() const;

    int isInAlarmIn3Flt1() const;
    int isInAlarmIn3Flt2() const;
    int isInAlarmIn3Flt3() const;

    int isInAlarmIn4Flt1() const;
    int isInAlarmIn4Flt2() const;
    int isInAlarmIn4Flt3() const;

    int isAlarmIn1Flt1() const;
    int isNormIn1Flt1() const;

    int isAlarmIn1Flt2() const;
    int isNormIn1Flt2() const;

    int isAlarmIn1Flt3() const;
    int isNormIn1Flt3() const;

    int isAlarmIn2Flt1() const;
    int isNormIn2Flt1() const;

    int isAlarmIn2Flt2() const;
    int isNormIn2Flt2() const;

    int isAlarmIn2Flt3() const;
    int isNormIn2Flt3() const;

    int isAlarmIn3Flt1() const;
    int isNormIn3Flt1() const;

    int isAlarmIn3Flt2() const;
    int isNormIn3Flt2() const;

    int isAlarmIn3Flt3() const;
    int isNormIn3Flt3() const;

    int isAlarmIn4Flt1() const;
    int isNormIn4Flt1() const;

    int isAlarmIn4Flt2() const;
    int isNormIn4Flt2() const;

    int isAlarmIn4Flt3() const;
    int isNormIn4Flt3() const;



};

#endif // SWPTGTYPE0X32_H
