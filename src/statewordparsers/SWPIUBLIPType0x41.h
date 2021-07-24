#ifndef SWPIUBLIPTYPE0X41_H
#define SWPIUBLIPTYPE0X41_H

#include "SWP.h"

class SWPIUBLIPType0x41 : public SWP
{
    quint8 _mask = 0x00;
public:
    SWPIUBLIPType0x41(const StateWord &stateWord, int numIU);
//    SWPIUBLIP(const QByteArray &byteWord, int numIU);
    SWPIUBLIPType0x41(const SWPIUBLIPType0x41 & parent);
    virtual ~SWPIUBLIPType0x41();

    int isOutAlarm() const;
    int isOn() const;
    int isOff() const;
    quint8 mask() const;
};

#endif // SWPIUBLIPTYPE0X41_H
