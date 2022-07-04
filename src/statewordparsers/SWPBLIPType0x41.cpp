#include "../src/statewordparsers/SWPBLIPType0x41.h"

const SWPSDBLIPType0x41 SWPBLIPType0x41::sd(int numSD) const
{
    return SWPSDBLIPType0x41(getStateWord(), numSD);
}

const SWPIUBLIPType0x41 SWPBLIPType0x41::iu(int numIU) const
{
    return SWPIUBLIPType0x41(getStateWord(), numIU);
}

SWPBLIPType0x41::SWPBLIPType0x41(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPBLIPType0x41::~SWPBLIPType0x41() {

}

int SWPBLIPType0x41::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int SWPBLIPType0x41::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<quint8>(byteWord().at(1)) & 0x40)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}
