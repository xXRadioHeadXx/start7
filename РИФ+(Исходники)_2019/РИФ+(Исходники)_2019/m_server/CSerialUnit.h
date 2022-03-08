//---------------------------------------------------------------------------
#ifndef SerialUnitH
#define SerialUnitH
//---------------------------------------------------------------------------
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13
//---------------------------------------------------------------------------
typedef unsigned int uint;
//---------------------------------------------------------------------------
class CSerial
{
public:
	CSerial();
	~CSerial();

	BOOL Open( int nPort = 2, int nBaud = 9600 );
	BOOL Close( void );

	int ReadData( void *, int );
	int SendData( const char *, int );
	int SendData2( unsigned char *, int );    
	int ReadDataWaiting( void );

	BOOL IsOpened( void ){ return( m_bOpened ); }

   int SendOk;

   int speed;
   void Send3FF();

   bool SetCmd( int Adr, int Cmd, int D1, bool send3FF );
   bool SetCmd1( int Adr, int Cmd, int D1, int D2, bool send3FF );
   bool SetCmd2( int Adr, int Cmd, bool send3FF );
   bool SetCmd3( int Adr, int Cmd, bool send3FF );
   bool SetCmd4( int Adr, int Cmd, int DdNum, bool send3FF );
   bool SetCmdSsoi2( int Adr, int Cmd, int D1 );
   bool SetCfg( int adr, int por, int rez, int t, bool send3FF );
   bool SetCfg1( int adr, bool on[4], bool send3FF );
   bool SetCfg2( int adr, int por1, int por2, bool send3FF );
   bool SetCfg3( int adr, int por1, int por2, int rez1, int rez2, bool send3FF );
   bool SetCfg4( int adr, int por1, int por2, int por3, int rez, bool send3FF );
   bool SetCfg5( int adr, int sett[4], bool send3FF );
   bool SetCfg6( int adr, int por, int rez, int t, bool send3FF );
   bool SetCfg7( int adr, int ddnum,
                 int f12_che1, int por_f1che1, int por_f2che1, int tv_f1che1, int tv_f2che1, int cnt_f1che1, int cnt_f2che1, int tp_f1che1, int tp_f2che1,
                 int f12_che2, int por_f1che2, int por_f2che2, int tv_f1che2, int tv_f2che2, int cnt_f1che2, int cnt_f2che2, int tp_f1che2, int tp_f2che2, bool send3FF  );
   bool SetCfg8( int adr, int BO_type, unsigned char cfg[26], int adr1, int adr2, bool send3FF  );
   bool SetCfg9( int adr, int ddnum,
                 int f12_che1, int por_f1che1, int por_f2che1, int tv_f1che1, int tv_f2che1, int cnt_f1che1, int cnt_f2che1, int tp_f1che1, int tp_f2che1, bool send3FF  );
   bool SetDk( int adr, bool send3FF );
   bool ResetFlags( int adr, bool send3FF );
   bool ResetFlags1( int adr, bool send3FF );
   bool SetOn( int adr, bool send3FF );
   bool SetOff( int adr, bool send3FF );
   bool SetPultOn( int adr, bool send3FF );
   bool SetPultOff( int adr, bool send3FF );
   bool SetStatus( int adr, bool send3FF );
   bool SetStatus1( int adr, bool send3FF );
   bool SetStatus2( int adr, bool send3FF );
   bool SetStatus3( int adr, int cmd, bool send3FF );
   bool SetStatus4( int adr, bool send3FF );
   bool SetStatus5( int adr, bool send3FF );
   bool SetIu( int adr, int status, bool send3FF );
   bool SetSd( int adr, int status, bool send3FF );
   int GetPaket( int adr, int packet[1000] );
   int GetPaketSsoi2( int adr, int packet[30] );
   int GetPaketSsoi2_v2( int adr, int packet[10000] );

   bool BS_setup( int b[9] );
   bool Dk( int kan, bool On );
   bool IuCmd( int k, int b, int cmd1, int cmd2, int cmd3 );

   int TvCmd( int m, int cmd );
   int TvOn( int m, int n );

   int TvLeft(int m);
   int TvRight(int m);
   int TvUp(int m);
   int TvDn(int m);
   int TvFUp(int m);
   int TvFDn(int m);
   int TvUv(int m);
   int TvUm(int m);

   int TvS( unsigned char buf[128] );

   bool SetCmdA4068( int adr, int Cmd, int data[8] );
   int GetPaketA4068( char packet[100] );

   void SetTabloPaket( int adr, int packet[27] );
   bool GetTabloPaket( int adr );

protected:
	BOOL WriteCommByte( unsigned char );
	int WriteCommBytes( unsigned char *, int size );

	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	BOOL m_bOpened;
};
//---------------------------------------------------------------------------
#endif
