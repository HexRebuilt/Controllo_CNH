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
//#include "WiFi_comunication.h"

struct T_Motors Motor;

//todo using a .h file that concatenates/separates the various data
String instruction;
float data[3]; 

void Data_Initialization(){
  // initialization of working data
  Motor.X_Power_Output = 0;
  Motor.Y_Power_Output = 0;
  Motor.Z_Power_Output = 0;

 //at the startup i want the platform to be in the ground
  deisired_postition.z_axis = Z_MINLENGHT;
  deisired_postition.rotation = 0;
  deisired_postition.inclination = 0; 
  
  //initialize the instruction to be empty
  instruction = "";
};

void Hardware_Initialization(){
  //pin initialization
  pinMode(Z_POTENTIOMETER,INPUT);
  
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
 * Function that manages the reception and setting of the input from serial
 * */
void serial_input(){
  float datain = getDataIn();
  if (datain >0){ //means that i have recived something
    //TODO READDATAIN in position
    Serial.print("DATA RECIEVED: Z desired = "); Serial.println(datain);
  
    //TODO ADDING THE OTHER VARIABLES
    data[0] = datain;
    set_Desired_Position(data);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

  serial_input();
  move_platform();
  
  //to be replaced with a write_status();
  write_Z_Height(z_reading()); //print in serial of the height


  delay(500);
}
