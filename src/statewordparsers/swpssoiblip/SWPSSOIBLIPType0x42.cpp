#include "swpssoiblip/SWPSSOIBLIPType0x42.h"

const SWPSSOISDBLIPType0x42 SWPSSOIBLIPType0x42::sd(int numSD) const
{
    return SWPSSOISDBLIPType0x42(getStateWord(), numSD);
}

SWPSSOIBLIPType0x42::SWPSSOIBLIPType0x42(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPSSOIBLIPType0x42::~SWPSSOIBLIPType0x42() {

}
