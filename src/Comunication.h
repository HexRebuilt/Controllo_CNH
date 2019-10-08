/**
 * file that manages ALL the comuncations. wifi, bt and trough serial port
 * and returns to the main program the position readed, that need to be anlyzed.
 * */

#include <Arduino.h>

class Comunication{
    
    private:
        Position displayed,readed;
        String instruction;
        InstructionDecoder decoder;
        SerialComunication serialPort; 
        WiFiComunication wifiComunication;
     
    public:

    void write(String messageOut){
        if(Serial.available()){
            Serial.println(messageOut);
        }
        wifiComunication.writeHTML(messageOut);
    }

    Position read(){
        
        instruction = wifiComunication.getDataIn();
        //the serial port is more important then wifi so overwrites its comand
        if(Serial.available() && instruction.compareTo("") ){
            instruction = serialPort.getDataIn();
            //instruction.concat("-");//to solve a bug
        }
        if ((instruction.compareTo(""))){ //means that i have read something
            readed = decoder.inputAnalyze(instruction);
            instruction = "";
            Serial.print("New Position: ");
            Serial.println(readed.toStringPosition());
            }
        
        return readed;
    }   

    void startup(Position initialPosition){
        readed = initialPosition;
        Serial.begin(19200);
        wifiComunication.startup();
    }             
};
