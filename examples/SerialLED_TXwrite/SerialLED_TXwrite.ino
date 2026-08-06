/*
  SerialLED_TXwrite.ino

  Demonstrates raw byte transmission using the SerialLED library.

  Default configuration:

    SerialLED.begin();

  uses:
    - 300 baud
    - LED_BUILTIN

  The matching reference receiver is:

    SerialLED_RX.ino

  Unlike print() and println(), write() transmits raw byte values.
  This makes it suitable for binary data, custom protocols and
  application-specific framing.
*/

#include <SerialLED.h>

void setup()
{
  // Default configuration:
  // 300 baud, LED_BUILTIN
  SerialLED.begin();
}

void loop()
{
  SerialLED.write('H');
  SerialLED.write('e');
  SerialLED.write('l');
  SerialLED.write('l');
  SerialLED.write('o');

  SerialLED.write('\r');
  SerialLED.write('\n');

  delay(1000);
}