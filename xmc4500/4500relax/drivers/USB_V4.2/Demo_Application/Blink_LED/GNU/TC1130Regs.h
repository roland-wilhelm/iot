//****************************************************************************
// Description:
//       Register Definition File for TC1130
//
//----------------------------------------------------------------------------
// History:
//                 
//        Rev.             Date        Description
//        --------------------------------------------------------------------
//        1.1              16.04.01    final version
//             
//
//
//****************************************************************************

#ifndef _REGISTER_DEFINITION_H_
#define _REGISTER_DEFINITION_H_


//****************************************************************************
// @Declaration of SFRs
//****************************************************************************
// Address Register 0 (AGPR) Global Address Register
#define A0                     (*((uword volatile *) 0xF7E1FF80))

// Address Register 1 (AGPR) Global Address Register
#define A1                     (*((uword volatile *) 0xF7E1FF84))

// Address Register 10 (AGPR) Stack Pointer
#define A10                    (*((uword volatile *) 0xF7E1FFA8))

// Address Register 11 (AGPR) Return Address
#define A11                    (*((uword volatile *) 0xF7E1FFAC))

// Address Register 12 (AGPR)
#define A12                    (*((uword volatile *) 0xF7E1FFB0))

// Address Register 13 (AGPR)
#define A13                    (*((uword volatile *) 0xF7E1FFB4))

// Address Register 14 (AGPR)
#define A14                    (*((uword volatile *) 0xF7E1FFB8))

// Address Register 15 (AGPR)
#define A15                    (*((uword volatile *) 0xF7E1FFBC))

// Address Register 2 (AGPR)
#define A2                     (*((uword volatile *) 0xF7E1FF88))

// Address Register 3 (AGPR)
#define A3                     (*((uword volatile *) 0xF7E1FF8C))

// Address Register 4 (AGPR)
#define A4                     (*((uword volatile *) 0xF7E1FF90))

// Address Register 5 (AGPR)
#define A5                     (*((uword volatile *) 0xF7E1FF94))

// Address Register 6 (AGPR)
#define A6                     (*((uword volatile *) 0xF7E1FF98))

// Address Register 7 (AGPR)
#define A7                     (*((uword volatile *) 0xF7E1FF9C))

// Address Register 8 (AGPR) Global Address Register
#define A8                     (*((uword volatile *) 0xF7E1FFA0))

// Address Register 9 (AGPR) Global Address Register
#define A9                     (*((uword volatile *) 0xF7E1FFA4))

// ASC Baudrate Timer Reload Register
#define ASC0_BG                (*((uword volatile *) 0xF0100314))

// ASC Clock Control Register
#define ASC0_CLC               (*((uword volatile *) 0xF0100300))
#define ASC0_CLC_DISR            ((T_Reg32 *) 0xF0100300)->bit0
#define ASC0_CLC_DISS            ((T_Reg32 *) 0xF0100300)->bit1
#define ASC0_CLC_EDIS            ((T_Reg32 *) 0xF0100300)->bit3
#define ASC0_CLC_FSOE            ((T_Reg32 *) 0xF0100300)->bit5
#define ASC0_CLC_SBWE            ((T_Reg32 *) 0xF0100300)->bit4
#define ASC0_CLC_SPEN            ((T_Reg32 *) 0xF0100300)->bit2

// ASC Control Register
#define ASC0_CON               (*((uword volatile *) 0xF0100310))
#define ASC0_CON_BRS             ((T_Reg32 *) 0xF0100310)->bit13
#define ASC0_CON_FDE             ((T_Reg32 *) 0xF0100310)->bit11
#define ASC0_CON_FE              ((T_Reg32 *) 0xF0100310)->bit9
#define ASC0_CON_FEN             ((T_Reg32 *) 0xF0100310)->bit6
#define ASC0_CON_LB              ((T_Reg32 *) 0xF0100310)->bit14
#define ASC0_CON_ODD             ((T_Reg32 *) 0xF0100310)->bit12
#define ASC0_CON_OE              ((T_Reg32 *) 0xF0100310)->bit10
#define ASC0_CON_OEN             ((T_Reg32 *) 0xF0100310)->bit7
#define ASC0_CON_PE              ((T_Reg32 *) 0xF0100310)->bit8
#define ASC0_CON_PEN             ((T_Reg32 *) 0xF0100310)->bit5
#define ASC0_CON_R               ((T_Reg32 *) 0xF0100310)->bit15
#define ASC0_CON_REN             ((T_Reg32 *) 0xF0100310)->bit4
#define ASC0_CON_STP             ((T_Reg32 *) 0xF0100310)->bit3

// ASC Error Interrupt Service Request Control Register
#define ASC0_ESRC              (*((uword volatile *) 0xF01003F8))
#define ASC0_ESRC_CLRR           ((T_Reg32 *) 0xF01003F8)->bit14
#define ASC0_ESRC_SETR           ((T_Reg32 *) 0xF01003F8)->bit15
#define ASC0_ESRC_SRE            ((T_Reg32 *) 0xF01003F8)->bit12
#define ASC0_ESRC_SRR            ((T_Reg32 *) 0xF01003F8)->bit13
#define ASC0_ESRC_TOS            ((T_Reg32 *) 0xF01003F8)->bit10

// ASC Fractional Divider Register
#define ASC0_FDV               (*((uword volatile *) 0xF0100318))

// ASC FIFO Status Register
#define ASC0_FSTAT             (*((uword volatile *) 0xF0100348))

// ASC Module Identification Register
#define ASC0_ID                (*((uword volatile *) 0xF0100308))

// ASC Peripheral Input Select Register
#define ASC0_PISEL             (*((uword volatile *) 0xF0100304))
#define ASC0_PISEL_RIS           ((T_Reg32 *) 0xF0100304)->bit0

// ASC IrDA Pulse Mode/Widdth Register
#define ASC0_PMW               (*((uword volatile *) 0xF010031C))
#define ASC0_PMW_IRPW            ((T_Reg32 *) 0xF010031C)->bit8

// ASC Receive Buffer Register
#define ASC0_RBUF              (*((uword volatile *) 0xF0100324))

// ASC Receive Interrupt Service Request Control Register
#define ASC0_RSRC              (*((uword volatile *) 0xF01003F4))
#define ASC0_RSRC_CLRR           ((T_Reg32 *) 0xF01003F4)->bit14
#define ASC0_RSRC_SETR           ((T_Reg32 *) 0xF01003F4)->bit15
#define ASC0_RSRC_SRE            ((T_Reg32 *) 0xF01003F4)->bit12
#define ASC0_RSRC_SRR            ((T_Reg32 *) 0xF01003F4)->bit13
#define ASC0_RSRC_TOS            ((T_Reg32 *) 0xF01003F4)->bit10

// SSC Receive FIFO Control Register
#define ASC0_RXFCON            (*((uword volatile *) 0xF0100340))
#define ASC0_RXFCON_RXFEN        ((T_Reg32 *) 0xF0100340)->bit0
#define ASC0_RXFCON_RXFLU        ((T_Reg32 *) 0xF0100340)->bit1
#define ASC0_RXFCON_RXTMEN       ((T_Reg32 *) 0xF0100340)->bit2

// ASC Transmit Buffer Service Request Control Register
#define ASC0_TBSRC             (*((uword volatile *) 0xF01003FC))
#define ASC0_TBSRC_CLRR          ((T_Reg32 *) 0xF01003FC)->bit14
#define ASC0_TBSRC_SETR          ((T_Reg32 *) 0xF01003FC)->bit15
#define ASC0_TBSRC_SRE           ((T_Reg32 *) 0xF01003FC)->bit12
#define ASC0_TBSRC_SRR           ((T_Reg32 *) 0xF01003FC)->bit13
#define ASC0_TBSRC_TOS           ((T_Reg32 *) 0xF01003FC)->bit10

// ASC Transmit Buffer Register
#define ASC0_TBUF              (*((uword volatile *) 0xF0100320))

// ASC Transmit Interrupt Service Request Control Register
#define ASC0_TSRC              (*((uword volatile *) 0xF01003F0))
#define ASC0_TSRC_CLRR           ((T_Reg32 *) 0xF01003F0)->bit14
#define ASC0_TSRC_SETR           ((T_Reg32 *) 0xF01003F0)->bit15
#define ASC0_TSRC_SRE            ((T_Reg32 *) 0xF01003F0)->bit12
#define ASC0_TSRC_SRR            ((T_Reg32 *) 0xF01003F0)->bit13
#define ASC0_TSRC_TOS            ((T_Reg32 *) 0xF01003F0)->bit10

// SSC Transmit FIFO Control Register
#define ASC0_TXFCON            (*((uword volatile *) 0xF0100344))
#define ASC0_TXFCON_TXFEN        ((T_Reg32 *) 0xF0100344)->bit0
#define ASC0_TXFCON_TXFLU        ((T_Reg32 *) 0xF0100344)->bit1
#define ASC0_TXFCON_TXTMEN       ((T_Reg32 *) 0xF0100344)->bit2

// ASC Hardware Bits Control Register
#define ASC0_WHBCON            (*((uword volatile *) 0xF0100350))
#define ASC0_WHBCON_CLRFE        ((T_Reg32 *) 0xF0100350)->bit9
#define ASC0_WHBCON_CLROE        ((T_Reg32 *) 0xF0100350)->bit10
#define ASC0_WHBCON_CLRPE        ((T_Reg32 *) 0xF0100350)->bit8
#define ASC0_WHBCON_CLRREN       ((T_Reg32 *) 0xF0100350)->bit4
#define ASC0_WHBCON_SETFE        ((T_Reg32 *) 0xF0100350)->bit12
#define ASC0_WHBCON_SETOE        ((T_Reg32 *) 0xF0100350)->bit13
#define ASC0_WHBCON_SETPE        ((T_Reg32 *) 0xF0100350)->bit11
#define ASC0_WHBCON_SETREN       ((T_Reg32 *) 0xF0100350)->bit5

// ASC Baudrate Timer Reload Register
#define ASC1_BG                (*((uword volatile *) 0xF0100414))

// ASC Clock Control Register
#define ASC1_CLC               (*((uword volatile *) 0xF0100400))
#define ASC1_CLC_DISR            ((T_Reg32 *) 0xF0100400)->bit0
#define ASC1_CLC_DISS            ((T_Reg32 *) 0xF0100400)->bit1
#define ASC1_CLC_EDIS            ((T_Reg32 *) 0xF0100400)->bit3
#define ASC1_CLC_FSOE            ((T_Reg32 *) 0xF0100400)->bit5
#define ASC1_CLC_SBWE            ((T_Reg32 *) 0xF0100400)->bit4
#define ASC1_CLC_SPEN            ((T_Reg32 *) 0xF0100400)->bit2

// ASC Control Register
#define ASC1_CON               (*((uword volatile *) 0xF0100410))
#define ASC1_CON_BRS             ((T_Reg32 *) 0xF0100410)->bit13
#define ASC1_CON_FDE             ((T_Reg32 *) 0xF0100410)->bit11
#define ASC1_CON_FE              ((T_Reg32 *) 0xF0100410)->bit9
#define ASC1_CON_FEN             ((T_Reg32 *) 0xF0100410)->bit6
#define ASC1_CON_LB              ((T_Reg32 *) 0xF0100410)->bit14
#define ASC1_CON_ODD             ((T_Reg32 *) 0xF0100410)->bit12
#define ASC1_CON_OE              ((T_Reg32 *) 0xF0100410)->bit10
#define ASC1_CON_OEN             ((T_Reg32 *) 0xF0100410)->bit7
#define ASC1_CON_PE              ((T_Reg32 *) 0xF0100410)->bit8
#define ASC1_CON_PEN             ((T_Reg32 *) 0xF0100410)->bit5
#define ASC1_CON_R               ((T_Reg32 *) 0xF0100410)->bit15
#define ASC1_CON_REN             ((T_Reg32 *) 0xF0100410)->bit4
#define ASC1_CON_STP             ((T_Reg32 *) 0xF0100410)->bit3

// ASC Error Interrupt Service Request Control Register
#define ASC1_ESRC              (*((uword volatile *) 0xF01004F8))
#define ASC1_ESRC_CLRR           ((T_Reg32 *) 0xF01004F8)->bit14
#define ASC1_ESRC_SETR           ((T_Reg32 *) 0xF01004F8)->bit15
#define ASC1_ESRC_SRE            ((T_Reg32 *) 0xF01004F8)->bit12
#define ASC1_ESRC_SRR            ((T_Reg32 *) 0xF01004F8)->bit13
#define ASC1_ESRC_TOS            ((T_Reg32 *) 0xF01004F8)->bit10

// ASC Fractional Divider Register
#define ASC1_FDV               (*((uword volatile *) 0xF0100418))

// ASC FIFO Status Register
#define ASC1_FSTAT             (*((uword volatile *) 0xF0100448))

// ASC Module Identification Register
#define ASC1_ID                (*((uword volatile *) 0xF0100408))

// ASC Peripheral Input Select Register
#define ASC1_PISEL             (*((uword volatile *) 0xF0100404))
#define ASC1_PISEL_RIS           ((T_Reg32 *) 0xF0100404)->bit0

// ASC IrDA Pulse Mode/Widdth Register
#define ASC1_PMW               (*((uword volatile *) 0xF010041C))
#define ASC1_PMW_IRPW            ((T_Reg32 *) 0xF010041C)->bit8

// ASC Receive Buffer Register
#define ASC1_RBUF              (*((uword volatile *) 0xF0100424))

// ASC Receive Interrupt Service Request Control Register
#define ASC1_RSRC              (*((uword volatile *) 0xF01004F4))
#define ASC1_RSRC_CLRR           ((T_Reg32 *) 0xF01004F4)->bit14
#define ASC1_RSRC_SETR           ((T_Reg32 *) 0xF01004F4)->bit15
#define ASC1_RSRC_SRE            ((T_Reg32 *) 0xF01004F4)->bit12
#define ASC1_RSRC_SRR            ((T_Reg32 *) 0xF01004F4)->bit13
#define ASC1_RSRC_TOS            ((T_Reg32 *) 0xF01004F4)->bit10

// SSC Receive FIFO Control Register
#define ASC1_RXFCON            (*((uword volatile *) 0xF0100440))
#define ASC1_RXFCON_RXFEN        ((T_Reg32 *) 0xF0100440)->bit0
#define ASC1_RXFCON_RXFLU        ((T_Reg32 *) 0xF0100440)->bit1
#define ASC1_RXFCON_RXTMEN       ((T_Reg32 *) 0xF0100440)->bit2

// ASC Transmit Buffer Service Request Control Register
#define ASC1_TBSRC             (*((uword volatile *) 0xF01004FC))
#define ASC1_TBSRC_CLRR          ((T_Reg32 *) 0xF01004FC)->bit14
#define ASC1_TBSRC_SETR          ((T_Reg32 *) 0xF01004FC)->bit15
#define ASC1_TBSRC_SRE           ((T_Reg32 *) 0xF01004FC)->bit12
#define ASC1_TBSRC_SRR           ((T_Reg32 *) 0xF01004FC)->bit13
#define ASC1_TBSRC_TOS           ((T_Reg32 *) 0xF01004FC)->bit10

// ASC Transmit Buffer Register
#define ASC1_TBUF              (*((uword volatile *) 0xF0100420))

// ASC Transmit Interrupt Service Request Control Register
#define ASC1_TSRC              (*((uword volatile *) 0xF01004F0))
#define ASC1_TSRC_CLRR           ((T_Reg32 *) 0xF01004F0)->bit14
#define ASC1_TSRC_SETR           ((T_Reg32 *) 0xF01004F0)->bit15
#define ASC1_TSRC_SRE            ((T_Reg32 *) 0xF01004F0)->bit12
#define ASC1_TSRC_SRR            ((T_Reg32 *) 0xF01004F0)->bit13
#define ASC1_TSRC_TOS            ((T_Reg32 *) 0xF01004F0)->bit10

// SSC Transmit FIFO Control Register
#define ASC1_TXFCON            (*((uword volatile *) 0xF0100444))
#define ASC1_TXFCON_TXFEN        ((T_Reg32 *) 0xF0100444)->bit0
#define ASC1_TXFCON_TXFLU        ((T_Reg32 *) 0xF0100444)->bit1
#define ASC1_TXFCON_TXTMEN       ((T_Reg32 *) 0xF0100444)->bit2

// ASC Hardware Bits Control Register
#define ASC1_WHBCON            (*((uword volatile *) 0xF0100450))
#define ASC1_WHBCON_CLRFE        ((T_Reg32 *) 0xF0100450)->bit9
#define ASC1_WHBCON_CLROE        ((T_Reg32 *) 0xF0100450)->bit10
#define ASC1_WHBCON_CLRPE        ((T_Reg32 *) 0xF0100450)->bit8
#define ASC1_WHBCON_CLRREN       ((T_Reg32 *) 0xF0100450)->bit4
#define ASC1_WHBCON_SETFE        ((T_Reg32 *) 0xF0100450)->bit12
#define ASC1_WHBCON_SETOE        ((T_Reg32 *) 0xF0100450)->bit13
#define ASC1_WHBCON_SETPE        ((T_Reg32 *) 0xF0100450)->bit11
#define ASC1_WHBCON_SETREN       ((T_Reg32 *) 0xF0100450)->bit5

// ASC Baudrate Timer Reload Register
#define ASC2_BG                (*((uword volatile *) 0xF0100514))

// ASC Clock Control Register
#define ASC2_CLC               (*((uword volatile *) 0xF0100500))
#define ASC2_CLC_DISR            ((T_Reg32 *) 0xF0100500)->bit0
#define ASC2_CLC_DISS            ((T_Reg32 *) 0xF0100500)->bit1
#define ASC2_CLC_EDIS            ((T_Reg32 *) 0xF0100500)->bit3
#define ASC2_CLC_FSOE            ((T_Reg32 *) 0xF0100500)->bit5
#define ASC2_CLC_SBWE            ((T_Reg32 *) 0xF0100500)->bit4
#define ASC2_CLC_SPEN            ((T_Reg32 *) 0xF0100500)->bit2

// ASC Control Register
#define ASC2_CON               (*((uword volatile *) 0xF0100510))
#define ASC2_CON_BRS             ((T_Reg32 *) 0xF0100510)->bit13
#define ASC2_CON_FDE             ((T_Reg32 *) 0xF0100510)->bit11
#define ASC2_CON_FE              ((T_Reg32 *) 0xF0100510)->bit9
#define ASC2_CON_FEN             ((T_Reg32 *) 0xF0100510)->bit6
#define ASC2_CON_LB              ((T_Reg32 *) 0xF0100510)->bit14
#define ASC2_CON_ODD             ((T_Reg32 *) 0xF0100510)->bit12
#define ASC2_CON_OE              ((T_Reg32 *) 0xF0100510)->bit10
#define ASC2_CON_OEN             ((T_Reg32 *) 0xF0100510)->bit7
#define ASC2_CON_PE              ((T_Reg32 *) 0xF0100510)->bit8
#define ASC2_CON_PEN             ((T_Reg32 *) 0xF0100510)->bit5
#define ASC2_CON_R               ((T_Reg32 *) 0xF0100510)->bit15
#define ASC2_CON_REN             ((T_Reg32 *) 0xF0100510)->bit4
#define ASC2_CON_STP             ((T_Reg32 *) 0xF0100510)->bit3

// ASC Error Interrupt Service Request Control Register
#define ASC2_ESRC              (*((uword volatile *) 0xF01005F8))
#define ASC2_ESRC_CLRR           ((T_Reg32 *) 0xF01005F8)->bit14
#define ASC2_ESRC_SETR           ((T_Reg32 *) 0xF01005F8)->bit15
#define ASC2_ESRC_SRE            ((T_Reg32 *) 0xF01005F8)->bit12
#define ASC2_ESRC_SRR            ((T_Reg32 *) 0xF01005F8)->bit13
#define ASC2_ESRC_TOS            ((T_Reg32 *) 0xF01005F8)->bit10

// ASC Fractional Divider Register
#define ASC2_FDV               (*((uword volatile *) 0xF0100518))

// ASC FIFO Status Register
#define ASC2_FSTAT             (*((uword volatile *) 0xF0100548))

// ASC Module Identification Register
#define ASC2_ID                (*((uword volatile *) 0xF0100508))

// ASC Peripheral Input Select Register
#define ASC2_PISEL             (*((uword volatile *) 0xF0100504))
#define ASC2_PISEL_RIS           ((T_Reg32 *) 0xF0100504)->bit0

// ASC IrDA Pulse Mode/Widdth Register
#define ASC2_PMW               (*((uword volatile *) 0xF010051C))
#define ASC2_PMW_IRPW            ((T_Reg32 *) 0xF010051C)->bit8

// ASC Receive Buffer Register
#define ASC2_RBUF              (*((uword volatile *) 0xF0100524))

// ASC Receive Interrupt Service Request Control Register
#define ASC2_RSRC              (*((uword volatile *) 0xF01005F4))
#define ASC2_RSRC_CLRR           ((T_Reg32 *) 0xF01005F4)->bit14
#define ASC2_RSRC_SETR           ((T_Reg32 *) 0xF01005F4)->bit15
#define ASC2_RSRC_SRE            ((T_Reg32 *) 0xF01005F4)->bit12
#define ASC2_RSRC_SRR            ((T_Reg32 *) 0xF01005F4)->bit13
#define ASC2_RSRC_TOS            ((T_Reg32 *) 0xF01005F4)->bit10

// SSC Receive FIFO Control Register
#define ASC2_RXFCON            (*((uword volatile *) 0xF0100540))
#define ASC2_RXFCON_RXFEN        ((T_Reg32 *) 0xF0100540)->bit0
#define ASC2_RXFCON_RXFLU        ((T_Reg32 *) 0xF0100540)->bit1
#define ASC2_RXFCON_RXTMEN       ((T_Reg32 *) 0xF0100540)->bit2

// ASC Transmit Buffer Service Request Control Register
#define ASC2_TBSRC             (*((uword volatile *) 0xF01005FC))
#define ASC2_TBSRC_CLRR          ((T_Reg32 *) 0xF01005FC)->bit14
#define ASC2_TBSRC_SETR          ((T_Reg32 *) 0xF01005FC)->bit15
#define ASC2_TBSRC_SRE           ((T_Reg32 *) 0xF01005FC)->bit12
#define ASC2_TBSRC_SRR           ((T_Reg32 *) 0xF01005FC)->bit13
#define ASC2_TBSRC_TOS           ((T_Reg32 *) 0xF01005FC)->bit10

// ASC Transmit Buffer Register
#define ASC2_TBUF              (*((uword volatile *) 0xF0100520))

// ASC Transmit Interrupt Service Request Control Register
#define ASC2_TSRC              (*((uword volatile *) 0xF01005F0))
#define ASC2_TSRC_CLRR           ((T_Reg32 *) 0xF01005F0)->bit14
#define ASC2_TSRC_SETR           ((T_Reg32 *) 0xF01005F0)->bit15
#define ASC2_TSRC_SRE            ((T_Reg32 *) 0xF01005F0)->bit12
#define ASC2_TSRC_SRR            ((T_Reg32 *) 0xF01005F0)->bit13
#define ASC2_TSRC_TOS            ((T_Reg32 *) 0xF01005F0)->bit10

// SSC Transmit FIFO Control Register
#define ASC2_TXFCON            (*((uword volatile *) 0xF0100544))
#define ASC2_TXFCON_TXFEN        ((T_Reg32 *) 0xF0100544)->bit0
#define ASC2_TXFCON_TXFLU        ((T_Reg32 *) 0xF0100544)->bit1
#define ASC2_TXFCON_TXTMEN       ((T_Reg32 *) 0xF0100544)->bit2

// ASC Hardware Bits Control Register
#define ASC2_WHBCON            (*((uword volatile *) 0xF0100550))
#define ASC2_WHBCON_CLRFE        ((T_Reg32 *) 0xF0100550)->bit9
#define ASC2_WHBCON_CLROE        ((T_Reg32 *) 0xF0100550)->bit10
#define ASC2_WHBCON_CLRPE        ((T_Reg32 *) 0xF0100550)->bit8
#define ASC2_WHBCON_CLRREN       ((T_Reg32 *) 0xF0100550)->bit4
#define ASC2_WHBCON_SETFE        ((T_Reg32 *) 0xF0100550)->bit12
#define ASC2_WHBCON_SETOE        ((T_Reg32 *) 0xF0100550)->bit13
#define ASC2_WHBCON_SETPE        ((T_Reg32 *) 0xF0100550)->bit11
#define ASC2_WHBCON_SETREN       ((T_Reg32 *) 0xF0100550)->bit5

// Interrupt Vector Table Pointer
#define BIV                    (*((uword volatile *) 0xF7E1FE20))
#define BIV_0                    0x00000001

// Trap Vector Table Pointer
#define BTV                    (*((uword volatile *) 0xF7E1FE24))
#define BTV_0                    0x00000001

// MultiCAN Clock Control Register
#define CAN_CLC                (*((uword volatile *) 0xF0004000))
#define CAN_CLC_DISR             0x00000001
#define CAN_CLC_DISS             0x00000002
#define CAN_CLC_EDIS             0x00000008
#define CAN_CLC_SBWE             0x00000010
#define CAN_CLC_SPEN             0x00000004

// MultiCAN Fractional Divider Register
#define CAN_FDR                (*((uword volatile *) 0xF000400C))
#define CAN_FDR_DISCLK           0x80000000
#define CAN_FDR_ENHW             0x40000000
#define CAN_FDR_SUSACK           0x10000000
#define CAN_FDR_SUSREQ           0x20000000

// MultiCAN Module Identification Register
#define CAN_ID                 (*((uword volatile *) 0xF0004008))

// List Register 0
#define CAN_LIST0              (*((uword volatile *) 0xF0004100))
#define CAN_LIST0_EMPTY          0x01000000

// List Register 1
#define CAN_LIST1              (*((uword volatile *) 0xF0004104))
#define CAN_LIST1_EMPTY          0x01000000

// List Register 2
#define CAN_LIST2              (*((uword volatile *) 0xF0004108))
#define CAN_LIST2_EMPTY          0x01000000

// List Register 3
#define CAN_LIST3              (*((uword volatile *) 0xF000410C))
#define CAN_LIST3_EMPTY          0x01000000

// List Register 4
#define CAN_LIST4              (*((uword volatile *) 0xF0004110))
#define CAN_LIST4_EMPTY          0x01000000

// List Register 5
#define CAN_LIST5              (*((uword volatile *) 0xF0004114))
#define CAN_LIST5_EMPTY          0x01000000

// List Register 6
#define CAN_LIST6              (*((uword volatile *) 0xF0004118))
#define CAN_LIST6_EMPTY          0x01000000

// List Register 7
#define CAN_LIST7              (*((uword volatile *) 0xF000411C))
#define CAN_LIST7_EMPTY          0x01000000

// MultiCAN Module Control Register
#define CAN_MCR                (*((uword volatile *) 0xF00041C8))

// Module Interrupt Trigger Register
#define CAN_MITR               (*((uword volatile *) 0xF00041CC))

// Message Object 0 Acceptance Mask Register
#define CAN_MOAMR0             (*((uword volatile *) 0xF000460C))
#define CAN_MOAMR0_MIDE          0x20000000

// Message Object 1 Acceptance Mask Register
#define CAN_MOAMR1             (*((uword volatile *) 0xF000462C))
#define CAN_MOAMR1_MIDE          0x20000000

// Message Object 10 Acceptance Mask Register
#define CAN_MOAMR10            (*((uword volatile *) 0xF000474C))
#define CAN_MOAMR10_MIDE         0x20000000

// Message Object 100 Acceptance Mask Register
#define CAN_MOAMR100           (*((uword volatile *) 0xF000528C))
#define CAN_MOAMR100_MIDE        0x20000000

// Message Object 101 Acceptance Mask Register
#define CAN_MOAMR101           (*((uword volatile *) 0xF00052AC))
#define CAN_MOAMR101_MIDE        0x20000000

// Message Object 102 Acceptance Mask Register
#define CAN_MOAMR102           (*((uword volatile *) 0xF00052CC))
#define CAN_MOAMR102_MIDE        0x20000000

// Message Object 103 Acceptance Mask Register
#define CAN_MOAMR103           (*((uword volatile *) 0xF00052EC))
#define CAN_MOAMR103_MIDE        0x20000000

// Message Object 104 Acceptance Mask Register
#define CAN_MOAMR104           (*((uword volatile *) 0xF000530C))
#define CAN_MOAMR104_MIDE        0x20000000

// Message Object 105 Acceptance Mask Register
#define CAN_MOAMR105           (*((uword volatile *) 0xF000532C))
#define CAN_MOAMR105_MIDE        0x20000000

// Message Object 106 Acceptance Mask Register
#define CAN_MOAMR106           (*((uword volatile *) 0xF000534C))
#define CAN_MOAMR106_MIDE        0x20000000

// Message Object 107 Acceptance Mask Register
#define CAN_MOAMR107           (*((uword volatile *) 0xF000536C))
#define CAN_MOAMR107_MIDE        0x20000000

// Message Object 108 Acceptance Mask Register
#define CAN_MOAMR108           (*((uword volatile *) 0xF000538C))
#define CAN_MOAMR108_MIDE        0x20000000

// Message Object 109 Acceptance Mask Register
#define CAN_MOAMR109           (*((uword volatile *) 0xF00053AC))
#define CAN_MOAMR109_MIDE        0x20000000

// Message Object 11 Acceptance Mask Register
#define CAN_MOAMR11            (*((uword volatile *) 0xF000476C))
#define CAN_MOAMR11_MIDE         0x20000000

// Message Object 110 Acceptance Mask Register
#define CAN_MOAMR110           (*((uword volatile *) 0xF00053CC))
#define CAN_MOAMR110_MIDE        0x20000000

// Message Object 111 Acceptance Mask Register
#define CAN_MOAMR111           (*((uword volatile *) 0xF00053EC))
#define CAN_MOAMR111_MIDE        0x20000000

// Message Object 112 Acceptance Mask Register
#define CAN_MOAMR112           (*((uword volatile *) 0xF000540C))
#define CAN_MOAMR112_MIDE        0x20000000

// Message Object 113 Acceptance Mask Register
#define CAN_MOAMR113           (*((uword volatile *) 0xF000542C))
#define CAN_MOAMR113_MIDE        0x20000000

// Message Object 114 Acceptance Mask Register
#define CAN_MOAMR114           (*((uword volatile *) 0xF000544C))
#define CAN_MOAMR114_MIDE        0x20000000

// Message Object 115 Acceptance Mask Register
#define CAN_MOAMR115           (*((uword volatile *) 0xF000546C))
#define CAN_MOAMR115_MIDE        0x20000000

// Message Object 116 Acceptance Mask Register
#define CAN_MOAMR116           (*((uword volatile *) 0xF000548C))
#define CAN_MOAMR116_MIDE        0x20000000

// Message Object 117 Acceptance Mask Register
#define CAN_MOAMR117           (*((uword volatile *) 0xF00054AC))
#define CAN_MOAMR117_MIDE        0x20000000

// Message Object 118 Acceptance Mask Register
#define CAN_MOAMR118           (*((uword volatile *) 0xF00054CC))
#define CAN_MOAMR118_MIDE        0x20000000

// Message Object 119 Acceptance Mask Register
#define CAN_MOAMR119           (*((uword volatile *) 0xF00054EC))
#define CAN_MOAMR119_MIDE        0x20000000

// Message Object 12 Acceptance Mask Register
#define CAN_MOAMR12            (*((uword volatile *) 0xF000478C))
#define CAN_MOAMR12_MIDE         0x20000000

// Message Object 120 Acceptance Mask Register
#define CAN_MOAMR120           (*((uword volatile *) 0xF000550C))
#define CAN_MOAMR120_MIDE        0x20000000

// Message Object 121 Acceptance Mask Register
#define CAN_MOAMR121           (*((uword volatile *) 0xF000552C))
#define CAN_MOAMR121_MIDE        0x20000000

// Message Object 122 Acceptance Mask Register
#define CAN_MOAMR122           (*((uword volatile *) 0xF000554C))
#define CAN_MOAMR122_MIDE        0x20000000

// Message Object 123 Acceptance Mask Register
#define CAN_MOAMR123           (*((uword volatile *) 0xF000556C))
#define CAN_MOAMR123_MIDE        0x20000000

// Message Object 124 Acceptance Mask Register
#define CAN_MOAMR124           (*((uword volatile *) 0xF000558C))
#define CAN_MOAMR124_MIDE        0x20000000

// Message Object 125 Acceptance Mask Register
#define CAN_MOAMR125           (*((uword volatile *) 0xF00055AC))
#define CAN_MOAMR125_MIDE        0x20000000

// Message Object 126 Acceptance Mask Register
#define CAN_MOAMR126           (*((uword volatile *) 0xF00055CC))
#define CAN_MOAMR126_MIDE        0x20000000

// Message Object 127 Acceptance Mask Register
#define CAN_MOAMR127           (*((uword volatile *) 0xF00055EC))
#define CAN_MOAMR127_MIDE        0x20000000

// Message Object 13 Acceptance Mask Register
#define CAN_MOAMR13            (*((uword volatile *) 0xF00047AC))
#define CAN_MOAMR13_MIDE         0x20000000

// Message Object 14 Acceptance Mask Register
#define CAN_MOAMR14            (*((uword volatile *) 0xF00047CC))
#define CAN_MOAMR14_MIDE         0x20000000

// Message Object 15 Acceptance Mask Register
#define CAN_MOAMR15            (*((uword volatile *) 0xF00047EC))
#define CAN_MOAMR15_MIDE         0x20000000

// Message Object 16 Acceptance Mask Register
#define CAN_MOAMR16            (*((uword volatile *) 0xF000480C))
#define CAN_MOAMR16_MIDE         0x20000000

// Message Object 17 Acceptance Mask Register
#define CAN_MOAMR17            (*((uword volatile *) 0xF000482C))
#define CAN_MOAMR17_MIDE         0x20000000

// Message Object 18 Acceptance Mask Register
#define CAN_MOAMR18            (*((uword volatile *) 0xF000484C))
#define CAN_MOAMR18_MIDE         0x20000000

// Message Object 19 Acceptance Mask Register
#define CAN_MOAMR19            (*((uword volatile *) 0xF000486C))
#define CAN_MOAMR19_MIDE         0x20000000

// Message Object 2 Acceptance Mask Register
#define CAN_MOAMR2             (*((uword volatile *) 0xF000464C))
#define CAN_MOAMR2_MIDE          0x20000000

// Message Object 20 Acceptance Mask Register
#define CAN_MOAMR20            (*((uword volatile *) 0xF000488C))
#define CAN_MOAMR20_MIDE         0x20000000

// Message Object 21 Acceptance Mask Register
#define CAN_MOAMR21            (*((uword volatile *) 0xF00048AC))
#define CAN_MOAMR21_MIDE         0x20000000

// Message Object 22 Acceptance Mask Register
#define CAN_MOAMR22            (*((uword volatile *) 0xF00048CC))
#define CAN_MOAMR22_MIDE         0x20000000

// Message Object 23 Acceptance Mask Register
#define CAN_MOAMR23            (*((uword volatile *) 0xF00048EC))
#define CAN_MOAMR23_MIDE         0x20000000

// Message Object 24 Acceptance Mask Register
#define CAN_MOAMR24            (*((uword volatile *) 0xF000490C))
#define CAN_MOAMR24_MIDE         0x20000000

// Message Object 25 Acceptance Mask Register
#define CAN_MOAMR25            (*((uword volatile *) 0xF000492C))
#define CAN_MOAMR25_MIDE         0x20000000

// Message Object 26 Acceptance Mask Register
#define CAN_MOAMR26            (*((uword volatile *) 0xF000494C))
#define CAN_MOAMR26_MIDE         0x20000000

// Message Object 27 Acceptance Mask Register
#define CAN_MOAMR27            (*((uword volatile *) 0xF000496C))
#define CAN_MOAMR27_MIDE         0x20000000

// Message Object 28 Acceptance Mask Register
#define CAN_MOAMR28            (*((uword volatile *) 0xF000498C))
#define CAN_MOAMR28_MIDE         0x20000000

// Message Object 29 Acceptance Mask Register
#define CAN_MOAMR29            (*((uword volatile *) 0xF00049AC))
#define CAN_MOAMR29_MIDE         0x20000000

// Message Object 3 Acceptance Mask Register
#define CAN_MOAMR3             (*((uword volatile *) 0xF000466C))
#define CAN_MOAMR3_MIDE          0x20000000

// Message Object 30 Acceptance Mask Register
#define CAN_MOAMR30            (*((uword volatile *) 0xF00049CC))
#define CAN_MOAMR30_MIDE         0x20000000

// Message Object 31 Acceptance Mask Register
#define CAN_MOAMR31            (*((uword volatile *) 0xF00049EC))
#define CAN_MOAMR31_MIDE         0x20000000

// Message Object 32 Acceptance Mask Register
#define CAN_MOAMR32            (*((uword volatile *) 0xF0004A0C))
#define CAN_MOAMR32_MIDE         0x20000000

// Message Object 33 Acceptance Mask Register
#define CAN_MOAMR33            (*((uword volatile *) 0xF0004A2C))
#define CAN_MOAMR33_MIDE         0x20000000

// Message Object 34 Acceptance Mask Register
#define CAN_MOAMR34            (*((uword volatile *) 0xF0004A4C))
#define CAN_MOAMR34_MIDE         0x20000000

// Message Object 35 Acceptance Mask Register
#define CAN_MOAMR35            (*((uword volatile *) 0xF0004A6C))
#define CAN_MOAMR35_MIDE         0x20000000

// Message Object 36 Acceptance Mask Register
#define CAN_MOAMR36            (*((uword volatile *) 0xF0004A8C))
#define CAN_MOAMR36_MIDE         0x20000000

// Message Object 37 Acceptance Mask Register
#define CAN_MOAMR37            (*((uword volatile *) 0xF0004AAC))
#define CAN_MOAMR37_MIDE         0x20000000

// Message Object 38 Acceptance Mask Register
#define CAN_MOAMR38            (*((uword volatile *) 0xF0004ACC))
#define CAN_MOAMR38_MIDE         0x20000000

// Message Object 39 Acceptance Mask Register
#define CAN_MOAMR39            (*((uword volatile *) 0xF0004AEC))
#define CAN_MOAMR39_MIDE         0x20000000

// Message Object 4 Acceptance Mask Register
#define CAN_MOAMR4             (*((uword volatile *) 0xF000468C))
#define CAN_MOAMR4_MIDE          0x20000000

// Message Object 40 Acceptance Mask Register
#define CAN_MOAMR40            (*((uword volatile *) 0xF0004B0C))
#define CAN_MOAMR40_MIDE         0x20000000

// Message Object 41 Acceptance Mask Register
#define CAN_MOAMR41            (*((uword volatile *) 0xF0004B2C))
#define CAN_MOAMR41_MIDE         0x20000000

// Message Object 42 Acceptance Mask Register
#define CAN_MOAMR42            (*((uword volatile *) 0xF0004B4C))
#define CAN_MOAMR42_MIDE         0x20000000

// Message Object 43 Acceptance Mask Register
#define CAN_MOAMR43            (*((uword volatile *) 0xF0004B6C))
#define CAN_MOAMR43_MIDE         0x20000000

// Message Object 44 Acceptance Mask Register
#define CAN_MOAMR44            (*((uword volatile *) 0xF0004B8C))
#define CAN_MOAMR44_MIDE         0x20000000

// Message Object 45 Acceptance Mask Register
#define CAN_MOAMR45            (*((uword volatile *) 0xF0004BAC))
#define CAN_MOAMR45_MIDE         0x20000000

// Message Object 46 Acceptance Mask Register
#define CAN_MOAMR46            (*((uword volatile *) 0xF0004BCC))
#define CAN_MOAMR46_MIDE         0x20000000

// Message Object 47 Acceptance Mask Register
#define CAN_MOAMR47            (*((uword volatile *) 0xF0004BEC))
#define CAN_MOAMR47_MIDE         0x20000000

// Message Object 48 Acceptance Mask Register
#define CAN_MOAMR48            (*((uword volatile *) 0xF0004C0C))
#define CAN_MOAMR48_MIDE         0x20000000

// Message Object 49 Acceptance Mask Register
#define CAN_MOAMR49            (*((uword volatile *) 0xF0004C2C))
#define CAN_MOAMR49_MIDE         0x20000000

// Message Object 5 Acceptance Mask Register
#define CAN_MOAMR5             (*((uword volatile *) 0xF00046AC))
#define CAN_MOAMR5_MIDE          0x20000000

// Message Object 50 Acceptance Mask Register
#define CAN_MOAMR50            (*((uword volatile *) 0xF0004C4C))
#define CAN_MOAMR50_MIDE         0x20000000

// Message Object 51 Acceptance Mask Register
#define CAN_MOAMR51            (*((uword volatile *) 0xF0004C6C))
#define CAN_MOAMR51_MIDE         0x20000000

// Message Object 52 Acceptance Mask Register
#define CAN_MOAMR52            (*((uword volatile *) 0xF0004C8C))
#define CAN_MOAMR52_MIDE         0x20000000

// Message Object 53 Acceptance Mask Register
#define CAN_MOAMR53            (*((uword volatile *) 0xF0004CAC))
#define CAN_MOAMR53_MIDE         0x20000000

// Message Object 54 Acceptance Mask Register
#define CAN_MOAMR54            (*((uword volatile *) 0xF0004CCC))
#define CAN_MOAMR54_MIDE         0x20000000

// Message Object 55 Acceptance Mask Register
#define CAN_MOAMR55            (*((uword volatile *) 0xF0004CEC))
#define CAN_MOAMR55_MIDE         0x20000000

// Message Object 56 Acceptance Mask Register
#define CAN_MOAMR56            (*((uword volatile *) 0xF0004D0C))
#define CAN_MOAMR56_MIDE         0x20000000

// Message Object 57 Acceptance Mask Register
#define CAN_MOAMR57            (*((uword volatile *) 0xF0004D2C))
#define CAN_MOAMR57_MIDE         0x20000000

// Message Object 58 Acceptance Mask Register
#define CAN_MOAMR58            (*((uword volatile *) 0xF0004D4C))
#define CAN_MOAMR58_MIDE         0x20000000

// Message Object 59 Acceptance Mask Register
#define CAN_MOAMR59            (*((uword volatile *) 0xF0004D6C))
#define CAN_MOAMR59_MIDE         0x20000000

// Message Object 6 Acceptance Mask Register
#define CAN_MOAMR6             (*((uword volatile *) 0xF00046CC))
#define CAN_MOAMR6_MIDE          0x20000000

// Message Object 60 Acceptance Mask Register
#define CAN_MOAMR60            (*((uword volatile *) 0xF0004D8C))
#define CAN_MOAMR60_MIDE         0x20000000

// Message Object 61 Acceptance Mask Register
#define CAN_MOAMR61            (*((uword volatile *) 0xF0004DAC))
#define CAN_MOAMR61_MIDE         0x20000000

// Message Object 62 Acceptance Mask Register
#define CAN_MOAMR62            (*((uword volatile *) 0xF0004DCC))
#define CAN_MOAMR62_MIDE         0x20000000

// Message Object 63 Acceptance Mask Register
#define CAN_MOAMR63            (*((uword volatile *) 0xF0004DEC))
#define CAN_MOAMR63_MIDE         0x20000000

// Message Object 64 Acceptance Mask Register
#define CAN_MOAMR64            (*((uword volatile *) 0xF0004E0C))
#define CAN_MOAMR64_MIDE         0x20000000

// Message Object 65 Acceptance Mask Register
#define CAN_MOAMR65            (*((uword volatile *) 0xF0004E2C))
#define CAN_MOAMR65_MIDE         0x20000000

// Message Object 66 Acceptance Mask Register
#define CAN_MOAMR66            (*((uword volatile *) 0xF0004E4C))
#define CAN_MOAMR66_MIDE         0x20000000

// Message Object 67 Acceptance Mask Register
#define CAN_MOAMR67            (*((uword volatile *) 0xF0004E6C))
#define CAN_MOAMR67_MIDE         0x20000000

// Message Object 68 Acceptance Mask Register
#define CAN_MOAMR68            (*((uword volatile *) 0xF0004E8C))
#define CAN_MOAMR68_MIDE         0x20000000

// Message Object 69 Acceptance Mask Register
#define CAN_MOAMR69            (*((uword volatile *) 0xF0004EAC))
#define CAN_MOAMR69_MIDE         0x20000000

// Message Object 7 Acceptance Mask Register
#define CAN_MOAMR7             (*((uword volatile *) 0xF00046EC))
#define CAN_MOAMR7_MIDE          0x20000000

// Message Object 70 Acceptance Mask Register
#define CAN_MOAMR70            (*((uword volatile *) 0xF0004ECC))
#define CAN_MOAMR70_MIDE         0x20000000

// Message Object 71 Acceptance Mask Register
#define CAN_MOAMR71            (*((uword volatile *) 0xF0004EEC))
#define CAN_MOAMR71_MIDE         0x20000000

// Message Object 72 Acceptance Mask Register
#define CAN_MOAMR72            (*((uword volatile *) 0xF0004F0C))
#define CAN_MOAMR72_MIDE         0x20000000

// Message Object 73 Acceptance Mask Register
#define CAN_MOAMR73            (*((uword volatile *) 0xF0004F2C))
#define CAN_MOAMR73_MIDE         0x20000000

// Message Object 74 Acceptance Mask Register
#define CAN_MOAMR74            (*((uword volatile *) 0xF0004F4C))
#define CAN_MOAMR74_MIDE         0x20000000

// Message Object 75 Acceptance Mask Register
#define CAN_MOAMR75            (*((uword volatile *) 0xF0004F6C))
#define CAN_MOAMR75_MIDE         0x20000000

// Message Object 76 Acceptance Mask Register
#define CAN_MOAMR76            (*((uword volatile *) 0xF0004F8C))
#define CAN_MOAMR76_MIDE         0x20000000

// Message Object 77 Acceptance Mask Register
#define CAN_MOAMR77            (*((uword volatile *) 0xF0004FAC))
#define CAN_MOAMR77_MIDE         0x20000000

// Message Object 78 Acceptance Mask Register
#define CAN_MOAMR78            (*((uword volatile *) 0xF0004FCC))
#define CAN_MOAMR78_MIDE         0x20000000

// Message Object 79 Acceptance Mask Register
#define CAN_MOAMR79            (*((uword volatile *) 0xF0004FEC))
#define CAN_MOAMR79_MIDE         0x20000000

// Message Object 8 Acceptance Mask Register
#define CAN_MOAMR8             (*((uword volatile *) 0xF000470C))
#define CAN_MOAMR8_MIDE          0x20000000

// Message Object 80 Acceptance Mask Register
#define CAN_MOAMR80            (*((uword volatile *) 0xF000500C))
#define CAN_MOAMR80_MIDE         0x20000000

// Message Object 81 Acceptance Mask Register
#define CAN_MOAMR81            (*((uword volatile *) 0xF000502C))
#define CAN_MOAMR81_MIDE         0x20000000

// Message Object 82 Acceptance Mask Register
#define CAN_MOAMR82            (*((uword volatile *) 0xF000504C))
#define CAN_MOAMR82_MIDE         0x20000000

// Message Object 83 Acceptance Mask Register
#define CAN_MOAMR83            (*((uword volatile *) 0xF000506C))
#define CAN_MOAMR83_MIDE         0x20000000

// Message Object 84 Acceptance Mask Register
#define CAN_MOAMR84            (*((uword volatile *) 0xF000508C))
#define CAN_MOAMR84_MIDE         0x20000000

// Message Object 85 Acceptance Mask Register
#define CAN_MOAMR85            (*((uword volatile *) 0xF00050AC))
#define CAN_MOAMR85_MIDE         0x20000000

// Message Object 86 Acceptance Mask Register
#define CAN_MOAMR86            (*((uword volatile *) 0xF00050CC))
#define CAN_MOAMR86_MIDE         0x20000000

// Message Object 87 Acceptance Mask Register
#define CAN_MOAMR87            (*((uword volatile *) 0xF00050EC))
#define CAN_MOAMR87_MIDE         0x20000000

// Message Object 88 Acceptance Mask Register
#define CAN_MOAMR88            (*((uword volatile *) 0xF000510C))
#define CAN_MOAMR88_MIDE         0x20000000

// Message Object 89 Acceptance Mask Register
#define CAN_MOAMR89            (*((uword volatile *) 0xF000512C))
#define CAN_MOAMR89_MIDE         0x20000000

// Message Object 9 Acceptance Mask Register
#define CAN_MOAMR9             (*((uword volatile *) 0xF000472C))
#define CAN_MOAMR9_MIDE          0x20000000

// Message Object 90 Acceptance Mask Register
#define CAN_MOAMR90            (*((uword volatile *) 0xF000514C))
#define CAN_MOAMR90_MIDE         0x20000000

// Message Object 91 Acceptance Mask Register
#define CAN_MOAMR91            (*((uword volatile *) 0xF000516C))
#define CAN_MOAMR91_MIDE         0x20000000

// Message Object 92 Acceptance Mask Register
#define CAN_MOAMR92            (*((uword volatile *) 0xF000518C))
#define CAN_MOAMR92_MIDE         0x20000000

// Message Object 93 Acceptance Mask Register
#define CAN_MOAMR93            (*((uword volatile *) 0xF00051AC))
#define CAN_MOAMR93_MIDE         0x20000000

// Message Object 94 Acceptance Mask Register
#define CAN_MOAMR94            (*((uword volatile *) 0xF00051CC))
#define CAN_MOAMR94_MIDE         0x20000000

// Message Object 95 Acceptance Mask Register
#define CAN_MOAMR95            (*((uword volatile *) 0xF00051EC))
#define CAN_MOAMR95_MIDE         0x20000000

// Message Object 96 Acceptance Mask Register
#define CAN_MOAMR96            (*((uword volatile *) 0xF000520C))
#define CAN_MOAMR96_MIDE         0x20000000

// Message Object 97 Acceptance Mask Register
#define CAN_MOAMR97            (*((uword volatile *) 0xF000522C))
#define CAN_MOAMR97_MIDE         0x20000000

// Message Object 98 Acceptance Mask Register
#define CAN_MOAMR98            (*((uword volatile *) 0xF000524C))
#define CAN_MOAMR98_MIDE         0x20000000

// Message Object 99 Acceptance Mask Register
#define CAN_MOAMR99            (*((uword volatile *) 0xF000526C))
#define CAN_MOAMR99_MIDE         0x20000000

// Message Object 0 Arbitration Register
#define CAN_MOAR0              (*((uword volatile *) 0xF0004618))
#define CAN_MOAR0_IDE            0x20000000

// Message Object 1 Arbitration Register
#define CAN_MOAR1              (*((uword volatile *) 0xF0004638))
#define CAN_MOAR1_IDE            0x20000000

// Message Object 10 Arbitration Register
#define CAN_MOAR10             (*((uword volatile *) 0xF0004758))
#define CAN_MOAR10_IDE           0x20000000

// Message Object 100 Arbitration Register
#define CAN_MOAR100            (*((uword volatile *) 0xF0005298))
#define CAN_MOAR100_IDE          0x20000000

// Message Object 101 Arbitration Register
#define CAN_MOAR101            (*((uword volatile *) 0xF00052B8))
#define CAN_MOAR101_IDE          0x20000000

// Message Object 102 Arbitration Register
#define CAN_MOAR102            (*((uword volatile *) 0xF00052D8))
#define CAN_MOAR102_IDE          0x20000000

// Message Object 103 Arbitration Register
#define CAN_MOAR103            (*((uword volatile *) 0xF00052F8))
#define CAN_MOAR103_IDE          0x20000000

// Message Object 104 Arbitration Register
#define CAN_MOAR104            (*((uword volatile *) 0xF0005318))
#define CAN_MOAR104_IDE          0x20000000

// Message Object 105 Arbitration Register
#define CAN_MOAR105            (*((uword volatile *) 0xF0005338))
#define CAN_MOAR105_IDE          0x20000000

// Message Object 106 Arbitration Register
#define CAN_MOAR106            (*((uword volatile *) 0xF0005358))
#define CAN_MOAR106_IDE          0x20000000

// Message Object 107 Arbitration Register
#define CAN_MOAR107            (*((uword volatile *) 0xF0005378))
#define CAN_MOAR107_IDE          0x20000000

// Message Object 108 Arbitration Register
#define CAN_MOAR108            (*((uword volatile *) 0xF0005398))
#define CAN_MOAR108_IDE          0x20000000

// Message Object 109 Arbitration Register
#define CAN_MOAR109            (*((uword volatile *) 0xF00053B8))
#define CAN_MOAR109_IDE          0x20000000

// Message Object 11 Arbitration Register
#define CAN_MOAR11             (*((uword volatile *) 0xF0004778))
#define CAN_MOAR11_IDE           0x20000000

// Message Object 110 Arbitration Register
#define CAN_MOAR110            (*((uword volatile *) 0xF00053D8))
#define CAN_MOAR110_IDE          0x20000000

// Message Object 111 Arbitration Register
#define CAN_MOAR111            (*((uword volatile *) 0xF00053F8))
#define CAN_MOAR111_IDE          0x20000000

// Message Object 112 Arbitration Register
#define CAN_MOAR112            (*((uword volatile *) 0xF0005418))
#define CAN_MOAR112_IDE          0x20000000

// Message Object 113 Arbitration Register
#define CAN_MOAR113            (*((uword volatile *) 0xF0005438))
#define CAN_MOAR113_IDE          0x20000000

// Message Object 114 Arbitration Register
#define CAN_MOAR114            (*((uword volatile *) 0xF0005458))
#define CAN_MOAR114_IDE          0x20000000

// Message Object 115 Arbitration Register
#define CAN_MOAR115            (*((uword volatile *) 0xF0005478))
#define CAN_MOAR115_IDE          0x20000000

// Message Object 116 Arbitration Register
#define CAN_MOAR116            (*((uword volatile *) 0xF0005498))
#define CAN_MOAR116_IDE          0x20000000

// Message Object 117 Arbitration Register
#define CAN_MOAR117            (*((uword volatile *) 0xF00054B8))
#define CAN_MOAR117_IDE          0x20000000

// Message Object 118 Arbitration Register
#define CAN_MOAR118            (*((uword volatile *) 0xF00054D8))
#define CAN_MOAR118_IDE          0x20000000

// Message Object 119 Arbitration Register
#define CAN_MOAR119            (*((uword volatile *) 0xF00054F8))
#define CAN_MOAR119_IDE          0x20000000

// Message Object 12 Arbitration Register
#define CAN_MOAR12             (*((uword volatile *) 0xF0004798))
#define CAN_MOAR12_IDE           0x20000000

// Message Object 120 Arbitration Register
#define CAN_MOAR120            (*((uword volatile *) 0xF0005518))
#define CAN_MOAR120_IDE          0x20000000

// Message Object 121 Arbitration Register
#define CAN_MOAR121            (*((uword volatile *) 0xF0005538))
#define CAN_MOAR121_IDE          0x20000000

// Message Object 122 Arbitration Register
#define CAN_MOAR122            (*((uword volatile *) 0xF0005558))
#define CAN_MOAR122_IDE          0x20000000

// Message Object 123 Arbitration Register
#define CAN_MOAR123            (*((uword volatile *) 0xF0005578))
#define CAN_MOAR123_IDE          0x20000000

// Message Object 124 Arbitration Register
#define CAN_MOAR124            (*((uword volatile *) 0xF0005598))
#define CAN_MOAR124_IDE          0x20000000

// Message Object 125 Arbitration Register
#define CAN_MOAR125            (*((uword volatile *) 0xF00055B8))
#define CAN_MOAR125_IDE          0x20000000

// Message Object 126 Arbitration Register
#define CAN_MOAR126            (*((uword volatile *) 0xF00055D8))
#define CAN_MOAR126_IDE          0x20000000

// Message Object 127 Arbitration Register
#define CAN_MOAR127            (*((uword volatile *) 0xF00055F8))
#define CAN_MOAR127_IDE          0x20000000

// Message Object 13 Arbitration Register
#define CAN_MOAR13             (*((uword volatile *) 0xF00047B8))
#define CAN_MOAR13_IDE           0x20000000

// Message Object 14 Arbitration Register
#define CAN_MOAR14             (*((uword volatile *) 0xF00047D8))
#define CAN_MOAR14_IDE           0x20000000

// Message Object 15 Arbitration Register
#define CAN_MOAR15             (*((uword volatile *) 0xF00047F8))
#define CAN_MOAR15_IDE           0x20000000

// Message Object 16 Arbitration Register
#define CAN_MOAR16             (*((uword volatile *) 0xF0004818))
#define CAN_MOAR16_IDE           0x20000000

// Message Object 17 Arbitration Register
#define CAN_MOAR17             (*((uword volatile *) 0xF0004838))
#define CAN_MOAR17_IDE           0x20000000

// Message Object 18 Arbitration Register
#define CAN_MOAR18             (*((uword volatile *) 0xF0004858))
#define CAN_MOAR18_IDE           0x20000000

// Message Object 19 Arbitration Register
#define CAN_MOAR19             (*((uword volatile *) 0xF0004878))
#define CAN_MOAR19_IDE           0x20000000

// Message Object 2 Arbitration Register
#define CAN_MOAR2              (*((uword volatile *) 0xF0004658))
#define CAN_MOAR2_IDE            0x20000000

// Message Object 20 Arbitration Register
#define CAN_MOAR20             (*((uword volatile *) 0xF0004898))
#define CAN_MOAR20_IDE           0x20000000

// Message Object 21 Arbitration Register
#define CAN_MOAR21             (*((uword volatile *) 0xF00048B8))
#define CAN_MOAR21_IDE           0x20000000

// Message Object 22 Arbitration Register
#define CAN_MOAR22             (*((uword volatile *) 0xF00048D8))
#define CAN_MOAR22_IDE           0x20000000

// Message Object 23 Arbitration Register
#define CAN_MOAR23             (*((uword volatile *) 0xF00048F8))
#define CAN_MOAR23_IDE           0x20000000

// Message Object 24 Arbitration Register
#define CAN_MOAR24             (*((uword volatile *) 0xF0004918))
#define CAN_MOAR24_IDE           0x20000000

// Message Object 25 Arbitration Register
#define CAN_MOAR25             (*((uword volatile *) 0xF0004938))
#define CAN_MOAR25_IDE           0x20000000

// Message Object 26 Arbitration Register
#define CAN_MOAR26             (*((uword volatile *) 0xF0004958))
#define CAN_MOAR26_IDE           0x20000000

// Message Object 27 Arbitration Register
#define CAN_MOAR27             (*((uword volatile *) 0xF0004978))
#define CAN_MOAR27_IDE           0x20000000

// Message Object 28 Arbitration Register
#define CAN_MOAR28             (*((uword volatile *) 0xF0004998))
#define CAN_MOAR28_IDE           0x20000000

// Message Object 29 Arbitration Register
#define CAN_MOAR29             (*((uword volatile *) 0xF00049B8))
#define CAN_MOAR29_IDE           0x20000000

// Message Object 3 Arbitration Register
#define CAN_MOAR3              (*((uword volatile *) 0xF0004678))
#define CAN_MOAR3_IDE            0x20000000

// Message Object 30 Arbitration Register
#define CAN_MOAR30             (*((uword volatile *) 0xF00049D8))
#define CAN_MOAR30_IDE           0x20000000

// Message Object 31 Arbitration Register
#define CAN_MOAR31             (*((uword volatile *) 0xF00049F8))
#define CAN_MOAR31_IDE           0x20000000

// Message Object 32 Arbitration Register
#define CAN_MOAR32             (*((uword volatile *) 0xF0004A18))
#define CAN_MOAR32_IDE           0x20000000

// Message Object 33 Arbitration Register
#define CAN_MOAR33             (*((uword volatile *) 0xF0004A38))
#define CAN_MOAR33_IDE           0x20000000

// Message Object 34 Arbitration Register
#define CAN_MOAR34             (*((uword volatile *) 0xF0004A58))
#define CAN_MOAR34_IDE           0x20000000

// Message Object 35 Arbitration Register
#define CAN_MOAR35             (*((uword volatile *) 0xF0004A78))
#define CAN_MOAR35_IDE           0x20000000

// Message Object 36 Arbitration Register
#define CAN_MOAR36             (*((uword volatile *) 0xF0004A98))
#define CAN_MOAR36_IDE           0x20000000

// Message Object 37 Arbitration Register
#define CAN_MOAR37             (*((uword volatile *) 0xF0004AB8))
#define CAN_MOAR37_IDE           0x20000000

// Message Object 38 Arbitration Register
#define CAN_MOAR38             (*((uword volatile *) 0xF0004AD8))
#define CAN_MOAR38_IDE           0x20000000

// Message Object 39 Arbitration Register
#define CAN_MOAR39             (*((uword volatile *) 0xF0004AF8))
#define CAN_MOAR39_IDE           0x20000000

// Message Object 4 Arbitration Register
#define CAN_MOAR4              (*((uword volatile *) 0xF0004698))
#define CAN_MOAR4_IDE            0x20000000

// Message Object 40 Arbitration Register
#define CAN_MOAR40             (*((uword volatile *) 0xF0004B18))
#define CAN_MOAR40_IDE           0x20000000

// Message Object 41 Arbitration Register
#define CAN_MOAR41             (*((uword volatile *) 0xF0004B38))
#define CAN_MOAR41_IDE           0x20000000

// Message Object 42 Arbitration Register
#define CAN_MOAR42             (*((uword volatile *) 0xF0004B58))
#define CAN_MOAR42_IDE           0x20000000

// Message Object 43 Arbitration Register
#define CAN_MOAR43             (*((uword volatile *) 0xF0004B78))
#define CAN_MOAR43_IDE           0x20000000

// Message Object 44 Arbitration Register
#define CAN_MOAR44             (*((uword volatile *) 0xF0004B98))
#define CAN_MOAR44_IDE           0x20000000

// Message Object 45 Arbitration Register
#define CAN_MOAR45             (*((uword volatile *) 0xF0004BB8))
#define CAN_MOAR45_IDE           0x20000000

// Message Object 46 Arbitration Register
#define CAN_MOAR46             (*((uword volatile *) 0xF0004BD8))
#define CAN_MOAR46_IDE           0x20000000

// Message Object 47 Arbitration Register
#define CAN_MOAR47             (*((uword volatile *) 0xF0004BF8))
#define CAN_MOAR47_IDE           0x20000000

// Message Object 48 Arbitration Register
#define CAN_MOAR48             (*((uword volatile *) 0xF0004C18))
#define CAN_MOAR48_IDE           0x20000000

// Message Object 49 Arbitration Register
#define CAN_MOAR49             (*((uword volatile *) 0xF0004C38))
#define CAN_MOAR49_IDE           0x20000000

// Message Object 5 Arbitration Register
#define CAN_MOAR5              (*((uword volatile *) 0xF00046B8))
#define CAN_MOAR5_IDE            0x20000000

// Message Object 50 Arbitration Register
#define CAN_MOAR50             (*((uword volatile *) 0xF0004C58))
#define CAN_MOAR50_IDE           0x20000000

// Message Object 51 Arbitration Register
#define CAN_MOAR51             (*((uword volatile *) 0xF0004C78))
#define CAN_MOAR51_IDE           0x20000000

// Message Object 52 Arbitration Register
#define CAN_MOAR52             (*((uword volatile *) 0xF0004C98))
#define CAN_MOAR52_IDE           0x20000000

// Message Object 53 Arbitration Register
#define CAN_MOAR53             (*((uword volatile *) 0xF0004CB8))
#define CAN_MOAR53_IDE           0x20000000

// Message Object 54 Arbitration Register
#define CAN_MOAR54             (*((uword volatile *) 0xF0004CD8))
#define CAN_MOAR54_IDE           0x20000000

// Message Object 55 Arbitration Register
#define CAN_MOAR55             (*((uword volatile *) 0xF0004CF8))
#define CAN_MOAR55_IDE           0x20000000

// Message Object 56 Arbitration Register
#define CAN_MOAR56             (*((uword volatile *) 0xF0004D18))
#define CAN_MOAR56_IDE           0x20000000

// Message Object 57 Arbitration Register
#define CAN_MOAR57             (*((uword volatile *) 0xF0004D38))
#define CAN_MOAR57_IDE           0x20000000

// Message Object 58 Arbitration Register
#define CAN_MOAR58             (*((uword volatile *) 0xF0004D58))
#define CAN_MOAR58_IDE           0x20000000

// Message Object 59 Arbitration Register
#define CAN_MOAR59             (*((uword volatile *) 0xF0004D78))
#define CAN_MOAR59_IDE           0x20000000

// Message Object 6 Arbitration Register
#define CAN_MOAR6              (*((uword volatile *) 0xF00046D8))
#define CAN_MOAR6_IDE            0x20000000

// Message Object 60 Arbitration Register
#define CAN_MOAR60             (*((uword volatile *) 0xF0004D98))
#define CAN_MOAR60_IDE           0x20000000

// Message Object 61 Arbitration Register
#define CAN_MOAR61             (*((uword volatile *) 0xF0004DB8))
#define CAN_MOAR61_IDE           0x20000000

// Message Object 62 Arbitration Register
#define CAN_MOAR62             (*((uword volatile *) 0xF0004DD8))
#define CAN_MOAR62_IDE           0x20000000

// Message Object 63 Arbitration Register
#define CAN_MOAR63             (*((uword volatile *) 0xF0004DF8))
#define CAN_MOAR63_IDE           0x20000000

// Message Object 64 Arbitration Register
#define CAN_MOAR64             (*((uword volatile *) 0xF0004E18))
#define CAN_MOAR64_IDE           0x20000000

// Message Object 65 Arbitration Register
#define CAN_MOAR65             (*((uword volatile *) 0xF0004E38))
#define CAN_MOAR65_IDE           0x20000000

// Message Object 66 Arbitration Register
#define CAN_MOAR66             (*((uword volatile *) 0xF0004E58))
#define CAN_MOAR66_IDE           0x20000000

// Message Object 67 Arbitration Register
#define CAN_MOAR67             (*((uword volatile *) 0xF0004E78))
#define CAN_MOAR67_IDE           0x20000000

// Message Object 68 Arbitration Register
#define CAN_MOAR68             (*((uword volatile *) 0xF0004E98))
#define CAN_MOAR68_IDE           0x20000000

// Message Object 69 Arbitration Register
#define CAN_MOAR69             (*((uword volatile *) 0xF0004EB8))
#define CAN_MOAR69_IDE           0x20000000

// Message Object 7 Arbitration Register
#define CAN_MOAR7              (*((uword volatile *) 0xF00046F8))
#define CAN_MOAR7_IDE            0x20000000

// Message Object 70 Arbitration Register
#define CAN_MOAR70             (*((uword volatile *) 0xF0004ED8))
#define CAN_MOAR70_IDE           0x20000000

// Message Object 71 Arbitration Register
#define CAN_MOAR71             (*((uword volatile *) 0xF0004EF8))
#define CAN_MOAR71_IDE           0x20000000

// Message Object 72 Arbitration Register
#define CAN_MOAR72             (*((uword volatile *) 0xF0004F18))
#define CAN_MOAR72_IDE           0x20000000

// Message Object 73 Arbitration Register
#define CAN_MOAR73             (*((uword volatile *) 0xF0004F38))
#define CAN_MOAR73_IDE           0x20000000

// Message Object 74 Arbitration Register
#define CAN_MOAR74             (*((uword volatile *) 0xF0004F58))
#define CAN_MOAR74_IDE           0x20000000

// Message Object 75 Arbitration Register
#define CAN_MOAR75             (*((uword volatile *) 0xF0004F78))
#define CAN_MOAR75_IDE           0x20000000

// Message Object 76 Arbitration Register
#define CAN_MOAR76             (*((uword volatile *) 0xF0004F98))
#define CAN_MOAR76_IDE           0x20000000

// Message Object 77 Arbitration Register
#define CAN_MOAR77             (*((uword volatile *) 0xF0004FB8))
#define CAN_MOAR77_IDE           0x20000000

// Message Object 78 Arbitration Register
#define CAN_MOAR78             (*((uword volatile *) 0xF0004FD8))
#define CAN_MOAR78_IDE           0x20000000

// Message Object 79 Arbitration Register
#define CAN_MOAR79             (*((uword volatile *) 0xF0004FF8))
#define CAN_MOAR79_IDE           0x20000000

// Message Object 8 Arbitration Register
#define CAN_MOAR8              (*((uword volatile *) 0xF0004718))
#define CAN_MOAR8_IDE            0x20000000

// Message Object 80 Arbitration Register
#define CAN_MOAR80             (*((uword volatile *) 0xF0005018))
#define CAN_MOAR80_IDE           0x20000000

// Message Object 81 Arbitration Register
#define CAN_MOAR81             (*((uword volatile *) 0xF0005038))
#define CAN_MOAR81_IDE           0x20000000

// Message Object 82 Arbitration Register
#define CAN_MOAR82             (*((uword volatile *) 0xF0005058))
#define CAN_MOAR82_IDE           0x20000000

// Message Object 83 Arbitration Register
#define CAN_MOAR83             (*((uword volatile *) 0xF0005078))
#define CAN_MOAR83_IDE           0x20000000

// Message Object 84 Arbitration Register
#define CAN_MOAR84             (*((uword volatile *) 0xF0005098))
#define CAN_MOAR84_IDE           0x20000000

// Message Object 85 Arbitration Register
#define CAN_MOAR85             (*((uword volatile *) 0xF00050B8))
#define CAN_MOAR85_IDE           0x20000000

// Message Object 86 Arbitration Register
#define CAN_MOAR86             (*((uword volatile *) 0xF00050D8))
#define CAN_MOAR86_IDE           0x20000000

// Message Object 87 Arbitration Register
#define CAN_MOAR87             (*((uword volatile *) 0xF00050F8))
#define CAN_MOAR87_IDE           0x20000000

// Message Object 88 Arbitration Register
#define CAN_MOAR88             (*((uword volatile *) 0xF0005118))
#define CAN_MOAR88_IDE           0x20000000

// Message Object 89 Arbitration Register
#define CAN_MOAR89             (*((uword volatile *) 0xF0005138))
#define CAN_MOAR89_IDE           0x20000000

// Message Object 9 Arbitration Register
#define CAN_MOAR9              (*((uword volatile *) 0xF0004738))
#define CAN_MOAR9_IDE            0x20000000

// Message Object 90 Arbitration Register
#define CAN_MOAR90             (*((uword volatile *) 0xF0005158))
#define CAN_MOAR90_IDE           0x20000000

// Message Object 91 Arbitration Register
#define CAN_MOAR91             (*((uword volatile *) 0xF0005178))
#define CAN_MOAR91_IDE           0x20000000

// Message Object 92 Arbitration Register
#define CAN_MOAR92             (*((uword volatile *) 0xF0005198))
#define CAN_MOAR92_IDE           0x20000000

// Message Object 93 Arbitration Register
#define CAN_MOAR93             (*((uword volatile *) 0xF00051B8))
#define CAN_MOAR93_IDE           0x20000000

// Message Object 94 Arbitration Register
#define CAN_MOAR94             (*((uword volatile *) 0xF00051D8))
#define CAN_MOAR94_IDE           0x20000000

// Message Object 95 Arbitration Register
#define CAN_MOAR95             (*((uword volatile *) 0xF00051F8))
#define CAN_MOAR95_IDE           0x20000000

// Message Object 96 Arbitration Register
#define CAN_MOAR96             (*((uword volatile *) 0xF0005218))
#define CAN_MOAR96_IDE           0x20000000

// Message Object 97 Arbitration Register
#define CAN_MOAR97             (*((uword volatile *) 0xF0005238))
#define CAN_MOAR97_IDE           0x20000000

// Message Object 98 Arbitration Register
#define CAN_MOAR98             (*((uword volatile *) 0xF0005258))
#define CAN_MOAR98_IDE           0x20000000

// Message Object 99 Arbitration Register
#define CAN_MOAR99             (*((uword volatile *) 0xF0005278))
#define CAN_MOAR99_IDE           0x20000000

// Message Object 0 Control Register
#define CAN_MOCTR0             (*((uword volatile *) 0xF000461C))
#define CAN_MOCTR0_DIR           0x00000800
#define CAN_MOCTR0_MSGLST        0x00000010
#define CAN_MOCTR0_MSGVAL        0x00000020
#define CAN_MOCTR0_NEWDAT        0x00000008
#define CAN_MOCTR0_RTSEL         0x00000040
#define CAN_MOCTR0_RXEN          0x00000080
#define CAN_MOCTR0_RXPND         0x00000001
#define CAN_MOCTR0_RXUPD         0x00000004
#define CAN_MOCTR0_TXEN0         0x00000200
#define CAN_MOCTR0_TXEN1         0x00000400
#define CAN_MOCTR0_TXPND         0x00000002
#define CAN_MOCTR0_TXRQ          0x00000100

// Message Object 1 Control Register
#define CAN_MOCTR1             (*((uword volatile *) 0xF000463C))
#define CAN_MOCTR1_DIR           0x00000800
#define CAN_MOCTR1_MSGLST        0x00000010
#define CAN_MOCTR1_MSGVAL        0x00000020
#define CAN_MOCTR1_NEWDAT        0x00000008
#define CAN_MOCTR1_RTSEL         0x00000040
#define CAN_MOCTR1_RXEN          0x00000080
#define CAN_MOCTR1_RXPND         0x00000001
#define CAN_MOCTR1_RXUPD         0x00000004
#define CAN_MOCTR1_TXEN0         0x00000200
#define CAN_MOCTR1_TXEN1         0x00000400
#define CAN_MOCTR1_TXPND         0x00000002
#define CAN_MOCTR1_TXRQ          0x00000100

// Message Object 10 Control Register
#define CAN_MOCTR10            (*((uword volatile *) 0xF000475C))
#define CAN_MOCTR10_DIR          0x00000800
#define CAN_MOCTR10_MSGLST       0x00000010
#define CAN_MOCTR10_MSGVAL       0x00000020
#define CAN_MOCTR10_NEWDAT       0x00000008
#define CAN_MOCTR10_RTSEL        0x00000040
#define CAN_MOCTR10_RXEN         0x00000080
#define CAN_MOCTR10_RXPND        0x00000001
#define CAN_MOCTR10_RXUPD        0x00000004
#define CAN_MOCTR10_TXEN0        0x00000200
#define CAN_MOCTR10_TXEN1        0x00000400
#define CAN_MOCTR10_TXPND        0x00000002
#define CAN_MOCTR10_TXRQ         0x00000100

// Message Object 100 Control Register
#define CAN_MOCTR100           (*((uword volatile *) 0xF000529C))
#define CAN_MOCTR100_DIR         0x00000800
#define CAN_MOCTR100_MSGLST      0x00000010
#define CAN_MOCTR100_MSGVAL      0x00000020
#define CAN_MOCTR100_NEWDAT      0x00000008
#define CAN_MOCTR100_RTSEL       0x00000040
#define CAN_MOCTR100_RXEN        0x00000080
#define CAN_MOCTR100_RXPND       0x00000001
#define CAN_MOCTR100_RXUPD       0x00000004
#define CAN_MOCTR100_TXEN0       0x00000200
#define CAN_MOCTR100_TXEN1       0x00000400
#define CAN_MOCTR100_TXPND       0x00000002
#define CAN_MOCTR100_TXRQ        0x00000100

// Message Object 101 Control Register
#define CAN_MOCTR101           (*((uword volatile *) 0xF00052BC))
#define CAN_MOCTR101_DIR         0x00000800
#define CAN_MOCTR101_MSGLST      0x00000010
#define CAN_MOCTR101_MSGVAL      0x00000020
#define CAN_MOCTR101_NEWDAT      0x00000008
#define CAN_MOCTR101_RTSEL       0x00000040
#define CAN_MOCTR101_RXEN        0x00000080
#define CAN_MOCTR101_RXPND       0x00000001
#define CAN_MOCTR101_RXUPD       0x00000004
#define CAN_MOCTR101_TXEN0       0x00000200
#define CAN_MOCTR101_TXEN1       0x00000400
#define CAN_MOCTR101_TXPND       0x00000002
#define CAN_MOCTR101_TXRQ        0x00000100

// Message Object 102 Control Register
#define CAN_MOCTR102           (*((uword volatile *) 0xF00052DC))
#define CAN_MOCTR102_DIR         0x00000800
#define CAN_MOCTR102_MSGLST      0x00000010
#define CAN_MOCTR102_MSGVAL      0x00000020
#define CAN_MOCTR102_NEWDAT      0x00000008
#define CAN_MOCTR102_RTSEL       0x00000040
#define CAN_MOCTR102_RXEN        0x00000080
#define CAN_MOCTR102_RXPND       0x00000001
#define CAN_MOCTR102_RXUPD       0x00000004
#define CAN_MOCTR102_TXEN0       0x00000200
#define CAN_MOCTR102_TXEN1       0x00000400
#define CAN_MOCTR102_TXPND       0x00000002
#define CAN_MOCTR102_TXRQ        0x00000100

// Message Object 103 Control Register
#define CAN_MOCTR103           (*((uword volatile *) 0xF00052FC))
#define CAN_MOCTR103_DIR         0x00000800
#define CAN_MOCTR103_MSGLST      0x00000010
#define CAN_MOCTR103_MSGVAL      0x00000020
#define CAN_MOCTR103_NEWDAT      0x00000008
#define CAN_MOCTR103_RTSEL       0x00000040
#define CAN_MOCTR103_RXEN        0x00000080
#define CAN_MOCTR103_RXPND       0x00000001
#define CAN_MOCTR103_RXUPD       0x00000004
#define CAN_MOCTR103_TXEN0       0x00000200
#define CAN_MOCTR103_TXEN1       0x00000400
#define CAN_MOCTR103_TXPND       0x00000002
#define CAN_MOCTR103_TXRQ        0x00000100

// Message Object 104 Control Register
#define CAN_MOCTR104           (*((uword volatile *) 0xF000531C))
#define CAN_MOCTR104_DIR         0x00000800
#define CAN_MOCTR104_MSGLST      0x00000010
#define CAN_MOCTR104_MSGVAL      0x00000020
#define CAN_MOCTR104_NEWDAT      0x00000008
#define CAN_MOCTR104_RTSEL       0x00000040
#define CAN_MOCTR104_RXEN        0x00000080
#define CAN_MOCTR104_RXPND       0x00000001
#define CAN_MOCTR104_RXUPD       0x00000004
#define CAN_MOCTR104_TXEN0       0x00000200
#define CAN_MOCTR104_TXEN1       0x00000400
#define CAN_MOCTR104_TXPND       0x00000002
#define CAN_MOCTR104_TXRQ        0x00000100

// Message Object 105 Control Register
#define CAN_MOCTR105           (*((uword volatile *) 0xF000533C))
#define CAN_MOCTR105_DIR         0x00000800
#define CAN_MOCTR105_MSGLST      0x00000010
#define CAN_MOCTR105_MSGVAL      0x00000020
#define CAN_MOCTR105_NEWDAT      0x00000008
#define CAN_MOCTR105_RTSEL       0x00000040
#define CAN_MOCTR105_RXEN        0x00000080
#define CAN_MOCTR105_RXPND       0x00000001
#define CAN_MOCTR105_RXUPD       0x00000004
#define CAN_MOCTR105_TXEN0       0x00000200
#define CAN_MOCTR105_TXEN1       0x00000400
#define CAN_MOCTR105_TXPND       0x00000002
#define CAN_MOCTR105_TXRQ        0x00000100

// Message Object 106 Control Register
#define CAN_MOCTR106           (*((uword volatile *) 0xF000535C))
#define CAN_MOCTR106_DIR         0x00000800
#define CAN_MOCTR106_MSGLST      0x00000010
#define CAN_MOCTR106_MSGVAL      0x00000020
#define CAN_MOCTR106_NEWDAT      0x00000008
#define CAN_MOCTR106_RTSEL       0x00000040
#define CAN_MOCTR106_RXEN        0x00000080
#define CAN_MOCTR106_RXPND       0x00000001
#define CAN_MOCTR106_RXUPD       0x00000004
#define CAN_MOCTR106_TXEN0       0x00000200
#define CAN_MOCTR106_TXEN1       0x00000400
#define CAN_MOCTR106_TXPND       0x00000002
#define CAN_MOCTR106_TXRQ        0x00000100

// Message Object 107 Control Register
#define CAN_MOCTR107           (*((uword volatile *) 0xF000537C))
#define CAN_MOCTR107_DIR         0x00000800
#define CAN_MOCTR107_MSGLST      0x00000010
#define CAN_MOCTR107_MSGVAL      0x00000020
#define CAN_MOCTR107_NEWDAT      0x00000008
#define CAN_MOCTR107_RTSEL       0x00000040
#define CAN_MOCTR107_RXEN        0x00000080
#define CAN_MOCTR107_RXPND       0x00000001
#define CAN_MOCTR107_RXUPD       0x00000004
#define CAN_MOCTR107_TXEN0       0x00000200
#define CAN_MOCTR107_TXEN1       0x00000400
#define CAN_MOCTR107_TXPND       0x00000002
#define CAN_MOCTR107_TXRQ        0x00000100

// Message Object 108 Control Register
#define CAN_MOCTR108           (*((uword volatile *) 0xF000539C))
#define CAN_MOCTR108_DIR         0x00000800
#define CAN_MOCTR108_MSGLST      0x00000010
#define CAN_MOCTR108_MSGVAL      0x00000020
#define CAN_MOCTR108_NEWDAT      0x00000008
#define CAN_MOCTR108_RTSEL       0x00000040
#define CAN_MOCTR108_RXEN        0x00000080
#define CAN_MOCTR108_RXPND       0x00000001
#define CAN_MOCTR108_RXUPD       0x00000004
#define CAN_MOCTR108_TXEN0       0x00000200
#define CAN_MOCTR108_TXEN1       0x00000400
#define CAN_MOCTR108_TXPND       0x00000002
#define CAN_MOCTR108_TXRQ        0x00000100

// Message Object 109 Control Register
#define CAN_MOCTR109           (*((uword volatile *) 0xF00053BC))
#define CAN_MOCTR109_DIR         0x00000800
#define CAN_MOCTR109_MSGLST      0x00000010
#define CAN_MOCTR109_MSGVAL      0x00000020
#define CAN_MOCTR109_NEWDAT      0x00000008
#define CAN_MOCTR109_RTSEL       0x00000040
#define CAN_MOCTR109_RXEN        0x00000080
#define CAN_MOCTR109_RXPND       0x00000001
#define CAN_MOCTR109_RXUPD       0x00000004
#define CAN_MOCTR109_TXEN0       0x00000200
#define CAN_MOCTR109_TXEN1       0x00000400
#define CAN_MOCTR109_TXPND       0x00000002
#define CAN_MOCTR109_TXRQ        0x00000100

// Message Object 11 Control Register
#define CAN_MOCTR11            (*((uword volatile *) 0xF000477C))
#define CAN_MOCTR11_DIR          0x00000800
#define CAN_MOCTR11_MSGLST       0x00000010
#define CAN_MOCTR11_MSGVAL       0x00000020
#define CAN_MOCTR11_NEWDAT       0x00000008
#define CAN_MOCTR11_RTSEL        0x00000040
#define CAN_MOCTR11_RXEN         0x00000080
#define CAN_MOCTR11_RXPND        0x00000001
#define CAN_MOCTR11_RXUPD        0x00000004
#define CAN_MOCTR11_TXEN0        0x00000200
#define CAN_MOCTR11_TXEN1        0x00000400
#define CAN_MOCTR11_TXPND        0x00000002
#define CAN_MOCTR11_TXRQ         0x00000100

// Message Object 110 Control Register
#define CAN_MOCTR110           (*((uword volatile *) 0xF00053DC))
#define CAN_MOCTR110_DIR         0x00000800
#define CAN_MOCTR110_MSGLST      0x00000010
#define CAN_MOCTR110_MSGVAL      0x00000020
#define CAN_MOCTR110_NEWDAT      0x00000008
#define CAN_MOCTR110_RTSEL       0x00000040
#define CAN_MOCTR110_RXEN        0x00000080
#define CAN_MOCTR110_RXPND       0x00000001
#define CAN_MOCTR110_RXUPD       0x00000004
#define CAN_MOCTR110_TXEN0       0x00000200
#define CAN_MOCTR110_TXEN1       0x00000400
#define CAN_MOCTR110_TXPND       0x00000002
#define CAN_MOCTR110_TXRQ        0x00000100

// Message Object 111 Control Register
#define CAN_MOCTR111           (*((uword volatile *) 0xF00053FC))
#define CAN_MOCTR111_DIR         0x00000800
#define CAN_MOCTR111_MSGLST      0x00000010
#define CAN_MOCTR111_MSGVAL      0x00000020
#define CAN_MOCTR111_NEWDAT      0x00000008
#define CAN_MOCTR111_RTSEL       0x00000040
#define CAN_MOCTR111_RXEN        0x00000080
#define CAN_MOCTR111_RXPND       0x00000001
#define CAN_MOCTR111_RXUPD       0x00000004
#define CAN_MOCTR111_TXEN0       0x00000200
#define CAN_MOCTR111_TXEN1       0x00000400
#define CAN_MOCTR111_TXPND       0x00000002
#define CAN_MOCTR111_TXRQ        0x00000100

// Message Object 112 Control Register
#define CAN_MOCTR112           (*((uword volatile *) 0xF000541C))
#define CAN_MOCTR112_DIR         0x00000800
#define CAN_MOCTR112_MSGLST      0x00000010
#define CAN_MOCTR112_MSGVAL      0x00000020
#define CAN_MOCTR112_NEWDAT      0x00000008
#define CAN_MOCTR112_RTSEL       0x00000040
#define CAN_MOCTR112_RXEN        0x00000080
#define CAN_MOCTR112_RXPND       0x00000001
#define CAN_MOCTR112_RXUPD       0x00000004
#define CAN_MOCTR112_TXEN0       0x00000200
#define CAN_MOCTR112_TXEN1       0x00000400
#define CAN_MOCTR112_TXPND       0x00000002
#define CAN_MOCTR112_TXRQ        0x00000100

// Message Object 113 Control Register
#define CAN_MOCTR113           (*((uword volatile *) 0xF000543C))
#define CAN_MOCTR113_DIR         0x00000800
#define CAN_MOCTR113_MSGLST      0x00000010
#define CAN_MOCTR113_MSGVAL      0x00000020
#define CAN_MOCTR113_NEWDAT      0x00000008
#define CAN_MOCTR113_RTSEL       0x00000040
#define CAN_MOCTR113_RXEN        0x00000080
#define CAN_MOCTR113_RXPND       0x00000001
#define CAN_MOCTR113_RXUPD       0x00000004
#define CAN_MOCTR113_TXEN0       0x00000200
#define CAN_MOCTR113_TXEN1       0x00000400
#define CAN_MOCTR113_TXPND       0x00000002
#define CAN_MOCTR113_TXRQ        0x00000100

// Message Object 114 Control Register
#define CAN_MOCTR114           (*((uword volatile *) 0xF000545C))
#define CAN_MOCTR114_DIR         0x00000800
#define CAN_MOCTR114_MSGLST      0x00000010
#define CAN_MOCTR114_MSGVAL      0x00000020
#define CAN_MOCTR114_NEWDAT      0x00000008
#define CAN_MOCTR114_RTSEL       0x00000040
#define CAN_MOCTR114_RXEN        0x00000080
#define CAN_MOCTR114_RXPND       0x00000001
#define CAN_MOCTR114_RXUPD       0x00000004
#define CAN_MOCTR114_TXEN0       0x00000200
#define CAN_MOCTR114_TXEN1       0x00000400
#define CAN_MOCTR114_TXPND       0x00000002
#define CAN_MOCTR114_TXRQ        0x00000100

// Message Object 115 Control Register
#define CAN_MOCTR115           (*((uword volatile *) 0xF000547C))
#define CAN_MOCTR115_DIR         0x00000800
#define CAN_MOCTR115_MSGLST      0x00000010
#define CAN_MOCTR115_MSGVAL      0x00000020
#define CAN_MOCTR115_NEWDAT      0x00000008
#define CAN_MOCTR115_RTSEL       0x00000040
#define CAN_MOCTR115_RXEN        0x00000080
#define CAN_MOCTR115_RXPND       0x00000001
#define CAN_MOCTR115_RXUPD       0x00000004
#define CAN_MOCTR115_TXEN0       0x00000200
#define CAN_MOCTR115_TXEN1       0x00000400
#define CAN_MOCTR115_TXPND       0x00000002
#define CAN_MOCTR115_TXRQ        0x00000100

// Message Object 116 Control Register
#define CAN_MOCTR116           (*((uword volatile *) 0xF000549C))
#define CAN_MOCTR116_DIR         0x00000800
#define CAN_MOCTR116_MSGLST      0x00000010
#define CAN_MOCTR116_MSGVAL      0x00000020
#define CAN_MOCTR116_NEWDAT      0x00000008
#define CAN_MOCTR116_RTSEL       0x00000040
#define CAN_MOCTR116_RXEN        0x00000080
#define CAN_MOCTR116_RXPND       0x00000001
#define CAN_MOCTR116_RXUPD       0x00000004
#define CAN_MOCTR116_TXEN0       0x00000200
#define CAN_MOCTR116_TXEN1       0x00000400
#define CAN_MOCTR116_TXPND       0x00000002
#define CAN_MOCTR116_TXRQ        0x00000100

// Message Object 117 Control Register
#define CAN_MOCTR117           (*((uword volatile *) 0xF00054BC))
#define CAN_MOCTR117_DIR         0x00000800
#define CAN_MOCTR117_MSGLST      0x00000010
#define CAN_MOCTR117_MSGVAL      0x00000020
#define CAN_MOCTR117_NEWDAT      0x00000008
#define CAN_MOCTR117_RTSEL       0x00000040
#define CAN_MOCTR117_RXEN        0x00000080
#define CAN_MOCTR117_RXPND       0x00000001
#define CAN_MOCTR117_RXUPD       0x00000004
#define CAN_MOCTR117_TXEN0       0x00000200
#define CAN_MOCTR117_TXEN1       0x00000400
#define CAN_MOCTR117_TXPND       0x00000002
#define CAN_MOCTR117_TXRQ        0x00000100

// Message Object 118 Control Register
#define CAN_MOCTR118           (*((uword volatile *) 0xF00054DC))
#define CAN_MOCTR118_DIR         0x00000800
#define CAN_MOCTR118_MSGLST      0x00000010
#define CAN_MOCTR118_MSGVAL      0x00000020
#define CAN_MOCTR118_NEWDAT      0x00000008
#define CAN_MOCTR118_RTSEL       0x00000040
#define CAN_MOCTR118_RXEN        0x00000080
#define CAN_MOCTR118_RXPND       0x00000001
#define CAN_MOCTR118_RXUPD       0x00000004
#define CAN_MOCTR118_TXEN0       0x00000200
#define CAN_MOCTR118_TXEN1       0x00000400
#define CAN_MOCTR118_TXPND       0x00000002
#define CAN_MOCTR118_TXRQ        0x00000100

// Message Object 119 Control Register
#define CAN_MOCTR119           (*((uword volatile *) 0xF00054FC))
#define CAN_MOCTR119_DIR         0x00000800
#define CAN_MOCTR119_MSGLST      0x00000010
#define CAN_MOCTR119_MSGVAL      0x00000020
#define CAN_MOCTR119_NEWDAT      0x00000008
#define CAN_MOCTR119_RTSEL       0x00000040
#define CAN_MOCTR119_RXEN        0x00000080
#define CAN_MOCTR119_RXPND       0x00000001
#define CAN_MOCTR119_RXUPD       0x00000004
#define CAN_MOCTR119_TXEN0       0x00000200
#define CAN_MOCTR119_TXEN1       0x00000400
#define CAN_MOCTR119_TXPND       0x00000002
#define CAN_MOCTR119_TXRQ        0x00000100

// Message Object 12 Control Register
#define CAN_MOCTR12            (*((uword volatile *) 0xF000479C))
#define CAN_MOCTR12_DIR          0x00000800
#define CAN_MOCTR12_MSGLST       0x00000010
#define CAN_MOCTR12_MSGVAL       0x00000020
#define CAN_MOCTR12_NEWDAT       0x00000008
#define CAN_MOCTR12_RTSEL        0x00000040
#define CAN_MOCTR12_RXEN         0x00000080
#define CAN_MOCTR12_RXPND        0x00000001
#define CAN_MOCTR12_RXUPD        0x00000004
#define CAN_MOCTR12_TXEN0        0x00000200
#define CAN_MOCTR12_TXEN1        0x00000400
#define CAN_MOCTR12_TXPND        0x00000002
#define CAN_MOCTR12_TXRQ         0x00000100

// Message Object 120 Control Register
#define CAN_MOCTR120           (*((uword volatile *) 0xF000551C))
#define CAN_MOCTR120_DIR         0x00000800
#define CAN_MOCTR120_MSGLST      0x00000010
#define CAN_MOCTR120_MSGVAL      0x00000020
#define CAN_MOCTR120_NEWDAT      0x00000008
#define CAN_MOCTR120_RTSEL       0x00000040
#define CAN_MOCTR120_RXEN        0x00000080
#define CAN_MOCTR120_RXPND       0x00000001
#define CAN_MOCTR120_RXUPD       0x00000004
#define CAN_MOCTR120_TXEN0       0x00000200
#define CAN_MOCTR120_TXEN1       0x00000400
#define CAN_MOCTR120_TXPND       0x00000002
#define CAN_MOCTR120_TXRQ        0x00000100

// Message Object 121 Control Register
#define CAN_MOCTR121           (*((uword volatile *) 0xF000553C))
#define CAN_MOCTR121_DIR         0x00000800
#define CAN_MOCTR121_MSGLST      0x00000010
#define CAN_MOCTR121_MSGVAL      0x00000020
#define CAN_MOCTR121_NEWDAT      0x00000008
#define CAN_MOCTR121_RTSEL       0x00000040
#define CAN_MOCTR121_RXEN        0x00000080
#define CAN_MOCTR121_RXPND       0x00000001
#define CAN_MOCTR121_RXUPD       0x00000004
#define CAN_MOCTR121_TXEN0       0x00000200
#define CAN_MOCTR121_TXEN1       0x00000400
#define CAN_MOCTR121_TXPND       0x00000002
#define CAN_MOCTR121_TXRQ        0x00000100

// Message Object 122 Control Register
#define CAN_MOCTR122           (*((uword volatile *) 0xF000555C))
#define CAN_MOCTR122_DIR         0x00000800
#define CAN_MOCTR122_MSGLST      0x00000010
#define CAN_MOCTR122_MSGVAL      0x00000020
#define CAN_MOCTR122_NEWDAT      0x00000008
#define CAN_MOCTR122_RTSEL       0x00000040
#define CAN_MOCTR122_RXEN        0x00000080
#define CAN_MOCTR122_RXPND       0x00000001
#define CAN_MOCTR122_RXUPD       0x00000004
#define CAN_MOCTR122_TXEN0       0x00000200
#define CAN_MOCTR122_TXEN1       0x00000400
#define CAN_MOCTR122_TXPND       0x00000002
#define CAN_MOCTR122_TXRQ        0x00000100

// Message Object 123 Control Register
#define CAN_MOCTR123           (*((uword volatile *) 0xF000557C))
#define CAN_MOCTR123_DIR         0x00000800
#define CAN_MOCTR123_MSGLST      0x00000010
#define CAN_MOCTR123_MSGVAL      0x00000020
#define CAN_MOCTR123_NEWDAT      0x00000008
#define CAN_MOCTR123_RTSEL       0x00000040
#define CAN_MOCTR123_RXEN        0x00000080
#define CAN_MOCTR123_RXPND       0x00000001
#define CAN_MOCTR123_RXUPD       0x00000004
#define CAN_MOCTR123_TXEN0       0x00000200
#define CAN_MOCTR123_TXEN1       0x00000400
#define CAN_MOCTR123_TXPND       0x00000002
#define CAN_MOCTR123_TXRQ        0x00000100

// Message Object 124 Control Register
#define CAN_MOCTR124           (*((uword volatile *) 0xF000559C))
#define CAN_MOCTR124_DIR         0x00000800
#define CAN_MOCTR124_MSGLST      0x00000010
#define CAN_MOCTR124_MSGVAL      0x00000020
#define CAN_MOCTR124_NEWDAT      0x00000008
#define CAN_MOCTR124_RTSEL       0x00000040
#define CAN_MOCTR124_RXEN        0x00000080
#define CAN_MOCTR124_RXPND       0x00000001
#define CAN_MOCTR124_RXUPD       0x00000004
#define CAN_MOCTR124_TXEN0       0x00000200
#define CAN_MOCTR124_TXEN1       0x00000400
#define CAN_MOCTR124_TXPND       0x00000002
#define CAN_MOCTR124_TXRQ        0x00000100

// Message Object 125 Control Register
#define CAN_MOCTR125           (*((uword volatile *) 0xF00055BC))
#define CAN_MOCTR125_DIR         0x00000800
#define CAN_MOCTR125_MSGLST      0x00000010
#define CAN_MOCTR125_MSGVAL      0x00000020
#define CAN_MOCTR125_NEWDAT      0x00000008
#define CAN_MOCTR125_RTSEL       0x00000040
#define CAN_MOCTR125_RXEN        0x00000080
#define CAN_MOCTR125_RXPND       0x00000001
#define CAN_MOCTR125_RXUPD       0x00000004
#define CAN_MOCTR125_TXEN0       0x00000200
#define CAN_MOCTR125_TXEN1       0x00000400
#define CAN_MOCTR125_TXPND       0x00000002
#define CAN_MOCTR125_TXRQ        0x00000100

// Message Object 126 Control Register
#define CAN_MOCTR126           (*((uword volatile *) 0xF00055DC))
#define CAN_MOCTR126_DIR         0x00000800
#define CAN_MOCTR126_MSGLST      0x00000010
#define CAN_MOCTR126_MSGVAL      0x00000020
#define CAN_MOCTR126_NEWDAT      0x00000008
#define CAN_MOCTR126_RTSEL       0x00000040
#define CAN_MOCTR126_RXEN        0x00000080
#define CAN_MOCTR126_RXPND       0x00000001
#define CAN_MOCTR126_RXUPD       0x00000004
#define CAN_MOCTR126_TXEN0       0x00000200
#define CAN_MOCTR126_TXEN1       0x00000400
#define CAN_MOCTR126_TXPND       0x00000002
#define CAN_MOCTR126_TXRQ        0x00000100

// Message Object 127 Control Register
#define CAN_MOCTR127           (*((uword volatile *) 0xF00055FC))
#define CAN_MOCTR127_DIR         0x00000800
#define CAN_MOCTR127_MSGLST      0x00000010
#define CAN_MOCTR127_MSGVAL      0x00000020
#define CAN_MOCTR127_NEWDAT      0x00000008
#define CAN_MOCTR127_RTSEL       0x00000040
#define CAN_MOCTR127_RXEN        0x00000080
#define CAN_MOCTR127_RXPND       0x00000001
#define CAN_MOCTR127_RXUPD       0x00000004
#define CAN_MOCTR127_TXEN0       0x00000200
#define CAN_MOCTR127_TXEN1       0x00000400
#define CAN_MOCTR127_TXPND       0x00000002
#define CAN_MOCTR127_TXRQ        0x00000100

// Message Object 13 Control Register
#define CAN_MOCTR13            (*((uword volatile *) 0xF00047BC))
#define CAN_MOCTR13_DIR          0x00000800
#define CAN_MOCTR13_MSGLST       0x00000010
#define CAN_MOCTR13_MSGVAL       0x00000020
#define CAN_MOCTR13_NEWDAT       0x00000008
#define CAN_MOCTR13_RTSEL        0x00000040
#define CAN_MOCTR13_RXEN         0x00000080
#define CAN_MOCTR13_RXPND        0x00000001
#define CAN_MOCTR13_RXUPD        0x00000004
#define CAN_MOCTR13_TXEN0        0x00000200
#define CAN_MOCTR13_TXEN1        0x00000400
#define CAN_MOCTR13_TXPND        0x00000002
#define CAN_MOCTR13_TXRQ         0x00000100

// Message Object 14 Control Register
#define CAN_MOCTR14            (*((uword volatile *) 0xF00047DC))
#define CAN_MOCTR14_DIR          0x00000800
#define CAN_MOCTR14_MSGLST       0x00000010
#define CAN_MOCTR14_MSGVAL       0x00000020
#define CAN_MOCTR14_NEWDAT       0x00000008
#define CAN_MOCTR14_RTSEL        0x00000040
#define CAN_MOCTR14_RXEN         0x00000080
#define CAN_MOCTR14_RXPND        0x00000001
#define CAN_MOCTR14_RXUPD        0x00000004
#define CAN_MOCTR14_TXEN0        0x00000200
#define CAN_MOCTR14_TXEN1        0x00000400
#define CAN_MOCTR14_TXPND        0x00000002
#define CAN_MOCTR14_TXRQ         0x00000100

// Message Object 15 Control Register
#define CAN_MOCTR15            (*((uword volatile *) 0xF00047FC))
#define CAN_MOCTR15_DIR          0x00000800
#define CAN_MOCTR15_MSGLST       0x00000010
#define CAN_MOCTR15_MSGVAL       0x00000020
#define CAN_MOCTR15_NEWDAT       0x00000008
#define CAN_MOCTR15_RTSEL        0x00000040
#define CAN_MOCTR15_RXEN         0x00000080
#define CAN_MOCTR15_RXPND        0x00000001
#define CAN_MOCTR15_RXUPD        0x00000004
#define CAN_MOCTR15_TXEN0        0x00000200
#define CAN_MOCTR15_TXEN1        0x00000400
#define CAN_MOCTR15_TXPND        0x00000002
#define CAN_MOCTR15_TXRQ         0x00000100

// Message Object 16 Control Register
#define CAN_MOCTR16            (*((uword volatile *) 0xF000481C))
#define CAN_MOCTR16_DIR          0x00000800
#define CAN_MOCTR16_MSGLST       0x00000010
#define CAN_MOCTR16_MSGVAL       0x00000020
#define CAN_MOCTR16_NEWDAT       0x00000008
#define CAN_MOCTR16_RTSEL        0x00000040
#define CAN_MOCTR16_RXEN         0x00000080
#define CAN_MOCTR16_RXPND        0x00000001
#define CAN_MOCTR16_RXUPD        0x00000004
#define CAN_MOCTR16_TXEN0        0x00000200
#define CAN_MOCTR16_TXEN1        0x00000400
#define CAN_MOCTR16_TXPND        0x00000002
#define CAN_MOCTR16_TXRQ         0x00000100

// Message Object 17 Control Register
#define CAN_MOCTR17            (*((uword volatile *) 0xF000483C))
#define CAN_MOCTR17_DIR          0x00000800
#define CAN_MOCTR17_MSGLST       0x00000010
#define CAN_MOCTR17_MSGVAL       0x00000020
#define CAN_MOCTR17_NEWDAT       0x00000008
#define CAN_MOCTR17_RTSEL        0x00000040
#define CAN_MOCTR17_RXEN         0x00000080
#define CAN_MOCTR17_RXPND        0x00000001
#define CAN_MOCTR17_RXUPD        0x00000004
#define CAN_MOCTR17_TXEN0        0x00000200
#define CAN_MOCTR17_TXEN1        0x00000400
#define CAN_MOCTR17_TXPND        0x00000002
#define CAN_MOCTR17_TXRQ         0x00000100

// Message Object 18 Control Register
#define CAN_MOCTR18            (*((uword volatile *) 0xF000485C))
#define CAN_MOCTR18_DIR          0x00000800
#define CAN_MOCTR18_MSGLST       0x00000010
#define CAN_MOCTR18_MSGVAL       0x00000020
#define CAN_MOCTR18_NEWDAT       0x00000008
#define CAN_MOCTR18_RTSEL        0x00000040
#define CAN_MOCTR18_RXEN         0x00000080
#define CAN_MOCTR18_RXPND        0x00000001
#define CAN_MOCTR18_RXUPD        0x00000004
#define CAN_MOCTR18_TXEN0        0x00000200
#define CAN_MOCTR18_TXEN1        0x00000400
#define CAN_MOCTR18_TXPND        0x00000002
#define CAN_MOCTR18_TXRQ         0x00000100

// Message Object 19 Control Register
#define CAN_MOCTR19            (*((uword volatile *) 0xF000487C))
#define CAN_MOCTR19_DIR          0x00000800
#define CAN_MOCTR19_MSGLST       0x00000010
#define CAN_MOCTR19_MSGVAL       0x00000020
#define CAN_MOCTR19_NEWDAT       0x00000008
#define CAN_MOCTR19_RTSEL        0x00000040
#define CAN_MOCTR19_RXEN         0x00000080
#define CAN_MOCTR19_RXPND        0x00000001
#define CAN_MOCTR19_RXUPD        0x00000004
#define CAN_MOCTR19_TXEN0        0x00000200
#define CAN_MOCTR19_TXEN1        0x00000400
#define CAN_MOCTR19_TXPND        0x00000002
#define CAN_MOCTR19_TXRQ         0x00000100

// Message Object 2 Control Register
#define CAN_MOCTR2             (*((uword volatile *) 0xF000465C))
#define CAN_MOCTR2_DIR           0x00000800
#define CAN_MOCTR2_MSGLST        0x00000010
#define CAN_MOCTR2_MSGVAL        0x00000020
#define CAN_MOCTR2_NEWDAT        0x00000008
#define CAN_MOCTR2_RTSEL         0x00000040
#define CAN_MOCTR2_RXEN          0x00000080
#define CAN_MOCTR2_RXPND         0x00000001
#define CAN_MOCTR2_RXUPD         0x00000004
#define CAN_MOCTR2_TXEN0         0x00000200
#define CAN_MOCTR2_TXEN1         0x00000400
#define CAN_MOCTR2_TXPND         0x00000002
#define CAN_MOCTR2_TXRQ          0x00000100

// Message Object 20 Control Register
#define CAN_MOCTR20            (*((uword volatile *) 0xF000489C))
#define CAN_MOCTR20_DIR          0x00000800
#define CAN_MOCTR20_MSGLST       0x00000010
#define CAN_MOCTR20_MSGVAL       0x00000020
#define CAN_MOCTR20_NEWDAT       0x00000008
#define CAN_MOCTR20_RTSEL        0x00000040
#define CAN_MOCTR20_RXEN         0x00000080
#define CAN_MOCTR20_RXPND        0x00000001
#define CAN_MOCTR20_RXUPD        0x00000004
#define CAN_MOCTR20_TXEN0        0x00000200
#define CAN_MOCTR20_TXEN1        0x00000400
#define CAN_MOCTR20_TXPND        0x00000002
#define CAN_MOCTR20_TXRQ         0x00000100

// Message Object 21 Control Register
#define CAN_MOCTR21            (*((uword volatile *) 0xF00048BC))
#define CAN_MOCTR21_DIR          0x00000800
#define CAN_MOCTR21_MSGLST       0x00000010
#define CAN_MOCTR21_MSGVAL       0x00000020
#define CAN_MOCTR21_NEWDAT       0x00000008
#define CAN_MOCTR21_RTSEL        0x00000040
#define CAN_MOCTR21_RXEN         0x00000080
#define CAN_MOCTR21_RXPND        0x00000001
#define CAN_MOCTR21_RXUPD        0x00000004
#define CAN_MOCTR21_TXEN0        0x00000200
#define CAN_MOCTR21_TXEN1        0x00000400
#define CAN_MOCTR21_TXPND        0x00000002
#define CAN_MOCTR21_TXRQ         0x00000100

// Message Object 22 Control Register
#define CAN_MOCTR22            (*((uword volatile *) 0xF00048DC))
#define CAN_MOCTR22_DIR          0x00000800
#define CAN_MOCTR22_MSGLST       0x00000010
#define CAN_MOCTR22_MSGVAL       0x00000020
#define CAN_MOCTR22_NEWDAT       0x00000008
#define CAN_MOCTR22_RTSEL        0x00000040
#define CAN_MOCTR22_RXEN         0x00000080
#define CAN_MOCTR22_RXPND        0x00000001
#define CAN_MOCTR22_RXUPD        0x00000004
#define CAN_MOCTR22_TXEN0        0x00000200
#define CAN_MOCTR22_TXEN1        0x00000400
#define CAN_MOCTR22_TXPND        0x00000002
#define CAN_MOCTR22_TXRQ         0x00000100

// Message Object 23 Control Register
#define CAN_MOCTR23            (*((uword volatile *) 0xF00048FC))
#define CAN_MOCTR23_DIR          0x00000800
#define CAN_MOCTR23_MSGLST       0x00000010
#define CAN_MOCTR23_MSGVAL       0x00000020
#define CAN_MOCTR23_NEWDAT       0x00000008
#define CAN_MOCTR23_RTSEL        0x00000040
#define CAN_MOCTR23_RXEN         0x00000080
#define CAN_MOCTR23_RXPND        0x00000001
#define CAN_MOCTR23_RXUPD        0x00000004
#define CAN_MOCTR23_TXEN0        0x00000200
#define CAN_MOCTR23_TXEN1        0x00000400
#define CAN_MOCTR23_TXPND        0x00000002
#define CAN_MOCTR23_TXRQ         0x00000100

// Message Object 24 Control Register
#define CAN_MOCTR24            (*((uword volatile *) 0xF000491C))
#define CAN_MOCTR24_DIR          0x00000800
#define CAN_MOCTR24_MSGLST       0x00000010
#define CAN_MOCTR24_MSGVAL       0x00000020
#define CAN_MOCTR24_NEWDAT       0x00000008
#define CAN_MOCTR24_RTSEL        0x00000040
#define CAN_MOCTR24_RXEN         0x00000080
#define CAN_MOCTR24_RXPND        0x00000001
#define CAN_MOCTR24_RXUPD        0x00000004
#define CAN_MOCTR24_TXEN0        0x00000200
#define CAN_MOCTR24_TXEN1        0x00000400
#define CAN_MOCTR24_TXPND        0x00000002
#define CAN_MOCTR24_TXRQ         0x00000100

// Message Object 25 Control Register
#define CAN_MOCTR25            (*((uword volatile *) 0xF000493C))
#define CAN_MOCTR25_DIR          0x00000800
#define CAN_MOCTR25_MSGLST       0x00000010
#define CAN_MOCTR25_MSGVAL       0x00000020
#define CAN_MOCTR25_NEWDAT       0x00000008
#define CAN_MOCTR25_RTSEL        0x00000040
#define CAN_MOCTR25_RXEN         0x00000080
#define CAN_MOCTR25_RXPND        0x00000001
#define CAN_MOCTR25_RXUPD        0x00000004
#define CAN_MOCTR25_TXEN0        0x00000200
#define CAN_MOCTR25_TXEN1        0x00000400
#define CAN_MOCTR25_TXPND        0x00000002
#define CAN_MOCTR25_TXRQ         0x00000100

// Message Object 26 Control Register
#define CAN_MOCTR26            (*((uword volatile *) 0xF000495C))
#define CAN_MOCTR26_DIR          0x00000800
#define CAN_MOCTR26_MSGLST       0x00000010
#define CAN_MOCTR26_MSGVAL       0x00000020
#define CAN_MOCTR26_NEWDAT       0x00000008
#define CAN_MOCTR26_RTSEL        0x00000040
#define CAN_MOCTR26_RXEN         0x00000080
#define CAN_MOCTR26_RXPND        0x00000001
#define CAN_MOCTR26_RXUPD        0x00000004
#define CAN_MOCTR26_TXEN0        0x00000200
#define CAN_MOCTR26_TXEN1        0x00000400
#define CAN_MOCTR26_TXPND        0x00000002
#define CAN_MOCTR26_TXRQ         0x00000100

// Message Object 27 Control Register
#define CAN_MOCTR27            (*((uword volatile *) 0xF000497C))
#define CAN_MOCTR27_DIR          0x00000800
#define CAN_MOCTR27_MSGLST       0x00000010
#define CAN_MOCTR27_MSGVAL       0x00000020
#define CAN_MOCTR27_NEWDAT       0x00000008
#define CAN_MOCTR27_RTSEL        0x00000040
#define CAN_MOCTR27_RXEN         0x00000080
#define CAN_MOCTR27_RXPND        0x00000001
#define CAN_MOCTR27_RXUPD        0x00000004
#define CAN_MOCTR27_TXEN0        0x00000200
#define CAN_MOCTR27_TXEN1        0x00000400
#define CAN_MOCTR27_TXPND        0x00000002
#define CAN_MOCTR27_TXRQ         0x00000100

// Message Object 28 Control Register
#define CAN_MOCTR28            (*((uword volatile *) 0xF000499C))
#define CAN_MOCTR28_DIR          0x00000800
#define CAN_MOCTR28_MSGLST       0x00000010
#define CAN_MOCTR28_MSGVAL       0x00000020
#define CAN_MOCTR28_NEWDAT       0x00000008
#define CAN_MOCTR28_RTSEL        0x00000040
#define CAN_MOCTR28_RXEN         0x00000080
#define CAN_MOCTR28_RXPND        0x00000001
#define CAN_MOCTR28_RXUPD        0x00000004
#define CAN_MOCTR28_TXEN0        0x00000200
#define CAN_MOCTR28_TXEN1        0x00000400
#define CAN_MOCTR28_TXPND        0x00000002
#define CAN_MOCTR28_TXRQ         0x00000100

// Message Object 29 Control Register
#define CAN_MOCTR29            (*((uword volatile *) 0xF00049BC))
#define CAN_MOCTR29_DIR          0x00000800
#define CAN_MOCTR29_MSGLST       0x00000010
#define CAN_MOCTR29_MSGVAL       0x00000020
#define CAN_MOCTR29_NEWDAT       0x00000008
#define CAN_MOCTR29_RTSEL        0x00000040
#define CAN_MOCTR29_RXEN         0x00000080
#define CAN_MOCTR29_RXPND        0x00000001
#define CAN_MOCTR29_RXUPD        0x00000004
#define CAN_MOCTR29_TXEN0        0x00000200
#define CAN_MOCTR29_TXEN1        0x00000400
#define CAN_MOCTR29_TXPND        0x00000002
#define CAN_MOCTR29_TXRQ         0x00000100

// Message Object 3 Control Register
#define CAN_MOCTR3             (*((uword volatile *) 0xF000467C))
#define CAN_MOCTR3_DIR           0x00000800
#define CAN_MOCTR3_MSGLST        0x00000010
#define CAN_MOCTR3_MSGVAL        0x00000020
#define CAN_MOCTR3_NEWDAT        0x00000008
#define CAN_MOCTR3_RTSEL         0x00000040
#define CAN_MOCTR3_RXEN          0x00000080
#define CAN_MOCTR3_RXPND         0x00000001
#define CAN_MOCTR3_RXUPD         0x00000004
#define CAN_MOCTR3_TXEN0         0x00000200
#define CAN_MOCTR3_TXEN1         0x00000400
#define CAN_MOCTR3_TXPND         0x00000002
#define CAN_MOCTR3_TXRQ          0x00000100

// Message Object 30 Control Register
#define CAN_MOCTR30            (*((uword volatile *) 0xF00049DC))
#define CAN_MOCTR30_DIR          0x00000800
#define CAN_MOCTR30_MSGLST       0x00000010
#define CAN_MOCTR30_MSGVAL       0x00000020
#define CAN_MOCTR30_NEWDAT       0x00000008
#define CAN_MOCTR30_RTSEL        0x00000040
#define CAN_MOCTR30_RXEN         0x00000080
#define CAN_MOCTR30_RXPND        0x00000001
#define CAN_MOCTR30_RXUPD        0x00000004
#define CAN_MOCTR30_TXEN0        0x00000200
#define CAN_MOCTR30_TXEN1        0x00000400
#define CAN_MOCTR30_TXPND        0x00000002
#define CAN_MOCTR30_TXRQ         0x00000100

// Message Object 31 Control Register
#define CAN_MOCTR31            (*((uword volatile *) 0xF00049FC))
#define CAN_MOCTR31_DIR          0x00000800
#define CAN_MOCTR31_MSGLST       0x00000010
#define CAN_MOCTR31_MSGVAL       0x00000020
#define CAN_MOCTR31_NEWDAT       0x00000008
#define CAN_MOCTR31_RTSEL        0x00000040
#define CAN_MOCTR31_RXEN         0x00000080
#define CAN_MOCTR31_RXPND        0x00000001
#define CAN_MOCTR31_RXUPD        0x00000004
#define CAN_MOCTR31_TXEN0        0x00000200
#define CAN_MOCTR31_TXEN1        0x00000400
#define CAN_MOCTR31_TXPND        0x00000002
#define CAN_MOCTR31_TXRQ         0x00000100

// Message Object 32 Control Register
#define CAN_MOCTR32            (*((uword volatile *) 0xF0004A1C))
#define CAN_MOCTR32_DIR          0x00000800
#define CAN_MOCTR32_MSGLST       0x00000010
#define CAN_MOCTR32_MSGVAL       0x00000020
#define CAN_MOCTR32_NEWDAT       0x00000008
#define CAN_MOCTR32_RTSEL        0x00000040
#define CAN_MOCTR32_RXEN         0x00000080
#define CAN_MOCTR32_RXPND        0x00000001
#define CAN_MOCTR32_RXUPD        0x00000004
#define CAN_MOCTR32_TXEN0        0x00000200
#define CAN_MOCTR32_TXEN1        0x00000400
#define CAN_MOCTR32_TXPND        0x00000002
#define CAN_MOCTR32_TXRQ         0x00000100

// Message Object 33 Control Register
#define CAN_MOCTR33            (*((uword volatile *) 0xF0004A3C))
#define CAN_MOCTR33_DIR          0x00000800
#define CAN_MOCTR33_MSGLST       0x00000010
#define CAN_MOCTR33_MSGVAL       0x00000020
#define CAN_MOCTR33_NEWDAT       0x00000008
#define CAN_MOCTR33_RTSEL        0x00000040
#define CAN_MOCTR33_RXEN         0x00000080
#define CAN_MOCTR33_RXPND        0x00000001
#define CAN_MOCTR33_RXUPD        0x00000004
#define CAN_MOCTR33_TXEN0        0x00000200
#define CAN_MOCTR33_TXEN1        0x00000400
#define CAN_MOCTR33_TXPND        0x00000002
#define CAN_MOCTR33_TXRQ         0x00000100

// Message Object 34 Control Register
#define CAN_MOCTR34            (*((uword volatile *) 0xF0004A5C))
#define CAN_MOCTR34_DIR          0x00000800
#define CAN_MOCTR34_MSGLST       0x00000010
#define CAN_MOCTR34_MSGVAL       0x00000020
#define CAN_MOCTR34_NEWDAT       0x00000008
#define CAN_MOCTR34_RTSEL        0x00000040
#define CAN_MOCTR34_RXEN         0x00000080
#define CAN_MOCTR34_RXPND        0x00000001
#define CAN_MOCTR34_RXUPD        0x00000004
#define CAN_MOCTR34_TXEN0        0x00000200
#define CAN_MOCTR34_TXEN1        0x00000400
#define CAN_MOCTR34_TXPND        0x00000002
#define CAN_MOCTR34_TXRQ         0x00000100

// Message Object 35 Control Register
#define CAN_MOCTR35            (*((uword volatile *) 0xF0004A7C))
#define CAN_MOCTR35_DIR          0x00000800
#define CAN_MOCTR35_MSGLST       0x00000010
#define CAN_MOCTR35_MSGVAL       0x00000020
#define CAN_MOCTR35_NEWDAT       0x00000008
#define CAN_MOCTR35_RTSEL        0x00000040
#define CAN_MOCTR35_RXEN         0x00000080
#define CAN_MOCTR35_RXPND        0x00000001
#define CAN_MOCTR35_RXUPD        0x00000004
#define CAN_MOCTR35_TXEN0        0x00000200
#define CAN_MOCTR35_TXEN1        0x00000400
#define CAN_MOCTR35_TXPND        0x00000002
#define CAN_MOCTR35_TXRQ         0x00000100

// Message Object 36 Control Register
#define CAN_MOCTR36            (*((uword volatile *) 0xF0004A9C))
#define CAN_MOCTR36_DIR          0x00000800
#define CAN_MOCTR36_MSGLST       0x00000010
#define CAN_MOCTR36_MSGVAL       0x00000020
#define CAN_MOCTR36_NEWDAT       0x00000008
#define CAN_MOCTR36_RTSEL        0x00000040
#define CAN_MOCTR36_RXEN         0x00000080
#define CAN_MOCTR36_RXPND        0x00000001
#define CAN_MOCTR36_RXUPD        0x00000004
#define CAN_MOCTR36_TXEN0        0x00000200
#define CAN_MOCTR36_TXEN1        0x00000400
#define CAN_MOCTR36_TXPND        0x00000002
#define CAN_MOCTR36_TXRQ         0x00000100

// Message Object 37 Control Register
#define CAN_MOCTR37            (*((uword volatile *) 0xF0004ABC))
#define CAN_MOCTR37_DIR          0x00000800
#define CAN_MOCTR37_MSGLST       0x00000010
#define CAN_MOCTR37_MSGVAL       0x00000020
#define CAN_MOCTR37_NEWDAT       0x00000008
#define CAN_MOCTR37_RTSEL        0x00000040
#define CAN_MOCTR37_RXEN         0x00000080
#define CAN_MOCTR37_RXPND        0x00000001
#define CAN_MOCTR37_RXUPD        0x00000004
#define CAN_MOCTR37_TXEN0        0x00000200
#define CAN_MOCTR37_TXEN1        0x00000400
#define CAN_MOCTR37_TXPND        0x00000002
#define CAN_MOCTR37_TXRQ         0x00000100

// Message Object 38 Control Register
#define CAN_MOCTR38            (*((uword volatile *) 0xF0004ADC))
#define CAN_MOCTR38_DIR          0x00000800
#define CAN_MOCTR38_MSGLST       0x00000010
#define CAN_MOCTR38_MSGVAL       0x00000020
#define CAN_MOCTR38_NEWDAT       0x00000008
#define CAN_MOCTR38_RTSEL        0x00000040
#define CAN_MOCTR38_RXEN         0x00000080
#define CAN_MOCTR38_RXPND        0x00000001
#define CAN_MOCTR38_RXUPD        0x00000004
#define CAN_MOCTR38_TXEN0        0x00000200
#define CAN_MOCTR38_TXEN1        0x00000400
#define CAN_MOCTR38_TXPND        0x00000002
#define CAN_MOCTR38_TXRQ         0x00000100

// Message Object 39 Control Register
#define CAN_MOCTR39            (*((uword volatile *) 0xF0004AFC))
#define CAN_MOCTR39_DIR          0x00000800
#define CAN_MOCTR39_MSGLST       0x00000010
#define CAN_MOCTR39_MSGVAL       0x00000020
#define CAN_MOCTR39_NEWDAT       0x00000008
#define CAN_MOCTR39_RTSEL        0x00000040
#define CAN_MOCTR39_RXEN         0x00000080
#define CAN_MOCTR39_RXPND        0x00000001
#define CAN_MOCTR39_RXUPD        0x00000004
#define CAN_MOCTR39_TXEN0        0x00000200
#define CAN_MOCTR39_TXEN1        0x00000400
#define CAN_MOCTR39_TXPND        0x00000002
#define CAN_MOCTR39_TXRQ         0x00000100

// Message Object 4 Control Register
#define CAN_MOCTR4             (*((uword volatile *) 0xF000469C))
#define CAN_MOCTR4_DIR           0x00000800
#define CAN_MOCTR4_MSGLST        0x00000010
#define CAN_MOCTR4_MSGVAL        0x00000020
#define CAN_MOCTR4_NEWDAT        0x00000008
#define CAN_MOCTR4_RTSEL         0x00000040
#define CAN_MOCTR4_RXEN          0x00000080
#define CAN_MOCTR4_RXPND         0x00000001
#define CAN_MOCTR4_RXUPD         0x00000004
#define CAN_MOCTR4_TXEN0         0x00000200
#define CAN_MOCTR4_TXEN1         0x00000400
#define CAN_MOCTR4_TXPND         0x00000002
#define CAN_MOCTR4_TXRQ          0x00000100

// Message Object 40 Control Register
#define CAN_MOCTR40            (*((uword volatile *) 0xF0004B1C))
#define CAN_MOCTR40_DIR          0x00000800
#define CAN_MOCTR40_MSGLST       0x00000010
#define CAN_MOCTR40_MSGVAL       0x00000020
#define CAN_MOCTR40_NEWDAT       0x00000008
#define CAN_MOCTR40_RTSEL        0x00000040
#define CAN_MOCTR40_RXEN         0x00000080
#define CAN_MOCTR40_RXPND        0x00000001
#define CAN_MOCTR40_RXUPD        0x00000004
#define CAN_MOCTR40_TXEN0        0x00000200
#define CAN_MOCTR40_TXEN1        0x00000400
#define CAN_MOCTR40_TXPND        0x00000002
#define CAN_MOCTR40_TXRQ         0x00000100

// Message Object 41 Control Register
#define CAN_MOCTR41            (*((uword volatile *) 0xF0004B3C))
#define CAN_MOCTR41_DIR          0x00000800
#define CAN_MOCTR41_MSGLST       0x00000010
#define CAN_MOCTR41_MSGVAL       0x00000020
#define CAN_MOCTR41_NEWDAT       0x00000008
#define CAN_MOCTR41_RTSEL        0x00000040
#define CAN_MOCTR41_RXEN         0x00000080
#define CAN_MOCTR41_RXPND        0x00000001
#define CAN_MOCTR41_RXUPD        0x00000004
#define CAN_MOCTR41_TXEN0        0x00000200
#define CAN_MOCTR41_TXEN1        0x00000400
#define CAN_MOCTR41_TXPND        0x00000002
#define CAN_MOCTR41_TXRQ         0x00000100

// Message Object 42 Control Register
#define CAN_MOCTR42            (*((uword volatile *) 0xF0004B5C))
#define CAN_MOCTR42_DIR          0x00000800
#define CAN_MOCTR42_MSGLST       0x00000010
#define CAN_MOCTR42_MSGVAL       0x00000020
#define CAN_MOCTR42_NEWDAT       0x00000008
#define CAN_MOCTR42_RTSEL        0x00000040
#define CAN_MOCTR42_RXEN         0x00000080
#define CAN_MOCTR42_RXPND        0x00000001
#define CAN_MOCTR42_RXUPD        0x00000004
#define CAN_MOCTR42_TXEN0        0x00000200
#define CAN_MOCTR42_TXEN1        0x00000400
#define CAN_MOCTR42_TXPND        0x00000002
#define CAN_MOCTR42_TXRQ         0x00000100

// Message Object 43 Control Register
#define CAN_MOCTR43            (*((uword volatile *) 0xF0004B7C))
#define CAN_MOCTR43_DIR          0x00000800
#define CAN_MOCTR43_MSGLST       0x00000010
#define CAN_MOCTR43_MSGVAL       0x00000020
#define CAN_MOCTR43_NEWDAT       0x00000008
#define CAN_MOCTR43_RTSEL        0x00000040
#define CAN_MOCTR43_RXEN         0x00000080
#define CAN_MOCTR43_RXPND        0x00000001
#define CAN_MOCTR43_RXUPD        0x00000004
#define CAN_MOCTR43_TXEN0        0x00000200
#define CAN_MOCTR43_TXEN1        0x00000400
#define CAN_MOCTR43_TXPND        0x00000002
#define CAN_MOCTR43_TXRQ         0x00000100

// Message Object 44 Control Register
#define CAN_MOCTR44            (*((uword volatile *) 0xF0004B9C))
#define CAN_MOCTR44_DIR          0x00000800
#define CAN_MOCTR44_MSGLST       0x00000010
#define CAN_MOCTR44_MSGVAL       0x00000020
#define CAN_MOCTR44_NEWDAT       0x00000008
#define CAN_MOCTR44_RTSEL        0x00000040
#define CAN_MOCTR44_RXEN         0x00000080
#define CAN_MOCTR44_RXPND        0x00000001
#define CAN_MOCTR44_RXUPD        0x00000004
#define CAN_MOCTR44_TXEN0        0x00000200
#define CAN_MOCTR44_TXEN1        0x00000400
#define CAN_MOCTR44_TXPND        0x00000002
#define CAN_MOCTR44_TXRQ         0x00000100

// Message Object 45 Control Register
#define CAN_MOCTR45            (*((uword volatile *) 0xF0004BBC))
#define CAN_MOCTR45_DIR          0x00000800
#define CAN_MOCTR45_MSGLST       0x00000010
#define CAN_MOCTR45_MSGVAL       0x00000020
#define CAN_MOCTR45_NEWDAT       0x00000008
#define CAN_MOCTR45_RTSEL        0x00000040
#define CAN_MOCTR45_RXEN         0x00000080
#define CAN_MOCTR45_RXPND        0x00000001
#define CAN_MOCTR45_RXUPD        0x00000004
#define CAN_MOCTR45_TXEN0        0x00000200
#define CAN_MOCTR45_TXEN1        0x00000400
#define CAN_MOCTR45_TXPND        0x00000002
#define CAN_MOCTR45_TXRQ         0x00000100

// Message Object 46 Control Register
#define CAN_MOCTR46            (*((uword volatile *) 0xF0004BDC))
#define CAN_MOCTR46_DIR          0x00000800
#define CAN_MOCTR46_MSGLST       0x00000010
#define CAN_MOCTR46_MSGVAL       0x00000020
#define CAN_MOCTR46_NEWDAT       0x00000008
#define CAN_MOCTR46_RTSEL        0x00000040
#define CAN_MOCTR46_RXEN         0x00000080
#define CAN_MOCTR46_RXPND        0x00000001
#define CAN_MOCTR46_RXUPD        0x00000004
#define CAN_MOCTR46_TXEN0        0x00000200
#define CAN_MOCTR46_TXEN1        0x00000400
#define CAN_MOCTR46_TXPND        0x00000002
#define CAN_MOCTR46_TXRQ         0x00000100

// Message Object 47 Control Register
#define CAN_MOCTR47            (*((uword volatile *) 0xF0004BFC))
#define CAN_MOCTR47_DIR          0x00000800
#define CAN_MOCTR47_MSGLST       0x00000010
#define CAN_MOCTR47_MSGVAL       0x00000020
#define CAN_MOCTR47_NEWDAT       0x00000008
#define CAN_MOCTR47_RTSEL        0x00000040
#define CAN_MOCTR47_RXEN         0x00000080
#define CAN_MOCTR47_RXPND        0x00000001
#define CAN_MOCTR47_RXUPD        0x00000004
#define CAN_MOCTR47_TXEN0        0x00000200
#define CAN_MOCTR47_TXEN1        0x00000400
#define CAN_MOCTR47_TXPND        0x00000002
#define CAN_MOCTR47_TXRQ         0x00000100

// Message Object 48 Control Register
#define CAN_MOCTR48            (*((uword volatile *) 0xF0004C1C))
#define CAN_MOCTR48_DIR          0x00000800
#define CAN_MOCTR48_MSGLST       0x00000010
#define CAN_MOCTR48_MSGVAL       0x00000020
#define CAN_MOCTR48_NEWDAT       0x00000008
#define CAN_MOCTR48_RTSEL        0x00000040
#define CAN_MOCTR48_RXEN         0x00000080
#define CAN_MOCTR48_RXPND        0x00000001
#define CAN_MOCTR48_RXUPD        0x00000004
#define CAN_MOCTR48_TXEN0        0x00000200
#define CAN_MOCTR48_TXEN1        0x00000400
#define CAN_MOCTR48_TXPND        0x00000002
#define CAN_MOCTR48_TXRQ         0x00000100

// Message Object 49 Control Register
#define CAN_MOCTR49            (*((uword volatile *) 0xF0004C3C))
#define CAN_MOCTR49_DIR          0x00000800
#define CAN_MOCTR49_MSGLST       0x00000010
#define CAN_MOCTR49_MSGVAL       0x00000020
#define CAN_MOCTR49_NEWDAT       0x00000008
#define CAN_MOCTR49_RTSEL        0x00000040
#define CAN_MOCTR49_RXEN         0x00000080
#define CAN_MOCTR49_RXPND        0x00000001
#define CAN_MOCTR49_RXUPD        0x00000004
#define CAN_MOCTR49_TXEN0        0x00000200
#define CAN_MOCTR49_TXEN1        0x00000400
#define CAN_MOCTR49_TXPND        0x00000002
#define CAN_MOCTR49_TXRQ         0x00000100

// Message Object 5 Control Register
#define CAN_MOCTR5             (*((uword volatile *) 0xF00046BC))
#define CAN_MOCTR5_DIR           0x00000800
#define CAN_MOCTR5_MSGLST        0x00000010
#define CAN_MOCTR5_MSGVAL        0x00000020
#define CAN_MOCTR5_NEWDAT        0x00000008
#define CAN_MOCTR5_RTSEL         0x00000040
#define CAN_MOCTR5_RXEN          0x00000080
#define CAN_MOCTR5_RXPND         0x00000001
#define CAN_MOCTR5_RXUPD         0x00000004
#define CAN_MOCTR5_TXEN0         0x00000200
#define CAN_MOCTR5_TXEN1         0x00000400
#define CAN_MOCTR5_TXPND         0x00000002
#define CAN_MOCTR5_TXRQ          0x00000100

// Message Object 50 Control Register
#define CAN_MOCTR50            (*((uword volatile *) 0xF0004C5C))
#define CAN_MOCTR50_DIR          0x00000800
#define CAN_MOCTR50_MSGLST       0x00000010
#define CAN_MOCTR50_MSGVAL       0x00000020
#define CAN_MOCTR50_NEWDAT       0x00000008
#define CAN_MOCTR50_RTSEL        0x00000040
#define CAN_MOCTR50_RXEN         0x00000080
#define CAN_MOCTR50_RXPND        0x00000001
#define CAN_MOCTR50_RXUPD        0x00000004
#define CAN_MOCTR50_TXEN0        0x00000200
#define CAN_MOCTR50_TXEN1        0x00000400
#define CAN_MOCTR50_TXPND        0x00000002
#define CAN_MOCTR50_TXRQ         0x00000100

// Message Object 51 Control Register
#define CAN_MOCTR51            (*((uword volatile *) 0xF0004C7C))
#define CAN_MOCTR51_DIR          0x00000800
#define CAN_MOCTR51_MSGLST       0x00000010
#define CAN_MOCTR51_MSGVAL       0x00000020
#define CAN_MOCTR51_NEWDAT       0x00000008
#define CAN_MOCTR51_RTSEL        0x00000040
#define CAN_MOCTR51_RXEN         0x00000080
#define CAN_MOCTR51_RXPND        0x00000001
#define CAN_MOCTR51_RXUPD        0x00000004
#define CAN_MOCTR51_TXEN0        0x00000200
#define CAN_MOCTR51_TXEN1        0x00000400
#define CAN_MOCTR51_TXPND        0x00000002
#define CAN_MOCTR51_TXRQ         0x00000100

// Message Object 52 Control Register
#define CAN_MOCTR52            (*((uword volatile *) 0xF0004C9C))
#define CAN_MOCTR52_DIR          0x00000800
#define CAN_MOCTR52_MSGLST       0x00000010
#define CAN_MOCTR52_MSGVAL       0x00000020
#define CAN_MOCTR52_NEWDAT       0x00000008
#define CAN_MOCTR52_RTSEL        0x00000040
#define CAN_MOCTR52_RXEN         0x00000080
#define CAN_MOCTR52_RXPND        0x00000001
#define CAN_MOCTR52_RXUPD        0x00000004
#define CAN_MOCTR52_TXEN0        0x00000200
#define CAN_MOCTR52_TXEN1        0x00000400
#define CAN_MOCTR52_TXPND        0x00000002
#define CAN_MOCTR52_TXRQ         0x00000100

// Message Object 53 Control Register
#define CAN_MOCTR53            (*((uword volatile *) 0xF0004CBC))
#define CAN_MOCTR53_DIR          0x00000800
#define CAN_MOCTR53_MSGLST       0x00000010
#define CAN_MOCTR53_MSGVAL       0x00000020
#define CAN_MOCTR53_NEWDAT       0x00000008
#define CAN_MOCTR53_RTSEL        0x00000040
#define CAN_MOCTR53_RXEN         0x00000080
#define CAN_MOCTR53_RXPND        0x00000001
#define CAN_MOCTR53_RXUPD        0x00000004
#define CAN_MOCTR53_TXEN0        0x00000200
#define CAN_MOCTR53_TXEN1        0x00000400
#define CAN_MOCTR53_TXPND        0x00000002
#define CAN_MOCTR53_TXRQ         0x00000100

// Message Object 54 Control Register
#define CAN_MOCTR54            (*((uword volatile *) 0xF0004CDC))
#define CAN_MOCTR54_DIR          0x00000800
#define CAN_MOCTR54_MSGLST       0x00000010
#define CAN_MOCTR54_MSGVAL       0x00000020
#define CAN_MOCTR54_NEWDAT       0x00000008
#define CAN_MOCTR54_RTSEL        0x00000040
#define CAN_MOCTR54_RXEN         0x00000080
#define CAN_MOCTR54_RXPND        0x00000001
#define CAN_MOCTR54_RXUPD        0x00000004
#define CAN_MOCTR54_TXEN0        0x00000200
#define CAN_MOCTR54_TXEN1        0x00000400
#define CAN_MOCTR54_TXPND        0x00000002
#define CAN_MOCTR54_TXRQ         0x00000100

// Message Object 55 Control Register
#define CAN_MOCTR55            (*((uword volatile *) 0xF0004CFC))
#define CAN_MOCTR55_DIR          0x00000800
#define CAN_MOCTR55_MSGLST       0x00000010
#define CAN_MOCTR55_MSGVAL       0x00000020
#define CAN_MOCTR55_NEWDAT       0x00000008
#define CAN_MOCTR55_RTSEL        0x00000040
#define CAN_MOCTR55_RXEN         0x00000080
#define CAN_MOCTR55_RXPND        0x00000001
#define CAN_MOCTR55_RXUPD        0x00000004
#define CAN_MOCTR55_TXEN0        0x00000200
#define CAN_MOCTR55_TXEN1        0x00000400
#define CAN_MOCTR55_TXPND        0x00000002
#define CAN_MOCTR55_TXRQ         0x00000100

// Message Object 56 Control Register
#define CAN_MOCTR56            (*((uword volatile *) 0xF0004D1C))
#define CAN_MOCTR56_DIR          0x00000800
#define CAN_MOCTR56_MSGLST       0x00000010
#define CAN_MOCTR56_MSGVAL       0x00000020
#define CAN_MOCTR56_NEWDAT       0x00000008
#define CAN_MOCTR56_RTSEL        0x00000040
#define CAN_MOCTR56_RXEN         0x00000080
#define CAN_MOCTR56_RXPND        0x00000001
#define CAN_MOCTR56_RXUPD        0x00000004
#define CAN_MOCTR56_TXEN0        0x00000200
#define CAN_MOCTR56_TXEN1        0x00000400
#define CAN_MOCTR56_TXPND        0x00000002
#define CAN_MOCTR56_TXRQ         0x00000100

// Message Object 57 Control Register
#define CAN_MOCTR57            (*((uword volatile *) 0xF0004D3C))
#define CAN_MOCTR57_DIR          0x00000800
#define CAN_MOCTR57_MSGLST       0x00000010
#define CAN_MOCTR57_MSGVAL       0x00000020
#define CAN_MOCTR57_NEWDAT       0x00000008
#define CAN_MOCTR57_RTSEL        0x00000040
#define CAN_MOCTR57_RXEN         0x00000080
#define CAN_MOCTR57_RXPND        0x00000001
#define CAN_MOCTR57_RXUPD        0x00000004
#define CAN_MOCTR57_TXEN0        0x00000200
#define CAN_MOCTR57_TXEN1        0x00000400
#define CAN_MOCTR57_TXPND        0x00000002
#define CAN_MOCTR57_TXRQ         0x00000100

// Message Object 58 Control Register
#define CAN_MOCTR58            (*((uword volatile *) 0xF0004D5C))
#define CAN_MOCTR58_DIR          0x00000800
#define CAN_MOCTR58_MSGLST       0x00000010
#define CAN_MOCTR58_MSGVAL       0x00000020
#define CAN_MOCTR58_NEWDAT       0x00000008
#define CAN_MOCTR58_RTSEL        0x00000040
#define CAN_MOCTR58_RXEN         0x00000080
#define CAN_MOCTR58_RXPND        0x00000001
#define CAN_MOCTR58_RXUPD        0x00000004
#define CAN_MOCTR58_TXEN0        0x00000200
#define CAN_MOCTR58_TXEN1        0x00000400
#define CAN_MOCTR58_TXPND        0x00000002
#define CAN_MOCTR58_TXRQ         0x00000100

// Message Object 59 Control Register
#define CAN_MOCTR59            (*((uword volatile *) 0xF0004D7C))
#define CAN_MOCTR59_DIR          0x00000800
#define CAN_MOCTR59_MSGLST       0x00000010
#define CAN_MOCTR59_MSGVAL       0x00000020
#define CAN_MOCTR59_NEWDAT       0x00000008
#define CAN_MOCTR59_RTSEL        0x00000040
#define CAN_MOCTR59_RXEN         0x00000080
#define CAN_MOCTR59_RXPND        0x00000001
#define CAN_MOCTR59_RXUPD        0x00000004
#define CAN_MOCTR59_TXEN0        0x00000200
#define CAN_MOCTR59_TXEN1        0x00000400
#define CAN_MOCTR59_TXPND        0x00000002
#define CAN_MOCTR59_TXRQ         0x00000100

// Message Object 6 Control Register
#define CAN_MOCTR6             (*((uword volatile *) 0xF00046DC))
#define CAN_MOCTR6_DIR           0x00000800
#define CAN_MOCTR6_MSGLST        0x00000010
#define CAN_MOCTR6_MSGVAL        0x00000020
#define CAN_MOCTR6_NEWDAT        0x00000008
#define CAN_MOCTR6_RTSEL         0x00000040
#define CAN_MOCTR6_RXEN          0x00000080
#define CAN_MOCTR6_RXPND         0x00000001
#define CAN_MOCTR6_RXUPD         0x00000004
#define CAN_MOCTR6_TXEN0         0x00000200
#define CAN_MOCTR6_TXEN1         0x00000400
#define CAN_MOCTR6_TXPND         0x00000002
#define CAN_MOCTR6_TXRQ          0x00000100

// Message Object 60 Control Register
#define CAN_MOCTR60            (*((uword volatile *) 0xF0004D9C))
#define CAN_MOCTR60_DIR          0x00000800
#define CAN_MOCTR60_MSGLST       0x00000010
#define CAN_MOCTR60_MSGVAL       0x00000020
#define CAN_MOCTR60_NEWDAT       0x00000008
#define CAN_MOCTR60_RTSEL        0x00000040
#define CAN_MOCTR60_RXEN         0x00000080
#define CAN_MOCTR60_RXPND        0x00000001
#define CAN_MOCTR60_RXUPD        0x00000004
#define CAN_MOCTR60_TXEN0        0x00000200
#define CAN_MOCTR60_TXEN1        0x00000400
#define CAN_MOCTR60_TXPND        0x00000002
#define CAN_MOCTR60_TXRQ         0x00000100

// Message Object 61 Control Register
#define CAN_MOCTR61            (*((uword volatile *) 0xF0004DBC))
#define CAN_MOCTR61_DIR          0x00000800
#define CAN_MOCTR61_MSGLST       0x00000010
#define CAN_MOCTR61_MSGVAL       0x00000020
#define CAN_MOCTR61_NEWDAT       0x00000008
#define CAN_MOCTR61_RTSEL        0x00000040
#define CAN_MOCTR61_RXEN         0x00000080
#define CAN_MOCTR61_RXPND        0x00000001
#define CAN_MOCTR61_RXUPD        0x00000004
#define CAN_MOCTR61_TXEN0        0x00000200
#define CAN_MOCTR61_TXEN1        0x00000400
#define CAN_MOCTR61_TXPND        0x00000002
#define CAN_MOCTR61_TXRQ         0x00000100

// Message Object 62 Control Register
#define CAN_MOCTR62            (*((uword volatile *) 0xF0004DDC))
#define CAN_MOCTR62_DIR          0x00000800
#define CAN_MOCTR62_MSGLST       0x00000010
#define CAN_MOCTR62_MSGVAL       0x00000020
#define CAN_MOCTR62_NEWDAT       0x00000008
#define CAN_MOCTR62_RTSEL        0x00000040
#define CAN_MOCTR62_RXEN         0x00000080
#define CAN_MOCTR62_RXPND        0x00000001
#define CAN_MOCTR62_RXUPD        0x00000004
#define CAN_MOCTR62_TXEN0        0x00000200
#define CAN_MOCTR62_TXEN1        0x00000400
#define CAN_MOCTR62_TXPND        0x00000002
#define CAN_MOCTR62_TXRQ         0x00000100

// Message Object 63 Control Register
#define CAN_MOCTR63            (*((uword volatile *) 0xF0004DFC))
#define CAN_MOCTR63_DIR          0x00000800
#define CAN_MOCTR63_MSGLST       0x00000010
#define CAN_MOCTR63_MSGVAL       0x00000020
#define CAN_MOCTR63_NEWDAT       0x00000008
#define CAN_MOCTR63_RTSEL        0x00000040
#define CAN_MOCTR63_RXEN         0x00000080
#define CAN_MOCTR63_RXPND        0x00000001
#define CAN_MOCTR63_RXUPD        0x00000004
#define CAN_MOCTR63_TXEN0        0x00000200
#define CAN_MOCTR63_TXEN1        0x00000400
#define CAN_MOCTR63_TXPND        0x00000002
#define CAN_MOCTR63_TXRQ         0x00000100

// Message Object 64 Control Register
#define CAN_MOCTR64            (*((uword volatile *) 0xF0004E1C))
#define CAN_MOCTR64_DIR          0x00000800
#define CAN_MOCTR64_MSGLST       0x00000010
#define CAN_MOCTR64_MSGVAL       0x00000020
#define CAN_MOCTR64_NEWDAT       0x00000008
#define CAN_MOCTR64_RTSEL        0x00000040
#define CAN_MOCTR64_RXEN         0x00000080
#define CAN_MOCTR64_RXPND        0x00000001
#define CAN_MOCTR64_RXUPD        0x00000004
#define CAN_MOCTR64_TXEN0        0x00000200
#define CAN_MOCTR64_TXEN1        0x00000400
#define CAN_MOCTR64_TXPND        0x00000002
#define CAN_MOCTR64_TXRQ         0x00000100

// Message Object 65 Control Register
#define CAN_MOCTR65            (*((uword volatile *) 0xF0004E3C))
#define CAN_MOCTR65_DIR          0x00000800
#define CAN_MOCTR65_MSGLST       0x00000010
#define CAN_MOCTR65_MSGVAL       0x00000020
#define CAN_MOCTR65_NEWDAT       0x00000008
#define CAN_MOCTR65_RTSEL        0x00000040
#define CAN_MOCTR65_RXEN         0x00000080
#define CAN_MOCTR65_RXPND        0x00000001
#define CAN_MOCTR65_RXUPD        0x00000004
#define CAN_MOCTR65_TXEN0        0x00000200
#define CAN_MOCTR65_TXEN1        0x00000400
#define CAN_MOCTR65_TXPND        0x00000002
#define CAN_MOCTR65_TXRQ         0x00000100

// Message Object 66 Control Register
#define CAN_MOCTR66            (*((uword volatile *) 0xF0004E5C))
#define CAN_MOCTR66_DIR          0x00000800
#define CAN_MOCTR66_MSGLST       0x00000010
#define CAN_MOCTR66_MSGVAL       0x00000020
#define CAN_MOCTR66_NEWDAT       0x00000008
#define CAN_MOCTR66_RTSEL        0x00000040
#define CAN_MOCTR66_RXEN         0x00000080
#define CAN_MOCTR66_RXPND        0x00000001
#define CAN_MOCTR66_RXUPD        0x00000004
#define CAN_MOCTR66_TXEN0        0x00000200
#define CAN_MOCTR66_TXEN1        0x00000400
#define CAN_MOCTR66_TXPND        0x00000002
#define CAN_MOCTR66_TXRQ         0x00000100

// Message Object 67 Control Register
#define CAN_MOCTR67            (*((uword volatile *) 0xF0004E7C))
#define CAN_MOCTR67_DIR          0x00000800
#define CAN_MOCTR67_MSGLST       0x00000010
#define CAN_MOCTR67_MSGVAL       0x00000020
#define CAN_MOCTR67_NEWDAT       0x00000008
#define CAN_MOCTR67_RTSEL        0x00000040
#define CAN_MOCTR67_RXEN         0x00000080
#define CAN_MOCTR67_RXPND        0x00000001
#define CAN_MOCTR67_RXUPD        0x00000004
#define CAN_MOCTR67_TXEN0        0x00000200
#define CAN_MOCTR67_TXEN1        0x00000400
#define CAN_MOCTR67_TXPND        0x00000002
#define CAN_MOCTR67_TXRQ         0x00000100

// Message Object 68 Control Register
#define CAN_MOCTR68            (*((uword volatile *) 0xF0004E9C))
#define CAN_MOCTR68_DIR          0x00000800
#define CAN_MOCTR68_MSGLST       0x00000010
#define CAN_MOCTR68_MSGVAL       0x00000020
#define CAN_MOCTR68_NEWDAT       0x00000008
#define CAN_MOCTR68_RTSEL        0x00000040
#define CAN_MOCTR68_RXEN         0x00000080
#define CAN_MOCTR68_RXPND        0x00000001
#define CAN_MOCTR68_RXUPD        0x00000004
#define CAN_MOCTR68_TXEN0        0x00000200
#define CAN_MOCTR68_TXEN1        0x00000400
#define CAN_MOCTR68_TXPND        0x00000002
#define CAN_MOCTR68_TXRQ         0x00000100

// Message Object 69 Control Register
#define CAN_MOCTR69            (*((uword volatile *) 0xF0004EBC))
#define CAN_MOCTR69_DIR          0x00000800
#define CAN_MOCTR69_MSGLST       0x00000010
#define CAN_MOCTR69_MSGVAL       0x00000020
#define CAN_MOCTR69_NEWDAT       0x00000008
#define CAN_MOCTR69_RTSEL        0x00000040
#define CAN_MOCTR69_RXEN         0x00000080
#define CAN_MOCTR69_RXPND        0x00000001
#define CAN_MOCTR69_RXUPD        0x00000004
#define CAN_MOCTR69_TXEN0        0x00000200
#define CAN_MOCTR69_TXEN1        0x00000400
#define CAN_MOCTR69_TXPND        0x00000002
#define CAN_MOCTR69_TXRQ         0x00000100

// Message Object 7 Control Register
#define CAN_MOCTR7             (*((uword volatile *) 0xF00046FC))
#define CAN_MOCTR7_DIR           0x00000800
#define CAN_MOCTR7_MSGLST        0x00000010
#define CAN_MOCTR7_MSGVAL        0x00000020
#define CAN_MOCTR7_NEWDAT        0x00000008
#define CAN_MOCTR7_RTSEL         0x00000040
#define CAN_MOCTR7_RXEN          0x00000080
#define CAN_MOCTR7_RXPND         0x00000001
#define CAN_MOCTR7_RXUPD         0x00000004
#define CAN_MOCTR7_TXEN0         0x00000200
#define CAN_MOCTR7_TXEN1         0x00000400
#define CAN_MOCTR7_TXPND         0x00000002
#define CAN_MOCTR7_TXRQ          0x00000100

// Message Object 70 Control Register
#define CAN_MOCTR70            (*((uword volatile *) 0xF0004EDC))
#define CAN_MOCTR70_DIR          0x00000800
#define CAN_MOCTR70_MSGLST       0x00000010
#define CAN_MOCTR70_MSGVAL       0x00000020
#define CAN_MOCTR70_NEWDAT       0x00000008
#define CAN_MOCTR70_RTSEL        0x00000040
#define CAN_MOCTR70_RXEN         0x00000080
#define CAN_MOCTR70_RXPND        0x00000001
#define CAN_MOCTR70_RXUPD        0x00000004
#define CAN_MOCTR70_TXEN0        0x00000200
#define CAN_MOCTR70_TXEN1        0x00000400
#define CAN_MOCTR70_TXPND        0x00000002
#define CAN_MOCTR70_TXRQ         0x00000100

// Message Object 71 Control Register
#define CAN_MOCTR71            (*((uword volatile *) 0xF0004EFC))
#define CAN_MOCTR71_DIR          0x00000800
#define CAN_MOCTR71_MSGLST       0x00000010
#define CAN_MOCTR71_MSGVAL       0x00000020
#define CAN_MOCTR71_NEWDAT       0x00000008
#define CAN_MOCTR71_RTSEL        0x00000040
#define CAN_MOCTR71_RXEN         0x00000080
#define CAN_MOCTR71_RXPND        0x00000001
#define CAN_MOCTR71_RXUPD        0x00000004
#define CAN_MOCTR71_TXEN0        0x00000200
#define CAN_MOCTR71_TXEN1        0x00000400
#define CAN_MOCTR71_TXPND        0x00000002
#define CAN_MOCTR71_TXRQ         0x00000100

// Message Object 72 Control Register
#define CAN_MOCTR72            (*((uword volatile *) 0xF0004F1C))
#define CAN_MOCTR72_DIR          0x00000800
#define CAN_MOCTR72_MSGLST       0x00000010
#define CAN_MOCTR72_MSGVAL       0x00000020
#define CAN_MOCTR72_NEWDAT       0x00000008
#define CAN_MOCTR72_RTSEL        0x00000040
#define CAN_MOCTR72_RXEN         0x00000080
#define CAN_MOCTR72_RXPND        0x00000001
#define CAN_MOCTR72_RXUPD        0x00000004
#define CAN_MOCTR72_TXEN0        0x00000200
#define CAN_MOCTR72_TXEN1        0x00000400
#define CAN_MOCTR72_TXPND        0x00000002
#define CAN_MOCTR72_TXRQ         0x00000100

// Message Object 73 Control Register
#define CAN_MOCTR73            (*((uword volatile *) 0xF0004F3C))
#define CAN_MOCTR73_DIR          0x00000800
#define CAN_MOCTR73_MSGLST       0x00000010
#define CAN_MOCTR73_MSGVAL       0x00000020
#define CAN_MOCTR73_NEWDAT       0x00000008
#define CAN_MOCTR73_RTSEL        0x00000040
#define CAN_MOCTR73_RXEN         0x00000080
#define CAN_MOCTR73_RXPND        0x00000001
#define CAN_MOCTR73_RXUPD        0x00000004
#define CAN_MOCTR73_TXEN0        0x00000200
#define CAN_MOCTR73_TXEN1        0x00000400
#define CAN_MOCTR73_TXPND        0x00000002
#define CAN_MOCTR73_TXRQ         0x00000100

// Message Object 74 Control Register
#define CAN_MOCTR74            (*((uword volatile *) 0xF0004F5C))
#define CAN_MOCTR74_DIR          0x00000800
#define CAN_MOCTR74_MSGLST       0x00000010
#define CAN_MOCTR74_MSGVAL       0x00000020
#define CAN_MOCTR74_NEWDAT       0x00000008
#define CAN_MOCTR74_RTSEL        0x00000040
#define CAN_MOCTR74_RXEN         0x00000080
#define CAN_MOCTR74_RXPND        0x00000001
#define CAN_MOCTR74_RXUPD        0x00000004
#define CAN_MOCTR74_TXEN0        0x00000200
#define CAN_MOCTR74_TXEN1        0x00000400
#define CAN_MOCTR74_TXPND        0x00000002
#define CAN_MOCTR74_TXRQ         0x00000100

// Message Object 75 Control Register
#define CAN_MOCTR75            (*((uword volatile *) 0xF0004F7C))
#define CAN_MOCTR75_DIR          0x00000800
#define CAN_MOCTR75_MSGLST       0x00000010
#define CAN_MOCTR75_MSGVAL       0x00000020
#define CAN_MOCTR75_NEWDAT       0x00000008
#define CAN_MOCTR75_RTSEL        0x00000040
#define CAN_MOCTR75_RXEN         0x00000080
#define CAN_MOCTR75_RXPND        0x00000001
#define CAN_MOCTR75_RXUPD        0x00000004
#define CAN_MOCTR75_TXEN0        0x00000200
#define CAN_MOCTR75_TXEN1        0x00000400
#define CAN_MOCTR75_TXPND        0x00000002
#define CAN_MOCTR75_TXRQ         0x00000100

// Message Object 76 Control Register
#define CAN_MOCTR76            (*((uword volatile *) 0xF0004F9C))
#define CAN_MOCTR76_DIR          0x00000800
#define CAN_MOCTR76_MSGLST       0x00000010
#define CAN_MOCTR76_MSGVAL       0x00000020
#define CAN_MOCTR76_NEWDAT       0x00000008
#define CAN_MOCTR76_RTSEL        0x00000040
#define CAN_MOCTR76_RXEN         0x00000080
#define CAN_MOCTR76_RXPND        0x00000001
#define CAN_MOCTR76_RXUPD        0x00000004
#define CAN_MOCTR76_TXEN0        0x00000200
#define CAN_MOCTR76_TXEN1        0x00000400
#define CAN_MOCTR76_TXPND        0x00000002
#define CAN_MOCTR76_TXRQ         0x00000100

// Message Object 77 Control Register
#define CAN_MOCTR77            (*((uword volatile *) 0xF0004FBC))
#define CAN_MOCTR77_DIR          0x00000800
#define CAN_MOCTR77_MSGLST       0x00000010
#define CAN_MOCTR77_MSGVAL       0x00000020
#define CAN_MOCTR77_NEWDAT       0x00000008
#define CAN_MOCTR77_RTSEL        0x00000040
#define CAN_MOCTR77_RXEN         0x00000080
#define CAN_MOCTR77_RXPND        0x00000001
#define CAN_MOCTR77_RXUPD        0x00000004
#define CAN_MOCTR77_TXEN0        0x00000200
#define CAN_MOCTR77_TXEN1        0x00000400
#define CAN_MOCTR77_TXPND        0x00000002
#define CAN_MOCTR77_TXRQ         0x00000100

// Message Object 78 Control Register
#define CAN_MOCTR78            (*((uword volatile *) 0xF0004FDC))
#define CAN_MOCTR78_DIR          0x00000800
#define CAN_MOCTR78_MSGLST       0x00000010
#define CAN_MOCTR78_MSGVAL       0x00000020
#define CAN_MOCTR78_NEWDAT       0x00000008
#define CAN_MOCTR78_RTSEL        0x00000040
#define CAN_MOCTR78_RXEN         0x00000080
#define CAN_MOCTR78_RXPND        0x00000001
#define CAN_MOCTR78_RXUPD        0x00000004
#define CAN_MOCTR78_TXEN0        0x00000200
#define CAN_MOCTR78_TXEN1        0x00000400
#define CAN_MOCTR78_TXPND        0x00000002
#define CAN_MOCTR78_TXRQ         0x00000100

// Message Object 79 Control Register
#define CAN_MOCTR79            (*((uword volatile *) 0xF0004FFC))
#define CAN_MOCTR79_DIR          0x00000800
#define CAN_MOCTR79_MSGLST       0x00000010
#define CAN_MOCTR79_MSGVAL       0x00000020
#define CAN_MOCTR79_NEWDAT       0x00000008
#define CAN_MOCTR79_RTSEL        0x00000040
#define CAN_MOCTR79_RXEN         0x00000080
#define CAN_MOCTR79_RXPND        0x00000001
#define CAN_MOCTR79_RXUPD        0x00000004
#define CAN_MOCTR79_TXEN0        0x00000200
#define CAN_MOCTR79_TXEN1        0x00000400
#define CAN_MOCTR79_TXPND        0x00000002
#define CAN_MOCTR79_TXRQ         0x00000100

// Message Object 8 Control Register
#define CAN_MOCTR8             (*((uword volatile *) 0xF000471C))
#define CAN_MOCTR8_DIR           0x00000800
#define CAN_MOCTR8_MSGLST        0x00000010
#define CAN_MOCTR8_MSGVAL        0x00000020
#define CAN_MOCTR8_NEWDAT        0x00000008
#define CAN_MOCTR8_RTSEL         0x00000040
#define CAN_MOCTR8_RXEN          0x00000080
#define CAN_MOCTR8_RXPND         0x00000001
#define CAN_MOCTR8_RXUPD         0x00000004
#define CAN_MOCTR8_TXEN0         0x00000200
#define CAN_MOCTR8_TXEN1         0x00000400
#define CAN_MOCTR8_TXPND         0x00000002
#define CAN_MOCTR8_TXRQ          0x00000100

// Message Object 80 Control Register
#define CAN_MOCTR80            (*((uword volatile *) 0xF000501C))
#define CAN_MOCTR80_DIR          0x00000800
#define CAN_MOCTR80_MSGLST       0x00000010
#define CAN_MOCTR80_MSGVAL       0x00000020
#define CAN_MOCTR80_NEWDAT       0x00000008
#define CAN_MOCTR80_RTSEL        0x00000040
#define CAN_MOCTR80_RXEN         0x00000080
#define CAN_MOCTR80_RXPND        0x00000001
#define CAN_MOCTR80_RXUPD        0x00000004
#define CAN_MOCTR80_TXEN0        0x00000200
#define CAN_MOCTR80_TXEN1        0x00000400
#define CAN_MOCTR80_TXPND        0x00000002
#define CAN_MOCTR80_TXRQ         0x00000100

// Message Object 81 Control Register
#define CAN_MOCTR81            (*((uword volatile *) 0xF000503C))
#define CAN_MOCTR81_DIR          0x00000800
#define CAN_MOCTR81_MSGLST       0x00000010
#define CAN_MOCTR81_MSGVAL       0x00000020
#define CAN_MOCTR81_NEWDAT       0x00000008
#define CAN_MOCTR81_RTSEL        0x00000040
#define CAN_MOCTR81_RXEN         0x00000080
#define CAN_MOCTR81_RXPND        0x00000001
#define CAN_MOCTR81_RXUPD        0x00000004
#define CAN_MOCTR81_TXEN0        0x00000200
#define CAN_MOCTR81_TXEN1        0x00000400
#define CAN_MOCTR81_TXPND        0x00000002
#define CAN_MOCTR81_TXRQ         0x00000100

// Message Object 82 Control Register
#define CAN_MOCTR82            (*((uword volatile *) 0xF000505C))
#define CAN_MOCTR82_DIR          0x00000800
#define CAN_MOCTR82_MSGLST       0x00000010
#define CAN_MOCTR82_MSGVAL       0x00000020
#define CAN_MOCTR82_NEWDAT       0x00000008
#define CAN_MOCTR82_RTSEL        0x00000040
#define CAN_MOCTR82_RXEN         0x00000080
#define CAN_MOCTR82_RXPND        0x00000001
#define CAN_MOCTR82_RXUPD        0x00000004
#define CAN_MOCTR82_TXEN0        0x00000200
#define CAN_MOCTR82_TXEN1        0x00000400
#define CAN_MOCTR82_TXPND        0x00000002
#define CAN_MOCTR82_TXRQ         0x00000100

// Message Object 83 Control Register
#define CAN_MOCTR83            (*((uword volatile *) 0xF000507C))
#define CAN_MOCTR83_DIR          0x00000800
#define CAN_MOCTR83_MSGLST       0x00000010
#define CAN_MOCTR83_MSGVAL       0x00000020
#define CAN_MOCTR83_NEWDAT       0x00000008
#define CAN_MOCTR83_RTSEL        0x00000040
#define CAN_MOCTR83_RXEN         0x00000080
#define CAN_MOCTR83_RXPND        0x00000001
#define CAN_MOCTR83_RXUPD        0x00000004
#define CAN_MOCTR83_TXEN0        0x00000200
#define CAN_MOCTR83_TXEN1        0x00000400
#define CAN_MOCTR83_TXPND        0x00000002
#define CAN_MOCTR83_TXRQ         0x00000100

// Message Object 84 Control Register
#define CAN_MOCTR84            (*((uword volatile *) 0xF000509C))
#define CAN_MOCTR84_DIR          0x00000800
#define CAN_MOCTR84_MSGLST       0x00000010
#define CAN_MOCTR84_MSGVAL       0x00000020
#define CAN_MOCTR84_NEWDAT       0x00000008
#define CAN_MOCTR84_RTSEL        0x00000040
#define CAN_MOCTR84_RXEN         0x00000080
#define CAN_MOCTR84_RXPND        0x00000001
#define CAN_MOCTR84_RXUPD        0x00000004
#define CAN_MOCTR84_TXEN0        0x00000200
#define CAN_MOCTR84_TXEN1        0x00000400
#define CAN_MOCTR84_TXPND        0x00000002
#define CAN_MOCTR84_TXRQ         0x00000100

// Message Object 85 Control Register
#define CAN_MOCTR85            (*((uword volatile *) 0xF00050BC))
#define CAN_MOCTR85_DIR          0x00000800
#define CAN_MOCTR85_MSGLST       0x00000010
#define CAN_MOCTR85_MSGVAL       0x00000020
#define CAN_MOCTR85_NEWDAT       0x00000008
#define CAN_MOCTR85_RTSEL        0x00000040
#define CAN_MOCTR85_RXEN         0x00000080
#define CAN_MOCTR85_RXPND        0x00000001
#define CAN_MOCTR85_RXUPD        0x00000004
#define CAN_MOCTR85_TXEN0        0x00000200
#define CAN_MOCTR85_TXEN1        0x00000400
#define CAN_MOCTR85_TXPND        0x00000002
#define CAN_MOCTR85_TXRQ         0x00000100

// Message Object 86 Control Register
#define CAN_MOCTR86            (*((uword volatile *) 0xF00050DC))
#define CAN_MOCTR86_DIR          0x00000800
#define CAN_MOCTR86_MSGLST       0x00000010
#define CAN_MOCTR86_MSGVAL       0x00000020
#define CAN_MOCTR86_NEWDAT       0x00000008
#define CAN_MOCTR86_RTSEL        0x00000040
#define CAN_MOCTR86_RXEN         0x00000080
#define CAN_MOCTR86_RXPND        0x00000001
#define CAN_MOCTR86_RXUPD        0x00000004
#define CAN_MOCTR86_TXEN0        0x00000200
#define CAN_MOCTR86_TXEN1        0x00000400
#define CAN_MOCTR86_TXPND        0x00000002
#define CAN_MOCTR86_TXRQ         0x00000100

// Message Object 87 Control Register
#define CAN_MOCTR87            (*((uword volatile *) 0xF00050FC))
#define CAN_MOCTR87_DIR          0x00000800
#define CAN_MOCTR87_MSGLST       0x00000010
#define CAN_MOCTR87_MSGVAL       0x00000020
#define CAN_MOCTR87_NEWDAT       0x00000008
#define CAN_MOCTR87_RTSEL        0x00000040
#define CAN_MOCTR87_RXEN         0x00000080
#define CAN_MOCTR87_RXPND        0x00000001
#define CAN_MOCTR87_RXUPD        0x00000004
#define CAN_MOCTR87_TXEN0        0x00000200
#define CAN_MOCTR87_TXEN1        0x00000400
#define CAN_MOCTR87_TXPND        0x00000002
#define CAN_MOCTR87_TXRQ         0x00000100

// Message Object 88 Control Register
#define CAN_MOCTR88            (*((uword volatile *) 0xF000511C))
#define CAN_MOCTR88_DIR          0x00000800
#define CAN_MOCTR88_MSGLST       0x00000010
#define CAN_MOCTR88_MSGVAL       0x00000020
#define CAN_MOCTR88_NEWDAT       0x00000008
#define CAN_MOCTR88_RTSEL        0x00000040
#define CAN_MOCTR88_RXEN         0x00000080
#define CAN_MOCTR88_RXPND        0x00000001
#define CAN_MOCTR88_RXUPD        0x00000004
#define CAN_MOCTR88_TXEN0        0x00000200
#define CAN_MOCTR88_TXEN1        0x00000400
#define CAN_MOCTR88_TXPND        0x00000002
#define CAN_MOCTR88_TXRQ         0x00000100

// Message Object 89 Control Register
#define CAN_MOCTR89            (*((uword volatile *) 0xF000513C))
#define CAN_MOCTR89_DIR          0x00000800
#define CAN_MOCTR89_MSGLST       0x00000010
#define CAN_MOCTR89_MSGVAL       0x00000020
#define CAN_MOCTR89_NEWDAT       0x00000008
#define CAN_MOCTR89_RTSEL        0x00000040
#define CAN_MOCTR89_RXEN         0x00000080
#define CAN_MOCTR89_RXPND        0x00000001
#define CAN_MOCTR89_RXUPD        0x00000004
#define CAN_MOCTR89_TXEN0        0x00000200
#define CAN_MOCTR89_TXEN1        0x00000400
#define CAN_MOCTR89_TXPND        0x00000002
#define CAN_MOCTR89_TXRQ         0x00000100

// Message Object 9 Control Register
#define CAN_MOCTR9             (*((uword volatile *) 0xF000473C))
#define CAN_MOCTR9_DIR           0x00000800
#define CAN_MOCTR9_MSGLST        0x00000010
#define CAN_MOCTR9_MSGVAL        0x00000020
#define CAN_MOCTR9_NEWDAT        0x00000008
#define CAN_MOCTR9_RTSEL         0x00000040
#define CAN_MOCTR9_RXEN          0x00000080
#define CAN_MOCTR9_RXPND         0x00000001
#define CAN_MOCTR9_RXUPD         0x00000004
#define CAN_MOCTR9_TXEN0         0x00000200
#define CAN_MOCTR9_TXEN1         0x00000400
#define CAN_MOCTR9_TXPND         0x00000002
#define CAN_MOCTR9_TXRQ          0x00000100

// Message Object 90 Control Register
#define CAN_MOCTR90            (*((uword volatile *) 0xF000515C))
#define CAN_MOCTR90_DIR          0x00000800
#define CAN_MOCTR90_MSGLST       0x00000010
#define CAN_MOCTR90_MSGVAL       0x00000020
#define CAN_MOCTR90_NEWDAT       0x00000008
#define CAN_MOCTR90_RTSEL        0x00000040
#define CAN_MOCTR90_RXEN         0x00000080
#define CAN_MOCTR90_RXPND        0x00000001
#define CAN_MOCTR90_RXUPD        0x00000004
#define CAN_MOCTR90_TXEN0        0x00000200
#define CAN_MOCTR90_TXEN1        0x00000400
#define CAN_MOCTR90_TXPND        0x00000002
#define CAN_MOCTR90_TXRQ         0x00000100

// Message Object 91 Control Register
#define CAN_MOCTR91            (*((uword volatile *) 0xF000517C))
#define CAN_MOCTR91_DIR          0x00000800
#define CAN_MOCTR91_MSGLST       0x00000010
#define CAN_MOCTR91_MSGVAL       0x00000020
#define CAN_MOCTR91_NEWDAT       0x00000008
#define CAN_MOCTR91_RTSEL        0x00000040
#define CAN_MOCTR91_RXEN         0x00000080
#define CAN_MOCTR91_RXPND        0x00000001
#define CAN_MOCTR91_RXUPD        0x00000004
#define CAN_MOCTR91_TXEN0        0x00000200
#define CAN_MOCTR91_TXEN1        0x00000400
#define CAN_MOCTR91_TXPND        0x00000002
#define CAN_MOCTR91_TXRQ         0x00000100

// Message Object 92 Control Register
#define CAN_MOCTR92            (*((uword volatile *) 0xF000519C))
#define CAN_MOCTR92_DIR          0x00000800
#define CAN_MOCTR92_MSGLST       0x00000010
#define CAN_MOCTR92_MSGVAL       0x00000020
#define CAN_MOCTR92_NEWDAT       0x00000008
#define CAN_MOCTR92_RTSEL        0x00000040
#define CAN_MOCTR92_RXEN         0x00000080
#define CAN_MOCTR92_RXPND        0x00000001
#define CAN_MOCTR92_RXUPD        0x00000004
#define CAN_MOCTR92_TXEN0        0x00000200
#define CAN_MOCTR92_TXEN1        0x00000400
#define CAN_MOCTR92_TXPND        0x00000002
#define CAN_MOCTR92_TXRQ         0x00000100

// Message Object 93 Control Register
#define CAN_MOCTR93            (*((uword volatile *) 0xF00051BC))
#define CAN_MOCTR93_DIR          0x00000800
#define CAN_MOCTR93_MSGLST       0x00000010
#define CAN_MOCTR93_MSGVAL       0x00000020
#define CAN_MOCTR93_NEWDAT       0x00000008
#define CAN_MOCTR93_RTSEL        0x00000040
#define CAN_MOCTR93_RXEN         0x00000080
#define CAN_MOCTR93_RXPND        0x00000001
#define CAN_MOCTR93_RXUPD        0x00000004
#define CAN_MOCTR93_TXEN0        0x00000200
#define CAN_MOCTR93_TXEN1        0x00000400
#define CAN_MOCTR93_TXPND        0x00000002
#define CAN_MOCTR93_TXRQ         0x00000100

// Message Object 94 Control Register
#define CAN_MOCTR94            (*((uword volatile *) 0xF00051DC))
#define CAN_MOCTR94_DIR          0x00000800
#define CAN_MOCTR94_MSGLST       0x00000010
#define CAN_MOCTR94_MSGVAL       0x00000020
#define CAN_MOCTR94_NEWDAT       0x00000008
#define CAN_MOCTR94_RTSEL        0x00000040
#define CAN_MOCTR94_RXEN         0x00000080
#define CAN_MOCTR94_RXPND        0x00000001
#define CAN_MOCTR94_RXUPD        0x00000004
#define CAN_MOCTR94_TXEN0        0x00000200
#define CAN_MOCTR94_TXEN1        0x00000400
#define CAN_MOCTR94_TXPND        0x00000002
#define CAN_MOCTR94_TXRQ         0x00000100

// Message Object 95 Control Register
#define CAN_MOCTR95            (*((uword volatile *) 0xF00051FC))
#define CAN_MOCTR95_DIR          0x00000800
#define CAN_MOCTR95_MSGLST       0x00000010
#define CAN_MOCTR95_MSGVAL       0x00000020
#define CAN_MOCTR95_NEWDAT       0x00000008
#define CAN_MOCTR95_RTSEL        0x00000040
#define CAN_MOCTR95_RXEN         0x00000080
#define CAN_MOCTR95_RXPND        0x00000001
#define CAN_MOCTR95_RXUPD        0x00000004
#define CAN_MOCTR95_TXEN0        0x00000200
#define CAN_MOCTR95_TXEN1        0x00000400
#define CAN_MOCTR95_TXPND        0x00000002
#define CAN_MOCTR95_TXRQ         0x00000100

// Message Object 96 Control Register
#define CAN_MOCTR96            (*((uword volatile *) 0xF000521C))
#define CAN_MOCTR96_DIR          0x00000800
#define CAN_MOCTR96_MSGLST       0x00000010
#define CAN_MOCTR96_MSGVAL       0x00000020
#define CAN_MOCTR96_NEWDAT       0x00000008
#define CAN_MOCTR96_RTSEL        0x00000040
#define CAN_MOCTR96_RXEN         0x00000080
#define CAN_MOCTR96_RXPND        0x00000001
#define CAN_MOCTR96_RXUPD        0x00000004
#define CAN_MOCTR96_TXEN0        0x00000200
#define CAN_MOCTR96_TXEN1        0x00000400
#define CAN_MOCTR96_TXPND        0x00000002
#define CAN_MOCTR96_TXRQ         0x00000100

// Message Object 97 Control Register
#define CAN_MOCTR97            (*((uword volatile *) 0xF000523C))
#define CAN_MOCTR97_DIR          0x00000800
#define CAN_MOCTR97_MSGLST       0x00000010
#define CAN_MOCTR97_MSGVAL       0x00000020
#define CAN_MOCTR97_NEWDAT       0x00000008
#define CAN_MOCTR97_RTSEL        0x00000040
#define CAN_MOCTR97_RXEN         0x00000080
#define CAN_MOCTR97_RXPND        0x00000001
#define CAN_MOCTR97_RXUPD        0x00000004
#define CAN_MOCTR97_TXEN0        0x00000200
#define CAN_MOCTR97_TXEN1        0x00000400
#define CAN_MOCTR97_TXPND        0x00000002
#define CAN_MOCTR97_TXRQ         0x00000100

// Message Object 98 Control Register
#define CAN_MOCTR98            (*((uword volatile *) 0xF000525C))
#define CAN_MOCTR98_DIR          0x00000800
#define CAN_MOCTR98_MSGLST       0x00000010
#define CAN_MOCTR98_MSGVAL       0x00000020
#define CAN_MOCTR98_NEWDAT       0x00000008
#define CAN_MOCTR98_RTSEL        0x00000040
#define CAN_MOCTR98_RXEN         0x00000080
#define CAN_MOCTR98_RXPND        0x00000001
#define CAN_MOCTR98_RXUPD        0x00000004
#define CAN_MOCTR98_TXEN0        0x00000200
#define CAN_MOCTR98_TXEN1        0x00000400
#define CAN_MOCTR98_TXPND        0x00000002
#define CAN_MOCTR98_TXRQ         0x00000100

// Message Object 99 Control Register
#define CAN_MOCTR99            (*((uword volatile *) 0xF000527C))
#define CAN_MOCTR99_DIR          0x00000800
#define CAN_MOCTR99_MSGLST       0x00000010
#define CAN_MOCTR99_MSGVAL       0x00000020
#define CAN_MOCTR99_NEWDAT       0x00000008
#define CAN_MOCTR99_RTSEL        0x00000040
#define CAN_MOCTR99_RXEN         0x00000080
#define CAN_MOCTR99_RXPND        0x00000001
#define CAN_MOCTR99_RXUPD        0x00000004
#define CAN_MOCTR99_TXEN0        0x00000200
#define CAN_MOCTR99_TXEN1        0x00000400
#define CAN_MOCTR99_TXPND        0x00000002
#define CAN_MOCTR99_TXRQ         0x00000100

// Message Object 0 Data Register High
#define CAN_MODATAH0           (*((uword volatile *) 0xF0004614))

// Message Object 1 Data Register High
#define CAN_MODATAH1           (*((uword volatile *) 0xF0004634))

// Message Object 10 Data Register High
#define CAN_MODATAH10          (*((uword volatile *) 0xF0004754))

// Message Object 100 Data Register High
#define CAN_MODATAH100         (*((uword volatile *) 0xF0005294))

// Message Object 101 Data Register High
#define CAN_MODATAH101         (*((uword volatile *) 0xF00052B4))

// Message Object 102 Data Register High
#define CAN_MODATAH102         (*((uword volatile *) 0xF00052D4))

// Message Object 103 Data Register High
#define CAN_MODATAH103         (*((uword volatile *) 0xF00052F4))

// Message Object 104 Data Register High
#define CAN_MODATAH104         (*((uword volatile *) 0xF0005314))

// Message Object 105 Data Register High
#define CAN_MODATAH105         (*((uword volatile *) 0xF0005334))

// Message Object 106 Data Register High
#define CAN_MODATAH106         (*((uword volatile *) 0xF0005354))

// Message Object 107 Data Register High
#define CAN_MODATAH107         (*((uword volatile *) 0xF0005374))

// Message Object 108 Data Register High
#define CAN_MODATAH108         (*((uword volatile *) 0xF0005394))

// Message Object 109 Data Register High
#define CAN_MODATAH109         (*((uword volatile *) 0xF00053B4))

// Message Object 11 Data Register High
#define CAN_MODATAH11          (*((uword volatile *) 0xF0004774))

// Message Object 110 Data Register High
#define CAN_MODATAH110         (*((uword volatile *) 0xF00053D4))

// Message Object 111 Data Register High
#define CAN_MODATAH111         (*((uword volatile *) 0xF00053F4))

// Message Object 112 Data Register High
#define CAN_MODATAH112         (*((uword volatile *) 0xF0005414))

// Message Object 113 Data Register High
#define CAN_MODATAH113         (*((uword volatile *) 0xF0005434))

// Message Object 114 Data Register High
#define CAN_MODATAH114         (*((uword volatile *) 0xF0005454))

// Message Object 115 Data Register High
#define CAN_MODATAH115         (*((uword volatile *) 0xF0005474))

// Message Object 116 Data Register High
#define CAN_MODATAH116         (*((uword volatile *) 0xF0005494))

// Message Object 117 Data Register High
#define CAN_MODATAH117         (*((uword volatile *) 0xF00054B4))

// Message Object 118 Data Register High
#define CAN_MODATAH118         (*((uword volatile *) 0xF00054D4))

// Message Object 119 Data Register High
#define CAN_MODATAH119         (*((uword volatile *) 0xF00054F4))

// Message Object 12 Data Register High
#define CAN_MODATAH12          (*((uword volatile *) 0xF0004794))

// Message Object 120 Data Register High
#define CAN_MODATAH120         (*((uword volatile *) 0xF0005514))

// Message Object 121 Data Register High
#define CAN_MODATAH121         (*((uword volatile *) 0xF0005534))

// Message Object 122 Data Register High
#define CAN_MODATAH122         (*((uword volatile *) 0xF0005554))

// Message Object 123 Data Register High
#define CAN_MODATAH123         (*((uword volatile *) 0xF0005574))

// Message Object 124 Data Register High
#define CAN_MODATAH124         (*((uword volatile *) 0xF0005594))

// Message Object 125 Data Register High
#define CAN_MODATAH125         (*((uword volatile *) 0xF00055B4))

// Message Object 126 Data Register High
#define CAN_MODATAH126         (*((uword volatile *) 0xF00055D4))

// Message Object 127 Data Register High
#define CAN_MODATAH127         (*((uword volatile *) 0xF00055F4))

// Message Object 13 Data Register High
#define CAN_MODATAH13          (*((uword volatile *) 0xF00047B4))

// Message Object 14 Data Register High
#define CAN_MODATAH14          (*((uword volatile *) 0xF00047D4))

// Message Object 15 Data Register High
#define CAN_MODATAH15          (*((uword volatile *) 0xF00047F4))

// Message Object 16 Data Register High
#define CAN_MODATAH16          (*((uword volatile *) 0xF0004814))

// Message Object 17 Data Register High
#define CAN_MODATAH17          (*((uword volatile *) 0xF0004834))

// Message Object 18 Data Register High
#define CAN_MODATAH18          (*((uword volatile *) 0xF0004854))

// Message Object 19 Data Register High
#define CAN_MODATAH19          (*((uword volatile *) 0xF0004874))

// Message Object 2 Data Register High
#define CAN_MODATAH2           (*((uword volatile *) 0xF0004654))

// Message Object 20 Data Register High
#define CAN_MODATAH20          (*((uword volatile *) 0xF0004894))

// Message Object 21 Data Register High
#define CAN_MODATAH21          (*((uword volatile *) 0xF00048B4))

// Message Object 22 Data Register High
#define CAN_MODATAH22          (*((uword volatile *) 0xF00048D4))

// Message Object 23 Data Register High
#define CAN_MODATAH23          (*((uword volatile *) 0xF00048F4))

// Message Object 24 Data Register High
#define CAN_MODATAH24          (*((uword volatile *) 0xF0004914))

// Message Object 25 Data Register High
#define CAN_MODATAH25          (*((uword volatile *) 0xF0004934))

// Message Object 26 Data Register High
#define CAN_MODATAH26          (*((uword volatile *) 0xF0004954))

// Message Object 27 Data Register High
#define CAN_MODATAH27          (*((uword volatile *) 0xF0004974))

// Message Object 28 Data Register High
#define CAN_MODATAH28          (*((uword volatile *) 0xF0004994))

// Message Object 29 Data Register High
#define CAN_MODATAH29          (*((uword volatile *) 0xF00049B4))

// Message Object 3 Data Register High
#define CAN_MODATAH3           (*((uword volatile *) 0xF0004674))

// Message Object 30 Data Register High
#define CAN_MODATAH30          (*((uword volatile *) 0xF00049D4))

// Message Object 31 Data Register High
#define CAN_MODATAH31          (*((uword volatile *) 0xF00049F4))

// Message Object 32 Data Register High
#define CAN_MODATAH32          (*((uword volatile *) 0xF0004A14))

// Message Object 33 Data Register High
#define CAN_MODATAH33          (*((uword volatile *) 0xF0004A34))

// Message Object 34 Data Register High
#define CAN_MODATAH34          (*((uword volatile *) 0xF0004A54))

// Message Object 35 Data Register High
#define CAN_MODATAH35          (*((uword volatile *) 0xF0004A74))

// Message Object 36 Data Register High
#define CAN_MODATAH36          (*((uword volatile *) 0xF0004A94))

// Message Object 37 Data Register High
#define CAN_MODATAH37          (*((uword volatile *) 0xF0004AB4))

// Message Object 38 Data Register High
#define CAN_MODATAH38          (*((uword volatile *) 0xF0004AD4))

// Message Object 39 Data Register High
#define CAN_MODATAH39          (*((uword volatile *) 0xF0004AF4))

// Message Object 4 Data Register High
#define CAN_MODATAH4           (*((uword volatile *) 0xF0004694))

// Message Object 40 Data Register High
#define CAN_MODATAH40          (*((uword volatile *) 0xF0004B14))

// Message Object 41 Data Register High
#define CAN_MODATAH41          (*((uword volatile *) 0xF0004B34))

// Message Object 42 Data Register High
#define CAN_MODATAH42          (*((uword volatile *) 0xF0004B54))

// Message Object 43 Data Register High
#define CAN_MODATAH43          (*((uword volatile *) 0xF0004B74))

// Message Object 44 Data Register High
#define CAN_MODATAH44          (*((uword volatile *) 0xF0004B94))

// Message Object 45 Data Register High
#define CAN_MODATAH45          (*((uword volatile *) 0xF0004BB4))

// Message Object 46 Data Register High
#define CAN_MODATAH46          (*((uword volatile *) 0xF0004BD4))

// Message Object 47 Data Register High
#define CAN_MODATAH47          (*((uword volatile *) 0xF0004BF4))

// Message Object 48 Data Register High
#define CAN_MODATAH48          (*((uword volatile *) 0xF0004C14))

// Message Object 49 Data Register High
#define CAN_MODATAH49          (*((uword volatile *) 0xF0004C34))

// Message Object 5 Data Register High
#define CAN_MODATAH5           (*((uword volatile *) 0xF00046B4))

// Message Object 50 Data Register High
#define CAN_MODATAH50          (*((uword volatile *) 0xF0004C54))

// Message Object 51 Data Register High
#define CAN_MODATAH51          (*((uword volatile *) 0xF0004C74))

// Message Object 52 Data Register High
#define CAN_MODATAH52          (*((uword volatile *) 0xF0004C94))

// Message Object 53 Data Register High
#define CAN_MODATAH53          (*((uword volatile *) 0xF0004CB4))

// Message Object 54 Data Register High
#define CAN_MODATAH54          (*((uword volatile *) 0xF0004CD4))

// Message Object 55 Data Register High
#define CAN_MODATAH55          (*((uword volatile *) 0xF0004CF4))

// Message Object 56 Data Register High
#define CAN_MODATAH56          (*((uword volatile *) 0xF0004D14))

// Message Object 57 Data Register High
#define CAN_MODATAH57          (*((uword volatile *) 0xF0004D34))

// Message Object 58 Data Register High
#define CAN_MODATAH58          (*((uword volatile *) 0xF0004D54))

// Message Object 59 Data Register High
#define CAN_MODATAH59          (*((uword volatile *) 0xF0004D74))

// Message Object 6 Data Register High
#define CAN_MODATAH6           (*((uword volatile *) 0xF00046D4))

// Message Object 60 Data Register High
#define CAN_MODATAH60          (*((uword volatile *) 0xF0004D94))

// Message Object 61 Data Register High
#define CAN_MODATAH61          (*((uword volatile *) 0xF0004DB4))

// Message Object 62 Data Register High
#define CAN_MODATAH62          (*((uword volatile *) 0xF0004DD4))

// Message Object 63 Data Register High
#define CAN_MODATAH63          (*((uword volatile *) 0xF0004DF4))

// Message Object 64 Data Register High
#define CAN_MODATAH64          (*((uword volatile *) 0xF0004E14))

// Message Object 65 Data Register High
#define CAN_MODATAH65          (*((uword volatile *) 0xF0004E34))

// Message Object 66 Data Register High
#define CAN_MODATAH66          (*((uword volatile *) 0xF0004E54))

// Message Object 67 Data Register High
#define CAN_MODATAH67          (*((uword volatile *) 0xF0004E74))

// Message Object 68 Data Register High
#define CAN_MODATAH68          (*((uword volatile *) 0xF0004E94))

// Message Object 69 Data Register High
#define CAN_MODATAH69          (*((uword volatile *) 0xF0004EB4))

// Message Object 7 Data Register High
#define CAN_MODATAH7           (*((uword volatile *) 0xF00046F4))

// Message Object 70 Data Register High
#define CAN_MODATAH70          (*((uword volatile *) 0xF0004ED4))

// Message Object 71 Data Register High
#define CAN_MODATAH71          (*((uword volatile *) 0xF0004EF4))

// Message Object 72 Data Register High
#define CAN_MODATAH72          (*((uword volatile *) 0xF0004F14))

// Message Object 73 Data Register High
#define CAN_MODATAH73          (*((uword volatile *) 0xF0004F34))

// Message Object 74 Data Register High
#define CAN_MODATAH74          (*((uword volatile *) 0xF0004F54))

// Message Object 75 Data Register High
#define CAN_MODATAH75          (*((uword volatile *) 0xF0004F74))

// Message Object 76 Data Register High
#define CAN_MODATAH76          (*((uword volatile *) 0xF0004F94))

// Message Object 77 Data Register High
#define CAN_MODATAH77          (*((uword volatile *) 0xF0004FB4))

// Message Object 78 Data Register High
#define CAN_MODATAH78          (*((uword volatile *) 0xF0004FD4))

// Message Object 79 Data Register High
#define CAN_MODATAH79          (*((uword volatile *) 0xF0004FF4))

// Message Object 8 Data Register High
#define CAN_MODATAH8           (*((uword volatile *) 0xF0004714))

// Message Object 80 Data Register High
#define CAN_MODATAH80          (*((uword volatile *) 0xF0005014))

// Message Object 81 Data Register High
#define CAN_MODATAH81          (*((uword volatile *) 0xF0005034))

// Message Object 82 Data Register High
#define CAN_MODATAH82          (*((uword volatile *) 0xF0005054))

// Message Object 83 Data Register High
#define CAN_MODATAH83          (*((uword volatile *) 0xF0005074))

// Message Object 84 Data Register High
#define CAN_MODATAH84          (*((uword volatile *) 0xF0005094))

// Message Object 85 Data Register High
#define CAN_MODATAH85          (*((uword volatile *) 0xF00050B4))

// Message Object 86 Data Register High
#define CAN_MODATAH86          (*((uword volatile *) 0xF00050D4))

// Message Object 87 Data Register High
#define CAN_MODATAH87          (*((uword volatile *) 0xF00050F4))

// Message Object 88 Data Register High
#define CAN_MODATAH88          (*((uword volatile *) 0xF0005114))

// Message Object 89 Data Register High
#define CAN_MODATAH89          (*((uword volatile *) 0xF0005134))

// Message Object 9 Data Register High
#define CAN_MODATAH9           (*((uword volatile *) 0xF0004734))

// Message Object 90 Data Register High
#define CAN_MODATAH90          (*((uword volatile *) 0xF0005154))

// Message Object 91 Data Register High
#define CAN_MODATAH91          (*((uword volatile *) 0xF0005174))

// Message Object 92 Data Register High
#define CAN_MODATAH92          (*((uword volatile *) 0xF0005194))

// Message Object 93 Data Register High
#define CAN_MODATAH93          (*((uword volatile *) 0xF00051B4))

// Message Object 94 Data Register High
#define CAN_MODATAH94          (*((uword volatile *) 0xF00051D4))

// Message Object 95 Data Register High
#define CAN_MODATAH95          (*((uword volatile *) 0xF00051F4))

// Message Object 96 Data Register High
#define CAN_MODATAH96          (*((uword volatile *) 0xF0005214))

// Message Object 97 Data Register High
#define CAN_MODATAH97          (*((uword volatile *) 0xF0005234))

// Message Object 98 Data Register High
#define CAN_MODATAH98          (*((uword volatile *) 0xF0005254))

// Message Object 99 Data Register High
#define CAN_MODATAH99          (*((uword volatile *) 0xF0005274))

// Message Object 0 Data Register Low
#define CAN_MODATAL0           (*((uword volatile *) 0xF0004610))

// Message Object 1 Data Register Low
#define CAN_MODATAL1           (*((uword volatile *) 0xF0004630))

// Message Object 10 Data Register Low
#define CAN_MODATAL10          (*((uword volatile *) 0xF0004750))

// Message Object 100 Data Register Low
#define CAN_MODATAL100         (*((uword volatile *) 0xF0005290))

// Message Object 101 Data Register Low
#define CAN_MODATAL101         (*((uword volatile *) 0xF00052B0))

// Message Object 102 Data Register Low
#define CAN_MODATAL102         (*((uword volatile *) 0xF00052D0))

// Message Object 103 Data Register Low
#define CAN_MODATAL103         (*((uword volatile *) 0xF00052F0))

// Message Object 104 Data Register Low
#define CAN_MODATAL104         (*((uword volatile *) 0xF0005310))

// Message Object 105 Data Register Low
#define CAN_MODATAL105         (*((uword volatile *) 0xF0005330))

// Message Object 106 Data Register Low
#define CAN_MODATAL106         (*((uword volatile *) 0xF0005350))

// Message Object 107 Data Register Low
#define CAN_MODATAL107         (*((uword volatile *) 0xF0005370))

// Message Object 108 Data Register Low
#define CAN_MODATAL108         (*((uword volatile *) 0xF0005390))

// Message Object 109 Data Register Low
#define CAN_MODATAL109         (*((uword volatile *) 0xF00053B0))

// Message Object 11 Data Register Low
#define CAN_MODATAL11          (*((uword volatile *) 0xF0004770))

// Message Object 110 Data Register Low
#define CAN_MODATAL110         (*((uword volatile *) 0xF00053D0))

// Message Object 111 Data Register Low
#define CAN_MODATAL111         (*((uword volatile *) 0xF00053F0))

// Message Object 112 Data Register Low
#define CAN_MODATAL112         (*((uword volatile *) 0xF0005410))

// Message Object 113 Data Register Low
#define CAN_MODATAL113         (*((uword volatile *) 0xF0005430))

// Message Object 114 Data Register Low
#define CAN_MODATAL114         (*((uword volatile *) 0xF0005450))

// Message Object 115 Data Register Low
#define CAN_MODATAL115         (*((uword volatile *) 0xF0005470))

// Message Object 116 Data Register Low
#define CAN_MODATAL116         (*((uword volatile *) 0xF0005490))

// Message Object 117 Data Register Low
#define CAN_MODATAL117         (*((uword volatile *) 0xF00054B0))

// Message Object 118 Data Register Low
#define CAN_MODATAL118         (*((uword volatile *) 0xF00054D0))

// Message Object 119 Data Register Low
#define CAN_MODATAL119         (*((uword volatile *) 0xF00054F0))

// Message Object 12 Data Register Low
#define CAN_MODATAL12          (*((uword volatile *) 0xF0004790))

// Message Object 120 Data Register Low
#define CAN_MODATAL120         (*((uword volatile *) 0xF0005510))

// Message Object 121 Data Register Low
#define CAN_MODATAL121         (*((uword volatile *) 0xF0005530))

// Message Object 122 Data Register Low
#define CAN_MODATAL122         (*((uword volatile *) 0xF0005550))

// Message Object 123 Data Register Low
#define CAN_MODATAL123         (*((uword volatile *) 0xF0005570))

// Message Object 124 Data Register Low
#define CAN_MODATAL124         (*((uword volatile *) 0xF0005590))

// Message Object 125 Data Register Low
#define CAN_MODATAL125         (*((uword volatile *) 0xF00055B0))

// Message Object 126 Data Register Low
#define CAN_MODATAL126         (*((uword volatile *) 0xF00055D0))

// Message Object 127 Data Register Low
#define CAN_MODATAL127         (*((uword volatile *) 0xF00055F0))

// Message Object 13 Data Register Low
#define CAN_MODATAL13          (*((uword volatile *) 0xF00047B0))

// Message Object 14 Data Register Low
#define CAN_MODATAL14          (*((uword volatile *) 0xF00047D0))

// Message Object 15 Data Register Low
#define CAN_MODATAL15          (*((uword volatile *) 0xF00047F0))

// Message Object 16 Data Register Low
#define CAN_MODATAL16          (*((uword volatile *) 0xF0004810))

// Message Object 17 Data Register Low
#define CAN_MODATAL17          (*((uword volatile *) 0xF0004830))

// Message Object 18 Data Register Low
#define CAN_MODATAL18          (*((uword volatile *) 0xF0004850))

// Message Object 19 Data Register Low
#define CAN_MODATAL19          (*((uword volatile *) 0xF0004870))

// Message Object 2 Data Register Low
#define CAN_MODATAL2           (*((uword volatile *) 0xF0004650))

// Message Object 20 Data Register Low
#define CAN_MODATAL20          (*((uword volatile *) 0xF0004890))

// Message Object 21 Data Register Low
#define CAN_MODATAL21          (*((uword volatile *) 0xF00048B0))

// Message Object 22 Data Register Low
#define CAN_MODATAL22          (*((uword volatile *) 0xF00048D0))

// Message Object 23 Data Register Low
#define CAN_MODATAL23          (*((uword volatile *) 0xF00048F0))

// Message Object 24 Data Register Low
#define CAN_MODATAL24          (*((uword volatile *) 0xF0004910))

// Message Object 25 Data Register Low
#define CAN_MODATAL25          (*((uword volatile *) 0xF0004930))

// Message Object 26 Data Register Low
#define CAN_MODATAL26          (*((uword volatile *) 0xF0004950))

// Message Object 27 Data Register Low
#define CAN_MODATAL27          (*((uword volatile *) 0xF0004970))

// Message Object 28 Data Register Low
#define CAN_MODATAL28          (*((uword volatile *) 0xF0004990))

// Message Object 29 Data Register Low
#define CAN_MODATAL29          (*((uword volatile *) 0xF00049B0))

// Message Object 3 Data Register Low
#define CAN_MODATAL3           (*((uword volatile *) 0xF0004670))

// Message Object 30 Data Register Low
#define CAN_MODATAL30          (*((uword volatile *) 0xF00049D0))

// Message Object 31 Data Register Low
#define CAN_MODATAL31          (*((uword volatile *) 0xF00049F0))

// Message Object 32 Data Register Low
#define CAN_MODATAL32          (*((uword volatile *) 0xF0004A10))

// Message Object 33 Data Register Low
#define CAN_MODATAL33          (*((uword volatile *) 0xF0004A30))

// Message Object 34 Data Register Low
#define CAN_MODATAL34          (*((uword volatile *) 0xF0004A50))

// Message Object 35 Data Register Low
#define CAN_MODATAL35          (*((uword volatile *) 0xF0004A70))

// Message Object 36 Data Register Low
#define CAN_MODATAL36          (*((uword volatile *) 0xF0004A90))

// Message Object 37 Data Register Low
#define CAN_MODATAL37          (*((uword volatile *) 0xF0004AB0))

// Message Object 38 Data Register Low
#define CAN_MODATAL38          (*((uword volatile *) 0xF0004AD0))

// Message Object 39 Data Register Low
#define CAN_MODATAL39          (*((uword volatile *) 0xF0004AF0))

// Message Object 4 Data Register Low
#define CAN_MODATAL4           (*((uword volatile *) 0xF0004690))

// Message Object 40 Data Register Low
#define CAN_MODATAL40          (*((uword volatile *) 0xF0004B10))

// Message Object 41 Data Register Low
#define CAN_MODATAL41          (*((uword volatile *) 0xF0004B30))

// Message Object 42 Data Register Low
#define CAN_MODATAL42          (*((uword volatile *) 0xF0004B50))

// Message Object 43 Data Register Low
#define CAN_MODATAL43          (*((uword volatile *) 0xF0004B70))

// Message Object 44 Data Register Low
#define CAN_MODATAL44          (*((uword volatile *) 0xF0004B90))

// Message Object 45 Data Register Low
#define CAN_MODATAL45          (*((uword volatile *) 0xF0004BB0))

// Message Object 46 Data Register Low
#define CAN_MODATAL46          (*((uword volatile *) 0xF0004BD0))

// Message Object 47 Data Register Low
#define CAN_MODATAL47          (*((uword volatile *) 0xF0004BF0))

// Message Object 48 Data Register Low
#define CAN_MODATAL48          (*((uword volatile *) 0xF0004C10))

// Message Object 49 Data Register Low
#define CAN_MODATAL49          (*((uword volatile *) 0xF0004C30))

// Message Object 5 Data Register Low
#define CAN_MODATAL5           (*((uword volatile *) 0xF00046B0))

// Message Object 50 Data Register Low
#define CAN_MODATAL50          (*((uword volatile *) 0xF0004C50))

// Message Object 51 Data Register Low
#define CAN_MODATAL51          (*((uword volatile *) 0xF0004C70))

// Message Object 52 Data Register Low
#define CAN_MODATAL52          (*((uword volatile *) 0xF0004C90))

// Message Object 53 Data Register Low
#define CAN_MODATAL53          (*((uword volatile *) 0xF0004CB0))

// Message Object 54 Data Register Low
#define CAN_MODATAL54          (*((uword volatile *) 0xF0004CD0))

// Message Object 55 Data Register Low
#define CAN_MODATAL55          (*((uword volatile *) 0xF0004CF0))

// Message Object 56 Data Register Low
#define CAN_MODATAL56          (*((uword volatile *) 0xF0004D10))

// Message Object 57 Data Register Low
#define CAN_MODATAL57          (*((uword volatile *) 0xF0004D30))

// Message Object 58 Data Register Low
#define CAN_MODATAL58          (*((uword volatile *) 0xF0004D50))

// Message Object 59 Data Register Low
#define CAN_MODATAL59          (*((uword volatile *) 0xF0004D70))

// Message Object 6 Data Register Low
#define CAN_MODATAL6           (*((uword volatile *) 0xF00046D0))

// Message Object 60 Data Register Low
#define CAN_MODATAL60          (*((uword volatile *) 0xF0004D90))

// Message Object 61 Data Register Low
#define CAN_MODATAL61          (*((uword volatile *) 0xF0004DB0))

// Message Object 62 Data Register Low
#define CAN_MODATAL62          (*((uword volatile *) 0xF0004DD0))

// Message Object 63 Data Register Low
#define CAN_MODATAL63          (*((uword volatile *) 0xF0004DF0))

// Message Object 64 Data Register Low
#define CAN_MODATAL64          (*((uword volatile *) 0xF0004E10))

// Message Object 65 Data Register Low
#define CAN_MODATAL65          (*((uword volatile *) 0xF0004E30))

// Message Object 66 Data Register Low
#define CAN_MODATAL66          (*((uword volatile *) 0xF0004E50))

// Message Object 67 Data Register Low
#define CAN_MODATAL67          (*((uword volatile *) 0xF0004E70))

// Message Object 68 Data Register Low
#define CAN_MODATAL68          (*((uword volatile *) 0xF0004E90))

// Message Object 69 Data Register Low
#define CAN_MODATAL69          (*((uword volatile *) 0xF0004EB0))

// Message Object 7 Data Register Low
#define CAN_MODATAL7           (*((uword volatile *) 0xF00046F0))

// Message Object 70 Data Register Low
#define CAN_MODATAL70          (*((uword volatile *) 0xF0004ED0))

// Message Object 71 Data Register Low
#define CAN_MODATAL71          (*((uword volatile *) 0xF0004EF0))

// Message Object 72 Data Register Low
#define CAN_MODATAL72          (*((uword volatile *) 0xF0004F10))

// Message Object 73 Data Register Low
#define CAN_MODATAL73          (*((uword volatile *) 0xF0004F30))

// Message Object 74 Data Register Low
#define CAN_MODATAL74          (*((uword volatile *) 0xF0004F50))

// Message Object 75 Data Register Low
#define CAN_MODATAL75          (*((uword volatile *) 0xF0004F70))

// Message Object 76 Data Register Low
#define CAN_MODATAL76          (*((uword volatile *) 0xF0004F90))

// Message Object 77 Data Register Low
#define CAN_MODATAL77          (*((uword volatile *) 0xF0004FB0))

// Message Object 78 Data Register Low
#define CAN_MODATAL78          (*((uword volatile *) 0xF0004FD0))

// Message Object 79 Data Register Low
#define CAN_MODATAL79          (*((uword volatile *) 0xF0004FF0))

// Message Object 8 Data Register Low
#define CAN_MODATAL8           (*((uword volatile *) 0xF0004710))

// Message Object 80 Data Register Low
#define CAN_MODATAL80          (*((uword volatile *) 0xF0005010))

// Message Object 81 Data Register Low
#define CAN_MODATAL81          (*((uword volatile *) 0xF0005030))

// Message Object 82 Data Register Low
#define CAN_MODATAL82          (*((uword volatile *) 0xF0005050))

// Message Object 83 Data Register Low
#define CAN_MODATAL83          (*((uword volatile *) 0xF0005070))

// Message Object 84 Data Register Low
#define CAN_MODATAL84          (*((uword volatile *) 0xF0005090))

// Message Object 85 Data Register Low
#define CAN_MODATAL85          (*((uword volatile *) 0xF00050B0))

// Message Object 86 Data Register Low
#define CAN_MODATAL86          (*((uword volatile *) 0xF00050D0))

// Message Object 87 Data Register Low
#define CAN_MODATAL87          (*((uword volatile *) 0xF00050F0))

// Message Object 88 Data Register Low
#define CAN_MODATAL88          (*((uword volatile *) 0xF0005110))

// Message Object 89 Data Register Low
#define CAN_MODATAL89          (*((uword volatile *) 0xF0005130))

// Message Object 9 Data Register Low
#define CAN_MODATAL9           (*((uword volatile *) 0xF0004730))

// Message Object 90 Data Register Low
#define CAN_MODATAL90          (*((uword volatile *) 0xF0005150))

// Message Object 91 Data Register Low
#define CAN_MODATAL91          (*((uword volatile *) 0xF0005170))

// Message Object 92 Data Register Low
#define CAN_MODATAL92          (*((uword volatile *) 0xF0005190))

// Message Object 93 Data Register Low
#define CAN_MODATAL93          (*((uword volatile *) 0xF00051B0))

// Message Object 94 Data Register Low
#define CAN_MODATAL94          (*((uword volatile *) 0xF00051D0))

// Message Object 95 Data Register Low
#define CAN_MODATAL95          (*((uword volatile *) 0xF00051F0))

// Message Object 96 Data Register Low
#define CAN_MODATAL96          (*((uword volatile *) 0xF0005210))

// Message Object 97 Data Register Low
#define CAN_MODATAL97          (*((uword volatile *) 0xF0005230))

// Message Object 98 Data Register Low
#define CAN_MODATAL98          (*((uword volatile *) 0xF0005250))

// Message Object 99 Data Register Low
#define CAN_MODATAL99          (*((uword volatile *) 0xF0005270))

// Message Object 0 Function Control Register
#define CAN_MOFCR0             (*((uword volatile *) 0xF0004600))
#define CAN_MOFCR0_DATC          0x00000800
#define CAN_MOFCR0_DLCC          0x00000400
#define CAN_MOFCR0_FRREN         0x00100000
#define CAN_MOFCR0_GDFS          0x00000100
#define CAN_MOFCR0_IDC           0x00000200
#define CAN_MOFCR0_OVIE          0x00040000
#define CAN_MOFCR0_RMM           0x00200000
#define CAN_MOFCR0_RXIE          0x00010000
#define CAN_MOFCR0_SDT           0x00400000
#define CAN_MOFCR0_STT           0x00800000
#define CAN_MOFCR0_TXIE          0x00020000

// Message Object 1 Function Control Register
#define CAN_MOFCR1             (*((uword volatile *) 0xF0004620))
#define CAN_MOFCR1_DATC          0x00000800
#define CAN_MOFCR1_DLCC          0x00000400
#define CAN_MOFCR1_FRREN         0x00100000
#define CAN_MOFCR1_GDFS          0x00000100
#define CAN_MOFCR1_IDC           0x00000200
#define CAN_MOFCR1_OVIE          0x00040000
#define CAN_MOFCR1_RMM           0x00200000
#define CAN_MOFCR1_RXIE          0x00010000
#define CAN_MOFCR1_SDT           0x00400000
#define CAN_MOFCR1_STT           0x00800000
#define CAN_MOFCR1_TXIE          0x00020000

// Message Object 10 Function Control Register
#define CAN_MOFCR10            (*((uword volatile *) 0xF0004740))
#define CAN_MOFCR10_0            0x00080000
#define CAN_MOFCR10_DATC         0x00000800
#define CAN_MOFCR10_DLCC         0x00000400
#define CAN_MOFCR10_FRREN        0x00100000
#define CAN_MOFCR10_GDFS         0x00000100
#define CAN_MOFCR10_IDC          0x00000200
#define CAN_MOFCR10_OVIE         0x00040000
#define CAN_MOFCR10_RMM          0x00200000
#define CAN_MOFCR10_RXIE         0x00010000
#define CAN_MOFCR10_SDT          0x00400000
#define CAN_MOFCR10_STT          0x00800000
#define CAN_MOFCR10_TXIE         0x00020000

// Message Object 100 Function Control Register
#define CAN_MOFCR100           (*((uword volatile *) 0xF0005280))
#define CAN_MOFCR100_0           0x00080000
#define CAN_MOFCR100_DATC        0x00000800
#define CAN_MOFCR100_DLCC        0x00000400
#define CAN_MOFCR100_FRREN       0x00100000
#define CAN_MOFCR100_GDFS        0x00000100
#define CAN_MOFCR100_IDC         0x00000200
#define CAN_MOFCR100_OVIE        0x00040000
#define CAN_MOFCR100_RMM         0x00200000
#define CAN_MOFCR100_RXIE        0x00010000
#define CAN_MOFCR100_SDT         0x00400000
#define CAN_MOFCR100_STT         0x00800000
#define CAN_MOFCR100_TXIE        0x00020000

// Message Object 101 Function Control Register
#define CAN_MOFCR101           (*((uword volatile *) 0xF00052A0))
#define CAN_MOFCR101_0           0x00080000
#define CAN_MOFCR101_DATC        0x00000800
#define CAN_MOFCR101_DLCC        0x00000400
#define CAN_MOFCR101_FRREN       0x00100000
#define CAN_MOFCR101_GDFS        0x00000100
#define CAN_MOFCR101_IDC         0x00000200
#define CAN_MOFCR101_OVIE        0x00040000
#define CAN_MOFCR101_RMM         0x00200000
#define CAN_MOFCR101_RXIE        0x00010000
#define CAN_MOFCR101_SDT         0x00400000
#define CAN_MOFCR101_STT         0x00800000
#define CAN_MOFCR101_TXIE        0x00020000

// Message Object 102 Function Control Register
#define CAN_MOFCR102           (*((uword volatile *) 0xF00052C0))
#define CAN_MOFCR102_0           0x00080000
#define CAN_MOFCR102_DATC        0x00000800
#define CAN_MOFCR102_DLCC        0x00000400
#define CAN_MOFCR102_FRREN       0x00100000
#define CAN_MOFCR102_GDFS        0x00000100
#define CAN_MOFCR102_IDC         0x00000200
#define CAN_MOFCR102_OVIE        0x00040000
#define CAN_MOFCR102_RMM         0x00200000
#define CAN_MOFCR102_RXIE        0x00010000
#define CAN_MOFCR102_SDT         0x00400000
#define CAN_MOFCR102_STT         0x00800000
#define CAN_MOFCR102_TXIE        0x00020000

// Message Object 103 Function Control Register
#define CAN_MOFCR103           (*((uword volatile *) 0xF00052E0))
#define CAN_MOFCR103_0           0x00080000
#define CAN_MOFCR103_DATC        0x00000800
#define CAN_MOFCR103_DLCC        0x00000400
#define CAN_MOFCR103_FRREN       0x00100000
#define CAN_MOFCR103_GDFS        0x00000100
#define CAN_MOFCR103_IDC         0x00000200
#define CAN_MOFCR103_OVIE        0x00040000
#define CAN_MOFCR103_RMM         0x00200000
#define CAN_MOFCR103_RXIE        0x00010000
#define CAN_MOFCR103_SDT         0x00400000
#define CAN_MOFCR103_STT         0x00800000
#define CAN_MOFCR103_TXIE        0x00020000

// Message Object 104 Function Control Register
#define CAN_MOFCR104           (*((uword volatile *) 0xF0005300))
#define CAN_MOFCR104_0           0x00080000
#define CAN_MOFCR104_DATC        0x00000800
#define CAN_MOFCR104_DLCC        0x00000400
#define CAN_MOFCR104_FRREN       0x00100000
#define CAN_MOFCR104_GDFS        0x00000100
#define CAN_MOFCR104_IDC         0x00000200
#define CAN_MOFCR104_OVIE        0x00040000
#define CAN_MOFCR104_RMM         0x00200000
#define CAN_MOFCR104_RXIE        0x00010000
#define CAN_MOFCR104_SDT         0x00400000
#define CAN_MOFCR104_STT         0x00800000
#define CAN_MOFCR104_TXIE        0x00020000

// Message Object 105 Function Control Register
#define CAN_MOFCR105           (*((uword volatile *) 0xF0005320))
#define CAN_MOFCR105_0           0x00080000
#define CAN_MOFCR105_DATC        0x00000800
#define CAN_MOFCR105_DLCC        0x00000400
#define CAN_MOFCR105_FRREN       0x00100000
#define CAN_MOFCR105_GDFS        0x00000100
#define CAN_MOFCR105_IDC         0x00000200
#define CAN_MOFCR105_OVIE        0x00040000
#define CAN_MOFCR105_RMM         0x00200000
#define CAN_MOFCR105_RXIE        0x00010000
#define CAN_MOFCR105_SDT         0x00400000
#define CAN_MOFCR105_STT         0x00800000
#define CAN_MOFCR105_TXIE        0x00020000

// Message Object 106 Function Control Register
#define CAN_MOFCR106           (*((uword volatile *) 0xF0005340))
#define CAN_MOFCR106_0           0x00080000
#define CAN_MOFCR106_DATC        0x00000800
#define CAN_MOFCR106_DLCC        0x00000400
#define CAN_MOFCR106_FRREN       0x00100000
#define CAN_MOFCR106_GDFS        0x00000100
#define CAN_MOFCR106_IDC         0x00000200
#define CAN_MOFCR106_OVIE        0x00040000
#define CAN_MOFCR106_RMM         0x00200000
#define CAN_MOFCR106_RXIE        0x00010000
#define CAN_MOFCR106_SDT         0x00400000
#define CAN_MOFCR106_STT         0x00800000
#define CAN_MOFCR106_TXIE        0x00020000

// Message Object 107 Function Control Register
#define CAN_MOFCR107           (*((uword volatile *) 0xF0005360))
#define CAN_MOFCR107_0           0x00080000
#define CAN_MOFCR107_DATC        0x00000800
#define CAN_MOFCR107_DLCC        0x00000400
#define CAN_MOFCR107_FRREN       0x00100000
#define CAN_MOFCR107_GDFS        0x00000100
#define CAN_MOFCR107_IDC         0x00000200
#define CAN_MOFCR107_OVIE        0x00040000
#define CAN_MOFCR107_RMM         0x00200000
#define CAN_MOFCR107_RXIE        0x00010000
#define CAN_MOFCR107_SDT         0x00400000
#define CAN_MOFCR107_STT         0x00800000
#define CAN_MOFCR107_TXIE        0x00020000

// Message Object 108 Function Control Register
#define CAN_MOFCR108           (*((uword volatile *) 0xF0005380))
#define CAN_MOFCR108_0           0x00080000
#define CAN_MOFCR108_DATC        0x00000800
#define CAN_MOFCR108_DLCC        0x00000400
#define CAN_MOFCR108_FRREN       0x00100000
#define CAN_MOFCR108_GDFS        0x00000100
#define CAN_MOFCR108_IDC         0x00000200
#define CAN_MOFCR108_OVIE        0x00040000
#define CAN_MOFCR108_RMM         0x00200000
#define CAN_MOFCR108_RXIE        0x00010000
#define CAN_MOFCR108_SDT         0x00400000
#define CAN_MOFCR108_STT         0x00800000
#define CAN_MOFCR108_TXIE        0x00020000

// Message Object 109 Function Control Register
#define CAN_MOFCR109           (*((uword volatile *) 0xF00053A0))
#define CAN_MOFCR109_0           0x00080000
#define CAN_MOFCR109_DATC        0x00000800
#define CAN_MOFCR109_DLCC        0x00000400
#define CAN_MOFCR109_FRREN       0x00100000
#define CAN_MOFCR109_GDFS        0x00000100
#define CAN_MOFCR109_IDC         0x00000200
#define CAN_MOFCR109_OVIE        0x00040000
#define CAN_MOFCR109_RMM         0x00200000
#define CAN_MOFCR109_RXIE        0x00010000
#define CAN_MOFCR109_SDT         0x00400000
#define CAN_MOFCR109_STT         0x00800000
#define CAN_MOFCR109_TXIE        0x00020000

// Message Object 11 Function Control Register
#define CAN_MOFCR11            (*((uword volatile *) 0xF0004760))
#define CAN_MOFCR11_0            0x00080000
#define CAN_MOFCR11_DATC         0x00000800
#define CAN_MOFCR11_DLCC         0x00000400
#define CAN_MOFCR11_FRREN        0x00100000
#define CAN_MOFCR11_GDFS         0x00000100
#define CAN_MOFCR11_IDC          0x00000200
#define CAN_MOFCR11_OVIE         0x00040000
#define CAN_MOFCR11_RMM          0x00200000
#define CAN_MOFCR11_RXIE         0x00010000
#define CAN_MOFCR11_SDT          0x00400000
#define CAN_MOFCR11_STT          0x00800000
#define CAN_MOFCR11_TXIE         0x00020000

// Message Object 110 Function Control Register
#define CAN_MOFCR110           (*((uword volatile *) 0xF00053C0))
#define CAN_MOFCR110_0           0x00080000
#define CAN_MOFCR110_DATC        0x00000800
#define CAN_MOFCR110_DLCC        0x00000400
#define CAN_MOFCR110_FRREN       0x00100000
#define CAN_MOFCR110_GDFS        0x00000100
#define CAN_MOFCR110_IDC         0x00000200
#define CAN_MOFCR110_OVIE        0x00040000
#define CAN_MOFCR110_RMM         0x00200000
#define CAN_MOFCR110_RXIE        0x00010000
#define CAN_MOFCR110_SDT         0x00400000
#define CAN_MOFCR110_STT         0x00800000
#define CAN_MOFCR110_TXIE        0x00020000

// Message Object 111 Function Control Register
#define CAN_MOFCR111           (*((uword volatile *) 0xF00053E0))
#define CAN_MOFCR111_0           0x00080000
#define CAN_MOFCR111_DATC        0x00000800
#define CAN_MOFCR111_DLCC        0x00000400
#define CAN_MOFCR111_FRREN       0x00100000
#define CAN_MOFCR111_GDFS        0x00000100
#define CAN_MOFCR111_IDC         0x00000200
#define CAN_MOFCR111_OVIE        0x00040000
#define CAN_MOFCR111_RMM         0x00200000
#define CAN_MOFCR111_RXIE        0x00010000
#define CAN_MOFCR111_SDT         0x00400000
#define CAN_MOFCR111_STT         0x00800000
#define CAN_MOFCR111_TXIE        0x00020000

// Message Object 112 Function Control Register
#define CAN_MOFCR112           (*((uword volatile *) 0xF0005400))
#define CAN_MOFCR112_0           0x00080000
#define CAN_MOFCR112_DATC        0x00000800
#define CAN_MOFCR112_DLCC        0x00000400
#define CAN_MOFCR112_FRREN       0x00100000
#define CAN_MOFCR112_GDFS        0x00000100
#define CAN_MOFCR112_IDC         0x00000200
#define CAN_MOFCR112_OVIE        0x00040000
#define CAN_MOFCR112_RMM         0x00200000
#define CAN_MOFCR112_RXIE        0x00010000
#define CAN_MOFCR112_SDT         0x00400000
#define CAN_MOFCR112_STT         0x00800000
#define CAN_MOFCR112_TXIE        0x00020000

// Message Object 113 Function Control Register
#define CAN_MOFCR113           (*((uword volatile *) 0xF0005420))
#define CAN_MOFCR113_0           0x00080000
#define CAN_MOFCR113_DATC        0x00000800
#define CAN_MOFCR113_DLCC        0x00000400
#define CAN_MOFCR113_FRREN       0x00100000
#define CAN_MOFCR113_GDFS        0x00000100
#define CAN_MOFCR113_IDC         0x00000200
#define CAN_MOFCR113_OVIE        0x00040000
#define CAN_MOFCR113_RMM         0x00200000
#define CAN_MOFCR113_RXIE        0x00010000
#define CAN_MOFCR113_SDT         0x00400000
#define CAN_MOFCR113_STT         0x00800000
#define CAN_MOFCR113_TXIE        0x00020000

// Message Object 114 Function Control Register
#define CAN_MOFCR114           (*((uword volatile *) 0xF0005440))
#define CAN_MOFCR114_0           0x00080000
#define CAN_MOFCR114_DATC        0x00000800
#define CAN_MOFCR114_DLCC        0x00000400
#define CAN_MOFCR114_FRREN       0x00100000
#define CAN_MOFCR114_GDFS        0x00000100
#define CAN_MOFCR114_IDC         0x00000200
#define CAN_MOFCR114_OVIE        0x00040000
#define CAN_MOFCR114_RMM         0x00200000
#define CAN_MOFCR114_RXIE        0x00010000
#define CAN_MOFCR114_SDT         0x00400000
#define CAN_MOFCR114_STT         0x00800000
#define CAN_MOFCR114_TXIE        0x00020000

// Message Object 115 Function Control Register
#define CAN_MOFCR115           (*((uword volatile *) 0xF0005460))
#define CAN_MOFCR115_0           0x00080000
#define CAN_MOFCR115_DATC        0x00000800
#define CAN_MOFCR115_DLCC        0x00000400
#define CAN_MOFCR115_FRREN       0x00100000
#define CAN_MOFCR115_GDFS        0x00000100
#define CAN_MOFCR115_IDC         0x00000200
#define CAN_MOFCR115_OVIE        0x00040000
#define CAN_MOFCR115_RMM         0x00200000
#define CAN_MOFCR115_RXIE        0x00010000
#define CAN_MOFCR115_SDT         0x00400000
#define CAN_MOFCR115_STT         0x00800000
#define CAN_MOFCR115_TXIE        0x00020000

// Message Object 116 Function Control Register
#define CAN_MOFCR116           (*((uword volatile *) 0xF0005480))
#define CAN_MOFCR116_0           0x00080000
#define CAN_MOFCR116_DATC        0x00000800
#define CAN_MOFCR116_DLCC        0x00000400
#define CAN_MOFCR116_FRREN       0x00100000
#define CAN_MOFCR116_GDFS        0x00000100
#define CAN_MOFCR116_IDC         0x00000200
#define CAN_MOFCR116_OVIE        0x00040000
#define CAN_MOFCR116_RMM         0x00200000
#define CAN_MOFCR116_RXIE        0x00010000
#define CAN_MOFCR116_SDT         0x00400000
#define CAN_MOFCR116_STT         0x00800000
#define CAN_MOFCR116_TXIE        0x00020000

// Message Object 117 Function Control Register
#define CAN_MOFCR117           (*((uword volatile *) 0xF00054A0))
#define CAN_MOFCR117_0           0x00080000
#define CAN_MOFCR117_DATC        0x00000800
#define CAN_MOFCR117_DLCC        0x00000400
#define CAN_MOFCR117_FRREN       0x00100000
#define CAN_MOFCR117_GDFS        0x00000100
#define CAN_MOFCR117_IDC         0x00000200
#define CAN_MOFCR117_OVIE        0x00040000
#define CAN_MOFCR117_RMM         0x00200000
#define CAN_MOFCR117_RXIE        0x00010000
#define CAN_MOFCR117_SDT         0x00400000
#define CAN_MOFCR117_STT         0x00800000
#define CAN_MOFCR117_TXIE        0x00020000

// Message Object 118 Function Control Register
#define CAN_MOFCR118           (*((uword volatile *) 0xF00054C0))
#define CAN_MOFCR118_0           0x00080000
#define CAN_MOFCR118_DATC        0x00000800
#define CAN_MOFCR118_DLCC        0x00000400
#define CAN_MOFCR118_FRREN       0x00100000
#define CAN_MOFCR118_GDFS        0x00000100
#define CAN_MOFCR118_IDC         0x00000200
#define CAN_MOFCR118_OVIE        0x00040000
#define CAN_MOFCR118_RMM         0x00200000
#define CAN_MOFCR118_RXIE        0x00010000
#define CAN_MOFCR118_SDT         0x00400000
#define CAN_MOFCR118_STT         0x00800000
#define CAN_MOFCR118_TXIE        0x00020000

// Message Object 119 Function Control Register
#define CAN_MOFCR119           (*((uword volatile *) 0xF00054E0))
#define CAN_MOFCR119_0           0x00080000
#define CAN_MOFCR119_DATC        0x00000800
#define CAN_MOFCR119_DLCC        0x00000400
#define CAN_MOFCR119_FRREN       0x00100000
#define CAN_MOFCR119_GDFS        0x00000100
#define CAN_MOFCR119_IDC         0x00000200
#define CAN_MOFCR119_OVIE        0x00040000
#define CAN_MOFCR119_RMM         0x00200000
#define CAN_MOFCR119_RXIE        0x00010000
#define CAN_MOFCR119_SDT         0x00400000
#define CAN_MOFCR119_STT         0x00800000
#define CAN_MOFCR119_TXIE        0x00020000

// Message Object 12 Function Control Register
#define CAN_MOFCR12            (*((uword volatile *) 0xF0004780))
#define CAN_MOFCR12_0            0x00080000
#define CAN_MOFCR12_DATC         0x00000800
#define CAN_MOFCR12_DLCC         0x00000400
#define CAN_MOFCR12_FRREN        0x00100000
#define CAN_MOFCR12_GDFS         0x00000100
#define CAN_MOFCR12_IDC          0x00000200
#define CAN_MOFCR12_OVIE         0x00040000
#define CAN_MOFCR12_RMM          0x00200000
#define CAN_MOFCR12_RXIE         0x00010000
#define CAN_MOFCR12_SDT          0x00400000
#define CAN_MOFCR12_STT          0x00800000
#define CAN_MOFCR12_TXIE         0x00020000

// Message Object 120 Function Control Register
#define CAN_MOFCR120           (*((uword volatile *) 0xF0005500))
#define CAN_MOFCR120_0           0x00080000
#define CAN_MOFCR120_DATC        0x00000800
#define CAN_MOFCR120_DLCC        0x00000400
#define CAN_MOFCR120_FRREN       0x00100000
#define CAN_MOFCR120_GDFS        0x00000100
#define CAN_MOFCR120_IDC         0x00000200
#define CAN_MOFCR120_OVIE        0x00040000
#define CAN_MOFCR120_RMM         0x00200000
#define CAN_MOFCR120_RXIE        0x00010000
#define CAN_MOFCR120_SDT         0x00400000
#define CAN_MOFCR120_STT         0x00800000
#define CAN_MOFCR120_TXIE        0x00020000

// Message Object 121 Function Control Register
#define CAN_MOFCR121           (*((uword volatile *) 0xF0005520))
#define CAN_MOFCR121_0           0x00080000
#define CAN_MOFCR121_DATC        0x00000800
#define CAN_MOFCR121_DLCC        0x00000400
#define CAN_MOFCR121_FRREN       0x00100000
#define CAN_MOFCR121_GDFS        0x00000100
#define CAN_MOFCR121_IDC         0x00000200
#define CAN_MOFCR121_OVIE        0x00040000
#define CAN_MOFCR121_RMM         0x00200000
#define CAN_MOFCR121_RXIE        0x00010000
#define CAN_MOFCR121_SDT         0x00400000
#define CAN_MOFCR121_STT         0x00800000
#define CAN_MOFCR121_TXIE        0x00020000

// Message Object 122 Function Control Register
#define CAN_MOFCR122           (*((uword volatile *) 0xF0005540))
#define CAN_MOFCR122_0           0x00080000
#define CAN_MOFCR122_DATC        0x00000800
#define CAN_MOFCR122_DLCC        0x00000400
#define CAN_MOFCR122_FRREN       0x00100000
#define CAN_MOFCR122_GDFS        0x00000100
#define CAN_MOFCR122_IDC         0x00000200
#define CAN_MOFCR122_OVIE        0x00040000
#define CAN_MOFCR122_RMM         0x00200000
#define CAN_MOFCR122_RXIE        0x00010000
#define CAN_MOFCR122_SDT         0x00400000
#define CAN_MOFCR122_STT         0x00800000
#define CAN_MOFCR122_TXIE        0x00020000

// Message Object 123 Function Control Register
#define CAN_MOFCR123           (*((uword volatile *) 0xF0005560))
#define CAN_MOFCR123_0           0x00080000
#define CAN_MOFCR123_DATC        0x00000800
#define CAN_MOFCR123_DLCC        0x00000400
#define CAN_MOFCR123_FRREN       0x00100000
#define CAN_MOFCR123_GDFS        0x00000100
#define CAN_MOFCR123_IDC         0x00000200
#define CAN_MOFCR123_OVIE        0x00040000
#define CAN_MOFCR123_RMM         0x00200000
#define CAN_MOFCR123_RXIE        0x00010000
#define CAN_MOFCR123_SDT         0x00400000
#define CAN_MOFCR123_STT         0x00800000
#define CAN_MOFCR123_TXIE        0x00020000

// Message Object 124 Function Control Register
#define CAN_MOFCR124           (*((uword volatile *) 0xF0005580))
#define CAN_MOFCR124_0           0x00080000
#define CAN_MOFCR124_DATC        0x00000800
#define CAN_MOFCR124_DLCC        0x00000400
#define CAN_MOFCR124_FRREN       0x00100000
#define CAN_MOFCR124_GDFS        0x00000100
#define CAN_MOFCR124_IDC         0x00000200
#define CAN_MOFCR124_OVIE        0x00040000
#define CAN_MOFCR124_RMM         0x00200000
#define CAN_MOFCR124_RXIE        0x00010000
#define CAN_MOFCR124_SDT         0x00400000
#define CAN_MOFCR124_STT         0x00800000
#define CAN_MOFCR124_TXIE        0x00020000

// Message Object 125 Function Control Register
#define CAN_MOFCR125           (*((uword volatile *) 0xF00055A0))
#define CAN_MOFCR125_0           0x00080000
#define CAN_MOFCR125_DATC        0x00000800
#define CAN_MOFCR125_DLCC        0x00000400
#define CAN_MOFCR125_FRREN       0x00100000
#define CAN_MOFCR125_GDFS        0x00000100
#define CAN_MOFCR125_IDC         0x00000200
#define CAN_MOFCR125_OVIE        0x00040000
#define CAN_MOFCR125_RMM         0x00200000
#define CAN_MOFCR125_RXIE        0x00010000
#define CAN_MOFCR125_SDT         0x00400000
#define CAN_MOFCR125_STT         0x00800000
#define CAN_MOFCR125_TXIE        0x00020000

// Message Object 126 Function Control Register
#define CAN_MOFCR126           (*((uword volatile *) 0xF00055C0))
#define CAN_MOFCR126_0           0x00080000
#define CAN_MOFCR126_DATC        0x00000800
#define CAN_MOFCR126_DLCC        0x00000400
#define CAN_MOFCR126_FRREN       0x00100000
#define CAN_MOFCR126_GDFS        0x00000100
#define CAN_MOFCR126_IDC         0x00000200
#define CAN_MOFCR126_OVIE        0x00040000
#define CAN_MOFCR126_RMM         0x00200000
#define CAN_MOFCR126_RXIE        0x00010000
#define CAN_MOFCR126_SDT         0x00400000
#define CAN_MOFCR126_STT         0x00800000
#define CAN_MOFCR126_TXIE        0x00020000

// Message Object 127 Function Control Register
#define CAN_MOFCR127           (*((uword volatile *) 0xF00055E0))
#define CAN_MOFCR127_0           0x00080000
#define CAN_MOFCR127_DATC        0x00000800
#define CAN_MOFCR127_DLCC        0x00000400
#define CAN_MOFCR127_FRREN       0x00100000
#define CAN_MOFCR127_GDFS        0x00000100
#define CAN_MOFCR127_IDC         0x00000200
#define CAN_MOFCR127_OVIE        0x00040000
#define CAN_MOFCR127_RMM         0x00200000
#define CAN_MOFCR127_RXIE        0x00010000
#define CAN_MOFCR127_SDT         0x00400000
#define CAN_MOFCR127_STT         0x00800000
#define CAN_MOFCR127_TXIE        0x00020000

// Message Object 13 Function Control Register
#define CAN_MOFCR13            (*((uword volatile *) 0xF00047A0))
#define CAN_MOFCR13_0            0x00080000
#define CAN_MOFCR13_DATC         0x00000800
#define CAN_MOFCR13_DLCC         0x00000400
#define CAN_MOFCR13_FRREN        0x00100000
#define CAN_MOFCR13_GDFS         0x00000100
#define CAN_MOFCR13_IDC          0x00000200
#define CAN_MOFCR13_OVIE         0x00040000
#define CAN_MOFCR13_RMM          0x00200000
#define CAN_MOFCR13_RXIE         0x00010000
#define CAN_MOFCR13_SDT          0x00400000
#define CAN_MOFCR13_STT          0x00800000
#define CAN_MOFCR13_TXIE         0x00020000

// Message Object 14 Function Control Register
#define CAN_MOFCR14            (*((uword volatile *) 0xF00047C0))
#define CAN_MOFCR14_0            0x00080000
#define CAN_MOFCR14_DATC         0x00000800
#define CAN_MOFCR14_DLCC         0x00000400
#define CAN_MOFCR14_FRREN        0x00100000
#define CAN_MOFCR14_GDFS         0x00000100
#define CAN_MOFCR14_IDC          0x00000200
#define CAN_MOFCR14_OVIE         0x00040000
#define CAN_MOFCR14_RMM          0x00200000
#define CAN_MOFCR14_RXIE         0x00010000
#define CAN_MOFCR14_SDT          0x00400000
#define CAN_MOFCR14_STT          0x00800000
#define CAN_MOFCR14_TXIE         0x00020000

// Message Object 15 Function Control Register
#define CAN_MOFCR15            (*((uword volatile *) 0xF00047E0))
#define CAN_MOFCR15_0            0x00080000
#define CAN_MOFCR15_DATC         0x00000800
#define CAN_MOFCR15_DLCC         0x00000400
#define CAN_MOFCR15_FRREN        0x00100000
#define CAN_MOFCR15_GDFS         0x00000100
#define CAN_MOFCR15_IDC          0x00000200
#define CAN_MOFCR15_OVIE         0x00040000
#define CAN_MOFCR15_RMM          0x00200000
#define CAN_MOFCR15_RXIE         0x00010000
#define CAN_MOFCR15_SDT          0x00400000
#define CAN_MOFCR15_STT          0x00800000
#define CAN_MOFCR15_TXIE         0x00020000

// Message Object 16 Function Control Register
#define CAN_MOFCR16            (*((uword volatile *) 0xF0004800))
#define CAN_MOFCR16_0            0x00080000
#define CAN_MOFCR16_DATC         0x00000800
#define CAN_MOFCR16_DLCC         0x00000400
#define CAN_MOFCR16_FRREN        0x00100000
#define CAN_MOFCR16_GDFS         0x00000100
#define CAN_MOFCR16_IDC          0x00000200
#define CAN_MOFCR16_OVIE         0x00040000
#define CAN_MOFCR16_RMM          0x00200000
#define CAN_MOFCR16_RXIE         0x00010000
#define CAN_MOFCR16_SDT          0x00400000
#define CAN_MOFCR16_STT          0x00800000
#define CAN_MOFCR16_TXIE         0x00020000

// Message Object 17 Function Control Register
#define CAN_MOFCR17            (*((uword volatile *) 0xF0004820))
#define CAN_MOFCR17_0            0x00080000
#define CAN_MOFCR17_DATC         0x00000800
#define CAN_MOFCR17_DLCC         0x00000400
#define CAN_MOFCR17_FRREN        0x00100000
#define CAN_MOFCR17_GDFS         0x00000100
#define CAN_MOFCR17_IDC          0x00000200
#define CAN_MOFCR17_OVIE         0x00040000
#define CAN_MOFCR17_RMM          0x00200000
#define CAN_MOFCR17_RXIE         0x00010000
#define CAN_MOFCR17_SDT          0x00400000
#define CAN_MOFCR17_STT          0x00800000
#define CAN_MOFCR17_TXIE         0x00020000

// Message Object 18 Function Control Register
#define CAN_MOFCR18            (*((uword volatile *) 0xF0004840))
#define CAN_MOFCR18_0            0x00080000
#define CAN_MOFCR18_DATC         0x00000800
#define CAN_MOFCR18_DLCC         0x00000400
#define CAN_MOFCR18_FRREN        0x00100000
#define CAN_MOFCR18_GDFS         0x00000100
#define CAN_MOFCR18_IDC          0x00000200
#define CAN_MOFCR18_OVIE         0x00040000
#define CAN_MOFCR18_RMM          0x00200000
#define CAN_MOFCR18_RXIE         0x00010000
#define CAN_MOFCR18_SDT          0x00400000
#define CAN_MOFCR18_STT          0x00800000
#define CAN_MOFCR18_TXIE         0x00020000

// Message Object 19 Function Control Register
#define CAN_MOFCR19            (*((uword volatile *) 0xF0004860))
#define CAN_MOFCR19_0            0x00080000
#define CAN_MOFCR19_DATC         0x00000800
#define CAN_MOFCR19_DLCC         0x00000400
#define CAN_MOFCR19_FRREN        0x00100000
#define CAN_MOFCR19_GDFS         0x00000100
#define CAN_MOFCR19_IDC          0x00000200
#define CAN_MOFCR19_OVIE         0x00040000
#define CAN_MOFCR19_RMM          0x00200000
#define CAN_MOFCR19_RXIE         0x00010000
#define CAN_MOFCR19_SDT          0x00400000
#define CAN_MOFCR19_STT          0x00800000
#define CAN_MOFCR19_TXIE         0x00020000

// Message Object 2 Function Control Register
#define CAN_MOFCR2             (*((uword volatile *) 0xF0004640))
#define CAN_MOFCR2_DATC          0x00000800
#define CAN_MOFCR2_DLCC          0x00000400
#define CAN_MOFCR2_FRREN         0x00100000
#define CAN_MOFCR2_GDFS          0x00000100
#define CAN_MOFCR2_IDC           0x00000200
#define CAN_MOFCR2_OVIE          0x00040000
#define CAN_MOFCR2_RMM           0x00200000
#define CAN_MOFCR2_RXIE          0x00010000
#define CAN_MOFCR2_SDT           0x00400000
#define CAN_MOFCR2_STT           0x00800000
#define CAN_MOFCR2_TXIE          0x00020000

// Message Object 20 Function Control Register
#define CAN_MOFCR20            (*((uword volatile *) 0xF0004880))
#define CAN_MOFCR20_0            0x00080000
#define CAN_MOFCR20_DATC         0x00000800
#define CAN_MOFCR20_DLCC         0x00000400
#define CAN_MOFCR20_FRREN        0x00100000
#define CAN_MOFCR20_GDFS         0x00000100
#define CAN_MOFCR20_IDC          0x00000200
#define CAN_MOFCR20_OVIE         0x00040000
#define CAN_MOFCR20_RMM          0x00200000
#define CAN_MOFCR20_RXIE         0x00010000
#define CAN_MOFCR20_SDT          0x00400000
#define CAN_MOFCR20_STT          0x00800000
#define CAN_MOFCR20_TXIE         0x00020000

// Message Object 21 Function Control Register
#define CAN_MOFCR21            (*((uword volatile *) 0xF00048A0))
#define CAN_MOFCR21_0            0x00080000
#define CAN_MOFCR21_DATC         0x00000800
#define CAN_MOFCR21_DLCC         0x00000400
#define CAN_MOFCR21_FRREN        0x00100000
#define CAN_MOFCR21_GDFS         0x00000100
#define CAN_MOFCR21_IDC          0x00000200
#define CAN_MOFCR21_OVIE         0x00040000
#define CAN_MOFCR21_RMM          0x00200000
#define CAN_MOFCR21_RXIE         0x00010000
#define CAN_MOFCR21_SDT          0x00400000
#define CAN_MOFCR21_STT          0x00800000
#define CAN_MOFCR21_TXIE         0x00020000

// Message Object 22 Function Control Register
#define CAN_MOFCR22            (*((uword volatile *) 0xF00048C0))
#define CAN_MOFCR22_0            0x00080000
#define CAN_MOFCR22_DATC         0x00000800
#define CAN_MOFCR22_DLCC         0x00000400
#define CAN_MOFCR22_FRREN        0x00100000
#define CAN_MOFCR22_GDFS         0x00000100
#define CAN_MOFCR22_IDC          0x00000200
#define CAN_MOFCR22_OVIE         0x00040000
#define CAN_MOFCR22_RMM          0x00200000
#define CAN_MOFCR22_RXIE         0x00010000
#define CAN_MOFCR22_SDT          0x00400000
#define CAN_MOFCR22_STT          0x00800000
#define CAN_MOFCR22_TXIE         0x00020000

// Message Object 23 Function Control Register
#define CAN_MOFCR23            (*((uword volatile *) 0xF00048E0))
#define CAN_MOFCR23_0            0x00080000
#define CAN_MOFCR23_DATC         0x00000800
#define CAN_MOFCR23_DLCC         0x00000400
#define CAN_MOFCR23_FRREN        0x00100000
#define CAN_MOFCR23_GDFS         0x00000100
#define CAN_MOFCR23_IDC          0x00000200
#define CAN_MOFCR23_OVIE         0x00040000
#define CAN_MOFCR23_RMM          0x00200000
#define CAN_MOFCR23_RXIE         0x00010000
#define CAN_MOFCR23_SDT          0x00400000
#define CAN_MOFCR23_STT          0x00800000
#define CAN_MOFCR23_TXIE         0x00020000

// Message Object 24 Function Control Register
#define CAN_MOFCR24            (*((uword volatile *) 0xF0004900))
#define CAN_MOFCR24_0            0x00080000
#define CAN_MOFCR24_DATC         0x00000800
#define CAN_MOFCR24_DLCC         0x00000400
#define CAN_MOFCR24_FRREN        0x00100000
#define CAN_MOFCR24_GDFS         0x00000100
#define CAN_MOFCR24_IDC          0x00000200
#define CAN_MOFCR24_OVIE         0x00040000
#define CAN_MOFCR24_RMM          0x00200000
#define CAN_MOFCR24_RXIE         0x00010000
#define CAN_MOFCR24_SDT          0x00400000
#define CAN_MOFCR24_STT          0x00800000
#define CAN_MOFCR24_TXIE         0x00020000

// Message Object 25 Function Control Register
#define CAN_MOFCR25            (*((uword volatile *) 0xF0004920))
#define CAN_MOFCR25_0            0x00080000
#define CAN_MOFCR25_DATC         0x00000800
#define CAN_MOFCR25_DLCC         0x00000400
#define CAN_MOFCR25_FRREN        0x00100000
#define CAN_MOFCR25_GDFS         0x00000100
#define CAN_MOFCR25_IDC          0x00000200
#define CAN_MOFCR25_OVIE         0x00040000
#define CAN_MOFCR25_RMM          0x00200000
#define CAN_MOFCR25_RXIE         0x00010000
#define CAN_MOFCR25_SDT          0x00400000
#define CAN_MOFCR25_STT          0x00800000
#define CAN_MOFCR25_TXIE         0x00020000

// Message Object 26 Function Control Register
#define CAN_MOFCR26            (*((uword volatile *) 0xF0004940))
#define CAN_MOFCR26_0            0x00080000
#define CAN_MOFCR26_DATC         0x00000800
#define CAN_MOFCR26_DLCC         0x00000400
#define CAN_MOFCR26_FRREN        0x00100000
#define CAN_MOFCR26_GDFS         0x00000100
#define CAN_MOFCR26_IDC          0x00000200
#define CAN_MOFCR26_OVIE         0x00040000
#define CAN_MOFCR26_RMM          0x00200000
#define CAN_MOFCR26_RXIE         0x00010000
#define CAN_MOFCR26_SDT          0x00400000
#define CAN_MOFCR26_STT          0x00800000
#define CAN_MOFCR26_TXIE         0x00020000

// Message Object 27 Function Control Register
#define CAN_MOFCR27            (*((uword volatile *) 0xF0004960))
#define CAN_MOFCR27_0            0x00080000
#define CAN_MOFCR27_DATC         0x00000800
#define CAN_MOFCR27_DLCC         0x00000400
#define CAN_MOFCR27_FRREN        0x00100000
#define CAN_MOFCR27_GDFS         0x00000100
#define CAN_MOFCR27_IDC          0x00000200
#define CAN_MOFCR27_OVIE         0x00040000
#define CAN_MOFCR27_RMM          0x00200000
#define CAN_MOFCR27_RXIE         0x00010000
#define CAN_MOFCR27_SDT          0x00400000
#define CAN_MOFCR27_STT          0x00800000
#define CAN_MOFCR27_TXIE         0x00020000

// Message Object 28 Function Control Register
#define CAN_MOFCR28            (*((uword volatile *) 0xF0004980))
#define CAN_MOFCR28_0            0x00080000
#define CAN_MOFCR28_DATC         0x00000800
#define CAN_MOFCR28_DLCC         0x00000400
#define CAN_MOFCR28_FRREN        0x00100000
#define CAN_MOFCR28_GDFS         0x00000100
#define CAN_MOFCR28_IDC          0x00000200
#define CAN_MOFCR28_OVIE         0x00040000
#define CAN_MOFCR28_RMM          0x00200000
#define CAN_MOFCR28_RXIE         0x00010000
#define CAN_MOFCR28_SDT          0x00400000
#define CAN_MOFCR28_STT          0x00800000
#define CAN_MOFCR28_TXIE         0x00020000

// Message Object 29 Function Control Register
#define CAN_MOFCR29            (*((uword volatile *) 0xF00049A0))
#define CAN_MOFCR29_0            0x00080000
#define CAN_MOFCR29_DATC         0x00000800
#define CAN_MOFCR29_DLCC         0x00000400
#define CAN_MOFCR29_FRREN        0x00100000
#define CAN_MOFCR29_GDFS         0x00000100
#define CAN_MOFCR29_IDC          0x00000200
#define CAN_MOFCR29_OVIE         0x00040000
#define CAN_MOFCR29_RMM          0x00200000
#define CAN_MOFCR29_RXIE         0x00010000
#define CAN_MOFCR29_SDT          0x00400000
#define CAN_MOFCR29_STT          0x00800000
#define CAN_MOFCR29_TXIE         0x00020000

// Message Object 3 Function Control Register
#define CAN_MOFCR3             (*((uword volatile *) 0xF0004660))
#define CAN_MOFCR3_DATC          0x00000800
#define CAN_MOFCR3_DLCC          0x00000400
#define CAN_MOFCR3_FRREN         0x00100000
#define CAN_MOFCR3_GDFS          0x00000100
#define CAN_MOFCR3_IDC           0x00000200
#define CAN_MOFCR3_OVIE          0x00040000
#define CAN_MOFCR3_RMM           0x00200000
#define CAN_MOFCR3_RXIE          0x00010000
#define CAN_MOFCR3_SDT           0x00400000
#define CAN_MOFCR3_STT           0x00800000
#define CAN_MOFCR3_TXIE          0x00020000

// Message Object 30 Function Control Register
#define CAN_MOFCR30            (*((uword volatile *) 0xF00049C0))
#define CAN_MOFCR30_0            0x00080000
#define CAN_MOFCR30_DATC         0x00000800
#define CAN_MOFCR30_DLCC         0x00000400
#define CAN_MOFCR30_FRREN        0x00100000
#define CAN_MOFCR30_GDFS         0x00000100
#define CAN_MOFCR30_IDC          0x00000200
#define CAN_MOFCR30_OVIE         0x00040000
#define CAN_MOFCR30_RMM          0x00200000
#define CAN_MOFCR30_RXIE         0x00010000
#define CAN_MOFCR30_SDT          0x00400000
#define CAN_MOFCR30_STT          0x00800000
#define CAN_MOFCR30_TXIE         0x00020000

// Message Object 31 Function Control Register
#define CAN_MOFCR31            (*((uword volatile *) 0xF00049E0))
#define CAN_MOFCR31_0            0x00080000
#define CAN_MOFCR31_DATC         0x00000800
#define CAN_MOFCR31_DLCC         0x00000400
#define CAN_MOFCR31_FRREN        0x00100000
#define CAN_MOFCR31_GDFS         0x00000100
#define CAN_MOFCR31_IDC          0x00000200
#define CAN_MOFCR31_OVIE         0x00040000
#define CAN_MOFCR31_RMM          0x00200000
#define CAN_MOFCR31_RXIE         0x00010000
#define CAN_MOFCR31_SDT          0x00400000
#define CAN_MOFCR31_STT          0x00800000
#define CAN_MOFCR31_TXIE         0x00020000

// Message Object 32 Function Control Register
#define CAN_MOFCR32            (*((uword volatile *) 0xF0004A00))
#define CAN_MOFCR32_0            0x00080000
#define CAN_MOFCR32_DATC         0x00000800
#define CAN_MOFCR32_DLCC         0x00000400
#define CAN_MOFCR32_FRREN        0x00100000
#define CAN_MOFCR32_GDFS         0x00000100
#define CAN_MOFCR32_IDC          0x00000200
#define CAN_MOFCR32_OVIE         0x00040000
#define CAN_MOFCR32_RMM          0x00200000
#define CAN_MOFCR32_RXIE         0x00010000
#define CAN_MOFCR32_SDT          0x00400000
#define CAN_MOFCR32_STT          0x00800000
#define CAN_MOFCR32_TXIE         0x00020000

// Message Object 33 Function Control Register
#define CAN_MOFCR33            (*((uword volatile *) 0xF0004A20))
#define CAN_MOFCR33_0            0x00080000
#define CAN_MOFCR33_DATC         0x00000800
#define CAN_MOFCR33_DLCC         0x00000400
#define CAN_MOFCR33_FRREN        0x00100000
#define CAN_MOFCR33_GDFS         0x00000100
#define CAN_MOFCR33_IDC          0x00000200
#define CAN_MOFCR33_OVIE         0x00040000
#define CAN_MOFCR33_RMM          0x00200000
#define CAN_MOFCR33_RXIE         0x00010000
#define CAN_MOFCR33_SDT          0x00400000
#define CAN_MOFCR33_STT          0x00800000
#define CAN_MOFCR33_TXIE         0x00020000

// Message Object 34 Function Control Register
#define CAN_MOFCR34            (*((uword volatile *) 0xF0004A40))
#define CAN_MOFCR34_0            0x00080000
#define CAN_MOFCR34_DATC         0x00000800
#define CAN_MOFCR34_DLCC         0x00000400
#define CAN_MOFCR34_FRREN        0x00100000
#define CAN_MOFCR34_GDFS         0x00000100
#define CAN_MOFCR34_IDC          0x00000200
#define CAN_MOFCR34_OVIE         0x00040000
#define CAN_MOFCR34_RMM          0x00200000
#define CAN_MOFCR34_RXIE         0x00010000
#define CAN_MOFCR34_SDT          0x00400000
#define CAN_MOFCR34_STT          0x00800000
#define CAN_MOFCR34_TXIE         0x00020000

// Message Object 35 Function Control Register
#define CAN_MOFCR35            (*((uword volatile *) 0xF0004A60))
#define CAN_MOFCR35_0            0x00080000
#define CAN_MOFCR35_DATC         0x00000800
#define CAN_MOFCR35_DLCC         0x00000400
#define CAN_MOFCR35_FRREN        0x00100000
#define CAN_MOFCR35_GDFS         0x00000100
#define CAN_MOFCR35_IDC          0x00000200
#define CAN_MOFCR35_OVIE         0x00040000
#define CAN_MOFCR35_RMM          0x00200000
#define CAN_MOFCR35_RXIE         0x00010000
#define CAN_MOFCR35_SDT          0x00400000
#define CAN_MOFCR35_STT          0x00800000
#define CAN_MOFCR35_TXIE         0x00020000

// Message Object 36 Function Control Register
#define CAN_MOFCR36            (*((uword volatile *) 0xF0004A80))
#define CAN_MOFCR36_0            0x00080000
#define CAN_MOFCR36_DATC         0x00000800
#define CAN_MOFCR36_DLCC         0x00000400
#define CAN_MOFCR36_FRREN        0x00100000
#define CAN_MOFCR36_GDFS         0x00000100
#define CAN_MOFCR36_IDC          0x00000200
#define CAN_MOFCR36_OVIE         0x00040000
#define CAN_MOFCR36_RMM          0x00200000
#define CAN_MOFCR36_RXIE         0x00010000
#define CAN_MOFCR36_SDT          0x00400000
#define CAN_MOFCR36_STT          0x00800000
#define CAN_MOFCR36_TXIE         0x00020000

// Message Object 37 Function Control Register
#define CAN_MOFCR37            (*((uword volatile *) 0xF0004AA0))
#define CAN_MOFCR37_0            0x00080000
#define CAN_MOFCR37_DATC         0x00000800
#define CAN_MOFCR37_DLCC         0x00000400
#define CAN_MOFCR37_FRREN        0x00100000
#define CAN_MOFCR37_GDFS         0x00000100
#define CAN_MOFCR37_IDC          0x00000200
#define CAN_MOFCR37_OVIE         0x00040000
#define CAN_MOFCR37_RMM          0x00200000
#define CAN_MOFCR37_RXIE         0x00010000
#define CAN_MOFCR37_SDT          0x00400000
#define CAN_MOFCR37_STT          0x00800000
#define CAN_MOFCR37_TXIE         0x00020000

// Message Object 38 Function Control Register
#define CAN_MOFCR38            (*((uword volatile *) 0xF0004AC0))
#define CAN_MOFCR38_0            0x00080000
#define CAN_MOFCR38_DATC         0x00000800
#define CAN_MOFCR38_DLCC         0x00000400
#define CAN_MOFCR38_FRREN        0x00100000
#define CAN_MOFCR38_GDFS         0x00000100
#define CAN_MOFCR38_IDC          0x00000200
#define CAN_MOFCR38_OVIE         0x00040000
#define CAN_MOFCR38_RMM          0x00200000
#define CAN_MOFCR38_RXIE         0x00010000
#define CAN_MOFCR38_SDT          0x00400000
#define CAN_MOFCR38_STT          0x00800000
#define CAN_MOFCR38_TXIE         0x00020000

// Message Object 39 Function Control Register
#define CAN_MOFCR39            (*((uword volatile *) 0xF0004AE0))
#define CAN_MOFCR39_0            0x00080000
#define CAN_MOFCR39_DATC         0x00000800
#define CAN_MOFCR39_DLCC         0x00000400
#define CAN_MOFCR39_FRREN        0x00100000
#define CAN_MOFCR39_GDFS         0x00000100
#define CAN_MOFCR39_IDC          0x00000200
#define CAN_MOFCR39_OVIE         0x00040000
#define CAN_MOFCR39_RMM          0x00200000
#define CAN_MOFCR39_RXIE         0x00010000
#define CAN_MOFCR39_SDT          0x00400000
#define CAN_MOFCR39_STT          0x00800000
#define CAN_MOFCR39_TXIE         0x00020000

// Message Object 4 Function Control Register
#define CAN_MOFCR4             (*((uword volatile *) 0xF0004680))
#define CAN_MOFCR4_DATC          0x00000800
#define CAN_MOFCR4_DLCC          0x00000400
#define CAN_MOFCR4_FRREN         0x00100000
#define CAN_MOFCR4_GDFS          0x00000100
#define CAN_MOFCR4_IDC           0x00000200
#define CAN_MOFCR4_OVIE          0x00040000
#define CAN_MOFCR4_RMM           0x00200000
#define CAN_MOFCR4_RXIE          0x00010000
#define CAN_MOFCR4_SDT           0x00400000
#define CAN_MOFCR4_STT           0x00800000
#define CAN_MOFCR4_TXIE          0x00020000

// Message Object 40 Function Control Register
#define CAN_MOFCR40            (*((uword volatile *) 0xF0004B00))
#define CAN_MOFCR40_0            0x00080000
#define CAN_MOFCR40_DATC         0x00000800
#define CAN_MOFCR40_DLCC         0x00000400
#define CAN_MOFCR40_FRREN        0x00100000
#define CAN_MOFCR40_GDFS         0x00000100
#define CAN_MOFCR40_IDC          0x00000200
#define CAN_MOFCR40_OVIE         0x00040000
#define CAN_MOFCR40_RMM          0x00200000
#define CAN_MOFCR40_RXIE         0x00010000
#define CAN_MOFCR40_SDT          0x00400000
#define CAN_MOFCR40_STT          0x00800000
#define CAN_MOFCR40_TXIE         0x00020000

// Message Object 41 Function Control Register
#define CAN_MOFCR41            (*((uword volatile *) 0xF0004B20))
#define CAN_MOFCR41_0            0x00080000
#define CAN_MOFCR41_DATC         0x00000800
#define CAN_MOFCR41_DLCC         0x00000400
#define CAN_MOFCR41_FRREN        0x00100000
#define CAN_MOFCR41_GDFS         0x00000100
#define CAN_MOFCR41_IDC          0x00000200
#define CAN_MOFCR41_OVIE         0x00040000
#define CAN_MOFCR41_RMM          0x00200000
#define CAN_MOFCR41_RXIE         0x00010000
#define CAN_MOFCR41_SDT          0x00400000
#define CAN_MOFCR41_STT          0x00800000
#define CAN_MOFCR41_TXIE         0x00020000

// Message Object 42 Function Control Register
#define CAN_MOFCR42            (*((uword volatile *) 0xF0004B40))
#define CAN_MOFCR42_0            0x00080000
#define CAN_MOFCR42_DATC         0x00000800
#define CAN_MOFCR42_DLCC         0x00000400
#define CAN_MOFCR42_FRREN        0x00100000
#define CAN_MOFCR42_GDFS         0x00000100
#define CAN_MOFCR42_IDC          0x00000200
#define CAN_MOFCR42_OVIE         0x00040000
#define CAN_MOFCR42_RMM          0x00200000
#define CAN_MOFCR42_RXIE         0x00010000
#define CAN_MOFCR42_SDT          0x00400000
#define CAN_MOFCR42_STT          0x00800000
#define CAN_MOFCR42_TXIE         0x00020000

// Message Object 43 Function Control Register
#define CAN_MOFCR43            (*((uword volatile *) 0xF0004B60))
#define CAN_MOFCR43_0            0x00080000
#define CAN_MOFCR43_DATC         0x00000800
#define CAN_MOFCR43_DLCC         0x00000400
#define CAN_MOFCR43_FRREN        0x00100000
#define CAN_MOFCR43_GDFS         0x00000100
#define CAN_MOFCR43_IDC          0x00000200
#define CAN_MOFCR43_OVIE         0x00040000
#define CAN_MOFCR43_RMM          0x00200000
#define CAN_MOFCR43_RXIE         0x00010000
#define CAN_MOFCR43_SDT          0x00400000
#define CAN_MOFCR43_STT          0x00800000
#define CAN_MOFCR43_TXIE         0x00020000

// Message Object 44 Function Control Register
#define CAN_MOFCR44            (*((uword volatile *) 0xF0004B80))
#define CAN_MOFCR44_0            0x00080000
#define CAN_MOFCR44_DATC         0x00000800
#define CAN_MOFCR44_DLCC         0x00000400
#define CAN_MOFCR44_FRREN        0x00100000
#define CAN_MOFCR44_GDFS         0x00000100
#define CAN_MOFCR44_IDC          0x00000200
#define CAN_MOFCR44_OVIE         0x00040000
#define CAN_MOFCR44_RMM          0x00200000
#define CAN_MOFCR44_RXIE         0x00010000
#define CAN_MOFCR44_SDT          0x00400000
#define CAN_MOFCR44_STT          0x00800000
#define CAN_MOFCR44_TXIE         0x00020000

// Message Object 45 Function Control Register
#define CAN_MOFCR45            (*((uword volatile *) 0xF0004BA0))
#define CAN_MOFCR45_0            0x00080000
#define CAN_MOFCR45_DATC         0x00000800
#define CAN_MOFCR45_DLCC         0x00000400
#define CAN_MOFCR45_FRREN        0x00100000
#define CAN_MOFCR45_GDFS         0x00000100
#define CAN_MOFCR45_IDC          0x00000200
#define CAN_MOFCR45_OVIE         0x00040000
#define CAN_MOFCR45_RMM          0x00200000
#define CAN_MOFCR45_RXIE         0x00010000
#define CAN_MOFCR45_SDT          0x00400000
#define CAN_MOFCR45_STT          0x00800000
#define CAN_MOFCR45_TXIE         0x00020000

// Message Object 46 Function Control Register
#define CAN_MOFCR46            (*((uword volatile *) 0xF0004BC0))
#define CAN_MOFCR46_0            0x00080000
#define CAN_MOFCR46_DATC         0x00000800
#define CAN_MOFCR46_DLCC         0x00000400
#define CAN_MOFCR46_FRREN        0x00100000
#define CAN_MOFCR46_GDFS         0x00000100
#define CAN_MOFCR46_IDC          0x00000200
#define CAN_MOFCR46_OVIE         0x00040000
#define CAN_MOFCR46_RMM          0x00200000
#define CAN_MOFCR46_RXIE         0x00010000
#define CAN_MOFCR46_SDT          0x00400000
#define CAN_MOFCR46_STT          0x00800000
#define CAN_MOFCR46_TXIE         0x00020000

// Message Object 47 Function Control Register
#define CAN_MOFCR47            (*((uword volatile *) 0xF0004BE0))
#define CAN_MOFCR47_0            0x00080000
#define CAN_MOFCR47_DATC         0x00000800
#define CAN_MOFCR47_DLCC         0x00000400
#define CAN_MOFCR47_FRREN        0x00100000
#define CAN_MOFCR47_GDFS         0x00000100
#define CAN_MOFCR47_IDC          0x00000200
#define CAN_MOFCR47_OVIE         0x00040000
#define CAN_MOFCR47_RMM          0x00200000
#define CAN_MOFCR47_RXIE         0x00010000
#define CAN_MOFCR47_SDT          0x00400000
#define CAN_MOFCR47_STT          0x00800000
#define CAN_MOFCR47_TXIE         0x00020000

// Message Object 48 Function Control Register
#define CAN_MOFCR48            (*((uword volatile *) 0xF0004C00))
#define CAN_MOFCR48_0            0x00080000
#define CAN_MOFCR48_DATC         0x00000800
#define CAN_MOFCR48_DLCC         0x00000400
#define CAN_MOFCR48_FRREN        0x00100000
#define CAN_MOFCR48_GDFS         0x00000100
#define CAN_MOFCR48_IDC          0x00000200
#define CAN_MOFCR48_OVIE         0x00040000
#define CAN_MOFCR48_RMM          0x00200000
#define CAN_MOFCR48_RXIE         0x00010000
#define CAN_MOFCR48_SDT          0x00400000
#define CAN_MOFCR48_STT          0x00800000
#define CAN_MOFCR48_TXIE         0x00020000

// Message Object 49 Function Control Register
#define CAN_MOFCR49            (*((uword volatile *) 0xF0004C20))
#define CAN_MOFCR49_0            0x00080000
#define CAN_MOFCR49_DATC         0x00000800
#define CAN_MOFCR49_DLCC         0x00000400
#define CAN_MOFCR49_FRREN        0x00100000
#define CAN_MOFCR49_GDFS         0x00000100
#define CAN_MOFCR49_IDC          0x00000200
#define CAN_MOFCR49_OVIE         0x00040000
#define CAN_MOFCR49_RMM          0x00200000
#define CAN_MOFCR49_RXIE         0x00010000
#define CAN_MOFCR49_SDT          0x00400000
#define CAN_MOFCR49_STT          0x00800000
#define CAN_MOFCR49_TXIE         0x00020000

// Message Object 5 Function Control Register
#define CAN_MOFCR5             (*((uword volatile *) 0xF00046A0))
#define CAN_MOFCR5_DATC          0x00000800
#define CAN_MOFCR5_DLCC          0x00000400
#define CAN_MOFCR5_FRREN         0x00100000
#define CAN_MOFCR5_GDFS          0x00000100
#define CAN_MOFCR5_IDC           0x00000200
#define CAN_MOFCR5_OVIE          0x00040000
#define CAN_MOFCR5_RMM           0x00200000
#define CAN_MOFCR5_RXIE          0x00010000
#define CAN_MOFCR5_SDT           0x00400000
#define CAN_MOFCR5_STT           0x00800000
#define CAN_MOFCR5_TXIE          0x00020000

// Message Object 50 Function Control Register
#define CAN_MOFCR50            (*((uword volatile *) 0xF0004C40))
#define CAN_MOFCR50_0            0x00080000
#define CAN_MOFCR50_DATC         0x00000800
#define CAN_MOFCR50_DLCC         0x00000400
#define CAN_MOFCR50_FRREN        0x00100000
#define CAN_MOFCR50_GDFS         0x00000100
#define CAN_MOFCR50_IDC          0x00000200
#define CAN_MOFCR50_OVIE         0x00040000
#define CAN_MOFCR50_RMM          0x00200000
#define CAN_MOFCR50_RXIE         0x00010000
#define CAN_MOFCR50_SDT          0x00400000
#define CAN_MOFCR50_STT          0x00800000
#define CAN_MOFCR50_TXIE         0x00020000

// Message Object 51 Function Control Register
#define CAN_MOFCR51            (*((uword volatile *) 0xF0004C60))
#define CAN_MOFCR51_0            0x00080000
#define CAN_MOFCR51_DATC         0x00000800
#define CAN_MOFCR51_DLCC         0x00000400
#define CAN_MOFCR51_FRREN        0x00100000
#define CAN_MOFCR51_GDFS         0x00000100
#define CAN_MOFCR51_IDC          0x00000200
#define CAN_MOFCR51_OVIE         0x00040000
#define CAN_MOFCR51_RMM          0x00200000
#define CAN_MOFCR51_RXIE         0x00010000
#define CAN_MOFCR51_SDT          0x00400000
#define CAN_MOFCR51_STT          0x00800000
#define CAN_MOFCR51_TXIE         0x00020000

// Message Object 52 Function Control Register
#define CAN_MOFCR52            (*((uword volatile *) 0xF0004C80))
#define CAN_MOFCR52_0            0x00080000
#define CAN_MOFCR52_DATC         0x00000800
#define CAN_MOFCR52_DLCC         0x00000400
#define CAN_MOFCR52_FRREN        0x00100000
#define CAN_MOFCR52_GDFS         0x00000100
#define CAN_MOFCR52_IDC          0x00000200
#define CAN_MOFCR52_OVIE         0x00040000
#define CAN_MOFCR52_RMM          0x00200000
#define CAN_MOFCR52_RXIE         0x00010000
#define CAN_MOFCR52_SDT          0x00400000
#define CAN_MOFCR52_STT          0x00800000
#define CAN_MOFCR52_TXIE         0x00020000

// Message Object 53 Function Control Register
#define CAN_MOFCR53            (*((uword volatile *) 0xF0004CA0))
#define CAN_MOFCR53_0            0x00080000
#define CAN_MOFCR53_DATC         0x00000800
#define CAN_MOFCR53_DLCC         0x00000400
#define CAN_MOFCR53_FRREN        0x00100000
#define CAN_MOFCR53_GDFS         0x00000100
#define CAN_MOFCR53_IDC          0x00000200
#define CAN_MOFCR53_OVIE         0x00040000
#define CAN_MOFCR53_RMM          0x00200000
#define CAN_MOFCR53_RXIE         0x00010000
#define CAN_MOFCR53_SDT          0x00400000
#define CAN_MOFCR53_STT          0x00800000
#define CAN_MOFCR53_TXIE         0x00020000

// Message Object 54 Function Control Register
#define CAN_MOFCR54            (*((uword volatile *) 0xF0004CC0))
#define CAN_MOFCR54_0            0x00080000
#define CAN_MOFCR54_DATC         0x00000800
#define CAN_MOFCR54_DLCC         0x00000400
#define CAN_MOFCR54_FRREN        0x00100000
#define CAN_MOFCR54_GDFS         0x00000100
#define CAN_MOFCR54_IDC          0x00000200
#define CAN_MOFCR54_OVIE         0x00040000
#define CAN_MOFCR54_RMM          0x00200000
#define CAN_MOFCR54_RXIE         0x00010000
#define CAN_MOFCR54_SDT          0x00400000
#define CAN_MOFCR54_STT          0x00800000
#define CAN_MOFCR54_TXIE         0x00020000

// Message Object 55 Function Control Register
#define CAN_MOFCR55            (*((uword volatile *) 0xF0004CE0))
#define CAN_MOFCR55_0            0x00080000
#define CAN_MOFCR55_DATC         0x00000800
#define CAN_MOFCR55_DLCC         0x00000400
#define CAN_MOFCR55_FRREN        0x00100000
#define CAN_MOFCR55_GDFS         0x00000100
#define CAN_MOFCR55_IDC          0x00000200
#define CAN_MOFCR55_OVIE         0x00040000
#define CAN_MOFCR55_RMM          0x00200000
#define CAN_MOFCR55_RXIE         0x00010000
#define CAN_MOFCR55_SDT          0x00400000
#define CAN_MOFCR55_STT          0x00800000
#define CAN_MOFCR55_TXIE         0x00020000

// Message Object 56 Function Control Register
#define CAN_MOFCR56            (*((uword volatile *) 0xF0004D00))
#define CAN_MOFCR56_0            0x00080000
#define CAN_MOFCR56_DATC         0x00000800
#define CAN_MOFCR56_DLCC         0x00000400
#define CAN_MOFCR56_FRREN        0x00100000
#define CAN_MOFCR56_GDFS         0x00000100
#define CAN_MOFCR56_IDC          0x00000200
#define CAN_MOFCR56_OVIE         0x00040000
#define CAN_MOFCR56_RMM          0x00200000
#define CAN_MOFCR56_RXIE         0x00010000
#define CAN_MOFCR56_SDT          0x00400000
#define CAN_MOFCR56_STT          0x00800000
#define CAN_MOFCR56_TXIE         0x00020000

// Message Object 57 Function Control Register
#define CAN_MOFCR57            (*((uword volatile *) 0xF0004D20))
#define CAN_MOFCR57_0            0x00080000
#define CAN_MOFCR57_DATC         0x00000800
#define CAN_MOFCR57_DLCC         0x00000400
#define CAN_MOFCR57_FRREN        0x00100000
#define CAN_MOFCR57_GDFS         0x00000100
#define CAN_MOFCR57_IDC          0x00000200
#define CAN_MOFCR57_OVIE         0x00040000
#define CAN_MOFCR57_RMM          0x00200000
#define CAN_MOFCR57_RXIE         0x00010000
#define CAN_MOFCR57_SDT          0x00400000
#define CAN_MOFCR57_STT          0x00800000
#define CAN_MOFCR57_TXIE         0x00020000

// Message Object 58 Function Control Register
#define CAN_MOFCR58            (*((uword volatile *) 0xF0004D40))
#define CAN_MOFCR58_0            0x00080000
#define CAN_MOFCR58_DATC         0x00000800
#define CAN_MOFCR58_DLCC         0x00000400
#define CAN_MOFCR58_FRREN        0x00100000
#define CAN_MOFCR58_GDFS         0x00000100
#define CAN_MOFCR58_IDC          0x00000200
#define CAN_MOFCR58_OVIE         0x00040000
#define CAN_MOFCR58_RMM          0x00200000
#define CAN_MOFCR58_RXIE         0x00010000
#define CAN_MOFCR58_SDT          0x00400000
#define CAN_MOFCR58_STT          0x00800000
#define CAN_MOFCR58_TXIE         0x00020000

// Message Object 59 Function Control Register
#define CAN_MOFCR59            (*((uword volatile *) 0xF0004D60))
#define CAN_MOFCR59_0            0x00080000
#define CAN_MOFCR59_DATC         0x00000800
#define CAN_MOFCR59_DLCC         0x00000400
#define CAN_MOFCR59_FRREN        0x00100000
#define CAN_MOFCR59_GDFS         0x00000100
#define CAN_MOFCR59_IDC          0x00000200
#define CAN_MOFCR59_OVIE         0x00040000
#define CAN_MOFCR59_RMM          0x00200000
#define CAN_MOFCR59_RXIE         0x00010000
#define CAN_MOFCR59_SDT          0x00400000
#define CAN_MOFCR59_STT          0x00800000
#define CAN_MOFCR59_TXIE         0x00020000

// Message Object 6 Function Control Register
#define CAN_MOFCR6             (*((uword volatile *) 0xF00046C0))
#define CAN_MOFCR6_DATC          0x00000800
#define CAN_MOFCR6_DLCC          0x00000400
#define CAN_MOFCR6_FRREN         0x00100000
#define CAN_MOFCR6_GDFS          0x00000100
#define CAN_MOFCR6_IDC           0x00000200
#define CAN_MOFCR6_OVIE          0x00040000
#define CAN_MOFCR6_RMM           0x00200000
#define CAN_MOFCR6_RXIE          0x00010000
#define CAN_MOFCR6_SDT           0x00400000
#define CAN_MOFCR6_STT           0x00800000
#define CAN_MOFCR6_TXIE          0x00020000

// Message Object 60 Function Control Register
#define CAN_MOFCR60            (*((uword volatile *) 0xF0004D80))
#define CAN_MOFCR60_0            0x00080000
#define CAN_MOFCR60_DATC         0x00000800
#define CAN_MOFCR60_DLCC         0x00000400
#define CAN_MOFCR60_FRREN        0x00100000
#define CAN_MOFCR60_GDFS         0x00000100
#define CAN_MOFCR60_IDC          0x00000200
#define CAN_MOFCR60_OVIE         0x00040000
#define CAN_MOFCR60_RMM          0x00200000
#define CAN_MOFCR60_RXIE         0x00010000
#define CAN_MOFCR60_SDT          0x00400000
#define CAN_MOFCR60_STT          0x00800000
#define CAN_MOFCR60_TXIE         0x00020000

// Message Object 61 Function Control Register
#define CAN_MOFCR61            (*((uword volatile *) 0xF0004DA0))
#define CAN_MOFCR61_0            0x00080000
#define CAN_MOFCR61_DATC         0x00000800
#define CAN_MOFCR61_DLCC         0x00000400
#define CAN_MOFCR61_FRREN        0x00100000
#define CAN_MOFCR61_GDFS         0x00000100
#define CAN_MOFCR61_IDC          0x00000200
#define CAN_MOFCR61_OVIE         0x00040000
#define CAN_MOFCR61_RMM          0x00200000
#define CAN_MOFCR61_RXIE         0x00010000
#define CAN_MOFCR61_SDT          0x00400000
#define CAN_MOFCR61_STT          0x00800000
#define CAN_MOFCR61_TXIE         0x00020000

// Message Object 62 Function Control Register
#define CAN_MOFCR62            (*((uword volatile *) 0xF0004DC0))
#define CAN_MOFCR62_0            0x00080000
#define CAN_MOFCR62_DATC         0x00000800
#define CAN_MOFCR62_DLCC         0x00000400
#define CAN_MOFCR62_FRREN        0x00100000
#define CAN_MOFCR62_GDFS         0x00000100
#define CAN_MOFCR62_IDC          0x00000200
#define CAN_MOFCR62_OVIE         0x00040000
#define CAN_MOFCR62_RMM          0x00200000
#define CAN_MOFCR62_RXIE         0x00010000
#define CAN_MOFCR62_SDT          0x00400000
#define CAN_MOFCR62_STT          0x00800000
#define CAN_MOFCR62_TXIE         0x00020000

// Message Object 63 Function Control Register
#define CAN_MOFCR63            (*((uword volatile *) 0xF0004DE0))
#define CAN_MOFCR63_0            0x00080000
#define CAN_MOFCR63_DATC         0x00000800
#define CAN_MOFCR63_DLCC         0x00000400
#define CAN_MOFCR63_FRREN        0x00100000
#define CAN_MOFCR63_GDFS         0x00000100
#define CAN_MOFCR63_IDC          0x00000200
#define CAN_MOFCR63_OVIE         0x00040000
#define CAN_MOFCR63_RMM          0x00200000
#define CAN_MOFCR63_RXIE         0x00010000
#define CAN_MOFCR63_SDT          0x00400000
#define CAN_MOFCR63_STT          0x00800000
#define CAN_MOFCR63_TXIE         0x00020000

// Message Object 64 Function Control Register
#define CAN_MOFCR64            (*((uword volatile *) 0xF0004E00))
#define CAN_MOFCR64_0            0x00080000
#define CAN_MOFCR64_DATC         0x00000800
#define CAN_MOFCR64_DLCC         0x00000400
#define CAN_MOFCR64_FRREN        0x00100000
#define CAN_MOFCR64_GDFS         0x00000100
#define CAN_MOFCR64_IDC          0x00000200
#define CAN_MOFCR64_OVIE         0x00040000
#define CAN_MOFCR64_RMM          0x00200000
#define CAN_MOFCR64_RXIE         0x00010000
#define CAN_MOFCR64_SDT          0x00400000
#define CAN_MOFCR64_STT          0x00800000
#define CAN_MOFCR64_TXIE         0x00020000

// Message Object 65 Function Control Register
#define CAN_MOFCR65            (*((uword volatile *) 0xF0004E20))
#define CAN_MOFCR65_0            0x00080000
#define CAN_MOFCR65_DATC         0x00000800
#define CAN_MOFCR65_DLCC         0x00000400
#define CAN_MOFCR65_FRREN        0x00100000
#define CAN_MOFCR65_GDFS         0x00000100
#define CAN_MOFCR65_IDC          0x00000200
#define CAN_MOFCR65_OVIE         0x00040000
#define CAN_MOFCR65_RMM          0x00200000
#define CAN_MOFCR65_RXIE         0x00010000
#define CAN_MOFCR65_SDT          0x00400000
#define CAN_MOFCR65_STT          0x00800000
#define CAN_MOFCR65_TXIE         0x00020000

// Message Object 66 Function Control Register
#define CAN_MOFCR66            (*((uword volatile *) 0xF0004E40))
#define CAN_MOFCR66_0            0x00080000
#define CAN_MOFCR66_DATC         0x00000800
#define CAN_MOFCR66_DLCC         0x00000400
#define CAN_MOFCR66_FRREN        0x00100000
#define CAN_MOFCR66_GDFS         0x00000100
#define CAN_MOFCR66_IDC          0x00000200
#define CAN_MOFCR66_OVIE         0x00040000
#define CAN_MOFCR66_RMM          0x00200000
#define CAN_MOFCR66_RXIE         0x00010000
#define CAN_MOFCR66_SDT          0x00400000
#define CAN_MOFCR66_STT          0x00800000
#define CAN_MOFCR66_TXIE         0x00020000

// Message Object 67 Function Control Register
#define CAN_MOFCR67            (*((uword volatile *) 0xF0004E60))
#define CAN_MOFCR67_0            0x00080000
#define CAN_MOFCR67_DATC         0x00000800
#define CAN_MOFCR67_DLCC         0x00000400
#define CAN_MOFCR67_FRREN        0x00100000
#define CAN_MOFCR67_GDFS         0x00000100
#define CAN_MOFCR67_IDC          0x00000200
#define CAN_MOFCR67_OVIE         0x00040000
#define CAN_MOFCR67_RMM          0x00200000
#define CAN_MOFCR67_RXIE         0x00010000
#define CAN_MOFCR67_SDT          0x00400000
#define CAN_MOFCR67_STT          0x00800000
#define CAN_MOFCR67_TXIE         0x00020000

// Message Object 68 Function Control Register
#define CAN_MOFCR68            (*((uword volatile *) 0xF0004E80))
#define CAN_MOFCR68_0            0x00080000
#define CAN_MOFCR68_DATC         0x00000800
#define CAN_MOFCR68_DLCC         0x00000400
#define CAN_MOFCR68_FRREN        0x00100000
#define CAN_MOFCR68_GDFS         0x00000100
#define CAN_MOFCR68_IDC          0x00000200
#define CAN_MOFCR68_OVIE         0x00040000
#define CAN_MOFCR68_RMM          0x00200000
#define CAN_MOFCR68_RXIE         0x00010000
#define CAN_MOFCR68_SDT          0x00400000
#define CAN_MOFCR68_STT          0x00800000
#define CAN_MOFCR68_TXIE         0x00020000

// Message Object 69 Function Control Register
#define CAN_MOFCR69            (*((uword volatile *) 0xF0004EA0))
#define CAN_MOFCR69_0            0x00080000
#define CAN_MOFCR69_DATC         0x00000800
#define CAN_MOFCR69_DLCC         0x00000400
#define CAN_MOFCR69_FRREN        0x00100000
#define CAN_MOFCR69_GDFS         0x00000100
#define CAN_MOFCR69_IDC          0x00000200
#define CAN_MOFCR69_OVIE         0x00040000
#define CAN_MOFCR69_RMM          0x00200000
#define CAN_MOFCR69_RXIE         0x00010000
#define CAN_MOFCR69_SDT          0x00400000
#define CAN_MOFCR69_STT          0x00800000
#define CAN_MOFCR69_TXIE         0x00020000

// Message Object 7 Function Control Register
#define CAN_MOFCR7             (*((uword volatile *) 0xF00046E0))
#define CAN_MOFCR7_DATC          0x00000800
#define CAN_MOFCR7_DLCC          0x00000400
#define CAN_MOFCR7_FRREN         0x00100000
#define CAN_MOFCR7_GDFS          0x00000100
#define CAN_MOFCR7_IDC           0x00000200
#define CAN_MOFCR7_OVIE          0x00040000
#define CAN_MOFCR7_RMM           0x00200000
#define CAN_MOFCR7_RXIE          0x00010000
#define CAN_MOFCR7_SDT           0x00400000
#define CAN_MOFCR7_STT           0x00800000
#define CAN_MOFCR7_TXIE          0x00020000

// Message Object 70 Function Control Register
#define CAN_MOFCR70            (*((uword volatile *) 0xF0004EC0))
#define CAN_MOFCR70_0            0x00080000
#define CAN_MOFCR70_DATC         0x00000800
#define CAN_MOFCR70_DLCC         0x00000400
#define CAN_MOFCR70_FRREN        0x00100000
#define CAN_MOFCR70_GDFS         0x00000100
#define CAN_MOFCR70_IDC          0x00000200
#define CAN_MOFCR70_OVIE         0x00040000
#define CAN_MOFCR70_RMM          0x00200000
#define CAN_MOFCR70_RXIE         0x00010000
#define CAN_MOFCR70_SDT          0x00400000
#define CAN_MOFCR70_STT          0x00800000
#define CAN_MOFCR70_TXIE         0x00020000

// Message Object 71 Function Control Register
#define CAN_MOFCR71            (*((uword volatile *) 0xF0004EE0))
#define CAN_MOFCR71_0            0x00080000
#define CAN_MOFCR71_DATC         0x00000800
#define CAN_MOFCR71_DLCC         0x00000400
#define CAN_MOFCR71_FRREN        0x00100000
#define CAN_MOFCR71_GDFS         0x00000100
#define CAN_MOFCR71_IDC          0x00000200
#define CAN_MOFCR71_OVIE         0x00040000
#define CAN_MOFCR71_RMM          0x00200000
#define CAN_MOFCR71_RXIE         0x00010000
#define CAN_MOFCR71_SDT          0x00400000
#define CAN_MOFCR71_STT          0x00800000
#define CAN_MOFCR71_TXIE         0x00020000

// Message Object 72 Function Control Register
#define CAN_MOFCR72            (*((uword volatile *) 0xF0004F00))
#define CAN_MOFCR72_0            0x00080000
#define CAN_MOFCR72_DATC         0x00000800
#define CAN_MOFCR72_DLCC         0x00000400
#define CAN_MOFCR72_FRREN        0x00100000
#define CAN_MOFCR72_GDFS         0x00000100
#define CAN_MOFCR72_IDC          0x00000200
#define CAN_MOFCR72_OVIE         0x00040000
#define CAN_MOFCR72_RMM          0x00200000
#define CAN_MOFCR72_RXIE         0x00010000
#define CAN_MOFCR72_SDT          0x00400000
#define CAN_MOFCR72_STT          0x00800000
#define CAN_MOFCR72_TXIE         0x00020000

// Message Object 73 Function Control Register
#define CAN_MOFCR73            (*((uword volatile *) 0xF0004F20))
#define CAN_MOFCR73_0            0x00080000
#define CAN_MOFCR73_DATC         0x00000800
#define CAN_MOFCR73_DLCC         0x00000400
#define CAN_MOFCR73_FRREN        0x00100000
#define CAN_MOFCR73_GDFS         0x00000100
#define CAN_MOFCR73_IDC          0x00000200
#define CAN_MOFCR73_OVIE         0x00040000
#define CAN_MOFCR73_RMM          0x00200000
#define CAN_MOFCR73_RXIE         0x00010000
#define CAN_MOFCR73_SDT          0x00400000
#define CAN_MOFCR73_STT          0x00800000
#define CAN_MOFCR73_TXIE         0x00020000

// Message Object 74 Function Control Register
#define CAN_MOFCR74            (*((uword volatile *) 0xF0004F40))
#define CAN_MOFCR74_0            0x00080000
#define CAN_MOFCR74_DATC         0x00000800
#define CAN_MOFCR74_DLCC         0x00000400
#define CAN_MOFCR74_FRREN        0x00100000
#define CAN_MOFCR74_GDFS         0x00000100
#define CAN_MOFCR74_IDC          0x00000200
#define CAN_MOFCR74_OVIE         0x00040000
#define CAN_MOFCR74_RMM          0x00200000
#define CAN_MOFCR74_RXIE         0x00010000
#define CAN_MOFCR74_SDT          0x00400000
#define CAN_MOFCR74_STT          0x00800000
#define CAN_MOFCR74_TXIE         0x00020000

// Message Object 75 Function Control Register
#define CAN_MOFCR75            (*((uword volatile *) 0xF0004F60))
#define CAN_MOFCR75_0            0x00080000
#define CAN_MOFCR75_DATC         0x00000800
#define CAN_MOFCR75_DLCC         0x00000400
#define CAN_MOFCR75_FRREN        0x00100000
#define CAN_MOFCR75_GDFS         0x00000100
#define CAN_MOFCR75_IDC          0x00000200
#define CAN_MOFCR75_OVIE         0x00040000
#define CAN_MOFCR75_RMM          0x00200000
#define CAN_MOFCR75_RXIE         0x00010000
#define CAN_MOFCR75_SDT          0x00400000
#define CAN_MOFCR75_STT          0x00800000
#define CAN_MOFCR75_TXIE         0x00020000

// Message Object 76 Function Control Register
#define CAN_MOFCR76            (*((uword volatile *) 0xF0004F80))
#define CAN_MOFCR76_0            0x00080000
#define CAN_MOFCR76_DATC         0x00000800
#define CAN_MOFCR76_DLCC         0x00000400
#define CAN_MOFCR76_FRREN        0x00100000
#define CAN_MOFCR76_GDFS         0x00000100
#define CAN_MOFCR76_IDC          0x00000200
#define CAN_MOFCR76_OVIE         0x00040000
#define CAN_MOFCR76_RMM          0x00200000
#define CAN_MOFCR76_RXIE         0x00010000
#define CAN_MOFCR76_SDT          0x00400000
#define CAN_MOFCR76_STT          0x00800000
#define CAN_MOFCR76_TXIE         0x00020000

// Message Object 77 Function Control Register
#define CAN_MOFCR77            (*((uword volatile *) 0xF0004FA0))
#define CAN_MOFCR77_0            0x00080000
#define CAN_MOFCR77_DATC         0x00000800
#define CAN_MOFCR77_DLCC         0x00000400
#define CAN_MOFCR77_FRREN        0x00100000
#define CAN_MOFCR77_GDFS         0x00000100
#define CAN_MOFCR77_IDC          0x00000200
#define CAN_MOFCR77_OVIE         0x00040000
#define CAN_MOFCR77_RMM          0x00200000
#define CAN_MOFCR77_RXIE         0x00010000
#define CAN_MOFCR77_SDT          0x00400000
#define CAN_MOFCR77_STT          0x00800000
#define CAN_MOFCR77_TXIE         0x00020000

// Message Object 78 Function Control Register
#define CAN_MOFCR78            (*((uword volatile *) 0xF0004FC0))
#define CAN_MOFCR78_0            0x00080000
#define CAN_MOFCR78_DATC         0x00000800
#define CAN_MOFCR78_DLCC         0x00000400
#define CAN_MOFCR78_FRREN        0x00100000
#define CAN_MOFCR78_GDFS         0x00000100
#define CAN_MOFCR78_IDC          0x00000200
#define CAN_MOFCR78_OVIE         0x00040000
#define CAN_MOFCR78_RMM          0x00200000
#define CAN_MOFCR78_RXIE         0x00010000
#define CAN_MOFCR78_SDT          0x00400000
#define CAN_MOFCR78_STT          0x00800000
#define CAN_MOFCR78_TXIE         0x00020000

// Message Object 79 Function Control Register
#define CAN_MOFCR79            (*((uword volatile *) 0xF0004FE0))
#define CAN_MOFCR79_0            0x00080000
#define CAN_MOFCR79_DATC         0x00000800
#define CAN_MOFCR79_DLCC         0x00000400
#define CAN_MOFCR79_FRREN        0x00100000
#define CAN_MOFCR79_GDFS         0x00000100
#define CAN_MOFCR79_IDC          0x00000200
#define CAN_MOFCR79_OVIE         0x00040000
#define CAN_MOFCR79_RMM          0x00200000
#define CAN_MOFCR79_RXIE         0x00010000
#define CAN_MOFCR79_SDT          0x00400000
#define CAN_MOFCR79_STT          0x00800000
#define CAN_MOFCR79_TXIE         0x00020000

// Message Object 8 Function Control Register
#define CAN_MOFCR8             (*((uword volatile *) 0xF0004700))
#define CAN_MOFCR8_DATC          0x00000800
#define CAN_MOFCR8_DLCC          0x00000400
#define CAN_MOFCR8_FRREN         0x00100000
#define CAN_MOFCR8_GDFS          0x00000100
#define CAN_MOFCR8_IDC           0x00000200
#define CAN_MOFCR8_OVIE          0x00040000
#define CAN_MOFCR8_RMM           0x00200000
#define CAN_MOFCR8_RXIE          0x00010000
#define CAN_MOFCR8_SDT           0x00400000
#define CAN_MOFCR8_STT           0x00800000
#define CAN_MOFCR8_TXIE          0x00020000

// Message Object 80 Function Control Register
#define CAN_MOFCR80            (*((uword volatile *) 0xF0005000))
#define CAN_MOFCR80_0            0x00080000
#define CAN_MOFCR80_DATC         0x00000800
#define CAN_MOFCR80_DLCC         0x00000400
#define CAN_MOFCR80_FRREN        0x00100000
#define CAN_MOFCR80_GDFS         0x00000100
#define CAN_MOFCR80_IDC          0x00000200
#define CAN_MOFCR80_OVIE         0x00040000
#define CAN_MOFCR80_RMM          0x00200000
#define CAN_MOFCR80_RXIE         0x00010000
#define CAN_MOFCR80_SDT          0x00400000
#define CAN_MOFCR80_STT          0x00800000
#define CAN_MOFCR80_TXIE         0x00020000

// Message Object 81 Function Control Register
#define CAN_MOFCR81            (*((uword volatile *) 0xF0005020))
#define CAN_MOFCR81_0            0x00080000
#define CAN_MOFCR81_DATC         0x00000800
#define CAN_MOFCR81_DLCC         0x00000400
#define CAN_MOFCR81_FRREN        0x00100000
#define CAN_MOFCR81_GDFS         0x00000100
#define CAN_MOFCR81_IDC          0x00000200
#define CAN_MOFCR81_OVIE         0x00040000
#define CAN_MOFCR81_RMM          0x00200000
#define CAN_MOFCR81_RXIE         0x00010000
#define CAN_MOFCR81_SDT          0x00400000
#define CAN_MOFCR81_STT          0x00800000
#define CAN_MOFCR81_TXIE         0x00020000

// Message Object 82 Function Control Register
#define CAN_MOFCR82            (*((uword volatile *) 0xF0005040))
#define CAN_MOFCR82_0            0x00080000
#define CAN_MOFCR82_DATC         0x00000800
#define CAN_MOFCR82_DLCC         0x00000400
#define CAN_MOFCR82_FRREN        0x00100000
#define CAN_MOFCR82_GDFS         0x00000100
#define CAN_MOFCR82_IDC          0x00000200
#define CAN_MOFCR82_OVIE         0x00040000
#define CAN_MOFCR82_RMM          0x00200000
#define CAN_MOFCR82_RXIE         0x00010000
#define CAN_MOFCR82_SDT          0x00400000
#define CAN_MOFCR82_STT          0x00800000
#define CAN_MOFCR82_TXIE         0x00020000

// Message Object 83 Function Control Register
#define CAN_MOFCR83            (*((uword volatile *) 0xF0005060))
#define CAN_MOFCR83_0            0x00080000
#define CAN_MOFCR83_DATC         0x00000800
#define CAN_MOFCR83_DLCC         0x00000400
#define CAN_MOFCR83_FRREN        0x00100000
#define CAN_MOFCR83_GDFS         0x00000100
#define CAN_MOFCR83_IDC          0x00000200
#define CAN_MOFCR83_OVIE         0x00040000
#define CAN_MOFCR83_RMM          0x00200000
#define CAN_MOFCR83_RXIE         0x00010000
#define CAN_MOFCR83_SDT          0x00400000
#define CAN_MOFCR83_STT          0x00800000
#define CAN_MOFCR83_TXIE         0x00020000

// Message Object 84 Function Control Register
#define CAN_MOFCR84            (*((uword volatile *) 0xF0005080))
#define CAN_MOFCR84_0            0x00080000
#define CAN_MOFCR84_DATC         0x00000800
#define CAN_MOFCR84_DLCC         0x00000400
#define CAN_MOFCR84_FRREN        0x00100000
#define CAN_MOFCR84_GDFS         0x00000100
#define CAN_MOFCR84_IDC          0x00000200
#define CAN_MOFCR84_OVIE         0x00040000
#define CAN_MOFCR84_RMM          0x00200000
#define CAN_MOFCR84_RXIE         0x00010000
#define CAN_MOFCR84_SDT          0x00400000
#define CAN_MOFCR84_STT          0x00800000
#define CAN_MOFCR84_TXIE         0x00020000

// Message Object 85 Function Control Register
#define CAN_MOFCR85            (*((uword volatile *) 0xF00050A0))
#define CAN_MOFCR85_0            0x00080000
#define CAN_MOFCR85_DATC         0x00000800
#define CAN_MOFCR85_DLCC         0x00000400
#define CAN_MOFCR85_FRREN        0x00100000
#define CAN_MOFCR85_GDFS         0x00000100
#define CAN_MOFCR85_IDC          0x00000200
#define CAN_MOFCR85_OVIE         0x00040000
#define CAN_MOFCR85_RMM          0x00200000
#define CAN_MOFCR85_RXIE         0x00010000
#define CAN_MOFCR85_SDT          0x00400000
#define CAN_MOFCR85_STT          0x00800000
#define CAN_MOFCR85_TXIE         0x00020000

// Message Object 86 Function Control Register
#define CAN_MOFCR86            (*((uword volatile *) 0xF00050C0))
#define CAN_MOFCR86_0            0x00080000
#define CAN_MOFCR86_DATC         0x00000800
#define CAN_MOFCR86_DLCC         0x00000400
#define CAN_MOFCR86_FRREN        0x00100000
#define CAN_MOFCR86_GDFS         0x00000100
#define CAN_MOFCR86_IDC          0x00000200
#define CAN_MOFCR86_OVIE         0x00040000
#define CAN_MOFCR86_RMM          0x00200000
#define CAN_MOFCR86_RXIE         0x00010000
#define CAN_MOFCR86_SDT          0x00400000
#define CAN_MOFCR86_STT          0x00800000
#define CAN_MOFCR86_TXIE         0x00020000

// Message Object 87 Function Control Register
#define CAN_MOFCR87            (*((uword volatile *) 0xF00050E0))
#define CAN_MOFCR87_0            0x00080000
#define CAN_MOFCR87_DATC         0x00000800
#define CAN_MOFCR87_DLCC         0x00000400
#define CAN_MOFCR87_FRREN        0x00100000
#define CAN_MOFCR87_GDFS         0x00000100
#define CAN_MOFCR87_IDC          0x00000200
#define CAN_MOFCR87_OVIE         0x00040000
#define CAN_MOFCR87_RMM          0x00200000
#define CAN_MOFCR87_RXIE         0x00010000
#define CAN_MOFCR87_SDT          0x00400000
#define CAN_MOFCR87_STT          0x00800000
#define CAN_MOFCR87_TXIE         0x00020000

// Message Object 88 Function Control Register
#define CAN_MOFCR88            (*((uword volatile *) 0xF0005100))
#define CAN_MOFCR88_0            0x00080000
#define CAN_MOFCR88_DATC         0x00000800
#define CAN_MOFCR88_DLCC         0x00000400
#define CAN_MOFCR88_FRREN        0x00100000
#define CAN_MOFCR88_GDFS         0x00000100
#define CAN_MOFCR88_IDC          0x00000200
#define CAN_MOFCR88_OVIE         0x00040000
#define CAN_MOFCR88_RMM          0x00200000
#define CAN_MOFCR88_RXIE         0x00010000
#define CAN_MOFCR88_SDT          0x00400000
#define CAN_MOFCR88_STT          0x00800000
#define CAN_MOFCR88_TXIE         0x00020000

// Message Object 89 Function Control Register
#define CAN_MOFCR89            (*((uword volatile *) 0xF0005120))
#define CAN_MOFCR89_0            0x00080000
#define CAN_MOFCR89_DATC         0x00000800
#define CAN_MOFCR89_DLCC         0x00000400
#define CAN_MOFCR89_FRREN        0x00100000
#define CAN_MOFCR89_GDFS         0x00000100
#define CAN_MOFCR89_IDC          0x00000200
#define CAN_MOFCR89_OVIE         0x00040000
#define CAN_MOFCR89_RMM          0x00200000
#define CAN_MOFCR89_RXIE         0x00010000
#define CAN_MOFCR89_SDT          0x00400000
#define CAN_MOFCR89_STT          0x00800000
#define CAN_MOFCR89_TXIE         0x00020000

// Message Object 9 Function Control Register
#define CAN_MOFCR9             (*((uword volatile *) 0xF0004720))
#define CAN_MOFCR9_0             0x00080000
#define CAN_MOFCR9_DATC          0x00000800
#define CAN_MOFCR9_DLCC          0x00000400
#define CAN_MOFCR9_FRREN         0x00100000
#define CAN_MOFCR9_GDFS          0x00000100
#define CAN_MOFCR9_IDC           0x00000200
#define CAN_MOFCR9_OVIE          0x00040000
#define CAN_MOFCR9_RMM           0x00200000
#define CAN_MOFCR9_RXIE          0x00010000
#define CAN_MOFCR9_SDT           0x00400000
#define CAN_MOFCR9_STT           0x00800000
#define CAN_MOFCR9_TXIE          0x00020000

// Message Object 90 Function Control Register
#define CAN_MOFCR90            (*((uword volatile *) 0xF0005140))
#define CAN_MOFCR90_0            0x00080000
#define CAN_MOFCR90_DATC         0x00000800
#define CAN_MOFCR90_DLCC         0x00000400
#define CAN_MOFCR90_FRREN        0x00100000
#define CAN_MOFCR90_GDFS         0x00000100
#define CAN_MOFCR90_IDC          0x00000200
#define CAN_MOFCR90_OVIE         0x00040000
#define CAN_MOFCR90_RMM          0x00200000
#define CAN_MOFCR90_RXIE         0x00010000
#define CAN_MOFCR90_SDT          0x00400000
#define CAN_MOFCR90_STT          0x00800000
#define CAN_MOFCR90_TXIE         0x00020000

// Message Object 91 Function Control Register
#define CAN_MOFCR91            (*((uword volatile *) 0xF0005160))
#define CAN_MOFCR91_0            0x00080000
#define CAN_MOFCR91_DATC         0x00000800
#define CAN_MOFCR91_DLCC         0x00000400
#define CAN_MOFCR91_FRREN        0x00100000
#define CAN_MOFCR91_GDFS         0x00000100
#define CAN_MOFCR91_IDC          0x00000200
#define CAN_MOFCR91_OVIE         0x00040000
#define CAN_MOFCR91_RMM          0x00200000
#define CAN_MOFCR91_RXIE         0x00010000
#define CAN_MOFCR91_SDT          0x00400000
#define CAN_MOFCR91_STT          0x00800000
#define CAN_MOFCR91_TXIE         0x00020000

// Message Object 92 Function Control Register
#define CAN_MOFCR92            (*((uword volatile *) 0xF0005180))
#define CAN_MOFCR92_0            0x00080000
#define CAN_MOFCR92_DATC         0x00000800
#define CAN_MOFCR92_DLCC         0x00000400
#define CAN_MOFCR92_FRREN        0x00100000
#define CAN_MOFCR92_GDFS         0x00000100
#define CAN_MOFCR92_IDC          0x00000200
#define CAN_MOFCR92_OVIE         0x00040000
#define CAN_MOFCR92_RMM          0x00200000
#define CAN_MOFCR92_RXIE         0x00010000
#define CAN_MOFCR92_SDT          0x00400000
#define CAN_MOFCR92_STT          0x00800000
#define CAN_MOFCR92_TXIE         0x00020000

// Message Object 93 Function Control Register
#define CAN_MOFCR93            (*((uword volatile *) 0xF00051A0))
#define CAN_MOFCR93_0            0x00080000
#define CAN_MOFCR93_DATC         0x00000800
#define CAN_MOFCR93_DLCC         0x00000400
#define CAN_MOFCR93_FRREN        0x00100000
#define CAN_MOFCR93_GDFS         0x00000100
#define CAN_MOFCR93_IDC          0x00000200
#define CAN_MOFCR93_OVIE         0x00040000
#define CAN_MOFCR93_RMM          0x00200000
#define CAN_MOFCR93_RXIE         0x00010000
#define CAN_MOFCR93_SDT          0x00400000
#define CAN_MOFCR93_STT          0x00800000
#define CAN_MOFCR93_TXIE         0x00020000

// Message Object 94 Function Control Register
#define CAN_MOFCR94            (*((uword volatile *) 0xF00051C0))
#define CAN_MOFCR94_0            0x00080000
#define CAN_MOFCR94_DATC         0x00000800
#define CAN_MOFCR94_DLCC         0x00000400
#define CAN_MOFCR94_FRREN        0x00100000
#define CAN_MOFCR94_GDFS         0x00000100
#define CAN_MOFCR94_IDC          0x00000200
#define CAN_MOFCR94_OVIE         0x00040000
#define CAN_MOFCR94_RMM          0x00200000
#define CAN_MOFCR94_RXIE         0x00010000
#define CAN_MOFCR94_SDT          0x00400000
#define CAN_MOFCR94_STT          0x00800000
#define CAN_MOFCR94_TXIE         0x00020000

// Message Object 95 Function Control Register
#define CAN_MOFCR95            (*((uword volatile *) 0xF00051E0))
#define CAN_MOFCR95_0            0x00080000
#define CAN_MOFCR95_DATC         0x00000800
#define CAN_MOFCR95_DLCC         0x00000400
#define CAN_MOFCR95_FRREN        0x00100000
#define CAN_MOFCR95_GDFS         0x00000100
#define CAN_MOFCR95_IDC          0x00000200
#define CAN_MOFCR95_OVIE         0x00040000
#define CAN_MOFCR95_RMM          0x00200000
#define CAN_MOFCR95_RXIE         0x00010000
#define CAN_MOFCR95_SDT          0x00400000
#define CAN_MOFCR95_STT          0x00800000
#define CAN_MOFCR95_TXIE         0x00020000

// Message Object 96 Function Control Register
#define CAN_MOFCR96            (*((uword volatile *) 0xF0005200))
#define CAN_MOFCR96_0            0x00080000
#define CAN_MOFCR96_DATC         0x00000800
#define CAN_MOFCR96_DLCC         0x00000400
#define CAN_MOFCR96_FRREN        0x00100000
#define CAN_MOFCR96_GDFS         0x00000100
#define CAN_MOFCR96_IDC          0x00000200
#define CAN_MOFCR96_OVIE         0x00040000
#define CAN_MOFCR96_RMM          0x00200000
#define CAN_MOFCR96_RXIE         0x00010000
#define CAN_MOFCR96_SDT          0x00400000
#define CAN_MOFCR96_STT          0x00800000
#define CAN_MOFCR96_TXIE         0x00020000

// Message Object 97 Function Control Register
#define CAN_MOFCR97            (*((uword volatile *) 0xF0005220))
#define CAN_MOFCR97_0            0x00080000
#define CAN_MOFCR97_DATC         0x00000800
#define CAN_MOFCR97_DLCC         0x00000400
#define CAN_MOFCR97_FRREN        0x00100000
#define CAN_MOFCR97_GDFS         0x00000100
#define CAN_MOFCR97_IDC          0x00000200
#define CAN_MOFCR97_OVIE         0x00040000
#define CAN_MOFCR97_RMM          0x00200000
#define CAN_MOFCR97_RXIE         0x00010000
#define CAN_MOFCR97_SDT          0x00400000
#define CAN_MOFCR97_STT          0x00800000
#define CAN_MOFCR97_TXIE         0x00020000

// Message Object 98 Function Control Register
#define CAN_MOFCR98            (*((uword volatile *) 0xF0005240))
#define CAN_MOFCR98_0            0x00080000
#define CAN_MOFCR98_DATC         0x00000800
#define CAN_MOFCR98_DLCC         0x00000400
#define CAN_MOFCR98_FRREN        0x00100000
#define CAN_MOFCR98_GDFS         0x00000100
#define CAN_MOFCR98_IDC          0x00000200
#define CAN_MOFCR98_OVIE         0x00040000
#define CAN_MOFCR98_RMM          0x00200000
#define CAN_MOFCR98_RXIE         0x00010000
#define CAN_MOFCR98_SDT          0x00400000
#define CAN_MOFCR98_STT          0x00800000
#define CAN_MOFCR98_TXIE         0x00020000

// Message Object 99 Function Control Register
#define CAN_MOFCR99            (*((uword volatile *) 0xF0005260))
#define CAN_MOFCR99_0            0x00080000
#define CAN_MOFCR99_DATC         0x00000800
#define CAN_MOFCR99_DLCC         0x00000400
#define CAN_MOFCR99_FRREN        0x00100000
#define CAN_MOFCR99_GDFS         0x00000100
#define CAN_MOFCR99_IDC          0x00000200
#define CAN_MOFCR99_OVIE         0x00040000
#define CAN_MOFCR99_RMM          0x00200000
#define CAN_MOFCR99_RXIE         0x00010000
#define CAN_MOFCR99_SDT          0x00400000
#define CAN_MOFCR99_STT          0x00800000
#define CAN_MOFCR99_TXIE         0x00020000

// Message Object 0 FIFO/Gateway Pointer Register
#define CAN_MOFGPR0            (*((uword volatile *) 0xF0004604))

// Message Object 1 FIFO/Gateway Pointer Register
#define CAN_MOFGPR1            (*((uword volatile *) 0xF0004624))

// Message Object 10 FIFO/Gateway Pointer Register
#define CAN_MOFGPR10           (*((uword volatile *) 0xF0004744))

// Message Object 100 FIFO/Gateway Pointer Register
#define CAN_MOFGPR100          (*((uword volatile *) 0xF0005284))

// Message Object 101 FIFO/Gateway Pointer Register
#define CAN_MOFGPR101          (*((uword volatile *) 0xF00052A4))

// Message Object 102 FIFO/Gateway Pointer Register
#define CAN_MOFGPR102          (*((uword volatile *) 0xF00052C4))

// Message Object 103 FIFO/Gateway Pointer Register
#define CAN_MOFGPR103          (*((uword volatile *) 0xF00052E4))

// Message Object 104 FIFO/Gateway Pointer Register
#define CAN_MOFGPR104          (*((uword volatile *) 0xF0005304))

// Message Object 105 FIFO/Gateway Pointer Register
#define CAN_MOFGPR105          (*((uword volatile *) 0xF0005324))

// Message Object 106 FIFO/Gateway Pointer Register
#define CAN_MOFGPR106          (*((uword volatile *) 0xF0005344))

// Message Object 107 FIFO/Gateway Pointer Register
#define CAN_MOFGPR107          (*((uword volatile *) 0xF0005364))

// Message Object 108 FIFO/Gateway Pointer Register
#define CAN_MOFGPR108          (*((uword volatile *) 0xF0005384))

// Message Object 109 FIFO/Gateway Pointer Register
#define CAN_MOFGPR109          (*((uword volatile *) 0xF00053A4))

// Message Object 11 FIFO/Gateway Pointer Register
#define CAN_MOFGPR11           (*((uword volatile *) 0xF0004764))

// Message Object 110 FIFO/Gateway Pointer Register
#define CAN_MOFGPR110          (*((uword volatile *) 0xF00053C4))

// Message Object 111 FIFO/Gateway Pointer Register
#define CAN_MOFGPR111          (*((uword volatile *) 0xF00053E4))

// Message Object 112 FIFO/Gateway Pointer Register
#define CAN_MOFGPR112          (*((uword volatile *) 0xF0005404))

// Message Object 113 FIFO/Gateway Pointer Register
#define CAN_MOFGPR113          (*((uword volatile *) 0xF0005424))

// Message Object 114 FIFO/Gateway Pointer Register
#define CAN_MOFGPR114          (*((uword volatile *) 0xF0005444))

// Message Object 115 FIFO/Gateway Pointer Register
#define CAN_MOFGPR115          (*((uword volatile *) 0xF0005464))

// Message Object 116 FIFO/Gateway Pointer Register
#define CAN_MOFGPR116          (*((uword volatile *) 0xF0005484))

// Message Object 117 FIFO/Gateway Pointer Register
#define CAN_MOFGPR117          (*((uword volatile *) 0xF00054A4))

// Message Object 118 FIFO/Gateway Pointer Register
#define CAN_MOFGPR118          (*((uword volatile *) 0xF00054C4))

// Message Object 119 FIFO/Gateway Pointer Register
#define CAN_MOFGPR119          (*((uword volatile *) 0xF00054E4))

// Message Object 12 FIFO/Gateway Pointer Register
#define CAN_MOFGPR12           (*((uword volatile *) 0xF0004784))

// Message Object 120 FIFO/Gateway Pointer Register
#define CAN_MOFGPR120          (*((uword volatile *) 0xF0005504))

// Message Object 121 FIFO/Gateway Pointer Register
#define CAN_MOFGPR121          (*((uword volatile *) 0xF0005524))

// Message Object 122 FIFO/Gateway Pointer Register
#define CAN_MOFGPR122          (*((uword volatile *) 0xF0005544))

// Message Object 123 FIFO/Gateway Pointer Register
#define CAN_MOFGPR123          (*((uword volatile *) 0xF0005564))

// Message Object 124 FIFO/Gateway Pointer Register
#define CAN_MOFGPR124          (*((uword volatile *) 0xF0005584))

// Message Object 125 FIFO/Gateway Pointer Register
#define CAN_MOFGPR125          (*((uword volatile *) 0xF00055A4))

// Message Object 126 FIFO/Gateway Pointer Register
#define CAN_MOFGPR126          (*((uword volatile *) 0xF00055C4))

// Message Object 127 FIFO/Gateway Pointer Register
#define CAN_MOFGPR127          (*((uword volatile *) 0xF00055E4))

// Message Object 13 FIFO/Gateway Pointer Register
#define CAN_MOFGPR13           (*((uword volatile *) 0xF00047A4))

// Message Object 14 FIFO/Gateway Pointer Register
#define CAN_MOFGPR14           (*((uword volatile *) 0xF00047C4))

// Message Object 15 FIFO/Gateway Pointer Register
#define CAN_MOFGPR15           (*((uword volatile *) 0xF00047E4))

// Message Object 16 FIFO/Gateway Pointer Register
#define CAN_MOFGPR16           (*((uword volatile *) 0xF0004804))

// Message Object 17 FIFO/Gateway Pointer Register
#define CAN_MOFGPR17           (*((uword volatile *) 0xF0004824))

// Message Object 18 FIFO/Gateway Pointer Register
#define CAN_MOFGPR18           (*((uword volatile *) 0xF0004844))

// Message Object 19 FIFO/Gateway Pointer Register
#define CAN_MOFGPR19           (*((uword volatile *) 0xF0004864))

// Message Object 2 FIFO/Gateway Pointer Register
#define CAN_MOFGPR2            (*((uword volatile *) 0xF0004644))

// Message Object 20 FIFO/Gateway Pointer Register
#define CAN_MOFGPR20           (*((uword volatile *) 0xF0004884))

// Message Object 21 FIFO/Gateway Pointer Register
#define CAN_MOFGPR21           (*((uword volatile *) 0xF00048A4))

// Message Object 22 FIFO/Gateway Pointer Register
#define CAN_MOFGPR22           (*((uword volatile *) 0xF00048C4))

// Message Object 23 FIFO/Gateway Pointer Register
#define CAN_MOFGPR23           (*((uword volatile *) 0xF00048E4))

// Message Object 24 FIFO/Gateway Pointer Register
#define CAN_MOFGPR24           (*((uword volatile *) 0xF0004904))

// Message Object 25 FIFO/Gateway Pointer Register
#define CAN_MOFGPR25           (*((uword volatile *) 0xF0004924))

// Message Object 26 FIFO/Gateway Pointer Register
#define CAN_MOFGPR26           (*((uword volatile *) 0xF0004944))

// Message Object 27 FIFO/Gateway Pointer Register
#define CAN_MOFGPR27           (*((uword volatile *) 0xF0004964))

// Message Object 28 FIFO/Gateway Pointer Register
#define CAN_MOFGPR28           (*((uword volatile *) 0xF0004984))

// Message Object 29 FIFO/Gateway Pointer Register
#define CAN_MOFGPR29           (*((uword volatile *) 0xF00049A4))

// Message Object 3 FIFO/Gateway Pointer Register
#define CAN_MOFGPR3            (*((uword volatile *) 0xF0004664))

// Message Object 30 FIFO/Gateway Pointer Register
#define CAN_MOFGPR30           (*((uword volatile *) 0xF00049C4))

// Message Object 31 FIFO/Gateway Pointer Register
#define CAN_MOFGPR31           (*((uword volatile *) 0xF00049E4))

// Message Object 32 FIFO/Gateway Pointer Register
#define CAN_MOFGPR32           (*((uword volatile *) 0xF0004A04))

// Message Object 33 FIFO/Gateway Pointer Register
#define CAN_MOFGPR33           (*((uword volatile *) 0xF0004A24))

// Message Object 34 FIFO/Gateway Pointer Register
#define CAN_MOFGPR34           (*((uword volatile *) 0xF0004A44))

// Message Object 35 FIFO/Gateway Pointer Register
#define CAN_MOFGPR35           (*((uword volatile *) 0xF0004A64))

// Message Object 36 FIFO/Gateway Pointer Register
#define CAN_MOFGPR36           (*((uword volatile *) 0xF0004A84))

// Message Object 37 FIFO/Gateway Pointer Register
#define CAN_MOFGPR37           (*((uword volatile *) 0xF0004AA4))

// Message Object 38 FIFO/Gateway Pointer Register
#define CAN_MOFGPR38           (*((uword volatile *) 0xF0004AC4))

// Message Object 39 FIFO/Gateway Pointer Register
#define CAN_MOFGPR39           (*((uword volatile *) 0xF0004AE4))

// Message Object 4 FIFO/Gateway Pointer Register
#define CAN_MOFGPR4            (*((uword volatile *) 0xF0004684))

// Message Object 40 FIFO/Gateway Pointer Register
#define CAN_MOFGPR40           (*((uword volatile *) 0xF0004B04))

// Message Object 41 FIFO/Gateway Pointer Register
#define CAN_MOFGPR41           (*((uword volatile *) 0xF0004B24))

// Message Object 42 FIFO/Gateway Pointer Register
#define CAN_MOFGPR42           (*((uword volatile *) 0xF0004B44))

// Message Object 43 FIFO/Gateway Pointer Register
#define CAN_MOFGPR43           (*((uword volatile *) 0xF0004B64))

// Message Object 44 FIFO/Gateway Pointer Register
#define CAN_MOFGPR44           (*((uword volatile *) 0xF0004B84))

// Message Object 45 FIFO/Gateway Pointer Register
#define CAN_MOFGPR45           (*((uword volatile *) 0xF0004BA4))

// Message Object 46 FIFO/Gateway Pointer Register
#define CAN_MOFGPR46           (*((uword volatile *) 0xF0004BC4))

// Message Object 47 FIFO/Gateway Pointer Register
#define CAN_MOFGPR47           (*((uword volatile *) 0xF0004BE4))

// Message Object 48 FIFO/Gateway Pointer Register
#define CAN_MOFGPR48           (*((uword volatile *) 0xF0004C04))

// Message Object 49 FIFO/Gateway Pointer Register
#define CAN_MOFGPR49           (*((uword volatile *) 0xF0004C24))

// Message Object 5 FIFO/Gateway Pointer Register
#define CAN_MOFGPR5            (*((uword volatile *) 0xF00046A4))

// Message Object 50 FIFO/Gateway Pointer Register
#define CAN_MOFGPR50           (*((uword volatile *) 0xF0004C44))

// Message Object 51 FIFO/Gateway Pointer Register
#define CAN_MOFGPR51           (*((uword volatile *) 0xF0004C64))

// Message Object 52 FIFO/Gateway Pointer Register
#define CAN_MOFGPR52           (*((uword volatile *) 0xF0004C84))

// Message Object 53 FIFO/Gateway Pointer Register
#define CAN_MOFGPR53           (*((uword volatile *) 0xF0004CA4))

// Message Object 54 FIFO/Gateway Pointer Register
#define CAN_MOFGPR54           (*((uword volatile *) 0xF0004CC4))

// Message Object 55 FIFO/Gateway Pointer Register
#define CAN_MOFGPR55           (*((uword volatile *) 0xF0004CE4))

// Message Object 56 FIFO/Gateway Pointer Register
#define CAN_MOFGPR56           (*((uword volatile *) 0xF0004D04))

// Message Object 57 FIFO/Gateway Pointer Register
#define CAN_MOFGPR57           (*((uword volatile *) 0xF0004D24))

// Message Object 58 FIFO/Gateway Pointer Register
#define CAN_MOFGPR58           (*((uword volatile *) 0xF0004D44))

// Message Object 59 FIFO/Gateway Pointer Register
#define CAN_MOFGPR59           (*((uword volatile *) 0xF0004D64))

// Message Object 6 FIFO/Gateway Pointer Register
#define CAN_MOFGPR6            (*((uword volatile *) 0xF00046C4))

// Message Object 60 FIFO/Gateway Pointer Register
#define CAN_MOFGPR60           (*((uword volatile *) 0xF0004D84))

// Message Object 61 FIFO/Gateway Pointer Register
#define CAN_MOFGPR61           (*((uword volatile *) 0xF0004DA4))

// Message Object 62 FIFO/Gateway Pointer Register
#define CAN_MOFGPR62           (*((uword volatile *) 0xF0004DC4))

// Message Object 63 FIFO/Gateway Pointer Register
#define CAN_MOFGPR63           (*((uword volatile *) 0xF0004DE4))

// Message Object 64 FIFO/Gateway Pointer Register
#define CAN_MOFGPR64           (*((uword volatile *) 0xF0004E04))

// Message Object 65 FIFO/Gateway Pointer Register
#define CAN_MOFGPR65           (*((uword volatile *) 0xF0004E24))

// Message Object 66 FIFO/Gateway Pointer Register
#define CAN_MOFGPR66           (*((uword volatile *) 0xF0004E44))

// Message Object 67 FIFO/Gateway Pointer Register
#define CAN_MOFGPR67           (*((uword volatile *) 0xF0004E64))

// Message Object 68 FIFO/Gateway Pointer Register
#define CAN_MOFGPR68           (*((uword volatile *) 0xF0004E84))

// Message Object 69 FIFO/Gateway Pointer Register
#define CAN_MOFGPR69           (*((uword volatile *) 0xF0004EA4))

// Message Object 7 FIFO/Gateway Pointer Register
#define CAN_MOFGPR7            (*((uword volatile *) 0xF00046E4))

// Message Object 70 FIFO/Gateway Pointer Register
#define CAN_MOFGPR70           (*((uword volatile *) 0xF0004EC4))

// Message Object 71 FIFO/Gateway Pointer Register
#define CAN_MOFGPR71           (*((uword volatile *) 0xF0004EE4))

// Message Object 72 FIFO/Gateway Pointer Register
#define CAN_MOFGPR72           (*((uword volatile *) 0xF0004F04))

// Message Object 73 FIFO/Gateway Pointer Register
#define CAN_MOFGPR73           (*((uword volatile *) 0xF0004F24))

// Message Object 74 FIFO/Gateway Pointer Register
#define CAN_MOFGPR74           (*((uword volatile *) 0xF0004F44))

// Message Object 75 FIFO/Gateway Pointer Register
#define CAN_MOFGPR75           (*((uword volatile *) 0xF0004F64))

// Message Object 76 FIFO/Gateway Pointer Register
#define CAN_MOFGPR76           (*((uword volatile *) 0xF0004F84))

// Message Object 77 FIFO/Gateway Pointer Register
#define CAN_MOFGPR77           (*((uword volatile *) 0xF0004FA4))

// Message Object 78 FIFO/Gateway Pointer Register
#define CAN_MOFGPR78           (*((uword volatile *) 0xF0004FC4))

// Message Object 79 FIFO/Gateway Pointer Register
#define CAN_MOFGPR79           (*((uword volatile *) 0xF0004FE4))

// Message Object 8 FIFO/Gateway Pointer Register
#define CAN_MOFGPR8            (*((uword volatile *) 0xF0004704))

// Message Object 80 FIFO/Gateway Pointer Register
#define CAN_MOFGPR80           (*((uword volatile *) 0xF0005004))

// Message Object 81 FIFO/Gateway Pointer Register
#define CAN_MOFGPR81           (*((uword volatile *) 0xF0005024))

// Message Object 82 FIFO/Gateway Pointer Register
#define CAN_MOFGPR82           (*((uword volatile *) 0xF0005044))

// Message Object 83 FIFO/Gateway Pointer Register
#define CAN_MOFGPR83           (*((uword volatile *) 0xF0005064))

// Message Object 84 FIFO/Gateway Pointer Register
#define CAN_MOFGPR84           (*((uword volatile *) 0xF0005084))

// Message Object 85 FIFO/Gateway Pointer Register
#define CAN_MOFGPR85           (*((uword volatile *) 0xF00050A4))

// Message Object 86 FIFO/Gateway Pointer Register
#define CAN_MOFGPR86           (*((uword volatile *) 0xF00050C4))

// Message Object 87 FIFO/Gateway Pointer Register
#define CAN_MOFGPR87           (*((uword volatile *) 0xF00050E4))

// Message Object 88 FIFO/Gateway Pointer Register
#define CAN_MOFGPR88           (*((uword volatile *) 0xF0005104))

// Message Object 89 FIFO/Gateway Pointer Register
#define CAN_MOFGPR89           (*((uword volatile *) 0xF0005124))

// Message Object 9 FIFO/Gateway Pointer Register
#define CAN_MOFGPR9            (*((uword volatile *) 0xF0004724))

// Message Object 90 FIFO/Gateway Pointer Register
#define CAN_MOFGPR90           (*((uword volatile *) 0xF0005144))

// Message Object 91 FIFO/Gateway Pointer Register
#define CAN_MOFGPR91           (*((uword volatile *) 0xF0005164))

// Message Object 92 FIFO/Gateway Pointer Register
#define CAN_MOFGPR92           (*((uword volatile *) 0xF0005184))

// Message Object 93 FIFO/Gateway Pointer Register
#define CAN_MOFGPR93           (*((uword volatile *) 0xF00051A4))

// Message Object 94 FIFO/Gateway Pointer Register
#define CAN_MOFGPR94           (*((uword volatile *) 0xF00051C4))

// Message Object 95 FIFO/Gateway Pointer Register
#define CAN_MOFGPR95           (*((uword volatile *) 0xF00051E4))

// Message Object 96 FIFO/Gateway Pointer Register
#define CAN_MOFGPR96           (*((uword volatile *) 0xF0005204))

// Message Object 97 FIFO/Gateway Pointer Register
#define CAN_MOFGPR97           (*((uword volatile *) 0xF0005224))

// Message Object 98 FIFO/Gateway Pointer Register
#define CAN_MOFGPR98           (*((uword volatile *) 0xF0005244))

// Message Object 99 FIFO/Gateway Pointer Register
#define CAN_MOFGPR99           (*((uword volatile *) 0xF0005264))

// Message Object 0 Interrupt Pointer Register
#define CAN_MOIPR0             (*((uword volatile *) 0xF0004608))

// Message Object 1 Interrupt Pointer Register
#define CAN_MOIPR1             (*((uword volatile *) 0xF0004628))

// Message Object 10 Interrupt Pointer Register
#define CAN_MOIPR10            (*((uword volatile *) 0xF0004748))

// Message Object 100 Interrupt Pointer Register
#define CAN_MOIPR100           (*((uword volatile *) 0xF0005288))

// Message Object 101 Interrupt Pointer Register
#define CAN_MOIPR101           (*((uword volatile *) 0xF00052A8))

// Message Object 102 Interrupt Pointer Register
#define CAN_MOIPR102           (*((uword volatile *) 0xF00052C8))

// Message Object 103 Interrupt Pointer Register
#define CAN_MOIPR103           (*((uword volatile *) 0xF00052E8))

// Message Object 104 Interrupt Pointer Register
#define CAN_MOIPR104           (*((uword volatile *) 0xF0005308))

// Message Object 105 Interrupt Pointer Register
#define CAN_MOIPR105           (*((uword volatile *) 0xF0005328))

// Message Object 106 Interrupt Pointer Register
#define CAN_MOIPR106           (*((uword volatile *) 0xF0005348))

// Message Object 107 Interrupt Pointer Register
#define CAN_MOIPR107           (*((uword volatile *) 0xF0005368))

// Message Object 108 Interrupt Pointer Register
#define CAN_MOIPR108           (*((uword volatile *) 0xF0005388))

// Message Object 109 Interrupt Pointer Register
#define CAN_MOIPR109           (*((uword volatile *) 0xF00053A8))

// Message Object 11 Interrupt Pointer Register
#define CAN_MOIPR11            (*((uword volatile *) 0xF0004768))

// Message Object 110 Interrupt Pointer Register
#define CAN_MOIPR110           (*((uword volatile *) 0xF00053C8))

// Message Object 111 Interrupt Pointer Register
#define CAN_MOIPR111           (*((uword volatile *) 0xF00053E8))

// Message Object 112 Interrupt Pointer Register
#define CAN_MOIPR112           (*((uword volatile *) 0xF0005408))

// Message Object 113 Interrupt Pointer Register
#define CAN_MOIPR113           (*((uword volatile *) 0xF0005428))

// Message Object 114 Interrupt Pointer Register
#define CAN_MOIPR114           (*((uword volatile *) 0xF0005448))

// Message Object 115 Interrupt Pointer Register
#define CAN_MOIPR115           (*((uword volatile *) 0xF0005468))

// Message Object 116 Interrupt Pointer Register
#define CAN_MOIPR116           (*((uword volatile *) 0xF0005488))

// Message Object 117 Interrupt Pointer Register
#define CAN_MOIPR117           (*((uword volatile *) 0xF00054A8))

// Message Object 118 Interrupt Pointer Register
#define CAN_MOIPR118           (*((uword volatile *) 0xF00054C8))

// Message Object 119 Interrupt Pointer Register
#define CAN_MOIPR119           (*((uword volatile *) 0xF00054E8))

// Message Object 12 Interrupt Pointer Register
#define CAN_MOIPR12            (*((uword volatile *) 0xF0004788))

// Message Object 120 Interrupt Pointer Register
#define CAN_MOIPR120           (*((uword volatile *) 0xF0005508))

// Message Object 121 Interrupt Pointer Register
#define CAN_MOIPR121           (*((uword volatile *) 0xF0005528))

// Message Object 122 Interrupt Pointer Register
#define CAN_MOIPR122           (*((uword volatile *) 0xF0005548))

// Message Object 123 Interrupt Pointer Register
#define CAN_MOIPR123           (*((uword volatile *) 0xF0005568))

// Message Object 124 Interrupt Pointer Register
#define CAN_MOIPR124           (*((uword volatile *) 0xF0005588))

// Message Object 125 Interrupt Pointer Register
#define CAN_MOIPR125           (*((uword volatile *) 0xF00055A8))

// Message Object 126 Interrupt Pointer Register
#define CAN_MOIPR126           (*((uword volatile *) 0xF00055C8))

// Message Object 127 Interrupt Pointer Register
#define CAN_MOIPR127           (*((uword volatile *) 0xF00055E8))

// Message Object 13 Interrupt Pointer Register
#define CAN_MOIPR13            (*((uword volatile *) 0xF00047A8))

// Message Object 14 Interrupt Pointer Register
#define CAN_MOIPR14            (*((uword volatile *) 0xF00047C8))

// Message Object 15 Interrupt Pointer Register
#define CAN_MOIPR15            (*((uword volatile *) 0xF00047E8))

// Message Object 16 Interrupt Pointer Register
#define CAN_MOIPR16            (*((uword volatile *) 0xF0004808))

// Message Object 17 Interrupt Pointer Register
#define CAN_MOIPR17            (*((uword volatile *) 0xF0004828))

// Message Object 18 Interrupt Pointer Register
#define CAN_MOIPR18            (*((uword volatile *) 0xF0004848))

// Message Object 19 Interrupt Pointer Register
#define CAN_MOIPR19            (*((uword volatile *) 0xF0004868))

// Message Object 2 Interrupt Pointer Register
#define CAN_MOIPR2             (*((uword volatile *) 0xF0004648))

// Message Object 20 Interrupt Pointer Register
#define CAN_MOIPR20            (*((uword volatile *) 0xF0004888))

// Message Object 21 Interrupt Pointer Register
#define CAN_MOIPR21            (*((uword volatile *) 0xF00048A8))

// Message Object 22 Interrupt Pointer Register
#define CAN_MOIPR22            (*((uword volatile *) 0xF00048C8))

// Message Object 23 Interrupt Pointer Register
#define CAN_MOIPR23            (*((uword volatile *) 0xF00048E8))

// Message Object 24 Interrupt Pointer Register
#define CAN_MOIPR24            (*((uword volatile *) 0xF0004908))

// Message Object 25 Interrupt Pointer Register
#define CAN_MOIPR25            (*((uword volatile *) 0xF0004928))

// Message Object 26 Interrupt Pointer Register
#define CAN_MOIPR26            (*((uword volatile *) 0xF0004948))

// Message Object 27 Interrupt Pointer Register
#define CAN_MOIPR27            (*((uword volatile *) 0xF0004968))

// Message Object 28 Interrupt Pointer Register
#define CAN_MOIPR28            (*((uword volatile *) 0xF0004988))

// Message Object 29 Interrupt Pointer Register
#define CAN_MOIPR29            (*((uword volatile *) 0xF00049A8))

// Message Object 3 Interrupt Pointer Register
#define CAN_MOIPR3             (*((uword volatile *) 0xF0004668))

// Message Object 30 Interrupt Pointer Register
#define CAN_MOIPR30            (*((uword volatile *) 0xF00049C8))

// Message Object 31 Interrupt Pointer Register
#define CAN_MOIPR31            (*((uword volatile *) 0xF00049E8))

// Message Object 32 Interrupt Pointer Register
#define CAN_MOIPR32            (*((uword volatile *) 0xF0004A08))

// Message Object 33 Interrupt Pointer Register
#define CAN_MOIPR33            (*((uword volatile *) 0xF0004A28))

// Message Object 34 Interrupt Pointer Register
#define CAN_MOIPR34            (*((uword volatile *) 0xF0004A48))

// Message Object 35 Interrupt Pointer Register
#define CAN_MOIPR35            (*((uword volatile *) 0xF0004A68))

// Message Object 36 Interrupt Pointer Register
#define CAN_MOIPR36            (*((uword volatile *) 0xF0004A88))

// Message Object 37 Interrupt Pointer Register
#define CAN_MOIPR37            (*((uword volatile *) 0xF0004AA8))

// Message Object 38 Interrupt Pointer Register
#define CAN_MOIPR38            (*((uword volatile *) 0xF0004AC8))

// Message Object 39 Interrupt Pointer Register
#define CAN_MOIPR39            (*((uword volatile *) 0xF0004AE8))

// Message Object 4 Interrupt Pointer Register
#define CAN_MOIPR4             (*((uword volatile *) 0xF0004688))

// Message Object 40 Interrupt Pointer Register
#define CAN_MOIPR40            (*((uword volatile *) 0xF0004B08))

// Message Object 41 Interrupt Pointer Register
#define CAN_MOIPR41            (*((uword volatile *) 0xF0004B28))

// Message Object 42 Interrupt Pointer Register
#define CAN_MOIPR42            (*((uword volatile *) 0xF0004B48))

// Message Object 43 Interrupt Pointer Register
#define CAN_MOIPR43            (*((uword volatile *) 0xF0004B68))

// Message Object 44 Interrupt Pointer Register
#define CAN_MOIPR44            (*((uword volatile *) 0xF0004B88))

// Message Object 45 Interrupt Pointer Register
#define CAN_MOIPR45            (*((uword volatile *) 0xF0004BA8))

// Message Object 46 Interrupt Pointer Register
#define CAN_MOIPR46            (*((uword volatile *) 0xF0004BC8))

// Message Object 47 Interrupt Pointer Register
#define CAN_MOIPR47            (*((uword volatile *) 0xF0004BE8))

// Message Object 48 Interrupt Pointer Register
#define CAN_MOIPR48            (*((uword volatile *) 0xF0004C08))

// Message Object 49 Interrupt Pointer Register
#define CAN_MOIPR49            (*((uword volatile *) 0xF0004C28))

// Message Object 5 Interrupt Pointer Register
#define CAN_MOIPR5             (*((uword volatile *) 0xF00046A8))

// Message Object 50 Interrupt Pointer Register
#define CAN_MOIPR50            (*((uword volatile *) 0xF0004C48))

// Message Object 51 Interrupt Pointer Register
#define CAN_MOIPR51            (*((uword volatile *) 0xF0004C68))

// Message Object 52 Interrupt Pointer Register
#define CAN_MOIPR52            (*((uword volatile *) 0xF0004C88))

// Message Object 53 Interrupt Pointer Register
#define CAN_MOIPR53            (*((uword volatile *) 0xF0004CA8))

// Message Object 54 Interrupt Pointer Register
#define CAN_MOIPR54            (*((uword volatile *) 0xF0004CC8))

// Message Object 55 Interrupt Pointer Register
#define CAN_MOIPR55            (*((uword volatile *) 0xF0004CE8))

// Message Object 56 Interrupt Pointer Register
#define CAN_MOIPR56            (*((uword volatile *) 0xF0004D08))

// Message Object 57 Interrupt Pointer Register
#define CAN_MOIPR57            (*((uword volatile *) 0xF0004D28))

// Message Object 58 Interrupt Pointer Register
#define CAN_MOIPR58            (*((uword volatile *) 0xF0004D48))

// Message Object 59 Interrupt Pointer Register
#define CAN_MOIPR59            (*((uword volatile *) 0xF0004D68))

// Message Object 6 Interrupt Pointer Register
#define CAN_MOIPR6             (*((uword volatile *) 0xF00046C8))

// Message Object 60 Interrupt Pointer Register
#define CAN_MOIPR60            (*((uword volatile *) 0xF0004D88))

// Message Object 61 Interrupt Pointer Register
#define CAN_MOIPR61            (*((uword volatile *) 0xF0004DA8))

// Message Object 62 Interrupt Pointer Register
#define CAN_MOIPR62            (*((uword volatile *) 0xF0004DC8))

// Message Object 63 Interrupt Pointer Register
#define CAN_MOIPR63            (*((uword volatile *) 0xF0004DE8))

// Message Object 64 Interrupt Pointer Register
#define CAN_MOIPR64            (*((uword volatile *) 0xF0004E08))

// Message Object 65 Interrupt Pointer Register
#define CAN_MOIPR65            (*((uword volatile *) 0xF0004E28))

// Message Object 66 Interrupt Pointer Register
#define CAN_MOIPR66            (*((uword volatile *) 0xF0004E48))

// Message Object 67 Interrupt Pointer Register
#define CAN_MOIPR67            (*((uword volatile *) 0xF0004E68))

// Message Object 68 Interrupt Pointer Register
#define CAN_MOIPR68            (*((uword volatile *) 0xF0004E88))

// Message Object 69 Interrupt Pointer Register
#define CAN_MOIPR69            (*((uword volatile *) 0xF0004EA8))

// Message Object 7 Interrupt Pointer Register
#define CAN_MOIPR7             (*((uword volatile *) 0xF00046E8))

// Message Object 70 Interrupt Pointer Register
#define CAN_MOIPR70            (*((uword volatile *) 0xF0004EC8))

// Message Object 71 Interrupt Pointer Register
#define CAN_MOIPR71            (*((uword volatile *) 0xF0004EE8))

// Message Object 72 Interrupt Pointer Register
#define CAN_MOIPR72            (*((uword volatile *) 0xF0004F08))

// Message Object 73 Interrupt Pointer Register
#define CAN_MOIPR73            (*((uword volatile *) 0xF0004F28))

// Message Object 74 Interrupt Pointer Register
#define CAN_MOIPR74            (*((uword volatile *) 0xF0004F48))

// Message Object 75 Interrupt Pointer Register
#define CAN_MOIPR75            (*((uword volatile *) 0xF0004F68))

// Message Object 76 Interrupt Pointer Register
#define CAN_MOIPR76            (*((uword volatile *) 0xF0004F88))

// Message Object 77 Interrupt Pointer Register
#define CAN_MOIPR77            (*((uword volatile *) 0xF0004FA8))

// Message Object 78 Interrupt Pointer Register
#define CAN_MOIPR78            (*((uword volatile *) 0xF0004FC8))

// Message Object 79 Interrupt Pointer Register
#define CAN_MOIPR79            (*((uword volatile *) 0xF0004FE8))

// Message Object 8 Interrupt Pointer Register
#define CAN_MOIPR8             (*((uword volatile *) 0xF0004708))

// Message Object 80 Interrupt Pointer Register
#define CAN_MOIPR80            (*((uword volatile *) 0xF0005008))

// Message Object 81 Interrupt Pointer Register
#define CAN_MOIPR81            (*((uword volatile *) 0xF0005028))

// Message Object 82 Interrupt Pointer Register
#define CAN_MOIPR82            (*((uword volatile *) 0xF0005048))

// Message Object 83 Interrupt Pointer Register
#define CAN_MOIPR83            (*((uword volatile *) 0xF0005068))

// Message Object 84 Interrupt Pointer Register
#define CAN_MOIPR84            (*((uword volatile *) 0xF0005088))

// Message Object 85 Interrupt Pointer Register
#define CAN_MOIPR85            (*((uword volatile *) 0xF00050A8))

// Message Object 86 Interrupt Pointer Register
#define CAN_MOIPR86            (*((uword volatile *) 0xF00050C8))

// Message Object 87 Interrupt Pointer Register
#define CAN_MOIPR87            (*((uword volatile *) 0xF00050E8))

// Message Object 88 Interrupt Pointer Register
#define CAN_MOIPR88            (*((uword volatile *) 0xF0005108))

// Message Object 89 Interrupt Pointer Register
#define CAN_MOIPR89            (*((uword volatile *) 0xF0005128))

// Message Object 9 Interrupt Pointer Register
#define CAN_MOIPR9             (*((uword volatile *) 0xF0004728))

// Message Object 90 Interrupt Pointer Register
#define CAN_MOIPR90            (*((uword volatile *) 0xF0005148))

// Message Object 91 Interrupt Pointer Register
#define CAN_MOIPR91            (*((uword volatile *) 0xF0005168))

// Message Object 92 Interrupt Pointer Register
#define CAN_MOIPR92            (*((uword volatile *) 0xF0005188))

// Message Object 93 Interrupt Pointer Register
#define CAN_MOIPR93            (*((uword volatile *) 0xF00051A8))

// Message Object 94 Interrupt Pointer Register
#define CAN_MOIPR94            (*((uword volatile *) 0xF00051C8))

// Message Object 95 Interrupt Pointer Register
#define CAN_MOIPR95            (*((uword volatile *) 0xF00051E8))

// Message Object 96 Interrupt Pointer Register
#define CAN_MOIPR96            (*((uword volatile *) 0xF0005208))

// Message Object 97 Interrupt Pointer Register
#define CAN_MOIPR97            (*((uword volatile *) 0xF0005228))

// Message Object 98 Interrupt Pointer Register
#define CAN_MOIPR98            (*((uword volatile *) 0xF0005248))

// Message Object 99 Interrupt Pointer Register
#define CAN_MOIPR99            (*((uword volatile *) 0xF0005268))

// Message Index Register 0
#define CAN_MSID0              (*((uword volatile *) 0xF0004140))

// Message Index Register 1
#define CAN_MSID1              (*((uword volatile *) 0xF0004144))

// Message Index Register 2
#define CAN_MSID2              (*((uword volatile *) 0xF0004148))

// Message Index Register 3
#define CAN_MSID3              (*((uword volatile *) 0xF000414C))

// Message Index Register 4
#define CAN_MSID4              (*((uword volatile *) 0xF0004150))

// Message Index Register 5
#define CAN_MSID5              (*((uword volatile *) 0xF0004154))

// Message Index Register 6
#define CAN_MSID6              (*((uword volatile *) 0xF0004158))

// Message Index Register 7
#define CAN_MSID7              (*((uword volatile *) 0xF000415C))

// Message Index Mask Register
#define CAN_MSIMASK            (*((uword volatile *) 0xF00041C0))

// Message Pending Register 0
#define CAN_MSPND0             (*((uword volatile *) 0xF0004120))

// Message Pending Register 1
#define CAN_MSPND1             (*((uword volatile *) 0xF0004124))

// Message Pending Register 2
#define CAN_MSPND2             (*((uword volatile *) 0xF0004128))

// Message Pending Register 3
#define CAN_MSPND3             (*((uword volatile *) 0xF000412C))

// Message Pending Register 4
#define CAN_MSPND4             (*((uword volatile *) 0xF0004130))

// Message Pending Register 5
#define CAN_MSPND5             (*((uword volatile *) 0xF0004134))

// Message Pending Register 6
#define CAN_MSPND6             (*((uword volatile *) 0xF0004138))

// Message Pending Register 7
#define CAN_MSPND7             (*((uword volatile *) 0xF000413C))

// Node 0 Bit Timing Register
#define CAN_NBTR0              (*((uword volatile *) 0xF0004210))
#define CAN_NBTR0_DIV8           0x00008000
#define CAN_NBTR0_FTX            0x00010000

// Node 1 Bit Timing Register
#define CAN_NBTR1              (*((uword volatile *) 0xF0004310))
#define CAN_NBTR1_DIV8           0x00008000
#define CAN_NBTR1_FTX            0x00010000

// Node 2 Bit Timing Register
#define CAN_NBTR2              (*((uword volatile *) 0xF0004410))
#define CAN_NBTR2_DIV8           0x00008000
#define CAN_NBTR2_FTX            0x00010000

// Node 3 Bit Timing Register
#define CAN_NBTR3              (*((uword volatile *) 0xF0004510))
#define CAN_NBTR3_DIV8           0x00008000
#define CAN_NBTR3_FTX            0x00010000

// Node 0 Control Register
#define CAN_NCR0               (*((uword volatile *) 0xF0004200))
#define CAN_NCR0_ALIE            0x00000008
#define CAN_NCR0_CALM            0x00000080
#define CAN_NCR0_CANDIS          0x00000010
#define CAN_NCR0_CCE             0x00000040
#define CAN_NCR0_INIT            0x00000001
#define CAN_NCR0_LECIE           0x00000004
#define CAN_NCR0_SUSEN           0x00000100
#define CAN_NCR0_TRIE            0x00000002

// Node 1 Control Register
#define CAN_NCR1               (*((uword volatile *) 0xF0004300))
#define CAN_NCR1_ALIE            0x00000008
#define CAN_NCR1_CALM            0x00000080
#define CAN_NCR1_CANDIS          0x00000010
#define CAN_NCR1_CCE             0x00000040
#define CAN_NCR1_INIT            0x00000001
#define CAN_NCR1_LECIE           0x00000004
#define CAN_NCR1_SUSEN           0x00000100
#define CAN_NCR1_TRIE            0x00000002

// Node 2 Control Register
#define CAN_NCR2               (*((uword volatile *) 0xF0004400))
#define CAN_NCR2_ALIE            0x00000008
#define CAN_NCR2_CALM            0x00000080
#define CAN_NCR2_CANDIS          0x00000010
#define CAN_NCR2_CCE             0x00000040
#define CAN_NCR2_INIT            0x00000001
#define CAN_NCR2_LECIE           0x00000004
#define CAN_NCR2_SUSEN           0x00000100
#define CAN_NCR2_TRIE            0x00000002

// Node 3 Control Register
#define CAN_NCR3               (*((uword volatile *) 0xF0004500))
#define CAN_NCR3_ALIE            0x00000008
#define CAN_NCR3_CALM            0x00000080
#define CAN_NCR3_CANDIS          0x00000010
#define CAN_NCR3_CCE             0x00000040
#define CAN_NCR3_INIT            0x00000001
#define CAN_NCR3_LECIE           0x00000004
#define CAN_NCR3_SUSEN           0x00000100
#define CAN_NCR3_TRIE            0x00000002

// Node 0 Error Counter Register
#define CAN_NECNT0             (*((uword volatile *) 0xF0004214))
#define CAN_NECNT0_LEINC         0x02000000
#define CAN_NECNT0_LETD          0x01000000

// Node 1 Error Counter Register
#define CAN_NECNT1             (*((uword volatile *) 0xF0004314))
#define CAN_NECNT1_LEINC         0x02000000
#define CAN_NECNT1_LETD          0x01000000

// Node 2 Error Counter Register
#define CAN_NECNT2             (*((uword volatile *) 0xF0004414))
#define CAN_NECNT2_LEINC         0x02000000
#define CAN_NECNT2_LETD          0x01000000

// Node 3 Error Counter Register
#define CAN_NECNT3             (*((uword volatile *) 0xF0004514))
#define CAN_NECNT3_LEINC         0x02000000
#define CAN_NECNT3_LETD          0x01000000

// Node 0 Frame Counter Register
#define CAN_NFCR0              (*((uword volatile *) 0xF0004218))
#define CAN_NFCR0_CFCIE          0x00400000
#define CAN_NFCR0_CFCOV          0x00800000

// Node 1 Frame Counter Register
#define CAN_NFCR1              (*((uword volatile *) 0xF0004318))
#define CAN_NFCR1_CFCIE          0x00400000
#define CAN_NFCR1_CFCOV          0x00800000

// Node 2 Frame Counter Register
#define CAN_NFCR2              (*((uword volatile *) 0xF0004418))
#define CAN_NFCR2_CFCIE          0x00400000
#define CAN_NFCR2_CFCOV          0x00800000

// Node 3 Frame Counter Register
#define CAN_NFCR3              (*((uword volatile *) 0xF0004518))
#define CAN_NFCR3_CFCIE          0x00400000
#define CAN_NFCR3_CFCOV          0x00800000

// Node 0 Interrupt Pointer Register
#define CAN_NIPR0              (*((uword volatile *) 0xF0004208))

// Node 1 Interrupt Pointer Register
#define CAN_NIPR1              (*((uword volatile *) 0xF0004308))

// Node 2 Interrupt Pointer Register
#define CAN_NIPR2              (*((uword volatile *) 0xF0004408))

// Node 3 Interrupt Pointer Register
#define CAN_NIPR3              (*((uword volatile *) 0xF0004508))

// Node 0 Port Control Register
#define CAN_NPCR0              (*((uword volatile *) 0xF000420C))
#define CAN_NPCR0_LBM            0x00000100

// Node 1 Port Control Register
#define CAN_NPCR1              (*((uword volatile *) 0xF000430C))
#define CAN_NPCR1_LBM            0x00000100

// Node 2 Port Control Register
#define CAN_NPCR2              (*((uword volatile *) 0xF000440C))
#define CAN_NPCR2_LBM            0x00000100

// Node 3 Port Control Register
#define CAN_NPCR3              (*((uword volatile *) 0xF000450C))
#define CAN_NPCR3_LBM            0x00000100

// Node 0 Status Register
#define CAN_NSR0               (*((uword volatile *) 0xF0004204))
#define CAN_NSR0_ALERT           0x00000020
#define CAN_NSR0_BOFF            0x00000080
#define CAN_NSR0_EWRN            0x00000040
#define CAN_NSR0_LLE             0x00000100
#define CAN_NSR0_LOE             0x00000200
#define CAN_NSR0_RXOK            0x00000010
#define CAN_NSR0_SUSACK          0x00000400
#define CAN_NSR0_TXOK            0x00000008

// Node 1 Status Register
#define CAN_NSR1               (*((uword volatile *) 0xF0004304))
#define CAN_NSR1_ALERT           0x00000020
#define CAN_NSR1_BOFF            0x00000080
#define CAN_NSR1_EWRN            0x00000040
#define CAN_NSR1_LLE             0x00000100
#define CAN_NSR1_LOE             0x00000200
#define CAN_NSR1_RXOK            0x00000010
#define CAN_NSR1_SUSACK          0x00000400
#define CAN_NSR1_TXOK            0x00000008

// Node 2 Status Register
#define CAN_NSR2               (*((uword volatile *) 0xF0004404))
#define CAN_NSR2_ALERT           0x00000020
#define CAN_NSR2_BOFF            0x00000080
#define CAN_NSR2_EWRN            0x00000040
#define CAN_NSR2_LLE             0x00000100
#define CAN_NSR2_LOE             0x00000200
#define CAN_NSR2_RXOK            0x00000010
#define CAN_NSR2_SUSACK          0x00000400
#define CAN_NSR2_TXOK            0x00000008

// Node 3 Status Register
#define CAN_NSR3               (*((uword volatile *) 0xF0004504))
#define CAN_NSR3_ALERT           0x00000020
#define CAN_NSR3_BOFF            0x00000080
#define CAN_NSR3_EWRN            0x00000040
#define CAN_NSR3_LLE             0x00000100
#define CAN_NSR3_LOE             0x00000200
#define CAN_NSR3_RXOK            0x00000010
#define CAN_NSR3_SUSACK          0x00000400
#define CAN_NSR3_TXOK            0x00000008

// Panel Control Register
#define CAN_PANCTR             (*((uword volatile *) 0xF00041C4))
#define CAN_PANCTR_BUSY          0x00000100
#define CAN_PANCTR_RBUSY         0x00000200

// CAN Service Request Control Register 0
#define CAN_SRC0               (*((uword volatile *) 0xF00040FC))
#define CAN_SRC0_CLRR            0x00004000
#define CAN_SRC0_SETR            0x00008000
#define CAN_SRC0_SRE             0x00001000
#define CAN_SRC0_SRR             0x00002000
#define CAN_SRC0_TOS             0x00000400

// CAN Service Request Control Register 1
#define CAN_SRC1               (*((uword volatile *) 0xF00040F8))
#define CAN_SRC1_CLRR            0x00004000
#define CAN_SRC1_SETR            0x00008000
#define CAN_SRC1_SRE             0x00001000
#define CAN_SRC1_SRR             0x00002000
#define CAN_SRC1_TOS             0x00000400

// CAN Service Request Control Register 10
#define CAN_SRC10              (*((uword volatile *) 0xF00040D4))
#define CAN_SRC10_CLRR           0x00004000
#define CAN_SRC10_SETR           0x00008000
#define CAN_SRC10_SRE            0x00001000
#define CAN_SRC10_SRR            0x00002000
#define CAN_SRC10_TOS            0x00000400

// CAN Service Request Control Register 11
#define CAN_SRC11              (*((uword volatile *) 0xF00040D0))
#define CAN_SRC11_CLRR           0x00004000
#define CAN_SRC11_SETR           0x00008000
#define CAN_SRC11_SRE            0x00001000
#define CAN_SRC11_SRR            0x00002000
#define CAN_SRC11_TOS            0x00000400

// CAN Service Request Control Register 12
#define CAN_SRC12              (*((uword volatile *) 0xF00040CC))
#define CAN_SRC12_CLRR           0x00004000
#define CAN_SRC12_SETR           0x00008000
#define CAN_SRC12_SRE            0x00001000
#define CAN_SRC12_SRR            0x00002000
#define CAN_SRC12_TOS            0x00000400

// CAN Service Request Control Register 13
#define CAN_SRC13              (*((uword volatile *) 0xF00040C8))
#define CAN_SRC13_CLRR           0x00004000
#define CAN_SRC13_SETR           0x00008000
#define CAN_SRC13_SRE            0x00001000
#define CAN_SRC13_SRR            0x00002000
#define CAN_SRC13_TOS            0x00000400

// CAN Service Request Control Register 14
#define CAN_SRC14              (*((uword volatile *) 0xF00040C4))
#define CAN_SRC14_CLRR           0x00004000
#define CAN_SRC14_SETR           0x00008000
#define CAN_SRC14_SRE            0x00001000
#define CAN_SRC14_SRR            0x00002000
#define CAN_SRC14_TOS            0x00000400

// CAN Service Request Control Register 15
#define CAN_SRC15              (*((uword volatile *) 0xF00040C0))
#define CAN_SRC15_CLRR           0x00004000
#define CAN_SRC15_SETR           0x00008000
#define CAN_SRC15_SRE            0x00001000
#define CAN_SRC15_SRR            0x00002000
#define CAN_SRC15_TOS            0x00000400

// CAN Service Request Control Register 2
#define CAN_SRC2               (*((uword volatile *) 0xF00040F4))
#define CAN_SRC2_CLRR            0x00004000
#define CAN_SRC2_SETR            0x00008000
#define CAN_SRC2_SRE             0x00001000
#define CAN_SRC2_SRR             0x00002000
#define CAN_SRC2_TOS             0x00000400

// CAN Service Request Control Register 3
#define CAN_SRC3               (*((uword volatile *) 0xF00040F0))
#define CAN_SRC3_CLRR            0x00004000
#define CAN_SRC3_SETR            0x00008000
#define CAN_SRC3_SRE             0x00001000
#define CAN_SRC3_SRR             0x00002000
#define CAN_SRC3_TOS             0x00000400

// CAN Service Request Control Register 4
#define CAN_SRC4               (*((uword volatile *) 0xF00040EC))
#define CAN_SRC4_CLRR            0x00004000
#define CAN_SRC4_SETR            0x00008000
#define CAN_SRC4_SRE             0x00001000
#define CAN_SRC4_SRR             0x00002000
#define CAN_SRC4_TOS             0x00000400

// CAN Service Request Control Register 5
#define CAN_SRC5               (*((uword volatile *) 0xF00040E8))
#define CAN_SRC5_CLRR            0x00004000
#define CAN_SRC5_SETR            0x00008000
#define CAN_SRC5_SRE             0x00001000
#define CAN_SRC5_SRR             0x00002000
#define CAN_SRC5_TOS             0x00000400

// CAN Service Request Control Register 6
#define CAN_SRC6               (*((uword volatile *) 0xF00040E4))
#define CAN_SRC6_CLRR            0x00004000
#define CAN_SRC6_SETR            0x00008000
#define CAN_SRC6_SRE             0x00001000
#define CAN_SRC6_SRR             0x00002000
#define CAN_SRC6_TOS             0x00000400

// Service Request Control Register 7
#define CAN_SRC7               (*((uword volatile *) 0xF00040E0))
#define CAN_SRC7_CLRR            0x00004000
#define CAN_SRC7_SETR            0x00008000
#define CAN_SRC7_SRE             0x00001000
#define CAN_SRC7_SRR             0x00002000
#define CAN_SRC7_TOS             0x00000400

// CAN Service Request Control Register 8
#define CAN_SRC8               (*((uword volatile *) 0xF00040DC))
#define CAN_SRC8_CLRR            0x00004000
#define CAN_SRC8_SETR            0x00008000
#define CAN_SRC8_SRE             0x00001000
#define CAN_SRC8_SRR             0x00002000
#define CAN_SRC8_TOS             0x00000400

// CAN Service Request Control Register 9
#define CAN_SRC9               (*((uword volatile *) 0xF00040D8))
#define CAN_SRC9_CLRR            0x00004000
#define CAN_SRC9_SETR            0x00008000
#define CAN_SRC9_SRE             0x00001000
#define CAN_SRC9_SRR             0x00002000
#define CAN_SRC9_TOS             0x00000400

// Cerberus Communication Mode Data Register
#define CBS_COMDATA            (*((uword volatile *) 0xF0000368))

// Cerberus Internal Controlled Trace Source Address Register
#define CBS_ICTSA              (*((uword volatile *) 0xF0000388))

// Cerberus Internal Controlled Trace Target Address Register
#define CBS_ICTTA              (*((uword volatile *) 0xF000038C))

// Cerberus Internal Mode Status and Control Register
#define CBS_INTMOD             (*((uword volatile *) 0xF0000384))
#define CBS_INTMOD_CHANNEL_P     ((T_Reg32 *) 0xF0000384)->bit4
#define CBS_INTMOD_CLRCS         ((T_Reg32 *) 0xF0000384)->bit3
#define CBS_INTMOD_CLRINTTRC     ((T_Reg32 *) 0xF0000384)->bit19
#define CBS_INTMOD_INTMOD        ((T_Reg32 *) 0xF0000384)->bit24
#define CBS_INTMOD_INTTRC        ((T_Reg32 *) 0xF0000384)->bit25
#define CBS_INTMOD_SETCRS        ((T_Reg32 *) 0xF0000384)->bit0
#define CBS_INTMOD_SETCS         ((T_Reg32 *) 0xF0000384)->bit2
#define CBS_INTMOD_SETCWS        ((T_Reg32 *) 0xF0000384)->bit1
#define CBS_INTMOD_SETINTMOD     ((T_Reg32 *) 0xF0000384)->bit16
#define CBS_INTMOD_SETINTTRC     ((T_Reg32 *) 0xF0000384)->bit18
#define CBS_INTMOD_TRCMODP       ((T_Reg32 *) 0xF0000384)->bit20

// Cerberus Status Register
#define CBS_IOSR               (*((uword volatile *) 0xF000036C))
#define CBS_IOSR_COMSYNC         ((T_Reg32 *) 0xF000036C)->bit7
#define CBS_IOSR_CRSYNC          ((T_Reg32 *) 0xF000036C)->bit4
#define CBS_IOSR_CWACK           ((T_Reg32 *) 0xF000036C)->bit6
#define CBS_IOSR_CWSYNC          ((T_Reg32 *) 0xF000036C)->bit5

// Module Identification Register
#define CBS_JDP_ID             (*((uword volatile *) 0xF0000308))

// Cerberus Break Bus Switch Configuration Register
#define CBS_MCDBBS             (*((uword volatile *) 0xF0000370))
#define CBS_MCDBBS_BSBM          ((T_Reg32 *) 0xF0000370)->bit2
#define CBS_MCDBBS_BSDMA         ((T_Reg32 *) 0xF0000370)->bit5
#define CBS_MCDBBS_BSM1          ((T_Reg32 *) 0xF0000370)->bit3
#define CBS_MCDBBS_BSPIN         ((T_Reg32 *) 0xF0000370)->bit16
#define CBS_MCDBBS_BSTC          ((T_Reg32 *) 0xF0000370)->bit0
#define CBS_MCDBBS_BTPIN         ((T_Reg32 *) 0xF0000370)->bit19
#define CBS_MCDBBS_BTSS          ((T_Reg32 *) 0xF0000370)->bit23
#define CBS_MCDBBS_BTT           ((T_Reg32 *) 0xF0000370)->bit20
#define CBS_MCDBBS_BTTC          ((T_Reg32 *) 0xF0000370)->bit8

// Cerberus Break Bus Switch Status Register
#define CBS_MCDBBSS            (*((uword volatile *) 0xF0000390))
#define CBS_MCDBBSS_BBC0         ((T_Reg32 *) 0xF0000390)->bit18
#define CBS_MCDBBSS_BBC1         ((T_Reg32 *) 0xF0000390)->bit19
#define CBS_MCDBBSS_BBS0         ((T_Reg32 *) 0xF0000390)->bit16
#define CBS_MCDBBSS_BBS1         ((T_Reg32 *) 0xF0000390)->bit17
#define CBS_MCDBBSS_BSCBM        ((T_Reg32 *) 0xF0000390)->bit10
#define CBS_MCDBBSS_BSCDMA       ((T_Reg32 *) 0xF0000390)->bit13
#define CBS_MCDBBSS_BSCM1        ((T_Reg32 *) 0xF0000390)->bit11
#define CBS_MCDBBSS_BSCTC        ((T_Reg32 *) 0xF0000390)->bit8
#define CBS_MCDBBSS_BSSBM        ((T_Reg32 *) 0xF0000390)->bit2
#define CBS_MCDBBSS_BSSDMA       ((T_Reg32 *) 0xF0000390)->bit5
#define CBS_MCDBBSS_BSSM1        ((T_Reg32 *) 0xF0000390)->bit3
#define CBS_MCDBBSS_BSSTC        ((T_Reg32 *) 0xF0000390)->bit0
#define CBS_MCDBBSS_CAPCLR       ((T_Reg32 *) 0xF0000390)->bit24

// Cerberus Suspend Signal Generation Status and Control Register
#define CBS_MCDSSG             (*((uword volatile *) 0xF0000374))
#define CBS_MCDSSG_BTSCL         ((T_Reg32 *) 0xF0000374)->bit0
#define CBS_MCDSSG_BTSEN         ((T_Reg32 *) 0xF0000374)->bit9
#define CBS_MCDSSG_BTSM          ((T_Reg32 *) 0xF0000374)->bit10
#define CBS_MCDSSG_BTSP          ((T_Reg32 *) 0xF0000374)->bit8
#define CBS_MCDSSG_SDS           ((T_Reg32 *) 0xF0000374)->bit25
#define CBS_MCDSSG_SOS           ((T_Reg32 *) 0xF0000374)->bit24
#define CBS_MCDSSG_SSSBRK        ((T_Reg32 *) 0xF0000374)->bit22
#define CBS_MCDSSG_SSSTC         ((T_Reg32 *) 0xF0000374)->bit16
#define CBS_MCDSSG_SUS           ((T_Reg32 *) 0xF0000374)->bit7
#define CBS_MCDSSG_SUSP          ((T_Reg32 *) 0xF0000374)->bit6

// Cerberus Suspend Signal Generation Configuration Register
#define CBS_MCDSSGC            (*((uword volatile *) 0xF0000394))
#define CBS_MCDSSGC_STCM         ((T_Reg32 *) 0xF0000394)->bit1
#define CBS_MCDSSGC_STCP         ((T_Reg32 *) 0xF0000394)->bit0
#define CBS_MCDSSGC_STCTC        ((T_Reg32 *) 0xF0000394)->bit2

// Cerberus OSCU Configuration and Control Register
#define CBS_OCNTRL             (*((uword volatile *) 0xF000037C))
#define CBS_OCNTRL_HARR          ((T_Reg32 *) 0xF000037C)->bit17
#define CBS_OCNTRL_HARRP         ((T_Reg32 *) 0xF000037C)->bit16
#define CBS_OCNTRL_TRCDEN        ((T_Reg32 *) 0xF000037C)->bit5
#define CBS_OCNTRL_TRCDENP       ((T_Reg32 *) 0xF000037C)->bit4
#define CBS_OCNTRL_TRCDS         ((T_Reg32 *) 0xF000037C)->bit7
#define CBS_OCNTRL_TRCDSP        ((T_Reg32 *) 0xF000037C)->bit6
#define CBS_OCNTRL_TRCEN         ((T_Reg32 *) 0xF000037C)->bit1
#define CBS_OCNTRL_TRCENP        ((T_Reg32 *) 0xF000037C)->bit0
#define CBS_OCNTRL_TRCMUX        ((T_Reg32 *) 0xF000037C)->bit3
#define CBS_OCNTRL_TRCMUXP       ((T_Reg32 *) 0xF000037C)->bit2
#define CBS_OCNTRL_WDTSUS        ((T_Reg32 *) 0xF000037C)->bit13
#define CBS_OCNTRL_WDTSUSP       ((T_Reg32 *) 0xF000037C)->bit12

// Cerberus OCDS Enable Control Register
#define CBS_OEC                (*((uword volatile *) 0xF0000378))
#define CBS_OEC_AUTOK            ((T_Reg32 *) 0xF0000378)->bit19
#define CBS_OEC_AUTOKP           ((T_Reg32 *) 0xF0000378)->bit18
#define CBS_OEC_IFLCK            ((T_Reg32 *) 0xF0000378)->bit17
#define CBS_OEC_IFLCKP           ((T_Reg32 *) 0xF0000378)->bit16

// Cerberus OSCU Status Register
#define CBS_OSTATE             (*((uword volatile *) 0xF0000380))
#define CBS_OSTATE_AUTOK         ((T_Reg32 *) 0xF0000380)->bit17
#define CBS_OSTATE_HARR          ((T_Reg32 *) 0xF0000380)->bit8
#define CBS_OSTATE_IFLCK         ((T_Reg32 *) 0xF0000380)->bit16
#define CBS_OSTATE_OEN           ((T_Reg32 *) 0xF0000380)->bit0
#define CBS_OSTATE_TRCDEN        ((T_Reg32 *) 0xF0000380)->bit3
#define CBS_OSTATE_TRCDS         ((T_Reg32 *) 0xF0000380)->bit4
#define CBS_OSTATE_TRCEN         ((T_Reg32 *) 0xF0000380)->bit1
#define CBS_OSTATE_TRCMUX        ((T_Reg32 *) 0xF0000380)->bit2
#define CBS_OSTATE_WDTSUS        ((T_Reg32 *) 0xF0000380)->bit7

// Cerberus Service Request Control Register
#define CBS_SRC                (*((uword volatile *) 0xF00003FC))
#define CBS_SRC_CLRR             ((T_Reg32 *) 0xF00003FC)->bit14
#define CBS_SRC_SETR             ((T_Reg32 *) 0xF00003FC)->bit15
#define CBS_SRC_SRE              ((T_Reg32 *) 0xF00003FC)->bit12
#define CBS_SRC_SRR              ((T_Reg32 *) 0xF00003FC)->bit13
#define CBS_SRC_TOS              ((T_Reg32 *) 0xF00003FC)->bit10

// Capture/Compare Register for Channel CC60
#define CCU60_CC60R            (*((uword volatile *) 0xF0002030))

// Capture/Compare Shadow Register for Channel CC60
#define CCU60_CC60SR           (*((uword volatile *) 0xF0002040))

// Capture/Compare Register for Channel CC61
#define CCU60_CC61R            (*((uword volatile *) 0xF0002034))

// Capture/Compare Shadow Register for Channel CC61
#define CCU60_CC61SR           (*((uword volatile *) 0xF0002044))

// Capture/Compare Register for Channel CC62
#define CCU60_CC62R            (*((uword volatile *) 0xF0002038))

// Capture/Compare Shadow Register for Channel CC62
#define CCU60_CC62SR           (*((uword volatile *) 0xF0002048))

// Compare Register for Channel CC63
#define CCU60_CC63R            (*((uword volatile *) 0xF0002058))

// Compare Shadow Register for Channel  CC63
#define CCU60_CC63SR           (*((uword volatile *) 0xF000205C))

// CCU60 Clock Control Register
#define CCU60_CLC              (*((uword volatile *) 0xF0002000))
#define CCU60_CLC_DISR           ((T_Reg32 *) 0xF0002000)->bit0
#define CCU60_CLC_DISS           ((T_Reg32 *) 0xF0002000)->bit1
#define CCU60_CLC_EDIS           ((T_Reg32 *) 0xF0002000)->bit3
#define CCU60_CLC_FSOE           ((T_Reg32 *) 0xF0002000)->bit5
#define CCU60_CLC_SBWE           ((T_Reg32 *) 0xF0002000)->bit4
#define CCU60_CLC_SPEN           ((T_Reg32 *) 0xF0002000)->bit2

// Compare State Modification Register
#define CCU60_CMPMODIF         (*((uword volatile *) 0xF0002064))
#define CCU60_CMPMODIF_MCC60R    ((T_Reg32 *) 0xF0002064)->bit8
#define CCU60_CMPMODIF_MCC60S    ((T_Reg32 *) 0xF0002064)->bit0
#define CCU60_CMPMODIF_MCC61R    ((T_Reg32 *) 0xF0002064)->bit9
#define CCU60_CMPMODIF_MCC61S    ((T_Reg32 *) 0xF0002064)->bit1
#define CCU60_CMPMODIF_MCC62R    ((T_Reg32 *) 0xF0002064)->bit10
#define CCU60_CMPMODIF_MCC62S    ((T_Reg32 *) 0xF0002064)->bit2
#define CCU60_CMPMODIF_MCC63R    ((T_Reg32 *) 0xF0002064)->bit14
#define CCU60_CMPMODIF_MCC63S    ((T_Reg32 *) 0xF0002064)->bit6

// Compare Status Register
#define CCU60_CMPSTAT          (*((uword volatile *) 0xF0002060))
#define CCU60_CMPSTAT_CC60PS     ((T_Reg32 *) 0xF0002060)->bit8
#define CCU60_CMPSTAT_CC60ST     ((T_Reg32 *) 0xF0002060)->bit0
#define CCU60_CMPSTAT_CC61PS     ((T_Reg32 *) 0xF0002060)->bit10
#define CCU60_CMPSTAT_CC61ST     ((T_Reg32 *) 0xF0002060)->bit1
#define CCU60_CMPSTAT_CC62PS     ((T_Reg32 *) 0xF0002060)->bit12
#define CCU60_CMPSTAT_CC62ST     ((T_Reg32 *) 0xF0002060)->bit2
#define CCU60_CMPSTAT_CC63ST     ((T_Reg32 *) 0xF0002060)->bit6
#define CCU60_CMPSTAT_CCPOS0     ((T_Reg32 *) 0xF0002060)->bit3
#define CCU60_CMPSTAT_CCPOS1     ((T_Reg32 *) 0xF0002060)->bit4
#define CCU60_CMPSTAT_CCPOS2     ((T_Reg32 *) 0xF0002060)->bit5
#define CCU60_CMPSTAT_COUT60PS   ((T_Reg32 *) 0xF0002060)->bit9
#define CCU60_CMPSTAT_COUT61PS   ((T_Reg32 *) 0xF0002060)->bit11
#define CCU60_CMPSTAT_COUT62PS   ((T_Reg32 *) 0xF0002060)->bit13
#define CCU60_CMPSTAT_COUT63PS   ((T_Reg32 *) 0xF0002060)->bit14
#define CCU60_CMPSTAT_T13IM      ((T_Reg32 *) 0xF0002060)->bit15

// CCU60 Fractional Divider Register
#define CCU60_FDR              (*((uword volatile *) 0xF000200C))
#define CCU60_FDR_DISCLK         ((T_Reg32 *) 0xF000200C)->bit31
#define CCU60_FDR_ENHW           ((T_Reg32 *) 0xF000200C)->bit30
#define CCU60_FDR_SUSACK         ((T_Reg32 *) 0xF000200C)->bit28
#define CCU60_FDR_SUSREQ         ((T_Reg32 *) 0xF000200C)->bit29

// Module Identification Register
#define CCU60_ID               (*((uword volatile *) 0xF0002008))

// Capture/Compare Interrupt Enable Register
#define CCU60_IEN              (*((uword volatile *) 0xF000209C))
#define CCU60_IEN_ENCC60F        ((T_Reg32 *) 0xF000209C)->bit1
#define CCU60_IEN_ENCC60R        ((T_Reg32 *) 0xF000209C)->bit0
#define CCU60_IEN_ENCC61F        ((T_Reg32 *) 0xF000209C)->bit3
#define CCU60_IEN_ENCC61R        ((T_Reg32 *) 0xF000209C)->bit2
#define CCU60_IEN_ENCC62F        ((T_Reg32 *) 0xF000209C)->bit5
#define CCU60_IEN_ENCC62R        ((T_Reg32 *) 0xF000209C)->bit4
#define CCU60_IEN_ENCHE          ((T_Reg32 *) 0xF000209C)->bit12
#define CCU60_IEN_ENIDLE         ((T_Reg32 *) 0xF000209C)->bit14
#define CCU60_IEN_ENSTR          ((T_Reg32 *) 0xF000209C)->bit15
#define CCU60_IEN_ENT12OM        ((T_Reg32 *) 0xF000209C)->bit6
#define CCU60_IEN_ENT12PM        ((T_Reg32 *) 0xF000209C)->bit7
#define CCU60_IEN_ENT13CM        ((T_Reg32 *) 0xF000209C)->bit8
#define CCU60_IEN_ENT13PM        ((T_Reg32 *) 0xF000209C)->bit9
#define CCU60_IEN_ENTRPF         ((T_Reg32 *) 0xF000209C)->bit10
#define CCU60_IEN_ENWHE          ((T_Reg32 *) 0xF000209C)->bit13

// Capture/Compare Interrupt Node Pointer Register
#define CCU60_INP              (*((uword volatile *) 0xF00020A0))

// Capture/Compare Interrupt Status Register
#define CCU60_IS               (*((uword volatile *) 0xF0002090))
#define CCU60_IS_CHE             ((T_Reg32 *) 0xF0002090)->bit12
#define CCU60_IS_ICC60F          ((T_Reg32 *) 0xF0002090)->bit1
#define CCU60_IS_ICC60R          ((T_Reg32 *) 0xF0002090)->bit0
#define CCU60_IS_ICC61F          ((T_Reg32 *) 0xF0002090)->bit3
#define CCU60_IS_ICC61R          ((T_Reg32 *) 0xF0002090)->bit2
#define CCU60_IS_ICC62F          ((T_Reg32 *) 0xF0002090)->bit5
#define CCU60_IS_ICC62R          ((T_Reg32 *) 0xF0002090)->bit4
#define CCU60_IS_IDLE            ((T_Reg32 *) 0xF0002090)->bit14
#define CCU60_IS_STR             ((T_Reg32 *) 0xF0002090)->bit15
#define CCU60_IS_T12OM           ((T_Reg32 *) 0xF0002090)->bit6
#define CCU60_IS_T12PM           ((T_Reg32 *) 0xF0002090)->bit7
#define CCU60_IS_T13CM           ((T_Reg32 *) 0xF0002090)->bit8
#define CCU60_IS_T13PM           ((T_Reg32 *) 0xF0002090)->bit9
#define CCU60_IS_TRPF            ((T_Reg32 *) 0xF0002090)->bit10
#define CCU60_IS_TRPS            ((T_Reg32 *) 0xF0002090)->bit11
#define CCU60_IS_WHE             ((T_Reg32 *) 0xF0002090)->bit13

// Capture/Compare Interrupt Status Reset Register
#define CCU60_ISR              (*((uword volatile *) 0xF0002098))
#define CCU60_ISR_RCC60F         ((T_Reg32 *) 0xF0002098)->bit1
#define CCU60_ISR_RCC60R         ((T_Reg32 *) 0xF0002098)->bit0
#define CCU60_ISR_RCC61F         ((T_Reg32 *) 0xF0002098)->bit3
#define CCU60_ISR_RCC61R         ((T_Reg32 *) 0xF0002098)->bit2
#define CCU60_ISR_RCC62F         ((T_Reg32 *) 0xF0002098)->bit5
#define CCU60_ISR_RCC62R         ((T_Reg32 *) 0xF0002098)->bit4
#define CCU60_ISR_RCHE           ((T_Reg32 *) 0xF0002098)->bit12
#define CCU60_ISR_RIDLE          ((T_Reg32 *) 0xF0002098)->bit14
#define CCU60_ISR_RSTR           ((T_Reg32 *) 0xF0002098)->bit15
#define CCU60_ISR_RT12OM         ((T_Reg32 *) 0xF0002098)->bit6
#define CCU60_ISR_RT12PM         ((T_Reg32 *) 0xF0002098)->bit7
#define CCU60_ISR_RT13CM         ((T_Reg32 *) 0xF0002098)->bit8
#define CCU60_ISR_RT13PM         ((T_Reg32 *) 0xF0002098)->bit9
#define CCU60_ISR_RTRPF          ((T_Reg32 *) 0xF0002098)->bit10
#define CCU60_ISR_RWHE           ((T_Reg32 *) 0xF0002098)->bit13

// Capture/Compare Interrupt Status Set Register
#define CCU60_ISS              (*((uword volatile *) 0xF0002094))
#define CCU60_ISS_SCC60F         ((T_Reg32 *) 0xF0002094)->bit1
#define CCU60_ISS_SCC60R         ((T_Reg32 *) 0xF0002094)->bit0
#define CCU60_ISS_SCC61F         ((T_Reg32 *) 0xF0002094)->bit3
#define CCU60_ISS_SCC61R         ((T_Reg32 *) 0xF0002094)->bit2
#define CCU60_ISS_SCC62F         ((T_Reg32 *) 0xF0002094)->bit5
#define CCU60_ISS_SCC62R         ((T_Reg32 *) 0xF0002094)->bit4
#define CCU60_ISS_SCHE           ((T_Reg32 *) 0xF0002094)->bit12
#define CCU60_ISS_SIDLE          ((T_Reg32 *) 0xF0002094)->bit14
#define CCU60_ISS_SSTR           ((T_Reg32 *) 0xF0002094)->bit15
#define CCU60_ISS_ST12OM         ((T_Reg32 *) 0xF0002094)->bit6
#define CCU60_ISS_ST12PM         ((T_Reg32 *) 0xF0002094)->bit7
#define CCU60_ISS_ST13CM         ((T_Reg32 *) 0xF0002094)->bit8
#define CCU60_ISS_ST13PM         ((T_Reg32 *) 0xF0002094)->bit9
#define CCU60_ISS_STRPF          ((T_Reg32 *) 0xF0002094)->bit10
#define CCU60_ISS_SWHC           ((T_Reg32 *) 0xF0002094)->bit11
#define CCU60_ISS_SWHE           ((T_Reg32 *) 0xF0002094)->bit13

// Multi-Channel Mode Control Register
#define CCU60_MCMCTR           (*((uword volatile *) 0xF0002088))

// Multi-Channel Mode Output Register
#define CCU60_MCMOUT           (*((uword volatile *) 0xF0002084))
#define CCU60_MCMOUT_R           ((T_Reg32 *) 0xF0002084)->bit6

// Multi-Channel Mode Output Shadow Register
#define CCU60_MCMOUTS          (*((uword volatile *) 0xF0002080))
#define CCU60_MCMOUTS_STRHP      ((T_Reg32 *) 0xF0002080)->bit15
#define CCU60_MCMOUTS_STRMCM     ((T_Reg32 *) 0xF0002080)->bit7

// Modulation Control Register
#define CCU60_MODCTR           (*((uword volatile *) 0xF0002070))
#define CCU60_MODCTR_ECT13O      ((T_Reg32 *) 0xF0002070)->bit15
#define CCU60_MODCTR_MCMEN       ((T_Reg32 *) 0xF0002070)->bit7

// Port Input Select Register 0
#define CCU60_PISEL0           (*((uword volatile *) 0xF0002010))

// Port Input Select Register 2
#define CCU60_PISEL2           (*((uword volatile *) 0xF0002014))

// Passive State Level Register
#define CCU60_PSLR             (*((uword volatile *) 0xF0002078))
#define CCU60_PSLR_PSL63         ((T_Reg32 *) 0xF0002078)->bit7

// CCU60 Service Request Control Register 0
#define CCU60_SRC0             (*((uword volatile *) 0xF00020FC))
#define CCU60_SRC0_CLRR          ((T_Reg32 *) 0xF00020FC)->bit14
#define CCU60_SRC0_SETR          ((T_Reg32 *) 0xF00020FC)->bit15
#define CCU60_SRC0_SRE           ((T_Reg32 *) 0xF00020FC)->bit12
#define CCU60_SRC0_SRR           ((T_Reg32 *) 0xF00020FC)->bit13
#define CCU60_SRC0_TOS           ((T_Reg32 *) 0xF00020FC)->bit10

// CCU60 Service Request Control Register 1
#define CCU60_SRC1             (*((uword volatile *) 0xF00020F8))
#define CCU60_SRC1_CLRR          ((T_Reg32 *) 0xF00020F8)->bit14
#define CCU60_SRC1_SETR          ((T_Reg32 *) 0xF00020F8)->bit15
#define CCU60_SRC1_SRE           ((T_Reg32 *) 0xF00020F8)->bit12
#define CCU60_SRC1_SRR           ((T_Reg32 *) 0xF00020F8)->bit13
#define CCU60_SRC1_TOS           ((T_Reg32 *) 0xF00020F8)->bit10

// CCU60 Service Request Control Register 2
#define CCU60_SRC2             (*((uword volatile *) 0xF00020F4))
#define CCU60_SRC2_CLRR          ((T_Reg32 *) 0xF00020F4)->bit14
#define CCU60_SRC2_SETR          ((T_Reg32 *) 0xF00020F4)->bit15
#define CCU60_SRC2_SRE           ((T_Reg32 *) 0xF00020F4)->bit12
#define CCU60_SRC2_SRR           ((T_Reg32 *) 0xF00020F4)->bit13
#define CCU60_SRC2_TOS           ((T_Reg32 *) 0xF00020F4)->bit10

// CCU60 Service Request Control Register 3
#define CCU60_SRC3             (*((uword volatile *) 0xF00020F0))
#define CCU60_SRC3_CLRR          ((T_Reg32 *) 0xF00020F0)->bit14
#define CCU60_SRC3_SETR          ((T_Reg32 *) 0xF00020F0)->bit15
#define CCU60_SRC3_SRE           ((T_Reg32 *) 0xF00020F0)->bit12
#define CCU60_SRC3_SRR           ((T_Reg32 *) 0xF00020F0)->bit13
#define CCU60_SRC3_TOS           ((T_Reg32 *) 0xF00020F0)->bit10

// Timer T12 Counter Register
#define CCU60_T12              (*((uword volatile *) 0xF0002020))

// Dead-Time Control Register for Timer12
#define CCU60_T12DTC           (*((uword volatile *) 0xF0002028))
#define CCU60_T12DTC_DTE0        ((T_Reg32 *) 0xF0002028)->bit8
#define CCU60_T12DTC_DTE1        ((T_Reg32 *) 0xF0002028)->bit9
#define CCU60_T12DTC_DTE2        ((T_Reg32 *) 0xF0002028)->bit10
#define CCU60_T12DTC_DTR0        ((T_Reg32 *) 0xF0002028)->bit12
#define CCU60_T12DTC_DTR1        ((T_Reg32 *) 0xF0002028)->bit13
#define CCU60_T12DTC_DTR2        ((T_Reg32 *) 0xF0002028)->bit14

// T12 Capture/Compare Mode Select Register
#define CCU60_T12MSEL          (*((uword volatile *) 0xF000207C))
#define CCU60_T12MSEL_DBYP       ((T_Reg32 *) 0xF000207C)->bit15

// Timer T12 period register
#define CCU60_T12PR            (*((uword volatile *) 0xF0002024))

// Timer T13 Register
#define CCU60_T13              (*((uword volatile *) 0xF0002050))

// Timer T13 Period Register
#define CCU60_T13PR            (*((uword volatile *) 0xF0002054))

// Timer Control Register 0
#define CCU60_TCTR0            (*((uword volatile *) 0xF0002068))
#define CCU60_TCTR0_CDIR         ((T_Reg32 *) 0xF0002068)->bit6
#define CCU60_TCTR0_CTM          ((T_Reg32 *) 0xF0002068)->bit7
#define CCU60_TCTR0_STE12        ((T_Reg32 *) 0xF0002068)->bit5
#define CCU60_TCTR0_STE13        ((T_Reg32 *) 0xF0002068)->bit13
#define CCU60_TCTR0_T12PRE       ((T_Reg32 *) 0xF0002068)->bit3
#define CCU60_TCTR0_T12R         ((T_Reg32 *) 0xF0002068)->bit4
#define CCU60_TCTR0_T13PRE       ((T_Reg32 *) 0xF0002068)->bit11
#define CCU60_TCTR0_T13R         ((T_Reg32 *) 0xF0002068)->bit12

// Timer Control Register 2
#define CCU60_TCTR2            (*((uword volatile *) 0xF000206C))
#define CCU60_TCTR2_SUSCFG       ((T_Reg32 *) 0xF000206C)->bit7
#define CCU60_TCTR2_T12SSC       ((T_Reg32 *) 0xF000206C)->bit0
#define CCU60_TCTR2_T13SSC       ((T_Reg32 *) 0xF000206C)->bit1

// Timer Control Register 4
#define CCU60_TCTR4            (*((uword volatile *) 0xF000203C))
#define CCU60_TCTR4_DTRES        ((T_Reg32 *) 0xF000203C)->bit3
#define CCU60_TCTR4_T12RES       ((T_Reg32 *) 0xF000203C)->bit2
#define CCU60_TCTR4_T12RR        ((T_Reg32 *) 0xF000203C)->bit0
#define CCU60_TCTR4_T12RS        ((T_Reg32 *) 0xF000203C)->bit1
#define CCU60_TCTR4_T12STD       ((T_Reg32 *) 0xF000203C)->bit7
#define CCU60_TCTR4_T12STR       ((T_Reg32 *) 0xF000203C)->bit6
#define CCU60_TCTR4_T13RES       ((T_Reg32 *) 0xF000203C)->bit10
#define CCU60_TCTR4_T13RR        ((T_Reg32 *) 0xF000203C)->bit8
#define CCU60_TCTR4_T13RS        ((T_Reg32 *) 0xF000203C)->bit9
#define CCU60_TCTR4_T13STD       ((T_Reg32 *) 0xF000203C)->bit15
#define CCU60_TCTR4_T13STR       ((T_Reg32 *) 0xF000203C)->bit14

// Trap Control Register
#define CCU60_TRPCTR           (*((uword volatile *) 0xF0002074))
#define CCU60_TRPCTR_TRPEN13     ((T_Reg32 *) 0xF0002074)->bit14
#define CCU60_TRPCTR_TRPM0       ((T_Reg32 *) 0xF0002074)->bit0
#define CCU60_TRPCTR_TRPM1       ((T_Reg32 *) 0xF0002074)->bit1
#define CCU60_TRPCTR_TRPM2       ((T_Reg32 *) 0xF0002074)->bit2
#define CCU60_TRPCTR_TRPPEN      ((T_Reg32 *) 0xF0002074)->bit15

// Capture/Compare Register for Channel CC60
#define CCU61_CC60R            (*((uword volatile *) 0xF0002130))

// Capture/Compare Shadow Register for Channel CC60
#define CCU61_CC60SR           (*((uword volatile *) 0xF0002140))

// Capture/Compare Register for Channel CC61
#define CCU61_CC61R            (*((uword volatile *) 0xF0002134))

// Capture/Compare Shadow Register for Channel CC61
#define CCU61_CC61SR           (*((uword volatile *) 0xF0002144))

// Capture/Compare Register for Channel CC62
#define CCU61_CC62R            (*((uword volatile *) 0xF0002138))

// Capture/Compare Shadow Register for Channel CC62
#define CCU61_CC62SR           (*((uword volatile *) 0xF0002148))

// Compare Register for Channel CC63
#define CCU61_CC63R            (*((uword volatile *) 0xF0002158))

// Compare Shadow Register for Channel  CC63
#define CCU61_CC63SR           (*((uword volatile *) 0xF000215C))

// Compare State Modification Register
#define CCU61_CMPMODIF         (*((uword volatile *) 0xF0002164))
#define CCU61_CMPMODIF_MCC60R    ((T_Reg32 *) 0xF0002164)->bit8
#define CCU61_CMPMODIF_MCC60S    ((T_Reg32 *) 0xF0002164)->bit0
#define CCU61_CMPMODIF_MCC61R    ((T_Reg32 *) 0xF0002164)->bit9
#define CCU61_CMPMODIF_MCC61S    ((T_Reg32 *) 0xF0002164)->bit1
#define CCU61_CMPMODIF_MCC62R    ((T_Reg32 *) 0xF0002164)->bit10
#define CCU61_CMPMODIF_MCC62S    ((T_Reg32 *) 0xF0002164)->bit2
#define CCU61_CMPMODIF_MCC63R    ((T_Reg32 *) 0xF0002164)->bit14
#define CCU61_CMPMODIF_MCC63S    ((T_Reg32 *) 0xF0002164)->bit6

// Compare Status Register
#define CCU61_CMPSTAT          (*((uword volatile *) 0xF0002160))
#define CCU61_CMPSTAT_CC60PS     ((T_Reg32 *) 0xF0002160)->bit8
#define CCU61_CMPSTAT_CC60ST     ((T_Reg32 *) 0xF0002160)->bit0
#define CCU61_CMPSTAT_CC61PS     ((T_Reg32 *) 0xF0002160)->bit10
#define CCU61_CMPSTAT_CC61ST     ((T_Reg32 *) 0xF0002160)->bit1
#define CCU61_CMPSTAT_CC62PS     ((T_Reg32 *) 0xF0002160)->bit12
#define CCU61_CMPSTAT_CC62ST     ((T_Reg32 *) 0xF0002160)->bit2
#define CCU61_CMPSTAT_CC63ST     ((T_Reg32 *) 0xF0002160)->bit6
#define CCU61_CMPSTAT_CCPOS0     ((T_Reg32 *) 0xF0002160)->bit3
#define CCU61_CMPSTAT_CCPOS1     ((T_Reg32 *) 0xF0002160)->bit4
#define CCU61_CMPSTAT_CCPOS2     ((T_Reg32 *) 0xF0002160)->bit5
#define CCU61_CMPSTAT_COUT60PS   ((T_Reg32 *) 0xF0002160)->bit9
#define CCU61_CMPSTAT_COUT61PS   ((T_Reg32 *) 0xF0002160)->bit11
#define CCU61_CMPSTAT_COUT62PS   ((T_Reg32 *) 0xF0002160)->bit13
#define CCU61_CMPSTAT_COUT63PS   ((T_Reg32 *) 0xF0002160)->bit14
#define CCU61_CMPSTAT_T13IM      ((T_Reg32 *) 0xF0002160)->bit15

// Module Identification Register
#define CCU61_ID               (*((uword volatile *) 0xF0002108))

// Capture/Compare Interrupt Enable Register
#define CCU61_IEN              (*((uword volatile *) 0xF000219C))
#define CCU61_IEN_ENCC60F        ((T_Reg32 *) 0xF000219C)->bit1
#define CCU61_IEN_ENCC60R        ((T_Reg32 *) 0xF000219C)->bit0
#define CCU61_IEN_ENCC61F        ((T_Reg32 *) 0xF000219C)->bit3
#define CCU61_IEN_ENCC61R        ((T_Reg32 *) 0xF000219C)->bit2
#define CCU61_IEN_ENCC62F        ((T_Reg32 *) 0xF000219C)->bit5
#define CCU61_IEN_ENCC62R        ((T_Reg32 *) 0xF000219C)->bit4
#define CCU61_IEN_ENCHE          ((T_Reg32 *) 0xF000219C)->bit12
#define CCU61_IEN_ENIDLE         ((T_Reg32 *) 0xF000219C)->bit14
#define CCU61_IEN_ENSTR          ((T_Reg32 *) 0xF000219C)->bit15
#define CCU61_IEN_ENT12OM        ((T_Reg32 *) 0xF000219C)->bit6
#define CCU61_IEN_ENT12PM        ((T_Reg32 *) 0xF000219C)->bit7
#define CCU61_IEN_ENT13CM        ((T_Reg32 *) 0xF000219C)->bit8
#define CCU61_IEN_ENT13PM        ((T_Reg32 *) 0xF000219C)->bit9
#define CCU61_IEN_ENTRPF         ((T_Reg32 *) 0xF000219C)->bit10
#define CCU61_IEN_ENWHE          ((T_Reg32 *) 0xF000219C)->bit13

// Capture/Compare Interrupt Node Pointer Register
#define CCU61_INP              (*((uword volatile *) 0xF00021A0))

// Capture/Compare Interrupt Status Register
#define CCU61_IS               (*((uword volatile *) 0xF0002190))
#define CCU61_IS_CHE             ((T_Reg32 *) 0xF0002190)->bit12
#define CCU61_IS_ICC60F          ((T_Reg32 *) 0xF0002190)->bit1
#define CCU61_IS_ICC60R          ((T_Reg32 *) 0xF0002190)->bit0
#define CCU61_IS_ICC61F          ((T_Reg32 *) 0xF0002190)->bit3
#define CCU61_IS_ICC61R          ((T_Reg32 *) 0xF0002190)->bit2
#define CCU61_IS_ICC62F          ((T_Reg32 *) 0xF0002190)->bit5
#define CCU61_IS_ICC62R          ((T_Reg32 *) 0xF0002190)->bit4
#define CCU61_IS_IDLE            ((T_Reg32 *) 0xF0002190)->bit14
#define CCU61_IS_STR             ((T_Reg32 *) 0xF0002190)->bit15
#define CCU61_IS_T12OM           ((T_Reg32 *) 0xF0002190)->bit6
#define CCU61_IS_T12PM           ((T_Reg32 *) 0xF0002190)->bit7
#define CCU61_IS_T13CM           ((T_Reg32 *) 0xF0002190)->bit8
#define CCU61_IS_T13PM           ((T_Reg32 *) 0xF0002190)->bit9
#define CCU61_IS_TRPF            ((T_Reg32 *) 0xF0002190)->bit10
#define CCU61_IS_TRPS            ((T_Reg32 *) 0xF0002190)->bit11
#define CCU61_IS_WHE             ((T_Reg32 *) 0xF0002190)->bit13

// Capture/Compare Interrupt Status Reset Register
#define CCU61_ISR              (*((uword volatile *) 0xF0002198))
#define CCU61_ISR_RCC60F         ((T_Reg32 *) 0xF0002198)->bit1
#define CCU61_ISR_RCC60R         ((T_Reg32 *) 0xF0002198)->bit0
#define CCU61_ISR_RCC61F         ((T_Reg32 *) 0xF0002198)->bit3
#define CCU61_ISR_RCC61R         ((T_Reg32 *) 0xF0002198)->bit2
#define CCU61_ISR_RCC62F         ((T_Reg32 *) 0xF0002198)->bit5
#define CCU61_ISR_RCC62R         ((T_Reg32 *) 0xF0002198)->bit4
#define CCU61_ISR_RCHE           ((T_Reg32 *) 0xF0002198)->bit12
#define CCU61_ISR_RIDLE          ((T_Reg32 *) 0xF0002198)->bit14
#define CCU61_ISR_RSTR           ((T_Reg32 *) 0xF0002198)->bit15
#define CCU61_ISR_RT12OM         ((T_Reg32 *) 0xF0002198)->bit6
#define CCU61_ISR_RT12PM         ((T_Reg32 *) 0xF0002198)->bit7
#define CCU61_ISR_RT13CM         ((T_Reg32 *) 0xF0002198)->bit8
#define CCU61_ISR_RT13PM         ((T_Reg32 *) 0xF0002198)->bit9
#define CCU61_ISR_RTRPF          ((T_Reg32 *) 0xF0002198)->bit10
#define CCU61_ISR_RWHE           ((T_Reg32 *) 0xF0002198)->bit13

// Capture/Compare Interrupt Status Set Register
#define CCU61_ISS              (*((uword volatile *) 0xF0002194))
#define CCU61_ISS_SCC60F         ((T_Reg32 *) 0xF0002194)->bit1
#define CCU61_ISS_SCC60R         ((T_Reg32 *) 0xF0002194)->bit0
#define CCU61_ISS_SCC61F         ((T_Reg32 *) 0xF0002194)->bit3
#define CCU61_ISS_SCC61R         ((T_Reg32 *) 0xF0002194)->bit2
#define CCU61_ISS_SCC62F         ((T_Reg32 *) 0xF0002194)->bit5
#define CCU61_ISS_SCC62R         ((T_Reg32 *) 0xF0002194)->bit4
#define CCU61_ISS_SCHE           ((T_Reg32 *) 0xF0002194)->bit12
#define CCU61_ISS_SIDLE          ((T_Reg32 *) 0xF0002194)->bit14
#define CCU61_ISS_SSTR           ((T_Reg32 *) 0xF0002194)->bit15
#define CCU61_ISS_ST12OM         ((T_Reg32 *) 0xF0002194)->bit6
#define CCU61_ISS_ST12PM         ((T_Reg32 *) 0xF0002194)->bit7
#define CCU61_ISS_ST13CM         ((T_Reg32 *) 0xF0002194)->bit8
#define CCU61_ISS_ST13PM         ((T_Reg32 *) 0xF0002194)->bit9
#define CCU61_ISS_STRPF          ((T_Reg32 *) 0xF0002194)->bit10
#define CCU61_ISS_SWHC           ((T_Reg32 *) 0xF0002194)->bit11
#define CCU61_ISS_SWHE           ((T_Reg32 *) 0xF0002194)->bit13

// Multi-Channel Mode Control Register
#define CCU61_MCMCTR           (*((uword volatile *) 0xF0002188))

// Multi-Channel Mode Output Register
#define CCU61_MCMOUT           (*((uword volatile *) 0xF0002184))
#define CCU61_MCMOUT_R           ((T_Reg32 *) 0xF0002184)->bit6

// Multi-Channel Mode Output Shadow Register
#define CCU61_MCMOUTS          (*((uword volatile *) 0xF0002180))
#define CCU61_MCMOUTS_STRHP      ((T_Reg32 *) 0xF0002180)->bit15
#define CCU61_MCMOUTS_STRMCM     ((T_Reg32 *) 0xF0002180)->bit7

// Modulation Control Register
#define CCU61_MODCTR           (*((uword volatile *) 0xF0002170))
#define CCU61_MODCTR_ECT13O      ((T_Reg32 *) 0xF0002170)->bit15
#define CCU61_MODCTR_MCMEN       ((T_Reg32 *) 0xF0002170)->bit7

// Port Input Select Register 0
#define CCU61_PISEL0           (*((uword volatile *) 0xF0002110))

// Port Input Select Register 2
#define CCU61_PISEL2           (*((uword volatile *) 0xF0002114))

// Passive State Level Register
#define CCU61_PSLR             (*((uword volatile *) 0xF0002178))
#define CCU61_PSLR_PSL63         ((T_Reg32 *) 0xF0002178)->bit7

// CCU60 Service Request Control Register 0
#define CCU61_SRC0             (*((uword volatile *) 0xF00021FC))
#define CCU61_SRC0_CLRR          ((T_Reg32 *) 0xF00021FC)->bit14
#define CCU61_SRC0_SETR          ((T_Reg32 *) 0xF00021FC)->bit15
#define CCU61_SRC0_SRE           ((T_Reg32 *) 0xF00021FC)->bit12
#define CCU61_SRC0_SRR           ((T_Reg32 *) 0xF00021FC)->bit13
#define CCU61_SRC0_TOS           ((T_Reg32 *) 0xF00021FC)->bit10

// CCU60 Service Request Control Register 1
#define CCU61_SRC1             (*((uword volatile *) 0xF00021F8))
#define CCU61_SRC1_CLRR          ((T_Reg32 *) 0xF00021F8)->bit14
#define CCU61_SRC1_SETR          ((T_Reg32 *) 0xF00021F8)->bit15
#define CCU61_SRC1_SRE           ((T_Reg32 *) 0xF00021F8)->bit12
#define CCU61_SRC1_SRR           ((T_Reg32 *) 0xF00021F8)->bit13
#define CCU61_SRC1_TOS           ((T_Reg32 *) 0xF00021F8)->bit10

// CCU60 Service Request Control Register 2
#define CCU61_SRC2             (*((uword volatile *) 0xF00021F4))
#define CCU61_SRC2_CLRR          ((T_Reg32 *) 0xF00021F4)->bit14
#define CCU61_SRC2_SETR          ((T_Reg32 *) 0xF00021F4)->bit15
#define CCU61_SRC2_SRE           ((T_Reg32 *) 0xF00021F4)->bit12
#define CCU61_SRC2_SRR           ((T_Reg32 *) 0xF00021F4)->bit13
#define CCU61_SRC2_TOS           ((T_Reg32 *) 0xF00021F4)->bit10

// CCU60 Service Request Control Register 3
#define CCU61_SRC3             (*((uword volatile *) 0xF00021F0))
#define CCU61_SRC3_CLRR          ((T_Reg32 *) 0xF00021F0)->bit14
#define CCU61_SRC3_SETR          ((T_Reg32 *) 0xF00021F0)->bit15
#define CCU61_SRC3_SRE           ((T_Reg32 *) 0xF00021F0)->bit12
#define CCU61_SRC3_SRR           ((T_Reg32 *) 0xF00021F0)->bit13
#define CCU61_SRC3_TOS           ((T_Reg32 *) 0xF00021F0)->bit10

// Timer T12 Counter Register
#define CCU61_T12              (*((uword volatile *) 0xF0002120))

// Dead-Time Control Register for Timer12
#define CCU61_T12DTC           (*((uword volatile *) 0xF0002128))
#define CCU61_T12DTC_DTE0        ((T_Reg32 *) 0xF0002128)->bit8
#define CCU61_T12DTC_DTE1        ((T_Reg32 *) 0xF0002128)->bit9
#define CCU61_T12DTC_DTE2        ((T_Reg32 *) 0xF0002128)->bit10
#define CCU61_T12DTC_DTR0        ((T_Reg32 *) 0xF0002128)->bit12
#define CCU61_T12DTC_DTR1        ((T_Reg32 *) 0xF0002128)->bit13
#define CCU61_T12DTC_DTR2        ((T_Reg32 *) 0xF0002128)->bit14

// T12 Capture/Compare Mode Select Register
#define CCU61_T12MSEL          (*((uword volatile *) 0xF000217C))
#define CCU61_T12MSEL_DBYP       ((T_Reg32 *) 0xF000217C)->bit15

// Timer T12 period register
#define CCU61_T12PR            (*((uword volatile *) 0xF0002124))

// Timer T13 Register
#define CCU61_T13              (*((uword volatile *) 0xF0002150))

// Timer T13 Period Register
#define CCU61_T13PR            (*((uword volatile *) 0xF0002154))

// Timer Control Register 0
#define CCU61_TCTR0            (*((uword volatile *) 0xF0002168))
#define CCU61_TCTR0_CDIR         ((T_Reg32 *) 0xF0002168)->bit6
#define CCU61_TCTR0_CTM          ((T_Reg32 *) 0xF0002168)->bit7
#define CCU61_TCTR0_STE12        ((T_Reg32 *) 0xF0002168)->bit5
#define CCU61_TCTR0_STE13        ((T_Reg32 *) 0xF0002168)->bit13
#define CCU61_TCTR0_T12PRE       ((T_Reg32 *) 0xF0002168)->bit3
#define CCU61_TCTR0_T12R         ((T_Reg32 *) 0xF0002168)->bit4
#define CCU61_TCTR0_T13PRE       ((T_Reg32 *) 0xF0002168)->bit11
#define CCU61_TCTR0_T13R         ((T_Reg32 *) 0xF0002168)->bit12

// Timer Control Register 2
#define CCU61_TCTR2            (*((uword volatile *) 0xF000216C))
#define CCU61_TCTR2_SUSCFG       ((T_Reg32 *) 0xF000216C)->bit7
#define CCU61_TCTR2_T12SSC       ((T_Reg32 *) 0xF000216C)->bit0
#define CCU61_TCTR2_T13SSC       ((T_Reg32 *) 0xF000216C)->bit1

// Timer Control Register 4
#define CCU61_TCTR4            (*((uword volatile *) 0xF000213C))
#define CCU61_TCTR4_DTRES        ((T_Reg32 *) 0xF000213C)->bit3
#define CCU61_TCTR4_T12RES       ((T_Reg32 *) 0xF000213C)->bit2
#define CCU61_TCTR4_T12RR        ((T_Reg32 *) 0xF000213C)->bit0
#define CCU61_TCTR4_T12RS        ((T_Reg32 *) 0xF000213C)->bit1
#define CCU61_TCTR4_T12STD       ((T_Reg32 *) 0xF000213C)->bit7
#define CCU61_TCTR4_T12STR       ((T_Reg32 *) 0xF000213C)->bit6
#define CCU61_TCTR4_T13RES       ((T_Reg32 *) 0xF000213C)->bit10
#define CCU61_TCTR4_T13RR        ((T_Reg32 *) 0xF000213C)->bit8
#define CCU61_TCTR4_T13RS        ((T_Reg32 *) 0xF000213C)->bit9
#define CCU61_TCTR4_T13STD       ((T_Reg32 *) 0xF000213C)->bit15
#define CCU61_TCTR4_T13STR       ((T_Reg32 *) 0xF000213C)->bit14

// Trap Control Register
#define CCU61_TRPCTR           (*((uword volatile *) 0xF0002174))
#define CCU61_TRPCTR_TRPEN13     ((T_Reg32 *) 0xF0002174)->bit14
#define CCU61_TRPCTR_TRPM0       ((T_Reg32 *) 0xF0002174)->bit0
#define CCU61_TRPCTR_TRPM1       ((T_Reg32 *) 0xF0002174)->bit1
#define CCU61_TRPCTR_TRPM2       ((T_Reg32 *) 0xF0002174)->bit2
#define CCU61_TRPCTR_TRPPEN      ((T_Reg32 *) 0xF0002174)->bit15

// Chip Identification Register
#define CHIPID                 (*((uword volatile *) 0xF0000074))

// Code Memory Protection Mode Register 0
#define CPM0                   (*((uword volatile *) 0xF7E1E200))
#define CPM0_BL0                 0x00000008
#define CPM0_BL1                 0x00000800
#define CPM0_BU0                 0x00000001
#define CPM0_BU1                 0x00000100
#define CPM0_XE0                 0x00000080
#define CPM0_XE1                 0x00008000
#define CPM0_XS0                 0x00000020
#define CPM0_XS1                 0x00002000

// Code Memory Protection Mode Register 1
#define CPM1                   (*((uword volatile *) 0xF7E1E280))
#define CPM1_BL0                 0x00000008
#define CPM1_BL1                 0x00000800
#define CPM1_BU0                 0x00000001
#define CPM1_BU1                 0x00000100
#define CPM1_XE0                 0x00000080
#define CPM1_XE1                 0x00008000
#define CPM1_XS0                 0x00000020
#define CPM1_XS1                 0x00002000

// Code Segment Protection Register Set 0, Range 0, Lower
#define CPR0_0L                (*((uword volatile *) 0xF7E1D000))

// Code Segment Protection Register Set 0, Range 0, Upper
#define CPR0_0U                (*((uword volatile *) 0xF7E1D004))

// Code Segment Protection Register Set 0, Range 1, Lower
#define CPR0_1L                (*((uword volatile *) 0xF7E1D008))

// Code Segment Protection Register Set 0, Range 1, Upper
#define CPR0_1U                (*((uword volatile *) 0xF7E1D00C))

// Code Segment Protection Register Set 1, Range 0, Lower
#define CPR1_0L                (*((uword volatile *) 0xF7E1D400))

// Code Segment Protection Register Set 1, Range 0, Upper
#define CPR1_0U                (*((uword volatile *) 0xF7E1D404))

// Code Segment Protection Register Set 1, Range 1, Lower
#define CPR1_1L                (*((uword volatile *) 0xF7E1D408))

// Code Segment Protection Register Set 1, Range 1, Upper
#define CPR1_1U                (*((uword volatile *) 0xF7E1D40C))

// CPS Module Identification Register
#define CPS_ID                 (*((uword volatile *) 0xF7E0FF08))

// CPU Identification Register
#define CPU_ID                 (*((uword volatile *) 0xF7E1FE18))

// Software Break Service Request Control Register
#define CPU_SBSRC              (*((uword volatile *) 0xF7E0FFBC))
#define CPU_SBSRC_CLRR           0x00004000
#define CPU_SBSRC_SETR           0x00008000
#define CPU_SBSRC_SRE            0x00001000
#define CPU_SBSRC_SRR            0x00002000
#define CPU_SBSRC_TOS            0x00000400

// CPU Service Request Control Register 0
#define CPU_SRC0               (*((uword volatile *) 0xF7E0FFFC))
#define CPU_SRC0_CLRR            0x00004000
#define CPU_SRC0_SETR            0x00008000
#define CPU_SRC0_SRE             0x00001000
#define CPU_SRC0_SRR             0x00002000
#define CPU_SRC0_TOS             0x00000400

// CPU Service Request Control Register 1
#define CPU_SRC1               (*((uword volatile *) 0xF7E0FFF8))
#define CPU_SRC1_CLRR            0x00004000
#define CPU_SRC1_SETR            0x00008000
#define CPU_SRC1_SRE             0x00001000
#define CPU_SRC1_SRR             0x00002000
#define CPU_SRC1_TOS             0x00000400

// CPU Service Request Control Register 2
#define CPU_SRC2               (*((uword volatile *) 0xF7E0FFF4))
#define CPU_SRC2_CLRR            0x00004000
#define CPU_SRC2_SETR            0x00008000
#define CPU_SRC2_SRE             0x00001000
#define CPU_SRC2_SRR             0x00002000
#define CPU_SRC2_TOS             0x00000400

// CPU Service Request Control Register 3
#define CPU_SRC3               (*((uword volatile *) 0xF7E0FFF0))
#define CPU_SRC3_CLRR            0x00004000
#define CPU_SRC3_SETR            0x00008000
#define CPU_SRC3_SRE             0x00001000
#define CPU_SRC3_SRR             0x00002000
#define CPU_SRC3_TOS             0x00000400

// Core SFR Access Break Event Specifier Register
#define CREVT                  (*((uword volatile *) 0xF7E1FD0C))
#define CREVT_BBM                0x00000008
#define CREVT_SUSP               0x00000020

// Data Register D0 (DGPR)
#define D0                     (*((uword volatile *) 0xF7E1FF00))

// Data Register D1 (DGPR)
#define D1                     (*((uword volatile *) 0xF7E1FF04))

// Data Register D10 (DGPR)
#define D10                    (*((uword volatile *) 0xF7E1FF28))

// Data Register D11 (DGPR)
#define D11                    (*((uword volatile *) 0xF7E1FF2C))

// Data Register D12 (DGPR)
#define D12                    (*((uword volatile *) 0xF7E1FF30))

// Data Register D13 (DGPR)
#define D13                    (*((uword volatile *) 0xF7E1FF34))

// Data Register D14 (DGPR)
#define D14                    (*((uword volatile *) 0xF7E1FF38))

// Data Register D15 (DGPR)
#define D15                    (*((uword volatile *) 0xF7E1FF3C))

// Data Register D2 (DGPR)
#define D2                     (*((uword volatile *) 0xF7E1FF08))

// Data Register D3 (DGPR)
#define D3                     (*((uword volatile *) 0xF7E1FF0C))

// Data Register D4 (DGPR)
#define D4                     (*((uword volatile *) 0xF7E1FF10))

// Data Register D5 (DGPR)
#define D5                     (*((uword volatile *) 0xF7E1FF14))

// Data Register D6 (DGPR)
#define D6                     (*((uword volatile *) 0xF7E1FF18))

// Data Register D7 (DGPR)
#define D7                     (*((uword volatile *) 0xF7E1FF1C))

// Data Register D8 (DGPR)
#define D8                     (*((uword volatile *) 0xF7E1FF20))

// Data Register D9 (DGPR)
#define D9                     (*((uword volatile *) 0xF7E1FF24))

// Debug Status Register
#define DBGSR                  (*((uword volatile *) 0xF7E1FD00))
#define DBGSR_DE                 0x00000001
#define DBGSR_PEVT               0x00000080
#define DBGSR_PREVSUSP           0x00000040
#define DBGSR_SUSP               0x00000010

// Debug Context Save Area Pointer
#define DCX                    (*((uword volatile *) 0xF7E1FD44))

// DMA Channel 00 Address Control Register
#define DMA_ADRCR00            (*((uword volatile *) 0xF0003C8C))
#define DMA_ADRCR00_INCD         ((T_Reg32 *) 0xF0003C8C)->bit7
#define DMA_ADRCR00_INCS         ((T_Reg32 *) 0xF0003C8C)->bit3

// DMA Channel 01 Address Control Register
#define DMA_ADRCR01            (*((uword volatile *) 0xF0003CAC))
#define DMA_ADRCR01_INCD         ((T_Reg32 *) 0xF0003CAC)->bit7
#define DMA_ADRCR01_INCS         ((T_Reg32 *) 0xF0003CAC)->bit3

// DMA Channel 02 Address Control Register
#define DMA_ADRCR02            (*((uword volatile *) 0xF0003CCC))
#define DMA_ADRCR02_INCD         ((T_Reg32 *) 0xF0003CCC)->bit7
#define DMA_ADRCR02_INCS         ((T_Reg32 *) 0xF0003CCC)->bit3

// DMA Channel 03 Address Control Register
#define DMA_ADRCR03            (*((uword volatile *) 0xF0003CEC))
#define DMA_ADRCR03_INCD         ((T_Reg32 *) 0xF0003CEC)->bit7
#define DMA_ADRCR03_INCS         ((T_Reg32 *) 0xF0003CEC)->bit3

// DMA Channel 04 Address Control Register
#define DMA_ADRCR04            (*((uword volatile *) 0xF0003D0C))
#define DMA_ADRCR04_INCD         ((T_Reg32 *) 0xF0003D0C)->bit7
#define DMA_ADRCR04_INCS         ((T_Reg32 *) 0xF0003D0C)->bit3

// DMA Channel 05 Address Control Register
#define DMA_ADRCR05            (*((uword volatile *) 0xF0003D2C))
#define DMA_ADRCR05_INCD         ((T_Reg32 *) 0xF0003D2C)->bit7
#define DMA_ADRCR05_INCS         ((T_Reg32 *) 0xF0003D2C)->bit3

// DMA Channel 06 Address Control Register
#define DMA_ADRCR06            (*((uword volatile *) 0xF0003D4C))
#define DMA_ADRCR06_INCD         ((T_Reg32 *) 0xF0003D4C)->bit7
#define DMA_ADRCR06_INCS         ((T_Reg32 *) 0xF0003D4C)->bit3

// DMA Channel 07 Address Control Register
#define DMA_ADRCR07            (*((uword volatile *) 0xF0003D6C))
#define DMA_ADRCR07_INCD         ((T_Reg32 *) 0xF0003D6C)->bit7
#define DMA_ADRCR07_INCS         ((T_Reg32 *) 0xF0003D6C)->bit3

// DMA Channel 00 Control Register
#define DMA_CHCR00             (*((uword volatile *) 0xF0003C84))
#define DMA_CHCR00_CHMODE        ((T_Reg32 *) 0xF0003C84)->bit20
#define DMA_CHCR00_CHPRIO        ((T_Reg32 *) 0xF0003C84)->bit28
#define DMA_CHCR00_DMAPRIO       ((T_Reg32 *) 0xF0003C84)->bit30
#define DMA_CHCR00_RROAT         ((T_Reg32 *) 0xF0003C84)->bit19

// DMA Channel 01 Control Register
#define DMA_CHCR01             (*((uword volatile *) 0xF0003CA4))
#define DMA_CHCR01_CHMODE        ((T_Reg32 *) 0xF0003CA4)->bit20
#define DMA_CHCR01_CHPRIO        ((T_Reg32 *) 0xF0003CA4)->bit28
#define DMA_CHCR01_DMAPRIO       ((T_Reg32 *) 0xF0003CA4)->bit30
#define DMA_CHCR01_RROAT         ((T_Reg32 *) 0xF0003CA4)->bit19

// DMA Channel 02 Control Register
#define DMA_CHCR02             (*((uword volatile *) 0xF0003CC4))
#define DMA_CHCR02_CHMODE        ((T_Reg32 *) 0xF0003CC4)->bit20
#define DMA_CHCR02_CHPRIO        ((T_Reg32 *) 0xF0003CC4)->bit28
#define DMA_CHCR02_DMAPRIO       ((T_Reg32 *) 0xF0003CC4)->bit30
#define DMA_CHCR02_RROAT         ((T_Reg32 *) 0xF0003CC4)->bit19

// DMA Channel 03 Control Register
#define DMA_CHCR03             (*((uword volatile *) 0xF0003CE4))
#define DMA_CHCR03_CHMODE        ((T_Reg32 *) 0xF0003CE4)->bit20
#define DMA_CHCR03_CHPRIO        ((T_Reg32 *) 0xF0003CE4)->bit28
#define DMA_CHCR03_DMAPRIO       ((T_Reg32 *) 0xF0003CE4)->bit30
#define DMA_CHCR03_RROAT         ((T_Reg32 *) 0xF0003CE4)->bit19

// DMA Channel 04 Control Register
#define DMA_CHCR04             (*((uword volatile *) 0xF0003D04))
#define DMA_CHCR04_CHMODE        ((T_Reg32 *) 0xF0003D04)->bit20
#define DMA_CHCR04_CHPRIO        ((T_Reg32 *) 0xF0003D04)->bit28
#define DMA_CHCR04_DMAPRIO       ((T_Reg32 *) 0xF0003D04)->bit30
#define DMA_CHCR04_RROAT         ((T_Reg32 *) 0xF0003D04)->bit19

// DMA Channel 05 Control Register
#define DMA_CHCR05             (*((uword volatile *) 0xF0003D24))
#define DMA_CHCR05_CHMODE        ((T_Reg32 *) 0xF0003D24)->bit20
#define DMA_CHCR05_CHPRIO        ((T_Reg32 *) 0xF0003D24)->bit28
#define DMA_CHCR05_DMAPRIO       ((T_Reg32 *) 0xF0003D24)->bit30
#define DMA_CHCR05_RROAT         ((T_Reg32 *) 0xF0003D24)->bit19

// DMA Channel 06 Control Register
#define DMA_CHCR06             (*((uword volatile *) 0xF0003D44))
#define DMA_CHCR06_CHMODE        ((T_Reg32 *) 0xF0003D44)->bit20
#define DMA_CHCR06_CHPRIO        ((T_Reg32 *) 0xF0003D44)->bit28
#define DMA_CHCR06_DMAPRIO       ((T_Reg32 *) 0xF0003D44)->bit30
#define DMA_CHCR06_RROAT         ((T_Reg32 *) 0xF0003D44)->bit19

// DMA Channel 07 Control Register
#define DMA_CHCR07             (*((uword volatile *) 0xF0003D64))
#define DMA_CHCR07_CHMODE        ((T_Reg32 *) 0xF0003D64)->bit20
#define DMA_CHCR07_CHPRIO        ((T_Reg32 *) 0xF0003D64)->bit28
#define DMA_CHCR07_DMAPRIO       ((T_Reg32 *) 0xF0003D64)->bit30
#define DMA_CHCR07_RROAT         ((T_Reg32 *) 0xF0003D64)->bit19

// DMA Channel 00 Interrupt Control Register
#define DMA_CHICR00            (*((uword volatile *) 0xF0003C88))
#define DMA_CHICR00_WRPDE        ((T_Reg32 *) 0xF0003C88)->bit1
#define DMA_CHICR00_WRPSE        ((T_Reg32 *) 0xF0003C88)->bit0

// DMA Channel 01 Interrupt Control Register
#define DMA_CHICR01            (*((uword volatile *) 0xF0003CA8))
#define DMA_CHICR01_WRPDE        ((T_Reg32 *) 0xF0003CA8)->bit1
#define DMA_CHICR01_WRPSE        ((T_Reg32 *) 0xF0003CA8)->bit0

// DMA Channel 02 Interrupt Control Register
#define DMA_CHICR02            (*((uword volatile *) 0xF0003CC8))
#define DMA_CHICR02_WRPDE        ((T_Reg32 *) 0xF0003CC8)->bit1
#define DMA_CHICR02_WRPSE        ((T_Reg32 *) 0xF0003CC8)->bit0

// DMA Channel 03 Interrupt Control Register
#define DMA_CHICR03            (*((uword volatile *) 0xF0003CE8))
#define DMA_CHICR03_WRPDE        ((T_Reg32 *) 0xF0003CE8)->bit1
#define DMA_CHICR03_WRPSE        ((T_Reg32 *) 0xF0003CE8)->bit0

// DMA Channel 04 Interrupt Control Register
#define DMA_CHICR04            (*((uword volatile *) 0xF0003D08))
#define DMA_CHICR04_WRPDE        ((T_Reg32 *) 0xF0003D08)->bit1
#define DMA_CHICR04_WRPSE        ((T_Reg32 *) 0xF0003D08)->bit0

// DMA Channel 05 Interrupt Control Register
#define DMA_CHICR05            (*((uword volatile *) 0xF0003D28))
#define DMA_CHICR05_WRPDE        ((T_Reg32 *) 0xF0003D28)->bit1
#define DMA_CHICR05_WRPSE        ((T_Reg32 *) 0xF0003D28)->bit0

// DMA Channel 06 Interrupt Control Register
#define DMA_CHICR06            (*((uword volatile *) 0xF0003D48))
#define DMA_CHICR06_WRPDE        ((T_Reg32 *) 0xF0003D48)->bit1
#define DMA_CHICR06_WRPSE        ((T_Reg32 *) 0xF0003D48)->bit0

// DMA Channel 07 Interrupt Control Register
#define DMA_CHICR07            (*((uword volatile *) 0xF0003D68))
#define DMA_CHICR07_WRPDE        ((T_Reg32 *) 0xF0003D68)->bit1
#define DMA_CHICR07_WRPSE        ((T_Reg32 *) 0xF0003D68)->bit0

// Channel Reset Request Register
#define DMA_CHRSTR             (*((uword volatile *) 0xF0003C10))
#define DMA_CHRSTR_CH00          ((T_Reg32 *) 0xF0003C10)->bit0
#define DMA_CHRSTR_CH01          ((T_Reg32 *) 0xF0003C10)->bit1
#define DMA_CHRSTR_CH02          ((T_Reg32 *) 0xF0003C10)->bit2
#define DMA_CHRSTR_CH03          ((T_Reg32 *) 0xF0003C10)->bit3
#define DMA_CHRSTR_CH04          ((T_Reg32 *) 0xF0003C10)->bit4
#define DMA_CHRSTR_CH05          ((T_Reg32 *) 0xF0003C10)->bit5
#define DMA_CHRSTR_CH06          ((T_Reg32 *) 0xF0003C10)->bit6
#define DMA_CHRSTR_CH07          ((T_Reg32 *) 0xF0003C10)->bit7

// Channel 00 Status Register
#define DMA_CHSR00             (*((uword volatile *) 0xF0003C80))
#define DMA_CHSR00_LXO           ((T_Reg32 *) 0xF0003C80)->bit15

// DMA Channel 01 Status Register
#define DMA_CHSR01             (*((uword volatile *) 0xF0003CA0))
#define DMA_CHSR01_LXO           ((T_Reg32 *) 0xF0003CA0)->bit15

// DMA Channel 02 Status Register
#define DMA_CHSR02             (*((uword volatile *) 0xF0003CC0))
#define DMA_CHSR02_LXO           ((T_Reg32 *) 0xF0003CC0)->bit15

// DMA Channel 03 Status Register
#define DMA_CHSR03             (*((uword volatile *) 0xF0003CE0))
#define DMA_CHSR03_LXO           ((T_Reg32 *) 0xF0003CE0)->bit15

// DMA Channel 04 Status Register
#define DMA_CHSR04             (*((uword volatile *) 0xF0003D00))
#define DMA_CHSR04_LXO           ((T_Reg32 *) 0xF0003D00)->bit15

// DMA Channel 05 Status Register
#define DMA_CHSR05             (*((uword volatile *) 0xF0003D20))
#define DMA_CHSR05_LXO           ((T_Reg32 *) 0xF0003D20)->bit15

// DMA Channel 06 Status Register
#define DMA_CHSR06             (*((uword volatile *) 0xF0003D40))
#define DMA_CHSR06_LXO           ((T_Reg32 *) 0xF0003D40)->bit15

// DMA Channel 07 Status Register
#define DMA_CHSR07             (*((uword volatile *) 0xF0003D60))
#define DMA_CHSR07_LXO           ((T_Reg32 *) 0xF0003D60)->bit15

// DMA Clock Control Register
#define DMA_CLC                (*((uword volatile *) 0xF0003C00))
#define DMA_CLC_DISR             ((T_Reg32 *) 0xF0003C00)->bit0
#define DMA_CLC_DISS             ((T_Reg32 *) 0xF0003C00)->bit1
#define DMA_CLC_FSOE             ((T_Reg32 *) 0xF0003C00)->bit5
#define DMA_CLC_SBWE             ((T_Reg32 *) 0xF0003C00)->bit4
#define DMA_CLC_SPEN             ((T_Reg32 *) 0xF0003C00)->bit2

// Clear Error Register
#define DMA_CLRE               (*((uword volatile *) 0xF0003C28))
#define DMA_CLRE_CFPI0ER         ((T_Reg32 *) 0xF0003C28)->bit20
#define DMA_CLRE_CFPI1ER         ((T_Reg32 *) 0xF0003C28)->bit21
#define DMA_CLRE_CLRMLI0         ((T_Reg32 *) 0xF0003C28)->bit27
#define DMA_CLRE_CLRMLI1         ((T_Reg32 *) 0xF0003C28)->bit31
#define DMA_CLRE_CME0DER         ((T_Reg32 *) 0xF0003C28)->bit17
#define DMA_CLRE_CME0SER         ((T_Reg32 *) 0xF0003C28)->bit16
#define DMA_CLRE_CTRL00          ((T_Reg32 *) 0xF0003C28)->bit0
#define DMA_CLRE_CTRL01          ((T_Reg32 *) 0xF0003C28)->bit1
#define DMA_CLRE_CTRL02          ((T_Reg32 *) 0xF0003C28)->bit2
#define DMA_CLRE_CTRL03          ((T_Reg32 *) 0xF0003C28)->bit3
#define DMA_CLRE_CTRL04          ((T_Reg32 *) 0xF0003C28)->bit4
#define DMA_CLRE_CTRL05          ((T_Reg32 *) 0xF0003C28)->bit5
#define DMA_CLRE_CTRL06          ((T_Reg32 *) 0xF0003C28)->bit6
#define DMA_CLRE_CTRL07          ((T_Reg32 *) 0xF0003C28)->bit7

// DMA Channel 00 Destination Address Register
#define DMA_DADR00             (*((uword volatile *) 0xF0003C94))

// DMA Channel 01 Destination Address Register
#define DMA_DADR01             (*((uword volatile *) 0xF0003CB4))

// DMA Channel 02 Destination Address Register
#define DMA_DADR02             (*((uword volatile *) 0xF0003CD4))

// DMA Channel 03 Destination Address Register
#define DMA_DADR03             (*((uword volatile *) 0xF0003CF4))

// DMA Channel 04 Destination Address Register
#define DMA_DADR04             (*((uword volatile *) 0xF0003D14))

// DMA Channel 05 Destination Address Register
#define DMA_DADR05             (*((uword volatile *) 0xF0003D34))

// DMA Channel 06 Destination Address Register
#define DMA_DADR06             (*((uword volatile *) 0xF0003D54))

// DMA Channel 07 Destination Address Register
#define DMA_DADR07             (*((uword volatile *) 0xF0003D74))

// Enable Error Register
#define DMA_EER                (*((uword volatile *) 0xF0003C20))
#define DMA_EER_EME0DER          ((T_Reg32 *) 0xF0003C20)->bit17
#define DMA_EER_EME0SER          ((T_Reg32 *) 0xF0003C20)->bit16
#define DMA_EER_ETRL00           ((T_Reg32 *) 0xF0003C20)->bit0
#define DMA_EER_ETRL01           ((T_Reg32 *) 0xF0003C20)->bit1
#define DMA_EER_ETRL02           ((T_Reg32 *) 0xF0003C20)->bit2
#define DMA_EER_ETRL03           ((T_Reg32 *) 0xF0003C20)->bit3
#define DMA_EER_ETRL04           ((T_Reg32 *) 0xF0003C20)->bit4
#define DMA_EER_ETRL05           ((T_Reg32 *) 0xF0003C20)->bit5
#define DMA_EER_ETRL06           ((T_Reg32 *) 0xF0003C20)->bit6
#define DMA_EER_ETRL07           ((T_Reg32 *) 0xF0003C20)->bit7

// Error Status Register
#define DMA_ERRSR              (*((uword volatile *) 0xF0003C24))
#define DMA_ERRSR_FPI0ER         ((T_Reg32 *) 0xF0003C24)->bit20
#define DMA_ERRSR_FPI1ER         ((T_Reg32 *) 0xF0003C24)->bit21
#define DMA_ERRSR_ME0DER         ((T_Reg32 *) 0xF0003C24)->bit17
#define DMA_ERRSR_ME0SER         ((T_Reg32 *) 0xF0003C24)->bit16
#define DMA_ERRSR_MLI0           ((T_Reg32 *) 0xF0003C24)->bit27
#define DMA_ERRSR_MLI1           ((T_Reg32 *) 0xF0003C24)->bit31
#define DMA_ERRSR_TRL00          ((T_Reg32 *) 0xF0003C24)->bit0
#define DMA_ERRSR_TRL01          ((T_Reg32 *) 0xF0003C24)->bit1
#define DMA_ERRSR_TRL02          ((T_Reg32 *) 0xF0003C24)->bit2
#define DMA_ERRSR_TRL03          ((T_Reg32 *) 0xF0003C24)->bit3
#define DMA_ERRSR_TRL04          ((T_Reg32 *) 0xF0003C24)->bit4
#define DMA_ERRSR_TRL05          ((T_Reg32 *) 0xF0003C24)->bit5
#define DMA_ERRSR_TRL06          ((T_Reg32 *) 0xF0003C24)->bit6
#define DMA_ERRSR_TRL07          ((T_Reg32 *) 0xF0003C24)->bit7

// DMA Global Interrupt Set Register
#define DMA_GINTR              (*((uword volatile *) 0xF0003C2C))
#define DMA_GINTR_SIDMA0         ((T_Reg32 *) 0xF0003C2C)->bit0
#define DMA_GINTR_SIDMA1         ((T_Reg32 *) 0xF0003C2C)->bit1
#define DMA_GINTR_SIDMA10        ((T_Reg32 *) 0xF0003C2C)->bit10
#define DMA_GINTR_SIDMA11        ((T_Reg32 *) 0xF0003C2C)->bit11
#define DMA_GINTR_SIDMA12        ((T_Reg32 *) 0xF0003C2C)->bit12
#define DMA_GINTR_SIDMA13        ((T_Reg32 *) 0xF0003C2C)->bit13
#define DMA_GINTR_SIDMA14        ((T_Reg32 *) 0xF0003C2C)->bit14
#define DMA_GINTR_SIDMA15        ((T_Reg32 *) 0xF0003C2C)->bit15
#define DMA_GINTR_SIDMA2         ((T_Reg32 *) 0xF0003C2C)->bit2
#define DMA_GINTR_SIDMA3         ((T_Reg32 *) 0xF0003C2C)->bit3
#define DMA_GINTR_SIDMA4         ((T_Reg32 *) 0xF0003C2C)->bit4
#define DMA_GINTR_SIDMA5         ((T_Reg32 *) 0xF0003C2C)->bit5
#define DMA_GINTR_SIDMA6         ((T_Reg32 *) 0xF0003C2C)->bit6
#define DMA_GINTR_SIDMA7         ((T_Reg32 *) 0xF0003C2C)->bit7
#define DMA_GINTR_SIDMA8         ((T_Reg32 *) 0xF0003C2C)->bit8
#define DMA_GINTR_SIDMA9         ((T_Reg32 *) 0xF0003C2C)->bit9

// Hardware Transaction Request Register
#define DMA_HTREQ              (*((uword volatile *) 0xF0003C1C))
#define DMA_HTREQ_DCH00          ((T_Reg32 *) 0xF0003C1C)->bit16
#define DMA_HTREQ_DCH01          ((T_Reg32 *) 0xF0003C1C)->bit17
#define DMA_HTREQ_DCH02          ((T_Reg32 *) 0xF0003C1C)->bit18
#define DMA_HTREQ_DCH03          ((T_Reg32 *) 0xF0003C1C)->bit19
#define DMA_HTREQ_DCH04          ((T_Reg32 *) 0xF0003C1C)->bit20
#define DMA_HTREQ_DCH05          ((T_Reg32 *) 0xF0003C1C)->bit21
#define DMA_HTREQ_DCH06          ((T_Reg32 *) 0xF0003C1C)->bit22
#define DMA_HTREQ_DCH07          ((T_Reg32 *) 0xF0003C1C)->bit23
#define DMA_HTREQ_ECH00          ((T_Reg32 *) 0xF0003C1C)->bit0
#define DMA_HTREQ_ECH01          ((T_Reg32 *) 0xF0003C1C)->bit1
#define DMA_HTREQ_ECH02          ((T_Reg32 *) 0xF0003C1C)->bit2
#define DMA_HTREQ_ECH03          ((T_Reg32 *) 0xF0003C1C)->bit3
#define DMA_HTREQ_ECH04          ((T_Reg32 *) 0xF0003C1C)->bit4
#define DMA_HTREQ_ECH05          ((T_Reg32 *) 0xF0003C1C)->bit5
#define DMA_HTREQ_ECH06          ((T_Reg32 *) 0xF0003C1C)->bit6
#define DMA_HTREQ_ECH07          ((T_Reg32 *) 0xF0003C1C)->bit7

// DMA Module Identification Register
#define DMA_ID                 (*((uword volatile *) 0xF0003C08))

// Interrupt Clear Register
#define DMA_INTCR              (*((uword volatile *) 0xF0003C58))
#define DMA_INTCR_CICH00         ((T_Reg32 *) 0xF0003C58)->bit0
#define DMA_INTCR_CICH01         ((T_Reg32 *) 0xF0003C58)->bit1
#define DMA_INTCR_CICH02         ((T_Reg32 *) 0xF0003C58)->bit2
#define DMA_INTCR_CICH03         ((T_Reg32 *) 0xF0003C58)->bit3
#define DMA_INTCR_CICH04         ((T_Reg32 *) 0xF0003C58)->bit4
#define DMA_INTCR_CICH05         ((T_Reg32 *) 0xF0003C58)->bit5
#define DMA_INTCR_CICH06         ((T_Reg32 *) 0xF0003C58)->bit6
#define DMA_INTCR_CICH07         ((T_Reg32 *) 0xF0003C58)->bit7
#define DMA_INTCR_CWRP00         ((T_Reg32 *) 0xF0003C58)->bit16
#define DMA_INTCR_CWRP01         ((T_Reg32 *) 0xF0003C58)->bit17
#define DMA_INTCR_CWRP02         ((T_Reg32 *) 0xF0003C58)->bit18
#define DMA_INTCR_CWRP03         ((T_Reg32 *) 0xF0003C58)->bit19
#define DMA_INTCR_CWRP04         ((T_Reg32 *) 0xF0003C58)->bit20
#define DMA_INTCR_CWRP05         ((T_Reg32 *) 0xF0003C58)->bit21
#define DMA_INTCR_CWRP06         ((T_Reg32 *) 0xF0003C58)->bit22
#define DMA_INTCR_CWRP07         ((T_Reg32 *) 0xF0003C58)->bit23

// Interrupt Status Register
#define DMA_INTSR              (*((uword volatile *) 0xF0003C54))
#define DMA_INTSR_ICH00          ((T_Reg32 *) 0xF0003C54)->bit0
#define DMA_INTSR_ICH01          ((T_Reg32 *) 0xF0003C54)->bit1
#define DMA_INTSR_ICH02          ((T_Reg32 *) 0xF0003C54)->bit2
#define DMA_INTSR_ICH03          ((T_Reg32 *) 0xF0003C54)->bit3
#define DMA_INTSR_ICH04          ((T_Reg32 *) 0xF0003C54)->bit4
#define DMA_INTSR_ICH05          ((T_Reg32 *) 0xF0003C54)->bit5
#define DMA_INTSR_ICH06          ((T_Reg32 *) 0xF0003C54)->bit6
#define DMA_INTSR_ICH07          ((T_Reg32 *) 0xF0003C54)->bit7
#define DMA_INTSR_PD00           ((T_Reg32 *) 0xF0003C54)->bit16
#define DMA_INTSR_PD01           ((T_Reg32 *) 0xF0003C54)->bit17
#define DMA_INTSR_PD02           ((T_Reg32 *) 0xF0003C54)->bit18
#define DMA_INTSR_PD03           ((T_Reg32 *) 0xF0003C54)->bit19
#define DMA_INTSR_PD04           ((T_Reg32 *) 0xF0003C54)->bit20
#define DMA_INTSR_PD05           ((T_Reg32 *) 0xF0003C54)->bit21
#define DMA_INTSR_PD06           ((T_Reg32 *) 0xF0003C54)->bit22
#define DMA_INTSR_PD07           ((T_Reg32 *) 0xF0003C54)->bit23

// Move Engine 0 Access Enable Register
#define DMA_ME0AENR            (*((uword volatile *) 0xF0003C44))
#define DMA_ME0AENR_AEN0         ((T_Reg32 *) 0xF0003C44)->bit0
#define DMA_ME0AENR_AEN1         ((T_Reg32 *) 0xF0003C44)->bit1
#define DMA_ME0AENR_AEN10        ((T_Reg32 *) 0xF0003C44)->bit10
#define DMA_ME0AENR_AEN11        ((T_Reg32 *) 0xF0003C44)->bit11
#define DMA_ME0AENR_AEN12        ((T_Reg32 *) 0xF0003C44)->bit12
#define DMA_ME0AENR_AEN13        ((T_Reg32 *) 0xF0003C44)->bit13
#define DMA_ME0AENR_AEN14        ((T_Reg32 *) 0xF0003C44)->bit14
#define DMA_ME0AENR_AEN15        ((T_Reg32 *) 0xF0003C44)->bit15
#define DMA_ME0AENR_AEN16        ((T_Reg32 *) 0xF0003C44)->bit16
#define DMA_ME0AENR_AEN17        ((T_Reg32 *) 0xF0003C44)->bit17
#define DMA_ME0AENR_AEN18        ((T_Reg32 *) 0xF0003C44)->bit18
#define DMA_ME0AENR_AEN19        ((T_Reg32 *) 0xF0003C44)->bit19
#define DMA_ME0AENR_AEN2         ((T_Reg32 *) 0xF0003C44)->bit2
#define DMA_ME0AENR_AEN20        ((T_Reg32 *) 0xF0003C44)->bit20
#define DMA_ME0AENR_AEN21        ((T_Reg32 *) 0xF0003C44)->bit21
#define DMA_ME0AENR_AEN22        ((T_Reg32 *) 0xF0003C44)->bit22
#define DMA_ME0AENR_AEN23        ((T_Reg32 *) 0xF0003C44)->bit23
#define DMA_ME0AENR_AEN24        ((T_Reg32 *) 0xF0003C44)->bit24
#define DMA_ME0AENR_AEN25        ((T_Reg32 *) 0xF0003C44)->bit25
#define DMA_ME0AENR_AEN26        ((T_Reg32 *) 0xF0003C44)->bit26
#define DMA_ME0AENR_AEN27        ((T_Reg32 *) 0xF0003C44)->bit27
#define DMA_ME0AENR_AEN28        ((T_Reg32 *) 0xF0003C44)->bit28
#define DMA_ME0AENR_AEN29        ((T_Reg32 *) 0xF0003C44)->bit29
#define DMA_ME0AENR_AEN3         ((T_Reg32 *) 0xF0003C44)->bit3
#define DMA_ME0AENR_AEN30        ((T_Reg32 *) 0xF0003C44)->bit30
#define DMA_ME0AENR_AEN31        ((T_Reg32 *) 0xF0003C44)->bit31
#define DMA_ME0AENR_AEN4         ((T_Reg32 *) 0xF0003C44)->bit4
#define DMA_ME0AENR_AEN5         ((T_Reg32 *) 0xF0003C44)->bit5
#define DMA_ME0AENR_AEN6         ((T_Reg32 *) 0xF0003C44)->bit6
#define DMA_ME0AENR_AEN7         ((T_Reg32 *) 0xF0003C44)->bit7
#define DMA_ME0AENR_AEN8         ((T_Reg32 *) 0xF0003C44)->bit8
#define DMA_ME0AENR_AEN9         ((T_Reg32 *) 0xF0003C44)->bit9

// Move Engine 0 Access Range Register
#define DMA_ME0ARR             (*((uword volatile *) 0xF0003C48))

// Move Engine 0 Pattern Register
#define DMA_ME0PR              (*((uword volatile *) 0xF0003C3C))

// Move Engine 0 Read Register
#define DMA_ME0R               (*((uword volatile *) 0xF0003C34))

// Move Engine Status Register
#define DMA_MESR               (*((uword volatile *) 0xF0003C30))
#define DMA_MESR_ME0RS           ((T_Reg32 *) 0xF0003C30)->bit0
#define DMA_MESR_ME0WS           ((T_Reg32 *) 0xF0003C30)->bit4

// MLI 0 Service Request Control Register 0
#define DMA_MLI0SRC0           (*((uword volatile *) 0xF0003EAC))
#define DMA_MLI0SRC0_CLRR        ((T_Reg32 *) 0xF0003EAC)->bit14
#define DMA_MLI0SRC0_SETR        ((T_Reg32 *) 0xF0003EAC)->bit15
#define DMA_MLI0SRC0_SRE         ((T_Reg32 *) 0xF0003EAC)->bit12
#define DMA_MLI0SRC0_SRR         ((T_Reg32 *) 0xF0003EAC)->bit13
#define DMA_MLI0SRC0_TOS         ((T_Reg32 *) 0xF0003EAC)->bit10

// MLI 0 Service Request Control Register 1
#define DMA_MLI0SRC1           (*((uword volatile *) 0xF0003EA8))
#define DMA_MLI0SRC1_CLRR        ((T_Reg32 *) 0xF0003EA8)->bit14
#define DMA_MLI0SRC1_SETR        ((T_Reg32 *) 0xF0003EA8)->bit15
#define DMA_MLI0SRC1_SRE         ((T_Reg32 *) 0xF0003EA8)->bit12
#define DMA_MLI0SRC1_SRR         ((T_Reg32 *) 0xF0003EA8)->bit13
#define DMA_MLI0SRC1_TOS         ((T_Reg32 *) 0xF0003EA8)->bit10

// MLI 0 Service Request Control Register 2
#define DMA_MLI0SRC2           (*((uword volatile *) 0xF0003EA4))
#define DMA_MLI0SRC2_CLRR        ((T_Reg32 *) 0xF0003EA4)->bit14
#define DMA_MLI0SRC2_SETR        ((T_Reg32 *) 0xF0003EA4)->bit15
#define DMA_MLI0SRC2_SRE         ((T_Reg32 *) 0xF0003EA4)->bit12
#define DMA_MLI0SRC2_SRR         ((T_Reg32 *) 0xF0003EA4)->bit13
#define DMA_MLI0SRC2_TOS         ((T_Reg32 *) 0xF0003EA4)->bit10

// MLI 0 Service Request Control Register 3
#define DMA_MLI0SRC3           (*((uword volatile *) 0xF0003EA0))
#define DMA_MLI0SRC3_CLRR        ((T_Reg32 *) 0xF0003EA0)->bit14
#define DMA_MLI0SRC3_SETR        ((T_Reg32 *) 0xF0003EA0)->bit15
#define DMA_MLI0SRC3_SRE         ((T_Reg32 *) 0xF0003EA0)->bit12
#define DMA_MLI0SRC3_SRR         ((T_Reg32 *) 0xF0003EA0)->bit13
#define DMA_MLI0SRC3_TOS         ((T_Reg32 *) 0xF0003EA0)->bit10

// MLI 1 Service Request Control Register 0
#define DMA_MLI1SRC0           (*((uword volatile *) 0xF0003EBC))
#define DMA_MLI1SRC0_CLRR        ((T_Reg32 *) 0xF0003EBC)->bit14
#define DMA_MLI1SRC0_SETR        ((T_Reg32 *) 0xF0003EBC)->bit15
#define DMA_MLI1SRC0_SRE         ((T_Reg32 *) 0xF0003EBC)->bit12
#define DMA_MLI1SRC0_SRR         ((T_Reg32 *) 0xF0003EBC)->bit13
#define DMA_MLI1SRC0_TOS         ((T_Reg32 *) 0xF0003EBC)->bit10

// MLI 1 Service Request Control Register 1
#define DMA_MLI1SRC1           (*((uword volatile *) 0xF0003EB8))
#define DMA_MLI1SRC1_CLRR        ((T_Reg32 *) 0xF0003EB8)->bit14
#define DMA_MLI1SRC1_SETR        ((T_Reg32 *) 0xF0003EB8)->bit15
#define DMA_MLI1SRC1_SRE         ((T_Reg32 *) 0xF0003EB8)->bit12
#define DMA_MLI1SRC1_SRR         ((T_Reg32 *) 0xF0003EB8)->bit13
#define DMA_MLI1SRC1_TOS         ((T_Reg32 *) 0xF0003EB8)->bit10

// OCDS Register
#define DMA_OCDSR              (*((uword volatile *) 0xF0003C64))
#define DMA_OCDSR_BRL0           ((T_Reg32 *) 0xF0003C64)->bit5

// DMA Channel 00 Source Address Register
#define DMA_SADR00             (*((uword volatile *) 0xF0003C90))

// DMA Channel 01 Source Address Register
#define DMA_SADR01             (*((uword volatile *) 0xF0003CB0))

// DMA Channel 02 Source Address Register
#define DMA_SADR02             (*((uword volatile *) 0xF0003CD0))

// DMA Channel 03 Source Address Register
#define DMA_SADR03             (*((uword volatile *) 0xF0003CF0))

// DMA Channel 04 Source Address Register
#define DMA_SADR04             (*((uword volatile *) 0xF0003D10))

// DMA Channel 05 Source Address Register
#define DMA_SADR05             (*((uword volatile *) 0xF0003D30))

// DMA Channel 06 Source Address Register
#define DMA_SADR06             (*((uword volatile *) 0xF0003D50))

// DMA Channel 07 Source Address Register
#define DMA_SADR07             (*((uword volatile *) 0xF0003D70))

// Channel 00 Shadowed Address Register
#define DMA_SHADR00            (*((uword volatile *) 0xF0003C98))

// DMA Channel 01 Shadowed Address Register
#define DMA_SHADR01            (*((uword volatile *) 0xF0003CB8))

// DMA Channel 02 Shadowed Address Register
#define DMA_SHADR02            (*((uword volatile *) 0xF0003CD8))

// DMA Channel 03 Shadowed Address Register
#define DMA_SHADR03            (*((uword volatile *) 0xF0003CF8))

// DMA Channel 04 Shadowed Address Register
#define DMA_SHADR04            (*((uword volatile *) 0xF0003D18))

// DMA Channel 05 Shadowed Address Register
#define DMA_SHADR05            (*((uword volatile *) 0xF0003D38))

// DMA Channel 06 Shadowed Address Register
#define DMA_SHADR06            (*((uword volatile *) 0xF0003D58))

// DMA Channel 07 Shadowed Address Register
#define DMA_SHADR07            (*((uword volatile *) 0xF0003D78))

// DMA Service Request Control Register 0
#define DMA_SRC0               (*((uword volatile *) 0xF0003EFC))
#define DMA_SRC0_CLRR            ((T_Reg32 *) 0xF0003EFC)->bit14
#define DMA_SRC0_SETR            ((T_Reg32 *) 0xF0003EFC)->bit15
#define DMA_SRC0_SRE             ((T_Reg32 *) 0xF0003EFC)->bit12
#define DMA_SRC0_SRR             ((T_Reg32 *) 0xF0003EFC)->bit13
#define DMA_SRC0_TOS             ((T_Reg32 *) 0xF0003EFC)->bit10

// DMA Service Request Control Register 1
#define DMA_SRC1               (*((uword volatile *) 0xF0003EF8))
#define DMA_SRC1_CLRR            ((T_Reg32 *) 0xF0003EF8)->bit14
#define DMA_SRC1_SETR            ((T_Reg32 *) 0xF0003EF8)->bit15
#define DMA_SRC1_SRE             ((T_Reg32 *) 0xF0003EF8)->bit12
#define DMA_SRC1_SRR             ((T_Reg32 *) 0xF0003EF8)->bit13
#define DMA_SRC1_TOS             ((T_Reg32 *) 0xF0003EF8)->bit10

// DMA Service Request Control Register 2
#define DMA_SRC2               (*((uword volatile *) 0xF0003EF4))
#define DMA_SRC2_CLRR            ((T_Reg32 *) 0xF0003EF4)->bit14
#define DMA_SRC2_SETR            ((T_Reg32 *) 0xF0003EF4)->bit15
#define DMA_SRC2_SRE             ((T_Reg32 *) 0xF0003EF4)->bit12
#define DMA_SRC2_SRR             ((T_Reg32 *) 0xF0003EF4)->bit13
#define DMA_SRC2_TOS             ((T_Reg32 *) 0xF0003EF4)->bit10

// DMA Service Request Control Register 3
#define DMA_SRC3               (*((uword volatile *) 0xF0003EF0))
#define DMA_SRC3_CLRR            ((T_Reg32 *) 0xF0003EF0)->bit14
#define DMA_SRC3_SETR            ((T_Reg32 *) 0xF0003EF0)->bit15
#define DMA_SRC3_SRE             ((T_Reg32 *) 0xF0003EF0)->bit12
#define DMA_SRC3_SRR             ((T_Reg32 *) 0xF0003EF0)->bit13
#define DMA_SRC3_TOS             ((T_Reg32 *) 0xF0003EF0)->bit10

// Software Transaction Request Register
#define DMA_STREQ              (*((uword volatile *) 0xF0003C18))
#define DMA_STREQ_SCH00          ((T_Reg32 *) 0xF0003C18)->bit0
#define DMA_STREQ_SCH01          ((T_Reg32 *) 0xF0003C18)->bit1
#define DMA_STREQ_SCH02          ((T_Reg32 *) 0xF0003C18)->bit2
#define DMA_STREQ_SCH03          ((T_Reg32 *) 0xF0003C18)->bit3
#define DMA_STREQ_SCH04          ((T_Reg32 *) 0xF0003C18)->bit4
#define DMA_STREQ_SCH05          ((T_Reg32 *) 0xF0003C18)->bit5
#define DMA_STREQ_SCH06          ((T_Reg32 *) 0xF0003C18)->bit6
#define DMA_STREQ_SCH07          ((T_Reg32 *) 0xF0003C18)->bit7

// Suspend Mode Register
#define DMA_SUSPMR             (*((uword volatile *) 0xF0003C68))
#define DMA_SUSPMR_SUSAC00       ((T_Reg32 *) 0xF0003C68)->bit16
#define DMA_SUSPMR_SUSAC01       ((T_Reg32 *) 0xF0003C68)->bit17
#define DMA_SUSPMR_SUSAC02       ((T_Reg32 *) 0xF0003C68)->bit18
#define DMA_SUSPMR_SUSAC03       ((T_Reg32 *) 0xF0003C68)->bit19
#define DMA_SUSPMR_SUSAC04       ((T_Reg32 *) 0xF0003C68)->bit20
#define DMA_SUSPMR_SUSAC05       ((T_Reg32 *) 0xF0003C68)->bit21
#define DMA_SUSPMR_SUSAC06       ((T_Reg32 *) 0xF0003C68)->bit22
#define DMA_SUSPMR_SUSAC07       ((T_Reg32 *) 0xF0003C68)->bit23
#define DMA_SUSPMR_SUSEN00       ((T_Reg32 *) 0xF0003C68)->bit0
#define DMA_SUSPMR_SUSEN01       ((T_Reg32 *) 0xF0003C68)->bit1
#define DMA_SUSPMR_SUSEN02       ((T_Reg32 *) 0xF0003C68)->bit2
#define DMA_SUSPMR_SUSEN03       ((T_Reg32 *) 0xF0003C68)->bit3
#define DMA_SUSPMR_SUSEN04       ((T_Reg32 *) 0xF0003C68)->bit4
#define DMA_SUSPMR_SUSEN05       ((T_Reg32 *) 0xF0003C68)->bit5
#define DMA_SUSPMR_SUSEN06       ((T_Reg32 *) 0xF0003C68)->bit6
#define DMA_SUSPMR_SUSEN07       ((T_Reg32 *) 0xF0003C68)->bit7

// System Interrupt Service Request Control Register 4
#define DMA_SYSSRC4            (*((uword volatile *) 0xF0003E8C))
#define DMA_SYSSRC4_CLRR         ((T_Reg32 *) 0xF0003E8C)->bit14
#define DMA_SYSSRC4_SETR         ((T_Reg32 *) 0xF0003E8C)->bit15
#define DMA_SYSSRC4_SRE          ((T_Reg32 *) 0xF0003E8C)->bit12
#define DMA_SYSSRC4_SRR          ((T_Reg32 *) 0xF0003E8C)->bit13
#define DMA_SYSSRC4_TOS          ((T_Reg32 *) 0xF0003E8C)->bit10

// DMA Bus Time-Out Control Register
#define DMA_TOCTR              (*((uword volatile *) 0xF0003E80))

// Transaction Request State Register
#define DMA_TRSR               (*((uword volatile *) 0xF0003C14))
#define DMA_TRSR_CH00            ((T_Reg32 *) 0xF0003C14)->bit0
#define DMA_TRSR_CH01            ((T_Reg32 *) 0xF0003C14)->bit1
#define DMA_TRSR_CH02            ((T_Reg32 *) 0xF0003C14)->bit2
#define DMA_TRSR_CH03            ((T_Reg32 *) 0xF0003C14)->bit3
#define DMA_TRSR_CH04            ((T_Reg32 *) 0xF0003C14)->bit4
#define DMA_TRSR_CH05            ((T_Reg32 *) 0xF0003C14)->bit5
#define DMA_TRSR_CH06            ((T_Reg32 *) 0xF0003C14)->bit6
#define DMA_TRSR_CH07            ((T_Reg32 *) 0xF0003C14)->bit7
#define DMA_TRSR_HTRE00          ((T_Reg32 *) 0xF0003C14)->bit16
#define DMA_TRSR_HTRE01          ((T_Reg32 *) 0xF0003C14)->bit17
#define DMA_TRSR_HTRE02          ((T_Reg32 *) 0xF0003C14)->bit18
#define DMA_TRSR_HTRE03          ((T_Reg32 *) 0xF0003C14)->bit19
#define DMA_TRSR_HTRE04          ((T_Reg32 *) 0xF0003C14)->bit20
#define DMA_TRSR_HTRE05          ((T_Reg32 *) 0xF0003C14)->bit21
#define DMA_TRSR_HTRE06          ((T_Reg32 *) 0xF0003C14)->bit22
#define DMA_TRSR_HTRE07          ((T_Reg32 *) 0xF0003C14)->bit23

// Wrap Status Register
#define DMA_WRPSR              (*((uword volatile *) 0xF0003C5C))
#define DMA_WRPSR_WRPD00         ((T_Reg32 *) 0xF0003C5C)->bit16
#define DMA_WRPSR_WRPD01         ((T_Reg32 *) 0xF0003C5C)->bit17
#define DMA_WRPSR_WRPD02         ((T_Reg32 *) 0xF0003C5C)->bit18
#define DMA_WRPSR_WRPD03         ((T_Reg32 *) 0xF0003C5C)->bit19
#define DMA_WRPSR_WRPD04         ((T_Reg32 *) 0xF0003C5C)->bit20
#define DMA_WRPSR_WRPD05         ((T_Reg32 *) 0xF0003C5C)->bit21
#define DMA_WRPSR_WRPD06         ((T_Reg32 *) 0xF0003C5C)->bit22
#define DMA_WRPSR_WRPD07         ((T_Reg32 *) 0xF0003C5C)->bit23
#define DMA_WRPSR_WRPS00         ((T_Reg32 *) 0xF0003C5C)->bit0
#define DMA_WRPSR_WRPS01         ((T_Reg32 *) 0xF0003C5C)->bit1
#define DMA_WRPSR_WRPS02         ((T_Reg32 *) 0xF0003C5C)->bit2
#define DMA_WRPSR_WRPS03         ((T_Reg32 *) 0xF0003C5C)->bit3
#define DMA_WRPSR_WRPS04         ((T_Reg32 *) 0xF0003C5C)->bit4
#define DMA_WRPSR_WRPS05         ((T_Reg32 *) 0xF0003C5C)->bit5
#define DMA_WRPSR_WRPS06         ((T_Reg32 *) 0xF0003C5C)->bit6
#define DMA_WRPSR_WRPS07         ((T_Reg32 *) 0xF0003C5C)->bit7

// DMI Asynchronous Trap Register
#define DMI_ATR                (*((uword volatile *) 0xF87FFC20))
#define DMI_ATR_CFEATF           ((T_Reg32 *) 0xF87FFC20)->bit10
#define DMI_ATR_CMEATF           ((T_Reg32 *) 0xF87FFC20)->bit11
#define DMI_ATR_CRLEATF          ((T_Reg32 *) 0xF87FFC20)->bit6
#define DMI_ATR_CRSEATF          ((T_Reg32 *) 0xF87FFC20)->bit7
#define DMI_ATR_CWLEATF          ((T_Reg32 *) 0xF87FFC20)->bit8
#define DMI_ATR_CWSEATF          ((T_Reg32 *) 0xF87FFC20)->bit9
#define DMI_ATR_LCEATF           ((T_Reg32 *) 0xF87FFC20)->bit4
#define DMI_ATR_LFEATF           ((T_Reg32 *) 0xF87FFC20)->bit2
#define DMI_ATR_LREATF           ((T_Reg32 *) 0xF87FFC20)->bit0
#define DMI_ATR_SCEATF           ((T_Reg32 *) 0xF87FFC20)->bit5
#define DMI_ATR_SFEATF           ((T_Reg32 *) 0xF87FFC20)->bit3
#define DMI_ATR_SREATF           ((T_Reg32 *) 0xF87FFC20)->bit1

// DMI Control Register
#define DMI_CON                (*((uword volatile *) 0xF87FFC10))

// DMI Control Register 1
#define DMI_CON1               (*((uword volatile *) 0xF87FFC28))
#define DMI_CON1_DC2SPR          ((T_Reg32 *) 0xF87FFC28)->bit0

// DMI Module Identification Register
#define DMI_ID                 (*((uword volatile *) 0xF87FFC08))

// DMI Synchronous Trap Register
#define DMI_STR                (*((uword volatile *) 0xF87FFC18))
#define DMI_STR_CFESTF           ((T_Reg32 *) 0xF87FFC18)->bit10
#define DMI_STR_CMESTF           ((T_Reg32 *) 0xF87FFC18)->bit11
#define DMI_STR_CRLESTF          ((T_Reg32 *) 0xF87FFC18)->bit6
#define DMI_STR_CRSESTF          ((T_Reg32 *) 0xF87FFC18)->bit7
#define DMI_STR_CWLESTF          ((T_Reg32 *) 0xF87FFC18)->bit8
#define DMI_STR_CWSESTF          ((T_Reg32 *) 0xF87FFC18)->bit9
#define DMI_STR_LCESTF           ((T_Reg32 *) 0xF87FFC18)->bit4
#define DMI_STR_LFESTF           ((T_Reg32 *) 0xF87FFC18)->bit2
#define DMI_STR_LRESTF           ((T_Reg32 *) 0xF87FFC18)->bit0
#define DMI_STR_SCESTF           ((T_Reg32 *) 0xF87FFC18)->bit5
#define DMI_STR_SFESTF           ((T_Reg32 *) 0xF87FFC18)->bit3
#define DMI_STR_SRESTF           ((T_Reg32 *) 0xF87FFC18)->bit1

// Debug Monitor Start Address Register
#define DMS                    (*((uword volatile *) 0xF7E1FD40))

// CPU SRAM Configuration Bit Chain Control Register
#define DMU_CSCACTL            (*((uword volatile *) 0xF8000490))
#define DMU_CSCACTL_CA0EN        ((T_Reg32 *) 0xF8000490)->bit0
#define DMU_CSCACTL_CA1EN        ((T_Reg32 *) 0xF8000490)->bit1
#define DMU_CSCACTL_CA2EN        ((T_Reg32 *) 0xF8000490)->bit2

// CPU SRAM Configuration Bit Chain Data In Register
#define DMU_CSCADIN            (*((uword volatile *) 0xF8000498))

// CPU SRAM Configuration Bit Chain Data Out Register
#define DMU_CSCADOUT           (*((uword volatile *) 0xF80004A0))

// DMU Module Identification Register
#define DMU_ID                 (*((uword volatile *) 0xF8000408))

// Soft-Error Trapped Address
#define DMU_SETA               (*((uword volatile *) 0xF80004A8))

// SRAM Redundancy Address
#define DMU_SRAR0              (*((uword volatile *) 0xF8000410))
#define DMU_SRAR0_VA             ((T_Reg32 *) 0xF8000410)->bit14

// SRAM Redundancy Address
#define DMU_SRAR1              (*((uword volatile *) 0xF8000418))
#define DMU_SRAR1_VA             ((T_Reg32 *) 0xF8000418)->bit14

// SRAM Redundancy Address
#define DMU_SRAR10             (*((uword volatile *) 0xF8000460))
#define DMU_SRAR10_VA            ((T_Reg32 *) 0xF8000460)->bit14

// SRAM Redundancy Address
#define DMU_SRAR11             (*((uword volatile *) 0xF8000468))
#define DMU_SRAR11_VA            ((T_Reg32 *) 0xF8000468)->bit14

// SRAM Redundancy Address
#define DMU_SRAR12             (*((uword volatile *) 0xF8000470))
#define DMU_SRAR12_VA            ((T_Reg32 *) 0xF8000470)->bit14

// SRAM Redundancy Address
#define DMU_SRAR13             (*((uword volatile *) 0xF8000478))
#define DMU_SRAR13_VA            ((T_Reg32 *) 0xF8000478)->bit14

// SRAM Redundancy Address
#define DMU_SRAR14             (*((uword volatile *) 0xF8000480))
#define DMU_SRAR14_VA            ((T_Reg32 *) 0xF8000480)->bit14

// SRAM Redundancy Address
#define DMU_SRAR15             (*((uword volatile *) 0xF8000488))
#define DMU_SRAR15_VA            ((T_Reg32 *) 0xF8000488)->bit14

// SRAM Redundancy Address
#define DMU_SRAR2              (*((uword volatile *) 0xF8000420))
#define DMU_SRAR2_VA             ((T_Reg32 *) 0xF8000420)->bit14

// SRAM Redundancy Address
#define DMU_SRAR3              (*((uword volatile *) 0xF8000428))
#define DMU_SRAR3_VA             ((T_Reg32 *) 0xF8000428)->bit14

// SRAM Redundancy Address
#define DMU_SRAR4              (*((uword volatile *) 0xF8000430))
#define DMU_SRAR4_VA             ((T_Reg32 *) 0xF8000430)->bit14

// SRAM Redundancy Address
#define DMU_SRAR5              (*((uword volatile *) 0xF8000438))
#define DMU_SRAR5_VA             ((T_Reg32 *) 0xF8000438)->bit14

// SRAM Redundancy Address
#define DMU_SRAR6              (*((uword volatile *) 0xF8000440))
#define DMU_SRAR6_VA             ((T_Reg32 *) 0xF8000440)->bit14

// SRAM Redundancy Address
#define DMU_SRAR7              (*((uword volatile *) 0xF8000448))
#define DMU_SRAR7_VA             ((T_Reg32 *) 0xF8000448)->bit14

// SRAM Redundancy Address
#define DMU_SRAR8              (*((uword volatile *) 0xF8000450))
#define DMU_SRAR8_VA             ((T_Reg32 *) 0xF8000450)->bit14

// SRAM Redundancy Address
#define DMU_SRAR9              (*((uword volatile *) 0xF8000458))
#define DMU_SRAR9_VA             ((T_Reg32 *) 0xF8000458)->bit14

// Data Memory Protection Mode Register 0
#define DPM0                   (*((uword volatile *) 0xF7E1E000))
#define DPM0_RBL0                0x00000004
#define DPM0_RBL1                0x00000400
#define DPM0_RBL2                0x00040000
#define DPM0_RBL3                0x04000000
#define DPM0_RBU0                0x00000001
#define DPM0_RBU1                0x00000100
#define DPM0_RBU2                0x00010000
#define DPM0_RBU3                0x01000000
#define DPM0_RE0                 0x00000040
#define DPM0_RE1                 0x00004000
#define DPM0_RE2                 0x00400000
#define DPM0_RE3                 0x40000000
#define DPM0_RS0                 0x00000010
#define DPM0_RS1                 0x00001000
#define DPM0_RS2                 0x00100000
#define DPM0_RS3                 0x10000000
#define DPM0_WBL0                0x00000008
#define DPM0_WBL1                0x00000800
#define DPM0_WBL2                0x00080000
#define DPM0_WBL3                0x08000000
#define DPM0_WBU0                0x00000002
#define DPM0_WBU1                0x00000200
#define DPM0_WBU2                0x00020000
#define DPM0_WBU3                0x02000000
#define DPM0_WE0                 0x00000080
#define DPM0_WE1                 0x00008000
#define DPM0_WE2                 0x00800000
#define DPM0_WE3                 0x80000000
#define DPM0_WS0                 0x00000020
#define DPM0_WS1                 0x00002000
#define DPM0_WS2                 0x00200000
#define DPM0_WS3                 0x20000000

// Data Memory Protection Mode Register 1
#define DPM1                   (*((uword volatile *) 0xF7E1E080))
#define DPM1_RBL0                0x00000004
#define DPM1_RBL1                0x00000400
#define DPM1_RBL2                0x00040000
#define DPM1_RBL3                0x04000000
#define DPM1_RBU0                0x00000001
#define DPM1_RBU1                0x00000100
#define DPM1_RBU2                0x00010000
#define DPM1_RBU3                0x01000000
#define DPM1_RE0                 0x00000040
#define DPM1_RE1                 0x00004000
#define DPM1_RE2                 0x00400000
#define DPM1_RE3                 0x40000000
#define DPM1_RS0                 0x00000010
#define DPM1_RS1                 0x00001000
#define DPM1_RS2                 0x00100000
#define DPM1_RS3                 0x10000000
#define DPM1_WBL0                0x00000008
#define DPM1_WBL1                0x00000800
#define DPM1_WBL2                0x00080000
#define DPM1_WBL3                0x08000000
#define DPM1_WBU0                0x00000002
#define DPM1_WBU1                0x00000200
#define DPM1_WBU2                0x00020000
#define DPM1_WBU3                0x02000000
#define DPM1_WE0                 0x00000080
#define DPM1_WE1                 0x00008000
#define DPM1_WE2                 0x00800000
#define DPM1_WE3                 0x80000000
#define DPM1_WS0                 0x00000020
#define DPM1_WS1                 0x00002000
#define DPM1_WS2                 0x00200000
#define DPM1_WS3                 0x20000000

// Data Segment Protection Register Set 0, Range 0, Lower
#define DPR0_0L                (*((uword volatile *) 0xF7E1C000))

// Data Segment Protection Register Set 0, Range 0, Upper
#define DPR0_0U                (*((uword volatile *) 0xF7E1C004))

// Data Segment Protection Register Set 0, Range 1, Lower
#define DPR0_1L                (*((uword volatile *) 0xF7E1C008))

// Data Segment Protection Register Set 0, Range 1, Upper
#define DPR0_1U                (*((uword volatile *) 0xF7E1C00C))

// Data Segment Protection Register Set 0, Range 2, Lower
#define DPR0_2L                (*((uword volatile *) 0xF7E1C010))

// Data Segment Protection Register Set 0, Range 2, Upper
#define DPR0_2U                (*((uword volatile *) 0xF7E1C014))

// Data Segment Protection Register Set 0, Range 3, Lower
#define DPR0_3L                (*((uword volatile *) 0xF7E1C018))

// Data Segment Protection Register Set 0, Range 3, Upper
#define DPR0_3U                (*((uword volatile *) 0xF7E1C01C))

// Data Segment Protection Register Set 1, Range 0, Lower
#define DPR1_0L                (*((uword volatile *) 0xF7E1C400))

// Data Segment Protection Register Set 1, Range 0, Upper
#define DPR1_0U                (*((uword volatile *) 0xF7E1C404))

// Data Segment Protection Register Set 1, Range 1, Lower
#define DPR1_1L                (*((uword volatile *) 0xF7E1C408))

// Data Segment Protection Register Set 1, Range 1, Upper
#define DPR1_1U                (*((uword volatile *) 0xF7E1C40C))

// Data Segment Protection Register Set 1, Range 2, Lower
#define DPR1_2L                (*((uword volatile *) 0xF7E1C410))

// Data Segment Protection Register Set 1, Range 2, Upper
#define DPR1_2U                (*((uword volatile *) 0xF7E1C414))

// Data Segment Protection Register Set 1, Range 3, Lower
#define DPR1_3L                (*((uword volatile *) 0xF7E1C418))

// Data Segment Protection Register Set 1, Range 0, Upper
#define DPR1_3U                (*((uword volatile *) 0xF7E1C41C))

// DR Service Request Control Register
#define DRSRC                  (*((uword volatile *) 0xF0000098))
#define DRSRC_CLRR               ((T_Reg32 *) 0xF0000098)->bit14
#define DRSRC_SETR               ((T_Reg32 *) 0xF0000098)->bit15
#define DRSRC_SRE                ((T_Reg32 *) 0xF0000098)->bit12
#define DRSRC_SRR                ((T_Reg32 *) 0xF0000098)->bit13
#define DRSRC_TOS                ((T_Reg32 *) 0xF0000098)->bit10

// DT Service Request Control Register
#define DTSRC                  (*((uword volatile *) 0xF000009C))
#define DTSRC_CLRR               ((T_Reg32 *) 0xF000009C)->bit14
#define DTSRC_SETR               ((T_Reg32 *) 0xF000009C)->bit15
#define DTSRC_SRE                ((T_Reg32 *) 0xF000009C)->bit12
#define DTSRC_SRR                ((T_Reg32 *) 0xF000009C)->bit13
#define DTSRC_TOS                ((T_Reg32 *) 0xF000009C)->bit10

// EBU_LMB Address Select Register 0
#define EBU_ADDRSEL0           (*((uword volatile *) 0xF8000080))
#define EBU_ADDRSEL0_ALTENAB     ((T_Reg32 *) 0xF8000080)->bit1
#define EBU_ADDRSEL0_REGENAB     ((T_Reg32 *) 0xF8000080)->bit0

// EBU_LMB Address Select Register 1
#define EBU_ADDRSEL1           (*((uword volatile *) 0xF8000088))
#define EBU_ADDRSEL1_ALTENAB     ((T_Reg32 *) 0xF8000088)->bit1
#define EBU_ADDRSEL1_REGENAB     ((T_Reg32 *) 0xF8000088)->bit0

// EBU_LMB Address Select Register 2
#define EBU_ADDRSEL2           (*((uword volatile *) 0xF8000090))
#define EBU_ADDRSEL2_ALTENAB     ((T_Reg32 *) 0xF8000090)->bit1
#define EBU_ADDRSEL2_REGENAB     ((T_Reg32 *) 0xF8000090)->bit0

// EBU_LMB Address Select Register 3
#define EBU_ADDRSEL3           (*((uword volatile *) 0xF8000098))
#define EBU_ADDRSEL3_ALTENAB     ((T_Reg32 *) 0xF8000098)->bit1
#define EBU_ADDRSEL3_REGENAB     ((T_Reg32 *) 0xF8000098)->bit0

// Burst Flash Control Register
#define EBU_BFCON              (*((uword volatile *) 0xF8000020))
#define EBU_BFCON_BFCMSEL        ((T_Reg32 *) 0xF8000020)->bit8
#define EBU_BFCON_DBA0           ((T_Reg32 *) 0xF8000020)->bit10
#define EBU_BFCON_DBA1           ((T_Reg32 *) 0xF8000020)->bit26
#define EBU_BFCON_EBSE0          ((T_Reg32 *) 0xF8000020)->bit9
#define EBU_BFCON_EBSE1          ((T_Reg32 *) 0xF8000020)->bit25
#define EBU_BFCON_FBBMSEL0       ((T_Reg32 *) 0xF8000020)->bit4
#define EBU_BFCON_FBBMSEL1       ((T_Reg32 *) 0xF8000020)->bit20
#define EBU_BFCON_FDBKEN         ((T_Reg32 *) 0xF8000020)->bit11
#define EBU_BFCON_WAITFUNC0      ((T_Reg32 *) 0xF8000020)->bit5
#define EBU_BFCON_WAITFUNC1      ((T_Reg32 *) 0xF8000020)->bit21

// EBU_LMB Bus Access Par. Reg.0
#define EBU_BUSAP0             (*((uword volatile *) 0xF8000100))

// EBU_LMB Bus Access Par. Reg.1
#define EBU_BUSAP1             (*((uword volatile *) 0xF8000108))

// EBU_LMB Bus Access Par. Reg.2
#define EBU_BUSAP2             (*((uword volatile *) 0xF8000110))

// EBU_LMB Bus Access Par. Reg.3
#define EBU_BUSAP3             (*((uword volatile *) 0xF8000118))

// EBU Bus Configuration Register 0
#define EBU_BUSCON0            (*((uword volatile *) 0xF80000C0))
#define EBU_BUSCON0_AALIGN       ((T_Reg32 *) 0xF80000C0)->bit9
#define EBU_BUSCON0_DLOAD        ((T_Reg32 *) 0xF80000C0)->bit17
#define EBU_BUSCON0_PREFETCH     ((T_Reg32 *) 0xF80000C0)->bit18
#define EBU_BUSCON0_WAITINV      ((T_Reg32 *) 0xF80000C0)->bit19
#define EBU_BUSCON0_WEAKPREFETCH ((T_Reg32 *) 0xF80000C0)->bit8
#define EBU_BUSCON0_WRITE        ((T_Reg32 *) 0xF80000C0)->bit31

// EBU Bus Configuration Register 1
#define EBU_BUSCON1            (*((uword volatile *) 0xF80000C8))
#define EBU_BUSCON1_AALIGN       ((T_Reg32 *) 0xF80000C8)->bit9
#define EBU_BUSCON1_DLOAD        ((T_Reg32 *) 0xF80000C8)->bit17
#define EBU_BUSCON1_PREFETCH     ((T_Reg32 *) 0xF80000C8)->bit18
#define EBU_BUSCON1_WAITINV      ((T_Reg32 *) 0xF80000C8)->bit19
#define EBU_BUSCON1_WEAKPREFETCH ((T_Reg32 *) 0xF80000C8)->bit8
#define EBU_BUSCON1_WRITE        ((T_Reg32 *) 0xF80000C8)->bit31

// EBU Bus Configuration Register 2
#define EBU_BUSCON2            (*((uword volatile *) 0xF80000D0))
#define EBU_BUSCON2_AALIGN       ((T_Reg32 *) 0xF80000D0)->bit9
#define EBU_BUSCON2_DLOAD        ((T_Reg32 *) 0xF80000D0)->bit17
#define EBU_BUSCON2_PREFETCH     ((T_Reg32 *) 0xF80000D0)->bit18
#define EBU_BUSCON2_WAITINV      ((T_Reg32 *) 0xF80000D0)->bit19
#define EBU_BUSCON2_WEAKPREFETCH ((T_Reg32 *) 0xF80000D0)->bit8
#define EBU_BUSCON2_WRITE        ((T_Reg32 *) 0xF80000D0)->bit31

// EBU Bus Configuration Register 3
#define EBU_BUSCON3            (*((uword volatile *) 0xF80000D8))
#define EBU_BUSCON3_AALIGN       ((T_Reg32 *) 0xF80000D8)->bit9
#define EBU_BUSCON3_DLOAD        ((T_Reg32 *) 0xF80000D8)->bit17
#define EBU_BUSCON3_PREFETCH     ((T_Reg32 *) 0xF80000D8)->bit18
#define EBU_BUSCON3_WAITINV      ((T_Reg32 *) 0xF80000D8)->bit19
#define EBU_BUSCON3_WEAKPREFETCH ((T_Reg32 *) 0xF80000D8)->bit8
#define EBU_BUSCON3_WRITE        ((T_Reg32 *) 0xF80000D8)->bit31

// EBU Clock Control Register
#define EBU_CLC                (*((uword volatile *) 0xF8000000))
#define EBU_CLC_DISR             ((T_Reg32 *) 0xF8000000)->bit0
#define EBU_CLC_DISS             ((T_Reg32 *) 0xF8000000)->bit1

// EBU_LMB Configuration Register
#define EBU_CON                (*((uword volatile *) 0xF8000010))
#define EBU_CON_ARBSYNC          ((T_Reg32 *) 0xF8000010)->bit5
#define EBU_CON_BFSSS            ((T_Reg32 *) 0xF8000010)->bit29
#define EBU_CON_CS0FAM           ((T_Reg32 *) 0xF8000010)->bit27
#define EBU_CON_EMUFAM           ((T_Reg32 *) 0xF8000010)->bit28
#define EBU_CON_EXTACC           ((T_Reg32 *) 0xF8000010)->bit3
#define EBU_CON_EXTLOCK          ((T_Reg32 *) 0xF8000010)->bit4
#define EBU_CON_EXTRECON         ((T_Reg32 *) 0xF8000010)->bit1
#define EBU_CON_EXTSVM           ((T_Reg32 *) 0xF8000010)->bit2
#define EBU_CON_SDCMSEL          ((T_Reg32 *) 0xF8000010)->bit26

// EBU_LMB Emulator Address Select Register
#define EBU_EMUAS              (*((uword volatile *) 0xF8000160))
#define EBU_EMUAS_ALTENAB        ((T_Reg32 *) 0xF8000160)->bit1
#define EBU_EMUAS_REGENAB        ((T_Reg32 *) 0xF8000160)->bit0

// EBU_LMB Emulator Bus Access Parameter Register
#define EBU_EMUBAP             (*((uword volatile *) 0xF8000170))

// EBU_LMB Emulator Control Register
#define EBU_EMUBC              (*((uword volatile *) 0xF8000168))
#define EBU_EMUBC_AALIGN         ((T_Reg32 *) 0xF8000168)->bit9
#define EBU_EMUBC_DLOAD          ((T_Reg32 *) 0xF8000168)->bit17
#define EBU_EMUBC_PREFETCH       ((T_Reg32 *) 0xF8000168)->bit18
#define EBU_EMUBC_WAITINV        ((T_Reg32 *) 0xF8000168)->bit19
#define EBU_EMUBC_WEAKPREFETCH   ((T_Reg32 *) 0xF8000168)->bit8
#define EBU_EMUBC_WRITE          ((T_Reg32 *) 0xF8000168)->bit31

// EBU_LMB Emulator Overlay Register
#define EBU_EMUOVL             (*((uword volatile *) 0xF8000178))

// EBU Module Identification Register
#define EBU_ID                 (*((uword volatile *) 0xF8000008))

// EBU_LMB SDRAM Control Register 0
#define EBU_SDRMCON0           (*((uword volatile *) 0xF8000050))

// EBU_LMB SDRAM Control Register 1
#define EBU_SDRMCON1           (*((uword volatile *) 0xF8000058))

// EBU_LMB SDRAM Mode Register 0
#define EBU_SDRMOD0            (*((uword volatile *) 0xF8000060))
#define EBU_SDRMOD0_BTYP         ((T_Reg32 *) 0xF8000060)->bit3

// EBU_LMB SDRAM Mode Register 1
#define EBU_SDRMOD1            (*((uword volatile *) 0xF8000068))
#define EBU_SDRMOD1_BTYP         ((T_Reg32 *) 0xF8000068)->bit3

// EBU_LMB SDRAM Refresh Register 0
#define EBU_SDRMREF0           (*((uword volatile *) 0xF8000040))
#define EBU_SDRMREF0_AUTOSELFR   ((T_Reg32 *) 0xF8000040)->bit13
#define EBU_SDRMREF0_SELFREN     ((T_Reg32 *) 0xF8000040)->bit12
#define EBU_SDRMREF0_SELFRENST   ((T_Reg32 *) 0xF8000040)->bit11
#define EBU_SDRMREF0_SELFREX     ((T_Reg32 *) 0xF8000040)->bit10
#define EBU_SDRMREF0_SELFREXST   ((T_Reg32 *) 0xF8000040)->bit9

// EBU_LMB SDRAM Refresh Register 0
#define EBU_SDRMREF1           (*((uword volatile *) 0xF8000048))
#define EBU_SDRMREF1_AUTOSELFR   ((T_Reg32 *) 0xF8000048)->bit13
#define EBU_SDRMREF1_SELFREN     ((T_Reg32 *) 0xF8000048)->bit12
#define EBU_SDRMREF1_SELFRENST   ((T_Reg32 *) 0xF8000048)->bit11
#define EBU_SDRMREF1_SELFREX     ((T_Reg32 *) 0xF8000048)->bit10
#define EBU_SDRMREF1_SELFREXST   ((T_Reg32 *) 0xF8000048)->bit9

// EBU_LMB SDRAM Status Register 0
#define EBU_SDRSTAT0           (*((uword volatile *) 0xF8000070))
#define EBU_SDRSTAT0_REFERR      ((T_Reg32 *) 0xF8000070)->bit0
#define EBU_SDRSTAT0_SDRMBUSY    ((T_Reg32 *) 0xF8000070)->bit1

// EBU_LMB SDRAM Status Register 1
#define EBU_SDRSTAT1           (*((uword volatile *) 0xF8000078))
#define EBU_SDRSTAT1_REFERR      ((T_Reg32 *) 0xF8000078)->bit0
#define EBU_SDRSTAT1_SDRMBUSY    ((T_Reg32 *) 0xF8000078)->bit1

// Test/Configuration Register
#define EBU_USERCON            (*((uword volatile *) 0xF8000190))
#define EBU_USERCON_DIP          ((T_Reg32 *) 0xF8000190)->bit0

// External Input Channel Register 0
#define EICR0                  (*((uword volatile *) 0xF00000B0))
#define EICR0_EIEN0              ((T_Reg32 *) 0xF00000B0)->bit11
#define EICR0_EIEN1              ((T_Reg32 *) 0xF00000B0)->bit27
#define EICR0_FEN0               ((T_Reg32 *) 0xF00000B0)->bit8
#define EICR0_FEN1               ((T_Reg32 *) 0xF00000B0)->bit24
#define EICR0_LDEN0              ((T_Reg32 *) 0xF00000B0)->bit10
#define EICR0_LDEN1              ((T_Reg32 *) 0xF00000B0)->bit26
#define EICR0_REN0               ((T_Reg32 *) 0xF00000B0)->bit9
#define EICR0_REN1               ((T_Reg32 *) 0xF00000B0)->bit25

// External Input Channel Register 1
#define EICR1                  (*((uword volatile *) 0xF00000B4))
#define EICR1_EIEN2              ((T_Reg32 *) 0xF00000B4)->bit11
#define EICR1_EIEN3              ((T_Reg32 *) 0xF00000B4)->bit27
#define EICR1_FEN2               ((T_Reg32 *) 0xF00000B4)->bit8
#define EICR1_FEN3               ((T_Reg32 *) 0xF00000B4)->bit24
#define EICR1_LDEN2              ((T_Reg32 *) 0xF00000B4)->bit10
#define EICR1_LDEN3              ((T_Reg32 *) 0xF00000B4)->bit26
#define EICR1_REN2               ((T_Reg32 *) 0xF00000B4)->bit9
#define EICR1_REN3               ((T_Reg32 *) 0xF00000B4)->bit25

// External Input Flag Register
#define EIFR                   (*((uword volatile *) 0xF00000B8))
#define EIFR_INTF0               ((T_Reg32 *) 0xF00000B8)->bit0
#define EIFR_INTF1               ((T_Reg32 *) 0xF00000B8)->bit1
#define EIFR_INTF2               ((T_Reg32 *) 0xF00000B8)->bit2
#define EIFR_INTF3               ((T_Reg32 *) 0xF00000B8)->bit3

// Service Request Control Reg. for Ext. Interrupt 0
#define EINT_SRC0              (*((uword volatile *) 0xF00000D8))
#define EINT_SRC0_CLRR           ((T_Reg32 *) 0xF00000D8)->bit14
#define EINT_SRC0_SETR           ((T_Reg32 *) 0xF00000D8)->bit15
#define EINT_SRC0_SRE            ((T_Reg32 *) 0xF00000D8)->bit12
#define EINT_SRC0_SRR            ((T_Reg32 *) 0xF00000D8)->bit13
#define EINT_SRC0_TOS            ((T_Reg32 *) 0xF00000D8)->bit10

// Service Request Control Reg. for Ext. Interrupt 1
#define EINT_SRC1              (*((uword volatile *) 0xF00000D4))
#define EINT_SRC1_CLRR           ((T_Reg32 *) 0xF00000D4)->bit14
#define EINT_SRC1_SETR           ((T_Reg32 *) 0xF00000D4)->bit15
#define EINT_SRC1_SRE            ((T_Reg32 *) 0xF00000D4)->bit12
#define EINT_SRC1_SRR            ((T_Reg32 *) 0xF00000D4)->bit13
#define EINT_SRC1_TOS            ((T_Reg32 *) 0xF00000D4)->bit10

// Service Request Control Reg. for Ext. Interrupt 2
#define EINT_SRC2              (*((uword volatile *) 0xF00000D0))
#define EINT_SRC2_CLRR           ((T_Reg32 *) 0xF00000D0)->bit14
#define EINT_SRC2_SETR           ((T_Reg32 *) 0xF00000D0)->bit15
#define EINT_SRC2_SRE            ((T_Reg32 *) 0xF00000D0)->bit12
#define EINT_SRC2_SRR            ((T_Reg32 *) 0xF00000D0)->bit13
#define EINT_SRC2_TOS            ((T_Reg32 *) 0xF00000D0)->bit10

// Service Request Control Reg. for Ext. Interrupt 3
#define EINT_SRC3              (*((uword volatile *) 0xF00000C8))
#define EINT_SRC3_CLRR           ((T_Reg32 *) 0xF00000C8)->bit14
#define EINT_SRC3_SETR           ((T_Reg32 *) 0xF00000C8)->bit15
#define EINT_SRC3_SRE            ((T_Reg32 *) 0xF00000C8)->bit12
#define EINT_SRC3_SRR            ((T_Reg32 *) 0xF00000C8)->bit13
#define EINT_SRC3_TOS            ((T_Reg32 *) 0xF00000C8)->bit10

// External Break Input Event Specifier Register
#define EXEVT                  (*((uword volatile *) 0xF7E1FD08))
#define EXEVT_0                  0x00000010
#define EXEVT_BBM                0x00000008
#define EXEVT_SUSP               0x00000020

// DR Command Register

// Free Context List Head Pointer
#define FCX                    (*((uword volatile *) 0xF7E1FE38))

// SCU Fusebox Data Register
#define FDR                    (*((uword volatile *) 0xF0000064))
#define FDR_VA                   ((T_Reg32 *) 0xF0000064)->bit14

// SCU Flag Modification Register
#define FMR                    (*((uword volatile *) 0xF00000BC))
#define FMR_FC0                  ((T_Reg32 *) 0xF00000BC)->bit16
#define FMR_FC1                  ((T_Reg32 *) 0xF00000BC)->bit17
#define FMR_FC2                  ((T_Reg32 *) 0xF00000BC)->bit18
#define FMR_FC3                  ((T_Reg32 *) 0xF00000BC)->bit19
#define FMR_FS0                  ((T_Reg32 *) 0xF00000BC)->bit0
#define FMR_FS1                  ((T_Reg32 *) 0xF00000BC)->bit1
#define FMR_FS2                  ((T_Reg32 *) 0xF00000BC)->bit2
#define FMR_FS3                  ((T_Reg32 *) 0xF00000BC)->bit3

// FPU Service Request Control Register
#define FPU_SRC                (*((uword volatile *) 0xF00000A0))
#define FPU_SRC_CLRR             ((T_Reg32 *) 0xF00000A0)->bit14
#define FPU_SRC_SETR             ((T_Reg32 *) 0xF00000A0)->bit15
#define FPU_SRC_SRE              ((T_Reg32 *) 0xF00000A0)->bit12
#define FPU_SRC_SRR              ((T_Reg32 *) 0xF00000A0)->bit13
#define FPU_SRC_TOS              ((T_Reg32 *) 0xF00000A0)->bit10

// Fusebox Selector Register
#define FSR                    (*((uword volatile *) 0xF0000060))
#define FSR_SEL0                 ((T_Reg32 *) 0xF0000060)->bit0
#define FSR_SEL1                 ((T_Reg32 *) 0xF0000060)->bit1
#define FSR_SEL2                 ((T_Reg32 *) 0xF0000060)->bit2
#define FSR_SEL3                 ((T_Reg32 *) 0xF0000060)->bit3

// GPTU Clock Control Register
#define GPTU_CLC               (*((uword volatile *) 0xF0000600))
#define GPTU_CLC_DISR            ((T_Reg32 *) 0xF0000600)->bit0
#define GPTU_CLC_DISS            ((T_Reg32 *) 0xF0000600)->bit1
#define GPTU_CLC_EDIS            ((T_Reg32 *) 0xF0000600)->bit3
#define GPTU_CLC_FSOE            ((T_Reg32 *) 0xF0000600)->bit5
#define GPTU_CLC_SBWE            ((T_Reg32 *) 0xF0000600)->bit4
#define GPTU_CLC_SPEN            ((T_Reg32 *) 0xF0000600)->bit2

// GPTU Module Identification Register
#define GPTU_ID                (*((uword volatile *) 0xF0000608))

// GPTU Output Source Selection Register
#define GPTU_OSEL              (*((uword volatile *) 0xF000062C))

// GPTU Output Register
#define GPTU_OUT               (*((uword volatile *) 0xF0000630))
#define GPTU_OUT_CLRO0           ((T_Reg32 *) 0xF0000630)->bit8
#define GPTU_OUT_CLRO1           ((T_Reg32 *) 0xF0000630)->bit9
#define GPTU_OUT_CLRO2           ((T_Reg32 *) 0xF0000630)->bit10
#define GPTU_OUT_CLRO3           ((T_Reg32 *) 0xF0000630)->bit11
#define GPTU_OUT_CLRO4           ((T_Reg32 *) 0xF0000630)->bit12
#define GPTU_OUT_CLRO5           ((T_Reg32 *) 0xF0000630)->bit13
#define GPTU_OUT_CLRO6           ((T_Reg32 *) 0xF0000630)->bit14
#define GPTU_OUT_CLRO7           ((T_Reg32 *) 0xF0000630)->bit15
#define GPTU_OUT_OUT0            ((T_Reg32 *) 0xF0000630)->bit0
#define GPTU_OUT_OUT1            ((T_Reg32 *) 0xF0000630)->bit1
#define GPTU_OUT_OUT2            ((T_Reg32 *) 0xF0000630)->bit2
#define GPTU_OUT_OUT3            ((T_Reg32 *) 0xF0000630)->bit3
#define GPTU_OUT_OUT4            ((T_Reg32 *) 0xF0000630)->bit4
#define GPTU_OUT_OUT5            ((T_Reg32 *) 0xF0000630)->bit5
#define GPTU_OUT_OUT6            ((T_Reg32 *) 0xF0000630)->bit6
#define GPTU_OUT_OUT7            ((T_Reg32 *) 0xF0000630)->bit7
#define GPTU_OUT_SETO0           ((T_Reg32 *) 0xF0000630)->bit16
#define GPTU_OUT_SETO1           ((T_Reg32 *) 0xF0000630)->bit17
#define GPTU_OUT_SETO2           ((T_Reg32 *) 0xF0000630)->bit18
#define GPTU_OUT_SETO3           ((T_Reg32 *) 0xF0000630)->bit19
#define GPTU_OUT_SETO4           ((T_Reg32 *) 0xF0000630)->bit20
#define GPTU_OUT_SETO5           ((T_Reg32 *) 0xF0000630)->bit21
#define GPTU_OUT_SETO6           ((T_Reg32 *) 0xF0000630)->bit22
#define GPTU_OUT_SETO7           ((T_Reg32 *) 0xF0000630)->bit23

// GPTU Service Request Control Register 0
#define GPTU_SRC0              (*((uword volatile *) 0xF00006FC))
#define GPTU_SRC0_CLRR           ((T_Reg32 *) 0xF00006FC)->bit14
#define GPTU_SRC0_SETR           ((T_Reg32 *) 0xF00006FC)->bit15
#define GPTU_SRC0_SRE            ((T_Reg32 *) 0xF00006FC)->bit12
#define GPTU_SRC0_SRR            ((T_Reg32 *) 0xF00006FC)->bit13
#define GPTU_SRC0_TOS            ((T_Reg32 *) 0xF00006FC)->bit10

// GPTU Service Request Control Register 1
#define GPTU_SRC1              (*((uword volatile *) 0xF00006F8))
#define GPTU_SRC1_CLRR           ((T_Reg32 *) 0xF00006F8)->bit14
#define GPTU_SRC1_SETR           ((T_Reg32 *) 0xF00006F8)->bit15
#define GPTU_SRC1_SRE            ((T_Reg32 *) 0xF00006F8)->bit12
#define GPTU_SRC1_SRR            ((T_Reg32 *) 0xF00006F8)->bit13
#define GPTU_SRC1_TOS            ((T_Reg32 *) 0xF00006F8)->bit10

// GPTU Service Request Control Register 2
#define GPTU_SRC2              (*((uword volatile *) 0xF00006F4))
#define GPTU_SRC2_CLRR           ((T_Reg32 *) 0xF00006F4)->bit14
#define GPTU_SRC2_SETR           ((T_Reg32 *) 0xF00006F4)->bit15
#define GPTU_SRC2_SRE            ((T_Reg32 *) 0xF00006F4)->bit12
#define GPTU_SRC2_SRR            ((T_Reg32 *) 0xF00006F4)->bit13
#define GPTU_SRC2_TOS            ((T_Reg32 *) 0xF00006F4)->bit10

// GPTU Service Request Control Register 3
#define GPTU_SRC3              (*((uword volatile *) 0xF00006F0))
#define GPTU_SRC3_CLRR           ((T_Reg32 *) 0xF00006F0)->bit14
#define GPTU_SRC3_SETR           ((T_Reg32 *) 0xF00006F0)->bit15
#define GPTU_SRC3_SRE            ((T_Reg32 *) 0xF00006F0)->bit12
#define GPTU_SRC3_SRR            ((T_Reg32 *) 0xF00006F0)->bit13
#define GPTU_SRC3_TOS            ((T_Reg32 *) 0xF00006F0)->bit10

// GPTU Service Request Control Register 4
#define GPTU_SRC4              (*((uword volatile *) 0xF00006EC))
#define GPTU_SRC4_CLRR           ((T_Reg32 *) 0xF00006EC)->bit14
#define GPTU_SRC4_SETR           ((T_Reg32 *) 0xF00006EC)->bit15
#define GPTU_SRC4_SRE            ((T_Reg32 *) 0xF00006EC)->bit12
#define GPTU_SRC4_SRR            ((T_Reg32 *) 0xF00006EC)->bit13
#define GPTU_SRC4_TOS            ((T_Reg32 *) 0xF00006EC)->bit10

// GPTU Service Request Control Register 5
#define GPTU_SRC5              (*((uword volatile *) 0xF00006E8))
#define GPTU_SRC5_CLRR           ((T_Reg32 *) 0xF00006E8)->bit14
#define GPTU_SRC5_SETR           ((T_Reg32 *) 0xF00006E8)->bit15
#define GPTU_SRC5_SRE            ((T_Reg32 *) 0xF00006E8)->bit12
#define GPTU_SRC5_SRR            ((T_Reg32 *) 0xF00006E8)->bit13
#define GPTU_SRC5_TOS            ((T_Reg32 *) 0xF00006E8)->bit10

// GPTU Service Request Control Register 6
#define GPTU_SRC6              (*((uword volatile *) 0xF00006E4))
#define GPTU_SRC6_CLRR           ((T_Reg32 *) 0xF00006E4)->bit14
#define GPTU_SRC6_SETR           ((T_Reg32 *) 0xF00006E4)->bit15
#define GPTU_SRC6_SRE            ((T_Reg32 *) 0xF00006E4)->bit12
#define GPTU_SRC6_SRR            ((T_Reg32 *) 0xF00006E4)->bit13
#define GPTU_SRC6_TOS            ((T_Reg32 *) 0xF00006E4)->bit10

// GPTU Service Request Control Register 7
#define GPTU_SRC7              (*((uword volatile *) 0xF00006E0))
#define GPTU_SRC7_CLRR           ((T_Reg32 *) 0xF00006E0)->bit14
#define GPTU_SRC7_SETR           ((T_Reg32 *) 0xF00006E0)->bit15
#define GPTU_SRC7_SRE            ((T_Reg32 *) 0xF00006E0)->bit12
#define GPTU_SRC7_SRR            ((T_Reg32 *) 0xF00006E0)->bit13
#define GPTU_SRC7_TOS            ((T_Reg32 *) 0xF00006E0)->bit10

// GPTU Service Request Source Select Register
#define GPTU_SRSEL             (*((uword volatile *) 0xF00006DC))

// GPTU Timers T0, T1 and T2 Run Control Register
#define GPTU_T012RUN           (*((uword volatile *) 0xF0000660))
#define GPTU_T012RUN_T0ARUN      ((T_Reg32 *) 0xF0000660)->bit0
#define GPTU_T012RUN_T0BRUN      ((T_Reg32 *) 0xF0000660)->bit1
#define GPTU_T012RUN_T0CRUN      ((T_Reg32 *) 0xF0000660)->bit2
#define GPTU_T012RUN_T0DRUN      ((T_Reg32 *) 0xF0000660)->bit3
#define GPTU_T012RUN_T1ARUN      ((T_Reg32 *) 0xF0000660)->bit4
#define GPTU_T012RUN_T1BRUN      ((T_Reg32 *) 0xF0000660)->bit5
#define GPTU_T012RUN_T1CRUN      ((T_Reg32 *) 0xF0000660)->bit6
#define GPTU_T012RUN_T1DRUN      ((T_Reg32 *) 0xF0000660)->bit7
#define GPTU_T012RUN_T2ACLRR     ((T_Reg32 *) 0xF0000660)->bit10
#define GPTU_T012RUN_T2ARUN      ((T_Reg32 *) 0xF0000660)->bit8
#define GPTU_T012RUN_T2ASETR     ((T_Reg32 *) 0xF0000660)->bit9
#define GPTU_T012RUN_T2BCLRR     ((T_Reg32 *) 0xF0000660)->bit14
#define GPTU_T012RUN_T2BRUN      ((T_Reg32 *) 0xF0000660)->bit12
#define GPTU_T012RUN_T2BSETR     ((T_Reg32 *) 0xF0000660)->bit13

// GPTU Timer T0 and T1 Input and Reload Source Selection Register
#define GPTU_T01IRS            (*((uword volatile *) 0xF0000610))
#define GPTU_T01IRS_T0AREL       ((T_Reg32 *) 0xF0000610)->bit16
#define GPTU_T01IRS_T0BREL       ((T_Reg32 *) 0xF0000610)->bit17
#define GPTU_T01IRS_T0CREL       ((T_Reg32 *) 0xF0000610)->bit18
#define GPTU_T01IRS_T0DREL       ((T_Reg32 *) 0xF0000610)->bit19
#define GPTU_T01IRS_T0INC        ((T_Reg32 *) 0xF0000610)->bit24
#define GPTU_T01IRS_T1AREL       ((T_Reg32 *) 0xF0000610)->bit20
#define GPTU_T01IRS_T1BREL       ((T_Reg32 *) 0xF0000610)->bit21
#define GPTU_T01IRS_T1CREL       ((T_Reg32 *) 0xF0000610)->bit22
#define GPTU_T01IRS_T1DREL       ((T_Reg32 *) 0xF0000610)->bit23
#define GPTU_T01IRS_T1INC        ((T_Reg32 *) 0xF0000610)->bit25

// GPTU  Timer T0 and T1 Output, Trigger and Service Request Register
#define GPTU_T01OTS            (*((uword volatile *) 0xF0000614))

// GPTU Timer T0 Count Register (T0C, T0B, T0A)
#define GPTU_T0CBA             (*((uword volatile *) 0xF0000638))

// GPTU Timer T0 Count Register (T0D, T0C, T0B,T0A)
#define GPTU_T0DCBA            (*((uword volatile *) 0xF0000634))

// GPTU Timer T0 Reload Register (T0RC, T0RB, T0RA)
#define GPTU_T0RCBA            (*((uword volatile *) 0xF0000640))

// GPTU Timer T0 Reload Register (T0RD, T0RC, T0RB,T0RA)
#define GPTU_T0RDCBA           (*((uword volatile *) 0xF000063C))

// GPTU Timer T1 Count Register (T1C, T1B, T1A)
#define GPTU_T1CBA             (*((uword volatile *) 0xF0000648))

// GPTU Timer T1 Count Register (T1D, T1C, T1B,T1A)
#define GPTU_T1DCBA            (*((uword volatile *) 0xF0000644))

// GPTU Timer T1 Reload Register (T1RC, T1RB, T1RA)
#define GPTU_T1RCBA            (*((uword volatile *) 0xF0000650))

// GPTU Timer T1 Reload Register (T1RD, T1RC, T1RB,T1RA)
#define GPTU_T1RDCBA           (*((uword volatile *) 0xF000064C))

// GPTU Timer T2 Count Register
#define GPTU_T2                (*((uword volatile *) 0xF0000654))

// GPTU Timer T2/T2A External Input Selection Register
#define GPTU_T2AIS             (*((uword volatile *) 0xF0000620))

// GPTU Timer T2B External Input Selection Register
#define GPTU_T2BIS             (*((uword volatile *) 0xF0000624))

// GPTU Timer T2 Control Register
#define GPTU_T2CON             (*((uword volatile *) 0xF0000618))
#define GPTU_T2CON_T2ACOS        ((T_Reg32 *) 0xF0000618)->bit8
#define GPTU_T2CON_T2ADIR        ((T_Reg32 *) 0xF0000618)->bit12
#define GPTU_T2CON_T2BCOS        ((T_Reg32 *) 0xF0000618)->bit24
#define GPTU_T2CON_T2BDIR        ((T_Reg32 *) 0xF0000618)->bit28
#define GPTU_T2CON_T2SPLIT       ((T_Reg32 *) 0xF0000618)->bit15

// GPTU Timer T2 External Input Edge Selection Register
#define GPTU_T2ES              (*((uword volatile *) 0xF0000628))

// GPTU Timer T2 Reload/Capture Register 0
#define GPTU_T2RC0             (*((uword volatile *) 0xF0000658))

// GPTU Timer T2 Reload/Capture Register 1
#define GPTU_T2RC1             (*((uword volatile *) 0xF000065C))

// GPTU Timer T2 Reload/Capture Control Register
#define GPTU_T2RCCON           (*((uword volatile *) 0xF000061C))

// ICU Interrupt Control Register
#define ICR                    (*((uword volatile *) 0xF7E1FE2C))
#define ICR_CONECYC              0x04000000
#define ICR_IE                   0x00000100

// Interrupt Gating Register 0
#define IGCR0                  (*((uword volatile *) 0xF00000C0))
#define IGCR0_GEEN0              ((T_Reg32 *) 0xF00000C0)->bit13
#define IGCR0_GEEN1              ((T_Reg32 *) 0xF00000C0)->bit29
#define IGCR0_IPEN00             ((T_Reg32 *) 0xF00000C0)->bit0
#define IGCR0_IPEN01             ((T_Reg32 *) 0xF00000C0)->bit1
#define IGCR0_IPEN02             ((T_Reg32 *) 0xF00000C0)->bit2
#define IGCR0_IPEN03             ((T_Reg32 *) 0xF00000C0)->bit3
#define IGCR0_IPEN10             ((T_Reg32 *) 0xF00000C0)->bit16
#define IGCR0_IPEN11             ((T_Reg32 *) 0xF00000C0)->bit17
#define IGCR0_IPEN12             ((T_Reg32 *) 0xF00000C0)->bit18
#define IGCR0_IPEN13             ((T_Reg32 *) 0xF00000C0)->bit19

// Interrupt Gating Register 1
#define IGCR1                  (*((uword volatile *) 0xF00000C4))
#define IGCR1_GEEN2              ((T_Reg32 *) 0xF00000C4)->bit13
#define IGCR1_GEEN3              ((T_Reg32 *) 0xF00000C4)->bit29
#define IGCR1_IPEN20             ((T_Reg32 *) 0xF00000C4)->bit0
#define IGCR1_IPEN21             ((T_Reg32 *) 0xF00000C4)->bit1
#define IGCR1_IPEN22             ((T_Reg32 *) 0xF00000C4)->bit2
#define IGCR1_IPEN23             ((T_Reg32 *) 0xF00000C4)->bit3
#define IGCR1_IPEN30             ((T_Reg32 *) 0xF00000C4)->bit16
#define IGCR1_IPEN31             ((T_Reg32 *) 0xF00000C4)->bit17
#define IGCR1_IPEN32             ((T_Reg32 *) 0xF00000C4)->bit18
#define IGCR1_IPEN33             ((T_Reg32 *) 0xF00000C4)->bit19

// IIC BUS Control Register
#define IIC_BUSCON             (*((uword volatile *) 0xF0100614))
#define IIC_BUSCON_BRPMOD        ((T_Reg32 *) 0xF0100614)->bit31
#define IIC_BUSCON_ICA0          ((T_Reg32 *) 0xF0100614)->bit16
#define IIC_BUSCON_ICA8          ((T_Reg32 *) 0xF0100614)->bit24
#define IIC_BUSCON_ICA9          ((T_Reg32 *) 0xF0100614)->bit25
#define IIC_BUSCON_SCLEN0        ((T_Reg32 *) 0xF0100614)->bit4
#define IIC_BUSCON_SCLEN1        ((T_Reg32 *) 0xF0100614)->bit5
#define IIC_BUSCON_SDAEN0        ((T_Reg32 *) 0xF0100614)->bit0
#define IIC_BUSCON_SDAEN1        ((T_Reg32 *) 0xF0100614)->bit1

// IIC Clock Control Register
#define IIC_CLC                (*((uword volatile *) 0xF0100600))
#define IIC_CLC_DISR             ((T_Reg32 *) 0xF0100600)->bit0
#define IIC_CLC_DISS             ((T_Reg32 *) 0xF0100600)->bit1
#define IIC_CLC_EDIS             ((T_Reg32 *) 0xF0100600)->bit3
#define IIC_CLC_FSOE             ((T_Reg32 *) 0xF0100600)->bit5
#define IIC_CLC_SBWE             ((T_Reg32 *) 0xF0100600)->bit4
#define IIC_CLC_SPEN             ((T_Reg32 *) 0xF0100600)->bit2

// IIC Module Identification Register
#define IIC_ID                 (*((uword volatile *) 0xF0100608))

// IIC Input Select Register
#define IIC_PISEL              (*((uword volatile *) 0xF0100604))
#define IIC_PISEL_SCLIS0         ((T_Reg32 *) 0xF0100604)->bit0
#define IIC_PISEL_SCLIS1         ((T_Reg32 *) 0xF0100604)->bit1
#define IIC_PISEL_SDAIS0         ((T_Reg32 *) 0xF0100604)->bit4
#define IIC_PISEL_SDAIS1         ((T_Reg32 *) 0xF0100604)->bit5

// Reset Transmit Buffer
#define IIC_RTB                (*((uword volatile *) 0xF0100618))

// System Control Register
#define IIC_SYSCON             (*((uword volatile *) 0xF0100610))
#define IIC_SYSCON_ACKDIS        ((T_Reg32 *) 0xF0100610)->bit21
#define IIC_SYSCON_ADR           ((T_Reg32 *) 0xF0100610)->bit0
#define IIC_SYSCON_AL            ((T_Reg32 *) 0xF0100610)->bit1
#define IIC_SYSCON_BB            ((T_Reg32 *) 0xF0100610)->bit4
#define IIC_SYSCON_BUM           ((T_Reg32 *) 0xF0100610)->bit20
#define IIC_SYSCON_IGE           ((T_Reg32 *) 0xF0100610)->bit24
#define IIC_SYSCON_INT           ((T_Reg32 *) 0xF0100610)->bit22
#define IIC_SYSCON_IRQD          ((T_Reg32 *) 0xF0100610)->bit5
#define IIC_SYSCON_IRQE          ((T_Reg32 *) 0xF0100610)->bit7
#define IIC_SYSCON_IRQP          ((T_Reg32 *) 0xF0100610)->bit6
#define IIC_SYSCON_LRB           ((T_Reg32 *) 0xF0100610)->bit3
#define IIC_SYSCON_M10           ((T_Reg32 *) 0xF0100610)->bit16
#define IIC_SYSCON_RMEN          ((T_Reg32 *) 0xF0100610)->bit15
#define IIC_SYSCON_RSC           ((T_Reg32 *) 0xF0100610)->bit17
#define IIC_SYSCON_SLA           ((T_Reg32 *) 0xF0100610)->bit2
#define IIC_SYSCON_STP           ((T_Reg32 *) 0xF0100610)->bit25
#define IIC_SYSCON_TRX           ((T_Reg32 *) 0xF0100610)->bit23
#define IIC_SYSCON_WMEN          ((T_Reg32 *) 0xF0100610)->bit31

// IIC Write Hardware Modifiied System Control
#define IIC_WHBSYSCON          (*((uword volatile *) 0xF0100620))
#define IIC_WHBSYSCON_CLRACKDIS  ((T_Reg32 *) 0xF0100620)->bit21
#define IIC_WHBSYSCON_CLRAL      ((T_Reg32 *) 0xF0100620)->bit1
#define IIC_WHBSYSCON_CLRBUM     ((T_Reg32 *) 0xF0100620)->bit19
#define IIC_WHBSYSCON_CLRIRQD    ((T_Reg32 *) 0xF0100620)->bit5
#define IIC_WHBSYSCON_CLRIRQE    ((T_Reg32 *) 0xF0100620)->bit7
#define IIC_WHBSYSCON_CLRIRQP    ((T_Reg32 *) 0xF0100620)->bit6
#define IIC_WHBSYSCON_CLRRMEN    ((T_Reg32 *) 0xF0100620)->bit14
#define IIC_WHBSYSCON_CLRRSC     ((T_Reg32 *) 0xF0100620)->bit16
#define IIC_WHBSYSCON_CLRSTP     ((T_Reg32 *) 0xF0100620)->bit25
#define IIC_WHBSYSCON_CLRTRX     ((T_Reg32 *) 0xF0100620)->bit23
#define IIC_WHBSYSCON_CLRWMEN    ((T_Reg32 *) 0xF0100620)->bit30
#define IIC_WHBSYSCON_SETACKDIS  ((T_Reg32 *) 0xF0100620)->bit22
#define IIC_WHBSYSCON_SETAL      ((T_Reg32 *) 0xF0100620)->bit2
#define IIC_WHBSYSCON_SETBUM     ((T_Reg32 *) 0xF0100620)->bit20
#define IIC_WHBSYSCON_SETIRQD    ((T_Reg32 *) 0xF0100620)->bit8
#define IIC_WHBSYSCON_SETIRQE    ((T_Reg32 *) 0xF0100620)->bit10
#define IIC_WHBSYSCON_SETIRQP    ((T_Reg32 *) 0xF0100620)->bit9
#define IIC_WHBSYSCON_SETRMEN    ((T_Reg32 *) 0xF0100620)->bit15
#define IIC_WHBSYSCON_SETRSC     ((T_Reg32 *) 0xF0100620)->bit17
#define IIC_WHBSYSCON_SETSTP     ((T_Reg32 *) 0xF0100620)->bit26
#define IIC_WHBSYSCON_SETTRX     ((T_Reg32 *) 0xF0100620)->bit24
#define IIC_WHBSYSCON_SETWMEN    ((T_Reg32 *) 0xF0100620)->bit31

// IIC Service Request Control Register 0
#define IIC_XP0SRC             (*((uword volatile *) 0xF01006FC))
#define IIC_XP0SRC_CLRR          ((T_Reg32 *) 0xF01006FC)->bit14
#define IIC_XP0SRC_SETR          ((T_Reg32 *) 0xF01006FC)->bit15
#define IIC_XP0SRC_SRE           ((T_Reg32 *) 0xF01006FC)->bit12
#define IIC_XP0SRC_SRR           ((T_Reg32 *) 0xF01006FC)->bit13
#define IIC_XP0SRC_TOS           ((T_Reg32 *) 0xF01006FC)->bit10

// IIC Service Request Control Register 1
#define IIC_XP1SRC             (*((uword volatile *) 0xF01006F8))
#define IIC_XP1SRC_CLRR          ((T_Reg32 *) 0xF01006F8)->bit14
#define IIC_XP1SRC_SETR          ((T_Reg32 *) 0xF01006F8)->bit15
#define IIC_XP1SRC_SRE           ((T_Reg32 *) 0xF01006F8)->bit12
#define IIC_XP1SRC_SRR           ((T_Reg32 *) 0xF01006F8)->bit13
#define IIC_XP1SRC_TOS           ((T_Reg32 *) 0xF01006F8)->bit10

// IIC Service Request Control Register 2
#define IIC_XP2SRC             (*((uword volatile *) 0xF01006F4))
#define IIC_XP2SRC_CLRR          ((T_Reg32 *) 0xF01006F4)->bit14
#define IIC_XP2SRC_SETR          ((T_Reg32 *) 0xF01006F4)->bit15
#define IIC_XP2SRC_SRE           ((T_Reg32 *) 0xF01006F4)->bit12
#define IIC_XP2SRC_SRR           ((T_Reg32 *) 0xF01006F4)->bit13
#define IIC_XP2SRC_TOS           ((T_Reg32 *) 0xF01006F4)->bit10

// Interrupt Stack Pointer
#define ISP                    (*((uword volatile *) 0xF7E1FE28))

// LBCU Module Identification Register
#define LBCU_ID                (*((uword volatile *) 0xF87FFE08))

// LMB Error Addres Register
#define LBCU_LEADDR            (*((uword volatile *) 0xF87FFE24))

// LMB Error Attributes Register
#define LBCU_LEATT             (*((uword volatile *) 0xF87FFE20))
#define LBCU_LEATT_LEC           ((T_Reg32 *) 0xF87FFE20)->bit0
#define LBCU_LEATT_LOC           ((T_Reg32 *) 0xF87FFE20)->bit15
#define LBCU_LEATT_NOS           ((T_Reg32 *) 0xF87FFE20)->bit14
#define LBCU_LEATT_RD            ((T_Reg32 *) 0xF87FFE20)->bit23
#define LBCU_LEATT_SVM           ((T_Reg32 *) 0xF87FFE20)->bit21
#define LBCU_LEATT_UIS           ((T_Reg32 *) 0xF87FFE20)->bit19
#define LBCU_LEATT_WR            ((T_Reg32 *) 0xF87FFE20)->bit22

// LMB Error Data Register (32 MSB's)
#define LBCU_LEDATH            (*((uword volatile *) 0xF87FFE2C))

// LMB Error Data Register (32 LSB's)
#define LBCU_LEDATL            (*((uword volatile *) 0xF87FFE28))

// PBCU Service Request Control Register
#define LBCU_SRC               (*((uword volatile *) 0xF87FFEFC))
#define LBCU_SRC_CLRR            ((T_Reg32 *) 0xF87FFEFC)->bit14
#define LBCU_SRC_SETR            ((T_Reg32 *) 0xF87FFEFC)->bit15
#define LBCU_SRC_SRE             ((T_Reg32 *) 0xF87FFEFC)->bit12
#define LBCU_SRC_SRR             ((T_Reg32 *) 0xF87FFEFC)->bit13
#define LBCU_SRC_TOS             ((T_Reg32 *) 0xF87FFEFC)->bit10

// Free Context List Limit Pointer
#define LCX                    (*((uword volatile *) 0xF7E1FE3C))

// LFI Configuration Register
#define LFI_CON                (*((uword volatile *) 0xF87FFF10))
#define LFI_CON_EBF              ((T_Reg32 *) 0xF87FFF10)->bit2
#define LFI_CON_EBL              ((T_Reg32 *) 0xF87FFF10)->bit1
#define LFI_CON_SPT              ((T_Reg32 *) 0xF87FFF10)->bit0

// LFI Module Identification Register
#define LFI_ID                 (*((uword volatile *) 0xF87FFF08))

// MAC Receive Interrupt Service Request Control Register 0
#define MACRX0SRC              (*((uword volatile *) 0xF0000080))
#define MACRX0SRC_CLRR           ((T_Reg32 *) 0xF0000080)->bit14
#define MACRX0SRC_SETR           ((T_Reg32 *) 0xF0000080)->bit15
#define MACRX0SRC_SRE            ((T_Reg32 *) 0xF0000080)->bit12
#define MACRX0SRC_SRR            ((T_Reg32 *) 0xF0000080)->bit13
#define MACRX0SRC_TOS            ((T_Reg32 *) 0xF0000080)->bit10

// MAC Receive Interrupt Service Request Control Register 1
#define MACRX1SRC              (*((uword volatile *) 0xF0000088))
#define MACRX1SRC_CLRR           ((T_Reg32 *) 0xF0000088)->bit14
#define MACRX1SRC_SETR           ((T_Reg32 *) 0xF0000088)->bit15
#define MACRX1SRC_SRE            ((T_Reg32 *) 0xF0000088)->bit12
#define MACRX1SRC_SRR            ((T_Reg32 *) 0xF0000088)->bit13
#define MACRX1SRC_TOS            ((T_Reg32 *) 0xF0000088)->bit10

// MAC Transmit Interrupt Service Request Control Register
#define MACTX0SRC              (*((uword volatile *) 0xF000007C))
#define MACTX0SRC_CLRR           ((T_Reg32 *) 0xF000007C)->bit14
#define MACTX0SRC_SETR           ((T_Reg32 *) 0xF000007C)->bit15
#define MACTX0SRC_SRE            ((T_Reg32 *) 0xF000007C)->bit12
#define MACTX0SRC_SRR            ((T_Reg32 *) 0xF000007C)->bit13
#define MACTX0SRC_TOS            ((T_Reg32 *) 0xF000007C)->bit10

// MAC Transmit Interrupt Service Request Control Register 1
#define MACTX1SRC              (*((uword volatile *) 0xF0000084))
#define MACTX1SRC_CLRR           ((T_Reg32 *) 0xF0000084)->bit14
#define MACTX1SRC_SETR           ((T_Reg32 *) 0xF0000084)->bit15
#define MACTX1SRC_SRE            ((T_Reg32 *) 0xF0000084)->bit12
#define MACTX1SRC_SRR            ((T_Reg32 *) 0xF0000084)->bit13
#define MACTX1SRC_TOS            ((T_Reg32 *) 0xF0000084)->bit10

// Manufacturer Identification Register
#define MANID                  (*((uword volatile *) 0xF0000070))

// MCHK Module Identification Register
#define MCHK_ID                (*((uword volatile *) 0xF010C208))

// MCHK Memory Checker Input Register
#define MCHK_IR                (*((uword volatile *) 0xF010C210))

// Memory Checker Result Register
#define MCHK_RR                (*((uword volatile *) 0xF010C214))

// Write Register
#define MCHK_WR                (*((uword volatile *) 0xF010C220))

// Access Enable Register
#define MLI0_AER               (*((uword volatile *) 0xF010C0B8))
#define MLI0_AER_AEN0            0x00000001
#define MLI0_AER_AEN1            0x00000002
#define MLI0_AER_AEN10           0x00000400
#define MLI0_AER_AEN11           0x00000800
#define MLI0_AER_AEN12           0x00001000
#define MLI0_AER_AEN13           0x00002000
#define MLI0_AER_AEN14           0x00004000
#define MLI0_AER_AEN15           0x00008000
#define MLI0_AER_AEN16           0x00010000
#define MLI0_AER_AEN17           0x00020000
#define MLI0_AER_AEN18           0x00040000
#define MLI0_AER_AEN19           0x00080000
#define MLI0_AER_AEN2            0x00000004
#define MLI0_AER_AEN20           0x00100000
#define MLI0_AER_AEN21           0x00200000
#define MLI0_AER_AEN22           0x00400000
#define MLI0_AER_AEN23           0x00800000
#define MLI0_AER_AEN24           0x01000000
#define MLI0_AER_AEN25           0x02000000
#define MLI0_AER_AEN26           0x04000000
#define MLI0_AER_AEN27           0x08000000
#define MLI0_AER_AEN28           0x10000000
#define MLI0_AER_AEN29           0x20000000
#define MLI0_AER_AEN3            0x00000008
#define MLI0_AER_AEN30           0x40000000
#define MLI0_AER_AEN31           0x80000000
#define MLI0_AER_AEN4            0x00000010
#define MLI0_AER_AEN5            0x00000020
#define MLI0_AER_AEN6            0x00000040
#define MLI0_AER_AEN7            0x00000080
#define MLI0_AER_AEN8            0x00000100
#define MLI0_AER_AEN9            0x00000200

// Access Range Register
#define MLI0_ARR               (*((uword volatile *) 0xF010C0BC))

// MLI Fractional Divider Register
#define MLI0_FDR               (*((uword volatile *) 0xF010C00C))
#define MLI0_FDR_DISCLK          0x80000000
#define MLI0_FDR_ENHW            0x40000000
#define MLI0_FDR_SM              0x00000800
#define MLI0_FDR_SUSACK          0x10000000
#define MLI0_FDR_SUSREQ          0x20000000

// MLI Global Interrupt Set Register
#define MLI0_GINTR             (*((uword volatile *) 0xF010C0B0))
#define MLI0_GINTR_SIMLI0        0x00000001
#define MLI0_GINTR_SIMLI1        0x00000002
#define MLI0_GINTR_SIMLI2        0x00000004
#define MLI0_GINTR_SIMLI3        0x00000008
#define MLI0_GINTR_SIMLI4        0x00000010
#define MLI0_GINTR_SIMLI5        0x00000020
#define MLI0_GINTR_SIMLI6        0x00000040
#define MLI0_GINTR_SIMLI7        0x00000080

// MLI Module Identification Register
#define MLI0_ID                (*((uword volatile *) 0xF010C008))

// Output Input Control Register
#define MLI0_OICR              (*((uword volatile *) 0xF010C0B4))
#define MLI0_OICR_RCE            0x10000000
#define MLI0_OICR_RCP            0x08000000
#define MLI0_OICR_RDP            0x80000000
#define MLI0_OICR_RRPA           0x00040000
#define MLI0_OICR_RRPB           0x00080000
#define MLI0_OICR_RRPC           0x00100000
#define MLI0_OICR_RRPD           0x00200000
#define MLI0_OICR_RVE            0x00008000
#define MLI0_OICR_RVP            0x01000000
#define MLI0_OICR_TCE            0x00001000
#define MLI0_OICR_TCP            0x00002000
#define MLI0_OICR_TDP            0x00004000
#define MLI0_OICR_TRE            0x00000800
#define MLI0_OICR_TRP            0x00000400
#define MLI0_OICR_TVEA           0x00000001
#define MLI0_OICR_TVEB           0x00000002
#define MLI0_OICR_TVEC           0x00000004
#define MLI0_OICR_TVED           0x00000008
#define MLI0_OICR_TVPA           0x00000010
#define MLI0_OICR_TVPB           0x00000020
#define MLI0_OICR_TVPC           0x00000040
#define MLI0_OICR_TVPD           0x00000080

// Receiver Address Register
#define MLI0_RADRR             (*((uword volatile *) 0xF010C08C))

// Receiver Control Register
#define MLI0_RCR               (*((uword volatile *) 0xF010C068))
#define MLI0_RCR_BEN             0x00100000
#define MLI0_RCR_MOD             0x00000100
#define MLI0_RCR_PE              0x00002000
#define MLI0_RCR_RCVRST          0x01000000

// Receiver Data Register
#define MLI0_RDATAR            (*((uword volatile *) 0xF010C090))

// Receiver Interrupt Enable Register
#define MLI0_RIER              (*((uword volatile *) 0xF010C0A4))
#define MLI0_RIER_CFRIE0         0x00000004
#define MLI0_RIER_CFRIE1         0x00000008
#define MLI0_RIER_CFRIE2         0x00000010
#define MLI0_RIER_CFRIE3         0x00000020
#define MLI0_RIER_CFRIR0         0x00040000
#define MLI0_RIER_CFRIR1         0x00080000
#define MLI0_RIER_CFRIR2         0x00100000
#define MLI0_RIER_CFRIR3         0x00200000
#define MLI0_RIER_DRAIE          0x00000200
#define MLI0_RIER_DRAIR          0x02000000
#define MLI0_RIER_ICE            0x00000040
#define MLI0_RIER_ICER           0x00400000
#define MLI0_RIER_MEIR           0x00020000
#define MLI0_RIER_MPEIR          0x01000000
#define MLI0_RIER_NFRIR          0x00010000
#define MLI0_RIER_PEIR           0x00800000

// Receiver Interrupt Node Pointer Register
#define MLI0_RINPR             (*((uword volatile *) 0xF010C0AC))

// Receiver Interrupt Status Register
#define MLI0_RISR              (*((uword volatile *) 0xF010C0A8))
#define MLI0_RISR_CFRI0          0x00000004
#define MLI0_RISR_CFRI1          0x00000008
#define MLI0_RISR_CFRI2          0x00000010
#define MLI0_RISR_CFRI3          0x00000020
#define MLI0_RISR_DRAI           0x00000200
#define MLI0_RISR_IC             0x00000040
#define MLI0_RISR_MEI            0x00000002
#define MLI0_RISR_MPEI           0x00000100
#define MLI0_RISR_NFRI           0x00000001
#define MLI0_RISR_PEI            0x00000080

// Receiver Pipe 0 Base Address Register
#define MLI0_RP0BAR            (*((uword volatile *) 0xF010C06C))

// Receiver Pipe 0 Status Register
#define MLI0_RP0STATR          (*((uword volatile *) 0xF010C07C))

// Receiver Pipe 1 Base Address Register
#define MLI0_RP1BAR            (*((uword volatile *) 0xF010C070))

// Receiver Pipe 1 Status Register
#define MLI0_RP1STATR          (*((uword volatile *) 0xF010C080))

// Receiver Pipe 2 Base Address Register
#define MLI0_RP2BAR            (*((uword volatile *) 0xF010C074))

// Receiver Pipe 2 Status Register
#define MLI0_RP2STATR          (*((uword volatile *) 0xF010C084))

// Receiver Pipe 3 Base Address Register
#define MLI0_RP3BAR            (*((uword volatile *) 0xF010C078))

// Receiver Pipe 3 Status Register
#define MLI0_RP3STATR          (*((uword volatile *) 0xF010C088))

// Set Clear Register
#define MLI0_SCR               (*((uword volatile *) 0xF010C094))
#define MLI0_SCR_CAV             0x01000000
#define MLI0_SCR_CBAV            0x00200000
#define MLI0_SCR_CCIV0           0x10000000
#define MLI0_SCR_CCIV1           0x20000000
#define MLI0_SCR_CCIV2           0x40000000
#define MLI0_SCR_CCIV3           0x80000000
#define MLI0_SCR_CCV0            0x00001000
#define MLI0_SCR_CCV1            0x00002000
#define MLI0_SCR_CCV2            0x00004000
#define MLI0_SCR_CCV3            0x00008000
#define MLI0_SCR_CDV0            0x00000100
#define MLI0_SCR_CDV1            0x00000200
#define MLI0_SCR_CDV2            0x00000400
#define MLI0_SCR_CDV3            0x00000800
#define MLI0_SCR_CMOD            0x00010000
#define MLI0_SCR_CNAE            0x08000000
#define MLI0_SCR_CRPE            0x02000000
#define MLI0_SCR_CTPE            0x04000000
#define MLI0_SCR_SCV0            0x00000001
#define MLI0_SCR_SCV1            0x00000002
#define MLI0_SCR_SCV2            0x00000004
#define MLI0_SCR_SCV3            0x00000008
#define MLI0_SCR_SMOD            0x00000010

// Transmitter Copy Base Address Register
#define MLI0_TCBAR             (*((uword volatile *) 0xF010C064))

// Transmitter Command Register
#define MLI0_TCMDR             (*((uword volatile *) 0xF010C028))

// Transmitter Control Register
#define MLI0_TCR               (*((uword volatile *) 0xF010C010))
#define MLI0_TCR_DNT             0x00000002
#define MLI0_TCR_MOD             0x00000001
#define MLI0_TCR_NO              0x00004000
#define MLI0_TCR_RTY             0x00000004
#define MLI0_TCR_TP              0x00008000

// Transmitter Data Read Answer Register
#define MLI0_TDRAR             (*((uword volatile *) 0xF010C050))

// Transmitter Interrupt Enable Register
#define MLI0_TIER              (*((uword volatile *) 0xF010C098))
#define MLI0_TIER_CFSIE0         0x00000010
#define MLI0_TIER_CFSIE1         0x00000020
#define MLI0_TIER_CFSIE2         0x00000040
#define MLI0_TIER_CFSIE3         0x00000080
#define MLI0_TIER_CFSIR0         0x00100000
#define MLI0_TIER_CFSIR1         0x00200000
#define MLI0_TIER_CFSIR2         0x00400000
#define MLI0_TIER_CFSIR3         0x00800000
#define MLI0_TIER_NFSIE0         0x00000001
#define MLI0_TIER_NFSIE1         0x00000002
#define MLI0_TIER_NFSIE2         0x00000004
#define MLI0_TIER_NFSIE3         0x00000008
#define MLI0_TIER_NFSIR0         0x00010000
#define MLI0_TIER_NFSIR1         0x00020000
#define MLI0_TIER_NFSIR2         0x00040000
#define MLI0_TIER_NFSIR3         0x00080000
#define MLI0_TIER_PEIE           0x00000100
#define MLI0_TIER_PEIR           0x01000000
#define MLI0_TIER_TEIE           0x00000200
#define MLI0_TIER_TEIR           0x02000000

// Transmitter Interrupt Node Pointer Register
#define MLI0_TINPR             (*((uword volatile *) 0xF010C0A0))

// Transmitter Interrupt Status Register
#define MLI0_TISR              (*((uword volatile *) 0xF010C09C))
#define MLI0_TISR_CFSI0          0x00000010
#define MLI0_TISR_CFSI1          0x00000020
#define MLI0_TISR_CFSI2          0x00000040
#define MLI0_TISR_CFSI3          0x00000080
#define MLI0_TISR_NFSI0          0x00000001
#define MLI0_TISR_NFSI1          0x00000002
#define MLI0_TISR_NFSI2          0x00000004
#define MLI0_TISR_NFSI3          0x00000008
#define MLI0_TISR_PEI            0x00000100
#define MLI0_TISR_TEI            0x00000200

// Transmitter Pipe 0 Address Offset Register
#define MLI0_TP0AOFR           (*((uword volatile *) 0xF010C030))

// Transmitter Pipe 0 Base Address Register
#define MLI0_TP0BAR            (*((uword volatile *) 0xF010C054))

// Transmitter Pipe 0 Data Register
#define MLI0_TP0DATAR          (*((uword volatile *) 0xF010C040))

// Transmitter Pipe 0 Status Register
#define MLI0_TP0STATR          (*((uword volatile *) 0xF010C018))
#define MLI0_TP0STATR_OP         0x00010000

// Transmitter Pipe 1 Address Offset Register
#define MLI0_TP1AOFR           (*((uword volatile *) 0xF010C034))

// Transmitter Pipe 1 Base Address Register
#define MLI0_TP1BAR            (*((uword volatile *) 0xF010C058))

// Transmitter Pipe 1 Data Register
#define MLI0_TP1DATAR          (*((uword volatile *) 0xF010C044))

// Transmitter Pipe 1 Status Register
#define MLI0_TP1STATR          (*((uword volatile *) 0xF010C01C))
#define MLI0_TP1STATR_OP         0x00010000

// Transmitter Pipe 2 Address Offset Register
#define MLI0_TP2AOFR           (*((uword volatile *) 0xF010C038))

// Transmitter Pipe 2 Base Address Register
#define MLI0_TP2BAR            (*((uword volatile *) 0xF010C05C))

// Transmitter Pipe 2 Data Register
#define MLI0_TP2DATAR          (*((uword volatile *) 0xF010C048))

// Transmitter Pipe 2 Status Register
#define MLI0_TP2STATR          (*((uword volatile *) 0xF010C020))
#define MLI0_TP2STATR_OP         0x00010000

// Transmitter Pipe 3 Address Offset Register
#define MLI0_TP3AOFR           (*((uword volatile *) 0xF010C03C))

// Transmitter Pipe 3 Base Address Register
#define MLI0_TP3BAR            (*((uword volatile *) 0xF010C060))

// Transmitter Pipe 3 Data Register
#define MLI0_TP3DATAR          (*((uword volatile *) 0xF010C04C))

// Transmitter Pipe 3 Status Register
#define MLI0_TP3STATR          (*((uword volatile *) 0xF010C024))
#define MLI0_TP3STATR_OP         0x00010000

// Transmitter Registers Status Register
#define MLI0_TRSTATR           (*((uword volatile *) 0xF010C02C))
#define MLI0_TRSTATR_AV          0x00000100
#define MLI0_TRSTATR_BAV         0x00000200
#define MLI0_TRSTATR_CV0         0x00000010
#define MLI0_TRSTATR_CV1         0x00000020
#define MLI0_TRSTATR_CV2         0x00000040
#define MLI0_TRSTATR_CV3         0x00000080
#define MLI0_TRSTATR_DV0         0x00010000
#define MLI0_TRSTATR_DV1         0x00020000
#define MLI0_TRSTATR_DV2         0x00040000
#define MLI0_TRSTATR_DV3         0x00080000
#define MLI0_TRSTATR_RP0         0x00100000
#define MLI0_TRSTATR_RP1         0x00200000
#define MLI0_TRSTATR_RP2         0x00400000
#define MLI0_TRSTATR_RP3         0x00800000

// Transmitter Status Register
#define MLI0_TSTATR            (*((uword volatile *) 0xF010C014))
#define MLI0_TSTATR_NAE          0x00000100
#define MLI0_TSTATR_PE           0x00000080

// Access Enable Register
#define MLI1_AER               (*((uword volatile *) 0xF010C1B8))
#define MLI1_AER_AEN0            0x00000001
#define MLI1_AER_AEN1            0x00000002
#define MLI1_AER_AEN10           0x00000400
#define MLI1_AER_AEN11           0x00000800
#define MLI1_AER_AEN12           0x00001000
#define MLI1_AER_AEN13           0x00002000
#define MLI1_AER_AEN14           0x00004000
#define MLI1_AER_AEN15           0x00008000
#define MLI1_AER_AEN16           0x00010000
#define MLI1_AER_AEN17           0x00020000
#define MLI1_AER_AEN18           0x00040000
#define MLI1_AER_AEN19           0x00080000
#define MLI1_AER_AEN2            0x00000004
#define MLI1_AER_AEN20           0x00100000
#define MLI1_AER_AEN21           0x00200000
#define MLI1_AER_AEN22           0x00400000
#define MLI1_AER_AEN23           0x00800000
#define MLI1_AER_AEN24           0x01000000
#define MLI1_AER_AEN25           0x02000000
#define MLI1_AER_AEN26           0x04000000
#define MLI1_AER_AEN27           0x08000000
#define MLI1_AER_AEN28           0x10000000
#define MLI1_AER_AEN29           0x20000000
#define MLI1_AER_AEN3            0x00000008
#define MLI1_AER_AEN30           0x40000000
#define MLI1_AER_AEN31           0x80000000
#define MLI1_AER_AEN4            0x00000010
#define MLI1_AER_AEN5            0x00000020
#define MLI1_AER_AEN6            0x00000040
#define MLI1_AER_AEN7            0x00000080
#define MLI1_AER_AEN8            0x00000100
#define MLI1_AER_AEN9            0x00000200

// Access Range Register
#define MLI1_ARR               (*((uword volatile *) 0xF010C1BC))

// MLI Fractional Divider Register
#define MLI1_FDR               (*((uword volatile *) 0xF010C10C))
#define MLI1_FDR_DISCLK          0x80000000
#define MLI1_FDR_ENHW            0x40000000
#define MLI1_FDR_SM              0x00000800
#define MLI1_FDR_SUSACK          0x10000000
#define MLI1_FDR_SUSREQ          0x20000000

// MLI Global Interrupt Set Register
#define MLI1_GINTR             (*((uword volatile *) 0xF010C1B0))
#define MLI1_GINTR_SIMLI0        0x00000001
#define MLI1_GINTR_SIMLI1        0x00000002
#define MLI1_GINTR_SIMLI2        0x00000004
#define MLI1_GINTR_SIMLI3        0x00000008
#define MLI1_GINTR_SIMLI4        0x00000010
#define MLI1_GINTR_SIMLI5        0x00000020
#define MLI1_GINTR_SIMLI6        0x00000040
#define MLI1_GINTR_SIMLI7        0x00000080

// MLI Module Identification Register
#define MLI1_ID                (*((uword volatile *) 0xF010C108))

// Output Input Control Register
#define MLI1_OICR              (*((uword volatile *) 0xF010C1B4))
#define MLI1_OICR_RCE            0x10000000
#define MLI1_OICR_RCP            0x08000000
#define MLI1_OICR_RDP            0x80000000
#define MLI1_OICR_RRPA           0x00040000
#define MLI1_OICR_RRPB           0x00080000
#define MLI1_OICR_RRPC           0x00100000
#define MLI1_OICR_RRPD           0x00200000
#define MLI1_OICR_RVE            0x00008000
#define MLI1_OICR_RVP            0x01000000
#define MLI1_OICR_TCE            0x00001000
#define MLI1_OICR_TCP            0x00002000
#define MLI1_OICR_TDP            0x00004000
#define MLI1_OICR_TRE            0x00000800
#define MLI1_OICR_TRP            0x00000400
#define MLI1_OICR_TVEA           0x00000001
#define MLI1_OICR_TVEB           0x00000002
#define MLI1_OICR_TVEC           0x00000004
#define MLI1_OICR_TVED           0x00000008
#define MLI1_OICR_TVPA           0x00000010
#define MLI1_OICR_TVPB           0x00000020
#define MLI1_OICR_TVPC           0x00000040
#define MLI1_OICR_TVPD           0x00000080

// Receiver Address Register
#define MLI1_RADRR             (*((uword volatile *) 0xF010C18C))

// Receiver Control Register
#define MLI1_RCR               (*((uword volatile *) 0xF010C168))
#define MLI1_RCR_BEN             0x00100000
#define MLI1_RCR_MOD             0x00000100
#define MLI1_RCR_PE              0x00002000
#define MLI1_RCR_RCVRST          0x01000000

// Receiver Data Register
#define MLI1_RDATAR            (*((uword volatile *) 0xF010C190))

// Receiver Interrupt Enable Register
#define MLI1_RIER              (*((uword volatile *) 0xF010C1A4))
#define MLI1_RIER_CFRIE0         0x00000004
#define MLI1_RIER_CFRIE1         0x00000008
#define MLI1_RIER_CFRIE2         0x00000010
#define MLI1_RIER_CFRIE3         0x00000020
#define MLI1_RIER_CFRIR0         0x00040000
#define MLI1_RIER_CFRIR1         0x00080000
#define MLI1_RIER_CFRIR2         0x00100000
#define MLI1_RIER_CFRIR3         0x00200000
#define MLI1_RIER_DRAIE          0x00000200
#define MLI1_RIER_DRAIR          0x02000000
#define MLI1_RIER_ICE            0x00000040
#define MLI1_RIER_ICER           0x00400000
#define MLI1_RIER_MEIR           0x00020000
#define MLI1_RIER_MPEIR          0x01000000
#define MLI1_RIER_NFRIR          0x00010000
#define MLI1_RIER_PEIR           0x00800000

// Receiver Interrupt Node Pointer Register
#define MLI1_RINPR             (*((uword volatile *) 0xF010C1AC))

// Receiver Interrupt Status Register
#define MLI1_RISR              (*((uword volatile *) 0xF010C1A8))
#define MLI1_RISR_CFRI0          0x00000004
#define MLI1_RISR_CFRI1          0x00000008
#define MLI1_RISR_CFRI2          0x00000010
#define MLI1_RISR_CFRI3          0x00000020
#define MLI1_RISR_DRAI           0x00000200
#define MLI1_RISR_IC             0x00000040
#define MLI1_RISR_MEI            0x00000002
#define MLI1_RISR_MPEI           0x00000100
#define MLI1_RISR_NFRI           0x00000001
#define MLI1_RISR_PEI            0x00000080

// Receiver Pipe 0 Base Address Register
#define MLI1_RP0BAR            (*((uword volatile *) 0xF010C16C))

// Receiver Pipe 0 Status Register
#define MLI1_RP0STATR          (*((uword volatile *) 0xF010C17C))

// Receiver Pipe 1 Base Address Register
#define MLI1_RP1BAR            (*((uword volatile *) 0xF010C170))

// Receiver Pipe 1 Status Register
#define MLI1_RP1STATR          (*((uword volatile *) 0xF010C180))

// Receiver Pipe 2 Base Address Register
#define MLI1_RP2BAR            (*((uword volatile *) 0xF010C174))

// Receiver Pipe 2 Status Register
#define MLI1_RP2STATR          (*((uword volatile *) 0xF010C184))

// Receiver Pipe 3 Base Address Register
#define MLI1_RP3BAR            (*((uword volatile *) 0xF010C178))

// Receiver Pipe 3 Status Register
#define MLI1_RP3STATR          (*((uword volatile *) 0xF010C188))

// Set Clear Register
#define MLI1_SCR               (*((uword volatile *) 0xF010C194))
#define MLI1_SCR_CAV             0x01000000
#define MLI1_SCR_CBAV            0x00200000
#define MLI1_SCR_CCIV0           0x10000000
#define MLI1_SCR_CCIV1           0x20000000
#define MLI1_SCR_CCIV2           0x40000000
#define MLI1_SCR_CCIV3           0x80000000
#define MLI1_SCR_CCV0            0x00001000
#define MLI1_SCR_CCV1            0x00002000
#define MLI1_SCR_CCV2            0x00004000
#define MLI1_SCR_CCV3            0x00008000
#define MLI1_SCR_CDV0            0x00000100
#define MLI1_SCR_CDV1            0x00000200
#define MLI1_SCR_CDV2            0x00000400
#define MLI1_SCR_CDV3            0x00000800
#define MLI1_SCR_CMOD            0x00010000
#define MLI1_SCR_CNAE            0x08000000
#define MLI1_SCR_CRPE            0x02000000
#define MLI1_SCR_CTPE            0x04000000
#define MLI1_SCR_SCV0            0x00000001
#define MLI1_SCR_SCV1            0x00000002
#define MLI1_SCR_SCV2            0x00000004
#define MLI1_SCR_SCV3            0x00000008
#define MLI1_SCR_SMOD            0x00000010

// Transmitter Copy Base Address Register
#define MLI1_TCBAR             (*((uword volatile *) 0xF010C164))

// Transmitter Command Register
#define MLI1_TCMDR             (*((uword volatile *) 0xF010C128))

// Transmitter Control Register
#define MLI1_TCR               (*((uword volatile *) 0xF010C110))
#define MLI1_TCR_DNT             0x00000002
#define MLI1_TCR_MOD             0x00000001
#define MLI1_TCR_NO              0x00004000
#define MLI1_TCR_RTY             0x00000004
#define MLI1_TCR_TP              0x00008000

// Transmitter Data Read Answer Register
#define MLI1_TDRAR             (*((uword volatile *) 0xF010C150))

// Transmitter Interrupt Enable Register
#define MLI1_TIER              (*((uword volatile *) 0xF010C198))
#define MLI1_TIER_CFSIE0         0x00000010
#define MLI1_TIER_CFSIE1         0x00000020
#define MLI1_TIER_CFSIE2         0x00000040
#define MLI1_TIER_CFSIE3         0x00000080
#define MLI1_TIER_CFSIR0         0x00100000
#define MLI1_TIER_CFSIR1         0x00200000
#define MLI1_TIER_CFSIR2         0x00400000
#define MLI1_TIER_CFSIR3         0x00800000
#define MLI1_TIER_NFSIE0         0x00000001
#define MLI1_TIER_NFSIE1         0x00000002
#define MLI1_TIER_NFSIE2         0x00000004
#define MLI1_TIER_NFSIE3         0x00000008
#define MLI1_TIER_NFSIR0         0x00010000
#define MLI1_TIER_NFSIR1         0x00020000
#define MLI1_TIER_NFSIR2         0x00040000
#define MLI1_TIER_NFSIR3         0x00080000
#define MLI1_TIER_PEIE           0x00000100
#define MLI1_TIER_PEIR           0x01000000
#define MLI1_TIER_TEIE           0x00000200
#define MLI1_TIER_TEIR           0x02000000

// Transmitter Interrupt Node Pointer Register
#define MLI1_TINPR             (*((uword volatile *) 0xF010C1A0))

// Transmitter Interrupt Status Register
#define MLI1_TISR              (*((uword volatile *) 0xF010C19C))
#define MLI1_TISR_CFSI0          0x00000010
#define MLI1_TISR_CFSI1          0x00000020
#define MLI1_TISR_CFSI2          0x00000040
#define MLI1_TISR_CFSI3          0x00000080
#define MLI1_TISR_NFSI0          0x00000001
#define MLI1_TISR_NFSI1          0x00000002
#define MLI1_TISR_NFSI2          0x00000004
#define MLI1_TISR_NFSI3          0x00000008
#define MLI1_TISR_PEI            0x00000100
#define MLI1_TISR_TEI            0x00000200

// Transmitter Pipe 0 Address Offset Register
#define MLI1_TP0AOFR           (*((uword volatile *) 0xF010C130))

// Transmitter Pipe 0 Base Address Register
#define MLI1_TP0BAR            (*((uword volatile *) 0xF010C154))

// Transmitter Pipe 0 Data Register
#define MLI1_TP0DATAR          (*((uword volatile *) 0xF010C140))

// Transmitter Pipe 0 Status Register
#define MLI1_TP0STATR          (*((uword volatile *) 0xF010C118))
#define MLI1_TP0STATR_OP         0x00010000

// Transmitter Pipe 1 Address Offset Register
#define MLI1_TP1AOFR           (*((uword volatile *) 0xF010C134))

// Transmitter Pipe 1 Base Address Register
#define MLI1_TP1BAR            (*((uword volatile *) 0xF010C158))

// Transmitter Pipe 1 Data Register
#define MLI1_TP1DATAR          (*((uword volatile *) 0xF010C144))

// Transmitter Pipe 1 Status Register
#define MLI1_TP1STATR          (*((uword volatile *) 0xF010C11C))
#define MLI1_TP1STATR_OP         0x00010000

// Transmitter Pipe 2 Address Offset Register
#define MLI1_TP2AOFR           (*((uword volatile *) 0xF010C138))

// Transmitter Pipe 2 Base Address Register
#define MLI1_TP2BAR            (*((uword volatile *) 0xF010C15C))

// Transmitter Pipe 2 Data Register
#define MLI1_TP2DATAR          (*((uword volatile *) 0xF010C148))

// Transmitter Pipe 2 Status Register
#define MLI1_TP2STATR          (*((uword volatile *) 0xF010C120))
#define MLI1_TP2STATR_OP         0x00010000

// Transmitter Pipe 3 Address Offset Register
#define MLI1_TP3AOFR           (*((uword volatile *) 0xF010C13C))

// Transmitter Pipe 3 Base Address Register
#define MLI1_TP3BAR            (*((uword volatile *) 0xF010C160))

// Transmitter Pipe 3 Data Register
#define MLI1_TP3DATAR          (*((uword volatile *) 0xF010C14C))

// Transmitter Pipe 3 Status Register
#define MLI1_TP3STATR          (*((uword volatile *) 0xF010C124))
#define MLI1_TP3STATR_OP         0x00010000

// Transmitter Registers Status Register
#define MLI1_TRSTATR           (*((uword volatile *) 0xF010C12C))
#define MLI1_TRSTATR_AV          0x00000100
#define MLI1_TRSTATR_BAV         0x00000200
#define MLI1_TRSTATR_CV0         0x00000010
#define MLI1_TRSTATR_CV1         0x00000020
#define MLI1_TRSTATR_CV2         0x00000040
#define MLI1_TRSTATR_CV3         0x00000080
#define MLI1_TRSTATR_DV0         0x00010000
#define MLI1_TRSTATR_DV1         0x00020000
#define MLI1_TRSTATR_DV2         0x00040000
#define MLI1_TRSTATR_DV3         0x00080000
#define MLI1_TRSTATR_RP0         0x00100000
#define MLI1_TRSTATR_RP1         0x00200000
#define MLI1_TRSTATR_RP2         0x00400000
#define MLI1_TRSTATR_RP3         0x00800000

// Transmitter Status Register
#define MLI1_TSTATR            (*((uword volatile *) 0xF010C114))
#define MLI1_TSTATR_NAE          0x00000100
#define MLI1_TSTATR_PE           0x00000080

// MMU Address Space Identifier Register
#define MMU_ASI                (*((uword volatile *) 0xF7E18004))

// MMU Configuration Register
#define MMU_CON                (*((uword volatile *) 0xF7E18000))
#define MMU_CON_MXT              0x00008000
#define MMU_CON_V                0x00000001

// MMU Identification Register
#define MMU_ID                 (*((uword volatile *) 0xF7E18008))

// MMU Translation Fault Address Register
#define MMU_TFA                (*((uword volatile *) 0xF7E18018))

// MMU Translation Physical Address Register
#define MMU_TPA                (*((uword volatile *) 0xF7E18010))
#define MMU_TPA_C                0x04000000
#define MMU_TPA_G                0x08000000
#define MMU_TPA_RE               0x10000000
#define MMU_TPA_V                0x80000000
#define MMU_TPA_WE               0x20000000
#define MMU_TPA_XE               0x40000000

// MMU Translation Page Index Register
#define MMU_TPX                (*((uword volatile *) 0xF7E18014))

// MMU Translation Virtual Address Register
#define MMU_TVA                (*((uword volatile *) 0xF7E1800C))

// NMI Status Register
#define NMISR                  (*((uword volatile *) 0xF000002C))
#define NMISR_NMIDPM             ((T_Reg32 *) 0xF000002C)->bit4
#define NMISR_NMIEXT             ((T_Reg32 *) 0xF000002C)->bit0
#define NMISR_NMIPER             ((T_Reg32 *) 0xF000002C)->bit3
#define NMISR_NMIPLL             ((T_Reg32 *) 0xF000002C)->bit1
#define NMISR_NMIWDT             ((T_Reg32 *) 0xF000002C)->bit2

// Oscillator Control Register
#define OSC_CON                (*((uword volatile *) 0xF0000018))
#define OSC_CON_MOSC             ((T_Reg32 *) 0xF0000018)->bit0
#define OSC_CON_OGC              ((T_Reg32 *) 0xF0000018)->bit4
#define OSC_CON_ORDRES           ((T_Reg32 *) 0xF0000018)->bit2
#define OSC_CON_OSCR             ((T_Reg32 *) 0xF0000018)->bit1

// Port 0 Alternate Select Register 0
#define P0_ALTSEL0             (*((uword volatile *) 0xF0000C44))
#define P0_ALTSEL0_P0            ((T_Reg32 *) 0xF0000C44)->bit0
#define P0_ALTSEL0_P1            ((T_Reg32 *) 0xF0000C44)->bit1
#define P0_ALTSEL0_P10           ((T_Reg32 *) 0xF0000C44)->bit10
#define P0_ALTSEL0_P11           ((T_Reg32 *) 0xF0000C44)->bit11
#define P0_ALTSEL0_P12           ((T_Reg32 *) 0xF0000C44)->bit12
#define P0_ALTSEL0_P13           ((T_Reg32 *) 0xF0000C44)->bit13
#define P0_ALTSEL0_P14           ((T_Reg32 *) 0xF0000C44)->bit14
#define P0_ALTSEL0_P15           ((T_Reg32 *) 0xF0000C44)->bit15
#define P0_ALTSEL0_P2            ((T_Reg32 *) 0xF0000C44)->bit2
#define P0_ALTSEL0_P3            ((T_Reg32 *) 0xF0000C44)->bit3
#define P0_ALTSEL0_P4            ((T_Reg32 *) 0xF0000C44)->bit4
#define P0_ALTSEL0_P5            ((T_Reg32 *) 0xF0000C44)->bit5
#define P0_ALTSEL0_P6            ((T_Reg32 *) 0xF0000C44)->bit6
#define P0_ALTSEL0_P7            ((T_Reg32 *) 0xF0000C44)->bit7
#define P0_ALTSEL0_P8            ((T_Reg32 *) 0xF0000C44)->bit8
#define P0_ALTSEL0_P9            ((T_Reg32 *) 0xF0000C44)->bit9

// Port 0 Alternate Select Register 1
#define P0_ALTSEL1             (*((uword volatile *) 0xF0000C48))
#define P0_ALTSEL1_P0            ((T_Reg32 *) 0xF0000C48)->bit0
#define P0_ALTSEL1_P1            ((T_Reg32 *) 0xF0000C48)->bit1
#define P0_ALTSEL1_P10           ((T_Reg32 *) 0xF0000C48)->bit10
#define P0_ALTSEL1_P11           ((T_Reg32 *) 0xF0000C48)->bit11
#define P0_ALTSEL1_P12           ((T_Reg32 *) 0xF0000C48)->bit12
#define P0_ALTSEL1_P13           ((T_Reg32 *) 0xF0000C48)->bit13
#define P0_ALTSEL1_P14           ((T_Reg32 *) 0xF0000C48)->bit14
#define P0_ALTSEL1_P15           ((T_Reg32 *) 0xF0000C48)->bit15
#define P0_ALTSEL1_P2            ((T_Reg32 *) 0xF0000C48)->bit2
#define P0_ALTSEL1_P3            ((T_Reg32 *) 0xF0000C48)->bit3
#define P0_ALTSEL1_P4            ((T_Reg32 *) 0xF0000C48)->bit4
#define P0_ALTSEL1_P5            ((T_Reg32 *) 0xF0000C48)->bit5
#define P0_ALTSEL1_P6            ((T_Reg32 *) 0xF0000C48)->bit6
#define P0_ALTSEL1_P7            ((T_Reg32 *) 0xF0000C48)->bit7
#define P0_ALTSEL1_P8            ((T_Reg32 *) 0xF0000C48)->bit8
#define P0_ALTSEL1_P9            ((T_Reg32 *) 0xF0000C48)->bit9

// Port 0 Direction Register
#define P0_DIR                 (*((uword volatile *) 0xF0000C18))
#define P0_DIR_P0                ((T_Reg32 *) 0xF0000C18)->bit0
#define P0_DIR_P1                ((T_Reg32 *) 0xF0000C18)->bit1
#define P0_DIR_P10               ((T_Reg32 *) 0xF0000C18)->bit10
#define P0_DIR_P11               ((T_Reg32 *) 0xF0000C18)->bit11
#define P0_DIR_P12               ((T_Reg32 *) 0xF0000C18)->bit12
#define P0_DIR_P13               ((T_Reg32 *) 0xF0000C18)->bit13
#define P0_DIR_P14               ((T_Reg32 *) 0xF0000C18)->bit14
#define P0_DIR_P15               ((T_Reg32 *) 0xF0000C18)->bit15
#define P0_DIR_P2                ((T_Reg32 *) 0xF0000C18)->bit2
#define P0_DIR_P3                ((T_Reg32 *) 0xF0000C18)->bit3
#define P0_DIR_P4                ((T_Reg32 *) 0xF0000C18)->bit4
#define P0_DIR_P5                ((T_Reg32 *) 0xF0000C18)->bit5
#define P0_DIR_P6                ((T_Reg32 *) 0xF0000C18)->bit6
#define P0_DIR_P7                ((T_Reg32 *) 0xF0000C18)->bit7
#define P0_DIR_P8                ((T_Reg32 *) 0xF0000C18)->bit8
#define P0_DIR_P9                ((T_Reg32 *) 0xF0000C18)->bit9

// Port 0 Data Input Register
#define P0_IN                  (*((uword volatile *) 0xF0000C14))
#define P0_IN_P0                 ((T_Reg32 *) 0xF0000C14)->bit0
#define P0_IN_P1                 ((T_Reg32 *) 0xF0000C14)->bit1
#define P0_IN_P10                ((T_Reg32 *) 0xF0000C14)->bit10
#define P0_IN_P11                ((T_Reg32 *) 0xF0000C14)->bit11
#define P0_IN_P12                ((T_Reg32 *) 0xF0000C14)->bit12
#define P0_IN_P13                ((T_Reg32 *) 0xF0000C14)->bit13
#define P0_IN_P14                ((T_Reg32 *) 0xF0000C14)->bit14
#define P0_IN_P15                ((T_Reg32 *) 0xF0000C14)->bit15
#define P0_IN_P2                 ((T_Reg32 *) 0xF0000C14)->bit2
#define P0_IN_P3                 ((T_Reg32 *) 0xF0000C14)->bit3
#define P0_IN_P4                 ((T_Reg32 *) 0xF0000C14)->bit4
#define P0_IN_P5                 ((T_Reg32 *) 0xF0000C14)->bit5
#define P0_IN_P6                 ((T_Reg32 *) 0xF0000C14)->bit6
#define P0_IN_P7                 ((T_Reg32 *) 0xF0000C14)->bit7
#define P0_IN_P8                 ((T_Reg32 *) 0xF0000C14)->bit8
#define P0_IN_P9                 ((T_Reg32 *) 0xF0000C14)->bit9

// Port 0 Open Drain Mode Register
#define P0_OD                  (*((uword volatile *) 0xF0000C1C))
#define P0_OD_P0                 ((T_Reg32 *) 0xF0000C1C)->bit0
#define P0_OD_P1                 ((T_Reg32 *) 0xF0000C1C)->bit1
#define P0_OD_P10                ((T_Reg32 *) 0xF0000C1C)->bit10
#define P0_OD_P11                ((T_Reg32 *) 0xF0000C1C)->bit11
#define P0_OD_P12                ((T_Reg32 *) 0xF0000C1C)->bit12
#define P0_OD_P13                ((T_Reg32 *) 0xF0000C1C)->bit13
#define P0_OD_P14                ((T_Reg32 *) 0xF0000C1C)->bit14
#define P0_OD_P15                ((T_Reg32 *) 0xF0000C1C)->bit15
#define P0_OD_P2                 ((T_Reg32 *) 0xF0000C1C)->bit2
#define P0_OD_P3                 ((T_Reg32 *) 0xF0000C1C)->bit3
#define P0_OD_P4                 ((T_Reg32 *) 0xF0000C1C)->bit4
#define P0_OD_P5                 ((T_Reg32 *) 0xF0000C1C)->bit5
#define P0_OD_P6                 ((T_Reg32 *) 0xF0000C1C)->bit6
#define P0_OD_P7                 ((T_Reg32 *) 0xF0000C1C)->bit7
#define P0_OD_P8                 ((T_Reg32 *) 0xF0000C1C)->bit8
#define P0_OD_P9                 ((T_Reg32 *) 0xF0000C1C)->bit9

// Port 0 Data Output Register
#define P0_OUT                 (*((uword volatile *) 0xF0000C10))
#define P0_OUT_P0                ((T_Reg32 *) 0xF0000C10)->bit0
#define P0_OUT_P1                ((T_Reg32 *) 0xF0000C10)->bit1
#define P0_OUT_P10               ((T_Reg32 *) 0xF0000C10)->bit10
#define P0_OUT_P11               ((T_Reg32 *) 0xF0000C10)->bit11
#define P0_OUT_P12               ((T_Reg32 *) 0xF0000C10)->bit12
#define P0_OUT_P13               ((T_Reg32 *) 0xF0000C10)->bit13
#define P0_OUT_P14               ((T_Reg32 *) 0xF0000C10)->bit14
#define P0_OUT_P15               ((T_Reg32 *) 0xF0000C10)->bit15
#define P0_OUT_P2                ((T_Reg32 *) 0xF0000C10)->bit2
#define P0_OUT_P3                ((T_Reg32 *) 0xF0000C10)->bit3
#define P0_OUT_P4                ((T_Reg32 *) 0xF0000C10)->bit4
#define P0_OUT_P5                ((T_Reg32 *) 0xF0000C10)->bit5
#define P0_OUT_P6                ((T_Reg32 *) 0xF0000C10)->bit6
#define P0_OUT_P7                ((T_Reg32 *) 0xF0000C10)->bit7
#define P0_OUT_P8                ((T_Reg32 *) 0xF0000C10)->bit8
#define P0_OUT_P9                ((T_Reg32 *) 0xF0000C10)->bit9

// Port 0 Pull up/down Enable Register
#define P0_PUDEN               (*((uword volatile *) 0xF0000C2C))
#define P0_PUDEN_P0              ((T_Reg32 *) 0xF0000C2C)->bit0
#define P0_PUDEN_P1              ((T_Reg32 *) 0xF0000C2C)->bit1
#define P0_PUDEN_P10             ((T_Reg32 *) 0xF0000C2C)->bit10
#define P0_PUDEN_P11             ((T_Reg32 *) 0xF0000C2C)->bit11
#define P0_PUDEN_P12             ((T_Reg32 *) 0xF0000C2C)->bit12
#define P0_PUDEN_P13             ((T_Reg32 *) 0xF0000C2C)->bit13
#define P0_PUDEN_P14             ((T_Reg32 *) 0xF0000C2C)->bit14
#define P0_PUDEN_P15             ((T_Reg32 *) 0xF0000C2C)->bit15
#define P0_PUDEN_P2              ((T_Reg32 *) 0xF0000C2C)->bit2
#define P0_PUDEN_P3              ((T_Reg32 *) 0xF0000C2C)->bit3
#define P0_PUDEN_P4              ((T_Reg32 *) 0xF0000C2C)->bit4
#define P0_PUDEN_P5              ((T_Reg32 *) 0xF0000C2C)->bit5
#define P0_PUDEN_P6              ((T_Reg32 *) 0xF0000C2C)->bit6
#define P0_PUDEN_P7              ((T_Reg32 *) 0xF0000C2C)->bit7
#define P0_PUDEN_P8              ((T_Reg32 *) 0xF0000C2C)->bit8
#define P0_PUDEN_P9              ((T_Reg32 *) 0xF0000C2C)->bit9

// Port 0 Pull up/down Select Register
#define P0_PUDSEL              (*((uword volatile *) 0xF0000C28))
#define P0_PUDSEL_P0             ((T_Reg32 *) 0xF0000C28)->bit0
#define P0_PUDSEL_P1             ((T_Reg32 *) 0xF0000C28)->bit1
#define P0_PUDSEL_P10            ((T_Reg32 *) 0xF0000C28)->bit10
#define P0_PUDSEL_P11            ((T_Reg32 *) 0xF0000C28)->bit11
#define P0_PUDSEL_P12            ((T_Reg32 *) 0xF0000C28)->bit12
#define P0_PUDSEL_P13            ((T_Reg32 *) 0xF0000C28)->bit13
#define P0_PUDSEL_P14            ((T_Reg32 *) 0xF0000C28)->bit14
#define P0_PUDSEL_P15            ((T_Reg32 *) 0xF0000C28)->bit15
#define P0_PUDSEL_P2             ((T_Reg32 *) 0xF0000C28)->bit2
#define P0_PUDSEL_P3             ((T_Reg32 *) 0xF0000C28)->bit3
#define P0_PUDSEL_P4             ((T_Reg32 *) 0xF0000C28)->bit4
#define P0_PUDSEL_P5             ((T_Reg32 *) 0xF0000C28)->bit5
#define P0_PUDSEL_P6             ((T_Reg32 *) 0xF0000C28)->bit6
#define P0_PUDSEL_P7             ((T_Reg32 *) 0xF0000C28)->bit7
#define P0_PUDSEL_P8             ((T_Reg32 *) 0xF0000C28)->bit8
#define P0_PUDSEL_P9             ((T_Reg32 *) 0xF0000C28)->bit9

// Port 1 Alternate Select Register 0
#define P1_ALTSEL0             (*((uword volatile *) 0xF0000D44))
#define P1_ALTSEL0_P0            ((T_Reg32 *) 0xF0000D44)->bit0
#define P1_ALTSEL0_P1            ((T_Reg32 *) 0xF0000D44)->bit1
#define P1_ALTSEL0_P10           ((T_Reg32 *) 0xF0000D44)->bit10
#define P1_ALTSEL0_P11           ((T_Reg32 *) 0xF0000D44)->bit11
#define P1_ALTSEL0_P12           ((T_Reg32 *) 0xF0000D44)->bit12
#define P1_ALTSEL0_P13           ((T_Reg32 *) 0xF0000D44)->bit13
#define P1_ALTSEL0_P14           ((T_Reg32 *) 0xF0000D44)->bit14
#define P1_ALTSEL0_P15           ((T_Reg32 *) 0xF0000D44)->bit15
#define P1_ALTSEL0_P2            ((T_Reg32 *) 0xF0000D44)->bit2
#define P1_ALTSEL0_P3            ((T_Reg32 *) 0xF0000D44)->bit3
#define P1_ALTSEL0_P4            ((T_Reg32 *) 0xF0000D44)->bit4
#define P1_ALTSEL0_P5            ((T_Reg32 *) 0xF0000D44)->bit5
#define P1_ALTSEL0_P6            ((T_Reg32 *) 0xF0000D44)->bit6
#define P1_ALTSEL0_P7            ((T_Reg32 *) 0xF0000D44)->bit7
#define P1_ALTSEL0_P8            ((T_Reg32 *) 0xF0000D44)->bit8
#define P1_ALTSEL0_P9            ((T_Reg32 *) 0xF0000D44)->bit9

// Port 1 Alternate Select Register 1
#define P1_ALTSEL1             (*((uword volatile *) 0xF0000D48))
#define P1_ALTSEL1_P0            ((T_Reg32 *) 0xF0000D48)->bit0
#define P1_ALTSEL1_P1            ((T_Reg32 *) 0xF0000D48)->bit1
#define P1_ALTSEL1_P10           ((T_Reg32 *) 0xF0000D48)->bit10
#define P1_ALTSEL1_P11           ((T_Reg32 *) 0xF0000D48)->bit11
#define P1_ALTSEL1_P12           ((T_Reg32 *) 0xF0000D48)->bit12
#define P1_ALTSEL1_P13           ((T_Reg32 *) 0xF0000D48)->bit13
#define P1_ALTSEL1_P14           ((T_Reg32 *) 0xF0000D48)->bit14
#define P1_ALTSEL1_P15           ((T_Reg32 *) 0xF0000D48)->bit15
#define P1_ALTSEL1_P2            ((T_Reg32 *) 0xF0000D48)->bit2
#define P1_ALTSEL1_P3            ((T_Reg32 *) 0xF0000D48)->bit3
#define P1_ALTSEL1_P4            ((T_Reg32 *) 0xF0000D48)->bit4
#define P1_ALTSEL1_P5            ((T_Reg32 *) 0xF0000D48)->bit5
#define P1_ALTSEL1_P6            ((T_Reg32 *) 0xF0000D48)->bit6
#define P1_ALTSEL1_P7            ((T_Reg32 *) 0xF0000D48)->bit7
#define P1_ALTSEL1_P8            ((T_Reg32 *) 0xF0000D48)->bit8
#define P1_ALTSEL1_P9            ((T_Reg32 *) 0xF0000D48)->bit9

// Port 1 Direction Register
#define P1_DIR                 (*((uword volatile *) 0xF0000D18))
#define P1_DIR_P0                ((T_Reg32 *) 0xF0000D18)->bit0
#define P1_DIR_P1                ((T_Reg32 *) 0xF0000D18)->bit1
#define P1_DIR_P10               ((T_Reg32 *) 0xF0000D18)->bit10
#define P1_DIR_P11               ((T_Reg32 *) 0xF0000D18)->bit11
#define P1_DIR_P12               ((T_Reg32 *) 0xF0000D18)->bit12
#define P1_DIR_P13               ((T_Reg32 *) 0xF0000D18)->bit13
#define P1_DIR_P14               ((T_Reg32 *) 0xF0000D18)->bit14
#define P1_DIR_P15               ((T_Reg32 *) 0xF0000D18)->bit15
#define P1_DIR_P2                ((T_Reg32 *) 0xF0000D18)->bit2
#define P1_DIR_P3                ((T_Reg32 *) 0xF0000D18)->bit3
#define P1_DIR_P4                ((T_Reg32 *) 0xF0000D18)->bit4
#define P1_DIR_P5                ((T_Reg32 *) 0xF0000D18)->bit5
#define P1_DIR_P6                ((T_Reg32 *) 0xF0000D18)->bit6
#define P1_DIR_P7                ((T_Reg32 *) 0xF0000D18)->bit7
#define P1_DIR_P8                ((T_Reg32 *) 0xF0000D18)->bit8
#define P1_DIR_P9                ((T_Reg32 *) 0xF0000D18)->bit9

// Port 1 Data Input Register
#define P1_IN                  (*((uword volatile *) 0xF0000D14))
#define P1_IN_P0                 ((T_Reg32 *) 0xF0000D14)->bit0
#define P1_IN_P1                 ((T_Reg32 *) 0xF0000D14)->bit1
#define P1_IN_P10                ((T_Reg32 *) 0xF0000D14)->bit10
#define P1_IN_P11                ((T_Reg32 *) 0xF0000D14)->bit11
#define P1_IN_P12                ((T_Reg32 *) 0xF0000D14)->bit12
#define P1_IN_P13                ((T_Reg32 *) 0xF0000D14)->bit13
#define P1_IN_P14                ((T_Reg32 *) 0xF0000D14)->bit14
#define P1_IN_P15                ((T_Reg32 *) 0xF0000D14)->bit15
#define P1_IN_P2                 ((T_Reg32 *) 0xF0000D14)->bit2
#define P1_IN_P3                 ((T_Reg32 *) 0xF0000D14)->bit3
#define P1_IN_P4                 ((T_Reg32 *) 0xF0000D14)->bit4
#define P1_IN_P5                 ((T_Reg32 *) 0xF0000D14)->bit5
#define P1_IN_P6                 ((T_Reg32 *) 0xF0000D14)->bit6
#define P1_IN_P7                 ((T_Reg32 *) 0xF0000D14)->bit7
#define P1_IN_P8                 ((T_Reg32 *) 0xF0000D14)->bit8
#define P1_IN_P9                 ((T_Reg32 *) 0xF0000D14)->bit9

// Port 1 Open Drain Mode Register
#define P1_OD                  (*((uword volatile *) 0xF0000D1C))
#define P1_OD_P0                 ((T_Reg32 *) 0xF0000D1C)->bit0
#define P1_OD_P1                 ((T_Reg32 *) 0xF0000D1C)->bit1
#define P1_OD_P10                ((T_Reg32 *) 0xF0000D1C)->bit10
#define P1_OD_P11                ((T_Reg32 *) 0xF0000D1C)->bit11
#define P1_OD_P12                ((T_Reg32 *) 0xF0000D1C)->bit12
#define P1_OD_P13                ((T_Reg32 *) 0xF0000D1C)->bit13
#define P1_OD_P14                ((T_Reg32 *) 0xF0000D1C)->bit14
#define P1_OD_P15                ((T_Reg32 *) 0xF0000D1C)->bit15
#define P1_OD_P2                 ((T_Reg32 *) 0xF0000D1C)->bit2
#define P1_OD_P3                 ((T_Reg32 *) 0xF0000D1C)->bit3
#define P1_OD_P4                 ((T_Reg32 *) 0xF0000D1C)->bit4
#define P1_OD_P5                 ((T_Reg32 *) 0xF0000D1C)->bit5
#define P1_OD_P6                 ((T_Reg32 *) 0xF0000D1C)->bit6
#define P1_OD_P7                 ((T_Reg32 *) 0xF0000D1C)->bit7
#define P1_OD_P8                 ((T_Reg32 *) 0xF0000D1C)->bit8
#define P1_OD_P9                 ((T_Reg32 *) 0xF0000D1C)->bit9

// Port 1 Data Output Register
#define P1_OUT                 (*((uword volatile *) 0xF0000D10))
#define P1_OUT_P0                ((T_Reg32 *) 0xF0000D10)->bit0
#define P1_OUT_P1                ((T_Reg32 *) 0xF0000D10)->bit1
#define P1_OUT_P10               ((T_Reg32 *) 0xF0000D10)->bit10
#define P1_OUT_P11               ((T_Reg32 *) 0xF0000D10)->bit11
#define P1_OUT_P12               ((T_Reg32 *) 0xF0000D10)->bit12
#define P1_OUT_P13               ((T_Reg32 *) 0xF0000D10)->bit13
#define P1_OUT_P14               ((T_Reg32 *) 0xF0000D10)->bit14
#define P1_OUT_P15               ((T_Reg32 *) 0xF0000D10)->bit15
#define P1_OUT_P2                ((T_Reg32 *) 0xF0000D10)->bit2
#define P1_OUT_P3                ((T_Reg32 *) 0xF0000D10)->bit3
#define P1_OUT_P4                ((T_Reg32 *) 0xF0000D10)->bit4
#define P1_OUT_P5                ((T_Reg32 *) 0xF0000D10)->bit5
#define P1_OUT_P6                ((T_Reg32 *) 0xF0000D10)->bit6
#define P1_OUT_P7                ((T_Reg32 *) 0xF0000D10)->bit7
#define P1_OUT_P8                ((T_Reg32 *) 0xF0000D10)->bit8
#define P1_OUT_P9                ((T_Reg32 *) 0xF0000D10)->bit9

// Port 1 Pull up/down Enable Register
#define P1_PUDEN               (*((uword volatile *) 0xF0000D2C))
#define P1_PUDEN_P0              ((T_Reg32 *) 0xF0000D2C)->bit0
#define P1_PUDEN_P1              ((T_Reg32 *) 0xF0000D2C)->bit1
#define P1_PUDEN_P10             ((T_Reg32 *) 0xF0000D2C)->bit10
#define P1_PUDEN_P11             ((T_Reg32 *) 0xF0000D2C)->bit11
#define P1_PUDEN_P12             ((T_Reg32 *) 0xF0000D2C)->bit12
#define P1_PUDEN_P13             ((T_Reg32 *) 0xF0000D2C)->bit13
#define P1_PUDEN_P14             ((T_Reg32 *) 0xF0000D2C)->bit14
#define P1_PUDEN_P15             ((T_Reg32 *) 0xF0000D2C)->bit15
#define P1_PUDEN_P2              ((T_Reg32 *) 0xF0000D2C)->bit2
#define P1_PUDEN_P3              ((T_Reg32 *) 0xF0000D2C)->bit3
#define P1_PUDEN_P4              ((T_Reg32 *) 0xF0000D2C)->bit4
#define P1_PUDEN_P5              ((T_Reg32 *) 0xF0000D2C)->bit5
#define P1_PUDEN_P6              ((T_Reg32 *) 0xF0000D2C)->bit6
#define P1_PUDEN_P7              ((T_Reg32 *) 0xF0000D2C)->bit7
#define P1_PUDEN_P8              ((T_Reg32 *) 0xF0000D2C)->bit8
#define P1_PUDEN_P9              ((T_Reg32 *) 0xF0000D2C)->bit9

// Port 1 Pull up/down Select Register
#define P1_PUDSEL              (*((uword volatile *) 0xF0000D28))
#define P1_PUDSEL_P0             ((T_Reg32 *) 0xF0000D28)->bit0
#define P1_PUDSEL_P1             ((T_Reg32 *) 0xF0000D28)->bit1
#define P1_PUDSEL_P10            ((T_Reg32 *) 0xF0000D28)->bit10
#define P1_PUDSEL_P11            ((T_Reg32 *) 0xF0000D28)->bit11
#define P1_PUDSEL_P12            ((T_Reg32 *) 0xF0000D28)->bit12
#define P1_PUDSEL_P13            ((T_Reg32 *) 0xF0000D28)->bit13
#define P1_PUDSEL_P14            ((T_Reg32 *) 0xF0000D28)->bit14
#define P1_PUDSEL_P15            ((T_Reg32 *) 0xF0000D28)->bit15
#define P1_PUDSEL_P2             ((T_Reg32 *) 0xF0000D28)->bit2
#define P1_PUDSEL_P3             ((T_Reg32 *) 0xF0000D28)->bit3
#define P1_PUDSEL_P4             ((T_Reg32 *) 0xF0000D28)->bit4
#define P1_PUDSEL_P5             ((T_Reg32 *) 0xF0000D28)->bit5
#define P1_PUDSEL_P6             ((T_Reg32 *) 0xF0000D28)->bit6
#define P1_PUDSEL_P7             ((T_Reg32 *) 0xF0000D28)->bit7
#define P1_PUDSEL_P8             ((T_Reg32 *) 0xF0000D28)->bit8
#define P1_PUDSEL_P9             ((T_Reg32 *) 0xF0000D28)->bit9

// Port 2 Alternate Select Register 0
#define P2_ALTSEL0             (*((uword volatile *) 0xF0000E44))
#define P2_ALTSEL0_P0            ((T_Reg32 *) 0xF0000E44)->bit0
#define P2_ALTSEL0_P1            ((T_Reg32 *) 0xF0000E44)->bit1
#define P2_ALTSEL0_P10           ((T_Reg32 *) 0xF0000E44)->bit10
#define P2_ALTSEL0_P11           ((T_Reg32 *) 0xF0000E44)->bit11
#define P2_ALTSEL0_P12           ((T_Reg32 *) 0xF0000E44)->bit12
#define P2_ALTSEL0_P13           ((T_Reg32 *) 0xF0000E44)->bit13
#define P2_ALTSEL0_P14           ((T_Reg32 *) 0xF0000E44)->bit14
#define P2_ALTSEL0_P15           ((T_Reg32 *) 0xF0000E44)->bit15
#define P2_ALTSEL0_P2            ((T_Reg32 *) 0xF0000E44)->bit2
#define P2_ALTSEL0_P3            ((T_Reg32 *) 0xF0000E44)->bit3
#define P2_ALTSEL0_P4            ((T_Reg32 *) 0xF0000E44)->bit4
#define P2_ALTSEL0_P5            ((T_Reg32 *) 0xF0000E44)->bit5
#define P2_ALTSEL0_P6            ((T_Reg32 *) 0xF0000E44)->bit6
#define P2_ALTSEL0_P7            ((T_Reg32 *) 0xF0000E44)->bit7
#define P2_ALTSEL0_P8            ((T_Reg32 *) 0xF0000E44)->bit8
#define P2_ALTSEL0_P9            ((T_Reg32 *) 0xF0000E44)->bit9

// Port 2 Alternate Select Register 1
#define P2_ALTSEL1             (*((uword volatile *) 0xF0000E48))
#define P2_ALTSEL1_P0            ((T_Reg32 *) 0xF0000E48)->bit0
#define P2_ALTSEL1_P1            ((T_Reg32 *) 0xF0000E48)->bit1
#define P2_ALTSEL1_P10           ((T_Reg32 *) 0xF0000E48)->bit10
#define P2_ALTSEL1_P11           ((T_Reg32 *) 0xF0000E48)->bit11
#define P2_ALTSEL1_P12           ((T_Reg32 *) 0xF0000E48)->bit12
#define P2_ALTSEL1_P13           ((T_Reg32 *) 0xF0000E48)->bit13
#define P2_ALTSEL1_P14           ((T_Reg32 *) 0xF0000E48)->bit14
#define P2_ALTSEL1_P15           ((T_Reg32 *) 0xF0000E48)->bit15
#define P2_ALTSEL1_P2            ((T_Reg32 *) 0xF0000E48)->bit2
#define P2_ALTSEL1_P3            ((T_Reg32 *) 0xF0000E48)->bit3
#define P2_ALTSEL1_P4            ((T_Reg32 *) 0xF0000E48)->bit4
#define P2_ALTSEL1_P5            ((T_Reg32 *) 0xF0000E48)->bit5
#define P2_ALTSEL1_P6            ((T_Reg32 *) 0xF0000E48)->bit6
#define P2_ALTSEL1_P7            ((T_Reg32 *) 0xF0000E48)->bit7
#define P2_ALTSEL1_P8            ((T_Reg32 *) 0xF0000E48)->bit8
#define P2_ALTSEL1_P9            ((T_Reg32 *) 0xF0000E48)->bit9

// Port 2 Direction Register
#define P2_DIR                 (*((uword volatile *) 0xF0000E18))
#define P2_DIR_P0                ((T_Reg32 *) 0xF0000E18)->bit0
#define P2_DIR_P1                ((T_Reg32 *) 0xF0000E18)->bit1
#define P2_DIR_P10               ((T_Reg32 *) 0xF0000E18)->bit10
#define P2_DIR_P11               ((T_Reg32 *) 0xF0000E18)->bit11
#define P2_DIR_P12               ((T_Reg32 *) 0xF0000E18)->bit12
#define P2_DIR_P13               ((T_Reg32 *) 0xF0000E18)->bit13
#define P2_DIR_P14               ((T_Reg32 *) 0xF0000E18)->bit14
#define P2_DIR_P15               ((T_Reg32 *) 0xF0000E18)->bit15
#define P2_DIR_P2                ((T_Reg32 *) 0xF0000E18)->bit2
#define P2_DIR_P3                ((T_Reg32 *) 0xF0000E18)->bit3
#define P2_DIR_P4                ((T_Reg32 *) 0xF0000E18)->bit4
#define P2_DIR_P5                ((T_Reg32 *) 0xF0000E18)->bit5
#define P2_DIR_P6                ((T_Reg32 *) 0xF0000E18)->bit6
#define P2_DIR_P7                ((T_Reg32 *) 0xF0000E18)->bit7
#define P2_DIR_P8                ((T_Reg32 *) 0xF0000E18)->bit8
#define P2_DIR_P9                ((T_Reg32 *) 0xF0000E18)->bit9

// Port 2 Data Input Register
#define P2_IN                  (*((uword volatile *) 0xF0000E14))
#define P2_IN_P0                 ((T_Reg32 *) 0xF0000E14)->bit0
#define P2_IN_P1                 ((T_Reg32 *) 0xF0000E14)->bit1
#define P2_IN_P10                ((T_Reg32 *) 0xF0000E14)->bit10
#define P2_IN_P11                ((T_Reg32 *) 0xF0000E14)->bit11
#define P2_IN_P12                ((T_Reg32 *) 0xF0000E14)->bit12
#define P2_IN_P13                ((T_Reg32 *) 0xF0000E14)->bit13
#define P2_IN_P14                ((T_Reg32 *) 0xF0000E14)->bit14
#define P2_IN_P15                ((T_Reg32 *) 0xF0000E14)->bit15
#define P2_IN_P2                 ((T_Reg32 *) 0xF0000E14)->bit2
#define P2_IN_P3                 ((T_Reg32 *) 0xF0000E14)->bit3
#define P2_IN_P4                 ((T_Reg32 *) 0xF0000E14)->bit4
#define P2_IN_P5                 ((T_Reg32 *) 0xF0000E14)->bit5
#define P2_IN_P6                 ((T_Reg32 *) 0xF0000E14)->bit6
#define P2_IN_P7                 ((T_Reg32 *) 0xF0000E14)->bit7
#define P2_IN_P8                 ((T_Reg32 *) 0xF0000E14)->bit8
#define P2_IN_P9                 ((T_Reg32 *) 0xF0000E14)->bit9

// Port 2 Open Drain Mode Register
#define P2_OD                  (*((uword volatile *) 0xF0000E1C))
#define P2_OD_P0                 ((T_Reg32 *) 0xF0000E1C)->bit0
#define P2_OD_P1                 ((T_Reg32 *) 0xF0000E1C)->bit1
#define P2_OD_P10                ((T_Reg32 *) 0xF0000E1C)->bit10
#define P2_OD_P11                ((T_Reg32 *) 0xF0000E1C)->bit11
#define P2_OD_P12                ((T_Reg32 *) 0xF0000E1C)->bit12
#define P2_OD_P13                ((T_Reg32 *) 0xF0000E1C)->bit13
#define P2_OD_P14                ((T_Reg32 *) 0xF0000E1C)->bit14
#define P2_OD_P15                ((T_Reg32 *) 0xF0000E1C)->bit15
#define P2_OD_P2                 ((T_Reg32 *) 0xF0000E1C)->bit2
#define P2_OD_P3                 ((T_Reg32 *) 0xF0000E1C)->bit3
#define P2_OD_P4                 ((T_Reg32 *) 0xF0000E1C)->bit4
#define P2_OD_P5                 ((T_Reg32 *) 0xF0000E1C)->bit5
#define P2_OD_P6                 ((T_Reg32 *) 0xF0000E1C)->bit6
#define P2_OD_P7                 ((T_Reg32 *) 0xF0000E1C)->bit7
#define P2_OD_P8                 ((T_Reg32 *) 0xF0000E1C)->bit8
#define P2_OD_P9                 ((T_Reg32 *) 0xF0000E1C)->bit9

// Port 2 Data Output Register
#define P2_OUT                 (*((uword volatile *) 0xF0000E10))
#define P2_OUT_P0                ((T_Reg32 *) 0xF0000E10)->bit0
#define P2_OUT_P1                ((T_Reg32 *) 0xF0000E10)->bit1
#define P2_OUT_P10               ((T_Reg32 *) 0xF0000E10)->bit10
#define P2_OUT_P11               ((T_Reg32 *) 0xF0000E10)->bit11
#define P2_OUT_P12               ((T_Reg32 *) 0xF0000E10)->bit12
#define P2_OUT_P13               ((T_Reg32 *) 0xF0000E10)->bit13
#define P2_OUT_P14               ((T_Reg32 *) 0xF0000E10)->bit14
#define P2_OUT_P15               ((T_Reg32 *) 0xF0000E10)->bit15
#define P2_OUT_P2                ((T_Reg32 *) 0xF0000E10)->bit2
#define P2_OUT_P3                ((T_Reg32 *) 0xF0000E10)->bit3
#define P2_OUT_P4                ((T_Reg32 *) 0xF0000E10)->bit4
#define P2_OUT_P5                ((T_Reg32 *) 0xF0000E10)->bit5
#define P2_OUT_P6                ((T_Reg32 *) 0xF0000E10)->bit6
#define P2_OUT_P7                ((T_Reg32 *) 0xF0000E10)->bit7
#define P2_OUT_P8                ((T_Reg32 *) 0xF0000E10)->bit8
#define P2_OUT_P9                ((T_Reg32 *) 0xF0000E10)->bit9

// Port 2 Pull up/down Enable Register
#define P2_PUDEN               (*((uword volatile *) 0xF0000E2C))
#define P2_PUDEN_P0              ((T_Reg32 *) 0xF0000E2C)->bit0
#define P2_PUDEN_P1              ((T_Reg32 *) 0xF0000E2C)->bit1
#define P2_PUDEN_P10             ((T_Reg32 *) 0xF0000E2C)->bit10
#define P2_PUDEN_P11             ((T_Reg32 *) 0xF0000E2C)->bit11
#define P2_PUDEN_P12             ((T_Reg32 *) 0xF0000E2C)->bit12
#define P2_PUDEN_P13             ((T_Reg32 *) 0xF0000E2C)->bit13
#define P2_PUDEN_P14             ((T_Reg32 *) 0xF0000E2C)->bit14
#define P2_PUDEN_P15             ((T_Reg32 *) 0xF0000E2C)->bit15
#define P2_PUDEN_P2              ((T_Reg32 *) 0xF0000E2C)->bit2
#define P2_PUDEN_P3              ((T_Reg32 *) 0xF0000E2C)->bit3
#define P2_PUDEN_P4              ((T_Reg32 *) 0xF0000E2C)->bit4
#define P2_PUDEN_P5              ((T_Reg32 *) 0xF0000E2C)->bit5
#define P2_PUDEN_P6              ((T_Reg32 *) 0xF0000E2C)->bit6
#define P2_PUDEN_P7              ((T_Reg32 *) 0xF0000E2C)->bit7
#define P2_PUDEN_P8              ((T_Reg32 *) 0xF0000E2C)->bit8
#define P2_PUDEN_P9              ((T_Reg32 *) 0xF0000E2C)->bit9

// Port 2 Pull up/down Select Register
#define P2_PUDSEL              (*((uword volatile *) 0xF0000E28))
#define P2_PUDSEL_P0             ((T_Reg32 *) 0xF0000E28)->bit0
#define P2_PUDSEL_P1             ((T_Reg32 *) 0xF0000E28)->bit1
#define P2_PUDSEL_P10            ((T_Reg32 *) 0xF0000E28)->bit10
#define P2_PUDSEL_P11            ((T_Reg32 *) 0xF0000E28)->bit11
#define P2_PUDSEL_P12            ((T_Reg32 *) 0xF0000E28)->bit12
#define P2_PUDSEL_P13            ((T_Reg32 *) 0xF0000E28)->bit13
#define P2_PUDSEL_P14            ((T_Reg32 *) 0xF0000E28)->bit14
#define P2_PUDSEL_P15            ((T_Reg32 *) 0xF0000E28)->bit15
#define P2_PUDSEL_P2             ((T_Reg32 *) 0xF0000E28)->bit2
#define P2_PUDSEL_P3             ((T_Reg32 *) 0xF0000E28)->bit3
#define P2_PUDSEL_P4             ((T_Reg32 *) 0xF0000E28)->bit4
#define P2_PUDSEL_P5             ((T_Reg32 *) 0xF0000E28)->bit5
#define P2_PUDSEL_P6             ((T_Reg32 *) 0xF0000E28)->bit6
#define P2_PUDSEL_P7             ((T_Reg32 *) 0xF0000E28)->bit7
#define P2_PUDSEL_P8             ((T_Reg32 *) 0xF0000E28)->bit8
#define P2_PUDSEL_P9             ((T_Reg32 *) 0xF0000E28)->bit9

// Port 3 Alternate Select Register 0
#define P3_ALTSEL0             (*((uword volatile *) 0xF0000F44))
#define P3_ALTSEL0_P0            ((T_Reg32 *) 0xF0000F44)->bit0
#define P3_ALTSEL0_P1            ((T_Reg32 *) 0xF0000F44)->bit1
#define P3_ALTSEL0_P10           ((T_Reg32 *) 0xF0000F44)->bit10
#define P3_ALTSEL0_P11           ((T_Reg32 *) 0xF0000F44)->bit11
#define P3_ALTSEL0_P12           ((T_Reg32 *) 0xF0000F44)->bit12
#define P3_ALTSEL0_P13           ((T_Reg32 *) 0xF0000F44)->bit13
#define P3_ALTSEL0_P14           ((T_Reg32 *) 0xF0000F44)->bit14
#define P3_ALTSEL0_P15           ((T_Reg32 *) 0xF0000F44)->bit15
#define P3_ALTSEL0_P2            ((T_Reg32 *) 0xF0000F44)->bit2
#define P3_ALTSEL0_P3            ((T_Reg32 *) 0xF0000F44)->bit3
#define P3_ALTSEL0_P4            ((T_Reg32 *) 0xF0000F44)->bit4
#define P3_ALTSEL0_P5            ((T_Reg32 *) 0xF0000F44)->bit5
#define P3_ALTSEL0_P6            ((T_Reg32 *) 0xF0000F44)->bit6
#define P3_ALTSEL0_P7            ((T_Reg32 *) 0xF0000F44)->bit7
#define P3_ALTSEL0_P8            ((T_Reg32 *) 0xF0000F44)->bit8
#define P3_ALTSEL0_P9            ((T_Reg32 *) 0xF0000F44)->bit9

// Port 3 Alternate Select Register 1
#define P3_ALTSEL1             (*((uword volatile *) 0xF0000F48))
#define P3_ALTSEL1_P0            ((T_Reg32 *) 0xF0000F48)->bit0
#define P3_ALTSEL1_P1            ((T_Reg32 *) 0xF0000F48)->bit1
#define P3_ALTSEL1_P10           ((T_Reg32 *) 0xF0000F48)->bit10
#define P3_ALTSEL1_P11           ((T_Reg32 *) 0xF0000F48)->bit11
#define P3_ALTSEL1_P12           ((T_Reg32 *) 0xF0000F48)->bit12
#define P3_ALTSEL1_P13           ((T_Reg32 *) 0xF0000F48)->bit13
#define P3_ALTSEL1_P14           ((T_Reg32 *) 0xF0000F48)->bit14
#define P3_ALTSEL1_P15           ((T_Reg32 *) 0xF0000F48)->bit15
#define P3_ALTSEL1_P2            ((T_Reg32 *) 0xF0000F48)->bit2
#define P3_ALTSEL1_P3            ((T_Reg32 *) 0xF0000F48)->bit3
#define P3_ALTSEL1_P4            ((T_Reg32 *) 0xF0000F48)->bit4
#define P3_ALTSEL1_P5            ((T_Reg32 *) 0xF0000F48)->bit5
#define P3_ALTSEL1_P6            ((T_Reg32 *) 0xF0000F48)->bit6
#define P3_ALTSEL1_P7            ((T_Reg32 *) 0xF0000F48)->bit7
#define P3_ALTSEL1_P8            ((T_Reg32 *) 0xF0000F48)->bit8
#define P3_ALTSEL1_P9            ((T_Reg32 *) 0xF0000F48)->bit9

// Port 3 Direction Register
#define P3_DIR                 (*((uword volatile *) 0xF0000F18))
#define P3_DIR_P0                ((T_Reg32 *) 0xF0000F18)->bit0
#define P3_DIR_P1                ((T_Reg32 *) 0xF0000F18)->bit1
#define P3_DIR_P10               ((T_Reg32 *) 0xF0000F18)->bit10
#define P3_DIR_P11               ((T_Reg32 *) 0xF0000F18)->bit11
#define P3_DIR_P12               ((T_Reg32 *) 0xF0000F18)->bit12
#define P3_DIR_P13               ((T_Reg32 *) 0xF0000F18)->bit13
#define P3_DIR_P14               ((T_Reg32 *) 0xF0000F18)->bit14
#define P3_DIR_P15               ((T_Reg32 *) 0xF0000F18)->bit15
#define P3_DIR_P2                ((T_Reg32 *) 0xF0000F18)->bit2
#define P3_DIR_P3                ((T_Reg32 *) 0xF0000F18)->bit3
#define P3_DIR_P4                ((T_Reg32 *) 0xF0000F18)->bit4
#define P3_DIR_P5                ((T_Reg32 *) 0xF0000F18)->bit5
#define P3_DIR_P6                ((T_Reg32 *) 0xF0000F18)->bit6
#define P3_DIR_P7                ((T_Reg32 *) 0xF0000F18)->bit7
#define P3_DIR_P8                ((T_Reg32 *) 0xF0000F18)->bit8
#define P3_DIR_P9                ((T_Reg32 *) 0xF0000F18)->bit9

// Port 3 Data Input Register
#define P3_IN                  (*((uword volatile *) 0xF0000F14))
#define P3_IN_P0                 ((T_Reg32 *) 0xF0000F14)->bit0
#define P3_IN_P1                 ((T_Reg32 *) 0xF0000F14)->bit1
#define P3_IN_P10                ((T_Reg32 *) 0xF0000F14)->bit10
#define P3_IN_P11                ((T_Reg32 *) 0xF0000F14)->bit11
#define P3_IN_P12                ((T_Reg32 *) 0xF0000F14)->bit12
#define P3_IN_P13                ((T_Reg32 *) 0xF0000F14)->bit13
#define P3_IN_P14                ((T_Reg32 *) 0xF0000F14)->bit14
#define P3_IN_P15                ((T_Reg32 *) 0xF0000F14)->bit15
#define P3_IN_P2                 ((T_Reg32 *) 0xF0000F14)->bit2
#define P3_IN_P3                 ((T_Reg32 *) 0xF0000F14)->bit3
#define P3_IN_P4                 ((T_Reg32 *) 0xF0000F14)->bit4
#define P3_IN_P5                 ((T_Reg32 *) 0xF0000F14)->bit5
#define P3_IN_P6                 ((T_Reg32 *) 0xF0000F14)->bit6
#define P3_IN_P7                 ((T_Reg32 *) 0xF0000F14)->bit7
#define P3_IN_P8                 ((T_Reg32 *) 0xF0000F14)->bit8
#define P3_IN_P9                 ((T_Reg32 *) 0xF0000F14)->bit9

// Port 3 Open Drain Mode Register
#define P3_OD                  (*((uword volatile *) 0xF0000F1C))
#define P3_OD_P0                 ((T_Reg32 *) 0xF0000F1C)->bit0
#define P3_OD_P1                 ((T_Reg32 *) 0xF0000F1C)->bit1
#define P3_OD_P10                ((T_Reg32 *) 0xF0000F1C)->bit10
#define P3_OD_P11                ((T_Reg32 *) 0xF0000F1C)->bit11
#define P3_OD_P12                ((T_Reg32 *) 0xF0000F1C)->bit12
#define P3_OD_P13                ((T_Reg32 *) 0xF0000F1C)->bit13
#define P3_OD_P14                ((T_Reg32 *) 0xF0000F1C)->bit14
#define P3_OD_P15                ((T_Reg32 *) 0xF0000F1C)->bit15
#define P3_OD_P2                 ((T_Reg32 *) 0xF0000F1C)->bit2
#define P3_OD_P3                 ((T_Reg32 *) 0xF0000F1C)->bit3
#define P3_OD_P4                 ((T_Reg32 *) 0xF0000F1C)->bit4
#define P3_OD_P5                 ((T_Reg32 *) 0xF0000F1C)->bit5
#define P3_OD_P6                 ((T_Reg32 *) 0xF0000F1C)->bit6
#define P3_OD_P7                 ((T_Reg32 *) 0xF0000F1C)->bit7
#define P3_OD_P8                 ((T_Reg32 *) 0xF0000F1C)->bit8
#define P3_OD_P9                 ((T_Reg32 *) 0xF0000F1C)->bit9

// Port 3 Data Output Register
#define P3_OUT                 (*((uword volatile *) 0xF0000F10))
#define P3_OUT_P0                ((T_Reg32 *) 0xF0000F10)->bit0
#define P3_OUT_P1                ((T_Reg32 *) 0xF0000F10)->bit1
#define P3_OUT_P10               ((T_Reg32 *) 0xF0000F10)->bit10
#define P3_OUT_P11               ((T_Reg32 *) 0xF0000F10)->bit11
#define P3_OUT_P12               ((T_Reg32 *) 0xF0000F10)->bit12
#define P3_OUT_P13               ((T_Reg32 *) 0xF0000F10)->bit13
#define P3_OUT_P14               ((T_Reg32 *) 0xF0000F10)->bit14
#define P3_OUT_P15               ((T_Reg32 *) 0xF0000F10)->bit15
#define P3_OUT_P2                ((T_Reg32 *) 0xF0000F10)->bit2
#define P3_OUT_P3                ((T_Reg32 *) 0xF0000F10)->bit3
#define P3_OUT_P4                ((T_Reg32 *) 0xF0000F10)->bit4
#define P3_OUT_P5                ((T_Reg32 *) 0xF0000F10)->bit5
#define P3_OUT_P6                ((T_Reg32 *) 0xF0000F10)->bit6
#define P3_OUT_P7                ((T_Reg32 *) 0xF0000F10)->bit7
#define P3_OUT_P8                ((T_Reg32 *) 0xF0000F10)->bit8
#define P3_OUT_P9                ((T_Reg32 *) 0xF0000F10)->bit9

// Port 3 Pull up/down Enable Register
#define P3_PUDEN               (*((uword volatile *) 0xF0000F2C))
#define P3_PUDEN_P0              ((T_Reg32 *) 0xF0000F2C)->bit0
#define P3_PUDEN_P1              ((T_Reg32 *) 0xF0000F2C)->bit1
#define P3_PUDEN_P10             ((T_Reg32 *) 0xF0000F2C)->bit10
#define P3_PUDEN_P11             ((T_Reg32 *) 0xF0000F2C)->bit11
#define P3_PUDEN_P12             ((T_Reg32 *) 0xF0000F2C)->bit12
#define P3_PUDEN_P13             ((T_Reg32 *) 0xF0000F2C)->bit13
#define P3_PUDEN_P14             ((T_Reg32 *) 0xF0000F2C)->bit14
#define P3_PUDEN_P15             ((T_Reg32 *) 0xF0000F2C)->bit15
#define P3_PUDEN_P2              ((T_Reg32 *) 0xF0000F2C)->bit2
#define P3_PUDEN_P3              ((T_Reg32 *) 0xF0000F2C)->bit3
#define P3_PUDEN_P4              ((T_Reg32 *) 0xF0000F2C)->bit4
#define P3_PUDEN_P5              ((T_Reg32 *) 0xF0000F2C)->bit5
#define P3_PUDEN_P6              ((T_Reg32 *) 0xF0000F2C)->bit6
#define P3_PUDEN_P7              ((T_Reg32 *) 0xF0000F2C)->bit7
#define P3_PUDEN_P8              ((T_Reg32 *) 0xF0000F2C)->bit8
#define P3_PUDEN_P9              ((T_Reg32 *) 0xF0000F2C)->bit9

// Port 3 Pull up/down Select Register
#define P3_PUDSEL              (*((uword volatile *) 0xF0000F28))
#define P3_PUDSEL_P0             ((T_Reg32 *) 0xF0000F28)->bit0
#define P3_PUDSEL_P1             ((T_Reg32 *) 0xF0000F28)->bit1
#define P3_PUDSEL_P10            ((T_Reg32 *) 0xF0000F28)->bit10
#define P3_PUDSEL_P11            ((T_Reg32 *) 0xF0000F28)->bit11
#define P3_PUDSEL_P12            ((T_Reg32 *) 0xF0000F28)->bit12
#define P3_PUDSEL_P13            ((T_Reg32 *) 0xF0000F28)->bit13
#define P3_PUDSEL_P14            ((T_Reg32 *) 0xF0000F28)->bit14
#define P3_PUDSEL_P15            ((T_Reg32 *) 0xF0000F28)->bit15
#define P3_PUDSEL_P2             ((T_Reg32 *) 0xF0000F28)->bit2
#define P3_PUDSEL_P3             ((T_Reg32 *) 0xF0000F28)->bit3
#define P3_PUDSEL_P4             ((T_Reg32 *) 0xF0000F28)->bit4
#define P3_PUDSEL_P5             ((T_Reg32 *) 0xF0000F28)->bit5
#define P3_PUDSEL_P6             ((T_Reg32 *) 0xF0000F28)->bit6
#define P3_PUDSEL_P7             ((T_Reg32 *) 0xF0000F28)->bit7
#define P3_PUDSEL_P8             ((T_Reg32 *) 0xF0000F28)->bit8
#define P3_PUDSEL_P9             ((T_Reg32 *) 0xF0000F28)->bit9

// Port 4 Alternate Select Register 0
#define P4_ALTSEL0             (*((uword volatile *) 0xF0001044))
#define P4_ALTSEL0_P0            ((T_Reg32 *) 0xF0001044)->bit0
#define P4_ALTSEL0_P1            ((T_Reg32 *) 0xF0001044)->bit1
#define P4_ALTSEL0_P2            ((T_Reg32 *) 0xF0001044)->bit2
#define P4_ALTSEL0_P3            ((T_Reg32 *) 0xF0001044)->bit3
#define P4_ALTSEL0_P4            ((T_Reg32 *) 0xF0001044)->bit4
#define P4_ALTSEL0_P5            ((T_Reg32 *) 0xF0001044)->bit5
#define P4_ALTSEL0_P6            ((T_Reg32 *) 0xF0001044)->bit6
#define P4_ALTSEL0_P7            ((T_Reg32 *) 0xF0001044)->bit7

// Port 4 Alternate Select Register 1
#define P4_ALTSEL1             (*((uword volatile *) 0xF0001048))
#define P4_ALTSEL1_P0            ((T_Reg32 *) 0xF0001048)->bit0
#define P4_ALTSEL1_P1            ((T_Reg32 *) 0xF0001048)->bit1
#define P4_ALTSEL1_P2            ((T_Reg32 *) 0xF0001048)->bit2
#define P4_ALTSEL1_P3            ((T_Reg32 *) 0xF0001048)->bit3
#define P4_ALTSEL1_P4            ((T_Reg32 *) 0xF0001048)->bit4
#define P4_ALTSEL1_P5            ((T_Reg32 *) 0xF0001048)->bit5
#define P4_ALTSEL1_P6            ((T_Reg32 *) 0xF0001048)->bit6
#define P4_ALTSEL1_P7            ((T_Reg32 *) 0xF0001048)->bit7

// Port 4 Direction Register
#define P4_DIR                 (*((uword volatile *) 0xF0001018))
#define P4_DIR_P0                ((T_Reg32 *) 0xF0001018)->bit0
#define P4_DIR_P1                ((T_Reg32 *) 0xF0001018)->bit1
#define P4_DIR_P2                ((T_Reg32 *) 0xF0001018)->bit2
#define P4_DIR_P3                ((T_Reg32 *) 0xF0001018)->bit3
#define P4_DIR_P4                ((T_Reg32 *) 0xF0001018)->bit4
#define P4_DIR_P5                ((T_Reg32 *) 0xF0001018)->bit5
#define P4_DIR_P6                ((T_Reg32 *) 0xF0001018)->bit6
#define P4_DIR_P7                ((T_Reg32 *) 0xF0001018)->bit7

// Port 4 Data Input Register
#define P4_IN                  (*((uword volatile *) 0xF0001014))
#define P4_IN_P0                 ((T_Reg32 *) 0xF0001014)->bit0
#define P4_IN_P1                 ((T_Reg32 *) 0xF0001014)->bit1
#define P4_IN_P2                 ((T_Reg32 *) 0xF0001014)->bit2
#define P4_IN_P3                 ((T_Reg32 *) 0xF0001014)->bit3
#define P4_IN_P4                 ((T_Reg32 *) 0xF0001014)->bit4
#define P4_IN_P5                 ((T_Reg32 *) 0xF0001014)->bit5
#define P4_IN_P6                 ((T_Reg32 *) 0xF0001014)->bit6
#define P4_IN_P7                 ((T_Reg32 *) 0xF0001014)->bit7

// Port 4 Open Drain Mode Register
#define P4_OD                  (*((uword volatile *) 0xF000101C))
#define P4_OD_P0                 ((T_Reg32 *) 0xF000101C)->bit0
#define P4_OD_P1                 ((T_Reg32 *) 0xF000101C)->bit1
#define P4_OD_P2                 ((T_Reg32 *) 0xF000101C)->bit2
#define P4_OD_P3                 ((T_Reg32 *) 0xF000101C)->bit3
#define P4_OD_P4                 ((T_Reg32 *) 0xF000101C)->bit4
#define P4_OD_P5                 ((T_Reg32 *) 0xF000101C)->bit5
#define P4_OD_P6                 ((T_Reg32 *) 0xF000101C)->bit6
#define P4_OD_P7                 ((T_Reg32 *) 0xF000101C)->bit7

// Port 4 Data Output Register
#define P4_OUT                 (*((uword volatile *) 0xF0001010))
#define P4_OUT_P0                ((T_Reg32 *) 0xF0001010)->bit0
#define P4_OUT_P1                ((T_Reg32 *) 0xF0001010)->bit1
#define P4_OUT_P2                ((T_Reg32 *) 0xF0001010)->bit2
#define P4_OUT_P3                ((T_Reg32 *) 0xF0001010)->bit3
#define P4_OUT_P4                ((T_Reg32 *) 0xF0001010)->bit4
#define P4_OUT_P5                ((T_Reg32 *) 0xF0001010)->bit5
#define P4_OUT_P6                ((T_Reg32 *) 0xF0001010)->bit6
#define P4_OUT_P7                ((T_Reg32 *) 0xF0001010)->bit7

// Port 4 Pull up/down Enable Register
#define P4_PUDEN               (*((uword volatile *) 0xF000102C))
#define P4_PUDEN_P0              ((T_Reg32 *) 0xF000102C)->bit0
#define P4_PUDEN_P1              ((T_Reg32 *) 0xF000102C)->bit1
#define P4_PUDEN_P2              ((T_Reg32 *) 0xF000102C)->bit2
#define P4_PUDEN_P3              ((T_Reg32 *) 0xF000102C)->bit3
#define P4_PUDEN_P4              ((T_Reg32 *) 0xF000102C)->bit4
#define P4_PUDEN_P5              ((T_Reg32 *) 0xF000102C)->bit5
#define P4_PUDEN_P6              ((T_Reg32 *) 0xF000102C)->bit6
#define P4_PUDEN_P7              ((T_Reg32 *) 0xF000102C)->bit7

// Port 4 Pull up/down Select Register
#define P4_PUDSEL              (*((uword volatile *) 0xF0001028))
#define P4_PUDSEL_P0             ((T_Reg32 *) 0xF0001028)->bit0
#define P4_PUDSEL_P1             ((T_Reg32 *) 0xF0001028)->bit1
#define P4_PUDSEL_P2             ((T_Reg32 *) 0xF0001028)->bit2
#define P4_PUDSEL_P3             ((T_Reg32 *) 0xF0001028)->bit3
#define P4_PUDSEL_P4             ((T_Reg32 *) 0xF0001028)->bit4
#define P4_PUDSEL_P5             ((T_Reg32 *) 0xF0001028)->bit5
#define P4_PUDSEL_P6             ((T_Reg32 *) 0xF0001028)->bit6
#define P4_PUDSEL_P7             ((T_Reg32 *) 0xF0001028)->bit7

// Program Counter
#define PC                     (*((uword volatile *) 0xF7E1FE08))
#define PC_0                     0x00000001

// Previous Context Information Register
#define PCXI                   (*((uword volatile *) 0xF7E1FE00))
#define PCXI_PIE                 0x00800000
#define PCXI_UL                  0x00400000

// PLL Clock Control Register
#define PLL_CLC                (*((uword volatile *) 0xF0000040))
#define PLL_CLC_BYPPIN           ((T_Reg32 *) 0xF0000040)->bit29
#define PLL_CLC_LOCK             ((T_Reg32 *) 0xF0000040)->bit0
#define PLL_CLC_OSCDISC          ((T_Reg32 *) 0xF0000040)->bit24
#define PLL_CLC_RESLD            ((T_Reg32 *) 0xF0000040)->bit1
#define PLL_CLC_SYSFSL           ((T_Reg32 *) 0xF0000040)->bit2
#define PLL_CLC_VCOBYP           ((T_Reg32 *) 0xF0000040)->bit5

// Power Management Control Register
#define PMG_CON                (*((uword volatile *) 0xF0000030))
#define PMG_CON_DSRE             ((T_Reg32 *) 0xF0000030)->bit0
#define PMG_CON_DSREQ            ((T_Reg32 *) 0xF0000030)->bit1

// Power Management Control and Status Register
#define PMG_CSR                (*((uword volatile *) 0xF0000034))

// PMI Control Register 0
#define PMI_CON0               (*((uword volatile *) 0xF87FFD10))
#define PMI_CON0_CC2SPR          ((T_Reg32 *) 0xF87FFD10)->bit0
#define PMI_CON0_CCBYP           ((T_Reg32 *) 0xF87FFD10)->bit1

// PMI Control Register 1
#define PMI_CON1               (*((uword volatile *) 0xF87FFD14))
#define PMI_CON1_CCINV           ((T_Reg32 *) 0xF87FFD14)->bit0

// PMI Control Register 2
#define PMI_CON2               (*((uword volatile *) 0xF87FFD18))

// PMI Module Identification Register
#define PMI_ID                 (*((uword volatile *) 0xF87FFD08))

// Program Status Word
#define PSW                    (*((uword volatile *) 0xF7E1FE04))
#define PSW_AV                   0x10000000
#define PSW_C                    0x80000000
#define PSW_CDE                  0x00000080
#define PSW_GW                   0x00000100
#define PSW_IS                   0x00000200
#define PSW_SAV                  0x08000000
#define PSW_SV                   0x20000000
#define PSW_V                    0x40000000

// RB Service Request Control 0 Register
#define RBSRC0                 (*((uword volatile *) 0xF000008C))
#define RBSRC0_CLRR              ((T_Reg32 *) 0xF000008C)->bit14
#define RBSRC0_SETR              ((T_Reg32 *) 0xF000008C)->bit15
#define RBSRC0_SRE               ((T_Reg32 *) 0xF000008C)->bit12
#define RBSRC0_SRR               ((T_Reg32 *) 0xF000008C)->bit13
#define RBSRC0_TOS               ((T_Reg32 *) 0xF000008C)->bit10

// RB Service Request Control 1 Register
#define RBSRC1                 (*((uword volatile *) 0xF0000090))
#define RBSRC1_CLRR              ((T_Reg32 *) 0xF0000090)->bit14
#define RBSRC1_SETR              ((T_Reg32 *) 0xF0000090)->bit15
#define RBSRC1_SRE               ((T_Reg32 *) 0xF0000090)->bit12
#define RBSRC1_SRR               ((T_Reg32 *) 0xF0000090)->bit13
#define RBSRC1_TOS               ((T_Reg32 *) 0xF0000090)->bit10

// Reset Request Register
#define RST_REQ                (*((uword volatile *) 0xF0000010))
#define RST_REQ_RREXT            ((T_Reg32 *) 0xF0000010)->bit2
#define RST_REQ_RRSTM            ((T_Reg32 *) 0xF0000010)->bit0
#define RST_REQ_SWBOOT           ((T_Reg32 *) 0xF0000010)->bit24
#define RST_REQ_SWBRKIN          ((T_Reg32 *) 0xF0000010)->bit21

// Reset Status Register
#define RST_SR                 (*((uword volatile *) 0xF0000014))
#define RST_SR_HDRST             ((T_Reg32 *) 0xF0000014)->bit28
#define RST_SR_HWBRKIN           ((T_Reg32 *) 0xF0000014)->bit21
#define RST_SR_PWDRST            ((T_Reg32 *) 0xF0000014)->bit31
#define RST_SR_PWORST            ((T_Reg32 *) 0xF0000014)->bit27
#define RST_SR_RSEXT             ((T_Reg32 *) 0xF0000014)->bit2
#define RST_SR_RSSTM             ((T_Reg32 *) 0xF0000014)->bit0
#define RST_SR_SFTRST            ((T_Reg32 *) 0xF0000014)->bit29
#define RST_SR_TESTMODE          ((T_Reg32 *) 0xF0000014)->bit20
#define RST_SR_WDTRST            ((T_Reg32 *) 0xF0000014)->bit30

// Redesign Tracing Identification Register
#define RTID                   (*((uword volatile *) 0xF0000078))
#define RTID_RT0                 ((T_Reg32 *) 0xF0000078)->bit0
#define RTID_RT1                 ((T_Reg32 *) 0xF0000078)->bit1
#define RTID_RT10                ((T_Reg32 *) 0xF0000078)->bit10
#define RTID_RT11                ((T_Reg32 *) 0xF0000078)->bit11
#define RTID_RT12                ((T_Reg32 *) 0xF0000078)->bit12
#define RTID_RT13                ((T_Reg32 *) 0xF0000078)->bit13
#define RTID_RT14                ((T_Reg32 *) 0xF0000078)->bit14
#define RTID_RT15                ((T_Reg32 *) 0xF0000078)->bit15
#define RTID_RT2                 ((T_Reg32 *) 0xF0000078)->bit2
#define RTID_RT3                 ((T_Reg32 *) 0xF0000078)->bit3
#define RTID_RT4                 ((T_Reg32 *) 0xF0000078)->bit4
#define RTID_RT5                 ((T_Reg32 *) 0xF0000078)->bit5
#define RTID_RT6                 ((T_Reg32 *) 0xF0000078)->bit6
#define RTID_RT7                 ((T_Reg32 *) 0xF0000078)->bit7
#define RTID_RT8                 ((T_Reg32 *) 0xF0000078)->bit8
#define RTID_RT9                 ((T_Reg32 *) 0xF0000078)->bit9

// SBCU Control Register
#define SBCU_CON               (*((uword volatile *) 0xF0000110))
#define SBCU_CON_DBG             ((T_Reg32 *) 0xF0000110)->bit16
#define SBCU_CON_PSE             ((T_Reg32 *) 0xF0000110)->bit18
#define SBCU_CON_SPE             ((T_Reg32 *) 0xF0000110)->bit19

// Debug Address1 Register (OCDS)
#define SBCU_DBADR1            (*((uword volatile *) 0xF0000138))

// Debug Address2 Register (OCDS)
#define SBCU_DBADR2            (*((uword volatile *) 0xF000013C))

// Debug Trapped Address Register (OCDS)
#define SBCU_DBADRT            (*((uword volatile *) 0xF0000148))

// Debug Bus Operation Register (OCDS)
#define SBCU_DBBOS             (*((uword volatile *) 0xF0000140))
#define SBCU_DBBOS_RD            ((T_Reg32 *) 0xF0000140)->bit12
#define SBCU_DBBOS_SVM           ((T_Reg32 *) 0xF0000140)->bit4
#define SBCU_DBBOS_WR            ((T_Reg32 *) 0xF0000140)->bit8

// Debug Trapped Bus Operation Register (OCDS)
#define SBCU_DBBOST            (*((uword volatile *) 0xF000014C))
#define SBCU_DBBOST_FPIABORT     ((T_Reg32 *) 0xF000014C)->bit13
#define SBCU_DBBOST_FPIOPS       ((T_Reg32 *) 0xF000014C)->bit11
#define SBCU_DBBOST_FPIRD        ((T_Reg32 *) 0xF000014C)->bit12
#define SBCU_DBBOST_FPIRDY       ((T_Reg32 *) 0xF000014C)->bit7
#define SBCU_DBBOST_FPISVM       ((T_Reg32 *) 0xF000014C)->bit4
#define SBCU_DBBOST_FPITOUT      ((T_Reg32 *) 0xF000014C)->bit14
#define SBCU_DBBOST_FPIWR        ((T_Reg32 *) 0xF000014C)->bit8

// Debug Control Register (OCDS)
#define SBCU_DBCNTL            (*((uword volatile *) 0xF0000130))
#define SBCU_DBCNTL_EO           ((T_Reg32 *) 0xF0000130)->bit0
#define SBCU_DBCNTL_OA           ((T_Reg32 *) 0xF0000130)->bit1
#define SBCU_DBCNTL_ONG          ((T_Reg32 *) 0xF0000130)->bit16
#define SBCU_DBCNTL_RA           ((T_Reg32 *) 0xF0000130)->bit4

// Debug Trapped Master Register (OCDS)
#define SBCU_DBGNTT            (*((uword volatile *) 0xF0000144))

// Debug Grant Mask Register (OCDS)
#define SBCU_DBGRNT            (*((uword volatile *) 0xF0000134))

// Error Address Capture Register
#define SBCU_EADD              (*((uword volatile *) 0xF0000124))

// Error Control Capture Register
#define SBCU_ECON              (*((uword volatile *) 0xF0000120))
#define SBCU_ECON_ABT            ((T_Reg32 *) 0xF0000120)->bit18
#define SBCU_ECON_RDN            ((T_Reg32 *) 0xF0000120)->bit23
#define SBCU_ECON_RDY            ((T_Reg32 *) 0xF0000120)->bit17
#define SBCU_ECON_SVM            ((T_Reg32 *) 0xF0000120)->bit21
#define SBCU_ECON_TOUT           ((T_Reg32 *) 0xF0000120)->bit16
#define SBCU_ECON_WRN            ((T_Reg32 *) 0xF0000120)->bit22

// Error Data Capture Register
#define SBCU_EDAT              (*((uword volatile *) 0xF0000128))

// SBCU Module Identification Register
#define SBCU_ID                (*((uword volatile *) 0xF0000108))

// SBCU Service Request Control Register
#define SBCU_SRC               (*((uword volatile *) 0xF00001FC))
#define SBCU_SRC_CLRR            ((T_Reg32 *) 0xF00001FC)->bit14
#define SBCU_SRC_SETR            ((T_Reg32 *) 0xF00001FC)->bit15
#define SBCU_SRC_SRE             ((T_Reg32 *) 0xF00001FC)->bit12
#define SBCU_SRC_SRR             ((T_Reg32 *) 0xF00001FC)->bit13
#define SBCU_SRC_TOS             ((T_Reg32 *) 0xF00001FC)->bit10

// SCU Control Register
#define SCU_CON                (*((uword volatile *) 0xF0000050))
#define SCU_CON_CANVRB           ((T_Reg32 *) 0xF0000050)->bit11
#define SCU_CON_CSGEN            ((T_Reg32 *) 0xF0000050)->bit3
#define SCU_CON_CSOEN            ((T_Reg32 *) 0xF0000050)->bit2
#define SCU_CON_DMIVRB           ((T_Reg32 *) 0xF0000050)->bit8
#define SCU_CON_DMUVRB           ((T_Reg32 *) 0xF0000050)->bit10
#define SCU_CON_EPUD             ((T_Reg32 *) 0xF0000050)->bit4
#define SCU_CON_FIEN             ((T_Reg32 *) 0xF0000050)->bit0
#define SCU_CON_NMIEN            ((T_Reg32 *) 0xF0000050)->bit5
#define SCU_CON_OUTEN            ((T_Reg32 *) 0xF0000050)->bit16
#define SCU_CON_PEREN            ((T_Reg32 *) 0xF0000050)->bit6
#define SCU_CON_PMIVRB           ((T_Reg32 *) 0xF0000050)->bit9
#define SCU_CON_RBOOTA           ((T_Reg32 *) 0xF0000050)->bit7
#define SCU_CON_VRBEN            ((T_Reg32 *) 0xF0000050)->bit1

// DMA Request Select Register
#define SCU_DMARS              (*((uword volatile *) 0xF00000DC))
#define SCU_DMARS_SEL0           ((T_Reg32 *) 0xF00000DC)->bit0
#define SCU_DMARS_SEL1           ((T_Reg32 *) 0xF00000DC)->bit1
#define SCU_DMARS_SEL2           ((T_Reg32 *) 0xF00000DC)->bit2
#define SCU_DMARS_SEL3           ((T_Reg32 *) 0xF00000DC)->bit3
#define SCU_DMARS_SEL4           ((T_Reg32 *) 0xF00000DC)->bit4
#define SCU_DMARS_SEL5           ((T_Reg32 *) 0xF00000DC)->bit5
#define SCU_DMARS_SEL6           ((T_Reg32 *) 0xF00000DC)->bit6
#define SCU_DMARS_SEL7           ((T_Reg32 *) 0xF00000DC)->bit7
#define SCU_DMARS_SEL8           ((T_Reg32 *) 0xF00000DC)->bit8
#define SCU_DMARS_SEL9           ((T_Reg32 *) 0xF00000DC)->bit9

// SCU Module Identification Register
#define SCU_ID                 (*((uword volatile *) 0xF0000008))

// SCU On Chip Test Control Register
#define SCU_OTCON              (*((uword volatile *) 0xF00000A8))
#define SCU_OTCON_OTMEN          ((T_Reg32 *) 0xF00000A8)->bit31

// SCU On Chip Test Data Register
#define SCU_OTDAT              (*((uword volatile *) 0xF00000AC))
#define SCU_OTDAT_T0             ((T_Reg32 *) 0xF00000AC)->bit0
#define SCU_OTDAT_T1             ((T_Reg32 *) 0xF00000AC)->bit1
#define SCU_OTDAT_T10            ((T_Reg32 *) 0xF00000AC)->bit10
#define SCU_OTDAT_T11            ((T_Reg32 *) 0xF00000AC)->bit11
#define SCU_OTDAT_T12            ((T_Reg32 *) 0xF00000AC)->bit12
#define SCU_OTDAT_T13            ((T_Reg32 *) 0xF00000AC)->bit13
#define SCU_OTDAT_T14            ((T_Reg32 *) 0xF00000AC)->bit14
#define SCU_OTDAT_T15            ((T_Reg32 *) 0xF00000AC)->bit15
#define SCU_OTDAT_T2             ((T_Reg32 *) 0xF00000AC)->bit2
#define SCU_OTDAT_T3             ((T_Reg32 *) 0xF00000AC)->bit3
#define SCU_OTDAT_T4             ((T_Reg32 *) 0xF00000AC)->bit4
#define SCU_OTDAT_T5             ((T_Reg32 *) 0xF00000AC)->bit5
#define SCU_OTDAT_T6             ((T_Reg32 *) 0xF00000AC)->bit6
#define SCU_OTDAT_T7             ((T_Reg32 *) 0xF00000AC)->bit7
#define SCU_OTDAT_T8             ((T_Reg32 *) 0xF00000AC)->bit8
#define SCU_OTDAT_T9             ((T_Reg32 *) 0xF00000AC)->bit9

// SCU Parity Error Trap Control Register
#define SCU_PETCR              (*((uword volatile *) 0xF0000068))
#define SCU_PETCR_PEN0           ((T_Reg32 *) 0xF0000068)->bit0
#define SCU_PETCR_PEN1           ((T_Reg32 *) 0xF0000068)->bit1
#define SCU_PETCR_PEN2           ((T_Reg32 *) 0xF0000068)->bit2
#define SCU_PETCR_PEN3           ((T_Reg32 *) 0xF0000068)->bit3
#define SCU_PETCR_PEN4           ((T_Reg32 *) 0xF0000068)->bit4

// SCU Parity Error Trap Status Register
#define SCU_PETSR              (*((uword volatile *) 0xF000006C))
#define SCU_PETSR_PFL0           ((T_Reg32 *) 0xF000006C)->bit0
#define SCU_PETSR_PFL1           ((T_Reg32 *) 0xF000006C)->bit1
#define SCU_PETSR_PFL2           ((T_Reg32 *) 0xF000006C)->bit2
#define SCU_PETSR_PFL3           ((T_Reg32 *) 0xF000006C)->bit3
#define SCU_PETSR_PFL4           ((T_Reg32 *) 0xF000006C)->bit4

// SCU Software Configuration Latched Inputs Register
#define SCU_SCLIR              (*((uword volatile *) 0xF0000038))
#define SCU_SCLIR_SW0PT0         ((T_Reg32 *) 0xF0000038)->bit0
#define SCU_SCLIR_SWOPT1         ((T_Reg32 *) 0xF0000038)->bit1
#define SCU_SCLIR_SWOPT10        ((T_Reg32 *) 0xF0000038)->bit10
#define SCU_SCLIR_SWOPT11        ((T_Reg32 *) 0xF0000038)->bit11
#define SCU_SCLIR_SWOPT12        ((T_Reg32 *) 0xF0000038)->bit12
#define SCU_SCLIR_SWOPT13        ((T_Reg32 *) 0xF0000038)->bit13
#define SCU_SCLIR_SWOPT14        ((T_Reg32 *) 0xF0000038)->bit14
#define SCU_SCLIR_SWOPT15        ((T_Reg32 *) 0xF0000038)->bit15
#define SCU_SCLIR_SWOPT2         ((T_Reg32 *) 0xF0000038)->bit2
#define SCU_SCLIR_SWOPT3         ((T_Reg32 *) 0xF0000038)->bit3
#define SCU_SCLIR_SWOPT4         ((T_Reg32 *) 0xF0000038)->bit4
#define SCU_SCLIR_SWOPT5         ((T_Reg32 *) 0xF0000038)->bit5
#define SCU_SCLIR_SWOPT6         ((T_Reg32 *) 0xF0000038)->bit6
#define SCU_SCLIR_SWOPT7         ((T_Reg32 *) 0xF0000038)->bit7
#define SCU_SCLIR_SWOPT8         ((T_Reg32 *) 0xF0000038)->bit8
#define SCU_SCLIR_SWOPT9         ((T_Reg32 *) 0xF0000038)->bit9

// SCU Status Register
#define SCU_STAT               (*((uword volatile *) 0xF0000054))
#define SCU_STAT_BOOTA           ((T_Reg32 *) 0xF0000054)->bit15
#define SCU_STAT_FII             ((T_Reg32 *) 0xF0000054)->bit4
#define SCU_STAT_FUI             ((T_Reg32 *) 0xF0000054)->bit1
#define SCU_STAT_FVI             ((T_Reg32 *) 0xF0000054)->bit3
#define SCU_STAT_FXI             ((T_Reg32 *) 0xF0000054)->bit0
#define SCU_STAT_FZI             ((T_Reg32 *) 0xF0000054)->bit2

// SSC Baudrate Timer Reload Register
#define SSC0_BR                (*((uword volatile *) 0xF0100114))

// SSC Clock Control Register
#define SSC0_CLC               (*((uword volatile *) 0xF0100100))
#define SSC0_CLC_DISR            0x00000001
#define SSC0_CLC_DISS            0x00000002
#define SSC0_CLC_EDIS            0x00000008
#define SSC0_CLC_FSOE            0x00000020
#define SSC0_CLC_SBWE            0x00000010
#define SSC0_CLC_SPEN            0x00000004

// SSC Control Register
#define SSC0_CON               (*((uword volatile *) 0xF0100110))
#define SSC0_CON_0               0x00002000
#define SSC0_CON_AREN            0x00001000
#define SSC0_CON_BEN             0x00000800
#define SSC0_CON_EN              0x00008000
#define SSC0_CON_HB              0x00000010
#define SSC0_CON_LB              0x00000080
#define SSC0_CON_MS              0x00004000
#define SSC0_CON_PEN             0x00000400
#define SSC0_CON_PH              0x00000020
#define SSC0_CON_PO              0x00000040
#define SSC0_CON_REN             0x00000200
#define SSC0_CON_TEN             0x00000100

// SSC Error Flag Modification Register
#define SSC0_EFM               (*((uword volatile *) 0xF010012C))
#define SSC0_EFM_CLRBE           0x00000800
#define SSC0_EFM_CLRPE           0x00000400
#define SSC0_EFM_CLRRE           0x00000200
#define SSC0_EFM_CLRTE           0x00000100
#define SSC0_EFM_SETBE           0x00008000
#define SSC0_EFM_SETPE           0x00004000
#define SSC0_EFM_SETRE           0x00002000
#define SSC0_EFM_SETTE           0x00001000

// SSC Error Interrupt Service Request Control Register
#define SSC0_ESRC              (*((uword volatile *) 0xF01001FC))
#define SSC0_ESRC_CLRR           0x00004000
#define SSC0_ESRC_SETR           0x00008000
#define SSC0_ESRC_SRE            0x00001000
#define SSC0_ESRC_SRR            0x00002000
#define SSC0_ESRC_TOS            0x00000400

// SSC Fractional Divider Register
#define SSC0_FDR               (*((uword volatile *) 0xF010010C))
#define SSC0_FDR_DISCLK          0x80000000
#define SSC0_FDR_ENHW            0x40000000
#define SSC0_FDR_SUSACK          0x10000000
#define SSC0_FDR_SUSREQ          0x20000000

// SSC FIFO Status Register
#define SSC0_FSTAT             (*((uword volatile *) 0xF0100138))

// SSC0 Module Identification Register
#define SSC0_ID                (*((uword volatile *) 0xF0100108))

// SSC Port Input Select Register
#define SSC0_PISEL             (*((uword volatile *) 0xF0100104))
#define SSC0_PISEL_MRIS          0x00000001
#define SSC0_PISEL_SCIS          0x00000004
#define SSC0_PISEL_SRIS          0x00000002
#define SSC0_PISEL_STIP          0x00000100

// SSC Receive Buffer Register
#define SSC0_RB                (*((uword volatile *) 0xF0100124))

// SSC Receive Interrupt Service Request Control Register
#define SSC0_RSRC              (*((uword volatile *) 0xF01001F8))
#define SSC0_RSRC_CLRR           0x00004000
#define SSC0_RSRC_SETR           0x00008000
#define SSC0_RSRC_SRE            0x00001000
#define SSC0_RSRC_SRR            0x00002000
#define SSC0_RSRC_TOS            0x00000400

// SSC Receive FIFO Control Register
#define SSC0_RXFCON            (*((uword volatile *) 0xF0100130))
#define SSC0_RXFCON_RXFEN        0x00000001
#define SSC0_RXFCON_RXFFLU       0x00000002
#define SSC0_RXFCON_RXTMEN       0x00000004

// Slave Select Output Control Register
#define SSC0_SSOC              (*((uword volatile *) 0xF0100118))
#define SSC0_SSOC_AOL0           0x00000001
#define SSC0_SSOC_AOL1           0x00000002
#define SSC0_SSOC_AOL2           0x00000004
#define SSC0_SSOC_AOL3           0x00000008
#define SSC0_SSOC_AOL4           0x00000010
#define SSC0_SSOC_AOL5           0x00000020
#define SSC0_SSOC_AOL6           0x00000040
#define SSC0_SSOC_AOL7           0x00000080
#define SSC0_SSOC_OEN0           0x00000100
#define SSC0_SSOC_OEN1           0x00000200
#define SSC0_SSOC_OEN2           0x00000400
#define SSC0_SSOC_OEN3           0x00000800
#define SSC0_SSOC_OEN4           0x00001000
#define SSC0_SSOC_OEN5           0x00002000
#define SSC0_SSOC_OEN6           0x00004000
#define SSC0_SSOC_OEN7           0x00008000

// Slave Select Output Timing Control Register
#define SSC0_SSOTC             (*((uword volatile *) 0xF010011C))
#define SSC0_SSOTC_SLSO7MOD      0x00000100

// SSC Status Register
#define SSC0_STAT              (*((uword volatile *) 0xF0100128))
#define SSC0_STAT_BE             0x00000800
#define SSC0_STAT_BSY            0x00001000
#define SSC0_STAT_PE             0x00000400
#define SSC0_STAT_RE             0x00000200
#define SSC0_STAT_TE             0x00000100

// SSC Transmit Buffer Register
#define SSC0_TB                (*((uword volatile *) 0xF0100120))

// SSC Transmit Interrupt Service Request Control Register
#define SSC0_TSRC              (*((uword volatile *) 0xF01001F4))
#define SSC0_TSRC_CLRR           0x00004000
#define SSC0_TSRC_SETR           0x00008000
#define SSC0_TSRC_SRE            0x00001000
#define SSC0_TSRC_SRR            0x00002000
#define SSC0_TSRC_TOS            0x00000400

// SSC Transmit FIFO Control Register
#define SSC0_TXFCON            (*((uword volatile *) 0xF0100134))
#define SSC0_TXFCON_TXFEN        0x00000001
#define SSC0_TXFCON_TXFFLU       0x00000002
#define SSC0_TXFCON_TXTMEN       0x00000004

// SSC Baudrate Timer Reload Register
#define SSC1_BR                (*((uword volatile *) 0xF0100214))

// SSC Clock Control Register
#define SSC1_CLC               (*((uword volatile *) 0xF0100200))
#define SSC1_CLC_DISR            0x00000001
#define SSC1_CLC_DISS            0x00000002
#define SSC1_CLC_EDIS            0x00000008
#define SSC1_CLC_FSOE            0x00000020
#define SSC1_CLC_SBWE            0x00000010
#define SSC1_CLC_SPEN            0x00000004

// SSC Control Register
#define SSC1_CON               (*((uword volatile *) 0xF0100210))
#define SSC1_CON_0               0x00002000
#define SSC1_CON_AREN            0x00001000
#define SSC1_CON_BEN             0x00000800
#define SSC1_CON_EN              0x00008000
#define SSC1_CON_HB              0x00000010
#define SSC1_CON_LB              0x00000080
#define SSC1_CON_MS              0x00004000
#define SSC1_CON_PEN             0x00000400
#define SSC1_CON_PH              0x00000020
#define SSC1_CON_PO              0x00000040
#define SSC1_CON_REN             0x00000200
#define SSC1_CON_TEN             0x00000100

// SSC Error Flag Modification Register
#define SSC1_EFM               (*((uword volatile *) 0xF010022C))
#define SSC1_EFM_CLRBE           0x00000800
#define SSC1_EFM_CLRPE           0x00000400
#define SSC1_EFM_CLRRE           0x00000200
#define SSC1_EFM_CLRTE           0x00000100
#define SSC1_EFM_SETBE           0x00008000
#define SSC1_EFM_SETPE           0x00004000
#define SSC1_EFM_SETRE           0x00002000
#define SSC1_EFM_SETTE           0x00001000

// SSC Error Interrupt Service Request Control Register
#define SSC1_ESRC              (*((uword volatile *) 0xF01002FC))
#define SSC1_ESRC_CLRR           0x00004000
#define SSC1_ESRC_SETR           0x00008000
#define SSC1_ESRC_SRE            0x00001000
#define SSC1_ESRC_SRR            0x00002000
#define SSC1_ESRC_TOS            0x00000400

// SSC Fractional Divider Register
#define SSC1_FDR               (*((uword volatile *) 0xF010020C))
#define SSC1_FDR_DISCLK          0x80000000
#define SSC1_FDR_ENHW            0x40000000
#define SSC1_FDR_SUSACK          0x10000000
#define SSC1_FDR_SUSREQ          0x20000000

// SSC FIFO Status Register
#define SSC1_FSTAT             (*((uword volatile *) 0xF0100238))

// SSC0 Module Identification Register
#define SSC1_ID                (*((uword volatile *) 0xF0100208))

// SSC Port Input Select Register
#define SSC1_PISEL             (*((uword volatile *) 0xF0100204))
#define SSC1_PISEL_MRIS          0x00000001
#define SSC1_PISEL_SCIS          0x00000004
#define SSC1_PISEL_SRIS          0x00000002
#define SSC1_PISEL_STIP          0x00000100

// SSC Receive Buffer Register
#define SSC1_RB                (*((uword volatile *) 0xF0100224))

// SSC Receive Interrupt Service Request Control Register
#define SSC1_RSRC              (*((uword volatile *) 0xF01002F8))
#define SSC1_RSRC_CLRR           0x00004000
#define SSC1_RSRC_SETR           0x00008000
#define SSC1_RSRC_SRE            0x00001000
#define SSC1_RSRC_SRR            0x00002000
#define SSC1_RSRC_TOS            0x00000400

// SSC Receive FIFO Control Register
#define SSC1_RXFCON            (*((uword volatile *) 0xF0100230))
#define SSC1_RXFCON_RXFEN        0x00000001
#define SSC1_RXFCON_RXFFLU       0x00000002
#define SSC1_RXFCON_RXTMEN       0x00000004

// Slave Select Output Control Register
#define SSC1_SSOC              (*((uword volatile *) 0xF0100218))
#define SSC1_SSOC_AOL0           0x00000001
#define SSC1_SSOC_AOL1           0x00000002
#define SSC1_SSOC_AOL2           0x00000004
#define SSC1_SSOC_AOL3           0x00000008
#define SSC1_SSOC_AOL4           0x00000010
#define SSC1_SSOC_AOL5           0x00000020
#define SSC1_SSOC_AOL6           0x00000040
#define SSC1_SSOC_AOL7           0x00000080
#define SSC1_SSOC_OEN0           0x00000100
#define SSC1_SSOC_OEN1           0x00000200
#define SSC1_SSOC_OEN2           0x00000400
#define SSC1_SSOC_OEN3           0x00000800
#define SSC1_SSOC_OEN4           0x00001000
#define SSC1_SSOC_OEN5           0x00002000
#define SSC1_SSOC_OEN6           0x00004000
#define SSC1_SSOC_OEN7           0x00008000

// Slave Select Output Timing Control Register
#define SSC1_SSOTC             (*((uword volatile *) 0xF010021C))
#define SSC1_SSOTC_SLSO7MOD      0x00000100

// SSC Status Register
#define SSC1_STAT              (*((uword volatile *) 0xF0100228))
#define SSC1_STAT_BE             0x00000800
#define SSC1_STAT_BSY            0x00001000
#define SSC1_STAT_PE             0x00000400
#define SSC1_STAT_RE             0x00000200
#define SSC1_STAT_TE             0x00000100

// SSC Transmit Buffer Register
#define SSC1_TB                (*((uword volatile *) 0xF0100220))

// SSC Transmit Interrupt Service Request Control Register
#define SSC1_TSRC              (*((uword volatile *) 0xF01002F4))
#define SSC1_TSRC_CLRR           0x00004000
#define SSC1_TSRC_SETR           0x00008000
#define SSC1_TSRC_SRE            0x00001000
#define SSC1_TSRC_SRR            0x00002000
#define SSC1_TSRC_TOS            0x00000400

// SSC Transmit FIFO Control Register
#define SSC1_TXFCON            (*((uword volatile *) 0xF0100234))
#define SSC1_TXFCON_TXFEN        0x00000001
#define SSC1_TXFCON_TXFFLU       0x00000002
#define SSC1_TXFCON_TXTMEN       0x00000004

// STM Capture Register
#define STM_CAP                (*((uword volatile *) 0xF000022C))

// STM Clock Control Register
#define STM_CLC                (*((uword volatile *) 0xF0000200))
#define STM_CLC_DISR             ((T_Reg32 *) 0xF0000200)->bit0
#define STM_CLC_DISS             ((T_Reg32 *) 0xF0000200)->bit1
#define STM_CLC_EDIS             ((T_Reg32 *) 0xF0000200)->bit3
#define STM_CLC_FSOE             ((T_Reg32 *) 0xF0000200)->bit5
#define STM_CLC_SBWE             ((T_Reg32 *) 0xF0000200)->bit4
#define STM_CLC_SPEN             ((T_Reg32 *) 0xF0000200)->bit2

// Compare Match Control Register
#define STM_CMCON              (*((uword volatile *) 0xF0000238))

// Compare Register 1
#define STM_CMP0               (*((uword volatile *) 0xF0000230))

// Compare Register 1
#define STM_CMP1               (*((uword volatile *) 0xF0000234))

// STM Interrupt Control Register
#define STM_ICR                (*((uword volatile *) 0xF000023C))
#define STM_ICR_CMP0EN           ((T_Reg32 *) 0xF000023C)->bit0
#define STM_ICR_CMP0IR           ((T_Reg32 *) 0xF000023C)->bit1
#define STM_ICR_CMP0OS           ((T_Reg32 *) 0xF000023C)->bit2
#define STM_ICR_CMP1EN           ((T_Reg32 *) 0xF000023C)->bit4
#define STM_ICR_CMP1IR           ((T_Reg32 *) 0xF000023C)->bit5
#define STM_ICR_CMP1OS           ((T_Reg32 *) 0xF000023C)->bit6

// STM Module Identification Register
#define STM_ID                 (*((uword volatile *) 0xF0000208))

// Interrupt Set/Reset Register
#define STM_ISRR               (*((uword volatile *) 0xF0000240))
#define STM_ISRR_CMP0IRR         ((T_Reg32 *) 0xF0000240)->bit0
#define STM_ISRR_CMP0IRS         ((T_Reg32 *) 0xF0000240)->bit1
#define STM_ISRR_CMP1IRR         ((T_Reg32 *) 0xF0000240)->bit2
#define STM_ISRR_CMP1IRS         ((T_Reg32 *) 0xF0000240)->bit3

// STM Service Request Control Register 0
#define STM_SRC0               (*((uword volatile *) 0xF00002FC))
#define STM_SRC0_CLRR            ((T_Reg32 *) 0xF00002FC)->bit14
#define STM_SRC0_SETR            ((T_Reg32 *) 0xF00002FC)->bit15
#define STM_SRC0_SRE             ((T_Reg32 *) 0xF00002FC)->bit12
#define STM_SRC0_SRR             ((T_Reg32 *) 0xF00002FC)->bit13
#define STM_SRC0_TOS             ((T_Reg32 *) 0xF00002FC)->bit10

// STM Service Request Control Register 1
#define STM_SRC1               (*((uword volatile *) 0xF00002F8))
#define STM_SRC1_CLRR            ((T_Reg32 *) 0xF00002F8)->bit14
#define STM_SRC1_SETR            ((T_Reg32 *) 0xF00002F8)->bit15
#define STM_SRC1_SRE             ((T_Reg32 *) 0xF00002F8)->bit12
#define STM_SRC1_SRR             ((T_Reg32 *) 0xF00002F8)->bit13
#define STM_SRC1_TOS             ((T_Reg32 *) 0xF00002F8)->bit10

// STM Register 0
#define STM_TIM0               (*((uword volatile *) 0xF0000210))

// STM Register 1
#define STM_TIM1               (*((uword volatile *) 0xF0000214))

// STM Register 2
#define STM_TIM2               (*((uword volatile *) 0xF0000218))

// STM Register 3
#define STM_TIM3               (*((uword volatile *) 0xF000021C))

// STM Register 4
#define STM_TIM4               (*((uword volatile *) 0xF0000220))

// STM Register 5
#define STM_TIM5               (*((uword volatile *) 0xF0000224))

// STM Register 6
#define STM_TIM6               (*((uword volatile *) 0xF0000228))

// Debug Instruction Break Event Specifier Register
#define SWEVT                  (*((uword volatile *) 0xF7E1FD10))
#define SWEVT_BBM                0x00000008
#define SWEVT_SUSP               0x00000020

// System Configuration Register
#define SYSCON                 (*((uword volatile *) 0xF7E1FE14))
#define SYSCON_FCDSF             0x00000001
#define SYSCON_PROTEN            0x00000002

// TB Service Request Control Register
#define TBSRC                  (*((uword volatile *) 0xF0000094))
#define TBSRC_CLRR               ((T_Reg32 *) 0xF0000094)->bit14
#define TBSRC_SETR               ((T_Reg32 *) 0xF0000094)->bit15
#define TBSRC_SRE                ((T_Reg32 *) 0xF0000094)->bit12
#define TBSRC_SRR                ((T_Reg32 *) 0xF0000094)->bit13
#define TBSRC_TOS                ((T_Reg32 *) 0xF0000094)->bit10

// Trigger Event 0 Specifier Register
#define TR0EVT                 (*((uword volatile *) 0xF7E1FD20))
#define TR0EVT_0                 0x00000010
#define TR0EVT_BBM               0x00000008
#define TR0EVT_DLR_LR            0x00000100
#define TR0EVT_DLR_U             0x00000200
#define TR0EVT_DU_LR             0x00000400
#define TR0EVT_DU_U              0x00000800
#define TR0EVT_SUSP              0x00000020

// Trigger Event 1 Specifier Register
#define TR1EVT                 (*((uword volatile *) 0xF7E1FD24))
#define TR1EVT_0                 0x00000010
#define TR1EVT_BBM               0x00000008
#define TR1EVT_DLR_LR            0x00000100
#define TR1EVT_DLR_U             0x00000200
#define TR1EVT_DU_LR             0x00000400
#define TR1EVT_DU_U              0x00000800
#define TR1EVT_SUSP              0x00000020


// Service Request Control Register 0
#define USB_SRC0               (*((uword volatile *) 0xF00E28FC))
#define USB_SRC0_CLRR            ((T_Reg32 *) 0xF00E28FC)->bit14
#define USB_SRC0_SETR            ((T_Reg32 *) 0xF00E28FC)->bit15
#define USB_SRC0_SRE             ((T_Reg32 *) 0xF00E28FC)->bit12
#define USB_SRC0_SRR             ((T_Reg32 *) 0xF00E28FC)->bit13
#define USB_SRC0_TOS             ((T_Reg32 *) 0xF00E28FC)->bit10

// Service Request Control Register 1
#define USB_SRC1               (*((uword volatile *) 0xF00E28F8))
#define USB_SRC1_CLRR            ((T_Reg32 *) 0xF00E28F8)->bit14
#define USB_SRC1_SETR            ((T_Reg32 *) 0xF00E28F8)->bit15
#define USB_SRC1_SRE             ((T_Reg32 *) 0xF00E28F8)->bit12
#define USB_SRC1_SRR             ((T_Reg32 *) 0xF00E28F8)->bit13
#define USB_SRC1_TOS             ((T_Reg32 *) 0xF00E28F8)->bit10

// Service Request Control Register 2
#define USB_SRC2               (*((uword volatile *) 0xF00E28F4))
#define USB_SRC2_CLRR            ((T_Reg32 *) 0xF00E28F4)->bit14
#define USB_SRC2_SETR            ((T_Reg32 *) 0xF00E28F4)->bit15
#define USB_SRC2_SRE             ((T_Reg32 *) 0xF00E28F4)->bit12
#define USB_SRC2_SRR             ((T_Reg32 *) 0xF00E28F4)->bit13
#define USB_SRC2_TOS             ((T_Reg32 *) 0xF00E28F4)->bit10

// Service Request Control Register 3
#define USB_SRC3               (*((uword volatile *) 0xF00E28F0))
#define USB_SRC3_CLRR            ((T_Reg32 *) 0xF00E28F0)->bit14
#define USB_SRC3_SETR            ((T_Reg32 *) 0xF00E28F0)->bit15
#define USB_SRC3_SRE             ((T_Reg32 *) 0xF00E28F0)->bit12
#define USB_SRC3_SRR             ((T_Reg32 *) 0xF00E28F0)->bit13
#define USB_SRC3_TOS             ((T_Reg32 *) 0xF00E28F0)->bit10

// Service Request Control Register 4
#define USB_SRC4               (*((uword volatile *) 0xF00E28EC))
#define USB_SRC4_CLRR            ((T_Reg32 *) 0xF00E28EC)->bit14
#define USB_SRC4_SETR            ((T_Reg32 *) 0xF00E28EC)->bit15
#define USB_SRC4_SRE             ((T_Reg32 *) 0xF00E28EC)->bit12
#define USB_SRC4_SRR             ((T_Reg32 *) 0xF00E28EC)->bit13
#define USB_SRC4_TOS             ((T_Reg32 *) 0xF00E28EC)->bit10

// Service Request Control Register 5
#define USB_SRC5               (*((uword volatile *) 0xF00E28E8))
#define USB_SRC5_CLRR            ((T_Reg32 *) 0xF00E28E8)->bit14
#define USB_SRC5_SETR            ((T_Reg32 *) 0xF00E28E8)->bit15
#define USB_SRC5_SRE             ((T_Reg32 *) 0xF00E28E8)->bit12
#define USB_SRC5_SRR             ((T_Reg32 *) 0xF00E28E8)->bit13
#define USB_SRC5_TOS             ((T_Reg32 *) 0xF00E28E8)->bit10

// Service Request Control Register 6
#define USB_SRC6               (*((uword volatile *) 0xF00E28E4))
#define USB_SRC6_CLRR            ((T_Reg32 *) 0xF00E28E4)->bit14
#define USB_SRC6_SETR            ((T_Reg32 *) 0xF00E28E4)->bit15
#define USB_SRC6_SRE             ((T_Reg32 *) 0xF00E28E4)->bit12
#define USB_SRC6_SRR             ((T_Reg32 *) 0xF00E28E4)->bit13
#define USB_SRC6_TOS             ((T_Reg32 *) 0xF00E28E4)->bit10

// Service Request Control Register 7
#define USB_SRC7               (*((uword volatile *) 0xF00E28E0))
#define USB_SRC7_CLRR            ((T_Reg32 *) 0xF00E28E0)->bit14
#define USB_SRC7_SETR            ((T_Reg32 *) 0xF00E28E0)->bit15
#define USB_SRC7_SRE             ((T_Reg32 *) 0xF00E28E0)->bit12
#define USB_SRC7_SRR             ((T_Reg32 *) 0xF00E28E0)->bit13
#define USB_SRC7_TOS             ((T_Reg32 *) 0xF00E28E0)->bit10


// Watchdog Timer Control Register 0
#define WDT_CON0               (*((uword volatile *) 0xF0000020))
#define WDT_CON0_ENDINIT         ((T_Reg32 *) 0xF0000020)->bit0
#define WDT_CON0_WDTLCK          ((T_Reg32 *) 0xF0000020)->bit1

// Watchdog Timer Control Register 1
#define WDT_CON1               (*((uword volatile *) 0xF0000024))
#define WDT_CON1_WDTDR           ((T_Reg32 *) 0xF0000024)->bit3
#define WDT_CON1_WDTIR           ((T_Reg32 *) 0xF0000024)->bit2

// Watchdog Timer Status Register
#define WDT_SR                 (*((uword volatile *) 0xF0000028))
#define WDT_SR_WDTAE             ((T_Reg32 *) 0xF0000028)->bit0
#define WDT_SR_WDTDS             ((T_Reg32 *) 0xF0000028)->bit3
#define WDT_SR_WDTIS             ((T_Reg32 *) 0xF0000028)->bit2
#define WDT_SR_WDTOE             ((T_Reg32 *) 0xF0000028)->bit1
#define WDT_SR_WDTPR             ((T_Reg32 *) 0xF0000028)->bit5
#define WDT_SR_WDTTO             ((T_Reg32 *) 0xF0000028)->bit4
#endif
