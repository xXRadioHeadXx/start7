//---------------------------------------------------------------------------
#ifndef TGobiSysUnitH
#define TGobiSysUnitH
//---------------------------------------------------------------------------
class TGobiIu
{
public:
   bool Use;    
   bool GobiCam;
   int Status;   /* ���������: 0-�� ����������,
                                   1-��������,
                                   2-���������
                                   10-������������� (��� �����) */
   int status1;
   int StatusOld; 
   int StatusOld2;
   int hCmd;         /* ������� ����������:
                        0 - �� ����������,
                        1 - ���������
                        2 - ��������  */
   bool hCmd2;

   int TreeIdx;   
   int Level;   
   AnsiString Name;

   int AutoOff;
   TDateTime OffDt;
};
//---------------------------------------------------------------------------
class TGobiSd
{
public:
   bool Use;
   int TreeIdx; 
   int Level;   

   bool AlarmFix; 
   int Status;       /* ���������: 0-�� ����������,
                                   1-�����,
                                   2- ������� �� ���������
                                   10-������������� (��� �����),
                                   11-������������� (��� ��),
                                   20-������� (��������)
                                   */
   int status1;
   int StatusOld; 
   int StatusOld2;
   int StatusFix; 

   bool DkOk;
   bool Dk;       
   bool Bazalt;   
   int OnOffCnt;
   bool BazaltCmd2;
   int AutoDk;
   bool PervoeSobytiePosleDk;

   bool Metka;    
   TTime Metka1Time, Metka2Time, Metka3Time, Metka4Time, MetkaDopuskTime;
   bool Metka1Ok, Metka2Ok, Metka3Ok, Metka4Ok;

   bool Razriv;   

   bool Vin;
   int Sin;

   int io;

   bool ConnectBlock;
   bool ConnectBlockHand;

   bool AlarmMsgOn;

   AnsiString Name;

   int asoosd_kk, asoosd_nn;

   double lan, lon;          
   AnsiString description;
};
//---------------------------------------------------------------------------
class TGobiCam
{
public:
   int k;
   int bl;
   int iu;
   int hcmd;
   TGobiCam();
};
//---------------------------------------------------------------------------
#define SdCnt 9
#define IuCnt 3
class TGobiBl
{
public:
   TGobiSd Sd[SdCnt];
   TGobiIu Iu[IuCnt];
   bool Use;
   bool Tv;
   int ErrCnt;
   bool NetSviazi;

   int Cmd; 
   TGobiIu Vk[IuCnt]; 

   int DkStatus; /* ��������� ���������� ������� ��
                     0 - �� �� �����������
                     1 - ���� ������� ������� "�������� ��"
                     2 - ����� (1) ������ ���������� ������� ��  */
   TTime DkTime;
   TDateTime AutoDkDt;
};
//---------------------------------------------------------------------------
#define BlCnt 128
class TGobiKanal
{
public:
   TGobiBl Bl[BlCnt];
   bool Use;
   int hCmd; /* ������� ����������:
                        0 - �� ����������,
                        1 - �������� ��
                        2 - ���������  ��
                        3 - � ��������� �� (����� ������� ������� �� ���)
                        4 - � ��������� �� (����� ������� ������� �� ����) */

   TDateTime AutoDkDt;
};
//---------------------------------------------------------------------------
#define KanCnt 4
#define MaxErrCnt1 20
#define MaxGobiCamCnt 4
class TGobiSys
{
public:
   TGobiKanal Kanal[KanCnt];
   int ErrCnt;       
   int Status;       /* ���������: 0-�� ����������,
                                   1-����� (���� �����),
                                   200-������������� (��� �����)
                                   201-����� ������������� */
   int StatusOld;    

   TTime DkDtTime1; 
   TTime DkDtTime2; 

   TGobiCam GobiCam[MaxGobiCamCnt];
   TGobiCam GobiCam2[MaxGobiCamCnt];

   int OprosAdr[KanCnt][BlCnt];

   bool AlarmMsgOn;

   TGobiSys();
   void Reset();
};
//---------------------------------------------------------------------------
class TGobiSys2
{
public:
   TGobiBl Bl[KanCnt][BlCnt];

   int OprosAdr[KanCnt][BlCnt];
   TTime DkDtTime[KanCnt]; 

   TGobiSys2();
   void Reset();
};
//---------------------------------------------------------------------------
#endif
