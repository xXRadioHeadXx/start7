#include "SWPTGType0x34.h"

SWPTGType2::SWPTGType2(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGType2::SWPTGType2(const SWPTGType2 &parent) :
    SWP(parent)
{
}

SWPTGType2::~SWPTGType2() {

}

SWPTGSubType2 SWPTGType2::in1() const
{
    return SWPTGSubType2(getStateWord().mid(0, 7));
}

SWPTGSubType2 SWPTGType2::in2() const
{
    return SWPTGSubType2(getStateWord().mid(7, 7));

}

SWPTGSubType2 SWPTGType2::in3() const
{
    return SWPTGSubType2(getStateWord().mid(14, 7));

}

SWPTGSubType2 SWPTGType2::in4() const
{
    return SWPTGSubType2(getStateWord().mid(21, 7));

}
