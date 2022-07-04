#include "../src/statewordparsers/swptg/SWPTGType0x34.h"

SWPTGType0x34::SWPTGType0x34(const StateWord &stateWord) :
    SWP(stateWord)
{

}

//SWPTGType0x34::SWPTGType0x34(const QByteArray &byteWord) :
//    SWP(byteWord)
//{
//}


SWPTGType0x34::~SWPTGType0x34() {

}

SWPTGSubType0x34 SWPTGType0x34::C(int numIn) const
{
    switch (numIn) {
    case 1:
    return C1();
    case 2:
    return C2();
    case 3:
    return C3();
    case 4:
    return C4();
    default:
    return SWPTGSubType0x34(StateWord());
    }
}

SWPTGSubType0x34 SWPTGType0x34::C1() const
{
    return SWPTGSubType0x34(StateWord(byteWord().mid(0, 7), cdate()));
}

SWPTGSubType0x34 SWPTGType0x34::C2() const
{
    return SWPTGSubType0x34(StateWord(byteWord().mid(7, 7), cdate()));

}

SWPTGSubType0x34 SWPTGType0x34::C3() const
{
    return SWPTGSubType0x34(StateWord(byteWord().mid(14, 7), cdate()));

}

SWPTGSubType0x34 SWPTGType0x34::C4() const
{
    return SWPTGSubType0x34(StateWord(byteWord().mid(21, 7), cdate()));

}
