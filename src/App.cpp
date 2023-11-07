#include "app.h"
#include "memory.h"

SwTimer_t g_twrTimer;
TimeStamp_t g_sendPacket;
TimeStamp_t g_receivedPacket;


BOOL ReceiveFlag = FALSE;
esp_now_peer_info_t peer1 = {};


BOOL MessageSendHandler(TimeStamp_t dataPtr, MemoryConfig_t memPtr[], DevType_t device)
{
    BOOL retVal = FALSE;

    g_sendPacket.retVal = TRUE;
    g_sendPacket.timeStamp = esp_timer_get_time();

    esp_err_t result = esp_now_send((const uint8_t *)&memPtr[device].mac, (const uint8_t *)&dataPtr, sizeof(TimeStamp_t));

    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
        retVal = TRUE;
    }
    else
    {
        Serial.println("Error sending the data");
        retVal = FALSE;
    }

    return retVal;
}

void TwrSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    ReceiveFlag = FALSE;
}

void TwrRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&g_receivedPacket, incomingData, sizeof(g_receivedPacket));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("TimeStamp: ");
    Serial.println(g_receivedPacket.timeStamp);
    Serial.print("Bool: ");
    Serial.println(g_receivedPacket.retVal);
    Serial.println();
    ReceiveFlag = TRUE;
}

BOOL TwrSentHandler(DevType_t Device)
{
    BOOL retVal = FALSE;

    if (IsTimeout(&g_twrTimer))
    {

        if (MessageSendHandler(g_sendPacket, g_devMemoryConfig, Device))
        {
            // ReceivedFlag = FALSE;
            SwTimerEnable(&g_twrTimer, 1000);
            retVal = TRUE;
        }
    }
    return retVal;
}

void Esp32NowInit()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    memcpy(peer1.peer_addr,(const void *) &g_devMemoryConfig[ANCHOR_DEVICE_ONE].mac, sizeof(peer1.peer_addr));
    peer1.channel = 0;
    peer1.encrypt = false;

    if (esp_now_add_peer(&peer1) != ESP_OK)
    {
        Serial.println("Failed to add peer1");
        return;
    }

    esp_now_register_send_cb(TwrSent);
    esp_now_register_recv_cb(TwrRecv);

}


