#ifndef SWPTGSUBTYPE0X34_H
#define SWPTGSUBTYPE0X34_H

#include "SWP.h"


class SWPTGSubType2 : public SWP
{
public:
    SWPTGSubType2(const QByteArray &stateWord);
    SWPTGSubType2(const SWPTGSubType2 & parent);
    virtual ~SWPTGSubType2();

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
