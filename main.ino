#include <Arduino.h>
#include "AT34C04_EEPROM.h"

#define EEPROM_I2C_ADDR 0x50 //Address of eeprom chip
AT34C04_EEPROM eeprom(EEPROM_I2C_ADDR); // init eeprom with 12c address


void setup()
{
  byte location = 1;
  byte value = 15;
  // write the value 15 into a memory loaction 
  eeprom.write(location, value);
}

void loop()
{
  // read the value from memory location 1
  byte value = eeprom.read(1);
}
