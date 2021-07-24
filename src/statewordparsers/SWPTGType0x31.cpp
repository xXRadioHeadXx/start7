#include "SWPTGType0x31.h"

SWPTGType0x31::SWPTGType0x31(const StateWord &stateWord) :
    SWP(stateWord)
{
}


//SWPTGType0x31::SWPTGType0x31(const QByteArray byteWord) :
//    SWP(byteWord)
//{
//}


SWPTGType0x31::~SWPTGType0x31() {

}

int SWPTGType0x31::isOn() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPTGType0x31::isOff() const
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPTGType0x31::isAlarm() const
{
    return ((1 == isInAlarm() && 1 == isOutAlarm() && 1 == isWasAlarm()) ? 1 : ((-1 == isInAlarm() || -1 == isOutAlarm() || -1 == isWasAlarm()) ? -1 : 0));
}

int SWPTGType0x31::isInAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x04))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isOutAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x02))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isNorm() const
{
    return ((1 == isOutAlarm() || 1 == isAlarm() || 1 == isOpened() || 1 == isInOpened()) ? 0 : ((-1 == isAlarm() || -1 == isOpened()) ? -1 : 1));
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int SWPTGType0x31::isWasAlarm() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isOpened() const
{
    return ((1 == isInOpened() && 1 == isWasOpened()) ? 1 : (-1 == isInOpened() || -1 == isWasOpened()) ? -1 : 0);
}

int SWPTGType0x31::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x40))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int SWPTGType0x31::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(2)) & static_cast<quint8>(0x80))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}
