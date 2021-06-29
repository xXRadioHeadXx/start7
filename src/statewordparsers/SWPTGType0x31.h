#ifndef SWPTGTYPE0X31_H
#define SWPTGTYPE0X31_H

#include "SWP.h"

class SWPTGType0x31 : public SWP
{
public:
    SWPTGType0x31(const StateWord &stateWord);
//    SWPTGType0x31(const QByteArray byteWord);
    SWPTGType0x31(const SWPTGType0x31 & parent);
    virtual ~SWPTGType0x31();

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
