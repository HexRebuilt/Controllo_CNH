/**
 * file in charge of reading the position 
 * 
 * 
 *  not clear if i want also to control the motors with it
 * */

#include <Arduino.h>
#include "Defines.h"
#include "Data_Types.h"

struct T_Position Position;
struct Desired_Position deisired_postition;

/**
 * function that decides if updating the value or not depending by the sensor sensibility in 
 * case of oscillations of the reading
 * current is the readed value, previous is the stored one and the tollerance is the system precision
 * */
float checkPrecision(float current, float previous, float tollerance){
  float diff = (abs) (current - previous);
  if (diff > tollerance){
    //Serial.println("updating");
     return current;
  }
  else
  {  
    //Serial.println("keeping");
    return previous;
  }
  
}

/**
 * one of the 3 sets of function that get a position from the analog sensors and gives back to the 
 * main the readed value
 * */
float z_reading(){
  int adc = 0;//initialize it beafore the reading
  adc = analogRead(Z_POTENTIOMETER); //pin a1
  int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023
  float current = 0;

  if(Z_INVERSE_LOGIC){ //look in defines.h for explanation
    current = map(adc ,0 , steps , Z_MAXLENGHT,Z_MINLENGHT );
  }
  else{
    current = map(adc ,0 , steps ,Z_MINLENGHT, Z_MAXLENGHT);
  }

  Position.z_axis = checkPrecision(current, Position.z_axis, Z_TOLLERANCE);


  return Position.z_axis;  
}


/**
 * function that sets the input from the main for the desired input
 * INPUT format: i from 0 to 2
 * 0 z height 1 inclination 2 rotation  
 * */

void set_Desired_Position(float input[]){
  //for now just the z
  deisired_postition.z_axis = input[0];
  //for now
  deisired_postition.inclination = 0;
  deisired_postition.rotation = 0;
  Serial.println("Position setted");
}
