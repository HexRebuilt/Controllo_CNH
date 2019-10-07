/**
 * File that menages the wifi comunication both in input and as a webserver
 * */

#include <Arduino.h>
#include <WiFi101.h>

#include "Secrets.h"

class WiFiComunication{
    private:
    
    ///////please enter your sensitive data in the Secret tab/Secrets.h
    char ssid[] = SECRET_SSID;        // your network SSID (name)
    char pass[] = SECRET_PSW;         // your network password (use for WPA, or use as key for WEP)
    int status = WL_IDLE_STATUS;      // the WiFi radio's status
    
    //set of arduino base function to connect to a network
    void printWiFiData() {
        // print your WiFi shield's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("IP Address: ");
        Serial.println(ip);
        Serial.println(ip);

        // print your MAC address:
        byte mac[6];
        WiFi.macAddress(mac);
        Serial.print("MAC address: ");
        printMacAddress(mac);

        }

    void printCurrentNet() {
        // print the SSID of the network you're attached to:
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        // print the MAC address of the router you're attached to:
        byte bssid[6];
        WiFi.BSSID(bssid);
        Serial.print("BSSID: ");
        printMacAddress(bssid);

        // print the received signal strength:
        long rssi = WiFi.RSSI();
        Serial.print("signal strength (RSSI):");
        Serial.println(rssi);

        // print the encryption type:
        byte encryption = WiFi.encryptionType();
        Serial.print("Encryption Type:");
        Serial.println(encryption, HEX);
        Serial.println();
        }

    void printMacAddress(byte mac[]) {
        for (int i = 5; i >= 0; i--) {
            if (mac[i] < 16) {
            Serial.print("0");
            }
            Serial.print(mac[i], HEX);
            if (i > 0) {
            Serial.print(":");
            }
        }
        Serial.println();
    }
    
    public:

    void startup(){
        WiFi.setPins(8,7,4,2); //in order to use the wifi module
        while (!Serial) {
            ; // wait for serial port to connect. Needed for native USB port only
        }

        // check for the presence of the shield:
        if (WiFi.status() == WL_NO_SHIELD) {
            Serial.println("WiFi shield not present");
            // don't continue:
            while (true);
        }

        // attempt to connect to WiFi network:
        while ( status != WL_CONNECTED) {
            Serial.print("Attempting to connect to WPA SSID: ");
            Serial.println(ssid);
            // Connect to WPA/WPA2 network:
            status = WiFi.begin(ssid, pass);

            // wait 10 seconds for connection:
            delay(10000);
        }

        // you're connected now, so print out the data:
        Serial.print("You're connected to the network");
        printCurrentNet();
        printWiFiData();

    }
        
    String getDataIn(){

        return "attimo";
    }
};