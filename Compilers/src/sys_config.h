/******************************************************************************
 *
 * $RCSfile: $
 * $Revision: $
 *
 * This module provides information about the project configuration
 * Copyright 2004, R O SoftWare
 * No guarantees, warrantees, or promises, implied or otherwise.
 * May be used for hobby or commercial purposes provided copyright
 * notice remains intact.
 *
 *****************************************************************************/
 
 /* modified by Martin Thomas */
 
// 5/2007 mt: adapted to LPC23xx/24xx 
 
#ifndef SYS_CONFIG_H__
#define SYS_CONFIG_H__

#include "app_types.h"
#include "LPC_REGS.h"

// some handy DEFINES
#ifndef FALSE
#define FALSE               0
#ifndef TRUE
#define TRUE                !FALSE
#endif
#endif

#ifndef BIT
#define BIT(n)              (1L << (n))
#endif


#define SW1_PIN FIO0PIN
#define SW1_BIT BIT(29)
#define SW2_PIN SW1_PIN
#define SW2_BIT BIT(18)

#define LED1_SET FIO0SET
#define LED1_DIR FIO0DIR
#define LED1_CLR FIO0CLR
#define LED1_PIN FIO0PIN
#define LED1_BIT BIT(21) /* MCI PWR */

#if 0
#define LED2_SET FIO1SET
#define LED2_DIR FIO1DIR
#define LED2_CLR FIO1CLR
#define LED2_BIT BIT(26) /* LCD BL */
#endif


#if 0
// declare functions and values from crt0.S & the linker control file
extern void reset(void);
// extern void exit(void);
extern void abort(void);
// maybe add interrupt vector addresses
#endif

#define HOST_BAUD_U0           (115200)
#define HOST_BAUD_U1           (115200)

#define WDOG()

// PLL setup values are computed within the LPC include file
// It relies upon the following defines
// PLL input is the XTAL at FOSC
// FCCO is FOSC * PLL_MUL * 2 / PLL_DIV
// 
#define FOSC                (12000000)  // Master Oscillator Freq.
#define PLL_MUL             (12)        // PLL Multiplier
#define PLL_DIV             (1)         // PLL Divider
#define CCLK_DIV            (4)         // PLL out -> CPU clock divider
#define CCLK                ( FCCO / CCLK_DIV ) // CPU Clock Freq.

// Pheripheral Bus Speed Divider
#define PBSD                4           // MUST BE 1, 2, or 4
#define PCLK                (CCLK / PBSD) // Pheripheal Bus Clock Freq.

// Do some value range testing
// TODO: check minimum for LPC23xx/24xx
#if ((FOSC < 10000000) || (FOSC > 25000000))
#error Fosc out of range (10MHz-25MHz)
#error correct and recompile
#endif

#if ((CCLK < 10000000) || (CCLK > 72000000))
// TODO: check minimum for LPC23xx/24xx
#error cclk out of range (10MHz-72MHz)
#error correct PLL_MUL and recompile
#endif

// "The resulting frequency must be in the range of 275 MHz to
// 550 MHz." (Manual p. 36)
#if ((FCCO < 275000000) || (FCCO > 550000000))
#error Fcco out of range (275MHz-550MHz)
#error internal algorithm error
#endif

#if ((PBSD != 1) && (PBSD != 2) && (PBSD != 4))
#error Pheripheal Bus Speed Divider (PBSD) illegal value (1, 2, or 4)
#endif

#define ROM_RUN

// The following ist not used in this example:
// Port Bit Definitions & Macros:    Description - initial conditions
// Port 0
#define P00_UNUSED_BIT      BIT(0)      // P0.00 unused - low output
#define P01_UNUSED_BIT      BIT(1)      // P0.01 unused - low output
#define P02_UNUSED_BIT      BIT(2)      // P0.02 unused - low output
#define P03_UNUSED_BIT      BIT(3)      // P0.03 unused - low output
#define P04_UNUSED_BIT      BIT(4)      // P0.04 unused - low output
#define P05_UNUSED_BIT      BIT(5)      // P0.05 unused - low output
#define P06_UNUSED_BIT      BIT(6)      // P0.06 unused - low output
#define P07_UNUSED_BIT      BIT(7)      // P0.06 unused - low output
#define P08_UNUSED_BIT      BIT(8)      // P0.08 unused - low output
#define P09_UNUSED_BIT      BIT(9)      // P0.09 unused - low output
#define P10_UNUSED_BIT      BIT(10)     // P0.10 unused - low output
#define P11_UNUSED_BIT      BIT(11)     // P0.11 unused - low output
#define P12_UNUSED_BIT      BIT(12)     // P0.12 unused - low output
#define P13_UNUSED_BIT      BIT(13)     // P0.13 unused - low output
#define P14_UNUSED_BIT      BIT(14)     // P0.14 unused - low output
#define P15_UNUSED_BIT      BIT(15)     // P0.15 unused - low output
#define P16_UNUSED_BIT      BIT(16)     // P0.16 unused - low output
#define P17_UNUSED_BIT      BIT(17)     // P0.17 unused - low output
#define P18_UNUSED_BIT      BIT(18)     // P0.18 unused - low output
#define P19_UNUSED_BIT      BIT(19)     // P0.19 unused - low output
#define P20_UNUSED_BIT      BIT(20)     // P0.20 unused - low output
#define P21_UNUSED_BIT      BIT(21)     // P0.21 unused - low output
#define P22_UNUSED_BIT      BIT(22)     // P0.22 unused - low output
#define P23_UNUSED_BIT      BIT(23)     // P0.23 unused - low output
#define P24_UNUSED_BIT      BIT(24)     // P0.24 unused - low output
#define P25_UNUSED_BIT      BIT(25)     // P0.25 unused - low output
#define P26_UNUSED_BIT      BIT(26)     // P0.26 unused - low output
#define P27_UNUSED_BIT      BIT(27)     // P0.27 unused - low output
#define P28_UNUSED_BIT      BIT(28)     // P0.28 unused - low output
#define P29_UNUSED_BIT      BIT(29)     // P0.29 unused - low output
#define P30_UNUSED_BIT      BIT(30)     // P0.30 unused - low output
#define P31_UNUSED_BIT      BIT(31)     // P0.31 unused - low output

