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

struct T_Position p0 = {Z_MINLENGHT, INCLINATION_MIN, ROT_MIN}; //level 0
struct T_Position p1 = {150,INCLINATION_MIN, 180}; //level 1 for installing blocs
struct T_Position p2 = {500,INCLINATION_MIN,ROT_MIN};
struct T_Position p3 = {500,INCLINATION_MIN,180};
struct T_Position p4 = {270, 20, ROT_MIN};
struct T_Position p5 = {270,20,180};
struct T_Position pALL[] = {p0,p1,p2,p3,p4,p5}; //for a rapid identification of the position asked
int dimension = sizeof(pALL) / sizeof(pALL[0]);



T_Position getPosition(int comand){
    if (comand <= dimension){
        return pALL[comand];
    }
    else {
        //means that i've send a wrong comand
        return p1; //it's the minimum safe position in case of the pallet is loaded
    }
}


