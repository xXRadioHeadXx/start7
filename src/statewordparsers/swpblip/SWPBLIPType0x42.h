#ifndef SWPBLIPTYPE0X42_H
#define SWPBLIPTYPE0X42_H

#include "../src/statewordparsers/SWP.h"
#include "../src/statewordparsers/swpblip/SWPSDBLIPType0x42.h"

class SWPBLIPType0x42 : public SWP
{
public:
    SWPBLIPType0x42(const StateWord &stateWord);

    SWPBLIPType0x42(const SWPBLIPType0x42&) = default;
    SWPBLIPType0x42(SWPBLIPType0x42&&) = default;
    SWPBLIPType0x42 & operator=(const SWPBLIPType0x42&) = default;
    SWPBLIPType0x42& operator=(SWPBLIPType0x42&&) = default;

    virtual ~SWPBLIPType0x42();

    const SWPSDBLIPType0x42 sd(int numSD) const;
    const SWPSDBLIPType0x42 sd1() const {return sd(1);};
    const SWPSDBLIPType0x42 sd2() const {return sd(2);};
    const SWPSDBLIPType0x42 sd3() const {return sd(3);};
    const SWPSDBLIPType0x42 sd4() const {return sd(4);};
    const SWPSDBLIPType0x42 sd5() const {return sd(5);};
    const SWPSDBLIPType0x42 sd6() const {return sd(6);};
    const SWPSDBLIPType0x42 sd7() const {return sd(7);};
    const SWPSDBLIPType0x42 sd8() const {return sd(8);};

};

#endif // SWPBLIPTYPE0X42_H
