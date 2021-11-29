
//#define MY_DEBUG
#define MY_BAUD_RATE 9600
#define MY_RADIO_RF24
#define MY_RF24_CS_PIN 5
#define MY_SIGNING_SOFT 
#define MY_PARENT_NODE_ID 0
#define MY_SIGNING_NODE_WHITELISTING {{.nodeId = MY_PARENT_NODE_ID,.serial = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}}
#define MY_SIGNING_REQUEST_SIGNATURES 
#define MY_SIGNING_SOFT_RANDOMSEED_PIN 15
#define MY_GATEWAY_ESP8266
#define MY_WIFI_SSID "ssid"
#define MY_WIFI_PASSWORD "pw"
#define MY_HOSTNAME "ESP8266_GW"
#define MY_IP_ADDRESS 10,0,10,254
#define MY_PORT 5003
#define MY_GATEWAY_MAX_CLIENTS 2
#define MY_DEFAULT_TX_LED_PIN  16  // the PCB, on board LED
#define KidsHeatId 0

#include <MySensors.h>

MyMessage HeatMsg(KidsHeatId, V_LOCK_STATUS);

void setup()
{
        static bool runonce = true;
    if (runonce)
    {
        runonce = false;
        Serial.begin(MY_BAUD_RATE, SERIAL_8N1, MY_ESP8266_SERIAL_MODE, 1);
        _begin();
    }
    //Serial.begin(115200);
}

void presentation()
{
	present(KidsHeatId, S_LOCK);
}

void loop()
{
	// Send locally attached sensors data here
  wait(100);
  if(analogRead(A0) > 1020){
    HeatMsg.setDestination(5);
    send(HeatMsg);
    wait(1000);
  }
}

void receive(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if (message.isAck()) {
     Serial.println("This is an ack from node");
  }

  if (message.sensor == 0) {
    float temp = message.getInt();
    Serial.println("Room temp reported: " + String(temp) + " *F");
  }
  if (message.sensor == 1) {
    float temp = message.getInt();
    Serial.println("Tort's tank temp reported: " + String(temp) + " *F");
  }
  if (message.sensor == 2) {
    float humd = message.getInt();
    Serial.println("Tort's tank humidity reported: " + String(humd) + " %");
  }
}
