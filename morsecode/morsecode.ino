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
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
 
    server.on("/morsecode", handleBody); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");

    //define morse code map
 
}
 
void loop() {
 
    server.handleClient(); //Handling of incoming requests
 
}
 
void handleBody() { //Handler for the body path
 
      if (server.hasArg("message")== false){ //Check if body received
 
            server.send(200, "text/plain", "Message not found");
            return; 
      }
 
      String message = server.arg("message");
      Serial.println(message);
      Serial.println("\n");
      
      server.send(200, "text/plain", message);
      
      int lengthOfMessage = message.length();
      for (int i = 0; i < lengthOfMessage; i++) 
      {
        String morseCodeForChar = getCodeForChar(String(message[i]));
        if(morseCodeForChar.length() > 0)
        {
          Serial.println(morseCodeForChar);
        }
        else
        {
          Serial.println("bad message -> "+message);
        }
      }
}

/*
String getStringFromCharArray(char* charArray){
  int lengthOfMessage = sizeof(charArray)/sizeof(char);
  String newStr = "";
  for(int i = 0; i<lengthOfMessage; i++){
    newStr += charArray[i];
  }
  return newStr;
}
*/

/*
char* getMorseCodeForMessage(String message) {
  int lengthOfMessage = message.length()+1;
  char *morseCode = new char[lengthOfMessage];
  for (int i = 0; i < lengthOfMessage; i++) {
    morseCode[i] = getCodeForChar(message[i]);
  }

  morseCode[lengthOfMessage - 1] = NULL;

  return morseCode;
}
*/

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

