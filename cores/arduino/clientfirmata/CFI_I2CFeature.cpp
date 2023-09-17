/*
  CFI_I2CFeature.cpp - ClientFirmata library
  Copyright (C) 2018 Immo Wache.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include "CFI_I2CFeature.h"
#include "CFI_ClientEncoder7Bit.h"

CFI_I2CFeature::CFI_I2CFeature(CFI_ClientFirmata& firmata) : _firmata(&firmata), _targetAddress(0),
    _inBuffer(NULL), _isAwaitingReply(false), _numIn(0), _requestId(0), _inCount(0)
{
    _firmata->addFeature(*this);
}

void CFI_I2CFeature::config(uint16_t delayTime, uint32_t clockFrequency, uint8_t sclPin, uint8_t sdaPin)
{
    byte buffer[11]{};

    buffer[0] = CFI_START_SYSEX;
    buffer[1] = CFI_I2C_CONFIG;
    buffer[2] = delayTime & 0x7F;
    buffer[3] = (delayTime >> 7) & 0x7F;
    buffer[4] = (clockFrequency >> 7) & 0x7F;
    buffer[5] = (clockFrequency >> 14) & 0x7F;
    buffer[6] = (clockFrequency >> 21) & 0x7F;
    buffer[7] = (clockFrequency >> 28) & 0x0F;
    buffer[8] = sclPin & 0x7F;
    buffer[9] = sdaPin & 0x7F;
    buffer[10] = CFI_END_SYSEX;
    _firmata->write(buffer, 14);
}

uint8_t CFI_I2CFeature::request(uint8_t targetAddress, uint8_t restartMode, uint8_t transferMode, uint8_t* outBuffer, uint8_t numOut, uint8_t* inBuffer, uint8_t numIn, int8_t targetRegister)
{
    _targetAddress = (uint8_t)(targetAddress & 0x7F);
    _requestId = 0;
    _numIn = numIn;
    _inBuffer = inBuffer;

    uint8_t addressMode = 0; // 0: 7-bit mode; 1: 10-bit mode
    uint8_t config = (restartMode & 0x01) << 6 | (addressMode & 0x01) << 5 |
        (transferMode & 0x03) << 3 | (_requestId & 0x03);

    _firmata->startSysex();
    _firmata->write(CFI_I2C_REQUEST);
    _firmata->write(_targetAddress);
    _firmata->write(config);
    switch (transferMode)
    {
    case CFI_I2C_WRITE:
        for (size_t i = 0; i < numOut; i++)
        {
            _firmata->sendValueAsTwo7bitBytes(outBuffer[i]);
        }
        break;
    case CFI_I2C_READ:
    case CFI_I2C_READ_CONTINUOUSLY:
        if (targetRegister != CFI_I2C_REGISTER_NOT_SPECIFIED)
        {
            _firmata->sendValueAsTwo7bitBytes(targetRegister);
        }
        _firmata->sendValueAsTwo7bitBytes(numIn);
        break;
    case CFI_I2C_STOP_READING:
    default:
        break;
    }
    _firmata->endSysex();

    if (transferMode == CFI_I2C_READ)
    {
        // Wait for I2C response from Firmata board
        _isAwaitingReply = true;
        while (_isAwaitingReply)
        {
            // ToDo: Add timeout logic
            _firmata->update();
        }
        // inBuffer was filled in handleSpiResponse(), see below
        return _inCount;
    }
    return 0;
}

void CFI_I2CFeature::setPinMode(byte pin, int mode)
{
    _firmata->setPinMode(pin, mode);
}

boolean CFI_I2CFeature::handleSysex(byte command, int argc, byte* argv)
{
    switch (command) {
    case CFI_I2C_REPLY:
        if (argc < 2)
        {
            CFI_DEBUG_PRINTLN(F("I2C reply: Empty message error"));
            return false;
        }
        handleI2cReply(argc, argv);
        return true;
    }
    return false;
}

void CFI_I2CFeature::handleI2cReply(byte argc, byte* argv)
{
    // Check for expected I2C reply
    if (!_isAwaitingReply)
	{
        CFI_DEBUG_PRINTLN(F("I2C reply: Not awaiting reply"));
		return;
	}
    _isAwaitingReply = false;

    // Check for cannel and device Id
	if (argv[0] != _targetAddress) {
        CFI_DEBUG_PRINT(F("I2C reply: Unknown target address received: "));
        CFI_DEBUG_PRINTLN(argv[0]);
		return;
	}
    // Check for request Id
    if (argv[1] != _requestId) {
        CFI_DEBUG_PRINT(F("I2C reply: Unknown requestId received: "));
        CFI_DEBUG_PRINTLN(argv[1]);
        return;
    }
    // Check for expected data length
    if (argc > _numIn * 2 + 4 || argc % 2 != 0) {
        CFI_DEBUG_PRINT(F("I2C reply: Wrong number of data bytes: "));
        CFI_DEBUG_PRINTLN(argc / 2 - 2);
        return;
    }
    uint8_t iRegister = argv[2] + (argv[3] << 7);
    _inCount = 0;
    for (size_t i = 4; i < argc; i += 2) {
        _inBuffer[i - 4] = argv[i] + (argv[i + 1] << 7);
        _inCount++;
    }
}

void CFI_I2CFeature::updateFeature()
{
}
