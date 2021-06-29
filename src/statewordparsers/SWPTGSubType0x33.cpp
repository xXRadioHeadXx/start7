#include "SWPTGSubType0x33.h"

int SWPTGSubType0x33::getFlang() const
{
    return flang;
}

int SWPTGSubType0x33::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x01))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x04))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x10))
            return 1; //Status::Alarm);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x40))
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
    if(byteWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x02))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x08))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x20))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x80))
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
    if(byteWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x01))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x02))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x04))
            return 1; //Status::Exist);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(byteWord().at(1)) & static_cast<quint8>(0x08))
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
    if(byteWord().isEmpty())
        return -1;
    switch (getFlang()) {
    case 1: {
        if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x01))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 2: {
        if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x02))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 3: {
        if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x04))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    case 4: {
        if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x08))
            return 1; //Status::Was);
        else
            return 0; //Status::Not;
    }
    default: {
        return -1;
    }
    }
}

int SWPTGSubType0x33::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGSubType0x33::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(0)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}


int SWPTGSubType0x33::isOpened() const
{
    return ((1 == isInOpened() && 1 == isWasOpened())) ? 1 : ((-1 == isInOpened() || -1 == isWasOpened()) ? -1 : 0);
}

int SWPTGSubType0x33::isAlarm() const
{
    return ((1 == isInAlarm() && 1 == isOutAlarm())) ? 1 : ((-1 == isInAlarm() || -1 == isOutAlarm()) ? -1 : 0);
}

int SWPTGSubType0x33::isNorm() const
{
    return ((1 == isOutAlarm() || 1 == isAlarm() || 1 == isOpened() || 1 == isInOpened() || 1 == isFault()) ? 0 : ((-1 == isAlarm() || -1 == isOpened() || -1 == isFault()) ? -1 : 1));
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

SWPTGSubType0x33::SWPTGSubType0x33(const StateWord &stateWord, const int flang) :
    SWP(stateWord),
    flang(flang)
{

}

//SWPTGSubType0x33::SWPTGSubType0x33(const QByteArray byteWord, const int flang) :
//    SWP(byteWord),
//    flang(flang)
//{

//}

SWPTGSubType0x33::SWPTGSubType0x33(const SWPTGSubType0x33 &parent) :
       SWP(parent),
       flang(parent.getFlang())
{

}

SWPTGSubType0x33::~SWPTGSubType0x33()
{

}
