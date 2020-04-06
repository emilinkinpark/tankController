/*
Libraries based on the Adafruit
Code taken or slightly modified from : http://www.esp32learning.com/code/esp32-and-bme680-sensor-example.php
*/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

Adafruit_BME680 bme; // I2C

#define SEALEVELPRESSURE_HPA (1013.25)

boolean bme680_heartbeat = 1; // Device Check

char air_temp = 0.00;
float ambient_pressure = 0.00;
float ambient_humidity = 0.00;
float ambient_altitude = 0.00;

void bmeInit()
{

  while (!Serial)
    ;
  //Serial.println(F("BME680 test"));

  if (!bme.begin(0x77))
  {
    bme680_heartbeat = 0;
    //Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void bmeRun()
{
  if (!bme.performReading())
  {
    bme680_heartbeat = 0;
    //Serial.println("Failed to perform reading :(");
  }
  air_temp = bme.temperature;
  ambient_pressure = bme.pressure / 100.0;
  ambient_humidity = bme.humidity;
  ambient_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // //Debugging Start

  // Serial.print("Temperature = ");
  // Serial.print(air_temp);
  // Serial.println(" *C");

  // Serial.print("Pressure = ");
  // Serial.print(ambient_pressure);
  // Serial.println(" hPa");

  // Serial.print("Humidity = ");
  // Serial.print(ambient_humidity);
  // Serial.println(" %");

  // // Serial.print("Gas = ");
  // // Serial.print(bme.gas_resistance / 1000.0);
  // // Serial.println(" KOhms");

  // Serial.print("Approx. Altitude = ");
  // Serial.print(ambient_altitude);
  // Serial.println(" m");
  // Serial.println();
  // //Debugging End
  delay(2000);
}