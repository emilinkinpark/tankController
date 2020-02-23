
/* The codes are licensed under GNU LESSER GENERAL PUBLIC LICENSE
*   Copyright © 2007 Free Software Foundation, Inc. <https://fsf.org/>
*   More on the lincense at <https://www.gnu.org/licenses/lgpl-3.0.en.html>
*   Everyone is permitted to copy and distribute verbatim copies of this license document, but changing is not allowed.
*   
*   Acknowledgement: The project uses libraries used in Arduino IDE.
*    
*   The purpose of this project is to create a decentralised or independent controller for Glory Aquaculture Pvt. Ltd's Prawn Intensive Farming Project. 
*   The MODBUSRTU communication protocol is implemented according to Modbus_over_serial_line_V1_02.pdf
*   Only MODBUS Holding Register (0x03) is implemented.
*/
#include "modbus.h"
#include "modbus.cpp"
#include "conversions.cpp"

#define slaveID 0x0E


int o2[12]; //O2 buffer length must have a size of 12 bytes
//int DOPerc[9];

void setup()
{
  Serial.begin(9600); //TXD0 - used as serial decorder

  // Serial1.begin(9600,SERIAL_8N1,4,2);
  /* UART1 Rx Pin = GPIO 4 and TX Pin = GPIO 2  
  Caution: Remove Pins before uploading firmware!!!!! */

  Serial2.begin(9600); /*  UART2 Rx Pin = GPIO 16 and TX Pin = GPIO 17           */
  

}

void loop()
{
  memset(o2,0,sizeof(o2));
  //memset(Temp,0,sizeof(DOPerc));

  
  
  // Start Measurement
   modbusTransmit(3, 0x0E, 0x03, 0x25, 0x00, 0x00, 0x01);
   delay(2000);


  modbusTransmit(3, 0x0E, 0x03, 0x26, 0x00, 0x00, 0x04);
  for (int i=0; i<=10; i++)
  {
      modbusRead(0x0E,o2);
      delay(500);
  }
  

  float Conv_Temp = floatTOdecimal(o2[3],o2[4],o2[5],o2[6]);
  Serial.write("Temperature: ");
  Serial.println(Conv_Temp);

  float Conv_DOPerc = floatTOdecimal(o2[7],o2[8],o2[9],o2[10]);
  Serial.write("DO Percentage: ");
  Serial.println(Conv_DOPerc*100);


  // Stop Measurement
   modbusTransmit(3, 0x0E, 0x03, 0x2E, 0x00, 0x00, 0x01);
   delay(100);


  //Request Temp
  // modbusTransmit(3, 0x0E, 0x03, 0x08, 0x00, 0x00, 0x02);
  // modbusRead(0x0E,Temp);

  // //Request Percentage DO
  // modbusTransmit(3, 0x0E, 0x03,0x12,0x04,0x00,0x02);
  // modbusRead(0x0E,DOPerc);
  // //End of Void Loop();
  delay(1000);
}

