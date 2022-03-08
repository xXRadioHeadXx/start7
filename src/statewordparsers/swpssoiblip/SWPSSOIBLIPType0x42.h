#ifndef SWPSSOIBLIPTYPE0X42_H
#define SWPSSOIBLIPTYPE0X42_H

#include "swpssoiblip/SWPSSOISDBLIPType0x42.h"



class SWPSSOIBLIPType0x42 : public SWP
{
public:
    SWPSSOIBLIPType0x42(const StateWord &stateWord);

    SWPSSOIBLIPType0x42(const SWPSSOIBLIPType0x42&) = default;
    SWPSSOIBLIPType0x42(SWPSSOIBLIPType0x42&&) = default;
    SWPSSOIBLIPType0x42 & operator=(const SWPSSOIBLIPType0x42&) = default;
    SWPSSOIBLIPType0x42& operator=(SWPSSOIBLIPType0x42&&) = default;

    virtual ~SWPSSOIBLIPType0x42();

    const SWPSSOISDBLIPType0x42 sd(int numSD) const;
    const SWPSSOISDBLIPType0x42 sd1() const {return sd(1);};
    const SWPSSOISDBLIPType0x42 sd2() const {return sd(2);};
    const SWPSSOISDBLIPType0x42 sd3() const {return sd(3);};
    const SWPSSOISDBLIPType0x42 sd4() const {return sd(4);};
    const SWPSSOISDBLIPType0x42 sd5() const {return sd(5);};
    const SWPSSOISDBLIPType0x42 sd6() const {return sd(6);};
    const SWPSSOISDBLIPType0x42 sd7() const {return sd(7);};
    const SWPSSOISDBLIPType0x42 sd8() const {return sd(8);};
};

#endif // SWPSSOIBLIPTYPE0X42_H
