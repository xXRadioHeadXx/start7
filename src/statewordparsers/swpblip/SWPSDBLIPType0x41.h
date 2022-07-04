#ifndef SWPSDBLIPTYPE0X41_H
#define SWPSDBLIPTYPE0X41_H

#include "../src/statewordparsers/SWP.h"

class SWPSDBLIPType0x41 : public SWP
{
    uint8_t _mask = 0x00;
public:
    SWPSDBLIPType0x41(const StateWord &stateWord, int numSD);

    SWPSDBLIPType0x41(const SWPSDBLIPType0x41&) = default;
    SWPSDBLIPType0x41(SWPSDBLIPType0x41&&) = default;
    SWPSDBLIPType0x41 & operator=(const SWPSDBLIPType0x41&) = default;
    SWPSDBLIPType0x41& operator=(SWPSDBLIPType0x41&&) = default;

    virtual ~SWPSDBLIPType0x41();

    int isAlarm() const;
    int isInAlarm() const;
    int isNorm() const;
    int isWasAlarm() const;
    int isOn() const;
    int isOff() const;
    uint8_t mask() const;
};

#endif // SWPSDBLIPTYPE0X41_H
