//---------------------------------------------------------------------------
#pragma hdrstop

#include "TSolidSysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
TSolidSys::TSolidSys()
{
   AutoTime = 250;
}
//---------------------------------------------------------------------------
void TSolidSys::SetTv( int num, bool status )
{
   int Num = num-1;
   Num = (Num/120)*32+2+(Num%120)/4;
   int rez = 0;
   if( status )
   {
      rez = 1;
      OutStatus[Num] |= rez<<((num-1)%4);
   }
   else
   {
      rez = (1<<((num-1)%4));
      rez = ~rez;
      rez = 0xFF & rez;
      OutStatus[Num] &= rez;
   }

   int b = OutStatus[Num];
   b = b & 0x0F;
   if( b == 0 ) OutStatus[Num] = 0;
   else OutStatus[Num] |= 0x80;
}
//---------------------------------------------------------------------------
bool TSolidSys::GetTv( int num )
{
   int Num = num-1;
   Num = (Num/120)*32+2+(Num%120)/4;
   int rez = 0;
   rez = OutStatus[Num]&0xFF;
   rez = (rez>>((num-1)%4))&1;

   if( rez == 1 ) return true;

   return false;
}
//---------------------------------------------------------------------------
void TSolidSys::ResetTv()
{
   for( int i = 0; i < 128; i++ ) OutStatus[i] = 0;
}
//---------------------------------------------------------------------------

