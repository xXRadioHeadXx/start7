#ifndef SWPTGTYPE0X33_H
#define SWPTGTYPE0X33_H

#include "SWP.h"

class SWPTGSubType0x33;
class SWPTGType0x33 : public SWP
{
public:
    SWPTGType0x33(const StateWord &stateWord);
//    SWPTGType0x33(const QByteArray &byteWord);

    SWPTGType0x33(const SWPTGType0x33&) = default;
    SWPTGType0x33(SWPTGType0x33&&) = default;
    SWPTGType0x33 & operator=(const SWPTGType0x33&) = default;
    SWPTGType0x33& operator=(SWPTGType0x33&&) = default;


    virtual ~SWPTGType0x33();

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

    SWPTGSubType0x33 C(int num) const;
    SWPTGSubType0x33 C1() const;
    SWPTGSubType0x33 C2() const;
    SWPTGSubType0x33 C3() const;
    SWPTGSubType0x33 C4() const;

    int isAlarm() const;

};

#endif // SWPTGTYPE0X33_H
