
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
#include <modbus.h>
#include <modbus.cpp>
int o2[30];
uint8_t length = 0;

void setup()
{
  Serial.begin(9600);                                                 //TXD0 - used as serial decorder
  
  // Serial1.begin(9600,SERIAL_8N1,4,2);   
  /* UART1 Rx Pin = GPIO 4 and TX Pin = GPIO 2  
  Caution: Remove Pins before uploading firmware!!!!! */
   
   Serial2.begin(9600);                                              /*  UART2 Rx Pin = GPIO 16 and TX Pin = GPIO 17           */

    length = modbusTransmit(3,0x0E,03,9,00,00,07);                  // Serial Port Number, Slave_ID, Function_Code, Upper Start_Address, Lower Start_Address, 
                                                                    // Upper Number of registers, Lower Number of registers 
     delay(1000);
      Serial.write("length: ");
      Serial.println(length);
      delay(5);
  


  
  modbusRead(o2,length);
       if (o2[0] == 0x0E)
      {
          Serial.println("Slave ID matched");
          
      }
      else
      {
          Serial.println("Slave ID mismatch");
      }
  

}
  
void loop()
{
  // Serial2.write(0x01);
  // delay(1000);
}