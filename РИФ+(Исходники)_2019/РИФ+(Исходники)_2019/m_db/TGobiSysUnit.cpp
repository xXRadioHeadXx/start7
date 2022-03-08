//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TGobiSysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TGobiSys::TGobiSys()
{
   ErrCnt = 0;
   Status = 0;
   StatusOld = 0;

   DkDtTime1 = EncodeTime(0, 0, 4, 750); //2,750
   DkDtTime2 = EncodeTime(0, 0, 10, 250); //6,250

   Reset();
}
//---------------------------------------------------------------------------
TGobiCam::TGobiCam()
{
   k = -1;
   bl = -1;
   iu = -1;
   hcmd = -1;
}
//---------------------------------------------------------------------------
void TGobiSys::Reset()
{
   for( int i = 0; i < KanCnt; i++ )
   {
      Kanal[i].Use = false;
      Kanal[i].hCmd = 0;
      for( int j = 0; j < BlCnt; j++ )
      {
         Kanal[i].Bl[j].Use = false;
         Kanal[i].Bl[j].ErrCnt = 1;
         Kanal[i].Bl[j].Tv = false;
         for( int k = 0; k < SdCnt; k++ )
         {
            Kanal[i].Bl[j].Sd[k].Use = false;
            Kanal[i].Bl[j].Sd[k].TreeIdx = 0;
            Kanal[i].Bl[j].Sd[k].Level = 0;
            Kanal[i].Bl[j].Sd[k].AlarmFix = true;
            Kanal[i].Bl[j].Sd[k].Status = 0;
            Kanal[i].Bl[j].Sd[k].status1 = 0;
            Kanal[i].Bl[j].Sd[k].StatusOld = -1;
            Kanal[i].Bl[j].Sd[k].StatusOld2 = -1;
            Kanal[i].Bl[j].Sd[k].StatusFix = -1;
            Kanal[i].Bl[j].Sd[k].DkOk = false;
            Kanal[i].Bl[j].Sd[k].Dk = true;
            Kanal[i].Bl[j].Sd[k].AutoDk = 0;
            Kanal[i].Bl[j].Sd[k].PervoeSobytiePosleDk = false;
            Kanal[i].Bl[j].Sd[k].Bazalt = false;
            Kanal[i].Bl[j].Sd[k].Metka = false;
            Kanal[i].Bl[j].Sd[k].Metka1Ok = false;
            Kanal[i].Bl[j].Sd[k].Metka2Ok = false;
            Kanal[i].Bl[j].Sd[k].Metka3Ok = false;
            Kanal[i].Bl[j].Sd[k].Metka4Ok = false;
            Kanal[i].Bl[j].Sd[k].OnOffCnt = -1;
            Kanal[i].Bl[j].Sd[k].Razriv = false;
            Kanal[i].Bl[j].Sd[k].Sin = -1;
            Kanal[i].Bl[j].Sd[k].ConnectBlock = false;
            Kanal[i].Bl[j].Sd[k].ConnectBlockHand = false;
            Kanal[i].Bl[j].Sd[k].AlarmMsgOn = false;
            Kanal[i].Bl[j].Sd[k].asoosd_kk = 0;
            Kanal[i].Bl[j].Sd[k].asoosd_nn = 0;
         }
         for( int l = 0; l < IuCnt; l++ )
         {
            Kanal[i].Bl[j].Iu[l].Use = false;
            Kanal[i].Bl[j].Iu[l].GobiCam = false;
            Kanal[i].Bl[j].Iu[l].Status = 0;
            Kanal[i].Bl[j].Iu[l].status1 = 0;
            Kanal[i].Bl[j].Iu[l].StatusOld = -1;
            Kanal[i].Bl[j].Iu[l].hCmd = 0;
            Kanal[i].Bl[j].Iu[l].hCmd2 = false;
            Kanal[i].Bl[j].Iu[l].StatusOld2 = -1;
            Kanal[i].Bl[j].Iu[l].TreeIdx = 0;
            Kanal[i].Bl[j].Iu[l].Level = 0;
            Kanal[i].Bl[j].Iu[l].AutoOff = 0;

            Kanal[i].Bl[j].Vk[l].Use = false;
            Kanal[i].Bl[j].Vk[l].GobiCam = false;
            Kanal[i].Bl[j].Vk[l].Status = 0;
            Kanal[i].Bl[j].Vk[l].status1 = 0;
            Kanal[i].Bl[j].Vk[l].StatusOld = -1;
            Kanal[i].Bl[j].Vk[l].hCmd = 0;
            Kanal[i].Bl[j].Vk[l].StatusOld2 = -1;
            Kanal[i].Bl[j].Vk[l].TreeIdx = 0;
         }

         OprosAdr[i][j] = -1;
      }
   }

   AlarmMsgOn = false;

   for( int i = 0; i < MaxGobiCamCnt; i++ )
   {
      GobiCam[i].k = -1;
      GobiCam[i].bl = -1;
      GobiCam[i].iu = -1;
      GobiCam2[i].k = -1;
      GobiCam2[i].bl = -1;
      GobiCam2[i].iu = -1;
   }
}
//---------------------------------------------------------------------------
TGobiSys2::TGobiSys2()
{
   Reset();

   for( int k = 0; k < KanCnt; k++ ) DkDtTime[k] = EncodeTime(0, 0, 10, 0);
}
//---------------------------------------------------------------------------
void TGobiSys2::Reset()
{
   for( int k = 0; k < KanCnt; k++ )
   for( int bl = 0; bl < BlCnt; bl++ )
   {
      Bl[k][bl].Use = false;
      Bl[k][bl].ErrCnt = 0;
      Bl[k][bl].Tv = false;
      Bl[k][bl].Cmd = 0xF0;
      Bl[k][bl].DkStatus = 0;
      Bl[k][bl].DkTime = 0.0;

      OprosAdr[k][bl] = 0;

      for( int sd = 0; sd < SdCnt; sd++ )
      {
         Bl[k][bl].Sd[sd].Use = false;
         Bl[k][bl].Sd[sd].TreeIdx = 0;
         Bl[k][bl].Sd[sd].Level = 0;
         Bl[k][bl].Sd[sd].AlarmFix = true;
         Bl[k][bl].Sd[sd].Status = 0;
         Bl[k][bl].Sd[sd].status1 = 0;
         Bl[k][bl].Sd[sd].StatusOld = 0;
         Bl[k][bl].Sd[sd].StatusOld2 = -1;
         Bl[k][bl].Sd[sd].StatusFix = -1;
         Bl[k][bl].Sd[sd].DkOk = false;
         Bl[k][bl].Sd[sd].Dk = true;
         Bl[k][bl].Sd[sd].Bazalt = false;
         Bl[k][bl].Sd[sd].Metka = false;
         Bl[k][bl].Sd[sd].Metka1Ok = false;
         Bl[k][bl].Sd[sd].Metka2Ok = false;
         Bl[k][bl].Sd[sd].Metka3Ok = false;
         Bl[k][bl].Sd[sd].Metka4Ok = false;
         Bl[k][bl].Sd[sd].OnOffCnt = -1;
         Bl[k][bl].Sd[sd].Vin = false;
         Bl[k][bl].Sd[sd].Sin = false;
         Bl[k][bl].Sd[sd].io = -1;
         Bl[k][bl].Sd[sd].BazaltCmd2 = false;
         Bl[k][bl].Sd[sd].ConnectBlock = false;
      }

      for( int iu = 0; iu < IuCnt; iu++ )
      {
         Bl[k][bl].Iu[iu].Use = false;
         Bl[k][bl].Iu[iu].GobiCam = false;
         Bl[k][bl].Iu[iu].TreeIdx = 0;
         Bl[k][bl].Iu[iu].Level = 0;
         Bl[k][bl].Iu[iu].Status = 0;
         Bl[k][bl].Iu[iu].status1 = 0;
         Bl[k][bl].Iu[iu].StatusOld = -1;
         Bl[k][bl].Iu[iu].hCmd = 0;
         Bl[k][bl].Iu[iu].StatusOld2 = -1;

         Bl[k][bl].Vk[iu].Use = false;
         Bl[k][bl].Vk[iu].GobiCam = false;
         Bl[k][bl].Vk[iu].Status = 0;
         Bl[k][bl].Vk[iu].status1 = 0;
         Bl[k][bl].Vk[iu].StatusOld = -1;
         Bl[k][bl].Vk[iu].hCmd = 0;
         Bl[k][bl].Vk[iu].StatusOld2 = -1;
      }
   }
}
//---------------------------------------------------------------------------

