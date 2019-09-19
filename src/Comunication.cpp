/**
 * used to connect to the wifi network
 * 
 * */

#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
#include "WiFi101_Util.h"

String comunicationLoop(){
  // listen for incoming clients
  WiFiClient client = server.available();
  if(client.available()) {
    //char c = client.read();//skip initial "/"
    #if(0) //use for debugging
      String command=client.readString ();
      Serial.print('"');Serial.print(command);Serial.print('"');
    #else 
      String command= client.readStringUntil('/');//Skips over "Put" to the start of the commands
      command= client.readStringUntil('/');
      if(command == "irsend") { //is this IR send command
        //processIR(client);
      } //add an else if there are other kinds of commands
    #endif
    client.stop();
  }
  delay(50);//Poll every 50ms
  return "null";
}