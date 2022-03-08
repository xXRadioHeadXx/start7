//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OperatorListUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
TSysOperatorList::TSysOperatorList()
{
   Reset();
}
//---------------------------------------------------------------------------
void TSysOperatorList::Reset()
{
   Use = false;

   for( int i = 0; i < MaxOperatorCnt; i++ )
   {
      Op[i].FamilyName = "";
      Op[i].FirstName = "";
      Op[i].SecondName = "";
      Op[i].Password = "";
   }

   OpCnt = 0;
}
//---------------------------------------------------------------------------
void TSysOperatorList::Sort()
{
   TStringList* MyList = new TStringList();
   MyList->Clear();
   AnsiString str, strt;

   for( int i = 0; i < MaxOperatorCnt; i++ )
   {
      if( Op[i].FamilyName != "" )
      {
         str.sprintf("%s %s %s %s", Op[i].FamilyName, Op[i].FirstName, Op[i].SecondName, Op[i].Password );
         MyList->Add(str);
      }
   }
   OpCnt = MyList->Count;

   MyList->Sort();

   int pos = 0;
   for( int i = 0; i < OpCnt; i++ )
   {
      str = MyList->Strings[i];
      pos = str.Pos(" ");
      if( pos > 0 )
      {
         strt = str.SubString(1, pos-1);
         Op[i].FamilyName = strt;
         str.Delete(1, pos);
      }

      pos = str.Pos(" ");
      if( pos > 0 )
      {
         strt = str.SubString(1, pos-1);
         Op[i].FirstName = strt;
         str.Delete(1, pos);
      }

      pos = str.Pos(" ");
      if( pos > 0 )
      {
         strt = str.SubString(1, pos-1);
         Op[i].SecondName = strt;
         str.Delete(1, pos);
      }

      Op[i].Password = str;
   }

   delete MyList;
}
//---------------------------------------------------------------------------

