#include "SWPTGType0x33.h"

SWPTGType0x33::SWPTGType0x33(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGType0x33::SWPTGType0x33(const SWPTGType0x33 &parent) :
    SWP(parent)
{
}

SWPTGType0x33::~SWPTGType0x33() {

}

int SWPTGType0x33::isInAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x01))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isWasOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isFaultC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isInAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOutAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isSideAlarmC4() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x33::isOpened() const
{
    return isInOpened();
}

int SWPTGType0x33::isAlarmC1() const
{
    return isInAlarmC1();
}

int SWPTGType0x33::isNormC1() const
{
    int isalarm = isAlarmC1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC2() const
{
    return isInAlarmC2();
}

int SWPTGType0x33::isNormC2() const
{
    int isalarm = isAlarmC2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC3() const
{
    return isInAlarmC3();
}

int SWPTGType0x33::isNormC3() const
{
    int isalarm = isAlarmC3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x33::isAlarmC4() const
{
    return isInAlarmC4();
}

int SWPTGType0x33::isNormC4() const
{
    int isalarm = isAlarmC4();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}
