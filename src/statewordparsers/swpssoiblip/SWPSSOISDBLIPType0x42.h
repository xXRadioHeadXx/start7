#ifndef SWPSSOISDBLIPTYPE0X42_H
#define SWPSSOISDBLIPTYPE0X42_H

#include "SWP.h"

class SWPSSOISDBLIPType0x42 : public SWP
{
    uint8_t _mask = 0x00;
public:
    SWPSSOISDBLIPType0x42(const StateWord &stateWord, int numSD);

    SWPSSOISDBLIPType0x42(const SWPSSOISDBLIPType0x42&) = default;
    SWPSSOISDBLIPType0x42(SWPSSOISDBLIPType0x42&&) = default;
    SWPSSOISDBLIPType0x42 & operator=(const SWPSSOISDBLIPType0x42&) = default;
    SWPSSOISDBLIPType0x42& operator=(SWPSSOISDBLIPType0x42&&) = default;

    virtual ~SWPSSOISDBLIPType0x42();

    int isInAlarm() const;
    int isShortCircuit() const;
    int isLineBreak() const;
    uint8_t mask() const;};

#endif // SWPSSOISDBLIPTYPE0X42_H
