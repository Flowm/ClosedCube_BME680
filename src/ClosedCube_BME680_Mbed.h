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


#ifndef _CLOSEDCUBE_BME680_MBED_h
#define _CLOSEDCUBE_BME680_MBED_h

#include <mbed.h>
#include "ClosedCube_BME680.h"

#define BME680_MEM_PAGE_MSK 0x10

class ClosedCube_BME680_Mbed : public ClosedCube_BME680 {

public:
    ClosedCube_BME680_Mbed(SPI &spi, DigitalOut &cs) :
        spi(spi),
        cs(cs)
    {
        mem_page_cur = get_mem_page();
    }

    uint8_t reset();

private:
    virtual void readBytes(uint8_t cmd, uint8_t* rdata, uint8_t len);
    virtual uint8_t writeBytes(uint8_t* data, uint8_t len);

    uint8_t get_mem_page();
    void set_mem_page(uint8_t reg_addr);

    uint8_t mem_page_cur;

    SPI& spi;
    DigitalOut& cs;
};

#endif
