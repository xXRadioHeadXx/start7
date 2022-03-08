#ifndef SWPIUBLIPTYPE0X41_H
#define SWPIUBLIPTYPE0X41_H

#include "SWP.h"

class SWPIUBLIPType0x41 : public SWP
{
    uint8_t _mask = 0x00;
public:
    SWPIUBLIPType0x41(const StateWord &stateWord, int numIU);
//    SWPIUBLIP(const QByteArray &byteWord, int numIU);

    SWPIUBLIPType0x41(const SWPIUBLIPType0x41&) = default;
    SWPIUBLIPType0x41(SWPIUBLIPType0x41&&) = default;
    SWPIUBLIPType0x41 & operator=(const SWPIUBLIPType0x41&) = default;
    SWPIUBLIPType0x41& operator=(SWPIUBLIPType0x41&&) = default;

    virtual ~SWPIUBLIPType0x41();

    int isOutAlarm() const;
    int isOn() const;
    int isOff() const;
    uint8_t mask() const;
};

#endif // SWPIUBLIPTYPE0X41_H
