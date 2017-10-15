#include <UbidotsESP8266.h>
#include <SoftwareSerial.h> 

#define SSID "crackpot2"
#define PASS "winteriscoming"

#define TOKEN "A1E-K1DbIaSFWLBiWVnOGcrQUfQFUWQcX4"
#define ID "59dba7dbc03f9750ce06303b"

Ubidots client(TOKEN);

void setup() {
  Serial.begin(9600);
  client.wifiConnection(SSID,PASS);
}

void loop() {
  float value = analogRead(A0);
  client.add(ID,value);
  client.sendAll();
}
