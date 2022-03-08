//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TNetClientUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TiNetClient::TiNetClient()
{
   Reset();
}
//---------------------------------------------------------------------------
void TiNetClient::Reset()
{
   KeepAliveCnt = 0;
   SocketHandle = 0;
   EventsAndStates = false;
}
//---------------------------------------------------------------------------
bool TiNetClient::IsExist( int h )
{
   if( SocketHandle == h ) return true;

   return false;
}
//---------------------------------------------------------------------------
void TiNetClient::Set(  int h )
{
   SocketHandle = h;
}
//---------------------------------------------------------------------------
bool TiNetClient::IsEmpty()
{
   if( SocketHandle == 0 ) return true;

   return false;
}
//---------------------------------------------------------------------------
TiNetSys::TiNetSys()
{
   Reset();
}
//---------------------------------------------------------------------------
void TiNetSys::Reset()
{
   for( int i = 0; i < NetClientMaxCnt; i++ ) iNetClient[i].Reset();
}
//---------------------------------------------------------------------------

