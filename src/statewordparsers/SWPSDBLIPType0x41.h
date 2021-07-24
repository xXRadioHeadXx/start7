#ifndef SWPSDBLIPTYPE0X41_H
#define SWPSDBLIPTYPE0X41_H

#include "SWP.h"

class SWPSDBLIPType0x41 : public SWP
{
    quint8 _mask = 0x00;
public:
    SWPSDBLIPType0x41(const StateWord &stateWord, int numSD);
//    SWPSDBLIP(const QByteArray &stateWord, int numSD);
    SWPSDBLIPType0x41(const SWPSDBLIPType0x41 & parent);
    virtual ~SWPSDBLIPType0x41();

    int isAlarm() const;
    int isInAlarm() const;
    int isNorm() const;
    int isWasAlarm() const;
    int isOn() const;
    int isOff() const;
    quint8 mask() const;
};

#endif // SWPSDBLIPTYPE0X41_H
