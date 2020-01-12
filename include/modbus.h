#ifdef _modbus_h
#define _modbus_h

//#include <Arduino.h>

static uint16_t crc16(uint8_t *buffer, uint16_t buffer_length); //Generates CRC based on Datastream 



void modbusTransmit(uint8_t slave_addr,uint8_t starting_address, uint8_t length); // Modbus Transmit Function
  /*  Working Process
   *  Takes the slave address, starting address and datalength, and stores it into data_stream.
   *  Generates CRC
   *  Takes in the serial buffer from data_stream and transfer to slave over Serial2(ESP32 UART2)
   *  CRC transmitted
   */


void modbusRead(int *buff, int length);
  /* Working Process
   * Waits for the serial buffer to be full
   * Reads each data and stores it into a buffer array until the Counter meets it's condition
   * The buffer array ignores Null string
  */


  #endif