#ifndef SWPT4KBODTYPE0X33_H
#define SWPT4KBODTYPE0X33_H

#include <SWP.h>

#include "SWPExistDK.h"
#include "SWPInOpened.h"
#include "SWPReady.h"
#include "SWPWasDK.h"
#include "SWPWasOpened.h"

class SWPT4KY4Type0x33;
class SWPT4KDDType0x33;
class SWPT4KBODType0x33 :
        public SWP
      , public SWPReady
      , public SWPExistDK
      , public SWPWasDK
      , public SWPInOpened
      , public SWPWasOpened
{
public:
    SWPT4KBODType0x33(const StateWord &stateWord);

    SWPT4KBODType0x33(const SWPT4KBODType0x33&) = default;
    SWPT4KBODType0x33(SWPT4KBODType0x33&&) = default;
    SWPT4KBODType0x33 & operator=(const SWPT4KBODType0x33&) = default;
    SWPT4KBODType0x33& operator=(SWPT4KBODType0x33&&) = default;

    virtual ~SWPT4KBODType0x33();

    int getDd() const;
    int getY4() const;

    SWPT4KY4Type0x33 y(int num) const;
    SWPT4KY4Type0x33 y1() const;
    SWPT4KY4Type0x33 y2() const;
    SWPT4KY4Type0x33 y3() const;
    SWPT4KY4Type0x33 y4() const;

    SWPT4KDDType0x33 dd() const;


    virtual int isReady() const final;
    virtual int isExistDK() const final;
    virtual int isWasDK() const final;
    virtual int isInOpened() const final;
    virtual int isWasOpened() const final;

};

#endif // SWPT4KBODTYPE0X33_H
