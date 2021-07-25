#ifndef SWPBLIPTYPE0X41_H
#define SWPBLIPTYPE0X41_H

#include "SWP.h"
#include "SWPIUBLIPType0x41.h"
#include "SWPSDBLIPType0x41.h"

class SWPBLIPType0x41 : public SWP
{
public:
    SWPBLIPType0x41(const StateWord &stateWord);

    SWPBLIPType0x41(const SWPBLIPType0x41&) = default;
    SWPBLIPType0x41(SWPBLIPType0x41&&) = default;
    SWPBLIPType0x41 & operator=(const SWPBLIPType0x41&) = default;
    SWPBLIPType0x41& operator=(SWPBLIPType0x41&&) = default;

    virtual ~SWPBLIPType0x41();

    int isExistDK() const;
    int isWasDK() const;

    const SWPSDBLIPType0x41 sd(int numSD) const;
    const SWPSDBLIPType0x41 sd1() const {return sd(1);};
    const SWPSDBLIPType0x41 sd2() const {return sd(2);};
    const SWPSDBLIPType0x41 sd3() const {return sd(3);};
    const SWPSDBLIPType0x41 sd4() const {return sd(4);};
    const SWPSDBLIPType0x41 sd5() const {return sd(5);};
    const SWPSDBLIPType0x41 sd6() const {return sd(6);};
    const SWPSDBLIPType0x41 sd7() const {return sd(7);};
    const SWPSDBLIPType0x41 sd8() const {return sd(8);};

    const SWPIUBLIPType0x41 iu(int numIU) const;
    const SWPIUBLIPType0x41 iu1() const {return iu(1);};
    const SWPIUBLIPType0x41 iu2() const {return iu(2);};
    const SWPIUBLIPType0x41 iu3() const {return iu(3);};
    const SWPIUBLIPType0x41 iu4() const {return iu(4);};

};

#endif // SWPBLIPTYPE0X41_H
