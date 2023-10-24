#include "App.h"
#include "Notation.h"
#include "Memory.h"
#include "SwTimer.h"
#include "freertos/queue.h"


MacAddress_t            g_macList[3];




QueueHandle_t packetQueue;
QueueHandle_t responseQueue;
void transmitterTask(void *pvParameters);
void receiverTask(void *pvParameters);

TimerHandle_t xTimer;
const TickType_t xPeriod = pdMS_TO_TICKS(3000);  // Timer period in milliseconds
void vTimerCallback(TimerHandle_t xTimer);
TaskHandle_t transmitterTaskHandle;
TaskHandle_t receiverTaskHandle;


void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  MemoryInit();
  Esp32NowInit();
  
  g_sendPacket.timeStamp = 1111;
  g_sendPacket.retVal = FALSE;

  SwTimerEnable(&TwrTimer, 1000);



  packetQueue = xQueueCreate(10, sizeof(TimeStamp_t));
  responseQueue = xQueueCreate(10, sizeof(TimeStamp_t));
  xTaskCreate(transmitterTask, "TransmitterTask", 2048, NULL, 5, NULL);


    
}
 




void loop()
{
    
 /*  if(IsTimeout(&TwrTimer))
    {
        if(MessageSendHandler(&g_sendPacket, g_devMemoryConfig, ANCHOR_DEVICE_ONE))
        {
            SwTimerEnable(&TwrTimer, 3000);
        }
    

    }*/



} 



void transmitterTask(void *pvParameters) {

     if(IsTimeout(&TwrTimer))
    {
        if(MessageSendHandler(&g_sendPacket, g_devMemoryConfig, ANCHOR_DEVICE_ONE))
        {
            SwTimerEnable(&TwrTimer, 3000);
        }           


    }

}




void vTimerCallback(TimerHandle_t xTimer) {
    // Task code to be executed when the timer expires
   // xTaskNotifyGive(transmitterTaskHandle);
   // xTaskNotifyGive(receiverTaskHandle);

    //MessageSendHandler(&g_sendPacket, g_devMemoryConfig, TAG_DEVICE);
}