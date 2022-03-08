//---------------------------------------------------------------------------
#ifndef TAdam4068SysUnitH
#define TAdam4068SysUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#define OutCnt4068 8
#define DevCnt4068 255
#define ErrCnt4068 5
class TAdam4068Dev
{
public:
   bool Use[OutCnt4068];
   int Out[OutCnt4068];
   int OutOld[OutCnt4068];
   int Out2[OutCnt4068];
   int Out3[OutCnt4068];
   int Cmd[OutCnt4068];
   int AdamOff[OutCnt4068];
   TDateTime OffDt[OutCnt4068];
   int TreeIdx[OutCnt4068];
};
//---------------------------------------------------------------------------
class TAdam4068Sys
{
public:
   int NetSviaziCnt;
   int Use[DevCnt4068];
   int ErrCnt[DevCnt4068];
   TAdam4068Dev Dev[DevCnt4068];

   void ResetDev();
};
//---------------------------------------------------------------------------
#endif
 