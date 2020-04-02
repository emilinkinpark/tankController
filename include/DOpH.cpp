#include "modbus.cpp"
#include "conversions.cpp"

// DO sensor ID
#define O2_slaveID 0x0E
#define O2_slaveID_DEC 14



float DOmgl;
float DO_Temp;

void DO()
{
  int o2[13]; //O2 buffer length must have a size of 12 bytes
  int incomingData[7];
  //Modbus Master Start
  memset(o2, 0, sizeof(o2));                     //Empties array
  memset(incomingData, 0, sizeof(incomingData)); //Empties array

  // Start Measurement
  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x25, 0x00, 0x00, 0x01); //Serial2 used for Transceive Data
  serial_flush_buffer(3);                                            //Cleaning Response
  delay(2000);
  //Serial.println("Starting Measurement");

  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x26, 0x00, 0x00, 0x04);
  for (int i = 0; i <= 5; i++)
  {
    modbusRead(3, O2_slaveID_DEC, 13, o2);
    delay(100);
  }

  Serial.println("Data Acquired");

  if (o2[0] != O2_slaveID_DEC) //Slave ID Check
  {
    // Serial.println("Slave ID not matched Transmission Halt!");
    //Serial.println(o2[0], HEX);
  }
  else
  {
    DO_Temp = floatTOdecimal(o2[3], o2[4], o2[5], o2[6]);
    //float Temp_Manipulation = Conv_Temp * 100;
    //Temp_Send = Temp_Manipulation;

    float Conv_DOPerc = floatTOdecimal(o2[7], o2[8], o2[9], o2[10]);
    DOmgl = domglcalc(DO_Temp, Conv_DOPerc);

    //  float DOmgl_Manipulation = DOmgl * 1000;
    //   DOmgl_Send = DOmgl_Manipulation;

    //   /*
    //   //Serial.write("Temperature: ");
    //   //Serial.println(Conv_Temp);
    //   //Serial.println(Temp_Send);

    //   //Serial.write("DO Percentage: ");
    //   //Serial.println(Conv_DOPerc * 100);
     // Serial.write("DO mg/L: ");
     // Serial.println(DOmgl);
    //   //Serial.println(DOmgl_Send);
    //   */
  }

  // Stop Measurement
  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x2E, 0x00, 0x00, 0x01);
  serial_flush_buffer(3); //Cleaning Response
  //delay(100);
  //  Serial.println("Stop Measurement");
}


void pH()
{
  //Future Implementation of pH Sensor
}