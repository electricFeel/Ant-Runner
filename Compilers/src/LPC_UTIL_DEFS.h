/* "ripped from the R O Software example and extended by mthomas */

#ifndef LPC_UTILDEFS_H
#define LPC_UTILDEFS_H

///////////////////////////////////////////////////////////////////////////////
// CLKSRC defines
#define CLKSRC_INT_RC    (0x00)
#define CLKSRC_MAIN_OSC  (0x01)
#define CLKSRC_MIN_RTC   (0x02)

///////////////////////////////////////////////////////////////////////////////
// SCS defines
#define SCS_GPIOM        (1UL<<0)
#define SCS_EMC_RST_DIS  (1UL<<1)
#define SCS_MCIPWR       (1UL<<3)
#define SCS_OSCRANGE     (1UL<<4)
#define SCS_OSCEN        (1UL<<5)
#define SCS_OSCSTAT      (1UL<<6)

///////////////////////////////////////////////////////////////////////////////
// MAM defines
#define MAMCR_OFF     0
#define MAMCR_PART    1
#define MAMCR_FULL    2

#define MAMTIM_CYCLES (((CCLK) + 19999999) / 20000000)

///////////////////////////////////////////////////////////////////////////////
// MEMMAP defines
#define MEMMAP_BBLK   0                 // Interrupt Vectors in Boot Block
#define MEMMAP_FLASH  1                 // Interrupt Vectors in Flash
#define MEMMAP_SRAM   2                 // Interrupt Vectors in SRAM

///////////////////////////////////////////////////////////////////////////////
// PLL defines & computations
// Compute the value of PLL_DIV and test range validity
// FOSC & PLL_MUL should be defined in project configuration file (config.h)
//#ifndef CCLK
//#define CCLK          (FOSC * PLL_MUL)  // CPU Clock Freq.
//#endif

// #define FCCO_MAX      (320000000)       // Max CC Osc Freq.
// #define PLL_DIV       (FCCO_MAX / (2 * CCLK)) // PLL Divider
#define FCCO          (FOSC * PLL_MUL * 2 / PLL_DIV) // CC Osc. Freq.

// PLLCON Register Bit Definitions
#define PLLCON_PLLE   (1 << 0)          // PLL Enable
#define PLLCON_PLLC   (1 << 1)          // PLL Connect

// PLLSTAT Register Bit Definitions
#define PLLSTAT_PLLE  (1UL<<24)
#define PLLSTAT_PLLC  (1UL<<25)
#define PLLSTAT_PLOCK (1UL<<26)

// PLLCFG Register Bit Definitions
#define PLLCFG_MSEL   ((PLL_MUL - 1) << 0) // PLL Multiplier
// #define PLLCFG_PSEL   ((PLL_DIV - 1) << 5) // PLL Divider
#define PLLCFG_NSEL   ((PLL_DIV - 1) << 16UL) // PLL Divider

// PLLSTAT Register Bit Definitions
#define PLLSTAT_LOCK  (1 << 10)         // PLL Lock Status Bit

#define CCLKCFG_CCLKSEL_VAL ((CCLK_DIV -1 ) << 0UL )

///////////////////////////////////////////////////////////////////////////////
// VPBDIV defines & computations
#define VPBDIV_VALUE  (PBSD & 0x03)     // VPBDIV value

///////////////////////////////////////////////////////////////////////////////
// SCS defines - mthomas
#define GPIO0M        (1 << 0)
#define GPIO1M        (1 << 1)

///////////////////////////////////////////////////////////////////////////////
// UART defines

#define U0_TX_PINSEL_REG  PINSEL0
#define U0_TX_PINSEL     (1UL<<4)  /* PINSEL0 Value for UART0 TX */
#define U0_TX_PINMASK    (3UL<<4)  /* PINSEL0 Mask  for UART0 RX */
#define U0_RX_PINSEL_REG  PINSEL0
#define U0_RX_PINSEL     (1UL<<6)  /* PINSEL0 Value for UART0 TX */
#define U0_RX_PINMASK    (3UL<<6)  /* PINSEL0 Mask  for UART0 RX */

#define U1_TX_PINSEL_REG  PINSEL0
#define U1_TX_PINSEL     (1UL<<30)  /* PINSEL0 Value for UART0 TX */
#define U1_TX_PINMASK    (3UL<<30)  /* PINSEL0 Mask  for UART0 RX */
#define U1_RX_PINSEL_REG  PINSEL1
#define U1_RX_PINSEL     (1UL<<0)  /* PINSEL0 Value for UART0 TX */
#define U1_RX_PINMASK    (3UL<<0)  /* PINSEL0 Mask  for UART0 RX */

