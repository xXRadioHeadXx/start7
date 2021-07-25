#ifndef SWPSDBLIPTYPE0X42_H
#define SWPSDBLIPTYPE0X42_H

#include "SWP.h"

class SWPSDBLIPType0x42 : public SWP
{
    quint8 _mask = 0x00;
public:
    SWPSDBLIPType0x42(const StateWord &stateWord, int numSD);

    SWPSDBLIPType0x42(const SWPSDBLIPType0x42&) = default;
    SWPSDBLIPType0x42(SWPSDBLIPType0x42&&) = default;
    SWPSDBLIPType0x42 & operator=(const SWPSDBLIPType0x42&) = default;
    SWPSDBLIPType0x42& operator=(SWPSDBLIPType0x42&&) = default;

    virtual ~SWPSDBLIPType0x42();

    int isInAlarm() const;
    int isShortCircuit() const;
    int isLineBreak() const;
    quint8 mask() const;

};

#endif // SWPSDBLIPTYPE0X42_H
