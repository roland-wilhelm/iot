;***************************************************************************
;**                                                                        *
;**  FILE        :  cstart.asm                                             *
;**                                                                        *
;**  DESCRIPTION :  C startup code                                         *
;**                                                                        *
;**  NOTE        :  When using EDE all macros are automatically set by the *
;**                 Project, Cpu and Bus configuration... dialog from the  *
;**                 EDE menu.                                              *
;**                                                                        *
;**  Copyright 1996-2005 Altium BV                                         *
;**                                                                        *
;**************************************************************************/

        .global _START                  ; reset vector address
        .global _start                  ; reset start address
        .global _exit                   ; exit return address
        .weak   _Exit                   ; exit return address (weak definition)

        .extern main                    ; start label user C program

.if !@DEF('_NO_EXIT')
        .extern exit                    ; C library exit function
.endif
.if !@DEF('_NO_USP_INIT')
        .extern _lc_ue_ustack           ; user stack end
.endif
.if !@DEF('_NO_ISP_INIT')
        .extern _lc_ue_istack           ; interrupt stack end
.endif
.if !@DEF('_NO_BIV_INIT')
        .extern (CODE) _lc_u_int_tab    ; interrupt table
.endif
.if !@DEF('_NO_BTV_INIT')
        .extern (CODE) _lc_u_trap_tab   ; trap table
.endif
.if !@DEF('_NO_A0A1_ADDRESSING')
        .extern (DATA) _SMALL_DATA_     ; centre of A0 addressable area
        .extern (DATA) _LITERAL_DATA_   ; centre of A1 addressable area
.endif
.if !@DEF('_NO_A8A9_ADDRESSING')
        .extern (DATA) _A8_DATA_        ; centre of A8 addressable area
        .extern (DATA) _A9_DATA_        ; centre of A9 addressable area
.endif
.if !@DEF('_NO_C_INIT')
        .extern _c_init                 ; C initialization function
.endif  
.if @DEF('_SYNC_ON_HALT')
        .extern _sync_on_halt           ; CrossView utilty function
.endif  


;       Deviating naming conventions
;
.if @DEF('_REGTC11IB_DEF') || @DEF('_REGPXB4225_DEF')
        WDT_CON0        .equ    WDTCON0
        WDT_CON1        .equ    WDTCON1
.endif
.if @DEF('_REGPXB4260_DEF') || @DEF('_REGTC1775B_DEF') || @DEF('_REGTC1765_DEF')
        EBU_ADDRSEL0     .equ    EBU_ADDSEL0
        EBU_ADDRSEL1     .equ    EBU_ADDSEL1
        EBU_ADDRSEL2     .equ    EBU_ADDSEL2
        EBU_ADDRSEL3     .equ    EBU_ADDSEL3
.endif  
.if @DEF('_REGPXB4260_DEF')
        EBU_SDRMCON0     .equ    EBU_DRMCON0
        EBU_SDRMCON1     .equ    EBU_DRMCON1
.endif  
.if @DEF('_REGTC1100_DEF') || @DEF('_REGTC1115_DEF') || @DEF('_REGTC1130_DEF') || @DEF('_REGTC1762_DEF') || @DEF('_REGTC1766_DEF') || @DEF('_REGTC1766B_DEF') || @DEF('_REGTC1796_DEF') || @DEF('_REGTC1796B_DEF')
        DMU_CON         .equ    DMI_CON
.endif  
.if @DEF('_REGTC1775B_DEF') || @DEF('_REGTC1765_DEF')
        PMU_CON0        .equ    PMU_CON
.endif  
.if @DEF('_REGTC1762_DEF') || @DEF('_REGTC1766_DEF') || @DEF('_REGTC1766B_DEF') || @DEF('_REGTC1796_DEF') || @DEF('_REGTC1796B_DEF')
        PMU_CON0        .equ    PMI_CON0
.endif  
.if @DEF('_REGTC1100_DEF') || @DEF('_REGTC1115_DEF') || @DEF('_REGTC1130_DEF') || @DEF('_REGTC1762_DEF') || @DEF('_REGTC1766_DEF') || @DEF('_REGTC1766B_DEF') || @DEF('_REGTC1796_DEF') || @DEF('_REGTC1796B_DEF')
        S_BCU_CON       .equ    SBCU_CON
