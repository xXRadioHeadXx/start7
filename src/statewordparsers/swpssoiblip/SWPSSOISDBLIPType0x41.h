#ifndef SWPSSOISDBLIPTYPE0X41_H
#define SWPSSOISDBLIPTYPE0X41_H

#include "SWP.h"

class SWPSSOISDBLIPType0x41 : public SWP
{
    uint8_t _mask = 0x00;
public:
    SWPSSOISDBLIPType0x41(const StateWord &stateWord, int numSD);

    SWPSSOISDBLIPType0x41(const SWPSSOISDBLIPType0x41&) = default;
    SWPSSOISDBLIPType0x41(SWPSSOISDBLIPType0x41&&) = default;
    SWPSSOISDBLIPType0x41 & operator=(const SWPSSOISDBLIPType0x41&) = default;
    SWPSSOISDBLIPType0x41& operator=(SWPSSOISDBLIPType0x41&&) = default;

    virtual ~SWPSSOISDBLIPType0x41();

    int isAlarm() const;
    int isInAlarm() const;
    int isNorm() const;
    int isInNorm() const;
    int isWasAlarm() const;
    int isOn() const;
    int isOff() const;
    uint8_t mask() const;
    int isOpened() const;
    int isInOpened() const;
    int isWasOpened() const;
};

#endif // SWPSSOISDBLIPTYPE0X41_H
