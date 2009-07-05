/*****************************************************************************
 *   fio.h:  Header file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
 ******************************************************************************/

// extended version with "mask"-parameter to init

#ifndef __FIO_H 
#define __FIO_H

#include "type.h"

/* bit 0 in SCS register, port 0/1 are regular ports when bit 0 
is 0,  fast ports when bit 0 is 1. */
#define GPIOM                          0x00000001

/* see master definition file lpc230x.h for more details */
#define REGULAR_PORT_DIR_BASE          GPIO_BASE_ADDR + 0x08
#define REGULAR_PORT_DIR_INDEX         0x10

#define HS_PORT_DIR_BASE               FIO_BASE_ADDR + 0x00
#define HS_PORT_DIR_INDEX              0x20

#define FAST_PORT          0x01
#define REGULAR_PORT       0x02

#define DIR_OUT            0x01
#define DIR_IN             0x02

extern void GPIOInit( DWORD PortNum, DWORD PortType, DWORD PortDir, DWORD Mask);

#endif /* end __FIO_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
