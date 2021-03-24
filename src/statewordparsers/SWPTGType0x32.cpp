#include "SWPTGType0x32.h"

SWPTGType4::SWPTGType4(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGType4::SWPTGType4(const SWPTGType4 &parent) :
    SWP(parent)
{
}

SWPTGType4::~SWPTGType4() {

}

int SWPTGType4::isInAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isOutAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isOutAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isWasOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isFaultC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isFaultC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isFaultC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isFaultC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isOutAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isOutAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isSideAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isSideAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isSideAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isSideAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isOpened() const
{
    return isInOpened();
}

int SWPTGType4::isAlarmC1() const
{
    return isInAlarmC1();
}

int SWPTGType4::isNormC1() const
{
    int isalarm = isAlarmC1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmC2() const
{
    return isInAlarmC2();
}

int SWPTGType4::isNormC2() const
{
    int isalarm = isAlarmC2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmC3() const
{
    return isInAlarmC3();
}

int SWPTGType4::isNormC3() const
{
    int isalarm = isAlarmC3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmC4() const
{
    return isInAlarmC4();
}

int SWPTGType4::isNormC4() const
{
    int isalarm = isAlarmC4();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::thresholdIn1() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(3,2).toInt();
}

int SWPTGType4::thresholdIn2() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(5,2).toInt();
}

int SWPTGType4::thresholdIn3() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(7,2).toInt();
}

int SWPTGType4::thresholdIn4() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(9,2).toInt();
}

int SWPTGType4::isInAlarmIn1Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn1Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x02))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn1Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType4::isInAlarmIn2Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x08))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn2Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn2Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x20))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType4::isInAlarmIn3Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn3Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x02))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn3Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}


int SWPTGType4::isInAlarmIn4Flt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x08))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn4Flt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isInAlarmIn4Flt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x20))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType4::isAlarmIn1Flt1() const
{
    return isInAlarmIn1Flt1();
}

int SWPTGType4::isNormIn1Flt1() const
{
    int isalarm = isAlarmIn1Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn1Flt2() const
{
    return isInAlarmIn1Flt2();
}

int SWPTGType4::isNormIn1Flt2() const
{
    int isalarm = isAlarmIn1Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn1Flt3() const
{
    return isInAlarmIn1Flt3();
}

int SWPTGType4::isNormIn1Flt3() const
{
    int isalarm = isAlarmIn1Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn2Flt1() const
{
    return isInAlarmIn2Flt1();
}

int SWPTGType4::isNormIn2Flt1() const
{
    int isalarm = isAlarmIn2Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn2Flt2() const
{
    return isInAlarmIn2Flt2();
}

int SWPTGType4::isNormIn2Flt2() const
{
    int isalarm = isAlarmIn2Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn2Flt3() const
{
    return isInAlarmIn2Flt3();
}

int SWPTGType4::isNormIn2Flt3() const
{
    int isalarm = isAlarmIn2Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn3Flt1() const
{
    return isInAlarmIn3Flt1();
}

int SWPTGType4::isNormIn3Flt1() const
{
    int isalarm = isAlarmIn3Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn3Flt2() const
{
    return isInAlarmIn3Flt2();
}

int SWPTGType4::isNormIn3Flt2() const
{
    int isalarm = isAlarmIn3Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn3Flt3() const
{
    return isInAlarmIn3Flt3();
}

int SWPTGType4::isNormIn3Flt3() const
{
    int isalarm = isAlarmIn3Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn4Flt1() const
{
    return isInAlarmIn4Flt1();
}

int SWPTGType4::isNormIn4Flt1() const
{
    int isalarm = isAlarmIn4Flt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn4Flt2() const
{
    return isInAlarmIn4Flt2();
}

int SWPTGType4::isNormIn4Flt2() const
{
    int isalarm = isAlarmIn4Flt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType4::isAlarmIn4Flt3() const
{
    return isInAlarmIn4Flt3();
}

int SWPTGType4::isNormIn4Flt3() const
{
    int isalarm = isAlarmIn4Flt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}
