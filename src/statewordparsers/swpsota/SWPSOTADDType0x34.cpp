#include "../src/statewordparsers/swpsota/SWPSOTADDFType0x34.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDType0x34.h"

int SWPSOTADDType0x34::getY4() const
{
    return y4;
}

int SWPSOTADDType0x34::getDd() const
{
    return dd;
}

SWPSOTADDFType0x34 SWPSOTADDType0x34::f(int num)
{
    return SWPSOTADDFType0x34(getStateWord(), getY4(), getDd(), num);
}

SWPSOTADDType0x34::SWPSOTADDType0x34(const StateWord &stateWord, const int y4, const int dd) :
    SWP(stateWord)
  , y4(y4)
  , dd(dd)
{

}

SWPSOTADDType0x34::~SWPSOTADDType0x34()
{

}
