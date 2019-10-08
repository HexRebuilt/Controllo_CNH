/**
 * file that compare the input value from serial and returns a position correpsonding with that index
 * 
 * */

#include <Arduino.h>
#include "Data_Types.h"
#include "Defines.h"

/**
 * a series of position that are going to be used during the process
 * */
class Position {
    private:
        int z_axis;
        int inclination;
        int rotation;
        String termination = "\t\n";
    
        /**
         * function that gives back an output formatted string 
         * */
        String write_Z_Height(){
            String tmp = "Z height [mm]: "; 
            tmp.concat (String(z_axis));
            tmp.concat (termination);
            return tmp;
        }

        /**
         * function that gives back an output formatted string 
         * */
        String write_rot_degree(){
            String tmp = "Rot degrees: "; 
            tmp.concat (String(rotation));
            tmp.concat (termination);
            return tmp;
        }
        
        /**
         * function that gives back an output formatted string 
         * */
        String write_inclination_degree(){
            String tmp = "Inclination degrees: "; 
            tmp.concat (String(inclination));
            tmp.concat (termination);
            return tmp;
        }
    
    public:

        int getZ(){
            return z_axis;
        }

        int getInclination(){
            return inclination;
        }

        int getRotation(){
            return rotation;
        }

        void setZ(int newZ){
            z_axis = newZ;
        }

        void setInclination(int newInclination){
            inclination = newInclination;
        }

        void setRotation(int newRotation){
            rotation = newRotation;
        }

        /**
         * function that gives back an output formatted string
         * */
        String toStringPosition(){
            String tmp = write_Z_Height();
            tmp.concat(write_inclination_degree());
            tmp.concat(write_rot_degree());
            return tmp;
        }

};



