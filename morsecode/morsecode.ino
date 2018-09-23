#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
 
const char* ssid = "halfbloodprince";
const char* password =  "sectumsempra";
int ledPin = D5; // GPIO2 of ESP8266

String morseMap[86][2] =         {{"A", ".-"},
        {"B", "-..."},
        {"C", "-.-."},
        {"D", "-.."},
        {"E", "."},
        {"F", "..-."},
        {"G", "--."},
        {"H", "...."},
        {"I", ".."},
        {"J", ".---"},
        {"K", "-.-"},
        {"L", ".-.."},
        {"M", "--"},
        {"N", "-."},
        {"O", "---"},
        {"P", ".--."},
        {"Q", "--.-"},
        {"R", ".-."},
        {"S","..."},
        {"T", "-"},
        {"U", "..-"},
        {"V", "...-"},
        {"W", ".--"},
        {"X", "-..-"},
        {"Y", "-.--"},
        {"Z", "--.."},
        {"a", ".-"},
        {"b", "-..."},
        {"c", "-.-."},
        {"d", "-.."},
        {"e", "."},
        {"f", "..-."},
        {"g", "--."},
        {"h", "...."},
        {"i", ".."},
        {"j", ".---"},
        {"k", "-.-"},
        {"l", ".-.."},
        {"m", "--"},
        {"n", "-."},
        {"o", "---"},
        {"p", ".--."},
        {"q", "--.-"},
        {"r", ".-."},
        {"s","..."},
        {"t", "-"},
        {"u", "..-"},
        {"v", "...-"},
        {"w", ".--"},
        {"x", "-..-"},
        {"y", "-.--"},
        {"z", "--.."},
        {"0", "-----"},
        {"1", ".----"},
        {"2", "..---"},
        {"3", "...--"},
        {"4", "....-"},
        {"5", "....."},
        {"6", "-...."},
        {"7", "--..."},
        {"8", "---.."},
        {"9", "----."},
        {"à", ".--.-"},
        {"å", ".--.-"},
        {"ä", ".-.-"},
        {"è", ".-..-"},
        {"é", "..-.."},
        {"ö", "---."},
        {"ü", "..--"},
        {"ß", "...--.."},
        {"ñ", "--.--"},
        {".", ".-.-.-"},
        {",", "--..--"},
        {":", "---..."},
        {";", "-.-.-."},
        {"?", "..--.."},
        {"-", "-....-"},
        {"_", "..--.-"},
        {"(", "-.--."},
        {")", "-.--.-"},
        {"'", ".----."},
        {"=", "-...-"},
        {"+", ".-.-."},
        {"/", "-..-."},
        {"@", ".--.-."},
        {" ", "/"}};

void setup() {
 
    Serial.begin(115200);
    WiFi.begin(ssid, password);  //Connect to the WiFi network

    pinMode(ledPin, OUTPUT);
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
 
    server.on("/", handlePost); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");
}
 
void loop() 
{
    server.handleClient(); //Handling of incoming requests
}
 
void handlePost() //Handler for post
{ 

      if (server.hasArg("message")== false){ //Check if body received
 
            server.send(200, "text/plain", "send message via http post to this URL as form data. key - 'message'");
            return; 
      }
 
      String message = server.arg("message");
      Serial.println(message);
      Serial.println("\n");
      
      server.send(200, "text/plain", message);

      for (int i = 0; i < message.length(); i++) 
      {
        String morseCodeForChar = getCodeForChar(String(message[i]));
        if(morseCodeForChar.length() > 0)
        {
          Serial.println(morseCodeForChar);
          displayCode(morseCodeForChar);
          delay(400);
        }
        else
        {
          Serial.println("bad message -> "+message);
        }
      }
}

String getCodeForChar(String c) 
{
  for(int i = 0; i<86; i++)
  {
    if(morseMap[i][0] == c)
    {      
      return morseMap[i][1];
    }
  }  
  
  return "";
}

void displayCode(String morseCode)
{
  for(int i = 0; i<morseCode.length(); i++)
  {
    play(morseCode[i]);
    delay(200);
  }
}

void play(char c)
{
  if(c == '.')
  {
    turnOnFor(100);
  }
  else if (c == '-')
  {
    turnOnFor(500);
  }
  else if (c == '/')
  {
    delay(1000);
  }
  //Serial.println(String(c));
}

void turnOnFor(int milliseconds)
{
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(milliseconds);                       // wait for a second
  digitalWrite(ledPin, LOW);
  delay(100);
}
