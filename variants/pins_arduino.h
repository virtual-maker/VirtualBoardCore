/*
  pins_arduino.h - Part of the VirtualBoard project

  The VirtualBoard library allows editing, building and debugging Arduino sketches
  in Visual C++ and Visual Studio IDE. The library emulates standard Arduino libraries
  and connects them e.g. with the real serial ports and NIC of the computer.
  Optionally, real binary and analogue I/O pins as well as I2C and SPI interfaces
  can be controlled via an IO-Warrior device.
  https://github.com/virtual-maker/VirtualBoard

  Created by Immo Wache <virtual.mkr@gmail.com>
  Copyright (c) 2022 Immo Wache. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef pins_arduino_h
#define pins_arduino_h

#include <inttypes.h>

// Arduino Duemilanove, Diecimila, and NG
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)

#define ARDUINO_ARCH_AVR
#define MAX_SERVOS 12

#define PIN_SERIAL_RX 0
#define PIN_SERIAL_TX 1

#define EXTERNAL_NUM_INTERRUPTS (2)
#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           6
#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)

#if defined(__AVR_ATmega8__)
#define digitalPinHasPWM(p)         ((p) == 9 || (p) == 10 || (p) == 11)
#else
#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)
#endif

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

static const uint8_t SS = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

#define PIN_WIRE_SDA        (18)
#define PIN_WIRE_SCL        (19)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN   (13)

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)
#define PIN_A6   (20)
#define PIN_A7   (21)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 21) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
//-------------------------------------------------------------------------------

// Leonardo and Micro
#elif defined(__AVR_ATmega32U4__)
#define ARDUINO_ARCH_AVR
#define MAX_SERVOS 12

#define NUM_DIGITAL_PINS  31
#define NUM_ANALOG_INPUTS 12

#define PIN_SERIAL_RX 0
#define PIN_SERIAL_TX 1

#define PIN_WIRE_SDA         (2)
#define PIN_WIRE_SCL         (3)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN 13
#define LED_BUILTIN_RX 17
#define LED_BUILTIN_TX 30

// Map SPI port to 'new' pins D14..D17
#define PIN_SPI_SS    (17)
#define PIN_SPI_MOSI  (16)
#define PIN_SPI_MISO  (14)
#define PIN_SPI_SCK   (15)

static const uint8_t SS = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// Mapping of analog pins as digital I/O
// A6-A11 share with digital pins
#define PIN_A0   (18)
#define PIN_A1   (19)
#define PIN_A2   (20)
#define PIN_A3   (21)
#define PIN_A4   (22)
#define PIN_A5   (23)
#define PIN_A6   (24)
#define PIN_A7   (25)
#define PIN_A8   (26)
#define PIN_A9   (27)
#define PIN_A10  (28)
#define PIN_A11  (29)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;	// D4
static const uint8_t A7 = PIN_A7;	// D6
static const uint8_t A8 = PIN_A8;	// D8
static const uint8_t A9 = PIN_A9;	// D9
static const uint8_t A10 = PIN_A10;	// D10
static const uint8_t A11 = PIN_A11;	// D12
//-------------------------------------------------------------------------------

// Arduino Nano Every
#elif defined(ARDUINO_AVR_NANO_EVERY)

#define MAX_SERVOS 12

#define PIN_SERIAL_RX 0
#define PIN_SERIAL_TX 1

#define EXTERNAL_NUM_INTERRUPTS  (2)
#define NUM_DIGITAL_PINS        (20)
#define NUM_ANALOG_INPUTS        (6)
#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)

#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10)

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

static const uint8_t SS = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

#define PIN_WIRE_SDA        (18)
#define PIN_WIRE_SCL        (19)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN   (13)

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)
#define PIN_A6   (20)
#define PIN_A7   (21)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
//-------------------------------------------------------------------------------

// ESP8266
// note: boot mode GPIOs 0, 2 and 15 can be used as outputs, GPIOs 6-11 are in use for flash IO
#elif defined(ARDUINO_ARCH_ESP8266)

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        17
#define NUM_ANALOG_INPUTS       1

// TODO: this should be <= 9 if flash is in DIO mode
#define isFlashInterfacePin(p)      ((p) >= 6 && (p) <= 11)

#define analogInputToDigitalPin(p)  ((p > 0) ? NOT_A_PIN : 0)

#define digitalPinToInterrupt(p)    (((p) < EXTERNAL_NUM_INTERRUPTS)? (p) : NOT_AN_INTERRUPT)

#define digitalPinHasPWM(p)         (((p) < NUM_DIGITAL_PINS && !isFlashInterfacePin(p))? 1 : 0)

#define PIN_SPI_SS   (15)
#define PIN_SPI_MOSI (13)
#define PIN_SPI_MISO (12)
#define PIN_SPI_SCK  (14)

static const uint8_t SS = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

#define PIN_WIRE_SDA (4)
#define PIN_WIRE_SCL (5)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#ifndef PIN_A0
#define PIN_A0 (17)
#endif /* PIN_A0 */

