class UltrasonicSensor{
  private:
    unsigned char i=0,j=0;
    unsigned int  readed_distance=0,smallest_distance= MAX_DISTANCE ;
    unsigned char Rx_DATA[8];
        /**
         * Distance Measurement Package
         * it's a group of 12 bites
         * FORMAT: {0x55,0xAA,0x(Sensor_address),0x00,0x02,sum of the previous values}
         * CRC: the last field is the 1 byte checksum
         * */
    unsigned char CMD[NUMBER_OF_SENSORS][6]={
                         {0x55,0xAA,0x11,0x00,0x02,0x12},
                         {0x55,0xAA,0x12,0x00,0x02,0x13},
                         {0x55,0xAA,0x13,0x00,0x02,0x14},
                         //{0x55,0xAA,0x44,0x00,0x02,0x45},
                          }; //Distance Measurement Package

  /**
   * Funciton that performs a 1 byte checksum on the reading
   * MODE: the 6th data is the checksum value. so is the one that will be compared to the one obtained
   * NOTE: the Rx_DATA contains also the 0 and 7 value in memory, so they won't be needed to be analyzed
   *          so the 6th value, but we need to discard the 0th one.
   * */
    boolean isCheckSumOk(){
        //this variable
        byte check = 0x00;
        for (int k = 0; k < 6; k++)
        {   Serial.print(Rx_DATA[k],HEX);
            check = check ^ Rx_DATA[k];
        }
        //check = check % 256;
        Serial.println("\nCheck: ");
        Serial.println(check,HEX);
        if (check == Rx_DATA[8])
        {
            return true;
        }else{
            Serial.println("Checksum not correct!");
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

  public:
    void setup() {
      Serial1.begin(256000);  //Serial1: Ultrasonice Sensors Serial Communication Port, baudrate: 19200
      Serial.begin(9600);   //Serial: USB Serial Monitor
    }

    /**
     * Function that's used to read all the sensors
     * */
    void readSensors(){
        
        for(j=0;j<NUMBER_OF_SENSORS;j++){
          for(i=0;i<6;i++){
            Serial1.write(CMD[j][i]);
          }

        delay(ULTRASONIC_DELAY);  //Wait returned result
        
        i=0;
        byte checksum = 0x00;
        while (Serial1.available()){  //Read Returned Value (This demo is only for reference, no data verification)
          Rx_DATA[i]=(Serial1.read());
          if (i != 0){
            checksum = checksum + Rx_DATA[i-1];
          }

          i++;
        }

        if (checksum == Rx_DATA[i-1]) //it means that the transmission is correct
        {
          //Serial.println("checksum ok");
          readed_distance=((Rx_DATA[5]<<8)|Rx_DATA[6]); //Read distance value
        /*
        Serial.print("URM07-UART module[");   //print distance
        Serial.print(j);
        Serial.print("]get_Dis= ");
        Serial.print(readed_distance);
        Serial.println("cm");
        */
        analyzeDistance(readed_distance);
        }

        else
        {
          Serial.println("Error with the check sum");
        }

      }
    }

    /**
     * Function that returns the smallest distance measured from all the sensors
     * */
    int getSmallestDistance(){
        //the smallest distance has to be reset to the max measureable in order to get the updated minimum
        smallest_distance = MAX_DISTANCE;
        readSensors();
        return smallest_distance;
    }

};