#ifndef SWPTGTYPE0X31_H
#define SWPTGTYPE0X31_H

#include <SWP.h>

class SWPTGType1 : public SWP
{
public:
    SWPTGType1(const QByteArray &stateWord);
    SWPTGType1(const SWPTGType1 & parent);
    virtual ~SWPTGType1();

    int isOn() const;
    int isOff() const;
    int isAlarm() const;
    int isInAlarm() const;
    int isOutAlarm() const;
    int isNorm() const;
    int isWasAlarm() const;
    int isExistDK() const;
    int isWasDK() const;
    int isOpened() const;
    int isInOpened() const;
    int isWasOpened() const;
};

#endif // SWPTGTYPE0X31_H
