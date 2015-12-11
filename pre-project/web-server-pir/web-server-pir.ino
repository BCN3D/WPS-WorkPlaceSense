#include <ESP8266WiFi.h>

//Variables network
const char* ssid = "BCN3D Technologies";
const char* password = "formacion";

WiFiServer server(80);
const int pirPin = 14;

int movestatus =0;

void setup() {    
  //Establish PIR
  pinMode(pirPin,INPUT);
    
  //Establish Serial connection
  Serial.begin(115200);
  delay(100); 
  
  //Print ssid
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);  
  
  //Connect to net
  WiFi.begin(ssid, password);
  //connecting to net
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
 //Print net status and @IP
  Serial.println();
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());  
  
  //Start server
  server.begin();
  Serial.println("Server started");  
}
 
void loop() {
  //receive the clients request and send the missage
  server_function();
  
  //Read the PIR sensor and changes the movestatus value each second
  movestatus = digitalRead(pirPin);
  if(movestatus == HIGH){    
    Serial.println("movement detected");
    delay(1000);
  }
  else {Serial.println("movement not detected"); delay(1000);}
}



