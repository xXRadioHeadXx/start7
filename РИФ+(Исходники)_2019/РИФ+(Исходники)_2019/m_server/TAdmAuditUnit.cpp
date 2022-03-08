//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TAdmAuditUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
bool TAdmAudit::Load( AnsiString fn )
{
   int iFileHandle;
   int iFileLength;

   if( !FileExists(fn) ) return (-1); 

   try
   {
      iFileHandle = FileOpen(fn, fmOpenRead);
      if( iFileHandle < 0 ) return (-2); 
      int DataSize = sizeof(TAdmAudit);
      iFileLength = FileSeek(iFileHandle, 0, 2);
      if( iFileLength != DataSize )
      {
         FileClose( iFileHandle );
         return (-3);
      }

      FileSeek(iFileHandle, 0, 0);
      FileRead(iFileHandle, this, sizeof(TAdmAudit));
      FileClose( iFileHandle );
   }
   catch(...)
   {
      return(-5); 
   }

   return 1;
}
//---------------------------------------------------------------------------
bool TAdmAudit::Save( AnsiString fn )
{
   int flag = 0;

   int iFileHandle;

   if( FileExists(fn) ) DeleteFile(fn);

   try
   {
      iFileHandle = FileCreate(fn);

      FileSeek(iFileHandle, 0, 2);
      FileWrite(iFileHandle, this, sizeof(TAdmAudit) );

      FileClose( iFileHandle );

      if( FileExists(fn) ) flag = 1;
      else flag = -5;
   }
   catch(...)
   {
      return(-5); 
   }

   return flag;
}
//---------------------------------------------------------------------------

