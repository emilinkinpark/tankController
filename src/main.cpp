
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


int Temp[9]; //O2 buffer length must have a size of 12 bytes
int DOPerc[7];

void setup()
{
  Serial.begin(9600); //TXD0 - used as serial decorder

  // Serial1.begin(9600,SERIAL_8N1,4,2);
  /* UART1 Rx Pin = GPIO 4 and TX Pin = GPIO 2  
  Caution: Remove Pins before uploading firmware!!!!! */

  Serial2.begin(9600); /*  UART2 Rx Pin = GPIO 16 and TX Pin = GPIO 17           */

  //   memset(o2, 0, sizeof(o2)); // Clears the array of old data;
}

void loop()
{

  //Start Measurement
  // modbusTransmit(3, 0x0E, 0x03, 0x25, 0x00, 0x00, 0x01);
  // delay(2000); // Wait 2 seconds

  //Request Temp
  modbusTransmit(3, 0x0E, 0x03, 0x08, 0x00, 0x00, 0x02);
  
  modbusRead(0x0E,Temp);
  
  
  
  
  
  
  
  // byte buffCount = 0;
  // char inChar = 0;
  // while (Serial2.available())
  // {
    

  //   while (inChar == 0x0E) // Matching Slave ID
  //   {
  //     inChar = Serial.read();
  //     Serial.println("Still Trying to find that bludger!");
  //   }
  //    Serial.println("Found my Slave");
  //   while (buffCount <= 8)
  //   {
  //     Serial.write("Buff Count: ");
  //     Serial.println(buffCount);
  //     inChar = Serial2.read();
  //     Serial.println(inChar, HEX);
  //     buff[buffCount] = inChar;
  //     buffCount++;
  //   }
  //     if (buffCount == 9)           // Must be one more than buffCount
  //     {
  //       Serial.println("End of Loop");
  //       break;
  //     }
  //     else
  //     {
  //       break;
  //       //Serial.println("Continuing Loop");
  //     }
    
  // }

  // float Conv_Temp = floatTOdecimal(buff[3],buff[4],buff[5],buff[6]);
  // Serial.write("Temperature: ");
  // Serial.println(Conv_Temp);

  // buff[buffCount] = '\0'; // Null terminate the string
  Serial.println("End of Main Loop");

  // for (int i=0;i<=6;i++){
  //   Serial.println(buff[i],HEX);
  // }
  // Serial.println("Printing Buffer End");

  
  delay(1000);
  // //End of Void Loop();
}

//modbusRead(Temp, 7); // Save data to Temp buffer
//Request Percentage DO
// modbusTransmit(3,0x0E,0x03,0x12,0x04,0x00,0x02);
// modbusRead(DOPerc, 8); // Save data to DOPerc buffer

//Stop Measurement
//modbusTransmit(3, 0x0E, 0x03, 0x2E, 0x00, 0x00, 0x01);

// float Conv_Temp = floatTOdecimal(Temp[3],Temp[4],Temp[5],Temp[6]);
// Serial.write("Temperature: ");
// Serial.println(Conv_Temp);

// Serial.println("Buffer Read");
// for (int i=0; i<=8;i++)
// {
//   Serial.println(Temp[i],HEX);
// }

// float Conv_DOperc = floatTOdecimal(DOPerc[3], DOPerc[4], DOPerc[5], DOPerc[6]);
// Serial.write("Percentage DO: ");
// Serial.println(Conv_DOperc);

//delay(5000);