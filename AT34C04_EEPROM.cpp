/*
    AT34C04_EEPROM.cpp - Library for reading and writing
    to external EEPROM AT34C04
    Created by Sadiq Awosanmi, April 21, 2021.

    https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8827G-SEEPROM-AT34C04-Datasheet.pdf
*/

#include "Arduino.h"
#include "AT34C04_EEPROM.h"
#include <Wire.h>

AT34C04_EEPROM::AT34C04_EEPROM(byte disk_address)
{
    _disk_address = disk_address;
}

bool AT34C04_EEPROM::_deviceReady(byte disk_address)
{
    uint32_t timeout = millis();
    bool ready = false;
    while (!ready && (millis() - timeout < DEVICE_READY_TIMEOUT))
    {
        Wire.beginTransmission(disk_address);
        byte status = Wire.endTransmission();
        ready = (status == I2C_STATUS_SUCCESS);
    }
    return ready;
}

void AT34C04_EEPROM::_writePageIdentifier(unsigned int memory_location)
{
    byte page = (memory_location <= 256) ? SPA_LOW : SPA_HIGH;

    Wire.beginTransmission(page);
    Wire.write((byte)0);
    Wire.write((byte)0);
    Wire.endTransmission();
}

byte AT34C04_EEPROM::_getAddressFromLocation(unsigned int memory_location)
{
    byte address = (memory_location <= MEMORY_BLOCK_SIZE) ? (byte)memory_location : (byte)(memory_location - MEMORY_BLOCK_SIZE - 1);
    return address;
}

void AT34C04_EEPROM::write(unsigned int memory_location, byte data)
{
    if (!_deviceReady(_disk_address) || memory_location > MEMORY_ADDRESS_MAX)
    {
        return;
    }
    _writePageIdentifier(memory_location);

    byte address = _getAddressFromLocation(memory_location);

    Wire.beginTransmission(_disk_address);
    Wire.write(address);
    Wire.write(data);
    Wire.endTransmission();
}

byte AT34C04_EEPROM::read(unsigned int memory_location)
{
    byte rdata = 0xFF;
    if (!_deviceReady(_disk_address))
    {
        return rdata;
    }
    _writePageIdentifier(memory_location);

    byte address = _getAddressFromLocation(memory_location);

    Wire.beginTransmission(_disk_address);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(_disk_address, DATA_BYTE_COUNT);
    if (Wire.available())
    {
        rdata = Wire.read();
    }

    return rdata;
}
