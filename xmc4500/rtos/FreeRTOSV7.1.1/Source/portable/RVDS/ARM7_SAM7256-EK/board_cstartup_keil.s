; * ----------------------------------------------------------------------------
; *         ATMEL Microcontroller Software Support 
; * ----------------------------------------------------------------------------
; * Copyright (c) 2008, Atmel Corporation
; *
; * All rights reserved.
; *
; * Redistribution and use in source and binary forms, with or without
; * modification, are permitted provided that the following conditions are met:
; *
; * - Redistributions of source code must retain the above copyright notice,
; * this list of conditions and the disclaimer below.
; *
; * Atmel's name may not be used to endorse or promote products derived from
; * this software without specific prior written permission.
; *
; * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
; * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
; * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
; * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
; * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
; * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
; * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
; * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; * ----------------------------------------------------------------------------


;     KEIL startup file for AT91SAM7X microcontrollers.

; ------------------------------------------------------------------------------
;          Definitions
; ------------------------------------------------------------------------------

; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

ARM_MODE_USR        EQU     0x10
ARM_MODE_FIQ        EQU     0x11
ARM_MODE_IRQ        EQU     0x12
ARM_MODE_SVC        EQU     0x13
ARM_MODE_ABT        EQU     0x17
ARM_MODE_UND        EQU     0x1B
ARM_MODE_SYS        EQU     0x1F

I_BIT               EQU     0x80            ; when I bit is set, IRQ is disabled
F_BIT               EQU     0x40            ; when F bit is set, FIQ is disabled

AT91C_BASE_AIC      EQU     0xFFFFF000
AIC_IVR             EQU     0x100
AIC_EOICR           EQU     0x130

UND_Stack_Size      EQU     0x00000000
SVC_Stack_Size      EQU     0x00000400
ABT_Stack_Size      EQU     0x00000008
FIQ_Stack_Size      EQU     0x00000008
IRQ_Stack_Size      EQU     0x00000600
USR_Stack_Size      EQU     0x00000100

        PRESERVE8

; Area Definition and Entry Point
; Startup Code must be linked first at Address at which it expects to run.

        AREA    VECTOR, CODE
        ARM

; Exception Vectors

	IMPORT vPortYieldProcessor
Vectors         LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
                LDR     PC, IRQ_Addr
             
                LDR     PC, FIQ_Addr



Reset_Addr      DCD     resetHandler
Undef_Addr      DCD     Undef_Handler
;SWI_Addr        DCD     SWI_Handler
SWI_Addr        DCD     vPortYieldProcessor
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                      ; Reserved Address 
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
IRQ_Handler     B       irqHandler
FIQ_Handler     B       FIQ_Handler


;------------------------------------------------------------------------------
; Handles incoming interrupt requests by branching to the corresponding
; handler, as defined in the AIC. Supports interrupt nesting.
;------------------------------------------------------------------------------

 ; Copy Exception Vectors to Internal RAM
   ; Reset Controller (RSTC) definitions
RSTC_BASE       EQU     0xFFFFFD00      ; RSTC Base Address
RSTC_MR         EQU     0x08            ; RSTC_MR Offset
 
                IF      :DEF:RAM_INTVEC
                ADR     R8, Vectors         ; Source
                LDR     R9, =RAM_BASE       ; Destination
                LDMIA   R8!, {R0-R7}        ; Load Vectors 
                STMIA   R9!, {R0-R7}        ; Store Vectors 
                LDMIA   R8!, {R0-R7}        ; Load Handler Addresses 
                STMIA   R9!, {R0-R7}        ; Store Handler Addresses
                ENDIF

        
; Remap on-chip RAM to address 0

