#ifndef TOhrObjUnitH
#define TOhrObjUnitH
#include "TRifSysUnit.h"
#include "TSotaSysUnit.h"
#include "TGobiSysUnit.h"
typedef class SCfgObj
{
public:
   int Type; 
   int Num1; 
   int Num2; 
   int Num3; 

   int Level;  
   AnsiString Name; 

   bool IconVisible;
   int X, Y;   

   AnsiString Icon1Path;
   AnsiString Icon2Path;
   AnsiString Icon3Path;
   AnsiString Icon4Path;
   AnsiString Icon5Path;
   AnsiString Icon6Path;
   AnsiString Icon7Path;
   AnsiString Icon8Path;

   bool Dk;
   bool Bazalt;   
   bool Metka;    
   bool Razriv;   

   int Metka1Time_0, Metka1Time_1;
   int Metka2Time_0, Metka2Time_1;
   int Metka3Time_0, Metka3Time_1;
   int Metka4Time_0, Metka4Time_1;
   int MetkaDopuskTime_0, MetkaDopuskTime_1;

   int AdamOff;   

   int Status;

   bool AlarmMsgOn;   

   bool ConnectBlock;

   int OutType;

   int asoosd_kk, asoosd_nn; 

   double lan, lon;           
   AnsiString description;

   bool UdpUse;   
   AnsiString UdpAdress;
   int UpdPort;

   SCfgObj();

} TCfgObj;
typedef TCfgObj* PCfgObj;
typedef TCfgObj* POprosObj;
struct TOutObj
{
   bool CfgMode;
   char PlanPath[500];
   int FileOperationId;

   int ImgOperationId;
   char ObjName[500];
   char ImgName[500];
   int ImgNum;
   char ImgPath[500];
   int ImgLeft;
   int ImgTop;
   bool IconVisible;

   bool AlarmResetFlag;

   TOutObj();
};
typedef TOutObj* POutObj;
struct TOprosOutObj
{
   bool OprosMode;
   char PlanPath[500];

   bool AlarmResetFlag;

   int RifRk[RifKanCnt][RifDevCnt*MaxInCnt];

   int GobiSd[KanCnt*BlCnt*SdCnt];
   int GobiIu[KanCnt*BlCnt*IuCnt];
   int GobiVk[KanCnt*BlCnt*IuCnt];

   int TochkaM[RifKanCnt][MaxTochkaMUchCnt];

   bool IconVisible;
   int X, Y;

   TOprosOutObj();
};
typedef TOprosOutObj* POprosOutObj;
typedef class SRastrObj
{
public:
   int Type; 
   int Num1; 
   int Num2; 

   SRastrObj();
} TRastrObj;
typedef TRastrObj* PRastrObj;
#endif
