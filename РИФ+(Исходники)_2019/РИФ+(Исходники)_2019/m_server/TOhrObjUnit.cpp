//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TOhrObjUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
SCfgObj::SCfgObj()
{
   Type = 0;
   Num1 = 0;
   Num2 = 0;
   Num3 = 0;
   Level = 0;
   Name = "";
   IconVisible = false;
   X = 20;
   Y = 20;
   Icon1Path = "";
   Icon2Path = "";
   Icon3Path = "";
   Icon4Path = "";
   Icon5Path = "";
   Icon6Path = "";
   Icon7Path = "";
   Icon8Path = "";
   Dk = true;
   Bazalt = false;
   Metka = false;
   Metka1Time_0 = 0;
   Metka1Time_1 = 0;
   Metka2Time_0 = 0;
   Metka2Time_1 = 0;
   Metka3Time_0 = 0;
   Metka3Time_1 = 0;
   Metka4Time_0 = 0;
   Metka4Time_1 = 0;
   MetkaDopuskTime_0 = 0;
   MetkaDopuskTime_1 = 1;
   Razriv = false;
   AdamOff = 0;
   Status = 0;
   AlarmMsgOn = false;
   ConnectBlock = false;
   asoosd_kk = 0;
   asoosd_nn = 0;
   lan = 0.0;
   lon = 0.0;
   description = "";
   UdpUse = false;
   UdpAdress = "";
   UpdPort = 950;
}
//---------------------------------------------------------------------------
TOutObj::TOutObj()
{
   CfgMode = false;
   memset(PlanPath,0,500);
   FileOperationId = 0;

   ImgOperationId = 0;
   memset(ObjName,0,500);
   memset(ImgName,0,500);
   ImgNum = -1;
   memset(ImgPath,0,500);
   ImgLeft = 0;
   ImgTop = 0;
   IconVisible = false;

   AlarmResetFlag = false;
}
//---------------------------------------------------------------------------
TOprosOutObj::TOprosOutObj()
{
   OprosMode = true;

   AlarmResetFlag = false;
   
   for( int kan = 0; kan < RifKanCnt; kan++ )
   for( int i = 0; i < RifDevCnt*MaxInCnt; i++ )
   {
      RifRk[kan][i] = 0;
   }

   for( int i = 0; i < KanCnt*BlCnt*SdCnt; i++ )
   {
      GobiSd[i] = 0;
   }

   for( int i = 0; i < KanCnt*BlCnt*IuCnt; i++ )
   {
      GobiIu[i] = 0;
      GobiVk[i] = 0;
   }

   for( int kan = 0; kan < RifKanCnt; kan++ )
   for( int i = 0; i < MaxTochkaMUchCnt; i++ )
   {
      TochkaM[kan][i] = 0;
   }

   IconVisible = false;
   X = 0;
   Y = 0;
}
//---------------------------------------------------------------------------
SRastrObj::SRastrObj()
{
   Type = 0;
   Num1 = 0;
   Num2 = 0;
}
//---------------------------------------------------------------------------

