//---------------------------------------------------------------------------
#ifndef EseU485IOUnitH
#define EseU485IOUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#define ESEU485DevCnt 4
//---------------------------------------------------------------------------
#define iLargeSize 512*1024
//---------------------------------------------------------------------------
#define  GET_CAM_MODEL_INFO         0x00  
#define  GET_GAIN_INFO              0x01  
#define  GET_BRIGHTNESS_INFO        0x02  
#define  GET_SHUTTER_INFO           0x03  
#define  GET_FORMAT_INFO            0x04  
#define  GET_TOP_INFO               0x05  
#define  GET_LEFT_INFO              0x06  
#define  GET_HEIGHT_INFO            0x07  
#define  GET_WIDTH_INFO             0x08  
#define  GET_COMRESS_QUALITY_INFO   0x09  
#define  GET_THERMOSTAT_INFO        0x0A  
#define  GET_BAUDRATE_INFO          0x0B  
#define  GET_MEMORY_INFO            0x0C  
#define  GET_AUTO_LEVEL_INFO        0x0D  
#define  GET_AUTO_MODE_INFO         0x0E  
#define  GET_AUTO_ZONE_LEFT_INFO    0x0F  
#define  GET_AUTO_ZONE_TOP_INFO     0x10  
#define  GET_AUTO_ZONE_RIGHT_INFO   0x11  
#define  GET_AUTO_ZONE_BOTTOM_INFO  0x12  
#define  GET_SHARPNESS_INFO         0x13  
#define  GET_GAMMA_INFO             0x14  
#define  GET_INTERVAL_INFO          0x15  
#define  GET_IRIS_INFO              0x16  
#define  GET_FRAME_CUT_INFO         0x17  
#define  GET_FRAME_INSERT_INFO      0x18  
#define  GET_IO_POLARITY_INFO       0x19  
#define  GET_MEMORY_SECTOR_SIZE_INFO   0x1B 

#define  GET_GAIN                   0x21  
#define  GET_BRIGHTNESS             0x22  
#define  GET_SHUTTER                0x23  
#define  GET_FORMAT                 0x24  
#define  GET_TOP                    0x25  
#define  GET_LEFT                   0x26  
#define  GET_HEIGHT                 0x27  
#define  GET_WIDTH                  0x28  
#define  GET_COMRESS_QUALITY        0x29  
#define  GET_THERMOSTAT             0x2A  
#define  GET_BAUDRATE               0x2B  
#define  GET_MEMORY                 0x2C  
#define  GET_AUTO_LEVEL             0x2D  
#define  GET_AUTO_MODE              0x2E  
#define  GET_AUTO_ZONE_LEFT         0x2F  
#define  GET_AUTO_ZONE_TOP          0x30  
#define  GET_AUTO_ZONE_RIGHT        0x31  
#define  GET_AUTO_ZONE_BOTTOM       0x32  
#define  GET_SHARPNESS              0x33  
#define  GET_GAMMA                  0x34  
#define  GET_INTERVAL               0x35  
#define  GET_IRIS                   0x36  
#define  GET_FRAME_CUT              0x37  
#define  GET_FRAME_INSERT           0x38  
#define  GET_IO_POLARITY            0x39  
#define  GET_AGC                    0x38  
#define  GET_AEC                    0x39  
#define  GET_AIC                    0x3A  
#define  GET_MEMORY_SECTOR_SIZE     0x3B  

#define  SET_GAIN                   0x41  
#define  SET_BRIGHTNESS             0x42  
#define  SET_SHUTTER                0x43  
#define  SET_FORMAT                 0x44  
#define  SET_TOP                    0x45  
#define  SET_LEFT                   0x46  
#define  SET_HEIGHT                 0x47  
#define  SET_WIDTH                  0x48  
#define  SET_COMRESS_QUALITY        0x49  
#define  SET_THERMOSTAT             0x4A  
#define  SET_BAUDRATE               0x4B  
#define  SET_MEMORY                 0x4C  
#define  SET_AUTO_LEVEL             0x4D  
#define  SET_AUTO_MODE              0x4E  
#define  SET_AUTO_ZONE_LEFT         0x4F  
#define  SET_AUTO_ZONE_TOP          0x50  
#define  SET_AUTO_ZONE_RIGHT        0x51  
#define  SET_AUTO_ZONE_BOTTOM       0x52  
#define  SET_SHARPNESS              0x53  
#define  SET_GAMMA                  0x54  
#define  SET_INTERVAL               0x55  
#define  SET_IRIS                   0x56  
#define  SET_FRAME_CUT              0x57  
#define  SET_FRAME_INSERT           0x58  
#define  SET_IO_POLARITY            0x59  
#define  SET_MEMORY_SECTOR_SIZE     0x5B  

#define  GET_CADR                   0x80  
#define  GET_MEMORY_INFO            0x0C  
#define  GET_MEMORY_RECORD          0xAC  
#define  SAVE_SETTINGS              0x7F  
//---------------------------------------------------------------------------
int SetCmd( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned short ucValue );
int SetCmd1( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned char ucValue );
int SetCmd2( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd, unsigned char ucMode, unsigned short usCntValue,
             unsigned short ucValue  );
int SetCmd3( char num1, unsigned char num2, unsigned char num3,
             unsigned char ucCmd );
int GetSettings( char num1, unsigned char num2, unsigned char num3,
                 unsigned char ucCmd,
					  unsigned short* usMinValue,
					  unsigned short* usMaxValue,
					  unsigned short* usValue,
					  unsigned char*  ucMode,
                 unsigned char pBuf[8],
                 unsigned char tBuf[64] );
int GetSettings2( char num1, unsigned char num2, unsigned char num3,
                 unsigned char ucCmd, unsigned char tBuf[2], unsigned char pBuffer[64] );
AnsiString RezToStr( int code );
//---------------------------------------------------------------------------
#endif
 