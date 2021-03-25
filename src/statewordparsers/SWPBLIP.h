#ifndef SWPBLIP_H
#define SWPBLIP_H

#include <SWP.h>
#include <SWPIUBLIP.h>
#include <SWPSDBLIP.h>

class SWPBLIP : public SWP
{
public:
    SWPBLIP(const QByteArray &stateWord);
    SWPBLIP(const SWPBLIP & parent);
    virtual ~SWPBLIP();

    int isExistDK() const;
    int isWasDK() const;

    const SWPSDBLIP sd(int numSD) const;
    const SWPSDBLIP sd1() const {return sd(1);};
    const SWPSDBLIP sd2() const {return sd(2);};
    const SWPSDBLIP sd3() const {return sd(3);};
    const SWPSDBLIP sd4() const {return sd(4);};
    const SWPSDBLIP sd5() const {return sd(5);};
    const SWPSDBLIP sd6() const {return sd(6);};
    const SWPSDBLIP sd7() const {return sd(7);};
    const SWPSDBLIP sd8() const {return sd(8);};

    const SWPIUBLIP iu(int numIU) const;
    const SWPIUBLIP iu1() const {return iu(1);};
    const SWPIUBLIP iu2() const {return iu(2);};
    const SWPIUBLIP iu3() const {return iu(3);};
    const SWPIUBLIP iu4() const {return iu(4);};

};

#endif // SWPBLIP_H
