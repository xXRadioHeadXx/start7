#include "SWPBLIP.h"

const SWPSDBLIP SWPBLIP::sd(int numSD) const
{
    return SWPSDBLIP(getStateWord(), numSD);
}

const SWPIUBLIP SWPBLIP::iu(int numIU) const
{
    return SWPIUBLIP(getStateWord(), numIU);
}

SWPBLIP::SWPBLIP(const StateWord &stateWord) :
    SWP(stateWord)
{
}

//SWPBLIP::SWPBLIP(const QByteArray &byteWord) :
//    SWP(byteWord)
//{
//}

SWPBLIP::SWPBLIP(const SWPBLIP &parent) :
    SWP(parent)
{
}

SWPBLIP::~SWPBLIP() {

}

int SWPBLIP::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int SWPBLIP::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & 0x40)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}
