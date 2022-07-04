#include "../src/statewordparsers/swpssoiblip/SWPSSOIBLIPType0x41.h"

const SWPSSOISDBLIPType0x41 SWPSSOIBLIPType0x41::sd(int numSD) const
{
    return SWPSSOISDBLIPType0x41(getStateWord(), numSD);
}

const SWPSSOIIUBLIPType0x41 SWPSSOIBLIPType0x41::iu(int numIU) const
{
    return SWPSSOIIUBLIPType0x41(getStateWord(), numIU);
}

SWPSSOIBLIPType0x41::SWPSSOIBLIPType0x41(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPSSOIBLIPType0x41::~SWPSSOIBLIPType0x41() {

}

int SWPSSOIBLIPType0x41::isExistDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int SWPSSOIBLIPType0x41::isWasDK() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x40)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSSOIBLIPType0x41::isInOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x10)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int SWPSSOIBLIPType0x41::isWasOpened() const
{
    if(byteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(byteWord().at(1)) & 0x20)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int SWPSSOIBLIPType0x41::isOpened() const
{
    return ((1 == isInOpened() && 1 == isWasOpened()) ? 1 : (-1 == isInOpened() || -1 == isWasOpened()) ? -1 : 0);
}

