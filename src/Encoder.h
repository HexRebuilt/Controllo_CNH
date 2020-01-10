//#include <Arduino.h>
//#include "encoder-defines.h"
//#include "Defines.h"

/**
 * NOTE: open this link before analizing the code. it's the base which is based on
 * https://www.cuidevices.com/product/resource/sample-code/amt22
 * */

class DigitalEncoder{
    public:

      /**
       * Function that maps the encoder signal into a degree rotation
       * */
      int getRotation(){
        int readvalue = (getRotationCount() ,DEC);
        int degree = map(readvalue ,0 , ENCODER_MAX_POSITIONS, ROT_MIN ,  ROT_MAX);
        return degree;
      }
      
      /*
       * The AMT22 bus allows for extended commands. The first byte is 0x00 like a normal position transfer, but the 
       * second byte is the command.  
       * This function takes the pin number of the desired device as an input
       */
      void setZeroSPI(uint8_t encoder)
      {
        spiWriteRead(AMT22_NOP, encoder, false);

        //this is the time required between bytes as specified in the datasheet.
        //We will implement that time delay here, however the arduino is not the fastest device so the delay
        //is likely inherantly there already
        delayMicroseconds(3); 
        
        spiWriteRead(AMT22_ZERO, encoder, true);
        delay(250); //250 second delay to allow the encoder to reset
      }

      /**
       *  The AMT22 bus allows for extended commands. The first byte is 0x00 like a normal position transfer, but the 
       *  second byte is the command.  
       *  This function takes the pin number of the desired device as an input
       * */
      void resetAMT22(uint8_t encoder)
      {
        spiWriteRead(AMT22_NOP, encoder, false);

        //this is the time required between bytes as specified in the datasheet.
        //We will implement that time delay here, however the arduino is not the fastest device so the delay
        //is likely inherantly there already
        delayMicroseconds(3); 
        
        spiWriteRead(AMT22_RESET, encoder, true);
        
        delay(250); //250 second delay to allow the encoder to start back up
      }

    private:
      
      /**
       * Function to get the rotation ocunting of the encoder.
       * OUTPUT: it then needs to be converted into a degree measurements
       * */
      uint16_t getRotationCount() {

        //if you want to set the zero position before beggining uncomment the following function call
        //setZeroSPI(ENC_PIN);
        
        //set attemps counter at 0 so we can try again if we get bad position    
        uint8_t attempts = 0;

        //this function gets the encoder position and returns it as a uint16_t
        //send the function either res12 or res14 for your encoders resolution
        //create a 16 bit variable to hold the encoders position
        uint16_t encoderPosition = getPositionSPI(ENC_PIN, RES12); 

        //if the position returned was 0xFFFF we know that there was an error calculating the checksum
        //make 3 attempts for position. we will pre-increment attempts because we'll use the number later and want 
        //an accurate count
        while (encoderPosition == 0xFFFF && ++attempts < 3)
        {
          encoderPosition = getPositionSPI(ENC_PIN, RES12); //try again
        }

        if (encoderPosition == 0xFFFF) //position is bad, let the user know how many times we tried
        {
          Serial.print("Encoder error. Attempts: ");
          Serial.print(attempts, DEC); //print out the number in decimal format. attempts - 1 is used since we post 
          //incremented the loop
          Serial.write(NEWLINE);
        }
        else //position was good, print to serial stream
        {
          
          Serial.print("Encoder 0: ");
          Serial.print(encoderPosition, DEC); //print the position in decimal format
          Serial.write(NEWLINE);
        }

        return encoderPosition;
      }

      /**
       * This function sets the state of the SPI line. It isn't necessary but makes the code more readable than having digitalWrite everywhere 
       * This function takes the pin number of the desired device as an input
       */
      void setCSLine (uint8_t encoder, uint8_t csLine)
      {
        digitalWrite(encoder, csLine);
      }

      /*
       * This function does the SPI transfer. sendByte is the byte to transmit. 
       * Use releaseLine to let the spiWriteRead function know if it should release
       * the chip select line after transfer.  
       * This function takes the pin number of the desired device as an input
       * The received data is returned.
       */
      uint8_t spiWriteRead(uint8_t sendByte, uint8_t encoder, uint8_t releaseLine)
      {
        //holder for the received over SPI
        uint8_t data;

        //set cs low, cs may already be low but there's no issue calling it again except for extra time
        setCSLine(encoder ,LOW);

        //There is a minimum time requirement after CS goes low before data can be clocked out of the encoder.
        //We will implement that time delay here, however the arduino is not the fastest device so the delay
        //is likely inherantly there already
        delayMicroseconds(3);

        //send the command  
        data = SPI.transfer(sendByte);
        delayMicroseconds(3); //There is also a minimum time after clocking that CS should remain asserted before we release it
        setCSLine(encoder, releaseLine); //if releaseLine is high set it high else it stays low
        
        return data;
      }

      /*
       * This function gets the absolute position from the AMT22 encoder using the SPI bus. The AMT22 position includes 2 checkbits to use
       * for position verification. Both 12-bit and 14-bit encoders transfer position via two bytes, giving 16-bits regardless of resolution.
       * For 12-bit encoders the position is left-shifted two bits, leaving the right two bits as zeros. This gives the impression that the encoder
       * is actually sending 14-bits, when it is actually sending 12-bit values, where every number is multiplied by 4. 
       * This function takes the pin number of the desired device as an input
       * This funciton expects res12 or res14 to properly format position responses.
       * Error values are returned as 0xFFFF
       */
      uint16_t getPositionSPI(uint8_t encoder, uint8_t resolution)
      {
        uint16_t currentPosition;       //16-bit response from encoder
        bool binaryArray[16];           //after receiving the position we will populate this array and use it for calculating the checksum

        //get first byte which is the high byte, shift it 8 bits. don't release line for the first byte
        currentPosition = spiWriteRead(AMT22_NOP, encoder, false) << 8;   

        //this is the time required between bytes as specified in the datasheet.
        //We will implement that time delay here, however the arduino is not the fastest device so the delay
        //is likely inherantly there already
        delayMicroseconds(3);

        //OR the low byte with the currentPosition variable. release line after second byte
        currentPosition |= spiWriteRead(AMT22_NOP, encoder, true);

        //run through the 16 bits of position and put each bit into a slot in the array so we can do the checksum calculation
        for(int i = 0; i < 16; i++) binaryArray[i] = (0x01) & (currentPosition >> (i));

          //using the equation on the datasheet we can calculate the checksums and then make sure they match what the encoder sent
        if ((binaryArray[15] == !(binaryArray[13] ^ binaryArray[11] ^ binaryArray[9] ^ binaryArray[7] ^ binaryArray[5] ^ binaryArray[3] ^ binaryArray[1]))
                && (binaryArray[14] == !(binaryArray[12] ^ binaryArray[10] ^ binaryArray[8] ^ binaryArray[6] ^ binaryArray[4] ^ binaryArray[2] ^ binaryArray[0])))
          {
            //we got back a good position, so just mask away the checkbits
            currentPosition &= 0x3FFF;
          }
        else
        {
          currentPosition = 0xFFFF; //bad position
        }

        //If the resolution is 12-bits, and wasn't 0xFFFF, then shift position, otherwise do nothing
        if ((resolution == RES12) && (currentPosition != 0xFFFF)) currentPosition = currentPosition >> 2;

        return currentPosition;
      }
};





