/**
 * File that provides control over the motors by modifying a digital potentiometer
 * probably it will be a mpc4131 digital potentiometer which has 129 steps
 * */

#include <Arduino.h>
#include "Defines.h" //it has information about the digital potentiometer

#ifdef MPC4131
#define STEPS 128 //it has 129 steps. one is for the 0 porition
#endif

unsigned char step_value(float delta){
    
    unsigned char Out; // unsigned output value (0-128)
	signed char Temp;  // signed temp variable
    int half_step = STEPS / 2;
	
    // clip input data

    	Temp =- ((signed char) Data);
        
	if (Temp > half_step) //means that i can only provide the maxvalue
		Temp = half_step;
	else if (Temp < -half_step)//means that i can only move with the minumum value
		Temp = -half_step;
	// adapt from signed to unsigned data
	
    Out = half_step + Temp;

    return Out;
}

void set_z_axis(float delta){
    Serial.println("Moving Z");
}

void set_inclination(float delta){
    Serial.println("Moving inclination");
}

void set_rotation(float delta){
    Serial.println("Moving rotation");
}
