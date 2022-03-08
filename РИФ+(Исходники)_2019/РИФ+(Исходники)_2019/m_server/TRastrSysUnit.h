//---------------------------------------------------------------------------
#ifndef TRastrSysUnitH
#define TRastrSysUnitH
#include <vcl.h>
//---------------------------------------------------------------------------
class TRastrTv
{
public:
   bool Use;     

   TRastrTv();
};
//---------------------------------------------------------------------------
#define TvCnt 32
class TRastrMonitor
{
public:
   bool Use;

   TRastrTv Tv[TvCnt];

   int AutoTv[TvCnt];
   bool Auto;

   TRastrMonitor();
   void AutoReset();
};
//---------------------------------------------------------------------------
#define MonCnt 4
class TRastrSys
{
public:
   TRastrMonitor Mon[MonCnt];
   double AutoTime;

   TRastrSys();
};
//---------------------------------------------------------------------------
#endif
