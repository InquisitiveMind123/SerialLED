#include "SerialLED.h"

void SerialLEDClass::begin(unsigned long baudRate, uint8_t txPin)
{
  _txPin = txPin;

  pinMode(_txPin, OUTPUT);

  // Idle state: logical 1 = LED off.
  digitalWrite(_txPin, LOW);

  if (baudRate == 0)
  {
    _bitTimeUs = 0;
    return;
  }

  _bitTimeUs = 1000000UL / baudRate;
}

size_t SerialLEDClass::write(uint8_t dataByte)
{
  if (_bitTimeUs == 0)
  {
    return 0;
  }

  writeStartBit();

  for (uint8_t bitIndex = 0; bitIndex < 8; ++bitIndex)
  {
    writeDataBit(dataByte & 0x01);
    dataByte >>= 1;
  }

  writeStopBit();

  return 1;
}

void SerialLEDClass::writeStartBit()
{
  writeBit(false);
}

void SerialLEDClass::writeDataBit(bool dataBit)
{
  writeBit(dataBit);
}

void SerialLEDClass::writeStopBit()
{
  writeBit(true);
}

void SerialLEDClass::writeBit(bool dataBit)
{
  // Logical 1 = LED off, logical 0 = LED on.
  digitalWrite(_txPin, dataBit ? LOW : HIGH);
  delayMicroseconds(_bitTimeUs);
}

SerialLEDClass SerialLED;
