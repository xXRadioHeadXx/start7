//---------------------------------------------------------------------------
#ifndef TNetClientSysUnitH
#define TNetClientSysUnitH
#include <vcl.h>
//---------------------------------------------------------------------------
class TNetSys
{
public:
   TStringList *DayBook;

   TNetSys();
};
//---------------------------------------------------------------------------
class TNetData
{
public:
   TStringList *DayBook;
   TNetData();
};
typedef TNetData* PNetData;
#endif
