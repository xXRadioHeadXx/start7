#include "SWPTGSubType0x34.h"

SWPTGSubType0x34::SWPTGSubType0x34(const QByteArray &stateWord) :
    SWP(stateWord)
{
}

SWPTGSubType0x34::SWPTGSubType0x34(const SWPTGSubType0x34 &parent) :
    SWP(parent)
{
}

SWPTGSubType0x34::~SWPTGSubType0x34() {

}

int SWPTGSubType0x34::numberIn() const
{
    if(getStateWord().isEmpty())
        return -1;
    return (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x03));
}

int SWPTGSubType0x34::isOnFlt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x04))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPTGSubType0x34::isOffFlt1() const
{
    int ison = isOnFlt1();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPTGSubType0x34::isOnFlt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x08))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPTGSubType0x34::isOffFlt2() const
{
    int ison = isOnFlt2();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPTGSubType0x34::isOnFlt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int SWPTGSubType0x34::isOffFlt3() const
{
    int ison = isOnFlt3();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

int SWPTGSubType0x34::thresholdFlt1() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(1,2).toInt();
}

int SWPTGSubType0x34::thresholdFlt2() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(3,2).toInt();
}

int SWPTGSubType0x34::thresholdFlt3() const
{
    if(getStateWord().isEmpty())
        return -1;
    return getStateWord().mid(5,2).toInt();
}
