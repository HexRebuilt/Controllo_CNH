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

#include "Defines.h"
//files that contains classes and data that are needed
#include "FilesToBeIncluded.h"


Position newPosition;
PositionControl pControl;
SerialComunication comunication;
int instruction;






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

/**
 * Function that manages the reception and setting of the string input from serial
 * and process it with the instrunction.h file to get a position 
 * */
void serial_input(){
  
  instruction = comunication.getDataIn();

  if (! (instruction == -1) ){ //means that i have recived something
    //TODO READDATAIN in a comunication file
    Serial.print("DATA RECIEVED: position "); Serial.println(instruction);
  
     //TODO adding a logic structure to the comunication

    //TODO modifying to send the control position a position and not a struct variable
    pControl.setDesiredPosition(newPosition);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

  serial_input();
  pControl.move_platform();
  
  comunication.outSerial( pControl.toStringCurrentPosition() );

  delay(500);
}
