#ifndef _POWER_H_
#define _POWER_H_

int  getCurrent(uint8_t portNum);
void setVoltage(uint8_t portNum, uint16_t adcValue);

#endif