.endif
.if @DEF('_REGTC1910_DEF') || @DEF('_REGTC1912_DEF') || @DEF('_REGTC1920B_DEF') 
        S_BCU_CON       .equ    BCU_CON
.endif
.if @DEF('_REGTC11IB_DEF')
        S_BCU_CON       .equ    BCU1_CON
        F_BCU_CON       .equ    BCU0_CON
.endif
.if @DEF('_REGTC1130_DEF')
        PMU_CON0        .equ    PMI_CON0
.endif 
;       macro for loading 32bit constants into address registers
CONST.A .MACRO  ax,v
        movh.a  ax,#@his(v)             ; high part with correction for signed addition
        lea     ax,[ax]@los(v)
        .ENDM

;       macro for loading 32bit constants into data registers
CONST.D .MACRO  dx,v
        movh    dx,#@his(v)
        addi    dx,dx,#@los(v)
        .ENDM

;       macro for 32bit indirect call
CALL.I  .MACRO  ax,v
        movh.a  ax,#@his(v)             ; high part with correction for signed addition
        lea     ax,[ax]@los(v)          ; call function indirectly to have more
.if @DEF('__TC113_CPU16__') || @DEF('__CPU_TC048__') 
        nop        
.endif                
        calli   ax                      ; freedom with CODE section allocation
        .ENDM   

; 
;       Reset "vector"
;       no .org: placed via the locator in appropriate boot section (see file tc.i)
;
        .sdecl  ".text.libc.reset",CODE
        .sect   ".text.libc.reset"
        .align  4

;       Turn CPU_TC065 CPU functional defect checking off in the reset vector
;
.if @DEF('__CPU_TC065__')
$CPU_TC065    OFF
.endif

_START:
;
;       Turn TC113_CPU14 CPU functional defect checking off
;
.if @DEF('__TC113_CPU14__')
$TC113_CPU14    OFF
.endif
        j       _start

;       Reset CPU_TC065 CPU functional defect checking after the reset vector
;
.if @DEF('__CPU_TC065__')
$CPU_TC065    ON
.endif

        .align  4        
;
;       BOOTCFG
;       External Boot Memory Configuration Word
;       (Boot memory Offset Address + 0x4)
;
.if     !(@DEF('_BOOTCFG_VALUE'))
_BOOTCFG_VALUE          .equ    0x800C
.endif
        .word   ( _BOOTCFG_VALUE )

;
;       argv[argc] of main() must yield 0
;
.if !@DEF('_NO_ARG_INIT')
        .sdecl  ".data.libc",DATA,ROM
        .sect   ".data.libc"
        .align  4
argv_space:
        .word   0
.endif

; 
;       Startup code at reset, residing in actual program space
;
        .sdecl  ".text.libc",CODE
        .sect   ".text.libc"
        .align  4
_start:
.include "sibug_function_entry.inc"

;
;       Re-enable and reset the call depth counter and  make A0,A1,A8,A9 
;       write-able. It is required for CrossView that these RESET values are
;       restored for each time the startup code is executed.
;
.if !@DEF('_NO_PSW_RESET')
        mfcr    d0,#PSW
        andn    d0,d0,#0x7f             ; reset counter
        insert  d0,d0,#1,#7,#1          ; enable
        insert  d0,d0,#1,#8,#1          ; set GW bit
        mtcr    #PSW,d0
        isync
.endif

;
;       TC112_COR16 workaround (aka CPU_TC.033):
;               The stack pointers are aligned to quad-word boundary
;               to workaround the TC112_COR16 functional problem.
;               Also the C compiler workaround for this CPU function problem
;               need to be enabled with --silicon-bug=cpu-tc033, to align circular
;               buffers on a quad-word boundary and to size all stack 
;               frames to an integral number of quad-words.
;
.if ( @DEF('__TC112_COR16__') || @DEF('__CPU_TC033__') )
        STACK_ALIGN     .equ    0xfffffff0
.else
        STACK_ALIGN     .equ    0xfffffff8
.endif