static const uint8_t A0 = PIN_A0;

#if defined(D1_MINI)
static const uint8_t D0 = 16;
static const uint8_t D1 = 5;
static const uint8_t D2 = 4;
static const uint8_t D3 = 0;
static const uint8_t D4 = 2;
static const uint8_t D5 = 14;
static const uint8_t D6 = 12;
static const uint8_t D7 = 13;
static const uint8_t D8 = 15;
static const uint8_t RX = 3;
static const uint8_t TX = 1;
#define LED_BUILTIN 2
#else
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1
#define LED_BUILTIN D0
#endif

// TODO: is this correct?
#define MAX_SERVOS 24
//-------------------------------------------------------------------------------

// ESP32-C3 LOLIN C3 mini
// note: boot mode GPIO 9 can be used as output
#elif defined(CONFIG_IDF_TARGET_ESP32C3)

#define EXTERNAL_NUM_INTERRUPTS 22
#define NUM_DIGITAL_PINS        22
#define NUM_ANALOG_INPUTS       6

#define analogInputToDigitalPin(p)  (((p) < NUM_ANALOG_INPUTS) ? (analogChannelToDigitalPin(p)) : -1)
#define digitalPinToInterrupt(p)    (((p) < NUM_DIGITAL_PINS) ? (p) : -1)
#define digitalPinHasPWM(p)         (p < EXTERNAL_NUM_INTERRUPTS)

static const uint8_t LED_BUILTIN = 7;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t TX = 21;
static const uint8_t RX = 20;

static const uint8_t SDA = 8;
static const uint8_t SCL = 10;

static const uint8_t SS = 5;
static const uint8_t MOSI = 4;
static const uint8_t MISO = 3;
static const uint8_t SCK = 2;

static const uint8_t A0 = 0;
static const uint8_t A1 = 1;
static const uint8_t A2 = 2;
static const uint8_t A3 = 3;
static const uint8_t A4 = 4;
static const uint8_t A5 = 5;
//-------------------------------------------------------------------------------


// ESP32-S2 LOLIN S2 mini
// note: boot mode GPIO 0 can be used as output
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
#define EXTERNAL_NUM_INTERRUPTS 46
#define NUM_DIGITAL_PINS        48
#define NUM_ANALOG_INPUTS       20

#define analogInputToDigitalPin(p)  (((p) < NUM_ANALOG_INPUTS) ? (analogChannelToDigitalPin(p)) : -1)
#define digitalPinToInterrupt(p)    (((p) < NUM_DIGITAL_PINS) ? (p) : -1)
#define digitalPinHasPWM(p)         (p < EXTERNAL_NUM_INTERRUPTS)

static const uint8_t LED_BUILTIN = 15;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t TX = 39;
static const uint8_t RX = 37;

static const uint8_t SDA = 33;
static const uint8_t SCL = 35;

static const uint8_t SS = 12;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 9;
static const uint8_t SCK = 7;

