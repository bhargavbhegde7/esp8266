# esp8266
Learning IOT with ESP8266 Wi-Fi module

# Connection for sketch upload

boot the ESP module with the below setup

| ESP8266    |      ARDUINO UNO |
|------------|------------------|
|RXD | RX <- 0|
|TXD |  TX -> 1|
|CH_PD |   HIGH (3.3v)|
|VCC  | HIGH (3.3v)|
|GND | GND|
|GPIO0  | LOW (GND)|
|GPIO2 | can be set using the code |
|RST | HIGH (3.3v) - make it low and back to high in order to reset the module|

go to preferences of energia IDE and add this in "additional board manager URL"
http://arduino.esp8266.com/stable/package_esp8266com_index.json

Here is a cool tutorial
https://diyhacking.com/esp8266-tutorial/
