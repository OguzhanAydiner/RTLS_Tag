#ifndef APP_H
#define APP_H


#include "Notation.h"
#include "Memory.h"




typedef struct {
	U32				timeStamp;
	BOOL			retVal;
} TimeStamp_t;



extern TimeStamp_t  	 g_sendPacket;
extern TimeStamp_t  	 g_receivedPacket;


/*                          Functions                                          */

void DataSentCallBack(const uint8_t *mac_addr, esp_now_send_status_t status);
BOOL MessageSendHandler(TimeStamp_t *dataPtr, MemoryConfig_t *memPtr, DevType_t device);
BOOL TimeStampHandler();
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
void Esp32NowInit();

#endif