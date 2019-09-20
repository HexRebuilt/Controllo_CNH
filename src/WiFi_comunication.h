#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
#include "WiFi_info.h"


int status = WL_IDLE_STATUS;
//edit the wifi information in the WiFi_info.h files
char ssid[] = WiFi_SSID; 
char pass[] = WiFi_PSW;
int keyIndex = 0;   // your network key Index number (needed only for WEP)
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
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    Serial.println("Only Serial connection avaible");
    return;
  }
  Serial.println("WiFI shield present");
  // Configure pins for Adafruit Feather M0 ATWINC1500
  WiFi.setPins(8, 7, 4, 2);

  while (WiFi.status() != WL_DISCONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); //connection to the wifi
    // Wait 5 seconds for connection
    delay(5000);
  }
  
  // Start the server
  server.begin();
  ip = WiFi.localIP();
  Serial.println("Server started");
  printWiFiStatus();
  

}