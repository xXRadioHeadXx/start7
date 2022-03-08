#ifndef SWPTGTYPE0X34_H
#define SWPTGTYPE0X34_H

#include "SWP.h"
#include "swptg/SWPTGSubType0x34.h"

class SWPTGType0x34 : public SWP
{
public:
    SWPTGType0x34(const StateWord &stateWord);
//    SWPTGType0x34(const QByteArray &byteWord);

    SWPTGType0x34(const SWPTGType0x34&) = default;
    SWPTGType0x34(SWPTGType0x34&&) = default;
    SWPTGType0x34 & operator=(const SWPTGType0x34&) = default;
    SWPTGType0x34& operator=(SWPTGType0x34&&) = default;

    virtual ~SWPTGType0x34();

    SWPTGSubType0x34 C(int numIn) const;

    SWPTGSubType0x34 C1() const;
    SWPTGSubType0x34 C2() const;
    SWPTGSubType0x34 C3() const;
    SWPTGSubType0x34 C4() const;
};

#endif // SWPTGTYPE0X34_H
