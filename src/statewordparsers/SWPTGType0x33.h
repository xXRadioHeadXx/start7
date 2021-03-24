#ifndef SWPTGTYPE0X33_H
#define SWPTGTYPE0X33_H

#include "SWP.h"

class SWPTGType3 : public SWP
{
public:
    SWPTGType3(const QByteArray &stateWord);
    SWPTGType3(const SWPTGType3 & parent);
    virtual ~SWPTGType3();

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

};

#endif // SWPTGTYPE0X33_H