;
;       Load user stack pointer
;
;       Disable this if not started from RESET vector. (E.g.
;       ROM monitors require to keep in control of vectors)
;
.if !@DEF('_NO_USP_INIT')
        CONST.D d0,_lc_ue_ustack                ; initialize user stack pointer
        CONST.D d7,STACK_ALIGN                  ; align label ue_ustack, note that
        and     d0,d7                           ; ub_ustack is aligned by the locator
        mov.a   sp,d0   
.endif

;
;       Clear Previous Context Pointer Segment Address and Offset Field.
;       It is required for CrossView stack trace that these RESET values 
;       are restored for each time the startup code is executed.
;
.if !@DEF('_NO_PCX_RESET')
        mfcr    d0,#PCXI
        movh    d1,#0xfff0
        and16   d0,d1
        mtcr    #PCXI,d0
        isync
.endif

;
;       Setup the context save area lists
;
;       Tables with start/end addresses go in a separate 'csa_areas' section
;
.if !@DEF('_NO_CSA_INIT')
;
        .sdecl  ".text.libc.csa_areas", CODE
        .sect   ".text.libc.csa_areas"
        .align  4

.if @DEF('__CPU_TC051__')
        MAX_NR_OF_CSA_AREAS     .equ    3
.else
        MAX_NR_OF_CSA_AREAS     .equ    1
.endif

csa_area_begin:                         ; csa_area_begin[MAX_NR_OF_CSA_AREAS]
.if @DEF('__CPU_TC051__')
        .extern _lc_ub_csa.01           ; context save area 1 begin
        .extern _lc_ub_csa.02           ; context save area 2 begin
        .extern _lc_ub_csa.03           ; context save area 3 begin
; 
        .word   _lc_ub_csa.01
        .word   _lc_ub_csa.02
        .word   _lc_ub_csa.03
.else
        .extern _lc_ub_csa.01           ; context save area 1 begin
; 
        .word   _lc_ub_csa.01
.endif

csa_area_end:                           ; csa_area_end[MAX_NR_OF_CSA_AREAS]
.if @DEF('__CPU_TC051__')
        .extern _lc_ue_csa.01           ; context save area 1 end
        .extern _lc_ue_csa.02           ; context save area 2 end
        .extern _lc_ue_csa.03           ; context save area 3 end
; 
        .word   _lc_ue_csa.01   
        .word   _lc_ue_csa.02
        .word   _lc_ue_csa.03
.else
        .extern _lc_ue_csa.01           ; context save area end
; 
        .word   _lc_ue_csa.01
.endif
;
;        Resume with the original '.text.libc' section 
; 
        .sect   ".text.libc"
;
        mov     d0,#-1                   ; D0 = index of CSA area, refered to as 'i'     
        j       test_max_csa_areas
;
start_linked_list:
        CONST.A a2,csa_area_begin       ; first calculate nr. of CSAs in this area:
        addsc.a a2,a2,d0,#2             ; get csa_area_begin[i]
        CONST.A a3,csa_area_end
        addsc.a a3,a3,d0,#2             ; get csa_area_end[i]
        ld16.w  d15,[a3]                ; load csa_area_end[i] address
        ld16.w  d2,[a2]                 ; load csa_area_begin[i] address
        sub     d15,d2                  ; 
        sh      d15,#-6                 ; (csa_area_begin-csa_area_end)/64
        jz      d15,test_max_csa_areas  ; if no CSA in this area, then get next area
;
        ld16.a  a2,[a2]                 ; A2 = csa_area_begin[i] address
        mov16.d d1,a2                   ;               
        extr.u  d1,d1,#28,#4            ; extract segment number
        sh      d1,d1,#16               ; D1 = shifted segment number
        jnz     d0,next_areas                   
;
first_area:                             ; Initialize the first time only:
        mov16.d d3,a2                   ; D3 = first CSA from first area 
        mov16   d2,#0
        st.w    [a2+]64,d2              ; store null pointer in (last!) CSA
        add16   d15,#-1                 ; one CSA handled
;
        mov16.d d2,a2                   ; 
        extr.u  d2,d2,#6,#16            ; get CSA index
        or16    d2,d1                   ; add segment number
        mtcr    #LCX,d2                 ; initialize LCX (second CSA in first area)
        isync
        j       load_loop_count
