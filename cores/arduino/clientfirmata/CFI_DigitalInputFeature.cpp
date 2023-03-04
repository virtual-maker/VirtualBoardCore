/*
  CFI_DigitalInputFeature.cpp - ClientFirmata library
  Copyright (C) 2022 Immo Wache.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include "CFI_DigitalInputFeature.h"

static void nothing(void) {
}

#if defined(EXTERNAL_NUM_INTERRUPTS)
static volatile int intMode[EXTERNAL_NUM_INTERRUPTS] = { 0 };
static volatile bool intState[EXTERNAL_NUM_INTERRUPTS] = { false };
static volatile bool intPending[EXTERNAL_NUM_INTERRUPTS] = { false };
static volatile voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS] = {
#if EXTERNAL_NUM_INTERRUPTS > 8
    #warning There are more than 8 external interrupts.Some callbacks may not be initialized.
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 7
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 6
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 5
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 4
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 3
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 2
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 1
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 0
    nothing,
#endif
};
#else
#pragma message ("WARNING: No pin interrupt feature supported")
#endif // EXTERNAL_NUM_INTERRUPTS

CFI_DigitalInputFeature::CFI_DigitalInputFeature(CFI_ClientFirmata &firmata) : _firmata(&firmata)
{
  for (size_t i = 0; i < 16; i++) {
    _digitalPorts[i] = 0;
    _reportPorts[i] = false;
  }
  _firmata->attach(*this);
}

void CFI_DigitalInputFeature::setDigitalPort(byte port, int value)
{
  if (port < 16) {
    _digitalPorts[port] = value;

#if defined(EXTERNAL_NUM_INTERRUPTS)
    if (port == 0) {
      for (size_t i = 0; i < 8; i++) {
        int8_t intNum = digitalPinToInterrupt(i);
        if (intNum != NOT_AN_INTERRUPT) {
          if (intFunc[intNum] != nothing) {
            bool pinValue = (value & (1 << (i & 0x07))) != 0;

            bool intTrigger = false;
            switch (intMode[intNum])
            {
            case CHANGE:
              intTrigger = pinValue != intState[intNum];
              break;
            case FALLING:
              intTrigger = !pinValue && intState[intNum];
              break;
            case RISING:
              intTrigger = pinValue && !intState[intNum];
              break;
            default:
              break;
            }

            intState[intNum] = pinValue;
            if (intTrigger) {
              if (interruptsEnabled) {
                intFunc[intNum]();
              } else {
                intPending[intNum] = true;
              }
            }
          }
        }
      }
    }
#endif // EXTERNAL_NUM_INTERRUPTS
  }
}

void CFI_DigitalInputFeature::setPinMode(byte pin, int mode)
{
  _firmata->setPinMode(pin, mode);

  byte port = (pin >> 3) & 0x0F;
  if (!_reportPorts[port]) {
    reportDigitalPort(port);
  }
}

void CFI_DigitalInputFeature::reportDigitalPort(byte port)
{
  byte message[2];

  message[0] = (byte)(CFI_REPORT_DIGITAL | port);
  message[1] = 1;
  _firmata->write(message, 2);

  _reportPorts[port] = true;
}

bool CFI_DigitalInputFeature::getPinValue(byte pin)
{
  int port = (pin >> 3) & 0x0F;

  byte value = _digitalPorts[port] & (1 << (pin & 0x07));
  return value != 0;
}

boolean CFI_DigitalInputFeature::handleSysex(byte command, int argc, byte* argv)
{
  return false;
}

void CFI_DigitalInputFeature::updateFeature()
{
}

void CFI_DigitalInputFeature::attachInterrupt(uint8_t interruptNum, void(*userFunc)(void), int mode)
{
#if defined(EXTERNAL_NUM_INTERRUPTS)
    if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        intFunc[interruptNum] = userFunc;
        intMode[interruptNum] = mode;
    }
#endif // EXTERNAL_NUM_INTERRUPTS
}

void CFI_DigitalInputFeature::detachInterrupt(uint8_t interruptNum)
{
#if defined(EXTERNAL_NUM_INTERRUPTS)
    if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        intFunc[interruptNum] = nothing;
    }
#endif // EXTERNAL_NUM_INTERRUPTS
}

void CFI_DigitalInputFeature::interrupts()
{
  interruptsEnabled = true;

#if defined(EXTERNAL_NUM_INTERRUPTS)
  for (size_t i = 0; i < 8; i++) {
    int8_t intNum = digitalPinToInterrupt(i);
    if (intNum != NOT_AN_INTERRUPT) {
      if (intFunc[intNum] != nothing && intPending[intNum]) {
        intPending[intNum] = false;
        intFunc[intNum]();
      }
    }
  }
#endif // EXTERNAL_NUM_INTERRUPTS
}

void CFI_DigitalInputFeature::noInterrupts()
{
    interruptsEnabled = false;
}

