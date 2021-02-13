 #include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define DHTTYPE DHT22 

#include "index.h" //HTML
#include "wifi.h" //WiFi

// DHT 22 on D2 pin
uint8_t DHTPin = D2;
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}

void handlereasurements(){
 Temperature = dht.readTemperature(); // Gets the values of the temperature
 Humidity = dht.readHumidity(); // Gets the values of the humidity 
 String JSON = "{";
    JSON += "\"Temperature\": ";
    JSON += (String) Temperature;
    JSON += ", ";
    JSON += "\"Humidity\": ";
    JSON += (String) Humidity;
    JSON += "}";
 server.send(200, "application/javascript", JSON);
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);
  dht.begin(); 
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("Connecting to WiFi");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readMeasurements", handlereasurements); //This page is called by java Script AJAX

  server.begin();
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient(); //Handle client requests
}