static const uint8_t A0 = 1;
static const uint8_t A1 = 2;
static const uint8_t A2 = 3;
static const uint8_t A3 = 4;
static const uint8_t A4 = 5;
static const uint8_t A5 = 6;
static const uint8_t A6 = 7;
static const uint8_t A7 = 8;
static const uint8_t A8 = 9;
static const uint8_t A9 = 10;
static const uint8_t A10 = 11;
static const uint8_t A11 = 12;
static const uint8_t A12 = 13;
static const uint8_t A13 = 14;
static const uint8_t A14 = 15;
static const uint8_t A15 = 16;
static const uint8_t A16 = 17;
static const uint8_t A17 = 18;
static const uint8_t A18 = 19;
static const uint8_t A19 = 20;
//-------------------------------------------------------------------------------


// Arduino Zero
// Note this will work with an Arduino Zero Pro, but not with an Arduino M0 Pro
// Arduino M0 Pro does not properly map pins to the board labeled pin numbers
#elif defined(_VARIANT_ARDUINO_ZERO_)
#define MAX_SERVOS 12

// Serial1
#define PIN_SERIAL1_RX       (0ul)
#define PIN_SERIAL1_TX       (1ul)

// Number of pins defined in PinDescription array
#define PINS_COUNT           (26u)
#define NUM_DIGITAL_PINS     (15u)
#define NUM_ANALOG_INPUTS    (7u)
#define NUM_ANALOG_OUTPUTS   (1u)

//Battery
#define ADC_BATTERY	(33u)

// LEDs
// ----
#define PIN_LED     (32u)
#define LED_BUILTIN PIN_LED

// Analog pins
// -----------
#define PIN_A0 (15u)
#define PIN_A1 (16u)
#define PIN_A2 (17u)
#define PIN_A3 (18u)
#define PIN_A4 (19u)
#define PIN_A5 (20u)
#define PIN_A6 (21u)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
#define ADC_RESOLUTION 12

// SPI Interfaces
// --------------
#define PIN_SPI_MISO  (10u)
#define PIN_SPI_MOSI  (8u)
#define PIN_SPI_SCK   (9u)
#define PIN_SPI_SS    (4u)

static const uint8_t SS = PIN_SPI_SS;   // SPI Slave SS not used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// Wire Interfaces
// ---------------
#define PIN_WIRE_SDA        (11u)
#define PIN_WIRE_SCL        (12u)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;
//-------------------------------------------------------------------------------

// Arduino MKRZero
// Arduino MKR WiFi 1010
// Arduino/Genuino MKR1000
#elif defined(ARDUINO_SAMD_MKRZERO) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKR1000)
#define MAX_SERVOS 12

// Serial1
#define PIN_SERIAL1_RX (13)
#define PIN_SERIAL1_TX (14)

#define NUM_ANALOG_INPUTS    (7u)

// LEDs
// ----
#define PIN_LED     (6u)
#define LED_BUILTIN PIN_LED

// Analog pins
// -----------
#define PIN_A0   (15u)
#define PIN_A1   (16u)
#define PIN_A2   (17u)
#define PIN_A3   (18u)
#define PIN_A4   (19u)
#define PIN_A5   (20u)
#define PIN_A6   (21u)
#define PIN_DAC0 (15u)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t DAC0 = PIN_DAC0;
#define ADC_RESOLUTION 12

// SPI Interfaces
// --------------
#define PIN_SPI_MISO  (10u)
#define PIN_SPI_MOSI  (8u)
#define PIN_SPI_SCK   (9u)
#define PIN_SPI_SS    (24u)
static const uint8_t SS = PIN_SPI_SS;   // SPI Slave SS not used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// Wire Interfaces
// ---------------
#define PIN_WIRE_SDA        (11u)
#define PIN_WIRE_SCL        (12u)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;
//-------------------------------------------------------------------------------

// Seeed XIAO M0 (SAMD)
#elif defined(ARDUINO_SEEED_XIAO_M0)

// Number of pins defined in PinDescription array
#define PINS_COUNT           (17u)
#define NUM_DIGITAL_PINS     (17u)
#define NUM_ANALOG_INPUTS    (11u)
#define NUM_ANALOG_OUTPUTS   (1u)

