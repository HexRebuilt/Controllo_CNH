/**
 * file that contains the class with the logic needed for safe operations in the
 * operation space.
 * it also includes the procedure needed for changing from a position to another
 * 
 * */

#include <Arduino.h>
#include "Defines.h"

class SafetyController{
    
    public:
    //it needs to check if the position send won't violate any safety standard
    boolean isReachable(Position desired){
        
        //TODO adding the safety logic
        return true;
    }

    /**
     * Funciton that checks if i'm working with a new pallet and in case
     * ignoring some of the safety feature
     * */
    boolean isNewPallet(Position current, Position desired){
        return true;
    }

    private:
        boolean ignorePins = false;
        boolean contactSwitch = false;
        boolean areaFree = false;
        boolean buzzer = false;
        boolean light = true; //true means grean and false means red light


};