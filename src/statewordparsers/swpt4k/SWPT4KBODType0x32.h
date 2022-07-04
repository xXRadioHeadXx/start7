#ifndef SWPT4KBODTYPE0X32_H
#define SWPT4KBODTYPE0X32_H

#include "../src/statewordparsers/SWP.h"

#include "../src/statewordparsers/SWPExistDK.h"
#include "../src/statewordparsers/SWPInOpened.h"
#include "../src/statewordparsers/SWPReady.h"
#include "../src/statewordparsers/SWPWasDK.h"
#include "../src/statewordparsers/SWPWasOpened.h"

class SWPT4KY4Type0x32;
class SWPT4KBODType0x32 :
          public SWP
        , public SWPReady
        , public SWPExistDK
        , public SWPWasDK
        , public SWPInOpened
        , public SWPWasOpened
{
public:
    SWPT4KBODType0x32(const StateWord &stateWord);

    SWPT4KBODType0x32(const SWPT4KBODType0x32&) = default;
    SWPT4KBODType0x32(SWPT4KBODType0x32&&) = default;
    SWPT4KBODType0x32 & operator=(const SWPT4KBODType0x32&) = default;
    SWPT4KBODType0x32& operator=(SWPT4KBODType0x32&&) = default;

    virtual ~SWPT4KBODType0x32();

    SWPT4KY4Type0x32 y(int num) const;
    SWPT4KY4Type0x32 y1() const;
    SWPT4KY4Type0x32 y2() const;
    SWPT4KY4Type0x32 y3() const;
    SWPT4KY4Type0x32 y4() const;

    virtual int isReady() const final;
    virtual int isExistDK() const final;
    virtual int isWasDK() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;


};

#endif // SWPT4KBODTYPE0X32_H
