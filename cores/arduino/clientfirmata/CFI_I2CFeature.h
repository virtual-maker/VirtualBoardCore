/*
  CFI_I2CFeature.h - ClientFirmata library
  Copyright (C) 2022 Immo Wache.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef CFI_I2CFeature_h
#define CFI_I2CFeature_h

#include <inttypes.h>
#include "CFI_ClientFirmata.h"
#include "CFI_ClientFirmataFeature.h"

#define CFI_I2C_WRITE                   0
#define CFI_I2C_READ                    1
#define CFI_I2C_READ_CONTINUOUSLY       2
#define CFI_I2C_STOP_READING            3

#define CFI_I2C_STOP_TX                 1
#define CFI_I2C_RESTART_TX              0
#define CFI_I2C_MAX_QUERIES             8
#define CFI_I2C_REGISTER_NOT_SPECIFIED  -1

#define MAX_I2C_BUF_SIZE 32


class CFI_ClientFirmata;

class CFI_I2CFeature : public CFI_ClientFirmataFeature
{
public:
    CFI_I2CFeature(CFI_ClientFirmata& firmata);

    void config(uint16_t delayTime, uint32_t clockFrequency = 100000ul, uint8_t sclPin = 255, uint8_t sdaPin = 255);
    uint8_t request(uint8_t targetAddress, uint8_t restartMode, uint8_t transferMode, uint8_t* outBuffer, uint8_t numOut, uint8_t* inBuffer, uint8_t numIn, int8_t targetRegister = CFI_I2C_REGISTER_NOT_SPECIFIED);

    void setPinMode(byte pin, int mode);
    boolean handleSysex(byte command, int argc, byte* argv);
    void updateFeature();

private:
    void handleI2cReply(byte argc, byte* argv);
    
    CFI_ClientFirmata* _firmata;

    bool _isAwaitingReply;
    uint8_t _targetAddress;
    uint8_t _requestId;
    uint8_t _numIn;
    uint8_t* _inBuffer;
    uint8_t _inCount;
};

#endif