;
next_areas:                             ; D3 = last CSA from previous area
        extr.u  d7,d3,#28,#4            ; extract segment number
        sh      d7,d7,#16               ; D1 = shifted segment number
        extr.u  d2,d3,#6,#16            ; get CSA index
        or16    d2,d7                   ; add segment number
        mov16.d d3,a2                   ; D3 = first CSA from this area
        st.w    [a2+]64,d2              ; store in first CSA from this area
        add16   d15,#-1                 ; one CSA handled
;
load_loop_count:
        jz      d15,init_fcx            ; if just one CSA in this area, then ready
        add16   d15,#-1                 ; 'correct' loopcount
        mov.a   a5,d15                  ; A5 = loop counter
loop:                                   ; D3 = previous CSA
        extr.u  d2,d3,#6,#16            ; get CSA index
        or16    d2,d1                   ; add segment number
        mov16.d d3,a2
        st.w    [a2+]64,d2              ; store "next" pointer
;
.include 'sibug_loop_before.inc'
;
        loop16  a5,loop
;
init_fcx:
        extr.u  d2,d3,#6,#16            ; get CSA index
        or16    d2,d1                   ; add segment number
        mtcr    #FCX,d2                 ; initialize FCX
        isync
;
test_max_csa_areas:
        add16   d0,#1                   ; increment index
        jlt     d0,#MAX_NR_OF_CSA_AREAS,start_linked_list
.endif

;
;
; Clear the ENDINIT bit in the WDT_CON0 register in order
; to disable the write-protection for registers protected 
; via the EndInit feature (for example: WDT_CON1).
;
        CALL.I  a2,_endinit_clear

;
;
; Call a function (assembly label) before the write-protection
; is enabled again. In this routine one can initialize the 
; registers protected via the EndInit feature.
; Beware that protected registers are unlocked for the duration 
; of the Time-out Period only!
;
.if @DEF('_CALL_ENDINIT')
        .extern _CALL_ENDINIT
        CALL.I  a2,_CALL_ENDINIT
.endif 

;
; Disable the Watchdog if requested. 
;       
.if @DEF('_WATCHDOG_DISABLE')
        CONST.A a2,WDT_CON1             ; get address WDT_CON1
        ld16.w  d0,[a2]                 ; load WDT_CON1
        CONST.D d1,0x08                 ; WDTDR is bit 3 of WDT_CON1
        or      d0,d0,d1                ; set WDT_CON1_WDTR 
        st16.w  [a2],d0                 ; request to disable the watchdog
.endif

;
;       TC113_PMU3 (aka PMI_TC.003) workaround:
;       The TLB-A and TLB-B mappings are set to a page size
;       of 16KB to workaround the TC113_PMU3 functional problem.
;
;       MMU_CON reset value: 0x7e0
;
.if ( @DEF('__TC113_PMU3__') || @DEF('__PMI_TC003__') ) && ( @DEF('_REGTC11IB_DEF') || @DEF('_REGTC1100_DEF') || @DEF('_REGTC1115_DEF') || @DEF('_REGTC1130_DEF') || @DEF('_REGTC1920B_DEF') )
        mov     d15,#(0x7e0 & ~0x1e | 0x14)
        mtcr    #MMU_CON,d15
.endif

;
;       Load Base Address of Trap Vector Table
;
;       Disable this if not started from RESET vector. (E.g.
;       ROM monitors require to keep in control of vectors)
;
.if !@DEF('_NO_BTV_INIT')
        CONST.D d0,_lc_u_trap_tab
        mtcr    #BTV,d0
        isync
.endif

;
;       Load Base Address of Interrupt Vector Table
;
;       Disable this if not started from RESET vector. (E.g.
;       ROM monitors require to keep in control of vectors)
;
.if !@DEF('_NO_BIV_INIT')
        CONST.D d0,_lc_u_int_tab
        mtcr    #BIV,d0
        isync
.endif

