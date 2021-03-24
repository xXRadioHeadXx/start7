#ifndef SWPTGTYPE0X34_H
#define SWPTGTYPE0X34_H

#include <SWP.h>
#include <SWPTGSubType0x34.h>

class SWPTGType2 : public SWP
{
public:
    SWPTGType2(const QByteArray &stateWord);
    SWPTGType2(const SWPTGType2 & parent);
    virtual ~SWPTGType2();

    SWPTGSubType2 in(int numIn) const{
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
        return SWPTGSubType2(QByteArray());
    };

    SWPTGSubType2 in1() const;
    SWPTGSubType2 in2() const;
    SWPTGSubType2 in3() const;
    SWPTGSubType2 in4() const;
};

#endif // SWPTGTYPE0X34_H
