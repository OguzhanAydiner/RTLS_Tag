#include "App.h"
#include "Notation.h"
#include "Memory.h"


MacAddress_t            g_macList[3];
TimeStamp_t             myData;


// Create a struct_message called myData


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("TimeStamp: ");
  Serial.println(myData.timeStamp);
  Serial.print("Bool: ");
  Serial.println(myData.retVal);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  
}
 
void loop() {

  Serial.println(WiFi.macAddress());
  delay(10000);
}