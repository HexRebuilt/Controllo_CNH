/**
 * file that contains the class with the logic needed for safe operations in the
 * operation space.
 * it also includes the procedure needed for changing from a position to another
 * 
 * */

#include <Arduino.h>
#include "Defines.h"
#include "Positions.h"

class SafetyController{
    public:
    //it needs to check if the position send won't violate any safety standard
    Position isReachable(Position desired){
        //if not safe return to the state 02

    }

};