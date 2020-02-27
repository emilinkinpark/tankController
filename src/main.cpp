
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

#define O2_slaveID 0x0E
#define O2_slaveID_DEC 14

uint16_t Temp_Send = 0;
uint16_t DOmgl_Send = 0;
uint16_t temp_transmit = 0;
uint16_t DOmgl_transmit = 0;

int o2[13]; //O2 buffer length must have a size of 12 bytes
int incomingData[7];

void setup()
{
  //Serial.begin(9600); //TXD0 - used as serial decorder

  Serial1.begin(9600, SERIAL_8N1, 4, 2);
  /* UART1 Rx Pin = GPIO 4 and TX Pin = GPIO 2  
  Caution: Remove Pins before uploading firmware!!!!! */

  Serial2.begin(9600); /*  UART2 Rx Pin = GPIO 16 and TX Pin = GPIO 17 */
}

void loop()
{
  memset(o2, 0, sizeof(o2));                     //Empties
  memset(incomingData, 0, sizeof(incomingData)); //Empties array

  // Start Measurement
  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x25, 0x00, 0x00, 0x01);
  serial_flush_buffer(3); //Cleaning Response
  delay(2000);
  //Serial.println("Starting Measurement");

  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x26, 0x00, 0x00, 0x04);
  for (int i = 0; i <= 5; i++)
  {
    modbusRead(3, O2_slaveID_DEC, 13, o2);
    delay(100);
  }

  //Serial.println("Data Acquired");

  if (o2[0] != 14) //Slave ID Check
  {
   // Serial.println("Slave ID not matched Transmission Halt!");
    //Serial.println(o2[0], HEX);
  }
  else
  {
    float Conv_Temp = floatTOdecimal(o2[3], o2[4], o2[5], o2[6]);
    float Temp_Manipulation = Conv_Temp * 100;
    Temp_Send = Temp_Manipulation;
    

    float Conv_DOPerc = floatTOdecimal(o2[7], o2[8], o2[9], o2[10]);
    float DOmgl = domglcalc(Conv_Temp, Conv_DOPerc);
    
    float DOmgl_Manipulation = DOmgl * 1000;
    DOmgl_Send = DOmgl_Manipulation;
    

    /*
    //Serial.write("Temperature: ");
    //Serial.println(Conv_Temp);
    //Serial.println(Temp_Send);

    //Serial.write("DO Percentage: ");
    //Serial.println(Conv_DOPerc * 100);
    //Serial.write("DO mg/L: ");
    //Serial.println(DOmgl);
    //Serial.println(DOmgl_Send);
    */

  }

  // Stop Measurement
  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x2E, 0x00, 0x00, 0x01);
  serial_flush_buffer(3); //Cleaning Response
  //delay(100);
  //Serial.println("Stop Measurement");
  //Modbus Transmit to MOXA

  /* Listens to Request from MOXA
  * Matches the datalength
  * Matches the slaveID and CRC Check
  * 
  */

  temp_transmit = dec_hex16(Temp_Send);
  DOmgl_transmit = dec_hex16(DOmgl_Send);

  for (size_t i = 0; i <= 7; i++)
  {
    incomingData[i] = Serial1.read();
  }

  if (incomingData[0] == 12)
  {
    //Serial.println("Serial ID found");
    modbusSlaveTransmit(2, 0x0C, 0x03, 0x04, temp_transmit >> 8, (uint8_t)temp_transmit, DOmgl_transmit >> 8, (uint8_t)DOmgl_transmit);
  }
  else
  {
    ;;//Serial.println("Not Found");
  }
  

  //delay(1000);

} //End of Void Loop