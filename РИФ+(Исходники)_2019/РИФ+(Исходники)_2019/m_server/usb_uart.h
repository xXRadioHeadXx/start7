#ifndef _USB_UART_H_
#define _USB_UART_H_

#ifdef USB_UART_EXPORTS
#define USB_UART_API __declspec(dllexport)
#else
#define USB_UART_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DEVICE_AT_ONCE	2
#define MAX_CHANNEL_NMB		4	

typedef struct _UART_STATUS
{	
   BYTE ChannelRate[MAX_CHANNEL_NMB];
   BYTE ChannelInterval[MAX_CHANNEL_NMB];
   unsigned short ChannelTimeout[MAX_CHANNEL_NMB];
   
} UART_STATUS, *PUART_STATUS;

typedef struct _DEVICE_ID_PARAMS{

	char	chDeviceSerial[8];
	char	chDeviceSecure[120];

} DEVICE_ID_PARAMS, *PDEVICE_ID_PARAMS;

BOOL InitDevice(char BusIndex);

BOOL USB_UART_API SendI2C(char BusIndex, unsigned char uDevAddr, unsigned char uRegAddr, unsigned char uHByte, unsigned char uLByte);
BOOL USB_UART_API ReceiveI2C(char BusIndex, unsigned char uDevAddr, unsigned char uRegAddr, unsigned char* puHByte, unsigned char* puLByte);

int USB_UART_API GetShortInputBuffer(char BusIndex, 
									 unsigned char uChannel,
									 unsigned char* pBuffer);

int USB_UART_API GetLargeInputBuffer(char BusIndex,
									 unsigned char uChannel, 
									 unsigned int iSize, 
									 unsigned char* pBuffer);

int USB_UART_API SendPacket(char BusIndex, 
							 unsigned char ucChannel, 
							 unsigned char ucSize,
							 unsigned char* pBuffer
							 );

int USB_UART_API SetUartMasterRate(char BusIndex,
									 unsigned char ucChannel, 
									 unsigned char ucDivider);

int USB_UART_API SetUartMasterInterval(char BusIndex,
									 unsigned char ucChannel, 
									 unsigned char ucUsInterval);

int USB_UART_API SetUartMasterTimeout(char BusIndex,
									 unsigned char ucChannel, 
									 unsigned short usMsTimeout);

int USB_UART_API GetUartStatus(char BusIndex,
							   PUART_STATUS pUartStatus);

int USB_UART_API SaveUartSettings(char BusIndex);

int USB_UART_API GetDeviceID(char BusIndex, PDEVICE_ID_PARAMS pID);	


#ifdef __cplusplus
}
#endif

#endif

