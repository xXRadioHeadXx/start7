//---------------------------------------------------------------------------
#ifndef TNetClientUnitH
#define TNetClientUnitH
//---------------------------------------------------------------------------
class TiNetClient
{
public:
   int  KeepAliveCnt;
   bool EventsAndStates;
   int SocketHandle;

   TiNetClient();

   void Reset();
   void Set( int h );
   bool IsExist( int h );
   bool IsEmpty();
};
//---------------------------------------------------------------------------
#define NetClientMaxCnt 1000
//---------------------------------------------------------------------------
class TiNetSys
{
public:
   TiNetClient iNetClient[NetClientMaxCnt];

   TiNetSys();
   void Reset();
};

#endif
 