/**
 * File that provides control over the motors by modifying a digital potentiometer
 * probably it will be a mpc4131 digital potentiometer which has 129 steps
 * */

#include <Arduino.h>
#include "Defines.h" //it has information about the digital potentiometer

#ifdef MPC4131
#define STEPS 128 //it has 129 steps. one is for the 0 porition
#endif

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

void move_z_axis(int delta){
    Serial.println("Moving Z");
}

void move_inclination(int delta){
    Serial.println("Moving inclination");
}

void move_rotation(int delta){
    Serial.println("Moving rotation");
}
