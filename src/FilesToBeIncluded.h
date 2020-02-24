/**
 * it's a list of files that has to be included in the main program in order to 
 * work properly.
 * the order is important because it allows to reduce the ammount of "include" in
 * each class in order to save memory space.
 * */
//#include "Arduino.h"
#include "Defines.h"

#include "Timer.H"

#include "Positions.h"

//those files requires position.h
#include "UltrasonicSensors.h"
#include "Safety.h"
#include "digital_potentiometer.h"
#include "mecvel_motors.h"
#include "Motors.h"
#include "Encoder.h"
//position control uses the previous library so must be included afterwards
#include "Position_control.h"
 
//comunication libraries
#include "InstructionDecoder.h"
#include "SerialComunication.h"
#include "Secrets.h"
#include "WifiComunication.h"
#include "Comunication.h"