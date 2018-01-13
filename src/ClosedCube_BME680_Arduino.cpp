/*

Arduino Library for Bosch Sensortec BME680 Environment Server
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2017 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


#ifdef ARDUINO
#include <Wire.h>
#include "ClosedCube_BME680_Arduino.h"


void ClosedCube_BME680_Arduino::readBytes(uint8_t cmd, uint8_t* rdata, uint8_t len) {
	Wire.beginTransmission(_address);
	Wire.write(cmd);
	Wire.endTransmission();

	Wire.requestFrom(_address, (uint8_t)len);
	Wire.readBytes(rdata, len);
}

uint8_t ClosedCube_BME680_Arduino::writeBytes(uint8_t* data, uint8_t len) {
	Wire.beginTransmission(_address);
	while (len--) {
		Wire.write(*data++);
	}
	return Wire.endTransmission();
}

#endif
