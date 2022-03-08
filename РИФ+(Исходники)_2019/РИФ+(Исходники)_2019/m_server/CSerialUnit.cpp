//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "CSerialUnit.h"
#include "MyApiUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
CSerial::CSerial()
{
	memset( &m_OverlappedRead, 0, sizeof( OVERLAPPED ) );
 	memset( &m_OverlappedWrite, 0, sizeof( OVERLAPPED ) );
	m_hIDComDev = NULL;
	m_bOpened = FALSE;
   SendOk = 1;
}
//---------------------------------------------------------------------------
CSerial::~CSerial()
{
	Close();
}
//---------------------------------------------------------------------------
BOOL CSerial::Open( int nPort, int nBaud )
{
   speed = nBaud;

	if( m_bOpened ) return( TRUE );

	char szPort[15];
	char szComParams[50];
	DCB dcb;

	if(nPort < 10) wsprintf( szPort, "COM%d", nPort );
   else wsprintf( szPort, "\\\\.\\COM%d", nPort );

	m_hIDComDev = CreateFile( szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );
	if( m_hIDComDev == NULL ) return( FALSE );

	memset( &m_OverlappedRead, 0, sizeof( OVERLAPPED ) );
 	memset( &m_OverlappedWrite, 0, sizeof( OVERLAPPED ) );

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout         = 0;
	CommTimeOuts.ReadTotalTimeoutMultiplier  = 0;
	CommTimeOuts.ReadTotalTimeoutConstant    = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant   = 0;
	SetCommTimeouts( m_hIDComDev, &CommTimeOuts );

	if(nPort < 10) wsprintf( szComParams, "COM%d:%d,n,8,1", nPort, nBaud );
   else wsprintf( szComParams, "\\\\.\\COM%d:%d,n,8,1", nPort, nBaud );

	m_OverlappedRead.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_OverlappedWrite.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

	dcb.DCBlength = sizeof( DCB );
	GetCommState( m_hIDComDev, &dcb );
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;

   dcb.fBinary = true;
   dcb.fOutxCtsFlow = false;
   dcb.fDtrControl = DTR_CONTROL_DISABLE;
   dcb.fDsrSensitivity = false;
   dcb.fNull = false;
   dcb.fRtsControl = RTS_CONTROL_DISABLE;
   dcb.fAbortOnError = false;
   dcb.Parity = 0;
   dcb.StopBits = 0;

	if( !SetCommState( m_hIDComDev, &dcb ) ||
		!SetupComm( m_hIDComDev, 10000, 10000 ) ||
		m_OverlappedRead.hEvent == NULL ||
		m_OverlappedWrite.hEvent == NULL ){
		DWORD dwError = GetLastError();
		if( m_OverlappedRead.hEvent != NULL ) CloseHandle( m_OverlappedRead.hEvent );
		if( m_OverlappedWrite.hEvent != NULL ) CloseHandle( m_OverlappedWrite.hEvent );
		CloseHandle( m_hIDComDev );
		return( FALSE );
		}

	m_bOpened = TRUE;

	return( m_bOpened );
}
//---------------------------------------------------------------------------
BOOL CSerial::Close( void )
{
	if( !m_bOpened || m_hIDComDev == NULL ) return( TRUE );

	if( m_OverlappedRead.hEvent != NULL ) CloseHandle( m_OverlappedRead.hEvent );
	if( m_OverlappedWrite.hEvent != NULL ) CloseHandle( m_OverlappedWrite.hEvent );
	CloseHandle( m_hIDComDev );
	m_bOpened = FALSE;
	m_hIDComDev = NULL;

	return( TRUE );
}
//---------------------------------------------------------------------------
BOOL CSerial::WriteCommByte( unsigned char ucByte )
{
	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile( m_hIDComDev, (LPSTR) &ucByte, 1, &dwBytesWritten, &m_OverlappedWrite );
	if( !bWriteStat && ( GetLastError() == ERROR_IO_PENDING ) ){
		if( WaitForSingleObject( m_OverlappedWrite.hEvent, 200 /*1000*/ ) ) dwBytesWritten = 0;
		else{
			GetOverlappedResult( m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, FALSE );
			m_OverlappedWrite.Offset += dwBytesWritten;
			}
		}

	return( TRUE );
}
//---------------------------------------------------------------------------
int CSerial::WriteCommBytes( unsigned char *buffer, int size )
{
	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile( m_hIDComDev, (LPSTR) buffer, size, &dwBytesWritten, &m_OverlappedWrite );
	if( !bWriteStat && ( GetLastError() == ERROR_IO_PENDING ) )
   {
		if( WaitForSingleObject( m_OverlappedWrite.hEvent, 200 /*1000*/ ) ) dwBytesWritten = 0;
		else
      {
			GetOverlappedResult( m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, FALSE );
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}

	return  dwBytesWritten;
}
//---------------------------------------------------------------------------
int CSerial::SendData( const char *buffer, int size )
{
	if( !m_bOpened || m_hIDComDev == NULL ) return( 0 );

	DWORD dwBytesWritten = 0;
	int i;
	for( i=0; i<size; i++ )
   {
		WriteCommByte( buffer[i] );
		dwBytesWritten++;
	}
	return( (int) dwBytesWritten );
}
//---------------------------------------------------------------------------
int CSerial::SendData2( unsigned char *buffer, int size )
{
   if( !m_bOpened || m_hIDComDev == NULL ) return( 0 );
	return (int) WriteCommBytes( buffer, size );
}
//---------------------------------------------------------------------------
int CSerial::ReadDataWaiting( void )
{
	if( !m_bOpened || m_hIDComDev == NULL ) return( 0 );

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError( m_hIDComDev, &dwErrorFlags, &ComStat );

	return( (int) ComStat.cbInQue );
}
//---------------------------------------------------------------------------
int CSerial::ReadData( void *buffer, int limit )
{
	if( !m_bOpened || m_hIDComDev == NULL ) return( 0 );

	BOOL bReadStatus;
	DWORD dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError( m_hIDComDev, &dwErrorFlags, &ComStat );
	if( !ComStat.cbInQue ) return( 0 );

	dwBytesRead = (DWORD) ComStat.cbInQue;
	if( limit < (int) dwBytesRead ) dwBytesRead = (DWORD) limit;

	bReadStatus = ReadFile( m_hIDComDev, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead );
	if( !bReadStatus ){
		if( GetLastError() == ERROR_IO_PENDING ){
			WaitForSingleObject( m_OverlappedRead.hEvent, 2000 );
			return( (int) dwBytesRead );
			}
		return( 0 );
		}

	return( (int) dwBytesRead );
}
//---------------------------------------------------------------------------
void CSerial::Send3FF()
{
   unsigned char pf[3];
   for( int i = 0; i < 3; i++ ) pf[i] = 0xFF;

   /* Передача */
   if( speed == 4800 ) SendData2( pf, 3 );
}
//---------------------------------------------------------------------------
bool CSerial::SetCmd( int Adr, int Cmd, int D1, bool send3FF )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = Adr;    
   p[3] = Cmd;   
   if( Cmd == 0x20 || Cmd == 0x2c || Cmd == 0xf2 )
   {
      p[2] = 1;   
      p[4] = D1; 
      for( int i = 1; i < 5; i++ ) p[5] = (p[5] + p[i])%256;   

      cnt = 6;
   }
   else
   {
      p[2] = 0;   
      for( int i = 1; i < 4; i++ ) p[4] = (p[4] + p[i])%256;   

      cnt = 5;
   }

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmd1( int Adr, int Cmd, int D1, int D2, bool send3FF )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = Adr;    
   p[2] = 2;   
   p[3] = Cmd;   
   p[4] = D1;  
   p[5] = D2;  
   for( int i = 1; i < 6; i++ ) p[6] = (p[6] + p[i])%256;   
   cnt = 7;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 
   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmd2( int Adr, int Cmd, bool send3FF  )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = Adr;    
   p[2] = 0;      
   p[3] = Cmd;    
   for( int i = 1; i < 4; i++ ) p[4] = (p[4] + p[i])%256;   
   cnt = 5;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false;

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmd3( int Adr, int Cmd, bool send3FF  )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;  
   p[1] = Adr;   
   p[2] = 0xFE;    
   p[3] = 0;      
   p[4] = Cmd;    
   for( int i = 1; i < 5; i++ ) p[5] = (p[5] + p[i])%256;   
   cnt = 6;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmd4( int Adr, int Cmd, int DdNum, bool send3FF )
{
   unsigned char p[20];
   for( int i = 0; i < 20; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = Adr;   
   p[2] = 0xFE;    
   p[3] = 1;      
   p[4] = Cmd;    
   p[5] = DdNum;  
   for( int i = 1; i < 6; i++ ) p[6] = (p[6] + p[i])%256;   
   cnt = 7;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false;

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmdSsoi2( int Adr, int Cmd, int D1 )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 6;

   char buffer[10000];
   memset(buffer, 0, 10000);

   p[0] = 0xB5;   
   p[1] = Adr;    
   p[2] = 0xFE;   
   p[3] = Cmd;    
   if( Cmd != 0xF2 ) D1 = 0;
   p[4] = D1;     

   for( int i = 1; i < 5; i++ ) p[5] = (p[5] + p[i])%256;   
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg( int adr, int por, int rez, int t, bool send3FF  )
{
   int temp1 = por;
   int temp2 = rez<<4;
   int temp3 = (t&1)<<6;
   int temp4 = (t&2)<<4;

   int cfg = temp1|temp2|temp3|temp4;

   return SetCmd( adr, 0x20, cfg, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg1( int adr, bool on[4], bool send3FF )
{
   int cfg = 0;
   for( int i = 0; i < 4; i++ )
      if( on[i] ) cfg += 16<<i;

   return SetCmd( adr, 0x20, cfg, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg2( int adr, int por1, int por2, bool send3FF )
{
   int temp1 = por1;
   int temp2 = por2<<4;
   int cfg = temp1|temp2;

   return SetCmd( adr, 0x2c, cfg, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg3( int adr, int por1, int por2, int rez1, int rez2, bool send3FF )
{
   int temp1 = por1;
   int temp2 = rez1<<4;
   int temp3 = por2;
   int temp4 = rez2<<4;
   int cfg1 = temp1|temp2;
   int cfg2 = temp3|temp4;

   return SetCmd1( adr, 0x2F, cfg1, cfg2, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg4( int adr, int por1, int por2, int por3, int rez, bool send3FF )
{
   int temp1 = por3;
   int temp2 = por2<<4;
   int temp3 = por1;
   int temp4 = rez<<4;
   int cfg1 = temp1|temp2;
   int cfg2 = temp3|temp4;

   return SetCmd1( adr, 0x2f, cfg1, cfg2, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg5( int adr, int sett[4], bool send3FF )
{
   unsigned char p[20];
   for( int i = 0; i < 20; i++ ) p[i] = 0;
   int cnt = 0;
   int temp = 0;

   p[0] = 0xB5;  
   p[1] = adr;    
   p[2] = 7;   
   p[3] = 0x20;   
   p[4] = sett[0];  

   temp = (sett[1]&0xFF00)>>8;
   p[5] = temp;  
   temp = sett[1]&0x00FF;
   p[6] = temp;  

   temp = (sett[2]&0xFF00)>>8;
   p[7] = temp;  
   temp = sett[2]&0x00FF;
   p[8] = temp;  

   temp = (sett[3]&0xFF00)>>8;
   p[9] = temp;  
   temp = sett[3]&0x00FF;
   p[10] = temp;  

   for( int i = 1; i < 11; i++ ) p[11] = (p[11] + p[i])%256;  
   cnt = 12;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg6( int adr, int por, int rez, int t, bool send3FF )
{
   int temp = t<<4;
   int cfg = por|temp;

   unsigned char p[20];
   for( int i = 0; i < 20; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = adr;    
   p[2] = 2;   
   p[3] = 0x20;    
   p[4] = cfg;  
   p[5] = rez;  
   for( int i = 1; i < 6; i++ ) p[6] = (p[6] + p[i])%256;   
   cnt = 7;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg7( int adr, int ddnum,
                       int f12_che1, int por_f1che1, int por_f2che1, int tv_f1che1, int tv_f2che1, int cnt_f1che1, int cnt_f2che1, int tp_f1che1, int tp_f2che1,
                       int f12_che2, int por_f1che2, int por_f2che2, int tv_f1che2, int tv_f2che2, int cnt_f1che2, int cnt_f2che2, int tp_f1che2, int tp_f2che2, bool send3FF )
{
   unsigned char p[30];
   for( int i = 0; i < 30; i++ ) p[i] = 0;
   int cnt = 0;

   int temp = 0;

   p[0] = 0xB5;   
   p[1] = adr;    
   p[2] = 0xFE;   
   p[3] = 23;     
   p[4] = 0x20;   
   p[5] = ddnum;

   p[6] = f12_che1;

   temp = por_f1che1&0xFF00;
   temp = temp>>8;
   p[7] = temp;
   temp = por_f1che1&0x00FF;
   p[8] = temp;

   temp = por_f2che1&0xFF00;
   temp = temp>>8;
   p[9] = temp;
   temp = por_f2che1&0x00FF;
   p[10] = temp;

   p[11] = tv_f1che1;
   p[12] = tv_f2che1;

   p[13] = cnt_f1che1;
   p[14] = cnt_f2che1;

   p[15] = tp_f1che1;
   p[16] = tp_f2che1;

   p[17] = f12_che2;

   temp = por_f1che2&0xFF00;
   temp = temp>>8;
   p[18] = temp;
   temp = por_f1che2&0x00FF;
   p[19] = temp;

   temp = por_f2che2&0xFF00;
   temp = temp>>8;
   p[20] = temp;
   temp = por_f2che2&0x00FF;
   p[21] = temp;

   p[22] = tv_f1che2;
   p[23] = tv_f2che2;

   p[24] = cnt_f1che2;
   p[25] = cnt_f2che2;

   p[26] = tp_f1che2;
   p[27] = tp_f2che2;

   for( int i = 1; i < 28; i++ ) p[28] = (p[28] + p[i])%256;   
   cnt = 29;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg8( int adr, int BO_type, unsigned char cfg[26], int adr1, int adr2, bool send3FF )
{
   unsigned char p[50];
   for( int i = 0; i < 50; i++ ) p[i] = 0;
   int cnt = 0;

   int temp = 0;

   p[0] = 0xB5;   
   p[1] = adr;    
   p[2] = 0xFE;   
   p[4] = 0x20;   
   p[5] = BO_type;   

   if( BO_type == 0 )
   {
      p[3] = 11;     
      for( int i = 0; i <= 7; i++ ) p[6+i] = cfg[i];
      p[14] = adr1;
      p[15] = adr2;

      for( int i = 1; i < 16; i++ ) p[16] = (p[16] + p[i])%256;   
      cnt = 17;
   }
   else if( BO_type == 1 )
   {
      p[3] = 29;     
      for( int i = 0; i < 26; i++ ) p[6+i] = cfg[i];
      p[32] = adr1;
      p[33] = adr2;

      for( int i = 1; i < 34; i++ ) p[34] = (p[34] + p[i])%256;   
      cnt = 35;
   }

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetCfg9( int adr, int ddnum,
                       int f12_che1, int por_f1che1, int por_f2che1, int tv_f1che1, int tv_f2che1, int cnt_f1che1, int cnt_f2che1, int tp_f1che1, int tp_f2che1, bool send3FF )
{
   unsigned char p[30];
   for( int i = 0; i < 30; i++ ) p[i] = 0;
   int cnt = 0;

   int temp = 0;

   p[0] = 0xB5;  
   p[1] = adr;    
   p[2] = 0xFE;   
   p[3] = 12;     
   p[4] = 0x20;   
   p[5] = ddnum;

   p[6] = f12_che1;

   temp = por_f1che1&0xFF00;
   temp = temp>>8;
   p[7] = temp;
   temp = por_f1che1&0x00FF;
   p[8] = temp;

   temp = por_f2che1&0xFF00;
   temp = temp>>8;
   p[9] = temp;
   temp = por_f2che1&0x00FF;
   p[10] = temp;

   p[11] = tv_f1che1;
   p[12] = tv_f2che1;

   p[13] = cnt_f1che1;
   p[14] = cnt_f2che1;

   p[15] = tp_f1che1;
   p[16] = tp_f2che1;

   for( int i = 1; i < 17; i++ ) p[17] = (p[17] + p[i])%256;   
   cnt = 18;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetDk( int adr, bool send3FF  )
{
   return SetCmd( adr, 0x21, 0, send3FF  );
}
//---------------------------------------------------------------------------
bool CSerial::ResetFlags( int adr, bool send3FF  )
{
   return SetCmd( adr, 0x24, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::ResetFlags1( int adr, bool send3FF )
{
   return SetCmd3( adr, 0x24, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetOn( int adr, bool send3FF )
{
   return SetCmd( adr, 0x26, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetOff( int adr, bool send3FF )
{
   return SetCmd( adr, 0x25, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetPultOn( int adr, bool send3FF )
{
   return SetCmd( adr, 0x27, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetPultOff( int adr, bool send3FF )
{
   return SetCmd( adr, 0x23, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus( int adr, bool send3FF )
{
   return SetCmd( adr, 0x22, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus1( int adr, bool send3FF )
{
   return SetCmd( adr, 0x2d, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus2( int adr, bool send3FF )
{
   return SetCmd( adr, 0x2e, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus3( int adr, int cmd, bool send3FF )
{
   bool fl = SetCmd( adr, cmd, 0, send3FF );
   return fl;
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus4( int adr, bool send3FF )
{
   return SetCmd( adr, 0x2c, 0, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetStatus5( int adr, bool send3FF )
{
   return SetCmd3( adr, 0x2e, send3FF );
}
//---------------------------------------------------------------------------
bool CSerial::SetSd( int adr, int status, bool send3FF )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;   
   p[1] = adr;    
   p[2] = 1;   
   p[3] = 0x20;    
   p[4] = status&0xFF;  
   for( int i = 1; i < 5; i++ ) p[5] = (p[5] + p[i])%256;   
   cnt = 6;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
bool CSerial::SetIu( int adr, int status, bool send3FF )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   p[0] = 0xB5;  
   p[1] = adr;    
   p[2] = 1;  
   p[3] = 0x23;    
   p[4] = status&0xFF;  
   for( int i = 1; i < 5; i++ ) p[5] = (p[5] + p[i])%256;  
   cnt = 6;

   if( send3FF ) Send3FF();
   int nBytesSent = SendData2( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
int CSerial::GetPaket( int adr, int packet[1000] )
{
   int flag = 0;
   char buff[1000];
   int buffer[1000];
   memset(buff, 0, 1000);
   memset(buffer, 0, 1000);

   for( int i = 0; i < 1000; i++ ) packet[i] = 0;

m1:
   flag = ReadDataWaiting();
   if(flag >= 1000)
   {
      for(int i = 0; i < flag/1000; i++) ReadData(buff, 1000);
      goto m1;
   }
   flag = ReadData(buff, flag);
   if(flag >= 1000) flag = 950;
   if( flag > 0 )
   {
      for( int i = 0; i < flag; i++ ) buffer[i] = buff[i] & 0xFF;
      
      for( int i = 0; i < flag; i++ )
      {
         if( buffer[i] == 0xB5 )
         {
            if( buffer[i+1] == 0xFE )
            {
               if( buffer[i+2] == adr || adr == 101 )
               {
                  int cntf = buffer[i+3]+6;
                  if( flag < cntf )
                  {
                     flag = -3; 
                  }
                  else
                  {
                      if( buffer[i+4] == 0x02 ||
                          buffer[i+4] == 0x04 ||
                          buffer[i+4] == 0x30 ||
                          buffer[i+4] == 0x31 ||
                          buffer[i+4] == 0x32 ||
                          buffer[i+4] == 0x33 ||
                          buffer[i+4] == 0x34 ||
                          buffer[i+4] == 0x41 ) 
                      {
                         int cnt = buffer[i+3] + 6;

                         int crc = 0, crc2 = 0;

                         for( int j = i+1; j < i+cnt-1; j++ ) crc = (crc + buffer[j])%256;
                         crc = crc & 0xFF;
                         crc2 = crc - adr + 1;
                         crc2 = crc2 & 0xFF;

                         if( crc == buffer[i+cnt-1] || crc2 == buffer[i+cnt-1] )
                         {
                            for( int j = 0; j <= cnt-1; j++ ) packet[j] = buffer[i+j];

                            flag = 1;
                            break;
                         }
                         else
                         {
                           flag = -6; 
                         }
                      }
                      else flag = -4; 
                  }
               }
               else flag = -4; 
            }
            else flag = -3; 
         }
         else flag = -2; 
      }
   }
   else flag = -1; 

   return flag;
}
//---------------------------------------------------------------------------
int CSerial::GetPaketSsoi2( int adr, int packet[30] )
{
   int flag = 0;
   char buffer[1030];
   memset( buffer, 0, 1030 );

   flag = ReadData(buffer, 1030);
   if( flag > 0 )
   {
      for( int i = 0; i < 1000; i++ )
      {
         if( buffer[i] == (char)0xB5 )
         {
            if( buffer[i+1] == (char)0xFE && buffer[i+2] == (char)0xFE && buffer[i+4] == (char)0xFF )
            {
               if( buffer[i+3] == (char)adr )
               {
                  flag = buffer[i+5] + 8;

                  char crc = 0;
                  for( int j = i+1; j < i+flag-1; j++ ) crc = (crc + (char)buffer[j])%256;

                  if( crc == buffer[i+flag-1] )
                  {
                     for( int j = 0; j < 30; j++ ) packet[j] = buffer[i+j]&0xFF;
                     flag = 1; 
                     break;
                  }
                  else flag = -6; 
               }
               else flag = -4; 
            }
            else flag = -3; 
         }
         else flag = -2; 
      }
   }
   else flag = -1; 

   if( flag != 1 ) for( int i = 0; i < 30; i++ ) packet[i] = 0;

   return flag;
}
//---------------------------------------------------------------------------
int CSerial::GetPaketSsoi2_v2( int adr, int packet[10000] )
{
   int flag = 0;
   char buffer[10000];
   memset(buffer, 0, 10000);

   flag = ReadDataWaiting();
   flag = ReadData(buffer, flag);
   if( flag > 0 ) for( int i = 0; i < flag; i++ ) packet[i] = buffer[i]&0xFF;

   return flag;
}
//---------------------------------------------------------------------------
bool CSerial::BS_setup( int b[9] )
{
   unsigned char p[9];
   for( int i = 0; i < 9; i++ ) p[i] = b[i]&0xFF;

   int nBytesSent = SendData( p, 9 );
   if( nBytesSent != 9 ) return 0; 
   return 1;
}
//---------------------------------------------------------------------------
bool CSerial::IuCmd( int k, int b, int cmd1, int cmd2, int cmd3 )
{
//MyDelay(1000);
   unsigned char p[2];
   for( int i = 0; i < 2; i++ ) p[i] = 0;
   p[0] = 0x80;
   p[0] = p[0] + k - 1;
   p[1] = b;
   char cm = 0;
   if( cmd1 == 2 ) cm = 0x10;
   p[1] = p[1] | cm;
   cm = 0;
   if( cmd2 == 2 ) cm = 0x20;
   p[1] = p[1] | cm;
   cm = 0;
   if( cmd3 == 2 ) cm = 0x40;
   p[1] = p[1] | cm;

   int nBytesSent = SendData( p, 2 );
   if( nBytesSent != 2 ) return 0; 

   return 1;
}
//---------------------------------------------------------------------------
bool CSerial::Dk( int kan, bool On )
{
   unsigned char p[2];
   for( int i = 0; i < 2; i++ ) p[i] = 0;
   p[0] = 0x80 + kan - 1;
   if( On ) p[1] = 0x10;

   /* Передача */
   int nBytesSent = SendData( p, 2 );
   if( nBytesSent != 2 ) return 0; 

   return 1;
}
//---------------------------------------------------------------------------
int CSerial::TvCmd( int m, int cmd )
{
   int flag = 0;

   int Adr1 = 0;
   Adr1 = m<<6;
   Adr1 = Adr1 & 224;
   Adr1 = Adr1 | cmd;

   char p[10];
   p[0] = 0;
   p[0] = Adr1;
   int nBytesSent = SendData( p, 1 );
   if( nBytesSent != 1 ) flag = 0; 
   else flag = 1;

   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvOn( int m, int n )
{
   int flag = 0;

   int Adr1 = 0;
   Adr1 = m<<6;
   Adr1 = Adr1 & 192;
   Adr1 = Adr1 | n;

   char p[100];
   p[0] = Adr1;
   int nBytesSent = SendData( p, 1 );
   if( nBytesSent != 1 ) flag = 0; 
   else flag = 1;

   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvLeft(int m)
{
   int flag;
   flag = TvCmd(m, 0x21);
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvRight(int m)
{
   int flag;
   flag = TvCmd(m, 0x20);
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvUp(int m)
{
   int flag;
   flag = TvCmd( m,0x22 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvDn(int m)
{
   int flag;
   flag = TvCmd( m,0x23 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvFUp(int m)
{
   int flag;
   flag = TvCmd( m,0x25 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvFDn(int m)
{
   int flag;
   flag = TvCmd( m,0x24 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvUv(int m)
{
   int flag;
   flag = TvCmd( m,0x27 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvUm(int m)
{
   int flag;
   flag = TvCmd( m,0x26 );
   return flag;
}
//---------------------------------------------------------------------------
int CSerial::TvS( unsigned char buf[128] )
{
   int flag;
   int nBytesSent = SendData( buf, 128 );
   if( nBytesSent != 128 ) flag = 0; 
   else flag = 1;

   return flag;
}
//---------------------------------------------------------------------------
bool CSerial::SetCmdA4068( int adr, int Cmd, int data[8]  )
{
   unsigned char p[10];
   for( int i = 0; i < 10; i++ ) p[i] = 0;
   int cnt = 0;

   char temp[100];
   sprintf(temp, "%02X", adr);

   int t = 0;
   switch( Cmd )
   {
      case 2:  p[0] = '$';
               p[1] = temp[0];
               p[2] = temp[1];
               p[3] = 'M';
               p[4] = 0xD;
               cnt = 5;
               break;
      case 3:  p[0] = '#';
               p[1] = temp[0];
               p[2] = temp[1];
               p[3] = '0';
               p[4] = '0';
               for( int i = 0; i < 8; i++ )
                  if( data[i] == 101) t = t | (1<<i);
               sprintf(temp, "%02X", t);
               p[5] = temp[0];
               p[6] = temp[1];
               p[7] = 0xD;
               cnt = 8;
               break;
      case 4:  p[0] = '$';
               p[1] = temp[0];
               p[2] = temp[1];
               p[3] = '5';
               p[4] = 0xD;
               cnt = 5;
               break;
      case 5:  p[0] = '#';
               p[1] = '*';
               p[2] = '*';
               cnt = 3;
               break;
      default:
               p[0] = '$';
               p[1] = temp[0];
               p[2] = temp[1];
               p[3] = '6';
               p[4] = 0xD;
               cnt = 5;
               break;
   }

   int nBytesSent = SendData( p, cnt );
   if( nBytesSent != cnt ) return false; 

   return true;
}
//---------------------------------------------------------------------------
int CSerial::GetPaketA4068( char packet[100] )
{
   int fl = 0;
   char buffer[1000];
   memset(buffer, 0, 1000);

   for( int i = 0; i < 100; i++ ) packet[i] = 0;

   fl = ReadDataWaiting();
   fl = ReadData(buffer, fl);

   if( fl > 0 )
   {
      for( int i = 0; i < 1000; i++ )
      {
         if( buffer[i] == '!' && buffer[i+7] == '\r' )
         {
            for( int j = 0; j <= i+7; j++) packet[j] = buffer[j+i]&0xFF;
            fl = 1;
            break;
         }
      }
   }
   else fl = -1; 

   return fl;
}
//---------------------------------------------------------------------------
void CSerial::SetTabloPaket( int adr, int packet[27] )
{
   unsigned char p[100];
   for( int i = 0; i < 100; i++ )  p[i] = 0; 
   
   p[0] = 0xE0;
   p[1] = 0x00; 
   p[2] = adr;  
   p[3] = 0x00;
   p[4] = 0x00;
   p[5] = 0x1B; 

   unsigned int crc = 0;
   for(int i = 0; i < 6; i++ ) crc += p[i];
   p[7] = crc & 0xFF;

   crc = (crc & 0xFF00)>>8;
   p[6] = (crc + p[7]) & 0xFF;

   crc = 0;
   for( int i = 0; i < 27; i++ )
   {
      p[8+i] = packet[i];
      crc = (crc+packet[i])%0x100;
   }

   p[8+27] = crc & 0xFF;

   SendData( p, 8+29 );
}
//---------------------------------------------------------------------------
bool CSerial::GetTabloPaket( int adr )
{
   int flag = 0;
   unsigned char buffer[1000];
   memset(buffer, 0, 1000);

   flag = ReadDataWaiting();
   flag = ReadData(buffer, flag);
   if( flag > 0 )
   {
      for( int i = 0; i < flag-2; i++ )
      {
         if( buffer[i] == 0xE0 && buffer[i+1] == adr )
         {
            return true;
         }
      }
   }

   return false;
}
//---------------------------------------------------------------------------