// Interrupt Enable Register bit definitions
#define UIER_RBR           (1UL << 0)    // (UIER_ERBFI) Enable Receive Data Available Interrupt
#define UIER_THRE          (1UL << 1)    // (UIER_ETBEI) Enable Transmit Holding Register Empty Interrupt
#define UIER_RX_LINE_STAT  (1UL << 2)    // (UIER_ELSI) Enable Receive Line Status Interrupt
#define UIER_MODEM_STAT_INT_EN (1UL<<3)  // (UIER_EDSSI) 
#define UIER_CTS_INT_ENT   (1UL << 7)    
#define UIER_ABTOIntEn     (1UL << 8)
#define UIER_ABE0IntEn     (1UL << 9)

// Interrupt ID Register bit definitions
#define UIIR_NO_INT         (1 << 0)    // NO INTERRUPTS PENDING if set 
#define UIIR_MS_INT         (0 << 1)    // MODEM Status
#define UIIR_THRE_INT       (1 << 1)    // Transmit Holding Register Empty
#define UIIR_RDA_INT        (2 << 1)    // Receive Data Available
#define UIIR_RLS_INT        (3 << 1)    // Receive Line Status
#define UIIR_CTI_INT        (6 << 1)    // Character Timeout Indicator
#define UIIR_ID_MASK        0x0E
#define UIIR_FIFO_ENABLE    (1<<6)
#define UIIR_ABEOInt        (1<<8)
#define UIIR_ABTOInt        (1<<9)

// FIFO Control Register bit definitions
#define UFCR_FIFO_ENABLE    (1 << 0)    // FIFO Enable
#define UFCR_RX_FIFO_RESET  (1 << 1)    // Reset Receive FIFO
#define UFCR_TX_FIFO_RESET  (1 << 2)    // Reset Transmit FIFO
#define UFCR_FIFO_TRIG1     (0 << 6)    // Trigger @ 1 character in FIFO
#define UFCR_FIFO_TRIG4     (1 << 6)    // Trigger @ 4 characters in FIFO
#define UFCR_FIFO_TRIG8     (2 << 6)    // Trigger @ 8 characters in FIFO
#define UFCR_FIFO_TRIG14    (3 << 6)    // Trigger @ 14 characters in FIFO

// Line Control Register bit definitions
#define ULCR_CHAR_5         (0 << 0)    // 5-bit character length
#define ULCR_CHAR_6         (1 << 0)    // 6-bit character length
#define ULCR_CHAR_7         (2 << 0)    // 7-bit character length
#define ULCR_CHAR_8         (3 << 0)    // 8-bit character length
#define ULCR_STOP_1         (0 << 2)    // 1 stop bit
#define ULCR_STOP_2         (1 << 2)    // 2 stop bits
#define ULCR_PAR_NO         (0 << 3)    // No Parity
#define ULCR_PAR_ODD        (1 << 3)    // Odd Parity
#define ULCR_PAR_EVEN       (3 << 3)    // Even Parity
#define ULCR_PAR_MARK       (5 << 3)    // MARK "1" Parity
#define ULCR_PAR_SPACE      (7 << 3)    // SPACE "0" Paruty
#define ULCR_BREAK_ENABLE   (1 << 6)    // Output BREAK line condition
#define ULCR_DLAB_ENABLE    (1 << 7)    // Enable Divisor Latch Access

// Modem Control Register bit definitions
#define UMCR_DTR            (1 << 0)    // Data Terminal Ready
#define UMCR_RTS            (1 << 1)    // Request To Send
#define UMCR_LB             (1 << 4)    // Loopback

// Line Status Register bit definitions
#define ULSR_RDR            (1 << 0)    // Receive Data Ready
#define ULSR_OE             (1 << 1)    // Overrun Error
#define ULSR_PE             (1 << 2)    // Parity Error
#define ULSR_FE             (1 << 3)    // Framing Error
#define ULSR_BI             (1 << 4)    // Break Interrupt
#define ULSR_THRE           (1 << 5)    // Transmit Holding Register Empty
#define ULSR_TEMT           (1 << 6)    // Transmitter Empty
#define ULSR_RXFE           (1 << 7)    // Error in Receive FIFO
#define ULSR_ERR_MASK       0x1E

// Modem Status Register bit definitions
#define UMSR_DCTS           (1 << 0)    // Delta Clear To Send
#define UMSR_DDSR           (1 << 1)    // Delta Data Set Ready
#define UMSR_TERI           (1 << 2)    // Trailing Edge Ring Indicator
#define UMSR_DDCD           (1 << 3)    // Delta Data Carrier Detect
#define UMSR_CTS            (1 << 4)    // Clear To Send
#define UMSR_DSR            (1 << 5)    // Data Set Ready
#define UMSR_RI             (1 << 6)    // Ring Indicator
#define UMSR_DCD            (1 << 7)    // Data Carrier Detect

///////////////////////////////////////////////////////////////////////////////
// TIMER defines

