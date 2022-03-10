#ifndef SWPT4KDDTYPE0X34_H
#define SWPT4KDDTYPE0X34_H

#include "SWP.h"
#include "SWPT4KDDCType0x34.h"
#include "SWPWeakening.h"


class SWPT4KDDType0x34 :
        public SWP
      , public SWPWeakening<int>
{
    int y4;
    int dd;

public:
    SWPT4KDDType0x34(const StateWord &stateWord,const int y4, const int dd);

    SWPT4KDDType0x34(const SWPT4KDDType0x34&) = default;
    SWPT4KDDType0x34(SWPT4KDDType0x34&&) = default;
    SWPT4KDDType0x34 & operator=(const SWPT4KDDType0x34&) = default;
    SWPT4KDDType0x34& operator=(SWPT4KDDType0x34&&) = default;

    virtual ~SWPT4KDDType0x34();

    int weakening() const override;
    int getY4() const;
    int getDd() const;

    SWPT4KDDCType0x34 c(int num);

};

#endif // SWPT4KDDTYPE0X34_H
