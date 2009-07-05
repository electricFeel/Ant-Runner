/******************************************************************************/
/* IAP In-System Application Programming Demo                                 */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
#include <stdio.h>                         /* standard I/O .h-file */
#include <LPC23xx.H>                       /* LPC23xx definitions  */
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "Serial.h"
#include "sbl_iap.h"
#include "fio.h"

#define LED_FIOPIN  FIO2PIN
#define LED_FIOSET  FIO2SET
#define LED_FIOCLR  FIO2CLR

#define LED_GREEN_MASK    (1UL<<0)
#define LED_RED_MASK      (1UL<<1)
#define LED_BLUE_MASK     (1UL<<2)

#define LED_NORTH_MASK (1UL<<3)
#define LED_SOUTH_MASK (1UL<<4)
#define LED_WEST_MASK  (1UL<<5)
#define LED_EAST_MASK  (1UL<<26)

#define kMCUId "lpc2368"
#define kApplicationStartAddr  0x00004000
#define kApplicationEndAddr    0x0007BFFF
#define kSPM_PAGE_SIZE         512
#define kUSART_RX_BUFFER_SIZE  kSPM_PAGE_SIZE               
#define kSoftwareIdentifier     "AVRBOOT"
#define kSoftwareVersionHigh   '0'
#define kSoftwareVersionLow    '7'

#define kDevType               0x74         //mega645
#define kSignatureByte3        0x1E         //mega2560
#define kSignatureByte2        0x98         //mega2560
#define kSignatureByte1        0x01         //mega2560      

extern void sysInit(void);
extern int getCurrent(uint8_t portNum);

void butterflyService(void);
char BufferLoad(unsigned int size, unsigned char memType);
void BlockRead(unsigned int size, unsigned char memType);

unsigned int gAddress=0; // butterfly address 
unsigned int gAddressPgm=kApplicationStartAddr;   //address to program
unsigned char gBuffer[kUSART_RX_BUFFER_SIZE];  //RAM buffer for  
unsigned char gDevice;
unsigned char gDevType;

volatile unsigned int purge;
unsigned int num=0;

static void time_waste( DWORD dv );

//unsigned int datax[80000] __attribute__((section(".text"))); 


void ledSpin()
{
    for (purge=0;purge<600000; purge++)
    {
        ;
    }

    num++;
    if (num==4)
    {
        num=0;
    }

    switch (num)
    {
    case 0:

        FIO2CLR |= LED_NORTH_MASK;
        FIO2SET |= LED_SOUTH_MASK;
        FIO2SET |= LED_WEST_MASK;
        FIO1SET |= LED_EAST_MASK;
        break;

    case 1:
        FIO2SET |= LED_NORTH_MASK;
        FIO2CLR |= LED_SOUTH_MASK;
        FIO2SET |= LED_WEST_MASK;
        FIO1SET |= LED_EAST_MASK;
        break;

    case 2:
        FIO2SET |= LED_NORTH_MASK;
        FIO2SET |= LED_SOUTH_MASK;
        FIO2CLR |= LED_WEST_MASK;
        FIO1SET |= LED_EAST_MASK;
        break;
    case 3:
        FIO2SET |= LED_NORTH_MASK;
        FIO2SET |= LED_SOUTH_MASK;
        FIO2SET |= LED_WEST_MASK;
        FIO1CLR |= LED_EAST_MASK;
        break;
    }
}

int main (void)  {	 

	sysInit();
             
    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_RED_MASK );
    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_GREEN_MASK );
    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_BLUE_MASK );

    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_NORTH_MASK );
    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_SOUTH_MASK );
    GPIOInit( 2, FAST_PORT, DIR_OUT, LED_WEST_MASK );
    GPIOInit( 1, FAST_PORT, DIR_OUT, LED_EAST_MASK );


    FIO2PIN |= LED_RED_MASK;
    FIO2PIN |= LED_GREEN_MASK;
    FIO2PIN |= LED_BLUE_MASK;
    
    FIO2PIN |= LED_NORTH_MASK;
    FIO2PIN |= LED_SOUTH_MASK;
    FIO2PIN |= LED_WEST_MASK;
    FIO1PIN |= LED_EAST_MASK;

    setup();

   while(1)
   {
       ledSpin();
       loop();
   }

}