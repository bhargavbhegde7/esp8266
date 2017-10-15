#include <ESP8266WiFi.h>

const char *SERVER_WIFI_SSID = "crackpot2";
const char *SERVER_WIFI_PASS = "winteriscoming";

void setup()
{
   Serial.print("Connecting to WiFi ");
   WiFi.begin(SERVER_WIFI_SSID,SERVER_WIFI_PASS);
   while(WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }
 
   Serial.println("Connected");
}

void loop(){
  
}

