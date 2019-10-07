/**
 * File that provides control over the motors by modifying a digital potentiometer
 * probably it will be a mpc4131 digital potentiometer which has 129 steps
 * */

#include <Arduino.h>
#include "Defines.h" //it has information about the digital potentiometer

#ifdef MPC4131
    #define STEPS 128 //it has 129 steps. one is for the 0 porition
#endif

class Motors{
    public:
        /**
         * Sets of 3 function in charge of moving the motor
         * */        
        void move_z_axis(int delta){
            Serial.println("Moving Z");
            setPotentiometer(Z_MOTOR_PIN, step_value(delta));
            
        }

        void move_inclination(int delta){
            Serial.println("Moving inclination");
            setPotentiometer(INCLINE_MOTOR_PIN, step_value(delta));
        }

        void move_rotation(int delta){
            Serial.println("Moving rotation");
            setPotentiometer(ROTATION_MOTOR_PIN, step_value(delta));
        }


    private:

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