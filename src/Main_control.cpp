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

//file function and data that are included
#include "Defines.h"  
#include "Data_Types.h" 
#include "Position_control.h" 
#include "Serial_Comunication.h"
#include "Positions.h"
//#include "WiFi_comunication.h"

//TODO the motor output must be controllerd by position contorl
struct T_Motors Motor;
//TODO move it to a setter in position_control that will include the class position
struct T_Position toSetPosition;

Position newPosition;
PositionControl pControl;

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
  
  //instruction = getDataIn();

  if (! (instruction == -1) ){ //means that i have recived something
    //TODO READDATAIN in a comunication file
    Serial.print("DATA RECIEVED: position "); Serial.println(instruction);
  
    //using the position.h to get the position
    //toSetPosition = getcomandPosition(instruction);

    //TODO modifying to send the control position a position and not a struct variable
    pControl.setDesiredPosition(newPosition);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

  serial_input();
  pControl.move_platform();
  
  //to be replaced with a write_status();
  outSerial(pControl.toStringCurrentPosition());

  delay(500);
}