MC_BASE EQU     0xFFFFFF00      ; MC Base Address
MC_RCR  EQU     0x00            ; MC_RCR Offset
RAM_BASE        EQU     0x00200000

                IF      :DEF:REMAP
                LDR     R0, =MC_BASE
                MOV     R1, #1
                STR     R1, [R0, #MC_RCR]   ; Remap
                ENDIF


irqHandler
        ;  Save interrupt context on the stack to allow nesting */
        SUB     lr, lr, #4
        STMFD   sp!, {lr}
        MRS     lr, SPSR
        STMFD   sp!, {r0,r1,lr}

        ; Write in the IVR to support Protect Mode */
        LDR     lr, =AT91C_BASE_AIC
        LDR     r0, [r14, #AIC_IVR]
        STR     lr, [r14, #AIC_IVR]

        ; Branch to interrupt handler in Supervisor mode */
        MSR     CPSR_c, #ARM_MODE_SVC
        STMFD   sp!, {r1-r4, r12, lr}
        MOV     lr, pc
        BX      r0
        LDMIA   sp!, {r1-r4, r12, lr}
        MSR     CPSR_c, #ARM_MODE_IRQ | I_BIT

        ; Acknowledge interrupt */
        LDR     lr, =AT91C_BASE_AIC
        STR     lr, [r14, #AIC_EOICR]

        ; Restore interrupt context and branch back to calling code
        LDMIA   sp!, {r0,r1,lr}
        MSR     SPSR_cxsf, lr
        LDMIA   sp!, {pc}^

;------------------------------------------------------------------------------
; After a reset, execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
; Initializes the chip and branches to the main() function.
;------------------------------------------------------------------------------
                
   		AREA  cstartup, CODE
   		ENTRY        ; Entry point for the application
		
   		
; Reset Handler

        EXPORT  resetHandler
        IMPORT	|Image$$Fixed_region$$Limit|
        IMPORT  |Image$$Relocate_region$$Base|
        IMPORT  |Image$$Relocate_region$$ZI$$Base|
        IMPORT  |Image$$Relocate_region$$ZI$$Limit|
        IMPORT  |Image$$ARM_LIB_STACK$$Base|
        IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|
        
		; Perform low-level initialization of the chip using LowLevelInit()
		IMPORT  LowLevelInit
		
resetHandler   

        ; Set pc to actual code location (i.e. not in remap zone)
	    LDR     pc, =label
label	    
		; Set up temporary stack (Top of the SRAM)
		LDR     r0, = |Image$$ARM_LIB_STACK$$ZI$$Limit|
        MOV     sp, r0
		; Call Low level init
	    LDR     r0, =LowLevelInit
        MOV     lr, pc
        BX      r0


;Initialize the Relocate_region segment 
		LDR 	r0, = |Image$$Fixed_region$$Limit|
		LDR 	r1, = |Image$$Relocate_region$$Base|
		LDR 	r3, = |Image$$Relocate_region$$ZI$$Base|
	    
	    CMP     r0, r1                 
     	BEQ     %1
     	
     	
        ; Copy init data
0       CMP     r1, r3         
        LDRCC   r2, [r0], #4   
        STRCC   r2, [r1], #4
        BCC     %0

1       LDR     r1, =|Image$$Relocate_region$$ZI$$Limit|
        MOV     r2, #0
2       CMP     r3, r1                  
        STRCC   r2, [r3], #4
        BCC     %2
       
               
; Setup Stack for each mode

        LDR     R0, = |Image$$ARM_LIB_STACK$$ZI$$Limit|

;  Enter IRQ Mode and set its Stack Pointer
        MSR     CPSR_c, #ARM_MODE_IRQ:OR:I_BIT:OR:F_BIT
        MOV     SP, R0
        SUB     R4, SP, #IRQ_Stack_Size

; Supervisor mode (interrupts enabled) 
        MSR     CPSR_c, #ARM_MODE_SVC | F_BIT
        MOV     SP, R4   

; Enter the C code

        IMPORT  __main
        LDR     R0, =__main
        BX      R0
loop4
        B       loop4                

       END