// Timer Interrupt Register Bit Definitions
#define TIR_MR0I    (1 << 0)            // Interrupt flag for match channel 0
#define TIR_MR1I    (1 << 1)            // Interrupt flag for match channel 1
#define TIR_MR2I    (1 << 2)            // Interrupt flag for match channel 2
#define TIR_MR3I    (1 << 3)            // Interrupt flag for match channel 3
#define TIR_CR0I    (1 << 4)            // Interrupt flag for capture channel 0 event
#define TIR_CR1I    (1 << 5)            // Interrupt flag for capture channel 1 event
#define TIR_CR2I    (1 << 6)            // Interrupt flag for capture channel 2 event
#define TIR_CR3I    (1 << 7)            // Interrupt flag for capture channel 3 event

// PWM Interrupt Register Bit Definitions
#define PWMIR_MR0I  (1 << 0)            // Interrupt flag for match channel 0
#define PWMIR_MR1I  (1 << 1)            // Interrupt flag for match channel 1
#define PWMIR_MR2I  (1 << 2)            // Interrupt flag for match channel 2
#define PWMIR_MR3I  (1 << 3)            // Interrupt flag for match channel 3
#define PWMIR_MR4I  (1 << 8)            // Interrupt flag for match channel 4
#define PWMIR_MR5I  (1 << 9)            // Interrupt flag for match channel 5
#define PWMIR_MR6I  (1 << 10)           // Interrupt flag for match channel 6
#define PWMIR_MASK  (0x070F)

// Timer Control Register Bit Definitions
#define TCR_ENABLE  (1 << 0)
#define TCR_RESET   (1 << 1)

// PWM Control Register Bit Definitions
#define PWMCR_ENABLE (1 << 0)
#define PWMCR_RESET (1 << 1)

// Timer Match Control Register Bit Definitions
#define TMCR_MR0_I  (1 << 0)            // Enable Interrupt when MR0 matches TC
#define TMCR_MR0_R  (1 << 1)            // Enable Reset of TC upon MR0 match
#define TMCR_MR0_S  (1 << 2)            // Enable Stop of TC upon MR0 match
#define TMCR_MR1_I  (1 << 3)            // Enable Interrupt when MR1 matches TC
#define TMCR_MR1_R  (1 << 4)            // Enable Reset of TC upon MR1 match
#define TMCR_MR1_S  (1 << 5)            // Enable Stop of TC upon MR1 match
#define TMCR_MR2_I  (1 << 6)            // Enable Interrupt when MR2 matches TC
#define TMCR_MR2_R  (1 << 7)            // Enable Reset of TC upon MR2 match
#define TMCR_MR2_S  (1 << 8)            // Enable Stop of TC upon MR2 match
#define TMCR_MR3_I  (1 << 9)            // Enable Interrupt when MR3 matches TC
#define TMCR_MR3_R  (1 << 10)           // Enable Reset of TC upon MR3 match
#define TMCR_MR3_S  (1 << 11)           // Enable Stop of TC upon MR3 match

// Timer Capture Control Register Bit Definitions
#define TCCR_CR0_R (1 << 0)            // Enable Rising edge on CAPn.0 will load TC to CR0
#define TCCR_CR0_F (1 << 1)            // Enable Falling edge on CAPn.0 will load TC to CR0
#define TCCR_CR0_I (1 << 2)            // Enable Interrupt on load of CR0
#define TCCR_CR1_R (1 << 3)            // Enable Rising edge on CAPn.1 will load TC to CR1
#define TCCR_CR1_F (1 << 4)            // Enable Falling edge on CAPn.1 will load TC to CR1
#define TCCR_CR1_I (1 << 5)            // Enable Interrupt on load of CR1
#define TCCR_CR2_R (1 << 6)            // Enable Rising edge on CAPn.2 will load TC to CR2
#define TCCR_CR2_F (1 << 7)            // Enable Falling edge on CAPn.2 will load TC to CR2
#define TCCR_CR2_I (1 << 8)            // Enable Interrupt on load of CR2
#define TCCR_CR3_R (1 << 9)            // Enable Rising edge on CAPn.3 will load TC to CR3
#define TCCR_CR3_F (1 << 10)           // Enable Falling edge on CAPn.3 will load TC to CR3
#define TCCR_CR3_I (1 << 11)           // Enable Interrupt on load of CR3

#if 0
///////////////////////////////////////////////////////////////////////////////
// VIC defines

// VIC Channel Assignments
#define VIC_WDT         0
#define VIC_TIMER0      4
#define VIC_TIMER1      5
#define VIC_UART0       6
#define VIC_UART1       7
#define VIC_PWM         8
#define VIC_PWM0        8
#define VIC_I2C         9
#define VIC_SPI         10
#define VIC_SPI0        10
#define VIC_SPI1        11
#define VIC_PLL         12
#define VIC_RTC         13
#define VIC_EINT0       14
#define VIC_EINT1       15
#define VIC_EINT2       16
#define VIC_EINT3       17
#define VIC_ADC         18

// Vector Control Register bit definitions
#define VIC_ENABLE      (1 << 5)

// Convert Channel Number to Bit Value
#define VIC_BIT(chan)   (1L << (chan))

#endif

#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX 0x200
#define VECT_PRIO_INDEX 0x200

#endif

