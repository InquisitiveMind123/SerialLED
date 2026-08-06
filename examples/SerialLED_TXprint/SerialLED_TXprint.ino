/*
  SerialLED_TXprint.ino

  Demonstrates the familiar Serial-style API of the SerialLED library.

  Default configuration:

    SerialLED.begin();

  uses:
    - 300 baud
    - LED_BUILTIN

  The matching reference receiver is:

    SerialLED_RX.ino

  One of the main design goals of SerialLED is API familiarity.
  Existing sketches can often be adapted by replacing:

      Serial.    ->    SerialLED.

  and vice versa.
*/

#include <SerialLED.h>

int n = 0;

void setup()
{
  // Default configuration:
  // 300 baud, LED_BUILTIN
  SerialLED.begin();
}

void loop()
{
  n++;

  SerialLED.print(n);
  SerialLED.println(". Hello from SerialLED");

  delay(1000);
}
