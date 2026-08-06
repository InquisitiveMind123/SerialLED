#ifndef SERIALLED_SERIALLED_H
#define SERIALLED_SERIALLED_H

#include <Arduino.h>
#include <Print.h>

class SerialLEDClass : public Print
{
public:
  void begin(
    unsigned long baudRate = 300,
    uint8_t txPin = LED_BUILTIN
  );

  size_t write(uint8_t dataByte) override;

  using Print::write;

private:
  uint8_t _txPin = LED_BUILTIN;
  unsigned long _bitTimeUs = 0;

  void writeStartBit();
  void writeDataBit(bool dataBit);
  void writeStopBit();
  void writeBit(bool dataBit);
};

extern SerialLEDClass SerialLED;

#endif
