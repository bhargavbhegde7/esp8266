#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *SERVER_WIFI_SSID = "crackpot2";
const char *SERVER_WIFI_PASS = "winteriscoming";

int ledPin = 2; // GPIO2 of ESP8266

void setupWiFi()
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

void setup() {
  Serial.begin(9600);
  setupWiFi();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;

  //Let is try a GET request first 
  //http.begin("http://192.168.0.104:8080/webappfordemo/Version");
  //http.begin("http://jsonplaceholder.typicode.com/users/1");http://192.168.0.8:8080/
  http.begin("http://192.168.0.8:3000/");

  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK)
  {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      String response = http.getString();

      String foo = "foo";
      String bar = "bar";

      //Serial.println(response);

      response.trim();

      int value = LOW;
      if(foo.equals(response))
      {
        Serial.println("FOO");
        digitalWrite(ledPin, HIGH);
        value = HIGH;
      }

      if(bar.equals(response))
      {
        Serial.println("BAR");
        digitalWrite(ledPin, LOW);
        value = LOW;
      }

      if(value == HIGH) {
        Serial.println("On");  
      } else {
        Serial.println("Off");
      }
  }
  else
  {
    Serial.println("Error in HTTP request");
  }

  http.end();
  
  Serial.println();

  delay(3000);

}
