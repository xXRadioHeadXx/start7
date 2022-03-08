//---------------------------------------------------------------------------
#ifndef TSolidSysUnitH
#define TSolidSysUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
class TSolidSys
{
public:
   int AutoTime;
   unsigned char OutStatus[128];

   void SetTv( int num, bool status );   
                                           
                                              
   bool GetTv( int num );
   void ResetTv();

   TSolidSys();
};
//---------------------------------------------------------------------------
#endif
