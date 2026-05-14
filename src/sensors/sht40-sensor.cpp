#include "sht40-sensor.h"
#include <Wire.h>

const uint8_t SHT40_ADDRESS = 0x44;

void initSHT40() {
    Wire.begin();
}

SHTReading readSHT40() {
    SHTReading reading;

    Wire.beginTransmission(SHT40_ADDRESS);
    Wire.write(0xFD);
    Wire.endTransmission();

    delay(10);
	
	uint8_t bytesReceived = Wire.requestFrom(SHT40_ADDRESS, 6); 
	if (bytesReceived != 6) {
		Serial.println("Incorrect byte size reading from SHT40…");
        reading.SHTValid = false;
		return reading;
	}
	
	uint8_t tempHigh = Wire.read();
	uint8_t tempLow  = Wire.read();
	Wire.read();
	
	uint8_t humHigh  = Wire.read();
	uint8_t humLow   = Wire.read();
	Wire.read();
	
	uint16_t rawTemp = tempHigh * 256 + tempLow;
	uint16_t rawHum = humHigh * 256 + humLow;
	
	reading.SHTTemp = -45 + 175 * (rawTemp / 65535.0);
	reading.SHTHum = 100 * (rawHum / 65535.0);

    if (reading.SHTTemp < -45 || reading.SHTTemp > 125 || reading.SHTHum < 0 || reading.SHTHum > 100) {
        reading.SHTValid = false;
        Serial.println("Error: SHT40 readings incorrect");
    } else { reading.SHTValid = true; }
	
	return reading;
}