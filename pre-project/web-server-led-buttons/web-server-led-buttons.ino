#include <ESP8266WiFi.h>


//Variables network
const char* ssid = "xavier.gomez";
const char* password = "1234567890";


WiFiServer server(80);
const int ledPin = 0;

void setup() {
  
  //Establish led
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,0);
  
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
  WiFiClient client = server.available();
  if(!client) return;
  
  while(!client.available()) delay(1);
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  int val;
  if(req.indexOf("/LED=ON") != -1) val = HIGH;
  else if (req.indexOf("/LED=OFF") != -1) val = LOW;
  else { client.stop(); return;}
  digitalWrite(ledPin,val);
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.print("Led pin is now: ");
  if(val == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("<p>GPIO0 <a href=\"/LED=ON\"><button>ON</button></a>&nbsp;<a href=\"/LED=OFF\"><button>OFF</button></a></p>"); 
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
}


