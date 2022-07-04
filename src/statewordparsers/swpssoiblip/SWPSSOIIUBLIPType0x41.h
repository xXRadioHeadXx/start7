#ifndef SWPSSOIIUBLIPTYPE0X41_H
#define SWPSSOIIUBLIPTYPE0X41_H

#include "../src/statewordparsers/SWP.h"


class SWPSSOIIUBLIPType0x41 : public SWP
{
    uint8_t _mask = 0x00;
public:
    SWPSSOIIUBLIPType0x41(const StateWord &stateWord, int numIU);
//    SWPIUBLIP(const QByteArray &byteWord, int numIU);

    SWPSSOIIUBLIPType0x41(const SWPSSOIIUBLIPType0x41&) = default;
    SWPSSOIIUBLIPType0x41(SWPSSOIIUBLIPType0x41&&) = default;
    SWPSSOIIUBLIPType0x41 & operator=(const SWPSSOIIUBLIPType0x41&) = default;
    SWPSSOIIUBLIPType0x41& operator=(SWPSSOIIUBLIPType0x41&&) = default;

    virtual ~SWPSSOIIUBLIPType0x41();

    int isOutAlarm() const;
    int isOn() const;
    int isOff() const;
    uint8_t mask() const;
};

#endif // SWPSSOIIUBLIPTYPE0X41_H
