/*
  SerialComparison.ino

  Demonstrates the similar APIs of Serial and SerialLED.

  Serial output is sent through the normal UART interface, while SerialLED
  sends the same data optically through LED_BUILTIN.

  Default SerialLED configuration:

    SerialLED.begin();

  uses:
    - 300 baud
    - LED_BUILTIN

  One of the main design goals of SerialLED is API familiarity.
  Existing sketches can often be adapted by replacing:

      Serial.    ->    SerialLED.

  and vice versa.

  The matching optical receiver is:

    SerialLED_RX.ino
*/

#include <SerialLED.h>

unsigned long counter = 0;

void setup()
{
  Serial.begin(115200);
  SerialLED.begin();
}

void loop()
{
  Serial.print("Counter: ");
  Serial.println(counter);

  SerialLED.print("Counter: ");
  SerialLED.println(counter);

  ++counter;
  delay(1000);
}