// Low-level pin register query macros
// -----------------------------------
#define digitalPinToPort(P)      (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P)   (1 << g_APinDescription[P].ulPin)
//#define analogInPinToBit(P)    ()
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port)  (&(port->IN.reg))
#define portModeRegister(port)   (&(port->DIR.reg))
#define digitalPinHasPWM(P)      (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

// LEDs
// ----
#define PIN_LED_13  (13u)
#define PIN_LED     PIN_LED_13
#define LED_BUILTIN PIN_LED


#define PIN_LED_RXL          (12u)
#define PIN_LED_TXL          (11u)
#define PIN_LED2             PIN_LED_RXL
#define PIN_LED3             PIN_LED_TXL

/*
 * Analog pins
 */
#define PIN_A0               (0ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 3)
#define PIN_A4               (PIN_A0 + 4)
#define PIN_A5               (PIN_A0 + 5)
#define PIN_A6               (PIN_A0 + 6)
#define PIN_A7               (PIN_A0 + 7)
#define PIN_A8               (PIN_A0 + 8)
#define PIN_A9               (PIN_A0 + 9)
#define PIN_A10              (PIN_A0 + 10)

#define PIN_DAC0             (PIN_A0)


static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
static const uint8_t A8 = PIN_A8;
static const uint8_t A9 = PIN_A9;
static const uint8_t A10 = PIN_A10;
static const uint8_t DAC0 = PIN_DAC0;

#define ADC_RESOLUTION		12

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

 // SPI interface for QSPI flash
#define PIN_SPI_MISO         (9u)
#define PIN_SPI_SCK          (8u)
#define PIN_SPI_MOSI         (10u)
#define PERIPH_SPI           sercom0
#define PAD_SPI_TX           SPI_PAD_2_SCK_3  // MOSI / SCK
#define PAD_SPI_RX           SERCOM_RX_PAD_1  // MISO

static const uint8_t SS = 4;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// /*
//  * RTL8720D Interfaces
//  */
#define RTL8720D_CHIP_PU        (1ul)

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

 // "external" public i2c interface
#define PIN_WIRE_SDA         (4u)
#define PIN_WIRE_SCL         (5u)
#define PERIPH_WIRE          sercom2
#define WIRE_IT_HANDLER      SERCOM2_Handler
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// USB
// ---
#define PIN_USB_HOST_ENABLE (14ul)
#define PIN_USB_DM          (15ul)
#define PIN_USB_DP          (16ul)

// I2S Interfaces
// --------------
#define I2S_INTERFACES_COUNT 0

#ifndef NO_USART_INTERFACE

// Serial1
#define PIN_SERIAL1_TX       (6ul)
#define PIN_SERIAL1_RX       (7ul)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)

#endif // not NO_USART_INTERFACE

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB

#ifndef NO_USART_INTERFACE

#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif


#define ADC_RESOLUTION 12
//-------------------------------------------------------------------------------

// STM32F103 Blue Pill
#elif defined(ARDUINO_BLUEPILL_F103C8)

#define ARDUINO_ARCH_STM32

// Bluepill USB connector on the top, MCU side - Blackpill USB connector on bottom, MCU Side  (pins are reversed vertically for Arduino Ananlog pin correct sequence.
// Left Side
#define PB9  0
#define PB8  1
#define PB7  2
#define PB6  3
#define PB5  4
#define PB4  5
#define PB3  6
#define PA15 7
#define PA12 8  // USB DP
#define PA11 9  // USB DM
#define PA10 10
#define PA9  11
#define PA8  12
#define PB15 13
#define PB14 14
#define PB13 15
#define PB12 16 // LED Blackpill
// Right side
#define PC13 17 // LED Bluepill
#define PC14 18
#define PC15 19
#define PA0  20 // A0
#define PA1  21 // A1
#define PA2  22 // A2
#define PA3  23 // A3
#define PA4  24 // A4
#define PA5  25 // A5
#define PA6  26 // A6
#define PA7  27 // A7
#define PB0  28 // A8
#define PB1  29 // A9
#define PB10 30
#define PB11 31
// Other
#define PB2  32 // BOOT1
#define PA13 33 // SWDI0
#define PA14 34 // SWCLK

