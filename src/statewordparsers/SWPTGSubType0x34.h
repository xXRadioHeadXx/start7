#ifndef SWPTGSUBTYPE0X34_H
#define SWPTGSUBTYPE0X34_H

#include "SWP.h"


class SWPTGSubType0x34 : public SWP
{
public:
    SWPTGSubType0x34(const QByteArray &stateWord);
    SWPTGSubType0x34(const SWPTGSubType0x34 & parent);
    virtual ~SWPTGSubType0x34();

    int numberIn() const;
    int isOnFlt1() const;
    int isOffFlt1() const;
    int isOnFlt2() const;
    int isOffFlt2() const;
    int isOnFlt3() const;
    int isOffFlt3() const;
    int thresholdFlt1() const;
    int thresholdFlt2() const;
    int thresholdFlt3() const;

};

#endif // SWPTGSUBTYPE0X34_H
