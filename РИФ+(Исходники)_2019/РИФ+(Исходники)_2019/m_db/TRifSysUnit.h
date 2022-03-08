//---------------------------------------------------------------------------
#ifndef TRifSysUnitH
#define TRifSysUnitH
//---------------------------------------------------------------------------
class TDd
{
public:
   bool Use;     

   AnsiString Name;

   int StatusUch[2]; 
   int StatusChE1[2];
   int StatusChE2[2];

   bool T1[2]; 
   bool T2[2]; 

   bool N1[2]; 
   bool N2[2]; 

   bool Ss[2]; 
   bool S[2];  

   bool Sv[2]; 
   bool V[2];  

   bool AlarmFix;
   int TreeIdx;
   int Level;  
   bool AlarmMsgOn;

   double lan, lon;
   AnsiString description;

   int Porog;

   int FlangNum;

   int sob_type;

   void Reset();
};
//---------------------------------------------------------------------------
#define MaxErrCnt 20
#define MaxIpBlSdCnt 8
#define MaxIpBlIuCnt 4
#define MaxInCnt MaxIpBlSdCnt+MaxIpBlIuCnt
#define MaxTochkaMDdCnt 200
#define MaxTochkaMUchCnt 4
class TRif_KoncentratorDev
{
public:
   bool Use;         
   int Adr;          
   int Type;         
   int Port;         

   AnsiString Name[MaxInCnt];

   int TreeIdx[MaxInCnt];
   int Level[MaxInCnt];  
   bool AlarmFix[MaxInCnt];

   bool InUse[MaxInCnt];   
   bool On[MaxInCnt];      
   int Status[MaxInCnt];       /* Новое состояние:
                                   [0..99] - Датчик включен
                                   0-не определено,
                                   1-норма,
                                   2-Конфигурация изменена после работы с пультом
                                   3-Команда ДК выполнена
                                   4-Команда управления выполнена
                                   10-Неисправность (нет связи),
                                   11-Неисправность (нет ДК),
                                   12-Неисправность (Уход уровня),
                                   13-Команда управления не выполнена
                                   20-Тревога (сработка),
                                   21-Тревога (вскрытие),
                                   22-Тревога (Конфигурация изменена),
                                   30-Работа с пультом
                                   31-Работа с пультом заверщена
                                   100 - Датчик выключен
                                   101 - Датчик включен */
   int StatusOld[MaxInCnt];

   int Cmd;
   int CmdCnt;

   int hCmd[MaxInCnt];     
   bool Tin[MaxInCnt];   
   int AutoOff[MaxInCnt];
   TDateTime OffDt[MaxInCnt];


   int Rezhim;       
   int Porogi;       
   int Takt;       
   int Porogi1, Porogi2; 
   int Porogi3;          
   int Rezhim1, Rezhim2; 
   bool Pult;            

   int Skvazhnost;   
   int Skvazhnost1;  
   int Skvazhnost2;  
   int Skvazhnost3;  

   int S; 

   bool Ohrana[MaxInCnt]; 


   int ErrCnt;       

   bool DkUse[MaxInCnt]; 
   bool Dk;
   int DkCnt;
   bool KDk[MaxInCnt];
   bool AutoDk;
   int AutoDkCnt;

   int Conf_variant; 

   int tF[4][3];    
   int nominPorog[4][3];
   int tempKoef; 
   int tochka_cmd; 
   bool Sv[4]; 
   bool Direction[4]; 
   int DirectionCnt[4]; 
   int PauseCnt[4]; 
   int OprosInterval; 

   bool Bazalt[MaxInCnt];
   int Key[MaxInCnt];
   int OnOffCnt[MaxInCnt];

   bool AlarmMsgOn[MaxInCnt];

   int StatusBO[2];
   TDd *Uch; 
   TDd *Dd; 
   unsigned char BO_cfg[26]; 
   int Uch2StartAdr, Uch4StartAdr;

   double lan[MaxInCnt], lon[MaxInCnt]; 
   AnsiString description[MaxInCnt];

   void Reset( int adr );
   double Uaru();
   double Uaru1( int s );
};
//---------------------------------------------------------------------------
int CalcRealPorog( int np, int k );
//---------------------------------------------------------------------------
#define RifDevCnt 101
#define RifKanCnt 256
class TRifSys
{
public:
   TRif_KoncentratorDev Rk[RifKanCnt][RifDevCnt];
   int OprosAdr[RifKanCnt][RifDevCnt];
   int OprosCnt[RifKanCnt];
   bool Opros[RifKanCnt];

   double Ul;
   double Uh;

   bool AutoDk;       
   TDateTime AutoDkPeriod;

   TRifSys();
   void Reset();
};
//---------------------------------------------------------------------------
class TDiagRif
{
   public:
   int Adr;
   int Port;
   bool On;
   bool Dk;
   bool T;
   bool Ts;
   bool Tv;
   bool Sdk;
   bool St;
   bool Sv;
   double U;
   double U2;
   double U3;
   int Status;
   bool Pult;
   bool Ts1;
   bool Ts2;
   bool Ts3;
   bool S;
   bool Luch1;
   bool Luch2;
   bool Luch3;

   void Reset();
   void Set( int sb, double u );
};
//---------------------------------------------------------------------------
class TDiagKonc
{
   public:
   int Adr;
   int Port;
   bool TIn[MaxInCnt];
   bool VIn;
   bool TOut[MaxInCnt];
   bool OnIn[MaxInCnt];
   bool TsIn[MaxInCnt];
   bool Ts;
   bool T;
   bool Dk;
   bool DkOut;
   bool Tv;
   int Status;

   void Reset();
   void Set( int d1, int d2, int d3 );
};
//---------------------------------------------------------------------------
#endif
