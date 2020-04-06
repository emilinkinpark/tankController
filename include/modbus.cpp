/* Dependent Headers */
#include <Arduino.h>

/* Dependent Variables */

//char buff[20]; //Stores Serial Read Data
/* Table of CRC values for top-order byte */
static const uint8_t table_crc_hi[] =
    {
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};

/* Table of CRC values for low-order byte */
static const uint8_t table_crc_lo[] =
    {
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
        0x43, 0x83, 0x41, 0x81, 0x80, 0x40};

static uint16_t crc16(uint8_t *buffer, uint16_t buffer_length)
{
  uint8_t crc_hi = 0xFF; /* high CRC byte initialized */
  uint8_t crc_lo = 0xFF; /* low CRC byte initialized */
  unsigned int i;        /* will index into CRC lookup */

  /* pass through message buffer */
  while (buffer_length--)
  {
    i = crc_hi ^ *buffer++; /* calculate the CRC  */
    crc_hi = crc_lo ^ table_crc_hi[i];
    crc_lo = table_crc_lo[i];
  }

  // /*Debugging */
  // Serial.write("CRC_High: ");
  // Serial.println(crc_hi, HEX);
  // Serial.write("CRC_LO: ");
  // Serial.println(crc_lo, HEX);
  // /*Debugging End*/

  return (crc_hi << 8 | crc_lo);
}

void serial_flush_buffer(uint8_t serialportnumber)
{
  switch (serialportnumber)
  {
  case 1:
    while (Serial.read() >= 0)
    {
      ; // do
    }

  case 2:
    while (Serial1.read() >= 0)
    {
      ; // do
    }
  case 3:
    while (Serial2.read() >= 0)
    {
      ; // do
    }
  }
}

void modbusMasterTransmit(uint8_t const serialportnumber, uint8_t slave_addr, uint8_t funccode, uint8_t upper_starting_address, uint8_t lower_starting_address, uint8_t upper_length, uint8_t lower_length) // Modbus Transmit Function
{
  /*  Working Process
   *  Define the serial port number to define the serial port like 1 - Serial, 2 - Serial1 and 3 - Serial2 
   *  Takes the slave address, starting address and datalength, and stores it into data_stream.
   *  Generates CRC
   *  Takes in the serial buffer from data_stream and transfer to slave over Serial2(ESP32 UART2)
   *  CRC transmitted
   */

  //    0               1                                2                                    3                                 4                       5
  //uint8_t data_stream[] = {slave_addr, hex[funccode], hex[upper_starting_address], hex[lower_starting_address], hex[upper_length], hex[lower_length]};
  uint8_t data_stream[] = {slave_addr, funccode, upper_starting_address, lower_starting_address, upper_length, lower_length};

  //  01                03                               25                                   00                                00                      01

  delay(200);                           // delay stop mixing up sent data during flash
  uint16_t CRC = crc16(data_stream, 6); //Generating CRC //Length Must be 6
  // Serial.println("Transmitting Start"); //Debugging

  switch (serialportnumber)
  {
  case 1: // Serial //Programming Port, use it with care
          //Serial.println("Case 1");
    for (int i = 0; i <= 5; i++)
    {
      Serial.write(data_stream[i]); //Sending out the data
      //delay(50);
      //Serial.println(data_stream[i], HEX);
    }

    Serial.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    Serial.write(CRC);      //Sending Lower CRC bits
    break;
    //End of Case 1
    break;

  case 2: //Serial1
    //       //Serial.println("Case 2");
    // for (int i = 0; i <= 7; i++)
    // {
    //   Serial1.write(data_stream[i]); //Sending out the data
    //   //delay(50);
    //   Serial.write("Data: ");
    //   Serial.println(i);
    //   Serial.println(data_stream[i], HEX);
    // }
    // //CRC_LOW = CRC;
    // //Serial1.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    // //Serial.println(CRC>>8,HEX);
    // //Serial1.write(CRC_LOW);      //Sending Lower CRC bits

    // //Serial.println(CRC_LOW,HEX);
    // break;
    //End of Case 2
  case 3: //Serial2
    //Serial.println("Case 3");
    for (int i = 0; i <= 5; i++)
    {
      Serial2.write(data_stream[i]); //Sending out the data
      //delay(50);
     // Serial.println(data_stream[i], HEX);
    }
    Serial2.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    Serial2.write(CRC);      //Sending Lower CRC bits
    break;
    //End of Case 3

  default:
    Serial.println("Case Not reached");
    break;

    //End of Switch
  }

  // /* CRC Debugging Start */
  // Serial.println(CRC, HEX);
  // Serial.println("Transmitting End");
  // /* CRC Debugging End*/
}

