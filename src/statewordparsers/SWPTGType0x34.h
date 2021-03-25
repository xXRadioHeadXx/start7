#ifndef SWPTGTYPE0X34_H
#define SWPTGTYPE0X34_H

#include <SWP.h>
#include <SWPTGSubType0x34.h>

class SWPTGType0x34 : public SWP
{
public:
    SWPTGType0x34(const QByteArray &stateWord);
    SWPTGType0x34(const SWPTGType0x34 & parent);
    virtual ~SWPTGType0x34();

    SWPTGSubType0x34 in(int numIn) const{
        switch (numIn) {
        case 1:
        return in1();
        case 2:
        return in2();
        case 3:
        return in3();
        case 4:
        return in4();
        }
        return SWPTGSubType0x34(QByteArray());
    };

    SWPTGSubType0x34 in1() const;
    SWPTGSubType0x34 in2() const;
    SWPTGSubType0x34 in3() const;
    SWPTGSubType0x34 in4() const;
};

#endif // SWPTGTYPE0X34_H
