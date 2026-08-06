/*
  SerialLED_TXfloat.ino

  Demonstrates floating-point output using the SerialLED library.

  Default configuration:

    SerialLED.begin();

  uses:
    - 300 baud
    - LED_BUILTIN

  The matching reference receiver is:

    SerialLED_RX.ino
*/

#include <SerialLED.h>

float value = 0.1234567;

void setup()
{
  SerialLED.begin();
}

void loop()
{
  value++;

  SerialLED.print(value, 5);
  SerialLED.println(" = next value");

  delay(1000);
}