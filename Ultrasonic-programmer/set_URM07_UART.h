
// # Author: Strictus.zhang@dfrobot.com
// # Date: 20.08.2016
// # Product Name: URM07-UART Ultrasonic Sensor
// # SKU: SEN0153
// # version number: 1.0
// # Code Description: 20-750cm distance measurement, the received data is not verified

// # Connection: Arduino LEonardo GPIO Power Supply
// # Pin VCC (URM07 V1.0) -> D3     (Arduino Leonardo)
// # Pin GND (URM07 V1.0) -> D2     (Arduino Leonardo)
// # Pin  RX (URM07 V1.0) -> TX1/D1 (Arduino Leonardo)
// # Pin  TX (URM07 V1.0) -> RX1/D0 (Arduino Leonardo)

#define set_addr 0x11

#define header_H    0x55 //Header
#define header_L    0xAA //Header
#define device_Addr set_addr //Address
#define data_Length 0x00 //Data length
#define get_Dis_CMD 0x02 //Command: Read Distance
#define checksum    (unsigned char)  (header_H+header_L+device_Addr+data_Length+get_Dis_CMD) //Checksum

#define set_header_H    0x55 //Header
#define set_header_L    0xAA //Header
#define set_device_Addr 0xAB //Address
#define set_data_Length 0x01 //Data length
#define set_get_Dis_CMD 0x55 //Command: Read Distance
#define set_new_Address set_addr
#define set_checksum    (unsigned char) (set_header_H+set_header_L+set_device_Addr+set_data_Length+set_get_Dis_CMD+ set_new_Address) //Checksum


#define temp_header_H     0x55 //Header
#define temp_header_L     0xAA //Header
#define temp_data_Length  0x00 //Data length
#define temp_get_Temp_CMD 0x03 //Command: Read Temperature
#define temp_checksum    (unsigned char) (temp_header_H+temp_header_L+device_Addr+temp_data_Length+temp_get_Temp_CMD) //check sum


int  temperature=0;
unsigned char temp_CMD[6]={temp_header_H,temp_header_L,device_Addr,temp_data_Length,temp_get_Temp_CMD,temp_checksum}; //Temperature Command package



unsigned char i=0;
unsigned int  Distance=0;
unsigned char Rx_DATA[8];
unsigned char CMD[6]={
  header_H,header_L,device_Addr,data_Length,get_Dis_CMD,checksum}; //Distance command package

unsigned char SetCMD[7]={
  set_header_H,set_header_L,set_device_Addr,set_data_Length,set_get_Dis_CMD,set_new_Address,set_checksum}; //Distance command package

void setup() {
  Serial1.begin(19200);  //Serial1: Ultrasonic Sensor Communication Serial Port, Buadrate: 19200
  Serial.begin(9600);   //Serial: USB Serial Data output, baudrate: 19200
  delay(5000);
  Serial.println("Setting address");
  delay(5000);
  for(i=0;i<7;i++){
    Serial.print("Sending: ");
    Serial.println(SetCMD[i]);
    Serial1.write(SetCMD[i]);
  }
}

void loop() {
  for(i=0;i<6;i++){
    Serial1.write(CMD[i]);
    //Serial.print("Sending ");
    //Serial.println(CMD[i]);
  }
  delay(150);  //Wait for the result
  i=0;
  while (Serial1.available()){  //Read the return data (Note: this demo is only for the reference, no data verification)
    Rx_DATA[i]=(Serial1.read());
    //Serial.println(Rx_DATA[i]);
    i++;
  }
  Distance=((Rx_DATA[5]<<8)|Rx_DATA[6]); //Read the distance value
  Serial.print(Distance);               //print distance value
  Serial.println("cm");
  delay(1000);




   for(i=0;i<6;i++){
    Serial1.write(temp_CMD[i]);
    }
 delay(50);  //Wait Data Return
 i=0;
 while (Serial1.available()){  //Read returned Data (Note: Demo is just for Reference , no data verification)
    Rx_DATA[i]=(Serial1.read());
    i++;
    }
 temperature=((Rx_DATA[5]<<8)|Rx_DATA[6]);  //Read temperature Value (10 times)
 Serial.print(temperature/10);             //Print Temperature
 Serial.print('.');
 Serial.print(temperature%10);
 Serial.println("C");
}