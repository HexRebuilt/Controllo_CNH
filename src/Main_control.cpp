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

struct T_Motors Motor;
struct T_Position toSetPosition;

int instruction;


void Data_Initialization(){
  // initialization of working data
  Motor.X_Power_Output = 0;
  Motor.Y_Power_Output = 0;
  Motor.Z_Power_Output = 0;

 //at the startup i want the platform to be in the ground
  toSetPosition.z_axis = Z_MINLENGHT;
  toSetPosition.rotation = ROT_MIN;
  toSetPosition.inclination = INCLINATION_MIN; 

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
    
}

/**
 * Function that manages the reception and setting of the string input from serial
 * and process it with the instrunction.h file to get a position 
 * */
void serial_input(){
  instruction = getDataIn();

  if (! (instruction == -1) ){ //means that i have recived something
    //TODO READDATAIN in position
    Serial.print("DATA RECIEVED: position "); Serial.println(instruction);
  
    //using the position.h to get the position
    toSetPosition = getPosition(instruction);

    //TODO ADDING THE OTHER VARIABLES
    set_Desired_Position(toSetPosition);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

  serial_input();
  move_platform();
  
  //to be replaced with a write_status();
  outSerial(outPosition());

  delay(500);
}
