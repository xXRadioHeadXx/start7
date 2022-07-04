#include "../src/statewordparsers/swpblip/SWPBLIPType0x42.h"

const SWPSDBLIPType0x42 SWPBLIPType0x42::sd(int numSD) const
{
    return SWPSDBLIPType0x42(getStateWord(), numSD);
}

SWPBLIPType0x42::SWPBLIPType0x42(const StateWord &stateWord) :
    SWP(stateWord)
{
}

SWPBLIPType0x42::~SWPBLIPType0x42() {

}
