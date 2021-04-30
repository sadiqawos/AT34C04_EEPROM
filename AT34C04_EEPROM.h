/*
  AT34C04_EEPROM.h - Library for reading and writing
  to external EEPROM AT34C04
  Created by Sadiq Awosanmi, April 21, 2021.

  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8827G-SEEPROM-AT34C04-Datasheet.pdf
*/

#ifndef AT34C04_EEPROM_h
#define AT34C04_EEPROM_h

#include "Arduino.h"

#define DATA_BYTE_COUNT 1
#define I2C_STATUS_SUCCESS 0
#define I2C_STATUS_DATA_TOO_LONG 1
#define I2C_STATUS_NACK_ADDR 2
#define I2C_STATUS_NACK_DATA 3
#define I2C_STATUS_OTHER_ERROR 4
#define DEVICE_READY_TIMEOUT 100
#define MEMORY_ADDRESS_MAX 512
#define MEMORY_BLOCK_SIZE 256
#define SPA_LOW 0b0110110
#define SPA_HIGH 0b0110111

class AT34C04_EEPROM
{
public:
  AT34C04_EEPROM(byte disk_address);
  void write(unsigned int memory_location, byte data);
  byte read(unsigned int memory_location);

private:
  byte _disk_address;
  byte _getAddressFromLocation(unsigned int memory_location);
  bool _deviceReady(byte disk_address);
  void _writePageIdentifier(unsigned int memory_location);
};

#endif
