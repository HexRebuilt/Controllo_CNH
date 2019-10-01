/**
 * File that's used for read/write comunication to the serial port
 * */


#include <Arduino.h>


/**
 * function to read from a serial port
 * if i get a -1 it means that there is no input so i don't need to proceed analyzing it
 * 
 * TODO using a binary condification for sending the messagges. for now it just works but for adding more steps it's necessary to add those
 * */

int getDataIn(){
   int value = -1;
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
    
    if(!instring.equals("")){ //if i have read somwthing
        value = instring.toInt();
        instring = "";
    }
  return value;
}


/**
 * function to output data from the serial connection
 * param: strout is the string to be displayed with the info
 * */
void outSerial(String strout){
    Serial.println(strout);
}

/**
 * function that gives back an output formatted string 
 * */
String write_Z_Height(float zheight){
    String tmp = "Z height: "; 
    tmp.concat (String(zheight));
    tmp.concat (" mm");

    //for now 
    outSerial(tmp);
    
    return tmp;
}

/**
 * function that gives back an output formatted string 
 * */
String write_rot_degree(float rot){
    String tmp = "Rot degree: "; 
    tmp.concat (String(rot));
    tmp.concat ("°");

    //for now 
    outSerial(tmp);
    
    return tmp;
}


