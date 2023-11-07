#ifndef APP_H
#define APP_H

#include "notation.h"
#include "memory.h"
#include "swTimer.h"

/*                          Functions                                          */

void TwrSent(const uint8_t *mac_addr, esp_now_send_status_t status);
BOOL MessageSendHandler(TimeStamp_t dataPtr, MemoryConfig_t memPtr[], DevType_t device);
void TwrRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
void Esp32NowInit();
BOOL TwrSentHandler(DevType_t Device);

extern SwTimer_t g_twrTimer;
extern TimeStamp_t g_sendPacket;
extern TimeStamp_t g_receivedPacket;
extern BOOL ReceiveFlag;
#endif