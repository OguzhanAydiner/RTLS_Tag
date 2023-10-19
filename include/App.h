#ifndef APP_H
#define APP_H


#include "Notation.h"
#include "Memory.h"


#endif

typedef struct {
	U32				timeStamp;
	BOOL			retVal;
} TimeStamp_t;






/*                          Functions                                          */

void DataSentCallBack(const uint8_t *mac_addr, esp_now_send_status_t status);
BOOL TimeStampHandler();


