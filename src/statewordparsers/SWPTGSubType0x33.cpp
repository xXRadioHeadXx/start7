#include "SWPTGSubType0x33.h"

int SWPTGSubType0x33::getFlang() const
{
    return flang;
}

int SWPTGSubType0x33::isInAlarm() const
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

int SWPTGSubType0x33::isOutAlarm() const
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

int SWPTGSubType0x33::isFault() const
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

int SWPTGSubType0x33::isSideAlarm() const
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

int SWPTGSubType0x33::isAlarm() const
{
    return isInAlarm();
}

int SWPTGSubType0x33::isNorm() const
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

SWPTGSubType0x33::SWPTGSubType0x33(const QByteArray stateWord, const int flang) :
    SWP(stateWord),
    flang(flang)
{

}

SWPTGSubType0x33::SWPTGSubType0x33(const SWPTGSubType0x33 &parent) :
       SWP(parent),
       flang(parent.getFlang())
{

}
