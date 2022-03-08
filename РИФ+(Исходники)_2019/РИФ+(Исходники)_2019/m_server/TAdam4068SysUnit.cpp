//---------------------------------------------------------------------------
#pragma hdrstop

#include "TAdam4068SysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void TAdam4068Sys::ResetDev()
{
   NetSviaziCnt = 0;
   for( int num1 = 0; num1 < DevCnt4068; num1++ )
      for( int num2 = 0; num2 < OutCnt4068; num2++ )
      {
         Use[num1] = 0;
         ErrCnt[num1] = 0;
         Dev[num1].Cmd[num2] = 0;
         Dev[num1].Use[num2] = false;
         Dev[num1].Out[num2] = 0;
         Dev[num1].OutOld[num2] = -1;
         Dev[num1].Out2[num2] = -1;
         Dev[num1].Out3[num2] = -1;
         Dev[num1].AdamOff[num2] = 0;
         Dev[num1].TreeIdx[num2] = 0;
      }
}
//---------------------------------------------------------------------------
