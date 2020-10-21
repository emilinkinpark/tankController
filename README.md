# tankController

The codes are licensed under GNU LESSER GENERAL PUBLIC LICENSE
*   Copyright © 2007 Free Software Foundation, Inc. <https://fsf.org/>
*   More on the license at <https://www.gnu.org/licenses/lgpl-3.0.en.html>
*   Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.
*   
*   Rouf Pvt. Ltd Bangladesh (Proposed) has complete rights over this firmware.
*
*   Acknowledgement: The project uses Arduino libraries.  
*   The aim is to build a ESP32 based firmware which acquire all sensors:
    1) Optical DO X 1 (MODBUS)
    2) pH X 1         (MODBUS) (Will be deactivated in the next version)
    3) MAX31865(For PT100) X 3      (SPI) (Has been moved to the emilinkinpark/Weather_Station)
    4) BME680 X 1     (I2C) (Has been moved to the emilinkinpark/Weather_Station)
*   The MODBUSRTU communication protocol is implemented according to Modbus_over_serial_line_V1_02.pdf
*   This program only reads data from multiple slave devices, performs necessary calculations and later sends to the MQTT broker.
*   ESP32 is used for it's versatility. 