void modbusSlaveTransmit(uint8_t const serialportnumber, uint8_t slave_addr, uint8_t funccode, uint8_t no_of_bytes, uint8_t data_1, uint8_t data_2, uint8_t data_3, uint8_t data_4) // Modbus Transmit Function
{
  /*  Working Process
   *  Define the serial port number to define the serial port like 1 - Serial, 2 - Serial1 and 3 - Serial2 
   *  Takes the slave address, starting address and datalength, and stores it into data_stream.
   *  Generates CRC
   *  Takes in the serial buffer from data_stream and transfer to slave over Serial2(ESP32 UART2)
   *  CRC transmitted
   */

  //    0               1                                2                                    3                                 4                       5
  //uint8_t data_stream[] = {slave_addr, hex[funccode], hex[upper_starting_address], hex[lower_starting_address], hex[upper_length], hex[lower_length]};
  uint8_t data_stream[] = {slave_addr, funccode, no_of_bytes, data_1, data_2, data_3, data_4};

  //  01                03                               25                                   00                                00                      01

  delay(200);                           // delay stop mixing up sent data during flash
  uint16_t CRC = crc16(data_stream, 7); //Generating CRC //Length Must be 6
  // uint8_t CRC_HIGH = (CRC>>8);
  // uint8_t CRC_LOW = CRC;
  // uint8_t data_stream[] = {slave_addr, funccode,  no_of_bytes,  data_1,  data_2,CRC_HIGH,CRC_LOW};
  // Serial.println("Transmitting Start"); //Debugging

  switch (serialportnumber)
  {
  case 1: // Serial //Programming Port, use it with care
          //Serial.println("Case 1");
    for (int i = 0; i <= 6; i++)
    {
      Serial.write(data_stream[i]); //Sending out the data
      //delay(50);
      // Serial.write("Data: "); Serial.println(i);
      Serial.println(data_stream[i], HEX);
    }
    Serial.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    Serial.write(CRC);      //Sending Lower CRC bits

    // Serial.println(CRC>>8);
    //Serial.println((uint8_t)CRC);

    //CRC_LOW = CRC;
    //Serial1.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    //Serial.println(CRC>>8,HEX);
    //Serial1.write(CRC_LOW);      //Sending Lower CRC bits

    //Serial.println(CRC_LOW,HEX);
    break;
    //End of Case 1

  case 2: //Serial1
          //Serial.println("Case 2");
    for (int i = 0; i <= 6; i++)
    {
      Serial1.write(data_stream[i]); //Sending out the data
      //delay(50);
      // Serial.write("Data: "); Serial.println(i); Serial.println(data_stream[i], HEX);
    }
    Serial1.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    Serial1.write(CRC);      //Sending Lower CRC bits

    // Serial.println(CRC>>8);
    //Serial.println((uint8_t)CRC);

    //CRC_LOW = CRC;
    //Serial1.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    //Serial.println(CRC>>8,HEX);
    //Serial1.write(CRC_LOW);      //Sending Lower CRC bits

    //Serial.println(CRC_LOW,HEX);
    break;
    //End of Case 2
  case 3: //Serial2
    //Serial.println("Case 3");
    for (int i = 0; i <= 6; i++)
    {
      Serial2.write(data_stream[i]); //Sending out the data
      //delay(50);
      // Serial.write("Data: "); Serial.println(i);  Serial.println(data_stream[i], HEX);
        }
    Serial2.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    Serial2.write(CRC);      //Sending Lower CRC bits

    //Serial.println(CRC>>8);
    //Serial.println((uint8_t)CRC);

    //CRC_LOW = CRC;
    //Serial1.write(CRC >> 8); //Sending Upper CRC bits i.e High bits
    //Serial.println(CRC>>8,HEX);
    //Serial1.write(CRC_LOW);      //Sending Lower CRC bits

    //Serial.println(CRC_LOW,HEX);
    break;
    //End of Case 3

  default:
    Serial.println("Case Not reached");
    break;

    //End of Switch
  }

  // /* CRC Debugging Start */
  // Serial.println(CRC, HEX);
  // Serial.println("Transmitting End");
  // /* CRC Debugging End*/
  //return lower_length;
}

