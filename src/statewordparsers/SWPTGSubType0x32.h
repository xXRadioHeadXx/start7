#ifndef SWPTGSUBTYPE0X32_H
#define SWPTGSUBTYPE0X32_H

#include "SWP.h"

class SWPTGSubType0x32 : public SWP
{
private:
    const int flang;
public:
    SWPTGSubType0x32(const StateWord &stateWord, const int flang);
//    SWPTGSubType0x32(const QByteArray &byteWord, const int flang);
    SWPTGSubType0x32(const SWPTGSubType0x32 & parent);
    virtual ~SWPTGSubType0x32();
    int getFlang() const;


    int isOutAlarm() const;
    int isInAlarm() const;

    int isExistDK() const;
    int isWasDK() const;

    int isInOpened() const;
    int isWasOpened() const;

    int isFault() const;

    int isSideAlarm() const;

    int isOpened() const;

    int isAlarm() const;
    int isNorm() const;

    int voltage() const;

    int isInAlarmFlt1() const;
    int isInAlarmFlt2() const;
    int isInAlarmFlt3() const;

    int isAlarmFlt1() const;
    int isNormFlt1() const;

    int isAlarmFlt2() const;
    int isNormFlt2() const;

    int isAlarmFlt3() const;
    int isNormFlt3() const;
};

#endif // SWPTGSUBTYPE0X32_H
