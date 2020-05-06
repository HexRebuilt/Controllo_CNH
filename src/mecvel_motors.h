#include "Arduino.h"
#include "Defines.h"

class mecvel_motors
{
private:
    /* data */
public:
    /**
     * function that modify the inclination of the platform
     * 
     * INPUT: it's a variation of the position that can be <0,>0
     * */
    void setPins(int delta){
        // Serial.println(delta);
        //Serial.println("Moving inclination");
        if (delta >0){ //i have to increase the inclination
            Serial.println("Increasing inclination");
            digitalWrite(INCLINE_DOWN_MOTOR_PIN,HIGH);
            digitalWrite(INCLINE_UP_MOTOR_PIN, LOW);
        }
        //this section is used in order to stop the platform after reaching the set point
        if (delta == 0){
            Serial.println("Inclination reached");
            digitalWrite(INCLINE_UP_MOTOR_PIN, HIGH);
            digitalWrite(INCLINE_DOWN_MOTOR_PIN,HIGH);
        }            
        else{ //i have to reduce the inclination
            Serial.println("Reducing inclination");
            digitalWrite(INCLINE_UP_MOTOR_PIN, HIGH);
            digitalWrite(INCLINE_DOWN_MOTOR_PIN,LOW);
        }   
    }
};
