/**
 * file in charge of reading and changing the position trough motor.h 
 * 
 * */

#include <Arduino.h>
#include "Defines.h"
#include "Data_Types.h"
#include "Motor.h"
#include "Positions.h" //it contains the value of the various position
class PositionControl {
  public:
    String toStringCurrentPosition(){
      return current.toStringPosition();
    }

    void setDesiredPosition(Position dataIn){
      desired.setZ(dataIn.getZ());
      desired.setInclination(dataIn.getInlcination());
      desired.setRotation(dataIn.getRotation());
    }

  private:
    Position current, desired;
    int adc = 0;//initialize it beafore the reading and it's shared between the reading function
    int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023 it's the same for all
    int readvalue= 0;

    /**
     * one of the 3 sets of function that get a position from the analog sensors and gives back the readed value
     * */
    int z_reading(){
      adc = analogRead(Z_AXIS_PIN);

      if(Z_INVERSE_LOGIC){ //look in defines.h for explanation
        readvalue = map(adc ,0 , steps , Z_MAXLENGHT,Z_MINLENGHT );
      }
      else{
        readvalue = map(adc ,0 , steps ,Z_MINLENGHT, Z_MAXLENGHT);
      }
      current.setZ(readvalue);

      return current.getZ();  
    }

    /**
     * one of the 3 sets of function that get a rotation from the analog sensors and gives back the readed value
     * */
    int rot_reading(){
      adc = analogRead(ROTATION_PIN);

      if(ROT_INVERSE_LOGIC){ //look in defines.h for explanation
        readvalue = map(adc ,0 , steps , ROT_MAX,ROT_MIN );
      }
      else{
        readvalue = map(adc ,0 , steps ,ROT_MIN, ROT_MAX);
      }
      current.setRotation(readvalue);
      return current.getRotation();  
    }

    /**
     * one of the 3 sets of function that get an inclination from the analog sensors and gives back the readed value
     * */
    int incline_reading(){
      adc = analogRead(INCLINATION_PIN); //pin a1
      
      if(INCLINATION_INVERSE_LOGIC){ //look in defines.h for explanation
        readvalue = map(adc ,0 , steps , INCLINATION_MAX,INCLINATION_MIN );
      }
      else{
        readvalue = map(adc ,0 , steps ,INCLINATION_MIN, INCLINATION_MAX);
      }
      current.setInclination(readvalue);

      return current.getInlcination();  
    }

    void read_ALL(){
      z_reading();
      rot_reading();
      incline_reading();
    }




};



Struct T_Position position,desired_position;


/**
 * I need to compensate for the sensor error while turning from 1deg to 360
 * it has a zone into which the degrees keep decreasing providing a series of 
 * wrong results.
 * still with the right logic of moovement this may not be a problem
 * */


/**
 * one of the 3 sets of function that get a position from the analog sensors and gives back the readed value
 * */
int z_reading(){
  int adc = 0;//initialize it beafore the reading
  adc = analogRead(ROTATION_PIN); //pin a1
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
int rot_reading(){
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

/**
 * one of the 3 sets of function that get an inclination from the analog sensors and gives back the readed value
 * */
int incline_reading(){
  int adc = 0;//initialize it beafore the reading
  adc = analogRead(INCLINATION_PIN); //pin a1
  int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023
  
  if(INCLINATION_INVERSE_LOGIC){ //look in defines.h for explanation
    position.inclination = map(adc ,0 , steps , INCLINATION_MAX,INCLINATION_MIN );
  }
  else{
    position.inclination = map(adc ,0 , steps ,INCLINATION_MIN, INCLINATION_MAX);
  }
  return position.inclination;  
}

void read_ALL(){
  z_reading();
  rot_reading();
  incline_reading();
}

/**
 * function that determine if a movement along an axis is required
 * */

boolean need_to_move(int current, int desired, int tollerance){
  int tmp = current - desired; //getting the difference
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
 * 
 * 
 * TODO ADDING THE LIMIT LOGIC TO THE MOVEMENT
 * */ 

void move_platform(){
  read_ALL();

  bool z = need_to_move(position.z_axis,desired_position.z_axis, Z_TOLLERANCE);
  bool incline = need_to_move(position.rotation,desired_position.rotation,ROT_TOLLERANCE);
  bool rotation = false; //need_to_move(position.inclination,desired_position.inclination,INCLINATION_TOLLERANCE);
  int axis = 3;
  bool move[axis] = {z, incline, rotation}; //for cyclic check and movement

  //checking if i need to move along each axis
  for (int i = 0; i < axis; i++)
  {
    if(move[i]){ //if true i need to move

      int delta; //difference from where i am and where i need to go
      switch(i){
        case 0: //z axis
        delta = desired_position.z_axis - position.z_axis;
        move_z_axis(delta);
        break;
        case 1: //inclination axis
        delta = desired_position.inclination - position.inclination;
        move_inclination(delta);
        break;
        case 2: //z axis
        delta = desired_position.rotation - position.rotation;
        move_rotation(delta);
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

void set_Desired_Position(T_Position inPosition ){
  desired_position = inPosition;
  Serial.println("Position setted");

}


//TODO move to a class position


/**
 * function that gives back an output formatted string 
 * */
String write_Z_Height(int zheight){
    String tmp = "Z height: "; 
    tmp.concat (String(zheight));
    tmp.concat (" mm");
    return tmp;
}

/**
 * function that gives back an output formatted string 
 * */
String write_rot_degree(int rot){
    String tmp = "Rot degree: "; 
    tmp.concat (String(rot));
    tmp.concat ("°");
    return tmp;
}

/**
 * function that gives back an output formatted string 
 * */
String write_inclination_degree(int inclination){
    String tmp = "Inclination degree: "; 
    tmp.concat (String(inclination));
    tmp.concat ("°");
    return tmp;
}

String outPosition(){
  String tmp = write_Z_Height(position.z_axis);
  tmp.concat(write_inclination_degree(position.inclination));
  tmp.concat(write_rot_degree(position.rotation));
  return tmp;
}
