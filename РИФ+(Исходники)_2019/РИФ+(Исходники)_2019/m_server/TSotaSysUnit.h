#ifndef TSotaSysUnitH
#define TSotaSysUnitH
class TSotaDv
{
public:
   bool Use;      

   int UchNum;

   int Status[2]; 

   unsigned int packet[2];

   bool AlarmFix;
   int TreeIdx;   

   int Porog;

   void Reset();
};
#define MaxSotaDvCnt 100
class TSotaUch
{
public:
   bool Use;      

   int Status[2]; 

   bool AlarmFix;
   bool IconVisible;
   int TreeIdx;   

   void Reset();
};
#define MaxSotaUchCnt 2
class TSotaFlang
{
public:
   bool Use;      

   int Status[2]; 

   bool AlarmFix;
   int TreeIdx;   

   TSotaUch Uch[MaxSotaUchCnt];
   TSotaDv Dv[MaxSotaDvCnt];

   int Porog;

   void Reset();
};
#define MaxSotaFlangCnt 2
#define SotaErrCnt 10
class TSotaBos
{
public:
   bool Use;      

   int ErrCnt;

   int Status[2]; 

   unsigned int packet[2];

   bool AlarmFix;
   int TreeIdx;   

   AnsiString Name;

   TSotaFlang Flang[MaxSotaFlangCnt];

   int Cmd;
   int K;
   int T;
   bool Pult;

   void Reset();
};
#define MaxSotaBosCnt 100
class TSotaPort
{
public:
   bool Use;      

   int PortSpeed;

   TSotaBos Bos[MaxSotaBosCnt];
   int OprosAdr[MaxSotaBosCnt];
   int OprosIdx;
   bool Opros;

   void Reset();
};
#define MaxSotaPortCnt 100
class TSotaSys
{
public:

   bool Use;

   int OprosInterval;

   TSotaPort SotaPort[MaxSotaPortCnt];

   void Reset();
};
#endif
