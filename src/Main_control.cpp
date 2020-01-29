//programma di test per il controllo dei motori in sincrono tramite centralina mecvel
//utilizzo anche dei potenziometri a filo per leggere i dati dal sensore
//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Main file for the motor managment (by using the Adafruit Feather M0 board)
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#include <string.h>
#include <SPI.h>

//files that contains classes and data that are needed
#include "FilesToBeIncluded.h"

String messageOut;
Position newPosition;
Comunication comunication;
PositionControl pControl;
Timer timer;


void Data_Initialization(){
  // initialization of working data
  

  //at the startup i want the platform to be in the ground
  newPosition.setZ(Z_MINLENGHT);
  newPosition.setInclination(INCLINATION_MIN);
  newPosition.setRotation(ROT_MIN);
  
};


void Hardware_Initialization(){
  //pin initialization
  //input pin
  pinMode(Z_AXIS_PIN,INPUT);
  pinMode(INCLINATION_PIN,INPUT);
  //output pins
  pinMode(INCLINE_UP_MOTOR_PIN,OUTPUT);
  pinMode(INCLINE_DOWN_MOTOR_PIN,OUTPUT);
  pinMode(Z_MOTOR_PIN,OUTPUT);
  pinMode(ROTATION_MOTOR_PIN,OUTPUT);
  pinMode(LED_PIN,OUTPUT);
  pinMode(ROTATION_PIN,OUTPUT);

  // SPI initialization
  SPI.begin();
  SPISettings(20000000, MSBFIRST, SPI_MODE3);

  // initializza serial port
  Serial.begin(19200);
  //Serial.begin(9600);
  

}

//TODO: remove the while loop when used without the serial port attached
void setup() {
    // put your setup code here, to run once:
    

    analogReadResolution(PRECISION);
    Data_Initialization();
    Hardware_Initialization();
    comunication.startup(newPosition);
    delay(2000);

    //at the startup the platform goes to the 0 level
    //TODO adding the check on safety pin connected in order to change the minimum height at the startup
    pControl.startup(newPosition);
    
}



void loop() {
  // put your main code here, to run repeatedly:
  
  //get the starting time
  timer.startTimer();
  
  newPosition = comunication.read();
  pControl.setDesiredPosition(newPosition);
  pControl.move_platform();
  messageOut = pControl.toStringCurrentPosition();
  comunication.write(messageOut);

  timer.timePassed();

  delay(100);
}

