#include "stdint.h"
#include "type.h"
#include "power.h"

uint16_t voltageValues[4] = {0,
                             0,
                             0,
                             0};

//*****************************************************************************
//* Gets the current from each face
//*  returns the current in milliamps on the +5v rail
//*  range: -2000 to 1700 mA
//*  accuracy: +-50mA 
//*  Current leaving is a negative number, while current incoming is a positive number. 
int getCurrent(uint8_t portNum) {

long current;

    current = voltageValues[portNum];

	/* Convert to millamps */
	current = (-1800 * ((long)current-542)) / 467;

return current;
}

//****************************************************************************
//* set the voltage reading from the ADC
void setVoltage(uint8_t portNum, uint16_t adcValue) {
    voltageValues[portNum] = adcValue;
}