// This must be a literal
#define NUM_DIGITAL_PINS        35
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       10
#define NUM_ANALOG_FIRST        20

// On-board LED pin number
#ifdef ARDUINO_BLUEPILL_F103C8
#define LED_BUILTIN             PC13
#else
#define LED_BUILTIN             PB12
#endif
#define LED_GREEN               LED_BUILTIN

// SPI Definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5
static const uint8_t SS = PIN_SPI_SS;   // SPI Slave SS not used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
//#define TIMER_TONE              TIM3

// Do not use basic timer: OC is required
//#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

#ifndef PWM_RESOLUTION
#define PWM_RESOLUTION              8
#endif

#define digitalPinIsValid(p)        ((p >= 0) && (p < NUM_DIGITAL_PINS))

// Specific for Firmata. As some pins could be duplicated,
// ensure 'p' is not one of the serial pins
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              (p == PIN_SERIAL_RX || p == PIN_SERIAL_TX)
#endif

// TODO: these are only quick and dirty definitions for Firmata so far
#define digitalPinHasI2C(p)         (p == PIN_WIRE_SDA || p == PIN_WIRE_SCL)
#define digitalPinHasSPI(p)         (p == PIN_SPI_MOSI || p == PIN_SPI_MISO ||  p == PIN_SPI_SCK)
#define digitalPinHasSerial(p)      (false)

#define MAX_NB_PORT 6
#define A0 PA0
#define MAX_SERVOS 12

//-------------------------------------------------------------------------------

#elif defined(ARDUINO_ARCH_RP2040)

// Seeed XIAO RP2040
#if defined(ARDUINO_SEEED_XIAO_RP2040)
// LEDs
#define PIN_LED        (17u)
#define PIN_LED_R      (17u)
#define PIN_LED_G      (16u)
#define PIN_LED_B      (25u)
#define LED_BUILTIN    PIN_LED

// Digital pins
static const uint8_t D0 = (26u);
static const uint8_t D1 = (27u);
static const uint8_t D2 = (28u);
static const uint8_t D3 = (29u);
static const uint8_t D4 = (6u);
static const uint8_t D5 = (7u);
static const uint8_t D6 = (0u);
static const uint8_t D7 = (1u);
static const uint8_t D8 = (2u);
static const uint8_t D9 = (4u);
static const uint8_t D10 = (3u);

// Analog pins
static const uint8_t A0 = (26u);
static const uint8_t A1 = (27u);
static const uint8_t A2 = (28u);
static const uint8_t A3 = (29u);
#define ADC_RESOLUTION 12

// NeoPixel
#define PIN_NEOPIXEL   (12u)
#define NEOPIXEL_POWER (11u)

// Serial1
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

// Serial2 not pinned out
#define PIN_SERIAL2_TX (31u)
#define PIN_SERIAL2_RX (31u)

// SPI
#define PIN_SPI0_MISO  (4u)
#define PIN_SPI0_MOSI  (3u)
#define PIN_SPI0_SCK   (2u)
#define PIN_SPI0_SS    (31u) // not pinned out
static const uint8_t SS = PIN_SPI0_SS;   // SPI Slave SS not used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI0_MOSI;
static const uint8_t MISO = PIN_SPI0_MISO;
static const uint8_t SCK = PIN_SPI0_SCK;

// Not pinned out
#define PIN_SPI1_MISO  (31u)
#define PIN_SPI1_MOSI  (31u)
#define PIN_SPI1_SCK   (31u)
#define PIN_SPI1_SS    (31u)
#define SPI_MISO       (PIN_SPI1_MISO)
#define SPI_MOSI       (PIN_SPI1_MOSI)
#define SPI_SCK        (PIN_SPI1_SCK)

