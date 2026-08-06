# SerialLED

## Typical use cases

SerialLED is intended for situations where no conventional communication
interface is available or desirable.

Typical applications include:

- Adding a maintenance interface to products that already contain a status LED.

- Retrieving diagnostic information from sealed or potted devices.

- Reading debug messages without a USB, UART or network connection.

- Devices located behind windows.

- Underwater devices where a physical electrical contact is impractical or impossible.

- Low-cost optical communication between microcontrollers.

- Educational projects demonstrating optical serial communication via an onboard or external LED.


## Ease of use

SerialLED provides a familiar Arduino `Print` API for optical data transmission through an onboard or external LED.

One of the primary design goals of SerialLED is **API familiarity**. Existing sketches can often be adapted simply by replacing:

```cpp
Serial.
```

with

```cpp
SerialLED.
```

and vice versa.

## Basic use

```cpp
#include <SerialLED.h>

void setup()
{
  SerialLED.begin();  // 300 baud, LED_BUILTIN
}

void loop()
{
  SerialLED.println("Hello");
  delay(1000);
}
```

The matching reference receiver is provided as:

```
SerialLED_RX.ino
```

## Alternative initialization

```cpp
SerialLED.begin(600);     // 600 baud, LED_BUILTIN
SerialLED.begin(300, 7);  // 300 baud, pin 7
SerialLED.begin(600, 7);  // 600 baud, pin 7
```

## Version 1.0 API

- `begin()`
- `write()`
- `print()`
- `println()`

## Default configuration

The default configuration is **300 baud** using `LED_BUILTIN`.

It was selected because it proved to be the **most robust while still providing a reasonable transfer rate**.

The maximum reliable baud rate depends on the complete hardware setup and the transmitted data and should therefore be determined experimentally for each individual application.

During development, successful transmissions of up to **9600 baud** were achieved with the reference implementation. These results demonstrate the potential of the concept but should not be interpreted as a guaranteed operating speed for other hardware configurations.

## Design philosophy

SerialLED is a **transport layer**.

Framing, checksums, CRCs, sequence numbers, acknowledgements and application-specific protocols can be implemented by the user on top of it.

The library intentionally focuses on providing a simple, familiar and lightweight optical transport interface.
