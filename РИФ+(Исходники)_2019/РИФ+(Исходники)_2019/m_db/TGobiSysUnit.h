//---------------------------------------------------------------------------
#ifndef TGobiSysUnitH
#define TGobiSysUnitH
//---------------------------------------------------------------------------
class TGobiIu
{
public:
   bool Use;    
   bool GobiCam;
   int Status;   /* Состояние: 0-не определено,
                                   1-включено,
                                   2-выключено
                                   10-Неисправность (Нет связи) */
   int status1;
   int StatusOld; 
   int StatusOld2;
   int hCmd;         /* Команда управления:
                        0 - не определена,
                        1 - выключить
                        2 - включить  */
   bool hCmd2;

   int TreeIdx;   
   int Level;   
   AnsiString Name;

   int AutoOff;
   TDateTime OffDt;
};
//---------------------------------------------------------------------------
class TGobiSd
{
public:
   bool Use;
   int TreeIdx; 
   int Level;   

   bool AlarmFix; 
   int Status;       /* Состояние: 0-не определено,
                                   1-норма,
                                   2- Команда ДК выполнена
                                   10-Неисправность (Нет связи),
                                   11-Неисправность (нет ДК),
                                   20-Тревога (сработка)
                                   */
   int status1;
   int StatusOld; 
   int StatusOld2;
   int StatusFix; 

   bool DkOk;
   bool Dk;       
   bool Bazalt;   
   int OnOffCnt;
   bool BazaltCmd2;
   int AutoDk;
   bool PervoeSobytiePosleDk;

   bool Metka;    
   TTime Metka1Time, Metka2Time, Metka3Time, Metka4Time, MetkaDopuskTime;
   bool Metka1Ok, Metka2Ok, Metka3Ok, Metka4Ok;

   bool Razriv;   

   bool Vin;
   int Sin;

   int io;

   bool ConnectBlock;
   bool ConnectBlockHand;

   bool AlarmMsgOn;

   AnsiString Name;

   int asoosd_kk, asoosd_nn;

   double lan, lon;          
   AnsiString description;
};
//---------------------------------------------------------------------------
class TGobiCam
{
public:
   int k;
   int bl;
   int iu;
   int hcmd;
   TGobiCam();
};
//---------------------------------------------------------------------------
#define SdCnt 9
#define IuCnt 3
class TGobiBl
{
public:
   TGobiSd Sd[SdCnt];
   TGobiIu Iu[IuCnt];
   bool Use;
   bool Tv;
   int ErrCnt;
   bool NetSviazi;

   int Cmd; 
   TGobiIu Vk[IuCnt]; 

   int DkStatus; /* Состояние выполнения команды ДК
                     0 - ДК не выполняется
                     1 - Надо послать команду "Включить ДК"
                     2 - После (1) период выполнения команды ДК  */
   TTime DkTime;
   TDateTime AutoDkDt;
};
//---------------------------------------------------------------------------
#define BlCnt 128
class TGobiKanal
{
public:
   TGobiBl Bl[BlCnt];
   bool Use;
   int hCmd; /* Команда управления:
                        0 - не определена,
                        1 - включить ДК
                        2 - выключить  ДК
                        3 - в состоянии ДК (после посылки команды ДК вкл)
                        4 - в состоянии ДК (после посылки команды ДК выкл) */

   TDateTime AutoDkDt;
};
//---------------------------------------------------------------------------
#define KanCnt 4
#define MaxErrCnt1 20
#define MaxGobiCamCnt 4
class TGobiSys
{
public:
   TGobiKanal Kanal[KanCnt];
   int ErrCnt;       
   int Status;       /* Состояние: 0-не определено,
                                   1-норма (Есть связь),
                                   200-Неисправность (Нет связи)
                                   201-Связь восстановлена */
   int StatusOld;    

   TTime DkDtTime1; 
   TTime DkDtTime2; 

   TGobiCam GobiCam[MaxGobiCamCnt];
   TGobiCam GobiCam2[MaxGobiCamCnt];

   int OprosAdr[KanCnt][BlCnt];

   bool AlarmMsgOn;

   TGobiSys();
   void Reset();
};
//---------------------------------------------------------------------------
class TGobiSys2
{
public:
   TGobiBl Bl[KanCnt][BlCnt];

   int OprosAdr[KanCnt][BlCnt];
   TTime DkDtTime[KanCnt]; 

   TGobiSys2();
   void Reset();
};
//---------------------------------------------------------------------------
#endif
