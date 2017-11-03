/**************************************************************************************

This is example for ClosedCube HDC1080 Humidity and Temperature Sensor breakout booard

Initial Date: 15-Sep-2017

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SCL to A5
SDA to A4
GND to common ground

Written by AA for ClosedCube

MIT License

**************************************************************************************/

#include <Wire.h>
#include "ClosedCube_BME680.h"

ClosedCube_BME680 bme680;

void setup()
{
	Wire.begin();

	Serial.begin(9600);
	Serial.println("ClosedCube BME680 ([T]empeature,[P]ressure,[H]umidity) Arduino Test");

	bme680.init(0x77); // I2C address: 0x76 or 0x77
	bme680.reset();

	Serial.print("Chip ID=0x");
	Serial.println(bme680.getChipID(), HEX);

	// oversampling: humidity = x1, temperature = x2, pressure = x16
	bme680.setOversampling(BME680_OVERSAMPLING_X1, BME680_OVERSAMPLING_X2, BME680_OVERSAMPLING_X16);
	bme680.setForcedMode();
}

void loop()
{
	ClosedCube_BME680_Status status = readAndPrintStatus();
	if (status.newDataFlag) {
		Serial.print("result: ");
		float temp = bme680.readTemperature();
		float pres = bme680.readPressure();
		float hum = bme680.readHumidity();

		Serial.print("T=");
		Serial.print(temp);
		Serial.print("C, RH=");
		Serial.print(hum);
		Serial.print("%, P=");
		Serial.print(pres);
		Serial.print("mbar");

		Serial.println();

		delay(1000); // let's do nothing and wait a bit before perform next measurements

		bme680.setForcedMode();
	} else {
		delay(200); // sensor data not yet ready
	}
}

ClosedCube_BME680_Status readAndPrintStatus() {
	ClosedCube_BME680_Status status = bme680.readStatus();
	Serial.print("status: (");
	Serial.print(status.newDataFlag);
	Serial.print(",");
	Serial.print(status.measuringStatusFlag);
	Serial.print(",");
	Serial.print(status.gasMeasuringStatusFlag);
	Serial.print(",");
	Serial.print(status.gasMeasurementIndex);
	Serial.println(") newDataFlag,StatusFlag,GasFlag,GasIndex");
	return status;
}
