#include <Arduino.h>
#define NUMBER_OF_SENSORS 3
#include "UltrasonicSensors.h"

UltrasonicSensor uSensor;
void setup() {
  //Serial1.begin(19200);  //Serial1: Ultrasonic Sensor Communication Serial Port, Buadrate: 19200
  Serial.begin(9600);   //Serial: USB Serial Data output, baudrate: 19200
  delay(5000);
  uSensor.setup();

}

void loop() {
  uSensor.getSmallestDistance();
  delay(500);
}