/*****************************************************************************/
/* STARTUP.S: Startup file for Blinky Example                                */
/*****************************************************************************/
/* Version: CodeSourcery Sourcery G++ Lite (with CS3)                        */
/*****************************************************************************/


/* 
//*** <<< Use Configuration Wizard in Context Menu >>> *** 
*/


/*
 *  The STARTUP.S code is executed after CPU Reset. This file may be 
 *  translated with the following SET symbols. In uVision these SET 
 *  symbols are entered under Options - ASM - Define.
 *
 *  REMAP: when set the startup code initializes the register MEMMAP 
 *  which overwrites the settings of the CPU configuration pins. The 
 *  startup and interrupt vectors are remapped from:
 *     0x00000000  default setting (not remapped)
 *     0x40000000  when RAM_MODE is used
 *
 *  RAM_MODE: when set the device is configured for code execution
 *  from on-chip RAM starting at address 0x40000000. 
 */


# Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

        .equ    Mode_USR,       0x10
        .equ    Mode_FIQ,       0x11
        .equ    Mode_IRQ,       0x12
        .equ    Mode_SVC,       0x13
        .equ    Mode_ABT,       0x17
        .equ    Mode_UND,       0x1B
        .equ    Mode_SYS,       0x1F

        .equ    I_Bit,          0x80    /* when I bit is set, IRQ is disabled */
        .equ    F_Bit,          0x40    /* when F bit is set, FIQ is disabled */


/*
// <h> Stack Configuration (Stack Sizes in Bytes)
//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
//   <o1> Abort Mode          <0x0-0xFFFFFFFF:8>
//   <o2> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
//   <o3> Interrupt Mode      <0x0-0xFFFFFFFF:8>
//   <o4> Supervisor Mode     <0x0-0xFFFFFFFF:8>
//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
// </h>
*/

        .equ    UND_Stack_Size, 0x00000000
		.equ    SVC_Stack_Size, 0x00000200
        .equ    ABT_Stack_Size, 0x00000000
        .equ    FIQ_Stack_Size, 0x00000000
        .equ    IRQ_Stack_Size, 0x00000100
        .equ    USR_Stack_Size, 0x00000000

        .section ".stack", "w"
        .align  3
        .globl  __cs3_stack_mem
        .globl  __cs3_stack_size
__cs3_stack_mem:
        .if     USR_Stack_Size
        .space  USR_Stack_Size
        .endif
        .if     SVC_Stack_Size
        .space  SVC_Stack_Size
        .endif
        .if     IRQ_Stack_Size
        .space  IRQ_Stack_Size
        .endif
        .if     FIQ_Stack_Size
        .space  FIQ_Stack_Size
        .endif
        .if     ABT_Stack_Size
        .space  ABT_Stack_Size
        .endif
        .if     UND_Stack_Size
        .space  UND_Stack_Size
        .endif
        .size   __cs3_stack_mem,  . - __cs3_stack_mem
        .set    __cs3_stack_size, . - __cs3_stack_mem


/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

        .equ    Heap_Size,      0x00000000

        .section ".heap", "w"
        .align  3
        .globl  __cs3_heap_start
        .globl  __cs3_heap_end
__cs3_heap_start:
        .if     Heap_Size
        .space  Heap_Size
        .endif
__cs3_heap_end:

# Exception Vectors

        .arm

        .section ".cs3.interrupt_vector"
        .globl  __cs3_interrupt_vector_arm
        .type   __cs3_interrupt_vector_arm, %object
__cs3_interrupt_vector_arm:

                LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            /* Reserved Vector */
#               LDR     PC, IRQ_Addr
#                LDR     PC, [PC, #-0x0FF0]     /* Vector from VicVectAddr */
          		LDR     PC, [PC, #-0x0120]     /* Vector from VicVectAddr */
                LDR     PC, FIQ_Addr

Reset_Addr:     .word   __cs3_reset_arm
Undef_Addr:     .word   Undef_Handler
SWI_Addr:       .word   SWI_Handler
PAbt_Addr:      .word   PAbt_Handler
DAbt_Addr:      .word   DAbt_Handler
                .word   0                      /* Reserved Address */
IRQ_Addr:       .word   IRQ_Handler
FIQ_Addr:       .word   FIQ_Handler

        .size   __cs3_interrupt_vector_arm, . - __cs3_interrupt_vector_arm


# Exception Handlers

        .section ".text"

        .weak   Undef_Handler
        .type   Undef_Handler, %function
Undef_Handler:  B       Undef_Handler
        .size   Undef_Handler, . - Undef_Handler

        .weak   SWI_Handler
        .type   SWI_Handler, %function
SWI_Handler:    B       SWI_Handler
        .size   SWI_Handler, . - SWI_Handler

        .weak   PAbt_Handler
        .type   PAbt_Handler, %function
PAbt_Handler:   B       PAbt_Handler
        .size   PAbt_Handler, . - PAbt_Handler

        .weak   DAbt_Handler
        .type   DAbt_Handler, %function
DAbt_Handler:   B       DAbt_Handler
        .size   DAbt_Handler, . - DAbt_Handler

        .weak   IRQ_Handler
        .type   IRQ_Handler, %function
IRQ_Handler:    B       IRQ_Handler
        .size   IRQ_Handler, . - IRQ_Handler

        .weak   FIQ_Handler
        .type   FIQ_Handler, %function
FIQ_Handler:    B       FIQ_Handler
        .size   FIQ_Handler, . - FIQ_Handler


# Reset Handler

        .section .cs3.reset,"x",%progbits
        .globl  __cs3_reset_arm
        .type   __cs3_reset_arm, %function
__cs3_reset_arm:
        .fnstart

# Initialise Interrupt System
#  ...


# Setup Stack for each mode

                LDR     R0, =__cs3_stack

#  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

#  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

#  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

#  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

#  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

#  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0

#  Setup a default Stack Limit (when compiled with "-mapcs-stack-check")
                SUB     SL, SP, #USR_Stack_Size


# Enter the C code

        .globl  _start
_start:
                LDR     R0,=__cs3_start_c
                BX      R0


        .fnend
        .size   __cs3_reset_arm, . - __cs3_reset_arm


        .end
