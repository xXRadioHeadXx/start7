#include "SWPTGSubType0x32.h"
#include "SWPTGType0x32.h"

SWPTGType0x32::SWPTGType0x32(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGType0x32::SWPTGType0x32(const SWPTGType0x32 &parent) :
    SWP(parent)
{
}

SWPTGType0x32::~SWPTGType0x32() {

}

int SWPTGType0x32::isInAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isOutAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isOutAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isWasOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isFaultC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isFaultC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isFaultC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isFaultC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isOutAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isOutAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isSideAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isSideAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isSideAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isSideAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isOpened() const
{
    return isInOpened();
}

int SWPTGType0x32::isAlarmC1() const
{
    return isInAlarmC1();
}

int SWPTGType0x32::isNormC1() const
{
    int isalarm = isAlarmC1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmC2() const
{
    return isInAlarmC2();
}

int SWPTGType0x32::isNormC2() const
{
    int isalarm = isAlarmC2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmC3() const
{
    return isInAlarmC3();
}

int SWPTGType0x32::isNormC3() const
{
    int isalarm = isAlarmC3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmC4() const
{
    return isInAlarmC4();
}

int SWPTGType0x32::isNormC4() const
{
    int isalarm = isAlarmC4();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::thresholdIn1() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(3,2).toInt();
}

int SWPTGType0x32::thresholdIn2() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(5,2).toInt();
}

int SWPTGType0x32::thresholdIn3() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(7,2).toInt();
}

int SWPTGType0x32::thresholdIn4() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(9,2).toInt();
}

int SWPTGType0x32::isInAlarmIn1Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn1Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x02))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn1Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType0x32::isInAlarmIn2Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x08))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn2Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn2Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x20))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType0x32::isInAlarmIn3Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn3Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x02))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn3Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType0x32::isInAlarmIn4Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x08))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn4Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isInAlarmIn4Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x20))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x32::isAlarmIn1Flt1() const
{
    return isInAlarmIn1Flt1();
}

int SWPTGType0x32::isNormIn1Flt1() const
{
    int isalarm = isAlarmIn1Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn1Flt2() const
{
    return isInAlarmIn1Flt2();
}

int SWPTGType0x32::isNormIn1Flt2() const
{
    int isalarm = isAlarmIn1Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn1Flt3() const
{
    return isInAlarmIn1Flt3();
}

int SWPTGType0x32::isNormIn1Flt3() const
{
    int isalarm = isAlarmIn1Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn2Flt1() const
{
    return isInAlarmIn2Flt1();
}

int SWPTGType0x32::isNormIn2Flt1() const
{
    int isalarm = isAlarmIn2Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn2Flt2() const
{
    return isInAlarmIn2Flt2();
}

int SWPTGType0x32::isNormIn2Flt2() const
{
    int isalarm = isAlarmIn2Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn2Flt3() const
{
    return isInAlarmIn2Flt3();
}

int SWPTGType0x32::isNormIn2Flt3() const
{
    int isalarm = isAlarmIn2Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn3Flt1() const
{
    return isInAlarmIn3Flt1();
}

int SWPTGType0x32::isNormIn3Flt1() const
{
    int isalarm = isAlarmIn3Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn3Flt2() const
{
    return isInAlarmIn3Flt2();
}

int SWPTGType0x32::isNormIn3Flt2() const
{
    int isalarm = isAlarmIn3Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn3Flt3() const
{
    return isInAlarmIn3Flt3();
}

int SWPTGType0x32::isNormIn3Flt3() const
{
    int isalarm = isAlarmIn3Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn4Flt1() const
{
    return isInAlarmIn4Flt1();
}

int SWPTGType0x32::isNormIn4Flt1() const
{
    int isalarm = isAlarmIn4Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn4Flt2() const
{
    return isInAlarmIn4Flt2();
}

int SWPTGType0x32::isNormIn4Flt2() const
{
    int isalarm = isAlarmIn4Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x32::isAlarmIn4Flt3() const
{
    return isInAlarmIn4Flt3();
}

int SWPTGType0x32::isNormIn4Flt3() const
{
    int isalarm = isAlarmIn4Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

SWPTGSubType0x32 SWPTGType0x32::C(int num) const
{
    return SWPTGSubType0x32(getStateWord(), num);
}

SWPTGSubType0x32 SWPTGType0x32::C1() const
{
    return C(1);
}
SWPTGSubType0x32 SWPTGType0x32::C2() const
{
    return C(2);
}
SWPTGSubType0x32 SWPTGType0x32::C3() const
{
    return C(3);
}
SWPTGSubType0x32 SWPTGType0x32::C4() const
{
    return C(4);
}

int SWPTGType0x32::isAlarm() const
{
    int result = 0;
    for(int ci = 1, n = 5; ci < n; ci++) {
        if(1 == C(ci).isInAlarm() ||
           1 == C(ci).isOutAlarm() ||
           1 == C(ci).isInAlarmFlt1() ||
           1 == C(ci).isInAlarmFlt2() ||
           1 == C(ci).isInAlarmFlt3()) {
            return 1;
        }

        if(0 != C(ci).isInAlarm() ||
           0 != C(ci).isOutAlarm() ||
           0 != C(ci).isInAlarmFlt1() ||
           0 != C(ci).isInAlarmFlt2() ||
           0 != C(ci).isInAlarmFlt3()) {
            result = -1;
        }
    }
    return result;
}
