/**
 * file in charge of reading the position 
 * 
 * 
 *  not clear if i want also to control the motors with it
 * */

#include <Arduino.h>
#include "Defines.h"
#include "Data_Types.h"
#include "Motor.h"

struct T_Position position;
struct Desired_Position deisired_postition;

/**
 * I need to compensate for the sensor error while turning from 1deg to 360
 * it has a zone into which the degrees keep decreasing providing a series of 
 * wrong results.
 * still with the right logic of moovement this may not be a problem
 * */


/**
 * one of the 3 sets of function that get a position from the analog sensors and gives back the readed value
 * */
float z_reading(){
  int adc = 0;//initialize it beafore the reading
  adc = analogRead(Z_AXIS_PIN); //pin a1
  int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023
  
  if(Z_INVERSE_LOGIC){ //look in defines.h for explanation
    position.z_axis = map(adc ,0 , steps , Z_MAXLENGHT,Z_MINLENGHT );
  }
  else{
    position.z_axis = map(adc ,0 , steps ,Z_MINLENGHT, Z_MAXLENGHT);
  }
  return position.z_axis;  
}

/**
 * one of the 3 sets of function that get a rotation from the analog sensors and gives back the readed value
 * */
float rot_reading(){
  int adc = 0;//initialize it beafore the reading
  adc = analogRead(ROTATION_PIN); //pin a1
  int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023
  
  if(ROT_INVERSE_LOGIC){ //look in defines.h for explanation
    position.rotation = map(adc ,0 , steps , ROT_MAX,ROT_MIN );
  }
  else{
    position.rotation = map(adc ,0 , steps ,ROT_MIN, ROT_MAX);
  }
  return position.rotation;  
}

void read_ALL(){
  z_reading();
  rot_reading();
  //TODO adding other axis
}

/**
 * function that determine if a movement along an axis is required
 * */

boolean need_to_move(float current, float desired, float tollerance){
  float tmp = current - desired; //getting the difference
  tmp = abs(tmp); //getting the absolute difference between the 2
  //Serial.println(tmp);
  if (tmp > tollerance){
    //Serial.println("NEED TO MOVE");
    return true;
  }
  else
  {
    //Serial.println("NO NEED TO MOVE");
    return false;
  }
}

/**
 * function that sends the comand to the motor function after determining if the
 * platform needs to go up or down. if they corresponds (with a margin of error) 
 * the platform won't move
 * 
 * it uses the desired_position in order to determine the direction of movement
 * */ 

void move_platform(){
  read_ALL();

  bool z = need_to_move(position.z_axis,deisired_postition.z_axis, Z_TOLLERANCE);
  bool incline = need_to_move(position.rotation,deisired_postition.rotation,ROT_TOLLERANCE);
  bool rotation = false;
  int axis = 3;
  bool move[axis] = {z, incline, rotation}; //for cyclic check and movement

  //checking if i need to move along each axis
  for (int i = 0; i < axis; i++)
  {
    if(move[i]){ //if true i need to move

      float delta; //difference from where i am and where i need to go
      switch(i){
        case 0: //z axis
        delta = deisired_postition.z_axis - position.z_axis;
        set_z_axis(delta);
        break;
        case 1: //inclination axis
        delta = deisired_postition.inclination - position.inclination;
        set_inclination(delta);
        break;
        case 2: //z axis
        delta = deisired_postition.rotation - position.rotation;
        set_rotation(delta);
        break;
      }
    }
  }
  
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
