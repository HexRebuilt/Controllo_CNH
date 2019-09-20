#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>

#include "WiFi_info.h" //for wifi configuration
#include "web_server.h" //for webserver

char ssid[] = WiFi_SSID; 
char pass[] = WiFi_PSW;
int keyIndex = 0;   // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;

// Initialize the WiFi server library
WiFiServer server(80);
IPAddress ip;


//function that prints over serial port the wireless informations
void printWiFiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    // print your WiFi shield's IP address:
    Serial.print("IP Address: ");
    Serial.println(ip);
    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

/**
 * function that defines the pins and connects to the network
 * */
void Setup_WiFi() {
  // check for the presence of the shield:
  
  // Configure pins for Adafruit Feather M0 ATWINC1500
  WiFi.setPins(8, 7, 4, 2);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    return;
  }
  Serial.println("WiFI shield present");
  
  while (WiFi.status() !=WL_CONNECTED) {
    // Connect to WPA/WPA2 network:
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // Wait 5 seconds for connection
    delay(5000);
  }
  Serial.println("Connected to the network");
  
  // Start the server
  Setup_web();
  ip = WiFi.localIP();
  Serial.println("Server started");
  
  printWiFiStatus();
}

/**
 * Function tht's called at each loop. it displays the data on a webpage
 * it returns a comand to the main that will analyze it and operate.
 * 
 * in input has a vector of strings constructed to be displayed by rows
 * */

//TODO analize the data string and split into smaller strings with informations
String Loop_WiFi(String main_data){
//si deve appoggiare ad un web server




}