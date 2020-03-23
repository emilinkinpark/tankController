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

float temperature = 0.00;
float pressure = 0.00;
float humidity = 0.00;
float altitude = 0.00;

void bmeInit()
{

  while (!Serial)
    ;
  Serial.println(F("BME680 test"));

  if (!bme.begin(0x77))
  {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
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
    Serial.println("Failed to perform reading :(");
  }
  temperature = bme.temperature;
  pressure = bme.pressure / 100.0;
  humidity = bme.humidity;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  //Debugging Start

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");
  Serial.println();
  //Debugging End
  delay(2000);
}