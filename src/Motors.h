/**
 * File that provides control over the motors by modifying a digital potentiometer
 * probably it will be a mpc4131 digital potentiometer which has 129 steps
 * 
 * the relay has to work with the low-com mode otherwise they won't link the pin 1&2 of the AZ2 to GND
 * */

#include <Arduino.h>
#include "Defines.h" //it has information about the digital potentiometer

#ifdef MPC4131
    #define STEPS 128 //it has 129 steps. one is for the 0 porition
#endif

class Motors{
    public:
        /**
         * function that modify the height of the platform by using 2 relays
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */       
        void move_z_axis(int delta){
            //Serial.println("Moving Z");
            setPotentiometer(Z_MOTOR_PIN, step_value(delta));
       
        }

        /**
         * function that modify the inclination of the platform
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */
        void move_inclination(int delta){
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



        /**
         * function that modify the rotation of the platform
         * 
         * INPUT: it's a variation of the position that can be <0,>0
         * */
        void move_rotation(int delta){
            //Serial.println("Moving rotation");
            setPotentiometer(ROTATION_MOTOR_PIN, step_value(delta));
        }


    private:

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

        /**
         * function that, given an input difference in position gives back a step value
         * to set the stepper
         * */
        unsigned char step_value(int data){
            unsigned char out; // unsigned output value (0-128)
            signed char temp;  // signed temp variable
            int half_step = STEPS / 2;
            
            temp =- ((signed char) data);
                
            if (temp > half_step) //means that i can only provide the maxvalue
                temp = half_step;
            else if (temp < -half_step)//means that i can only move with the minumum value
                temp = -half_step;
            // adapt from signed to unsigned data
            
            out = half_step + temp;

            return out;
        }
        /**
         * functions that sends the value to the digital potentiometer and sets it
         * the cs is the pin that controls the controller and out is the value to set
         * 
         * */
        void setPotentiometer(int cs, unsigned char out){
            // Puts low the chip select  
	        digitalWrite(cs, LOW);
	        // Send the first byte equal to zero to write the Wiper register
	        SPI.transfer(0);
	        // Send the second byte with the position of the Wiper (0-128)
	        SPI.transfer(out);
	        // Puts high the chip select
	        digitalWrite(cs, HIGH);
        }

};