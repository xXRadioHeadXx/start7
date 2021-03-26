#include "SWPTGType0x34.h"

SWPTGType0x34::SWPTGType0x34(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGType0x34::SWPTGType0x34(const SWPTGType0x34 &parent) :
    SWP(parent)
{
}

SWPTGType0x34::~SWPTGType0x34() {

}

SWPTGSubType0x34 SWPTGType0x34::in1() const
{
    return SWPTGSubType0x34(getStateWord().mid(0, 7));
}

SWPTGSubType0x34 SWPTGType0x34::in2() const
{
    return SWPTGSubType0x34(getStateWord().mid(7, 7));

}

SWPTGSubType0x34 SWPTGType0x34::in3() const
{
    return SWPTGSubType0x34(getStateWord().mid(14, 7));

}

SWPTGSubType0x34 SWPTGType0x34::in4() const
{
    return SWPTGSubType0x34(getStateWord().mid(21, 7));

}