;
;       Load interupt stack pointer
;
;       Disable this if not started from RESET vector. (E.g.
;       ROM monitors require to keep in control of vectors)
;
.if !@DEF('_NO_ISP_INIT')
        CONST.D d0,_lc_ue_istack  
        CONST.D d7,STACK_ALIGN                  ; align label ue_istack, note that
        and     d0,d7                           ; ub_istack is aligned by the locator
        mtcr    #ISP,d0                         ; initialize interrupt stack pointer
        isync
.endif
               

;
;       PMU configuration
;
.if @DEF('_PMU_CON_VALUE')
        CONST.D d2, _PMU_CON_VALUE
        CONST.A a5, PMU_CON0
        st.w    [a5], d2
.endif
.if @DEF('_PMU_EIFCON_VALUE')
        CONST.D d2, _PMU_EIFCON_VALUE
        CONST.A a5, PMU_EIFCON
        st.w    [a5], d2
.endif

;
;       Data cache control (Reset 0H)
;
;
;       TC113_CPU13 workaround:
;               The 16KB D-Cache is enabled to workaround
;               the TC113_CPU13 functional problem.     
;               NOTE:   Setting the D-Cache size must be done at the
;                       very beginning of the startup code.
;
.if @DEF('__TC113_CPU13__')     
        mov16   d15,#1
        CONST.A a15, DMU_CON
        st.w    [a15], d15
.elif @DEF('_REGTC1765_DEF')
        mov16   d15,#0xCA
        CONST.A a15, DMU_CON
        st.w    [a15], d15
.endif

;
;       Bus configuration EBU_CLC within endinit 
;
.if @DEF('_EBUCLC_VALUE') && !@DEF('_NO_BUS_CONF')
        CONST.D d2, _EBUCLC_VALUE
        CONST.A a15, EBU_CLC
        st.w    [a15], d2
.endif

;
; Set the ENDINIT bit in the WDT_CON0 register again
; to enable the write-protection and to prevent a time-out. 
;
        CALL.I  a2,_endinit_set

 
;
;       TC113_PMU1 (aka PMU_TC.004) workaround:
;       The split mode is disabled on the LMB bus to workaround
;       the TC113_PMU1 functional problem.
;
.if ( @DEF('__TC113_PMU1__') || @DEF('__PMU_TC004__') ) && !( @DEF('_REGTC1762_DEF') || @DEF('_REGTC1766_DEF') || @DEF('_REGTC1766B_DEF') || @DEF('_REGTC1796_DEF') || @DEF('_REGTC1796B_DEF') )
        mov16   d7,#-2
        CONST.A a15, LFI_CON
        ld.w    d15,[a15]
        and16   d15,d7
        st.w    [a15], d15      
.endif

;
;       TC112_COR15 workaround:
;       The starvation protection is disabled to workaround
;       the TC112_COR15 functional problem.
;
.if @DEF('__TC112_COR15__')
        CONST.A a3,BCU_CON
        CONST.D d2,0xFFF7FFFF
        ld16.w  d0,[a3]
        and     d0,d2,d0
        st16.w  [a3],d0 
.endif
 
;
;       Inititialize global address registers a0/a1 to support
;       __a0/__a1 storage qualifiers of the C compiler.
;
.if !@DEF('_NO_A0A1_ADDRESSING')
        CONST.A a0,_SMALL_DATA_
        CONST.A a1,_LITERAL_DATA_
.endif

;
;       Inititialize global address registers a8/a9 to support
;       __a8/__a9 storage qualifiers of the C compiler. A8 and A9
;       are reserved for OS use, or for application use in cases 
;       where the application ans OS are tightly coupled.
;
.if !@DEF('_NO_A8A9_ADDRESSING')
        CONST.A a8,_A8_DATA_
        CONST.A a9,_A9_DATA_
.endif
               
