//---------------------------------------------------------------------------
#pragma hdrstop

#include "EseU485IOUnit.h"
#include "usb_uart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma warn -aus
//---------------------------------------------------------------------------
int SetCmd( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned short ucValue )
{
	unsigned char CommandPacket[]= {0xb5, 0x01, 0xfe,
							0x00,
							0x08,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00};

	CommandPacket[1]=num3;
	CommandPacket[3]=ucCmd;
	CommandPacket[5]=ucMode;
	CommandPacket[11]=(ucValue & 0xFF00)>>8;
	CommandPacket[12]=(ucValue & 0xFF);
	CommandPacket[13]=CommandPacket[1]+CommandPacket[2]+CommandPacket[3]+CommandPacket[4]+
						CommandPacket[5]+CommandPacket[6]+CommandPacket[7]+CommandPacket[8]+
						CommandPacket[9]+CommandPacket[10]+CommandPacket[11]+CommandPacket[12];

   return SendPacket(num1,num2,sizeof(CommandPacket),&CommandPacket[0]);
}
//---------------------------------------------------------------------------
int SetCmd1( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned char ucValue )
{
	unsigned char CommandPacket[]= {0xb5, 0x01, 0xfe,
							0x00,
							0x08,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00};

	CommandPacket[1]=num3;
	CommandPacket[3]=ucCmd;
	CommandPacket[5]=ucMode;
	CommandPacket[11]=(ucValue & 0xFF00)>>8;
	CommandPacket[12]=(ucValue & 0xFF);
	CommandPacket[13]=CommandPacket[1]+CommandPacket[2]+CommandPacket[3]+CommandPacket[4]+
						CommandPacket[5]+CommandPacket[6]+CommandPacket[7]+CommandPacket[8]+
						CommandPacket[9]+CommandPacket[10]+CommandPacket[11]+CommandPacket[12];

   return SendPacket(num1,num2,sizeof(CommandPacket),&CommandPacket[0]);
}
//---------------------------------------------------------------------------
int SetCmd2( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned short usCntValue,
             unsigned short ucValue  )
{
	unsigned char CommandPacket[]={0xb5,0x01,0xfe,
							0x00,
							0x08,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00};

	CommandPacket[1]=num3;
	CommandPacket[3]=ucCmd;
	CommandPacket[5]=ucMode;
	CommandPacket[9]=(usCntValue & 0xFF00)>>8;
	CommandPacket[10]=(usCntValue & 0xFF);
	CommandPacket[11]=(ucValue & 0xFF00)>>8;
	CommandPacket[12]=(ucValue & 0xFF);
	CommandPacket[13]=CommandPacket[1]+CommandPacket[2]+CommandPacket[3]+CommandPacket[4]+
						CommandPacket[5]+CommandPacket[6]+CommandPacket[7]+CommandPacket[8]+
						CommandPacket[9]+CommandPacket[10]+CommandPacket[11]+CommandPacket[12];

	return SendPacket(num1,num2,sizeof(CommandPacket),&CommandPacket[0]);
}
//---------------------------------------------------------------------------
int SetCmd3( char num1, unsigned char num2, unsigned char num3, unsigned char ucCmd )
{
	unsigned char CommandPacket[]= {0xb5, 0x01, 0xfe, 0x00, 0x00, 0x00};

	CommandPacket[1]=num3;
	CommandPacket[3]=ucCmd;
   for( int i = 1; i < 5; i++ ) CommandPacket[5] = (CommandPacket[5] + CommandPacket[i])%256;	

   return SendPacket(num1,num2,sizeof(CommandPacket),&CommandPacket[0]);
}
//---------------------------------------------------------------------------
int GetSettings( char num1, unsigned char num2, unsigned char num3,
                 unsigned char ucCmd,
  					  unsigned short* usMinValue,
					  unsigned short* usMaxValue,
					  unsigned short* usValue,
					  unsigned char*  ucMode,
                 unsigned char pBuf[8],
                 unsigned char tBuf[64] )
{
   int rez = -1;
   unsigned char pBuffer[64];
   for(int i = 0; i < 64; i++ ) { pBuffer[i] = 0; tBuf[i] = 0; }
   for(int i = 0; i < 8; i++ ) pBuf[i] = 0;

   Sleep(100);
   rez = GetShortInputBuffer(num1,num2,pBuffer);
   for(int i = 0; i < 64; i++ ) tBuf[i] = pBuffer[i];

	unsigned char crc;
	if( rez == 0 )
   {
      rez = 102; 
   	crc = 0;

      if( pBuffer[63] != 0 ) 
      {
          for( int i = 0; i < (63-16); i++ )
          {
             if( (pBuffer[i+1] == 0xfe) && (pBuffer[i+3] == ucCmd) )
             {
                if( pBuffer[i+2] == num3 )
                {
                   for( int j = 1; j < 16; j++ ) crc = crc + pBuffer[i+j];
                   crc = crc - (num3-1);

                   if( crc == pBuffer[i+16] )
                   {
                      *ucMode = pBuffer[i+8]&3;
                      unsigned short t = pBuffer[i+10]<<8;
                      t = t + pBuffer[i+11];
                      *usMinValue = t;
                      t = pBuffer[i+12]<<8;
                      t = t + pBuffer[i+13];
                      *usMaxValue = t;
                      t = pBuffer[i+14]<<8;
                      t = t + pBuffer[i+15];
                      *usValue= t;

                      pBuf[0] = pBuffer[i+8];
                      pBuf[1] = pBuffer[i+9];
                      pBuf[2] = pBuffer[i+10];
                      pBuf[3] = pBuffer[i+11];
                      pBuf[4] = pBuffer[i+12];
                      pBuf[5] = pBuffer[i+13];
                      pBuf[6] = pBuffer[i+14];
                      pBuf[7] = pBuffer[i+15];

                      rez = 0;
                      break;
                   }
                   else
                   {
                      rez = 103; 
                      break;
                   }
                }
                else rez = 102; 
             }
             else rez = 102; 
          }
      }
      else rez = 104; 
   }

   return rez;
}
//---------------------------------------------------------------------------
int GetSettings2( char num1, unsigned char num2, unsigned char num3,
                 unsigned char ucCmd, unsigned char tBuf[2], unsigned char pBuffer[64] )
{
   int rez = 104;
   for(int i = 0; i < 64; i++ ) pBuffer[i] = 0;

   rez = GetShortInputBuffer(num1,num2,pBuffer);
   for(int i = 0; i < 64; i++ ) pBuffer[i] = pBuffer[i]&0xFF;

	unsigned char crc;
	if( rez == 0 )
   {
      rez = 102; 
   	crc = 0;

      if( pBuffer[63] >= 8 )
      {
         for(int i = 0; i < 63-8; i++)
         {
            if( pBuffer[i] == 0xB5 || pBuffer[i] == 0xFF )
            {
               if( pBuffer[i+1] == 0xFE )
               {
                  if( pBuffer[i+2] == num3 )
                  {
                     if( pBuffer[i+3] == ucCmd )
                     {
                        for( int j = i+1; j < i+7; j++ ) crc = crc + pBuffer[j];
                        if( crc == pBuffer[i+7] )
                        {
                           tBuf[0] = pBuffer[i+5];
                           tBuf[1] = pBuffer[i+6];

                           rez = 0; 
                           break;
                        }
                        else  rez = 103; 
                     }
                  }
               }
            }
         }
      }
   }

   return rez;
}
//---------------------------------------------------------------------------
AnsiString RezToStr( int code )
{
   AnsiString rez;

   switch( code )
   {
      case 0:  rez = "Операция завершена успешно. Код = "; break;
      case 1:  rez = "Неправильный входной параметр. Код = "; break;
      case 2:  rez = "ESE-U485 повреждено или отсутствует. Код = "; break;
      case 3:  rez = "Внутренняя ошибка ESE-U485. Код = "; break;
      case 4:  rez = "Внутренняя ошибка ESE-U485. Код = "; break;
      case 101:  rez = "Ошибка выделения памяти. Код = "; break;
      case 102:  rez = "Ошибка принятого пакета. Код = "; break;
      case 103:  rez = "Ошибка контрольной суммы. Код = "; break;
      case 104:  rez = "Ошибка. Нет ответа от камеры. Код = "; break;
      case 105:  rez = "Ошибка. Серийный номер устройства не совпадает с данными файла конфигурации. Код = "; break;
      default: rez = "Неизвестная ошибка. Код = "; break;
   }

   rez = rez + IntToStr(code);
   
   return rez;
}
//---------------------------------------------------------------------------

