/**
 * it's a list of files that has to be included in the main program in order to 
 * work properly.
 * the order is important because it allows to reduce the ammount of "include" in
 * each class in order to save memory space.
 * */
#include "Defines.h"
#include "Positions.h"

#include "InstructionDecoder.h"
#include "SerialComunication.h"
#include "Secrets.h"
#include "WifiComunication.h"
#include "Comunication.h"
//those files requires position.h

#include "Safety.h"
#include "Motors.h"
//position control uses the previous library so must be included afterwards
#include "Position_control.h" 
