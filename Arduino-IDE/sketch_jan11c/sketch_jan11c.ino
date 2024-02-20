#include<WiFi.h>        //include the wifi library


const char* ssid     = "acts";
const char* password = "";

void setup(){
  Serial.begin(115200);       //Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("\n");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n");
  Serial.println("Connection established");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop(){
  
}
