//programma di test per il controllo dei motori in sincrono tramite centralina mecvel
//utilizzo anche dei potenziometri a filo per leggere i dati dal sensore
//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Main file for the motor managment (by using the Adafruit Feather M0 board)
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <string.h>
#include <SPI.h>
//#include <Wire.h>

//files that contains classes and data that are needed
#include "FilesToBeIncluded.h"


Position newPosition;
PositionControl pControl;
InstructionDecoder decoder;
SerialComunication comunication;
String instruction;






void Data_Initialization(){
  // initialization of working data
  

 //at the startup i want the platform to be in the ground
  newPosition.setZ(Z_MINLENGHT);
  newPosition.setInclination(INCLINATION_MIN);
  newPosition.setRotation(ROT_MIN);

  instruction = -1; //if -1 means that i have not recieved anything
    
};


void Hardware_Initialization(){
  //pin initialization
  pinMode(Z_AXIS_PIN,INPUT);
  pinMode(ROTATION_PIN,INPUT);
  pinMode(INCLINATION_PIN,INPUT);
  pinMode(Z_MOTOR_PIN,OUTPUT);
  pinMode(INCLINE_MOTOR_PIN,OUTPUT);
  pinMode(ROTATION_MOTOR_PIN,OUTPUT);


  //initialize i2c. Need to call only ONCE
  //Wire.begin(); // begins and sets the I2C clock at 100KHz
  //Wire.setClock(I2C_SPEED); // sets the I2C clock at 400KHz

  // initializza serial port
  Serial.begin(115200);

  // SPI initialization
  SPI.begin();
  SPISettings(20000000, MSBFIRST, SPI_MODE3);

  
}

//TODO: remove the while loop when used without the serial port attached
void setup() {
    // put your setup code here, to run once:
    analogReadResolution(PRECISION);
    Serial.begin(9600);
    Data_Initialization();
    Hardware_Initialization();
    delay(2000);

    //at the startup the platform goes to the 0 level
    pControl.setDesiredPosition(newPosition);
    
}

void reading(){
    instruction = comunication.getDataIn();
    if (!(instruction.compareTo(""))){ //means that i have read something
      newPosition = decoder.inputAnalyze(instruction);
      pControl.setDesiredPosition(newPosition);
    }
}


void loop() {
  // put your main code here, to run repeatedly:
  reading();

  pControl.move_platform();
  
  comunication.outSerial( pControl.toStringCurrentPosition() );

  delay(500);
}
