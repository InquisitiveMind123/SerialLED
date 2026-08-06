/*
  SerialLED_RX.ino

  Reference receiver for the SerialLED optical data transmission project.

  This sketch receives UART-style optical data from an LED using a BPW40
  phototransistor and forwards the received text to the Serial Monitor.

  Transmission format:
    - 1 start bit
    - 8 data bits
    - No parity
    - 1 stop bit
    - Least significant bit first

  The receiver status LED is optional but recommended. It briefly lights
  whenever valid text data is received. This provides immediate feedback
  while positioning the optical probe over the transmitting LED.

  The default receiver setting is 300 baud and therefore matches:

    SerialLED.begin();

  on the transmitter.

  Reference receiver circuit:

                         +5 V
                          |
                        [10 kΩ]
                          |
                          +---------------- Arduino D2 (RX_PIN)
                          |
                         (K)
                        BPW40
                         (A)
                          |
                         GND

  Optional receiver status LED:

    Arduino D13 (LED_PIN) ----[330 Ω]----|>|---- GND
                                         LED

  Four-core probe cable:
    - VCC
    - GND
    - Phototransistor signal
    - Status LED signal

  Notes:
    - The reference configuration uses 300 baud.
    - The maximum reliable baud rate depends on the complete hardware setup
      and transmitted data and must be determined experimentally.
    - Initial characters may be corrupted if the probe is positioned while
      a transmission is already in progress.
*/

// Comment out this line if no receiver status LED is used.
#define USE_STATUS_LED

const byte RX_PIN = 2;

#ifdef USE_STATUS_LED
const byte LED_PIN = 13;
const unsigned long LED_PULSE_MS = 20;

unsigned long ledPulseStartTime = 0;
bool ledPulseActive = false;
#endif

// Reference configuration (default).
// This matches SerialLED.begin() on the transmitter.
const unsigned int BIT_US = 3333; // 300 baud

// Alternative test values:
//
// const unsigned int BIT_US = 10000; // 100 baud
// const unsigned int BIT_US = 1667;  // 600 baud
// const unsigned int BIT_US = 833;   // 1200 baud
// const unsigned int BIT_US = 417;   // 2400 baud
// const unsigned int BIT_US = 208;   // 4800 baud
// const unsigned int BIT_US = 104;   // 9600 baud

byte readByteOptical()
{
  byte dataByte = 0;

  // Move to the middle of the start bit.
  delayMicroseconds(BIT_US / 2);

  if (digitalRead(RX_PIN) != LOW)
  {
    return 0; // No valid start bit
  }

  // Move to the middle of data bit 0.
  delayMicroseconds(BIT_US);

  for (byte bitIndex = 0; bitIndex < 8; bitIndex++)
  {
    if (digitalRead(RX_PIN) == HIGH)
    {
      bitSet(dataByte, bitIndex);
    }

    delayMicroseconds(BIT_US);
  }

  return dataByte;
}

#ifdef USE_STATUS_LED

void startLedPulse()
{
  digitalWrite(LED_PIN, HIGH);

  ledPulseStartTime = millis();
  ledPulseActive = true;
}

void updateLed()
{
  if (ledPulseActive &&
      millis() - ledPulseStartTime >= LED_PULSE_MS)
  {
    digitalWrite(LED_PIN, LOW);
    ledPulseActive = false;
  }
}

#endif

void setup()
{
  pinMode(RX_PIN, INPUT);

#ifdef USE_STATUS_LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
#endif

  Serial.begin(115200);
  Serial.println("SerialLED RX ready");
}

void loop()
{
#ifdef USE_STATUS_LED
  updateLed();
#endif

  // Wait for the idle level.
  while (digitalRead(RX_PIN) == LOW)
  {
#ifdef USE_STATUS_LED
    updateLed();
#endif
  }

  // Wait for the start bit.
  while (digitalRead(RX_PIN) == HIGH)
  {
#ifdef USE_STATUS_LED
    updateLed();
#endif
  }

  byte dataByte = readByteOptical();

  // Forward printable ASCII characters and normal line endings.
  if ((dataByte >= 32 && dataByte <= 126) ||
      dataByte == '\r' ||
      dataByte == '\n')
  {
    Serial.write(dataByte);

#ifdef USE_STATUS_LED
    startLedPulse();
#endif
  }
  else
  {
    // Make invalid or unsupported bytes visible during testing.
    Serial.print('?');
  }

#ifdef USE_STATUS_LED
  updateLed();
#endif
}
