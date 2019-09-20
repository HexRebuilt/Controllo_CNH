//programma di test per il controllo dei motori in sincrono tramite centralina mecvel
//utilizzo anche dei potenziometri a filo per leggere i dati dal sensore
//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Main file for the motor managment (by using the Adafruit Feather M0 board)
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#include <Arduino.h>
//file function and data that are included
#include "Defines.h"  
#include "Data_Types.h" 
#include "Position_control.h" 
#include "WiFi_comunication.h"

struct T_Motors Motor;

void Data_Initialization(){
  // initialization of working data
  Motor.X_Power_Output = 0;
  Motor.Y_Power_Output = 0;
  Motor.Z_Power_Output = 0;
  
};

void Hardware_Initialization(){
  //pin initialization
  pinMode(Z_POTENTIOMETER,INPUT);
  
  Setup_WiFi();
}

//TODO: remove the while loop when used without the serial port attached
void setup() {
    // put your setup code here, to run once:
        //TODO: remove this loop when used without the serial port attached
    while(!Serial){
      delay(1000);
    }
    
    analogReadResolution(Z_PRECISION);

    Serial.begin(9600);
    Data_Initialization();
    Hardware_Initialization();


    Serial.println("Startup");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Z height = "); Serial.println(z_reading());
  delay(500);
}
