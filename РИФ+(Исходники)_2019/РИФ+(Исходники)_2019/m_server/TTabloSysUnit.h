//---------------------------------------------------------------------------
#ifndef TTabloSysUnitH
#define TTabloSysUnitH
//---------------------------------------------------------------------------
class TTabloDev
{
public:
   bool Use;
   int Num;
   int NumOld;
};
//---------------------------------------------------------------------------
#define TabloDevCnt 4
class TTabloSys
{
public:
   bool Use;
   TTabloDev Dev[TabloDevCnt];
   int SbrosTablo;

   void Reset();
};
//---------------------------------------------------------------------------
#endif
