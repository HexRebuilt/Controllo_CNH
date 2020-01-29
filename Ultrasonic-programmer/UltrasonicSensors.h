// # Author: Strictus.zhang@dfrobot.com
// # Date: 20.08.2016
// # Product Name: URM07-UART Ultrasonic Sensor
// # SKU: SEN0153
// # version number: 1.0
// # Code Description: Cascade Connection: Temperature & Distance measurement, the received data is not verified
// # Connection: Arduino LEonardo GPIO Power Supply

// # Pin RX (URM07 V1.0) -> TX1/D1 (Arduino Leonardo)
// # Pin TX (URM07 V1.0) -> RX1/D0 (Arduino Leonardo)

#include "Arduino.h"

class UltrasonicSensor{

    private:
        #define MAX_DISTANCE 750
        unsigned char i=0,j=0;
        unsigned char Rx_DATA[8]; //6 for the message, 1 for the start of the comunication and 1 for the end. tot=8
        unsigned int smallest_distance = MAX_DISTANCE; //750mm is the maximum readable    


        /**
         * Distance Measurement Package
         * it's a group of 12 bites
         * FORMAT: {0x55,0xAA,0x(Sensor_number)(Sensor_number),0x00,0x02,sum of the previous values}
         * CRC: the last field is the 1 byte checksum
         * */
        
        unsigned char CMD[NUMBER_OF_SENSORS][6]={
            {0x55,0xAA,0x11,0x00,0x02,0x00}, //first sensor
            {0x55,0xAA,0x12,0x00,0x02,0x00}, //second one
            {0x55,0xAA,0x13,0x00,0x02,0x00}, //...
            //{0x55,0xAA,0x44,0x00,0x02,0x00}, //forth one if needed
        }; 

        /**
         * Function that uses the UART protocol to read the sensors distance
         * */
        void readAllSensors() {
            for(j=0;j<NUMBER_OF_SENSORS;j++){
                    for(i=0;i<6;i++){
                        Serial1.write(CMD[j][i]);
                    }
                readDataIn();
            }
                
        }

        /**
         * Function that performs the reading from the serial1 port with uart protocol.
         * it uses the global variables given by the manifacturer for this class
         * */
        void readDataIn(){
            unsigned int distance=0;
            //Read Returned Value
            while (Serial1.available()){ 
                Rx_DATA[i]= Serial1.read();
                i++;
                //Read distance value if not overwritten will give back the previous value
                //Serial.print("DEBUG: i value while reading = ");
                //Serial.println(i);
            }
            distance=( (Rx_DATA[5]<<8) | Rx_DATA[6] ); 
                            
            if(isCheckSumOk()){
                printDistance(distance);
                analyzeDistance(distance);
                
            }
        }

        /**
         * Funciton that performs a 1 byte checksum on the reading
         * MODE: the 6th data is the checksum value. so is the one that will be compared to the one obtained
         * NOTE: the Rx_DATA contains also the 0 and 7 value in memory, so they won't be needed to be analyzed
         *          so the 6th value, but we need to discard the 0th one.
         * */
        boolean isCheckSumOk(){
            //this variable
            uint8_t check = 0;
            for (int k = 0; k < 6; k++)
            {
                //Serial.print("Debug checksum: Rx= ");
                //Serial.println(Rx_DATA[k]);
                check = check + Rx_DATA[k];
            }
            if (check == Rx_DATA[6])
            {
                return true;
            }else{
                Serial.println("Serial not right!");
                return false;
            }           
        }

        /**
         * Function that checks if the measured distance is smaller than the smallest one currently measured
         * */
        void analyzeDistance(unsigned int readed){
            if (readed < smallest_distance)
            {
                smallest_distance = readed;
            }
        }

        /**
         * function that prints out the distance measured from the module
         * */
        void printDistance(int distance){
            Serial.print("URM07-UART module["); //print distance
            Serial.print(j);
            Serial.print("]get_Dis= ");
            Serial.print(distance);
            Serial.println(" cm");
        }
        /**
        * function that calculates the cheskum for all the sending messages
        * */
        void setChecksum(){
            for(int i=0; i<NUMBER_OF_SENSORS;i++){
                for (int j = 0; j < 6; j++)
                {
                    CMD[i][6]=CMD[i][6]+CMD[i][j];
                }
            }
        }    
    public:
        void setup() {
            Serial1.begin(19200); //Serial1: Ultrasonice Sensors Serial Communication Port, baudrate: 19200
            //Serial.begin(19200); //Serial: USB Serial Monitor already present in the main code
            //Setting the cheksum for the sending message
            setChecksum();
        }

        /**
         * Function that returns the smallest distance measured from all the sensors
         * */
        int getSmallestDistance(){
            //the smallest distance has to be reset to the max measureable in order to get the updated minimum
            smallest_distance = MAX_DISTANCE;
            readAllSensors();
            return smallest_distance;
        }
        

};