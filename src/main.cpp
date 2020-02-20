
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

#include <modbus.cpp>



void setup(){
  Serial.begin(9600);  //TXD0 - used as serial decorder
  Serial2.begin(9600); //TXD2 - used for ModbusRTU

  
  //modbusTransmit(0x01,03,25,00,00,01);
  //(uint8_t slave_addr, function_code, uint8_t upper_starting_address, uint8_t lower_starting_address, uint8_t upper_length, uint8_t lower_length)
  
  for (size_t i = 0; i <= 2; i++)
  {
    uint8_t length = modbusTransmit(0x01,03,26,00,00,04);        // Slave_ID, Function_Code, Upper Start_Address, Lower Start_Address, 
                                                //Upper Number of registers, Lower Number of registers 
     delay(1000);
     Serial.write("length: ");
     Serial.println(length);
  }
 

}
  
void loop()
{
  //
}
