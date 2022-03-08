#ifndef SWPSSOIBLIPTYPE0X41_H
#define SWPSSOIBLIPTYPE0X41_H

#include "SWP.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"

class SWPSSOIBLIPType0x41 : public SWP
{
public:
    SWPSSOIBLIPType0x41(const StateWord &stateWord);

    SWPSSOIBLIPType0x41(const SWPSSOIBLIPType0x41&) = default;
    SWPSSOIBLIPType0x41(SWPSSOIBLIPType0x41&&) = default;
    SWPSSOIBLIPType0x41 & operator=(const SWPSSOIBLIPType0x41&) = default;
    SWPSSOIBLIPType0x41& operator=(SWPSSOIBLIPType0x41&&) = default;

    virtual ~SWPSSOIBLIPType0x41();

    int isExistDK() const;
    int isWasDK() const;
    int isOpened() const;
    int isInOpened() const;
    int isWasOpened() const;

    const SWPSSOISDBLIPType0x41 sd(int numSD) const;
    const SWPSSOISDBLIPType0x41 sd1() const {return sd(1);};
    const SWPSSOISDBLIPType0x41 sd2() const {return sd(2);};
    const SWPSSOISDBLIPType0x41 sd3() const {return sd(3);};
    const SWPSSOISDBLIPType0x41 sd4() const {return sd(4);};
    const SWPSSOISDBLIPType0x41 sd5() const {return sd(5);};
    const SWPSSOISDBLIPType0x41 sd6() const {return sd(6);};
    const SWPSSOISDBLIPType0x41 sd7() const {return sd(7);};
    const SWPSSOISDBLIPType0x41 sd8() const {return sd(8);};
    const SWPSSOISDBLIPType0x41 sd9() const {return sd(9);};

    const SWPSSOIIUBLIPType0x41 iu(int numIU) const;
    const SWPSSOIIUBLIPType0x41 iu1() const {return iu(1);};
    const SWPSSOIIUBLIPType0x41 iu2() const {return iu(2);};
    const SWPSSOIIUBLIPType0x41 iu3() const {return iu(3);};
    const SWPSSOIIUBLIPType0x41 iu4() const {return iu(4);};
};

#endif // SWPSSOIBLIPTYPE0X41_H
