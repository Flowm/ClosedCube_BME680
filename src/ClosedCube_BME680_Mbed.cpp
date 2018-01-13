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


#ifndef ARDUINO
#include "ClosedCube_BME680_Mbed.h"


uint8_t ClosedCube_BME680_Mbed::reset() {
	uint8_t ret = ClosedCube_BME680::reset();
	mem_page_cur = get_mem_page();
	return ret;
}

void ClosedCube_BME680_Mbed::readBytes(uint8_t cmd, uint8_t* rdata, uint8_t len) {
	if (cmd != BME680_REG_STATUS) {
		set_mem_page(cmd);
	}

	// SPI register reads have the msb set
	cmd = cmd | 0x80;

	cs = 0;
	spi.write((char*) &cmd, 1, NULL, 0);
	spi.write(NULL, 0, (char*) rdata, len);
	cs = 1;
}

uint8_t ClosedCube_BME680_Mbed::writeBytes(uint8_t* data, uint8_t len) {
	if (data[0] != BME680_REG_STATUS) {
		set_mem_page(data[0]);
	}

	// SPI register writes have the msb unset
	data[0] = data[0] & 0x7F;

	cs = 0;
	spi.write((char*) data, len, NULL, 0);
	cs = 1;

	return 0;
}

uint8_t ClosedCube_BME680_Mbed::get_mem_page() {
	return readByte(BME680_REG_STATUS) & BME680_MEM_PAGE_MSK;
}

/**
 * SPI reads/writes to registers with the msb set require switching to a
 * different register page as the msb is used as a r/w indicator for SPI
 */
void ClosedCube_BME680_Mbed::set_mem_page(uint8_t reg_addr) {
	uint8_t mem_page_req;

	if (reg_addr > 0x7F) {
		mem_page_req = 0 << 4; // BME680_MEM_PAGE1;
	} else {
		mem_page_req = 1 << 4; // BME680_MEM_PAGE0;
	}

	if (mem_page_cur != mem_page_req) {
		uint8_t wdata[] = {
			BME680_REG_STATUS,
			mem_page_req
		};
		writeBytes(wdata, sizeof(wdata));

		mem_page_cur = get_mem_page();
		//printf("DBG: Addr:%02X WPage:%02X CPage:%02X SWITCHED\r\n", reg_addr, mem_page_req, mem_page_cur);
	}
}

#endif
