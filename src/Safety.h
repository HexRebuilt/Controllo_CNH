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

    /**
     * function that is used just one time to set the safe positions. 
     * the ground one, the one that is used to connect the pins and the 
     * switches, the one that prevents inclination and rotation
     * 
     * */
    void startup(){
        ground.setZ(Z_GROUND);
        ground.setRotation(0);
        ground.setInclination(0);

        
        connectPins.setZ(Z_PINS);
        connectPins.setRotation(0);
        connectPins.setInclination(0);

        
        switches.setZ(Z_GROUND);
        switches.setRotation(180);
        switches.setInclination(0);


    }


    private:
        boolean newPallet = true;
        boolean ignorePins = false;
        boolean contactSwitch = false;
        boolean areaFree = false;
        boolean lights = true; //true means grean and false means red light
        Position ground, connectPins, switches;
         


        //it needs to check if the position send won't violate any safety standard
        boolean isReachable(Position desired){
            
            //TODO adding the safety logic
            return true;
        }

        /**
         * Funciton that checks if i'm working with a new pallet and in case
         * ignoring some of the safety feature
         * 
         * INPUT: is the desired position. if it is the first position that is used 
         *          to connect the pallet to the platform, it's safe to ignore some pins
         * OUTPUT: is a boolean value that say if the platform can ingnore some safety 
         *         functions
         * 
         * */
        boolean isNewPallet(Position desired){
            //means that i have a new pallet
            if(isSamePosition(desired,ground) && newPallet == true){
                newPallet = false;
                return true;
            }

            //means that i've completed the operations and coming back down to the gound
            if(isSamePosition(desired,ground) && newPallet == false){
                newPallet = true;
                return false;
            }

            //means that's not a new pallet
            if(newPallet == false){
                return false;
            }
        }

        /**
         * Function that check if the two positions are the same
         * INPUT: the desired position and the one that needs to be checked
         * OUTPUT: a boolean value that says if the two position are the same
         * */
        boolean isSamePosition(Position desired, Position checked){
            if(desired.getInclination() == checked.getInclination())
            {
                if (desired.getRotation() == checked.getRotation())
                {
                    if (desired.getZ() == checked.getZ())
                    {
                        return true;
                    }
                    
                    
                }
            }
            else
            {
                return false;
            }
               
        }
};