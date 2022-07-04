#ifndef SWPSOTABODTYPE0X33_H
#define SWPSOTABODTYPE0X33_H

#include "../src/statewordparsers/SWP.h"

#include "../src/statewordparsers/SWPExistDK.h"
#include "../src/statewordparsers/SWPInOpened.h"
#include "../src/statewordparsers/SWPReady.h"
#include "../src/statewordparsers/SWPWasDK.h"
#include "../src/statewordparsers/SWPWasOpened.h"

class SWPSOTAY4Type0x33;
class SWPSOTADDType0x33;
class SWPSOTABODType0x33 :
        public SWP
      , public SWPReady
      , public SWPExistDK
      , public SWPWasDK
      , public SWPInOpened
      , public SWPWasOpened
{
public:
    SWPSOTABODType0x33(const StateWord &stateWord);

    SWPSOTABODType0x33(const SWPSOTABODType0x33&) = default;
    SWPSOTABODType0x33(SWPSOTABODType0x33&&) = default;
    SWPSOTABODType0x33 & operator=(const SWPSOTABODType0x33&) = default;
    SWPSOTABODType0x33& operator=(SWPSOTABODType0x33&&) = default;

    virtual ~SWPSOTABODType0x33();

    int getDd() const;
    int getY4() const;

    SWPSOTAY4Type0x33 y(int num) const;
    SWPSOTAY4Type0x33 y1() const;
    SWPSOTAY4Type0x33 y2() const;
    SWPSOTAY4Type0x33 y3() const;
    SWPSOTAY4Type0x33 y4() const;

    SWPSOTADDType0x33 dd() const;


    virtual int isReady() const final;
    virtual int isExistDK() const final;
    virtual int isWasDK() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;

};

#endif // SWPSOTABODTYPE0X33_H
