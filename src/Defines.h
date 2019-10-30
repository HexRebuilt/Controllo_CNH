//------------------------------------------------------------------------------
 // ORGANIZATION : Kyneprox srl
 // PROJECT      : Controllo_motori
 // FILE         : DEFINES.H
 // PURPOSE      : Global simbols and constants definition
 // AUTHOR       : Simone Andreini
 //------------------------------------------------------------------------------



//cpu constant
#define CPU_HZ 48000000
#define TIMER_PRESCALER_DIV 1024
#define INT_FREQUENCY 10

//comunication
#define CHARACTER_SPLITTER '-'

//digital potentiometer type
#define MPC4131

//bit for the adc
#define PRECISION 12

//analog pins               //for the old board
#define Z_AXIS_PIN      A1  //JOY X
#define INCLINATION_PIN A2  //JOY Y
#define ROTATION_PIN    A3  //FIRE PIN

//motor pins                    //from the old board
#define Z_MOTOR_PIN   12  
#define ROTATION_MOTOR_PIN  11  
#define INCLINE_UP_MOTOR_PIN      10  //IN1 relay
#define INCLINE_DOWN_MOTOR_PIN    9   //IN2 relay


//palleto position constant
#define Z_NO_INCLINATION 500 //mm from the ground
#define Z_GROUND         50 //mm under those it will be prevented to inclinate or rotate 
#define Z_PINS           70 //mm used to connect the pins
#define Z_Switch         70 //mm


//Z axis constants
#define Z_MAXLENGHT 200 //in mm
#define Z_MINLENGHT 46   //in mm
#define Z_INVERSE_LOGIC true //if the max lenght is at 0v, minimum at 3.3v
#define Z_TOLLERANCE 5 //10mm of tollerance

//Rotation axis constants
#define ROT_MIN 1     //degrees
#define ROT_MAX 360   //degrees
#define ROT_INVERSE_LOGIC false //it increase tension with CW rotation
#define ROT_TOLLERANCE 1 //degrees

//inclination axis constant
#define INCLINATION_MIN 0 //degrees
#define INCLINATION_MAX 25 //degrees
#define INCLINATION_INVERSE_LOGIC true
#define INCLINATION_TOLLERANCE 1 //degrees

//analog sensors constant
#define WIRE_POT_K 10 //10kohm potentiometer

//realy time constant
#define REALY_INTERVAL  500 //ms




