//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TSotaSysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void TSotaDv::Reset()
{
   Use = false;
   UchNum = 0;
   Status[0] = -1;
   Status[1] = -1;
   TreeIdx = 0;
   AlarmFix = true;
   for( int i = 0; i < 2; i++ ) packet[i] = 0;
   Porog = -1;
}
//---------------------------------------------------------------------------
void TSotaUch::Reset()
{
   Use = false;
   Status[0] = -1;
   Status[1] = -1;
   TreeIdx = 0;
   AlarmFix = true;
   IconVisible = false;
}
//---------------------------------------------------------------------------
void TSotaFlang::Reset()
{
   Use = false;
   Status[0] = -1;
   Status[1] = -1;
   AlarmFix = true;
   TreeIdx = 0;

   for( int i = 0; i < MaxSotaUchCnt; i++ ) Uch[i].Reset();
   for( int i = 0; i < MaxSotaDvCnt; i++ ) Dv[i].Reset();

   Porog = -1;
}
//---------------------------------------------------------------------------
void TSotaBos::Reset()
{
   Use = false;
   Status[0] = -1;
   Status[1] = -1;
   TreeIdx = 0;
   ErrCnt = 0;
   AlarmFix = true;
   for( int i = 0; i < 2; i++ ) packet[i] = 0;

   Cmd = 0;
   K = -1;
   T = -1;
   Pult = false;

   for( int i = 0; i < MaxSotaFlangCnt; i++ ) Flang[i].Reset();
}
//---------------------------------------------------------------------------
void TSotaPort::Reset()
{
   Use = false;
   PortSpeed = 4800;
   OprosIdx = -1;
   Opros = false;

   for( int i = 0; i < MaxSotaBosCnt; i++ )
   {
      Bos[i].Reset();
      OprosAdr[i] = -1;
   }
}
//---------------------------------------------------------------------------
void TSotaSys::Reset()
{
   Use = false;

   OprosInterval = 300;

   for( int i = 0; i < MaxSotaBosCnt; i++ )
   {
      SotaPort[i].Reset();
   }
}
//---------------------------------------------------------------------------

