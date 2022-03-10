#ifndef SWPT4KBODTYPE0X34_H
#define SWPT4KBODTYPE0X34_H

#include <SWP.h>

class SWPT4KDDType0x34;
class SWPT4KBODType0x34 : public SWP
{
public:
    SWPT4KBODType0x34(const StateWord &stateWord);

    SWPT4KBODType0x34(const SWPT4KBODType0x34&) = default;
    SWPT4KBODType0x34(SWPT4KBODType0x34&&) = default;
    SWPT4KBODType0x34 & operator=(const SWPT4KBODType0x34&) = default;
    SWPT4KBODType0x34& operator=(SWPT4KBODType0x34&&) = default;

    virtual ~SWPT4KBODType0x34();

    int getDd() const;
    int getY4() const;

    SWPT4KDDType0x34 dd() const;

};

#endif // SWPT4KBODTYPE0X34_H
