/**
 * File that provides control over the motors by modifying a digital potentiometer
 * probably it will be a mpc4131 digital potentiometer which has 129 steps
 * 
 * the relay has to work with the low-com mode otherwise they won't link the pin 1&2 of the AZ2 to GND
 * */

//#include <Arduino.h>
//#include "Defines.h" //it has information about the digital potentiometer
//#include "MPC4131.h" 


class Motors{
    private:
        digitalPotentiometer rot_pot, z_pot, inlcine_pot;
        mecvel_motors inclination;


        /**
         * Function used to change the state of one relay module
         * 
         * INPUT: is the pinNo. of the relay
         * */
        void relayHighToLow(int pin){
                digitalWrite(pin, HIGH);
                delay(REALY_INTERVAL);
                digitalWrite(pin,LOW);
        }
        
        /**
         * Function used to change the state of one relay module
         * 
         * INPUT: is the pinNo. of the relay
         * */
        void relayLowToHigh(int pin){
                digitalWrite(pin, LOW);
                delay(REALY_INTERVAL);
                digitalWrite(pin,HIGH);
        }

    
    public:
        /**
         * function that modify the height of the platform by using 2 relays
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */       
        void move_z_axis(int delta){
            //Serial.println("Moving Z");
            z_pot.setPotentiometer(Z_MOTOR_PIN, delta);
       
        }

        /**
         * function that modify the inclination of the platform
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */
        void move_inclination(int delta){
            inclination.setPins(delta);
            //incline_pot.setPotentiometer(INCLINATION_MOTOR_PIN, delta);
        }

        /**
         * function that modify the rotation of the platform
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */
        void move_rotation(int delta){
            //Serial.println("Moving rotation");
            rot_pot.setPotentiometer(ROTATION_MOTOR_PIN, delta);
        }
};