/**
 * file in charge of reading and changing the position trough motor.h 
 * 
 * */

#include <Arduino.h>


class PositionControl {
  public:
    /**
     * Function that starts the safety features and set the firts startup position
     * */

    void startup(Position dataIn){
      safety.startup();
      setDesiredPosition(dataIn);
    }

    String toStringCurrentPosition(){
      String tmp = "Current position: " + current.toStringPosition()
                    +"\t-----\nDesired position: "+desired.toStringPosition();
      return tmp;
    }
    /**
     * Function that form the main gets the new desired position and sets it
     * input format: a Position variable 
     * 
     * */
    void setDesiredPosition(Position dataIn){
      
      //TODO i need to include the rest to a "safe" position before move to another one
      //only in case if i'm not at the ground level or inserting the pin blocks
      desired.setZ(dataIn.getZ());
      desired.setInclination(dataIn.getInclination());
      desired.setRotation(dataIn.getRotation());
      
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
      //--------------------------------
      //i need to ADD THE SAFETY FEATURE
      //--------------------------------
      if(safety.isSafe(desired)){

        int axis = 3;
        //checking if i need to move along each axis 
        for (int i = 0; i < axis; i++)
        {
          int delta; //difference from where i am and where i need to go
          switch(i){
            case 0: //z axis
            delta = getDifference(desired.getZ(), current.getZ(), Z_TOLLERANCE);
            moving(delta);
            motors.move_z_axis(delta);
            break;
            case 1: //inclination axis
            delta = getDifference(desired.getInclination(), current.getInclination(),INCLINATION_TOLLERANCE);
            moving(delta);
            motors.move_inclination(delta);
            break;
            case 2: //rotation axis
            delta = getDifference(desired.getRotation(), current.getRotation(), ROT_TOLLERANCE);
            moving(delta);
            motors.move_rotation(delta);
            break;
          }
        }
      }
      
      else{
        //it's not safe. i need to stop every axis
        Serial.println("It's not safe to move!");
        motors.move_inclination(0);
        motors.move_rotation(0);
        motors.move_z_axis(0);
      }
    }


  private:
    Position current, desired;
    int adc = 0;//initialize it beafore the reading and it's shared between the reading function
    int steps = (int) pow(2.0,PRECISION) -1; //number of steps depending by the bits ex: 8 = 1023 it's the same for all
    int readvalue= 0;
    Motors motors;
    SafetyController safety;

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

      return current.getInclination();  
    }

    void read_ALL(){
      z_reading();
      rot_reading();
      incline_reading();
    }

    /**
     * function that determine if a movement along an axis is required
     * 
     * INPUT: the desired position , the input difference in position and the tollerance of the axis
     * OUTPUT: an integer that, if the tollerance is respected is 0, otherwise is 
     *        the  delta value
     * */

    int getDifference(int desiredPosition, int currentPosition, int tollerance){
      int delta = abs(desiredPosition - currentPosition); //getting the absolute difference between the 2
      if (delta > tollerance){
        //Serial.println("NEED TO MOVE");
        delta = desiredPosition - currentPosition;
        return delta;
      }
      else
      {
        //Serial.println("NO NEED TO MOVE");
        return 0;
      }
    }

    /**
     * Function that tell the safety controller to turn on or off the led
     * INPUT: delta is the difference from the desired and current position, inlcuding the tollerance
     * */

    void moving(int delta){
      if (delta == 0) 
      {
        //means that the platform is not mooving
        safety.setLed(true);
      }
      else 
      {
        safety.setLed(false);
      }
      
    }

};
