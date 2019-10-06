/**
 * File that's needed in order to transform the input string as a comand to a
 * position that has to be returned after a decoding
 * */

#include <Arduino.h>

class InstructionDecoder{
    public:

        /**
         * function that checks the string in input and decodes it. 
         * STRING FORMAT: zValue[mm]-inclineValue[deg]-rotValue[deg]
         * */
        Position inputAnalyze(String instruction){
            Serial.print("DATA RECIEVED: position "); Serial.println(instruction);
            size_t inputLenght = sizeof(instruction) / sizeof (instruction[0]);
            int comandRead = 0; //indicates which position has to be set
            String analyzed = "";
            
            for (int i=0; i <inputLenght; i++){
                char current = instruction.charAt(i);
                if ( current == '-' ) //means that i have found a delimiter character
                {
                    Serial.println("analyzing the portion of the string");
                    int newValue = analyzed.toInt();
                    setPosition(comandRead,newValue);
                    
                    comandRead++;
                    analyzed = "";
                }
                else{
                    analyzed += (char)current; //i'm adding the value to the string to be anlyzed
                }
            }
            return newPosition;
        }
        
    private:
    Position newPosition;
    /**
     * function that given the ammount of comand analyzed sets the corrisponding value
     * in the newPosition.
     * INPUT FORMAT: zValue[mm]-inclineValue[deg]-rotValue[deg]
     * */
    void setPosition(int comandRead, int newValue){
        switch (comandRead)
        {
        case 0:
            //i'm reading the z
            newPosition.setZ(newValue);
            break;
        case 1:
            //i'm reading the inclination
            newPosition.setInclination(newValue);
            break;
        case 2:
            //i'm reading the rotation
            newPosition.setRotation(newValue);
            break;

        default:
            Serial.println("Error during the decodification of the string!");
            break;
        }
    }
    

};
