/**
 * File that's used for read/write comunication to the serial port
 * */


#include <Arduino.h>

class SerialComunication {
    public:
        /**
         * function to read from a serial port
         * if i get a "" it means that there is no input so i don't need to proceed analyzing it
         * 
         * the output will be sent to a decoder
         * */
        String getDataIn(){
            String instring = "";
                while (Serial.available() > 0) {
                    int inChar = Serial.read();
                    if (inChar != '\n') {
                        // As long as the incoming byte
                        // is not a newline,
                        // convert the incoming byte to a char
                        // and add it to the string
                        instring += (char)inChar;
                    }
                }
            return instring;
        }


        /**
         * function to output data from the serial connection
         * param: strout is the string to be displayed with the info
         * */
        void outSerial(String strout){
            Serial.println(strout);
        }

};