// Wire
#define __WIRE0_DEVICE (i2c1)
#define PIN_WIRE0_SDA  (6u)
#define PIN_WIRE0_SCL  (7u)
#define SDA            PIN_WIRE0_SDA
#define SCL            PIN_WIRE0_SCL
#define I2C_SDA        (SDA)
#define I2C_SCL        (SCL)

// Wire1 not pinned out
#define __WIRE1_DEVICE (i2c0)
#define PIN_WIRE1_SDA  (31u)
#define PIN_WIRE1_SCL  (31u)

#define SERIAL_HOWMANY (1u)
#define SPI_HOWMANY    (1u)
#define WIRE_HOWMANY   (1u)

// Raspberry Pi Pico
#elif defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

// LEDs
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
#define PIN_LED        (32u)
#else
#define PIN_LED        (25u)
#endif

// Serial
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)

// SPI
#define PIN_SPI0_MISO  (16u)
#define PIN_SPI0_MOSI  (19u)
#define PIN_SPI0_SCK   (18u)
#define PIN_SPI0_SS    (17u)

#define PIN_SPI1_MISO  (12u)
#define PIN_SPI1_MOSI  (15u)
#define PIN_SPI1_SCK   (14u)
#define PIN_SPI1_SS    (13u)

// Wire
#define PIN_WIRE0_SDA  (4u)
#define PIN_WIRE0_SCL  (5u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define SERIAL_HOWMANY (3u)
#define SPI_HOWMANY    (2u)
#define WIRE_HOWMANY   (2u)

#define PINS_COUNT          (30u)
#define NUM_DIGITAL_PINS    (30u)
#define NUM_ANALOG_INPUTS   (4u)
#define NUM_ANALOG_OUTPUTS  (0u)
#define ADC_RESOLUTION      (12u)

#define LED_BUILTIN PIN_LED

static const uint8_t D0 = (0u);
static const uint8_t D1 = (1u);
static const uint8_t D2 = (2u);
static const uint8_t D3 = (3u);
static const uint8_t D4 = (4u);
static const uint8_t D5 = (5u);
static const uint8_t D6 = (6u);
static const uint8_t D7 = (7u);
static const uint8_t D8 = (8u);
static const uint8_t D9 = (9u);
static const uint8_t D10 = (10u);
static const uint8_t D11 = (11u);
static const uint8_t D12 = (12u);
static const uint8_t D13 = (13u);
static const uint8_t D14 = (14u);
static const uint8_t D15 = (15u);
static const uint8_t D16 = (16u);
static const uint8_t D17 = (17u);
static const uint8_t D18 = (18u);
static const uint8_t D19 = (19u);
static const uint8_t D20 = (20u);
static const uint8_t D21 = (21u);
static const uint8_t D22 = (22u);
static const uint8_t D23 = (23u);
static const uint8_t D24 = (24u);
static const uint8_t D25 = (25u);
static const uint8_t D26 = (26u);
static const uint8_t D27 = (27u);
static const uint8_t D28 = (28u);
static const uint8_t D29 = (29u);

#ifdef __PIN_A0
static const uint8_t A0 = __PIN_A0;
#else
static const uint8_t A0 = (26u);
#endif

#ifdef __PIN_A1
static const uint8_t A1 = __PIN_A1;
#else
static const uint8_t A1 = (27u);
#endif

#ifdef __PIN_A2
static const uint8_t A2 = __PIN_A2;
#else
static const uint8_t A2 = (28u);
#endif

#ifdef __PIN_A3
static const uint8_t A3 = __PIN_A3;
#else
static const uint8_t A3 = (29u);
#endif

static const uint8_t SS = PIN_SPI0_SS;
static const uint8_t MOSI = PIN_SPI0_MOSI;
static const uint8_t MISO = PIN_SPI0_MISO;
static const uint8_t SCK = PIN_SPI0_SCK;

static const uint8_t SDA = PIN_WIRE0_SDA;
static const uint8_t SCL = PIN_WIRE0_SCL;

#else
#error Unknown board with Raspberry Pico 2040 architecture
#endif

//-------------------------------------------------------------------------------

// anything else
#else
#error "Please edit variants/pins_arduino.h or #define existing board type"
#endif

#endif