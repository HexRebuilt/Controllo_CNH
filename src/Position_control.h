/**
 * file in charge of reading and changing the position trough motor.h 
 * 
 * */

#include <Arduino.h>


class PositionControl {
  public:
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
     * 
     * 
     * TODO ADDING THE LIMIT LOGIC TO THE MOVEMENT
     * */ 

    void move_platform(){
      read_ALL();

      bool z = need_to_move(current.getZ(),desired.getZ(), Z_TOLLERANCE);
      bool incline = need_to_move(current.getRotation(),desired.getRotation(),ROT_TOLLERANCE);
      bool rotation = false; //need_to_move(current.getInclination ,desired.getInclination ,INCLINATION_TOLLERANCE);
      int axis = 3;
      bool move[axis] = {z, incline, rotation}; //for cyclic check and movement

      //checking if i need to move along each axis 
      for (int i = 0; i < axis; i++)
      {
        if(move[i]){ //if true i need to move

          int delta; //difference from where i am and where i need to go
          switch(i){
            case 0: //z axis
            delta = desired.getZ() - current.getZ();
            motors.move_z_axis(delta);
            break;
            case 1: //inclination axis
            delta = desired.getInclination() - current.getInclination();
            motors.move_inclination(delta);
            break;
            case 2: //rotation axis
            delta = desired.getRotation() - current.getRotation();
            motors.move_rotation(delta);
            break;
          }
        }
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
     * input: the current value, the desired one and the tollerance of the axis
     * output: a boolean that if true means that the platform needs to move. if false
     * doesn't need to
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


};
