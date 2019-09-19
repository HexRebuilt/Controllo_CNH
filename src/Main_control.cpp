//programma di test per il controllo dei motori in sincrono tramite centralina mecvel
//utilizzo anche dei potenziometri a filo per leggere i dati dal sensore
//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Main file for the motor managment (by using the Adafruit Feather M0 board)
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <String.h>
#include "Defines.h" //file that contains all the constant used in the program 
#include "Data_Types.h"
#include "Position_control.h"


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
}

void setup() {
    // put your setup code here, to run once:
    analogReadResolution(Z_PRECISION);
    Serial.begin(9600);
    Data_Initialization();
    Hardware_Initialization();
    delay(1000);
    Serial.println("Startup");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Z height = "); Serial.println(z_reading());
  delay(500);
}
