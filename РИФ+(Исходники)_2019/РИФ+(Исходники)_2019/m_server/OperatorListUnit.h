//---------------------------------------------------------------------------
#ifndef OperatorListUnitH
#define OperatorListUnitH
//---------------------------------------------------------------------------
class TSysOperator
{
   public:
   AnsiString FamilyName, FirstName, SecondName, Password;
};
//---------------------------------------------------------------------------
#define MaxOperatorCnt 1000
class TSysOperatorList
{
   public:
   bool Use;
   TSysOperator Op[MaxOperatorCnt];
   int OpCnt;

   TSysOperatorList();
   void Reset();
   void Sort();
};
//---------------------------------------------------------------------------
#endif
