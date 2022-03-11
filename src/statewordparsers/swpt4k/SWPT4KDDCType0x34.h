#ifndef SWPT4KDDCTYPE0X34_H
#define SWPT4KDDCTYPE0X34_H

#include <SWP.h>
#include "SWPWeakening.h"

class SWPT4KDDCFType0x34;
class SWPT4KDDCType0x34 :
        public SWP
      , public SWPWeakening<int>
{
    int y4;
    int dd;
    int c;
public:
    SWPT4KDDCType0x34(const StateWord &stateWord, const int y4, const int dd, const int c);

    SWPT4KDDCType0x34(const SWPT4KDDCType0x34&) = default;
    SWPT4KDDCType0x34(SWPT4KDDCType0x34&&) = default;
    SWPT4KDDCType0x34 & operator=(const SWPT4KDDCType0x34&) = default;
    SWPT4KDDCType0x34& operator=(SWPT4KDDCType0x34&&) = default;

    virtual ~SWPT4KDDCType0x34();
    int getY4() const;
    int getDd() const;
    int getC() const;

    SWPT4KDDCFType0x34 f(int num);

    int weakening() const override;
};

#endif // SWPT4KDDCTYPE0X34_H
