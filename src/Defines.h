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

//analog pins 
#define Z_POTENTIOMETER A1//15 //A1 JOYX

//Z axis constants
#define Z_MAXLENGHT 200.0 //in mm
#define Z_MINLENGHT 46.0   //in mm
#define Z_INVERSE_LOGIC true //if the max lenght is at 0v, minimum at 3.3v
#define Z_TOLLERANCE 10.0 //10mm of tollerance

//analog sensors constant
#define WIRE_POT_K 10 //10kohm potentiometer


#endif
