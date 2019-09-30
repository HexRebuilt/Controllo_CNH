//------------------------------------------------------------------------------
 // ORGANIZATION : Kyneprox srl
 // PROJECT      : Controllo_motori
 // FILE         : DEFINES.H
 // PURPOSE      : Global simbols and constants definition
 // AUTHOR       : Simone Andreini
 //------------------------------------------------------------------------------
#ifndef DEFINES_H
#define DEFINES_H

//cpu constant
#define CPU_HZ 48000000
#define TIMER_PRESCALER_DIV 1024
#define INT_FREQUENCY 10


#define PRECISION 12 //bit for the adc

//analog pins             //for the old board
#define Z_AXIS_PIN           A1//JOY X
#define INCLINATION_PIN A2//JOY Y
#define ROTATION_PIN    A3//FIRE PIN

//Z axis constants
#define Z_MAXLENGHT 200.0 //in mm
#define Z_MINLENGHT 46.0   //in mm
#define Z_INVERSE_LOGIC true //if the max lenght is at 0v, minimum at 3.3v
#define Z_TOLLERANCE 5.0 //10mm of tollerance

//Rotation axis constants
#define ROT_MIN 0.0     //degrees
#define ROT_MAX 360.0   //degrees
#define ROT_INVERSE_LOGIC false //it increase tension with CW rotation
#define ROT_TOLLERANCE 1.5 //degrees

//analog sensors constant
#define WIRE_POT_K 10 //10kohm potentiometer


#endif
