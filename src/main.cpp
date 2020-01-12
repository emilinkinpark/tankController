
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

#define slaveId 5
#define startingAddress 0
#define dataLength 3


void setup(){
  Serial.begin(9600);  //TXD0 - used as serial decorder
  Serial2.begin(9600); //TXD2 - used for ModbusRTU

  modbusTransmit(slaveId, startingAddress, dataLength);
  modbusRead(buff, dataLength);
  
  float salinity = buff[6]/10.00;
  float temperature = buff[8]/10.00;
    

  Serial.write("\n");
  Serial.write("Salinity: ");
  Serial.print(salinity);
  Serial.write("‰");
  Serial.write("\n");


  Serial.write("\n");
  Serial.write("Temperture: ");
  Serial.print(temperature);
  Serial.write("°C");
  Serial.write("\n");

}
  
void loop(){
  //Do Nothing
}
