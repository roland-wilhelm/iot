;/*----------------------------------------------------------------------------
; *      RL-ARM - RTX
; *----------------------------------------------------------------------------
; *      Name:    SVC_TABLE.S
; *      Purpose: Pre-defined SVC Table for CORTEX M3
; *      Rev.:    V4.50
; *----------------------------------------------------------------------------
; *      This code is part of the RealView Run-Time Library.
; *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
; *      SVC Functions for QK Interrupt Protection from user mode 
; *---------------------------------------------------------------------------*/


                AREA    SVC_TABLE, CODE, READONLY

                EXPORT  SVC_Count

SVC_Cnt         EQU    (SVC_End-SVC_Table)/4
SVC_Count       DCD     SVC_Cnt

; Import user SVC functions here.
                IMPORT  __SVC_0
				IMPORT  __SVC_1
                EXPORT  SVC_Table
SVC_Table
; Insert user SVC functions here. SVC 0 used by RTL Kernel.
                DCD     __SVC_0                 ; calls disable_irq
				DCD     __SVC_1                 ; calls enable_irq

SVC_End

                END

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