void modbusRead(uint8_t serialportnumber, char SlaveID, int datalength, int *buff)
{
  /* Working Process:
   * Define the serial port number to define the serial port like 1 - Serial, 2 - Serial1 and 3 - Serial2 
   * Waits for the serial buffer to be full
   * Reads each data and stores it into a buffer array until the Counter meets it's condition
   * The buffer array ignores Null string
  */

  char inChar = 0;
  byte buffCount = 0;
  // byte loopcounter = 0;
  //uint8_t datalength = temp_length;

  /* Debugging Start */
  //Serial.println("Serial Read start");
  //Serial.println(Serial2.available());
  /* Debugging End */
  switch (serialportnumber)
  {
  case 1: //Serial1 //Caution Programming Port, Do not use for loop purposes.
          //Serial.println("Case 1");

    while (Serial.available())
    {
      while (buffCount <= datalength)
      {
        inChar = Serial.read();
        // Serial.write("Buff Count: "); Serial.println(buffCount); Serial.println(inChar, HEX); //Debugging buffCount and Read Data
        buff[buffCount] = inChar;

        if (buff[0] != SlaveID) // If SlaveID not Matched; set buffCount = 0; and keep looping
        {
          //Serial.println("Salve ID Not Matched");
          //Serial.println(buff[0],HEX);
          buffCount = 0;
          //break;
        }
        else
        {
          //Serial.println("Salve ID Found");
          //Serial.println(buff[0],HEX);
          buffCount++;
        }
      }

      if (buffCount == datalength) //Break if Datalength Reached
      {
        //Serial.println("End of Loop");
        break;
      }
      else
      {
        continue;
        //Serial.println("Continuing Loop");
      }
      //Serial.println("End of Loop");    //Debugging
    }
    //Serial.println("Read Complete");    //Debugging
    break;
    //End of Case 1

  case 2: //Serial1
    //Serial.println("Case 2");
    while (Serial1.available())
    {
      while (buffCount <= datalength)
      {
        inChar = Serial1.read();
        Serial.write("Buff Count: "); Serial.println(buffCount); Serial.println(inChar, HEX); //Debugging buffCount and Read Data
        buff[buffCount] = inChar;

        if (buff[0] != SlaveID) // If SlaveID not Matched; set buffCount = 0; and keep looping
        {
          //Serial.println("Salve ID Not Matched");
          //Serial.println(buff[0],HEX);
          buffCount = 0;
          //break;
        }
        else
        {
          //Serial.println("Salve ID Found");
          //Serial.println(buff[0],HEX);
          buffCount++;
        }
      }

      if (buffCount == datalength) //Break if Datalength Reached
      {
        //Serial.println("End of Loop");
        break;
      }
      else
      {
        continue;
        //Serial.println("Continuing Loop");
      }
      //Serial.println("End of Loop");    //Debugging
    }
    //Serial.println("Read Complete");    //Debugging
    break;
    //End of Case 2

  case 3: //Serial2
    //Serial.println("Case 3");

    while (Serial2.available())
    {
      while (buffCount <= datalength)
      {
        inChar = Serial2.read();
        //Serial.write("Buff Count: "); Serial.println(buffCount); Serial.println(inChar, HEX); //Debugging buffCount and Read Data
        buff[buffCount] = inChar;

        if (buff[0] != SlaveID) // If SlaveID not Matched; set buffCount = 0; and keep looping
        {
          //Serial.println("Salve ID Not Matched");
          //Serial.println(buff[0],HEX);
          buffCount = 0;
          //break;
        }
        else
        {
          //Serial.println("Salve ID Found");
          //Serial.println(buff[0],HEX);
          buffCount++;
        }
      }

      if (buffCount == datalength) //Break if Datalength Reached
      {
        serial_flush_buffer(2);
        break;
      }
      else
      {
        continue;
        //Serial.println("Continuing Loop");
      }
      //Serial.println("End of Loop");    //Debugging
    }
    //Serial.println("Read Complete");    //Debugging
    break;
    //End of Switch
  }
  
}

void modbus_slave()
{
  // //Modbus Transmit to MOXA

  // /* Listens to Request from MOXA
  // * Matches the datalength
  // * Matches the slaveID
  // *
  // */

  // temp_transmit = dec_hex16(Temp_Send);
  // DOmgl_transmit = dec_hex16(DOmgl_Send);
  // //Modbus Master End
  
  // //Modbus Slave Start
  // for (size_t i = 0; i <= 7; i++)
  // {
  //   incomingData[i] = Serial1.read();
  // }

  // if (incomingData[0] == 12)        //Matches Slave ID to Transmit Response Frame
  // {
  //   //Serial.println("Serial ID found");
  //   modbusSlaveTransmit(2, 0x0C, 0x03, 0x04, temp_transmit >> 8, (uint8_t)temp_transmit, DOmgl_transmit >> 8, (uint8_t)DOmgl_transmit);
  // }
  // else
  // {
  //   ;;//Serial.println("Not Found");
  // }
  // //Modbus Slave End
}