;
;       Initialize Bus configuration registers
;       
.if !@DEF('_NO_BUS_CONF')
;
;       Set register-values according to .define's created by the EDE
;
        .if @DEF('_ADDRSEL0_VALUE')
                CONST.D d2, _ADDRSEL0_VALUE
                CONST.A a15, EBU_ADDRSEL0
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL1_VALUE')
                CONST.D d2, _ADDRSEL1_VALUE
                CONST.A a15, EBU_ADDRSEL1
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL2_VALUE')
                CONST.D d2, _ADDRSEL2_VALUE
                CONST.A a15, EBU_ADDRSEL2
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL3_VALUE')
                CONST.D d2, _ADDRSEL3_VALUE
                CONST.A a15, EBU_ADDRSEL3
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL4_VALUE')
                CONST.D d2, _ADDRSEL4_VALUE
                CONST.A a15, EBU_ADDRSEL4
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL5_VALUE')
                CONST.D d2, _ADDRSEL5_VALUE
                CONST.A a15, EBU_ADDRSEL5
                st.w    [a15], d2
        .endif
        .if @DEF('_ADDRSEL6_VALUE')
                CONST.D d2, _ADDRSEL6_VALUE
                CONST.A a15, EBU_ADDRSEL6
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP0_VALUE')
                CONST.D d2, _BUSAP0_VALUE
                CONST.A a15, EBU_BUSAP0
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP1_VALUE')
                CONST.D d2, _BUSAP1_VALUE
                CONST.A a15, EBU_BUSAP1
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP2_VALUE')
                CONST.D d2, _BUSAP2_VALUE
                CONST.A a15, EBU_BUSAP2
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP3_VALUE')
                CONST.D d2, _BUSAP3_VALUE
                CONST.A a15, EBU_BUSAP3
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP4_VALUE')
                CONST.D d2, _BUSAP4_VALUE
                CONST.A a15, EBU_BUSAP4
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP5_VALUE')
                CONST.D d2, _BUSAP5_VALUE
                CONST.A a15, EBU_BUSAP5
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSAP6_VALUE')
                CONST.D d2, _BUSAP6_VALUE
                CONST.A a15, EBU_BUSAP6
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON0_VALUE')
                CONST.D d2, _BUSCON0_VALUE
                CONST.A a15, EBU_BUSCON0
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON1_VALUE')
                CONST.D d2, _BUSCON1_VALUE
                CONST.A a15, EBU_BUSCON1
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON2_VALUE')
                CONST.D d2, _BUSCON2_VALUE
                CONST.A a15, EBU_BUSCON2
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON3_VALUE')
                CONST.D d2, _BUSCON3_VALUE
                CONST.A a15, EBU_BUSCON3
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON4_VALUE')
                CONST.D d2, _BUSCON4_VALUE
                CONST.A a15, EBU_BUSCON4
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON5_VALUE')
                CONST.D d2, _BUSCON5_VALUE
                CONST.A a15, EBU_BUSCON5
                st.w    [a15], d2
        .endif
        .if @DEF('_BUSCON6_VALUE')
                CONST.D d2, _BUSCON6_VALUE
                CONST.A a15, EBU_BUSCON6
                st.w    [a15], d2
        .endif
        .if @DEF('_EMUAS_VALUE')
                CONST.D d2, _EMUAS_VALUE
                CONST.A a15, EBU_EMUAS
                st.w    [a15], d2
        .endif
        .if @DEF('_EMUBC_VALUE')
                CONST.D d2, _EMUBC_VALUE
                CONST.A a15, EBU_EMUBC
                st.w    [a15], d2
        .endif
        .if @DEF('_EMUCON_VALUE')
                CONST.D d2, _EMUCON_VALUE
                CONST.A a15, EBU_EMUCON
                st.w    [a15], d2
        .endif
        .if @DEF('_EMUBAP_VALUE')
                CONST.D d2, _EMUBAP_VALUE
                CONST.A a15, EBU_EMUBAP
                st.w    [a15], d2
        .endif
        .if @DEF('_EMUOVL_VALUE')
                CONST.D d2, _EMUOVL_VALUE
                CONST.A a15, EBU_EMUOVL
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMCON0_VALUE')
                CONST.D d2, _SDRMCON0_VALUE
                CONST.A a15, EBU_SDRMCON0
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMCON1_VALUE')
                CONST.D d2, _SDRMCON1_VALUE
                CONST.A a15, EBU_SDRMCON1
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMOD0_VALUE')
                CONST.D d2, _SDRMOD0_VALUE
                CONST.A a15, EBU_SDRMOD0
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMOD1_VALUE')
                CONST.D d2, _SDRMOD1_VALUE
                CONST.A a15, EBU_SDRMOD1
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMREF0_VALUE')
                CONST.D d2, _SDRMREF0_VALUE
                CONST.A a15, EBU_SDRMREF0
                st.w    [a15], d2
        .endif
        .if @DEF('_SDRMREF1_VALUE')
                CONST.D d2, _SDRMREF1_VALUE
                CONST.A a15, EBU_SDRMREF1
                st.w    [a15], d2
        .endif
        .if @DEF('_BFCON_VALUE')
                CONST.D d2, _BFCON_VALUE
                CONST.A a15, EBU_BFCON
                st.w    [a15], d2
        .endif
        .if @DEF('_BCUCON_VALUE')
                CONST.D d2, _BCUCON_VALUE
                CONST.A a15, BCU_CON
                st.w    [a15], d2
        .endif
        .if @DEF('_F_BCUCON_VALUE')
                CONST.D d2, _F_BCUCON_VALUE
                CONST.A a15, F_BCU_CON
                st.w    [a15], d2
        .endif
        .if @DEF('_S_BCUCON_VALUE')
                CONST.D d2, _S_BCUCON_VALUE
                CONST.A a15, S_BCU_CON
                st.w    [a15], d2
        .endif
        .if @DEF('_EBUCON_VALUE')
                CONST.D d2, _EBUCON_VALUE
                CONST.A a15, EBU_CON
                st.w    [a15], d2
        .endif
        .if @DEF('_MCDBBS_VALUE')
                CONST.D d2, _MCDBBS_VALUE
                CONST.A a15, MCDBBS 
                st.w    [a15], d2
        .endif
