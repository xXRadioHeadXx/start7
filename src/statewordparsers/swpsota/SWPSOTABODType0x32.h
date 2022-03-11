#ifndef SWPSOTABODTYPE0X32_H
#define SWPSOTABODTYPE0X32_H

#include "SWP.h"

#include "SWPExistDK.h"
#include "SWPInOpened.h"
#include "SWPReady.h"
#include "SWPWasDK.h"
#include "SWPWasOpened.h"

class SWPSOTAY4Type0x32;
class SWPSOTABODType0x32 :
          public SWP
        , public SWPReady
        , public SWPExistDK
        , public SWPWasDK
        , public SWPInOpened
        , public SWPWasOpened
{
public:
    SWPSOTABODType0x32(const StateWord &stateWord);

    SWPSOTABODType0x32(const SWPSOTABODType0x32&) = default;
    SWPSOTABODType0x32(SWPSOTABODType0x32&&) = default;
    SWPSOTABODType0x32 & operator=(const SWPSOTABODType0x32&) = default;
    SWPSOTABODType0x32& operator=(SWPSOTABODType0x32&&) = default;

    virtual ~SWPSOTABODType0x32();

    SWPSOTAY4Type0x32 y(int num) const;
    SWPSOTAY4Type0x32 y1() const;
    SWPSOTAY4Type0x32 y2() const;
    SWPSOTAY4Type0x32 y3() const;
    SWPSOTAY4Type0x32 y4() const;

    virtual int isReady() const final;
    virtual int isExistDK() const final;
    virtual int isWasDK() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;


};

#endif // SWPSOTABODTYPE0X32_H
