
/* The codes are licensed under GNU LESSER GENERAL PUBLIC LICENSE
*   Copyright © 2007 Free Software Foundation, Inc. <https://fsf.org/>
*   More on the lincense at <https://www.gnu.org/licenses/lgpl-3.0.en.html>
*   Everyone is permitted to copy and distribute verbatim copies of this license document, but changing is not allowed.
*   
*   Acknowledgement: The project uses a lot of free libraries from different contributors. An special thanks to all hard working software people. 
*                    Specific acknowledgement is made into the seperate files in the include folder.
*    
*   The purpose of this project is to create a decentralised or independent controller for Glory Agro Project Ltd's Intensive Prawn Farming Project. 
*   The field slave devices talks back to ESP32 (Master) over RS485 Modbus.
*   The data is taken in and send to Raspberrypi MQTT server over Wifi
*   
*/

#include "mqtt.cpp"
#include "modbus.h"
#include "modbus.cpp"

#include "conversions.cpp"
#include "bme680.cpp"

//Serial Pins Definition

#define UART1_RX 4
#define UART1_TX 2
#define UART2_RX 16
#define UART2_TX 17

// TCS3200 Color Sensor

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 32
#define S1 33
#define S2 25
#define S3 26
#define sensorOut 35

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// DO sensor ID
#define O2_slaveID 0x0E
#define O2_slaveID_DEC 14

// Global Variables for Temperature and DO mg/L for Optical DO Sensor
uint16_t Temp_Send = 0;
uint16_t DOmgl_Send = 0;
uint16_t temp_transmit = 0;
uint16_t DOmgl_transmit = 0;

int o2[13]; //O2 buffer length must have a size of 12 bytes
int incomingData[7];

void Core0code(void *pvParameters) //All other sensor and MQTT interface
{
  for (;;)
  {

    // bmeRun();          // Running bme680 codes
    //   //TCS3200 Code Start
    //   // Setting RED (R) filtered photodiodes to be read
    //   digitalWrite(S2,LOW);
    //   digitalWrite(S3,LOW);

    //   // Reading the output frequency
    //   redFrequency = pulseIn(sensorOut, LOW);

    //    // Printing the RED (R) value
    //   Serial.print("R = ");
    //   Serial.print(redFrequency);
    //   delay(100);

    //   // Setting GREEN (G) filtered photodiodes to be read
    //   digitalWrite(S2,HIGH);
    //   digitalWrite(S3,HIGH);

    //   // Reading the output frequency
    //   greenFrequency = pulseIn(sensorOut, LOW);

    //   // Printing the GREEN (G) value
    //   Serial.print(" G = ");
    //   Serial.print(greenFrequency);
    //   delay(100);

    //   // Setting BLUE (B) filtered photodiodes to be read
    //   digitalWrite(S2,LOW);
    //   digitalWrite(S3,HIGH);

    //   // Reading the output frequency
    //   blueFrequency = pulseIn(sensorOut, LOW);

    //   // Printing the BLUE (B) value
    //   Serial.print(" B = ");
    //   Serial.println(blueFrequency);
    //   delay(100);
    // // TCS3200 code end
  }
}

void setup()
{

  //xTaskCreatePinnedToCore(Core0code, "Task0", 10000, NULL, 1, NULL, 0);   // Handle to access core 0, ill advised to use while using WiFi or BLE

  Serial.begin(9600); //TXD0 - used as serial decorder

  //Serial1.begin(9600, SERIAL_8N1, UART1_RX, UART1_TX);
  //Caution: Remove Pins before uploading firmware!!!!! // Shared with Flash

  //Serial2.begin(9600, SERIAL_8N1, UART2_RX, UART2_TX);
  bmeInit();   // Initialising BME680 Dependencies
  mqtt_init(); //Initialising MQTT Dependencies

  // // TCS3200 Color Sensor Setup
  // // Setting the outputs
  // pinMode(S0, OUTPUT);
  // pinMode(S1, OUTPUT);
  // pinMode(S2, OUTPUT);
  // pinMode(S3, OUTPUT);

  // // Setting the sensorOut as an input
  // pinMode(sensorOut, INPUT);

  // // Setting frequency scaling to 20%
  // digitalWrite(S0,HIGH);
  // digitalWrite(S1,LOW);
  // // TCS3200 Sensor Setup end

}

void loop() // All Modbus Operation
{

  // //Modbus Master Start
  // memset(o2, 0, sizeof(o2));                     //Empties array
  // memset(incomingData, 0, sizeof(incomingData)); //Empties array

  // // Start Measurement
  // modbusMasterTransmit(3, O2_slaveID, 0x03, 0x25, 0x00, 0x00, 0x01);
  // serial_flush_buffer(3); //Cleaning Response
  // delay(2000);
  // //Serial.println("Starting Measurement");

  // modbusMasterTransmit(3, O2_slaveID, 0x03, 0x26, 0x00, 0x00, 0x04);
  // for (int i = 0; i <= 5; i++)
  // {
  //   modbusRead(3, O2_slaveID_DEC, 13, o2);
  //   delay(100);
  // }

  // //Serial.println("Data Acquired");

  // if (o2[0] != 14) //Slave ID Check
  // {
  //  // Serial.println("Slave ID not matched Transmission Halt!");
  //   //Serial.println(o2[0], HEX);
  // }
  // else
  // {
  //   float Conv_Temp = floatTOdecimal(o2[3], o2[4], o2[5], o2[6]);
  //   float Temp_Manipulation = Conv_Temp * 100;
  //   Temp_Send = Temp_Manipulation;

  //   float Conv_DOPerc = floatTOdecimal(o2[7], o2[8], o2[9], o2[10]);
  //   float DOmgl = domglcalc(Conv_Temp, Conv_DOPerc);

  //   float DOmgl_Manipulation = DOmgl * 1000;
  //   DOmgl_Send = DOmgl_Manipulation;

  //   /*
  //   //Serial.write("Temperature: ");
  //   //Serial.println(Conv_Temp);
  //   //Serial.println(Temp_Send);

  //   //Serial.write("DO Percentage: ");
  //   //Serial.println(Conv_DOPerc * 100);
  //   //Serial.write("DO mg/L: ");
  //   //Serial.println(DOmgl);
  //   //Serial.println(DOmgl_Send);
  //   */

  // }

  // // Stop Measurement
  // modbusMasterTransmit(3, O2_slaveID, 0x03, 0x2E, 0x00, 0x00, 0x01);
  // serial_flush_buffer(3); //Cleaning Response
  // //delay(100);
  // //Serial.println("Stop Measurement");
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

  long now = millis(); //MQTT dependant
  
  
  
  bmeRun(); //BME680 reading




  //MQTT Start
  mqttloop();
  //mqttpayload(air_temp, 0, 0, 0, ambient_pressure, ambient_humidity, ambient_altitude, 0, 0, 0, 0);
  if (now - lastMsg > 5000)
  {
    lastMsg = now;
    char str[50];  //Stores Payload to send out
    char temp[8]; 

    dtostrf(air_temp, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"air_temp\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);

    dtostrf(ambient_pressure, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_pressure\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);
    delay(100);


    dtostrf(ambient_humidity, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_humidity\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);

    dtostrf(ambient_altitude, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_altitude\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);
    delay(100);


    dtostrf(heartbeat, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"heartbeat\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/heartbeat", str);
    heartbeat++;


    memset(str, 0, sizeof(str));   //Empties array
  }
  //MQTT End

  //Serial.println(millis()-now);   //Shows time to complete a full cycle in milli seconds
}