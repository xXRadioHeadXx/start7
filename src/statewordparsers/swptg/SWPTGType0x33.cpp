#include "../src/statewordparsers/swptg/SWPTGType0x33.h"

#include "../src/statewordparsers/swptg/SWPTGSubType0x33.h"

SWPTGType0x33::SWPTGType0x33(const StateWord &stateWord) :
    SWP(stateWord)
{

}

//SWPTGType0x33::SWPTGType0x33(const QByteArray &byteWord) :
//    SWP(byteWord)
//{
//}


SWPTGType0x33::~SWPTGType0x33() {

}

int SWPTGType0x33::isInAlarmC1() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC1() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC2() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC2() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(0)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC1() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC2() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x02))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC3() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC4() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x08))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC3() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC3() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC4() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x40))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC4() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & static_cast<uint8_t>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC1() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x01))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC2() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC3() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x04))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC4() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(2)) & static_cast<uint8_t>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOpened() const
{
    return ((1 == isInOpened() && 1 == isWasOpened()) ? 1 : (-1 == isInOpened() || -1 == isWasOpened()) ? -1 : 0);
}

int SWPTGType0x33::isAlarmC1() const
{
    return ((1 == isInAlarmC1() && 1 == isOutAlarmC1()) ? 1 : ((-1 == isInAlarmC1() || -1 == isOutAlarmC1()) ? -1 : 0));
}

int SWPTGType0x33::isNormC1() const
{
    return ((1 == isOutAlarmC1() || 1 == isAlarmC1() || 1 == isOpened() || 1 == isInOpened() || 1 == isFaultC1()) ? 0 : ((-1 == isAlarmC1() || -1 == isOpened() || -1 == isFaultC1()) ? -1 : 1));
    int isalarm = isAlarmC1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC2() const
{
    return ((1 == isInAlarmC2() && 1 == isOutAlarmC2()) ? 1 : ((-1 == isInAlarmC2() || -1 == isOutAlarmC2()) ? -1 : 0));
}

int SWPTGType0x33::isNormC2() const
{
    return ((1 == isOutAlarmC2() || 1 == isAlarmC2() || 1 == isOpened() || 1 == isInOpened() || 1 == isFaultC2()) ? 0 : ((-1 == isAlarmC2() || -1 == isOpened() || -1 == isFaultC2()) ? -1 : 1));
    int isalarm = isAlarmC2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC3() const
{
    return ((1 == isInAlarmC3() && 1 == isOutAlarmC3()) ? 1 : ((-1 == isInAlarmC3() || -1 == isOutAlarmC3()) ? -1 : 0));
}

int SWPTGType0x33::isNormC3() const
{
    return ((1 == isOutAlarmC3() || 1 == isAlarmC3() || 1 == isOpened() || 1 == isInOpened() || 1 == isFaultC3()) ? 0 : ((-1 == isAlarmC3() || -1 == isOpened() || -1 == isFaultC3()) ? -1 : 1));
    int isalarm = isAlarmC3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC4() const
{
    return ((1 == isInAlarmC4() && 1 == isOutAlarmC4()) ? 1 : ((-1 == isInAlarmC4() || -1 == isOutAlarmC4()) ? -1 : 0));
}

int SWPTGType0x33::isNormC4() const
{
    return ((1 == isOutAlarmC4() || 1 == isAlarmC4() || 1 == isOpened() || 1 == isInOpened() || 1 == isFaultC4()) ? 0 : ((-1 == isAlarmC4() || -1 == isOpened() || -1 == isFaultC4()) ? -1 : 1));
    int isalarm = isAlarmC4();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

SWPTGSubType0x33 SWPTGType0x33::C(int num) const
{
    return SWPTGSubType0x33(getStateWord(), num);
}

SWPTGSubType0x33 SWPTGType0x33::C1() const
{
    return C(1);
}
SWPTGSubType0x33 SWPTGType0x33::C2() const
{
    return C(2);
}
SWPTGSubType0x33 SWPTGType0x33::C3() const
{
    return C(3);
}
SWPTGSubType0x33 SWPTGType0x33::C4() const
{
    return C(4);
}

int SWPTGType0x33::isAlarm() const
{
    int result = 0;
    for(int ci = 1, n = 5; ci < n; ci++) {
        if(1 == C(ci).isAlarm()) {
            return 1;
        }

        if(0 != C(ci).isAlarm()) {
            result = -1;
        }
    }
    return result;
}

