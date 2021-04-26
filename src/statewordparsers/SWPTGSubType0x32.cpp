#include "SWPTGSubType0x32.h"

SWPTGSubType0x32::SWPTGSubType0x32(const QByteArray &stateWord, const int flang) :
    SWP(stateWord),
    flang(flang)
{
}

SWPTGSubType0x32::SWPTGSubType0x32(const SWPTGSubType0x32 &parent) :
    SWP(parent),
    flang(parent.getFlang())
{
}

SWPTGSubType0x32::~SWPTGSubType0x32() {

}

int SWPTGSubType0x32::getFlang() const
{
    return flang;
}

int SWPTGSubType0x32::isInAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x01))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x04))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isOutAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x02))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x08))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isExistDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGSubType0x32::isWasDK() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGSubType0x32::isInOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGSubType0x32::isWasOpened() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGSubType0x32::isFault() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isSideAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isOpened() const
{
    return isInOpened();
}

int SWPTGSubType0x32::isAlarm() const
{
    return isInAlarm();
}


int SWPTGSubType0x32::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGSubType0x32::threshold() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        return getStateWord().mid(3,2).toInt();
    }
    case 2: {
        return getStateWord().mid(5,2).toInt();
    }
    case 3: {
        return getStateWord().mid(7,2).toInt();
    }
    case 4: {
        return getStateWord().mid(9,2).toInt();
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isInAlarmFlt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x01))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x08))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x01))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x08))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isInAlarmFlt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x02))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x10))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x02))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x10))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isInAlarmFlt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x04))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(getStateWord().at(11)) & static_cast<quint8>(0x20))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x04))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(getStateWord().at(12)) & static_cast<quint8>(0x20))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x32::isAlarmFlt1() const
{
    return isInAlarmFlt1();
}

int SWPTGSubType0x32::isAlarmFlt2() const
{
    return isInAlarmFlt2();
}

int SWPTGSubType0x32::isAlarmFlt3() const
{
    return isInAlarmFlt3();
}

int SWPTGSubType0x32::isNormFlt1() const
{
    int isalarm = isAlarmFlt1();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGSubType0x32::isNormFlt2() const
{
    int isalarm = isAlarmFlt2();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGSubType0x32::isNormFlt3() const
{
    int isalarm = isAlarmFlt3();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}