// Port 1
// Port Bit Definitions & Macros:    Description - initial conditions
#define P1_00_UNUSED_BIT      BIT(0)      // P1_0.00 unused - low output
#define P1_01_UNUSED_BIT      BIT(1)      // P1_0.01 unused - low output
#define P1_02_UNUSED_BIT      BIT(2)      // P1_0.02 unused - low output
#define P1_03_UNUSED_BIT      BIT(3)      // P1_0.03 unused - low output
#define P1_04_UNUSED_BIT      BIT(4)      // P1_0.04 unused - low output
#define P1_05_UNUSED_BIT      BIT(5)      // P1_0.05 unused - low output
#define P1_06_UNUSED_BIT      BIT(6)      // P1_0.06 unused - low output
#define P1_07_UNUSED_BIT      BIT(7)      // P1_0.06 unused - low output
#define P1_08_UNUSED_BIT      BIT(8)      // P1_0.08 unused - low output
#define P1_09_UNUSED_BIT      BIT(9)      // P1_0.09 unused - low output
#define P1_10_UNUSED_BIT      BIT(10)     // P1_0.10 unused - low output
#define P1_11_UNUSED_BIT      BIT(11)     // P1_0.11 unused - low output
#define P1_12_UNUSED_BIT      BIT(12)     // P1_0.12 unused - low output
#define P1_13_UNUSED_BIT      BIT(13)     // P1_0.13 unused - low output
#define P1_14_UNUSED_BIT      BIT(14)     // P1_0.14 unused - low output
#define P1_15_UNUSED_BIT      BIT(15)     // P1_0.15 unused - low output
#define P1_16_UNUSED_BIT      BIT(16)     // P1_0.16 unused - low output
#define P1_17_UNUSED_BIT      BIT(17)     // P1_0.17 unused - low output
#define P1_18_UNUSED_BIT      BIT(18)     // P1_0.18 unused - low output
#define P1_19_UNUSED_BIT      BIT(19)     // P1_0.19 unused - low output
#define P1_20_UNUSED_BIT      BIT(20)     // P1_0.20 unused - low output
#define P1_21_UNUSED_BIT      BIT(21)     // P1_0.21 unused - low output
#define P1_22_UNUSED_BIT      BIT(22)     // P1_0.22 unused - low output
#define P1_23_UNUSED_BIT      BIT(23)     // P1_0.23 unused - low output
#define P1_24_UNUSED_BIT      BIT(24)     // P1_0.24 unused - low output
#define P1_25_UNUSED_BIT      BIT(25)     // P1_0.25 unused - low output
#define P1_26_UNUSED_BIT      BIT(26)     // P1_0.26 unused - low output
#define P1_27_UNUSED_BIT      BIT(27)     // P1_0.27 unused - low output
#define P1_28_UNUSED_BIT      BIT(28)     // P1_0.28 unused - low output
#define P1_29_UNUSED_BIT      BIT(29)     // P1_0.29 unused - low output
#define P1_30_UNUSED_BIT      BIT(30)     // P1_0.30 unused - low output
#define P1_31_UNUSED_BIT      BIT(31)     // P1_0.31 unused - low output


#define PIO_INPUT_BITS      (uint32_t) ( \
		0 )

#define PIO_ZERO_BITS       (uint32_t) ( \
		P00_UNUSED_BIT | \
		P01_UNUSED_BIT | \
		P02_UNUSED_BIT | \
		P03_UNUSED_BIT | \
		P04_UNUSED_BIT | \
		P05_UNUSED_BIT | \
		P06_UNUSED_BIT | \
		P07_UNUSED_BIT | \
		P08_UNUSED_BIT | \
		P09_UNUSED_BIT | \
		P10_UNUSED_BIT | \
		P11_UNUSED_BIT | \
		P12_UNUSED_BIT | \
		P13_UNUSED_BIT | \
		P14_UNUSED_BIT | \
		P15_UNUSED_BIT | \
		P16_UNUSED_BIT | \
		P16_UNUSED_BIT | \
		P17_UNUSED_BIT | \
		P18_UNUSED_BIT | \
		P19_UNUSED_BIT | \
		P20_UNUSED_BIT | \
		P21_UNUSED_BIT | \
		P22_UNUSED_BIT | \
		P23_UNUSED_BIT | \
		P24_UNUSED_BIT | \
		P25_UNUSED_BIT | \
		P26_UNUSED_BIT | \
		P27_UNUSED_BIT | \
		P28_UNUSED_BIT | \
		P29_UNUSED_BIT | \
		P30_UNUSED_BIT | \
		P31_UNUSED_BIT | \
		0 )

#define PIO_ONE_BITS        (uint32_t) ( \
		0 )

#define PIO_OUTPUT_BITS     (uint32_t) ( \
		PIO_ZERO_BITS | \
		PIO_ONE_BITS )

#endif