.endif

;
;
;       Initialize and clear C variables
;
.if !@DEF('_NO_C_INIT')
        CALL.I  a2,_c_init              ; initialize data
.endif  

;
;       Call a function (assembly label) before main()
;
.if @DEF('_CALL_INIT')
        .extern _CALL_INIT
        CALL.I  a2,_CALL_INIT
.endif  


;
;       Clear argc and argv[] of main()
;
.if !@DEF('_NO_ARG_INIT')
        mov16   d4,#0                   ; argc    == 0
        CONST.A a4,argv_space           ; argv[0] == 0
.endif

;
;       Main default return value is 0
;
.if !@DEF('_NO_EXIT')
        mov16   d2,#0                   ; set default exit value
.endif

;
;       Call C program
;
        CALL.I  a2,main                 ; call main()

;
;       Call C library exit function
;
;       The exit() function causes normal program termination to occur. First, all 
;       functions registered by the atexit() function are called in the reverse 
;       order. Next, all open streams with unwritten buffered data are flushed, all 
;       open streams are closed and all files created by the tmpfile() function are 
;       removed.
;
.if !@DEF('_NO_EXIT')
        mov16   d4,d2                   ; pass return value to exit()
        CALL.I  a2,exit                 ; call exit()
.endif

;
;       The exit() function jumps _exit and a breakpoint is set
;       at _exit by the CrossView debugger to halt execution.
;       
_Exit:
_exit:  debug16                         ; halt the execution if debug mode is enabled  
.include 'sibug_loop_before.inc' 
        loopu   _exit                   ; otherwise loop
;
;       Default trap vectors are resolved from the C-library
;
.if !@DEF('_NO_BTV_INIT')
.if !@DEF('_USERDEFINED_TRAP_0')
        .extern (CODE) _trapmmu
.endif
.if !@DEF('_USERDEFINED_TRAP_1')
        .extern (CODE) _trapprotection
.endif
.if !@DEF('_USERDEFINED_TRAP_2')
        .extern (CODE) _trapinstruction
.endif
.if !@DEF('_USERDEFINED_TRAP_3')
        .extern (CODE) _trapcontext
.endif
.if !@DEF('_USERDEFINED_TRAP_4')
        .extern (CODE) _trapbus
.endif
.if !@DEF('_USERDEFINED_TRAP_5')
        .extern (CODE) _trapassertion
.endif
.if !@DEF('_USERDEFINED_TRAP_6')
        .extern (CODE) _trapsystem
.endif
.if !@DEF('_USERDEFINED_TRAP_7')
        .extern (CODE) _trapnmi
