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
    
        /**
         * function that gives back an output formatted string 
         * */
        String write_Z_Height(){
            String tmp = "Z height: "; 
            tmp.concat (String(z_axis));
            tmp.concat (" mm");
            return tmp;
        }

        /**
         * function that gives back an output formatted string 
         * */
        String write_rot_degree(){
            String tmp = "Rot degree: "; 
            tmp.concat (String(inclination));
            tmp.concat ("°");
            return tmp;
        }
        
        /**
         * function that gives back an output formatted string 
         * */
        String write_inclination_degree(){
            String tmp = "Inclination degree: "; 
            tmp.concat (String(inclination));
            tmp.concat ("°");
            return tmp;
        }
    
    public:

        int getZ(){
            return z_axis;
        }

        int getInlcination(){
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



//TODO removing this shit
struct T_Position p0 = {Z_MINLENGHT, INCLINATION_MIN, ROT_MIN}; //level 0
struct T_Position p1 = {150,INCLINATION_MIN, 180}; //level 1 for installing blocs
struct T_Position p2 = {500,INCLINATION_MIN,ROT_MIN};
struct T_Position p3 = {500,INCLINATION_MIN,180};
struct T_Position p4 = {270, 20, ROT_MIN};
struct T_Position p5 = {270,20,180};
struct T_Position pALL[] = {p0,p1,p2,p3,p4,p5}; //for a rapid identification of the position asked
int dimension = sizeof(pALL) / sizeof(pALL[0]);



T_Position getcomandPosition(int comand){
    if (comand <= dimension){
        return pALL[comand];
    }
    else {
        //means that i've send a wrong comand
        return p1; //it's the minimum safe position in case of the pallet is loaded
    }
}


