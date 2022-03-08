//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TRifSysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
void TRif_KoncentratorDev::Reset( int adr )
{
   Use = false;
   Adr = adr;
   Type = 0;
   Port = 1;
   for( int i = 0; i < MaxInCnt; i++ )
   {
      InUse[i] = false;
      TreeIdx[i] = 0;
      Level[i] = 0;
      AlarmFix[i] = true;
      Status[i] = 0;
      StatusOld[i] = 0;
      Ohrana[i] = false;
      On[i] = false;
      KDk[i] = false;
      DkUse[i] = true;
      hCmd[i] = 0;
      Tin[i] = false;
      Bazalt[i] = false;
      Key[i] = 0;
      OnOffCnt[i] = 0;
      AlarmMsgOn[i] = false;
      AutoOff[i] = 0;
   }
   Rezhim = -1;
   Rezhim1 = -1;
   Rezhim2 = -1;
   Porogi = -1;
   Porogi1 = -1;
   Porogi2 = -1;
   Porogi3 = -1;
   Takt = -1;
   Skvazhnost = 0;
   Skvazhnost1 = 0;
   Skvazhnost2 = 0;
   ErrCnt = 0;
   DkCnt = 0;
   Dk = false;
   AutoDk = false;
   AutoDkCnt = 0;
   Cmd = 0x22;
   CmdCnt = 0;
   S = -1;
   Pult = false;
   Conf_variant = -1;

   for( int i = 0; i < 4; i++ )
   for( int j = 0; j < 3; j++ )
   {
      nominPorog[i][j] = -1;
      tF[i][j] = -1;
   }
   tempKoef = -1;
   tochka_cmd = 0x2e;
   for( int i = 0; i < 4; i++ )
   {
      Sv[i] = false;
      Direction[i] = false;
      DirectionCnt[i] = 0;
      PauseCnt[i] = 0;
   }
   OprosInterval = 0;

   for( int i = 0; i < 2; i++ ) StatusBO[i] = -1;
//   for( int uch = 0; uch < MaxTochkaMUchCnt; uch++ ) Uch[uch].Reset();
//   for( int dd = 0; dd < MaxTochkaMDdCnt; dd++ ) Dd[dd].Reset();
   for( int i = 0; i < 26; i++ ) BO_cfg[i] = 0;
   Uch2StartAdr = 0;
   Uch4StartAdr = 0;
}
//---------------------------------------------------------------------------
double TRif_KoncentratorDev::Uaru()
{
   double Uaru = 0.0;
   Uaru = (double)Skvazhnost;
   Uaru = Uaru / 255.0;
   Uaru = 5.0 * Uaru;
   Uaru = 5.0 - Uaru;
   return Uaru;
}
//---------------------------------------------------------------------------
double TRif_KoncentratorDev::Uaru1( int s )
{
   double Uaru = 0.0;
   Uaru = (double)s;
   Uaru = Uaru / 255.0;
   Uaru = 5.0 * Uaru;
   Uaru = 5.0 - Uaru;
   return Uaru;
}
//---------------------------------------------------------------------------
int CalcRealPorog( int np, int k )
{
   int k1 = 0, k2 = 16;
   switch( k )
   {
      case 0: k1 = 3; break;
      case 1: k1 = 4; break;
      case 2: k1 = 6; break;
      case 3: k1 = 10; break;
      case 4: k1 = 12; break;
      case 5: k1 = 15; break;
      case 6: k1 = 16; break;
      case 7: k1 = 14; break;
      case 8: k1 = 13; break;
      case 9: k1 = 11; break;
      case 10: k1 = 10; break;
   }

   int rez = np * 5 * k1 / k2;

   return rez;
}
//---------------------------------------------------------------------------
TRifSys::TRifSys()
{
   Ul = 0.00;
   Uh = 5.00;
   Reset();
   AutoDk = false;
}
//---------------------------------------------------------------------------
void TRifSys::Reset()
{
   for( int c = 0; c < RifKanCnt; c++ )
   {
      for( int i = 0; i < RifDevCnt; i++ )
      {
         Rk[c][i].Reset(i+1);
         OprosAdr[c][i] = 0;
      }
      OprosCnt[c] = 0;
      Opros[c] = false;
   }
}
//---------------------------------------------------------------------------
void TDiagRif::Reset()
{
   On = false;
   Dk = false;
   T = false;
   Ts = false;
   Tv = false;
   Sdk = false;
   St = false;
   Sv = false;
   U = 0.0;
   U2 = 0.0;
   U3 = 0.0;
   Status = 0;
   Pult = false;
   Ts1 = false;
   Ts2 = false;
   Ts3 = false;
   S = false;
   Luch1 = true;
   Luch2 = true;
   Luch3 = true;
}
//---------------------------------------------------------------------------
void TDiagRif::Set( int sb, double u )
{
   On = false;
   Dk = false;
   T = false;
   Ts = false;
   Tv = false;
   Sdk = false;
   St = false;
   Sv = false;
   U = 0.0;

   int temp = 0;
   temp = sb & 1;
   if( temp == 1 ) On = true;

   temp = 0;
   temp = sb & 2;
   if( temp == 2 ) Ts = true;

   temp = 0;
   temp = sb & 4;
   if( temp == 4 ) St = true;

   temp = 0;
   temp = sb & 8;
   if( temp == 8 ) T = true;

   temp = 0;
   temp = sb & 16;
   if( temp == 16 ) Sdk = true;

   temp = 0;
   temp = sb & 32;
   if( temp == 32 ) Dk = true;

   temp = 0;
   temp = sb & 64;
   if( temp == 64 ) Sv = true;

   temp = 0;
   temp = sb & 128;
   if( temp == 128 ) Tv = true;

   U = u;
}
//---------------------------------------------------------------------------
void TDiagKonc::Reset()
{
   for( int i = 0; i < MaxInCnt; i++ )
   {
      TIn[i] = false;
      TOut[i] = false;
      OnIn[i] = false;
      TsIn[i] = false;
   }
   VIn = false;
   Ts = false;
   T = false;
   Tv = false;
   Dk = false;
   Status = 0;
   DkOut = false;
}
//---------------------------------------------------------------------------
void TDiagKonc::Set( int d1, int d2, int d3 )
{
   Reset();

   int temp = 0;
   temp = d1 & 1;
   if( temp == 1 ) TIn[0] = true;

   temp = 0;
   temp = d1 & 2;
   if( temp == 2 ) TIn[1] = true;

   temp = 0;
   temp = d1 & 4;
   if( temp == 4 ) TIn[2] = true;

   temp = 0;
   temp = d1 & 8;
   if( temp == 8 ) TIn[3] = true;

   temp = 0;
   temp = d1 & 16;
   if( temp == 16 ) DkOut = true;

   temp = 0;
   temp = d1 & 32;
   if( temp == 32 ) VIn = true;

   temp = 0;
   temp = d2 & 1;
   if( temp == 1 ) TOut[0] = true;

   temp = 0;
   temp = d2 & 2;
   if( temp == 2 ) TOut[1] = true;

   temp = 0;
   temp = d2 & 4;
   if( temp == 4 ) TOut[2] = true;

   temp = 0;
   temp = d2 & 8;
   if( temp == 8 ) TOut[3] = true;

   temp = 0;
   temp = d2 & 16;
   if( temp == 16 ) OnIn[0] = true;

   temp = 0;
   temp = d2 & 32;
   if( temp == 32 ) OnIn[1] = true;

   temp = 0;
   temp = d2 & 64;
   if( temp == 64 ) OnIn[2] = true;

   temp = 0;
   temp = d2 & 128;
   if( temp == 128 ) OnIn[3] = true;

   temp = 0;
   temp = d3 & 1;
   if( temp == 1 ) TsIn[0] = true;

   temp = 0;
   temp = d3 & 2;
   if( temp == 2 ) TsIn[1] = true;

   temp = 0;
   temp = d3 & 4;
   if( temp == 4 ) TsIn[2] = true;

   temp = 0;
   temp = d3 & 8;
   if( temp == 8 ) TsIn[3] = true;

   temp = 0;
   temp = d3 & 16;
   if( temp == 16 ) Ts = true;

   temp = 0;
   temp = d3 & 32;
   if( temp == 32 ) T = true;

   temp = 0;
   temp = d3 & 64;
   if( temp == 64 ) Dk = true;

   temp = 0;
   temp = d3 & 128;
   if( temp == 128 ) Tv = true;
}
//---------------------------------------------------------------------------
void TDd::Reset()
{
   Use = false;

   for( int i = 0; i < 2; i++ )
   {
      StatusUch[i] = -1;

      StatusChE1[i] = -1;
      StatusChE2[i] = -1;

      T1[i] = false;
      T2[i] = false;
      N1[i] = false;
      N2[i] = false;
      Ss[i] = false;
      S[i] = false;
      Sv[i] = false;
      V[i] = false;
   }

   TreeIdx = 0;
   Level = 0;
   AlarmFix = true;
   Porog = -1;
   lan = 0.0;
   lon = 0.0;
   description = "";
   FlangNum = 0;
   sob_type = 0;
}
//---------------------------------------------------------------------------