.endif
.endif
;
; 
; 
;--------------------------------------------------------------------------
; Utility subroutines
;--------------------------------------------------------------------------
; function:     _endinit_clear
; input:        None
; output:       Bit ENDINIT in WDTCON0 is cleared
; other registers used:
;               D0, D1, D2, D4, A3, A4 - work register
; description:  Clears the ENDINIT bit in the 
;               WDT_CON0 register in order to disable the 
; write-protection for registers protected 
; via the EndInit feature (ie. WDT_CON1, BTV, 
; BIV, ISP, mod_CLC).
;--------------------------------------------------------------------------
;
        .global _endinit_clear
;
_endinit_clear:
;
; 1st step: Password access (create password and send to WDT_CON0)
;
        CONST.A a3,WDT_CON0             ; get address WDT_CON0
        ld16.w  d0,[a3]                 ; get WDT_CON0 in d0
;
        CONST.A a4,WDT_CON1             ; get address WDT_CON1
        ld16.w  d1,[a4]                 ; get WDT_CON1_WDTDR WDT_CON1_WDTIR
;
        CONST.D d2,0xFFFFFF01   ; mask hardware password 0,1
        and     d0,d2,d0                ; in copy of WDT_CON0 (d0),
        or      d0,d0,#0xF0             ; set WDTHPW1 to 0xF and load
        and     d4,d1,#0x0C             ; copy of WDT_CON1_WDTDR and
        or      d0,d4,d0                ; WDT_CON1_WDTIR (d1)
        st16.w  [a3],d0                 ; set WDT_CON0
;
; 2nd step: Modify access, set the bit ENDINIT to 0 to allow access to
;                       registers: WDT_CON1, BTV, BIV, ISP and mod_CLC
;
        CONST.D d4,0xFFFFFFF0           ; mask WDTHPW0,WDTLCK,ENDINIT
        and     d0,d4,d0                ; in copy of WDT_CON0 (d0)
        or      d0,d0,#0X02             ; WDTHPW0=0,WDTLCK=1,ENDINIT=0
        isync
        st16.w  [a3],d0                 ; set WDT_CON0
;
        ret                             ;
;
;--------------------------------------------------------------------------
; function:     _endinit_set
; input:
;       None
; output:
;   Bit ENDINIT in WDTCON0 is set
; other registers used:
;       D0, D1, D2, D4, A3, A4 - work register
; description: Clears the ENDINIT bit in the 
; WDT_CON0 register in order to disable the 
; write-protection for registers protected 
; via the EndInit feature (ie. WDT_CON1, BTV, 
; BIV, ISP, mod_CLC).
;--------------------------------------------------------------------------
;
        .global _endinit_set
;
_endinit_set:
;
; 1st step: Password access (create password and send to WDT_CON0)
;
        CONST.A a3,WDT_CON0             ; get address WDT_CON0
        ld16.w  d0,[a3]                 ; get WDT_CON0 in d0
;
        CONST.A a4,WDT_CON1             ; get address WDT_CON1
        ld16.w  d1,[a4]                 ; get WDT_CON1_WDTDR WDT_CON1_WDTIR
;
        CONST.D d2,0xFFFFFF01           ; mask hardware password 0,1
        and     d0,d2,d0                ; in copy of WDT_CON0 (d0),
        or      d0,d0,#0xF0             ; set WDTHPW1 to 0xF and load
        and     d4,d1,#0x0C             ; copy of WDT_CON1_WDTDR and
        or      d0,d4,d0                ; WDT_CON1_WDTIR (d1)
        st16.w  [a3],d0                 ; set WDT_CON0
;
; 2nd step: Modify access, set the bit ENDINIT to 1  
;
        CONST.D d4,0xFFFFFFF0           ; mask WDTHPW0,WDTLCK,ENDINIT
        and     d0,d4,d0                ; in copy of WDT_CON0 (d0)
        or      d0,d0,#0X03             ; WDTHPW0=0,WDTLCK=1,ENDINIT=1
        isync
        st16.w  [a3],d0                 ; set WDT_CON0
;
        ret                             ;
;--------------------------------------------------------------------------
