/* =============================================================================
** Copyright (C) 2004 Infineon Technologies.
**
** All rights reserved.
** =============================================================================
**
** =============================================================================
**
** This document contains proprietary information belonging to Infineon 
** Technologies. Passing on and copying of this document, and communication of 
** its contents is not permitted without prior written authorisation.
**
** =============================================================================
*/
/* =============================================================================
**
** Revision Information :
** @FILENAME@:       CAN_IDL.h
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: Provides the hardware dependent features like registers address 
**           mapping and control bit position in corresponding register. While 
**           porting to new hardware this file has to be ported
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      S.A.Kazmi          Release after code review.
** 21/06/2004      Mahesh             More comments added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

#ifndef __CAN_IDL_H
#define __CAN_IDL_H

#include "compiler.h"
#include "common.h"
#include "can_cfg.h"
#include "can_api.h"

/* Define the product this layer is written for: */
#define CAN_PRODUCT TC1130

/*
  Number of CAN nodes supported by CAN module
*/
#define CAN_HW_NUM 4

/****************************************************************************
 @Declaration of SFRs
****************************************************************************/
/*"MultiCAN Clock Control Register" */
#define CAN_HW_CLC			(*((IFX_UINT32 volatile *) 0xF0004000))
#define CAN_CLC_DISR		((T_Reg32 *) 0xF0004000)->bit0 
#define CAN_CLC_DISS		((T_Reg32 *) 0xF0004000)->bit1 
#define CAN_CLC_SPEN		((T_Reg32 *) 0xF0004000)->bit2 
#define CAN_CLC_EDIS		((T_Reg32 *) 0xF0004000)->bit3 
#define CAN_CLC_SBWE		((T_Reg32 *) 0xF0004000)->bit4 


/*"MultiCAN Module Identification Register" */
#define CAN_HW_ID			(*((IFX_UINT32 volatile *) 0xF0004008))

/*"MultiCAN Fractional Divider Register" */
#define CAN_HW_FDR			(*((IFX_UINT32 volatile *) 0xF000400C))
#define CAN_FDR_SUSACK		((T_Reg32 *) 0xF000400C)->bit28 
#define CAN_FDR_SUSREQ		((T_Reg32 *) 0xF000400C)->bit29 
#define CAN_FDR_ENHW		((T_Reg32 *) 0xF000400C)->bit30 
#define CAN_FDR_DISCLK		((T_Reg32 *) 0xF000400C)->bit31 

/*"CAN Service Request Control Register 15" */
#define CAN_HW_SRC15		(*((IFX_UINT32 volatile *) 0xF00040C0))
#define CAN_SRC15_TOS		((T_Reg32 *) 0xF00040C0)->bit10 
#define CAN_SRC15_SRE		((T_Reg32 *) 0xF00040C0)->bit12 
#define CAN_SRC15_SRR		((T_Reg32 *) 0xF00040C0)->bit13 
#define CAN_SRC15_CLRR		((T_Reg32 *) 0xF00040C0)->bit14 
#define CAN_SRC15_SETR		((T_Reg32 *) 0xF00040C0)->bit15 

/*"CAN Service Request Control Register 14" */
#define CAN_HW_SRC14		(*((IFX_UINT32 volatile *) 0xF00040C4))
#define CAN_SRC14_TOS		((T_Reg32 *) 0xF00040C4)->bit10 
#define CAN_SRC14_SRE		((T_Reg32 *) 0xF00040C4)->bit12 
#define CAN_SRC14_SRR		((T_Reg32 *) 0xF00040C4)->bit13 
#define CAN_SRC14_CLRR		((T_Reg32 *) 0xF00040C4)->bit14 
#define CAN_SRC14_SETR		((T_Reg32 *) 0xF00040C4)->bit15 

/*"CAN Service Request Control Register 13" */
#define CAN_HW_SRC13		(*((IFX_UINT32 volatile *) 0xF00040C8))
#define CAN_SRC13_TOS		((T_Reg32 *) 0xF00040C8)->bit10 
#define CAN_SRC13_SRE		((T_Reg32 *) 0xF00040C8)->bit12 
#define CAN_SRC13_SRR		((T_Reg32 *) 0xF00040C8)->bit13 
#define CAN_SRC13_CLRR		((T_Reg32 *) 0xF00040C8)->bit14 
#define CAN_SRC13_SETR		((T_Reg32 *) 0xF00040C8)->bit15 

/*"CAN Service Request Control Register 12" */
#define CAN_HW_SRC12		(*((IFX_UINT32 volatile *) 0xF00040CC))
#define CAN_SRC12_TOS		((T_Reg32 *) 0xF00040CC)->bit10 
#define CAN_SRC12_SRE		((T_Reg32 *) 0xF00040CC)->bit12 
#define CAN_SRC12_SRR		((T_Reg32 *) 0xF00040CC)->bit13 
#define CAN_SRC12_CLRR		((T_Reg32 *) 0xF00040CC)->bit14 
#define CAN_SRC12_SETR		((T_Reg32 *) 0xF00040CC)->bit15 

/*"CAN Service Request Control Register 11" */
#define CAN_HW_SRC11		(*((IFX_UINT32 volatile *) 0xF00040D0))
#define CAN_SRC11_TOS		((T_Reg32 *) 0xF00040D0)->bit10 
#define CAN_SRC11_SRE		((T_Reg32 *) 0xF00040D0)->bit12 
#define CAN_SRC11_SRR		((T_Reg32 *) 0xF00040D0)->bit13 
#define CAN_SRC11_CLRR		((T_Reg32 *) 0xF00040D0)->bit14 
#define CAN_SRC11_SETR		((T_Reg32 *) 0xF00040D0)->bit15 

/*"CAN Service Request Control Register 10" */
#define CAN_HW_SRC10		(*((IFX_UINT32 volatile *) 0xF00040D4))
#define CAN_SRC10_TOS		((T_Reg32 *) 0xF00040D4)->bit10 
#define CAN_SRC10_SRE		((T_Reg32 *) 0xF00040D4)->bit12 
#define CAN_SRC10_SRR		((T_Reg32 *) 0xF00040D4)->bit13 
#define CAN_SRC10_CLRR		((T_Reg32 *) 0xF00040D4)->bit14 
#define CAN_SRC10_SETR		((T_Reg32 *) 0xF00040D4)->bit15 

/*"CAN Service Request Control Register 9" */
#define CAN_HW_SRC9			(*((IFX_UINT32 volatile *) 0xF00040D8))
#define CAN_SRC9_SRE		((T_Reg32 *) 0xF00040D8)->bit12 
#define CAN_SRC9_SRR		((T_Reg32 *) 0xF00040D8)->bit13 
#define CAN_SRC9_CLRR		((T_Reg32 *) 0xF00040D8)->bit14 
#define CAN_SRC9_SETR		((T_Reg32 *) 0xF00040D8)->bit15 

/*"CAN Service Request Control Register 8" */
#define CAN_HW_SRC8			(*((IFX_UINT32 volatile *) 0xF00040DC))
#define CAN_SRC8_SRE		((T_Reg32 *) 0xF00040DC)->bit12 
#define CAN_SRC8_SRR		((T_Reg32 *) 0xF00040DC)->bit13 
#define CAN_SRC8_CLRR		((T_Reg32 *) 0xF00040DC)->bit14 
#define CAN_SRC8_SETR		((T_Reg32 *) 0xF00040DC)->bit15 

/*"CAN Service Request Control Register 7" */
#define CAN_HW_SRC7			(*((IFX_UINT32 volatile *) 0xF00040E0))
#define CAN_SRC7_SRE		((T_Reg32 *) 0xF00040E0)->bit12 
#define CAN_SRC7_SRR		((T_Reg32 *) 0xF00040E0)->bit13 
#define CAN_SRC7_CLRR		((T_Reg32 *) 0xF00040E0)->bit14 
#define CAN_SRC7_SETR		((T_Reg32 *) 0xF00040E0)->bit15 

/*"CAN Service Request Control Register 6" */
#define CAN_HW_SRC6			(*((IFX_UINT32 volatile *) 0xF00040E4))
#define CAN_SRC6_SRE		((T_Reg32 *) 0xF00040E4)->bit12 
#define CAN_SRC6_SRR		((T_Reg32 *) 0xF00040E4)->bit13 
#define CAN_SRC6_CLRR		((T_Reg32 *) 0xF00040E4)->bit14 
#define CAN_SRC6_SETR		((T_Reg32 *) 0xF00040E4)->bit15 

/*"CAN Service Request Control Register 5" */
#define CAN_HW_SRC5			(*((IFX_UINT32 volatile *) 0xF00040E8))
#define CAN_SRC5_SRE		((T_Reg32 *) 0xF00040E8)->bit12 
#define CAN_SRC5_SRR		((T_Reg32 *) 0xF00040E8)->bit13 
#define CAN_SRC5_CLRR		((T_Reg32 *) 0xF00040E8)->bit14 
#define CAN_SRC5_SETR		((T_Reg32 *) 0xF00040E8)->bit15 

/*"CAN Service Request Control Register 4" */
#define CAN_HW_SRC4			(*((IFX_UINT32 volatile *) 0xF00040EC))
#define CAN_SRC4_SRE		((T_Reg32 *) 0xF00040EC)->bit12 
#define CAN_SRC4_SRR		((T_Reg32 *) 0xF00040EC)->bit13 
#define CAN_SRC4_CLRR		((T_Reg32 *) 0xF00040EC)->bit14 
#define CAN_SRC4_SETR		((T_Reg32 *) 0xF00040EC)->bit15 

/*"CAN Service Request Control Register 3" */
#define CAN_HW_SRC3			(*((IFX_UINT32 volatile *) 0xF00040F0))
#define CAN_SRC3_SRE		((T_Reg32 *) 0xF00040F0)->bit12 
#define CAN_SRC3_SRR		((T_Reg32 *) 0xF00040F0)->bit13 
#define CAN_SRC3_CLRR		((T_Reg32 *) 0xF00040F0)->bit14 
#define CAN_SRC3_SETR		((T_Reg32 *) 0xF00040F0)->bit15 

/*"CAN Service Request Control Register 2" */
#define CAN_HW_SRC2			(*((IFX_UINT32 volatile *) 0xF00040F4))
#define CAN_SRC2_SRE		((T_Reg32 *) 0xF00040F4)->bit12 
#define CAN_SRC2_SRR		((T_Reg32 *) 0xF00040F4)->bit13 
#define CAN_SRC2_CLRR		((T_Reg32 *) 0xF00040F4)->bit14 
#define CAN_SRC2_SETR		((T_Reg32 *) 0xF00040F4)->bit15 

/*"CAN Service Request Control Register 1" */
#define CAN_HW_SRC1			(*((IFX_UINT32 volatile *) 0xF00040F8))
#define CAN_SRC1_SRE		((T_Reg32 *) 0xF00040F8)->bit12 
#define CAN_SRC1_SRR		((T_Reg32 *) 0xF00040F8)->bit13 
#define CAN_SRC1_CLRR		((T_Reg32 *) 0xF00040F8)->bit14 
#define CAN_SRC1_SETR		((T_Reg32 *) 0xF00040F8)->bit15 

/*"CAN Service Request Control Register 0" */
#define CAN_HW_SRC0			(*((IFX_UINT32 volatile *) 0xF00040FC))
#define CAN_SRC0_SRE		((T_Reg32 *) 0xF00040FC)->bit12 
#define CAN_SRC0_SRR		((T_Reg32 *) 0xF00040FC)->bit13 
#define CAN_SRC0_CLRR		((T_Reg32 *) 0xF00040FC)->bit14 
#define CAN_SRC0_SETR		((T_Reg32 *) 0xF00040FC)->bit15 



/* "Message Index Registers"  */
#define CAN_HW_MSID0			(*((IFX_UINT32 volatile *) 0xF0004140))
#define CAN_HW_MSID1			(*((IFX_UINT32 volatile *) 0xF0004144))
#define CAN_HW_MSID2			(*((IFX_UINT32 volatile *) 0xF0004148))
#define CAN_HW_MSID3			(*((IFX_UINT32 volatile *) 0xF000414C))
#define CAN_HW_MSID4			(*((IFX_UINT32 volatile *) 0xF0004150))
#define CAN_HW_MSID5			(*((IFX_UINT32 volatile *) 0xF0004154))
#define CAN_HW_MSID6			(*((IFX_UINT32 volatile *) 0xF0004158))
#define CAN_HW_MSID7			(*((IFX_UINT32 volatile *) 0xF000415C))
#define CAN_HW_MSIMASK			(*((IFX_UINT32 volatile *) 0xF00041C0))


#define CAN_HW_MSID 			((IFX_UINT32 volatile *) 0xF0004140)
#define CAN_HW_MSPND			((IFX_UINT32 volatile *) 0xF0004120)

/* "Panel Control Register" */
#define CAN_HW_PANCTR			(*((IFX_UINT32 volatile *) 0xF00041C4))
#define CAN_PANCTR_BUSY		    ((T_Reg32 *) 0xF00041C4)->bit8 
#define CAN_PANCTR_RBUSY		((T_Reg32 *) 0xF00041C4)->bit9 

/*"Module Interrupt Trigger Register" */
#define CAN_HW_MITR			(*((IFX_UINT32 volatile *) 0xF00041CC))

/*"Node 0 Control Register" */
#define CAN_HW_NCR0			(*((IFX_UINT32 volatile *) 0xF0004200))
#define CAN_NCR0_INIT		((T_Reg32 *) 0xF0004200)->bit0 
#define CAN_NCR0_TRIE		((T_Reg32 *) 0xF0004200)->bit1 
#define CAN_NCR0_LECIE		((T_Reg32 *) 0xF0004200)->bit2 
#define CAN_NCR0_ALIE		((T_Reg32 *) 0xF0004200)->bit3 
#define CAN_NCR0_CANDIS		((T_Reg32 *) 0xF0004200)->bit4 
#define CAN_NCR0_CCE		((T_Reg32 *) 0xF0004200)->bit6 
#define CAN_NCR0_CALM		((T_Reg32 *) 0xF0004200)->bit7 
#define CAN_NCR0_SUSEN		((T_Reg32 *) 0xF0004200)->bit8 

/*"Node 0 Status Register" */
#define CAN_HW_NSR0			(*((IFX_UINT32 volatile *) 0xF0004204))
#define CAN_NSR0_EWRN		((T_Reg32 *) 0xF0004204)->bit6 
#define CAN_NSR0_BOFF		((T_Reg32 *) 0xF0004204)->bit7 
#define CAN_NSR0_LLE		((T_Reg32 *) 0xF0004204)->bit8 
#define CAN_NSR0_LOE		((T_Reg32 *) 0xF0004204)->bit9 
#define CAN_NSR0_SUSACK		((T_Reg32 *) 0xF0004204)->bit10 

#define CAN_NBTR0_DIV8		((T_Reg32 *) 0xF0004210)->bit15 
#define CAN_NBTR0_FTX		((T_Reg32 *) 0xF0004210)->bit16 

#define CAN_NECNT0_LETD		((T_Reg32 *) 0xF0004214)->bit24 
#define CAN_NECNT0_LEINC	((T_Reg32 *) 0xF0004214)->bit25 

/*"Node 0 Frame Counter Register" */
#define CAN_HW_NFCR0		(*((IFX_UINT32 volatile *) 0xF0004218))

/*"Node 1 Control Register" */
#define CAN_HW_NCR1			(*((IFX_UINT32 volatile *) 0xF0004300))
#define CAN_NCR1_INIT		((T_Reg32 *) 0xF0004300)->bit0 
#define CAN_NCR1_TRIE		((T_Reg32 *) 0xF0004300)->bit1 
#define CAN_NCR1_LECIE		((T_Reg32 *) 0xF0004300)->bit2 
#define CAN_NCR1_ALIE		((T_Reg32 *) 0xF0004300)->bit3 
#define CAN_NCR1_CANDIS		((T_Reg32 *) 0xF0004300)->bit4 
#define CAN_NCR1_CCE		((T_Reg32 *) 0xF0004300)->bit6 
#define CAN_NCR1_CALM		((T_Reg32 *) 0xF0004300)->bit7 
#define CAN_NCR1_SUSEN		((T_Reg32 *) 0xF0004300)->bit8 

/*"Node 1 Status Register" */
#define CAN_HW_NSR1			(*((IFX_UINT32 volatile *) 0xF0004304))
#define CAN_NSR1_EWRN		((T_Reg32 *) 0xF0004304)->bit6 
#define CAN_NSR1_BOFF		((T_Reg32 *) 0xF0004304)->bit7 
#define CAN_NSR1_LLE		((T_Reg32 *) 0xF0004304)->bit8 
#define CAN_NSR1_LOE		((T_Reg32 *) 0xF0004304)->bit9 
#define CAN_NSR1_SUSACK		((T_Reg32 *) 0xF0004304)->bit10 

#define CAN_NBTR1_DIV8		((T_Reg32 *) 0xF0004310)->bit15 
#define CAN_NBTR1_FTX		((T_Reg32 *) 0xF0004310)->bit16 

#define CAN_NECNT1_LETD		((T_Reg32 *) 0xF0004314)->bit24 
#define CAN_NECNT1_LEINC	((T_Reg32 *) 0xF0004314)->bit25 

/*"Node 1 Frame Counter Register" */
#define CAN_HW_NFCR1		(*((IFX_UINT32 volatile *) 0xF0004318))

/*"Node 2 Control Register" */
#define CAN_NCR2_INIT		((T_Reg32 *) 0xF0004400)->bit0 
#define CAN_NCR2_TRIE		((T_Reg32 *) 0xF0004400)->bit1 
#define CAN_NCR2_LECIE		((T_Reg32 *) 0xF0004400)->bit2 
#define CAN_NCR2_ALIE		((T_Reg32 *) 0xF0004400)->bit3 
#define CAN_NCR2_CANDIS		((T_Reg32 *) 0xF0004400)->bit4 
#define CAN_NCR2_CCE		((T_Reg32 *) 0xF0004400)->bit6 
#define CAN_NCR2_CALM		((T_Reg32 *) 0xF0004400)->bit7 
#define CAN_NCR2_SUSEN		((T_Reg32 *) 0xF0004400)->bit8 

/*"Node 2 Status Register" */
#define CAN_HW_NSR2			(*((IFX_UINT32 volatile *) 0xF0004404))
#define CAN_NSR2_EWRN		((T_Reg32 *) 0xF0004404)->bit6 
#define CAN_NSR2_BOFF		((T_Reg32 *) 0xF0004404)->bit7 
#define CAN_NSR2_LLE		((T_Reg32 *) 0xF0004404)->bit8 
#define CAN_NSR2_LOE		((T_Reg32 *) 0xF0004404)->bit9 
#define CAN_NSR2_SUSACK		((T_Reg32 *) 0xF0004404)->bit10 

/*"Node 2 Port Control Register" */
#define CAN_HW_NPCR2		(*((IFX_UINT32 volatile *) 0xF000440C))

/*"Node 2 Bit Timing Register" */
#define CAN_NBTR2_DIV8		((T_Reg32 *) 0xF0004410)->bit15 
#define CAN_NBTR2_FTX		((T_Reg32 *) 0xF0004410)->bit16 

/*"Node 2 Error Counter Register" */
#define CAN_NECNT2_LETD		((T_Reg32 *) 0xF0004414)->bit24 
#define CAN_NECNT2_LEINC	((T_Reg32 *) 0xF0004414)->bit25 

/*"Node 2 Frame Counter Register" */
#define CAN_HW_NFCR2		(*((IFX_UINT32 volatile *) 0xF0004418))

/*"Node 3 Control Register" */
#define CAN_HW_NCR3			(*((IFX_UINT32 volatile *) 0xF0004500))
#define CAN_NCR3_INIT		((T_Reg32 *) 0xF0004500)->bit0 
#define CAN_NCR3_TRIE		((T_Reg32 *) 0xF0004500)->bit1 
#define CAN_NCR3_LECIE		((T_Reg32 *) 0xF0004500)->bit2 
#define CAN_NCR3_ALIE		((T_Reg32 *) 0xF0004500)->bit3 
#define CAN_NCR3_CANDIS		((T_Reg32 *) 0xF0004500)->bit4 
#define CAN_NCR3_CCE		((T_Reg32 *) 0xF0004500)->bit6 
#define CAN_NCR3_CALM		((T_Reg32 *) 0xF0004500)->bit7 
#define CAN_NCR3_SUSEN		((T_Reg32 *) 0xF0004500)->bit8 

/*"Node 3 Status Register" */
#define CAN_HW_NSR3			(*((IFX_UINT32 volatile *) 0xF0004504))
#define CAN_NSR3_EWRN		((T_Reg32 *) 0xF0004504)->bit6 
#define CAN_NSR3_BOFF		((T_Reg32 *) 0xF0004504)->bit7 
#define CAN_NSR3_LLE		((T_Reg32 *) 0xF0004504)->bit8 
#define CAN_NSR3_LOE		((T_Reg32 *) 0xF0004504)->bit9 
#define CAN_NSR3_SUSACK		((T_Reg32 *) 0xF0004504)->bit10 

/*"Node 3 Bit Timing Register" */
#define CAN_NBTR3_DIV8		((T_Reg32 *) 0xF0004510)->bit15 
#define CAN_NBTR3_FTX		((T_Reg32 *) 0xF0004510)->bit16 

/*"Node 3 Error Counter Register" */
#define CAN_NECNT3_LETD		((T_Reg32 *) 0xF0004514)->bit24 
#define CAN_NECNT3_LEINC	((T_Reg32 *) 0xF0004514)->bit25 

/*"Node 3 Frame Counter Register" */
#define CAN_HW_NFCR3		(*((IFX_UINT32 volatile *) 0xF0004518))

/*
  CAN Node control and status fields, for more information about each field
  refer to CAN_API.h file.
*/
typedef struct  
{
	IFX_VUINT32	CAN_NCR  ;	/*@field	Node Control Register for the MultiCan Module				*/
	IFX_VUINT32	CAN_NSR  ;	/*@field	Node Stat Register for the MultiCan Module				*/
	IFX_VUINT32	CAN_NIPR ;	/*@field	Node Interrupt Priority Register for the MultiCan Module	*/
	IFX_VUINT32	CAN_NPCR ;	/*@field	Node Port Control Register for the MultiCan Module			*/
	IFX_VUINT32	CAN_NBTR ;	/*@field	Node Bit timing Register for the MultiCan Module			*/	
	IFX_VUINT32	CAN_NECNT;	/*@field	Node Error Counter Register for the MultiCan Module			*/		
	IFX_VUINT32	CAN_NFCR ;	/*@field	Node Frame Counter Register for the MultiCan Module			*/
}CAN_HW_stCanNodeObj;	

/*
  Base address of each CAN node
*/
#define CAN_HW_NODE0  ( (volatile CAN_HW_stCanNodeObj* ) 0xF0004200 ) 
#define CAN_HW_NODE1  ( (volatile CAN_HW_stCanNodeObj* ) 0xF0004300 ) 
#define CAN_HW_NODE2  ( (volatile CAN_HW_stCanNodeObj* ) 0xF0004400 ) 
#define CAN_HW_NODE3  ( (volatile CAN_HW_stCanNodeObj* ) 0xF0004500 )

#define CAN_HW_TABLE volatile CAN_HW_stCanNodeObj* CAN_NODE_ADDR[CAN_HW_NUM] \
= {CAN_HW_NODE0, CAN_HW_NODE1, CAN_HW_NODE2, CAN_HW_NODE3}

#define CAN_NODE(x) CAN_NODE_ADDR[x]


/*
  Bit masks and location for CAN module.
*/
#define	CAN_MOCTRX_RXPND	0x00000001
#define CAN_MOCTRX_DIR      0x00000800
#define CAN_MOCTRX_MSGLST   0x00000010
#define CAN_MOCTRX_MSGVAL   0x00000020
#define CAN_MOCTRX_NEWDAT   0x00000008
#define CAN_MOCTRX_RTSEL    0x00000040
#define CAN_MOCTRX_RXEN     0x00000080
#define CAN_MOCTRX_RXPND    0x00000001
#define CAN_MOCTRX_RXUPD    0x00000004
#define CAN_MOCTRX_TXEN0    0x00000200
#define CAN_MOCTRX_TXEN1    0x00000400
#define CAN_MOCTRX_TXPND    0x00000002
#define CAN_MOCTRX_TXRQ     0x00000100


#define CAN_MODULE_NUMBER_MASK		0xFFFF0000
#define CAN_MODULE_TYPE_MASK		0x0000FF00
#define CAN_MODULE_REV_MASK			0x000000FF
#define FDR_STEP_MASK				0x000003FF
#define FDR_SUSCTRL_MASK			0x00003000
#define FDR_DIVIDOR_MASK			0x0000C000
#define TRANSMIT_ENABLE_MASK		0x07000000
#define DATA_LENGTH_MASK			0x0F000000
#define NEWDATA_PRESENT_MASK		0x00000008
#define NCRX_INIT_MASK				0x00000001
#define NCRX_TRIE_MASK				0x00000002
#define NCRX_LECIE_MASK				0x00000004
#define NCRX_ALIE_MASK				0x00000008
#define NCRX_CAN_DIS_MASK			0x00000010
#define NCRX_CCE_MASK				0x00000040
#define NCRX_CALM_MASK				0x00000080
#define NCRX_SUSEN_MASK				0x00000100
#define NIPRX_ALINP_MASK			0x0000000F
#define NIPRX_LECINP_MASK			0x000000F0
#define NIPRX_TRINP_MASK			0x00000F00
#define NIPRX_CFCINP_MASK			0x0000F000
#define NECNTX_EWRNLVL_MASK			0x00FF0000
#define NBTRX_TSEG1_MASK			0x00000F00
#define NBTRX_TSEG2_MASK			0x00007000
#define NBTRX_SJW_MASK				0x000000C0
#define NBTRX_BRP_MASK				0x0000003F
#define NFCRX_CFCSEL_MASK			0x00070000
#define NFCRX_CFC_MASK				0x0000FFFF
#define NFCRX_CFMOD_MASK			0x00180000
#define NPCRX_LOOPBACK_MASK			0x00000100
#define SRCN_SRPN_MASK				0x000000FF
#define PO_PULLUP_PULLDN_SEL_MASK	0x0000FF00
#define PO_OPEN_DRAIN_MASK			0x0000AA00
#define P1_PULLUP_PULLDN_SEL_MASK	0x000000FF
#define P1_OPEN_DRAIN_MASK			0x0000000A
#define CLK_DISR_MASK				0x00000001
#define MOFCR_MMC_MASK 				0x0000000F

#define CAN_HW_NSR_TXOK             0x00000008 
#define CAN_HW_NSR_RXOK             0x00000010
#define CAN_HW_NSR_EWRN				0x00000040
#define CAN_HW_NSR_BOFF             0x00000080
#define CAN_HW_NSR_ALERT            0x00000020   

#define P0_PULLUP_PULLDN_EN_MASK	0x0000FF00	  			
#define P1_PULLUP_PULLDN_EN_MASK	0x000000FF

#define DLC_LOCATION					24
#define FDR_DIVIDOR_LOCATION			14
#define FDR_SUSCTRL_LOCATION			12
#define NODE_INIT_LOCATION				0 
#define NODE_TRIE_LOCATION				1
#define NODE_LECIE_LOCATION				2
#define	NODE_ALIE_LOCATION				3
#define	NODE_CANDIS_LOCATION			4
#define	NODE_CCE_LOCATION				6
#define NODE_CALM_LOCATION				7
#define NODE_SUSEN_LOCATION				7
#define NODE_LOOP_BACK_LOCATION			8
#define NIPRX_ALINP_LOCATION			0
#define NIPRX_LECINP_LOCATION			4
#define NIPRX_TRINP_LOCATION			8
#define NIPRX_CFCINP_LOCATION			12
#define NECNTX_EWRNLVL_LOCATION			16
#define DIV8_LOCATION					15
#define NBTRX_TSEG1_LOCATION			8
#define NBTRX_TSEG2_LOCATION			12
#define NBTRX_SJW_LOCATION				6
#define NBTRX_BRP_LOCATION				0
#define NFCRX_CFCSEL_LOCATION			16
#define NFCRX_CFCIE_LOCATION			22
#define NFCRX_CFC_LOCATION				0
#define NFCRX_CFMOD_LOCATION			19
#define NPCRX_LOOPBACK_LOCATION			8
#define SRCN_SRE_LOCATION				12
#define	SRCN_TOS_LOCATION				10
#define SRCN_SRPN_LOCATION				0
#define PO_PULLUP_PULLDN_SEL_LOCATION	8
#define PO_OPEN_DRAIN_LOCATION			8
#define P1_PULLUP_PULLDN_SEL_LOCATION	0
#define P1_OPEN_DRAIN_LOCATION			0
#define P0_PULLUP_PULLDN_EN_LOCATION	8
#define P1_PULLUP_PULLDN_EN_LOCATION	0
#define CLK_DISR_LOCATION				0
#define MOFCR_MMC_LOCATION				0

#define IS_TRANSMIT_OBJECT		0x00000800
#define IS_EXTENDED_IDENTIFIER	0x20000000
#define CAN_NODE_DISABLE		0x00000010
#define	RESET_NEWDAT			0x00000008
#define	SET_MSGVAL				0x00200000
#define TRANSMIT_ENABLE			0x0F000000	

#define MAX_NODES				4
#define MAX_MSGOBJECTS 128
#define	INIT_AND_CCE	0x00000041

#define CAN_READ_ISR_BASE	0x00000001
#define CAN_WRITE_ISR_BASE	0x00000005

#define CFSEL_ALL 7
#define CFMOD_ALL 3

#define CFSEL_FRAME_TX_CORRECT			0x00000004
#define CFSEL_TIME_RX_CORRECT			0x00000002
#define CFSEL_BIT_FOREIGN_MONITORED		0x00000001

#define CFMOD_FRAME_BASE				0x0000
#define CFMOD_TIME_BASE					0x0001
#define CFMOD_BIT_TIMING_MODE			0x0002

#define MMC_TX_BASE_VALUE 				0x00000002
#define MMC_RX_BASE_VALUE 				0x00000001
#define	MMC_TX_SLAVE_VALUE				0x00000003
#define MMC_GATEWAY_SRC_OB				0x00000004

#define	CAN_MOCTRX_RXPND				0x00000001
#define CAN_MOCTRX_DIR      			0x00000800
#define CAN_MOCTRX_MSGLST   			0x00000010
#define CAN_MOCTRX_MSGVAL    			0x00000020
#define CAN_MOCTRX_NEWDAT   			0x00000008
#define CAN_MOCTRX_RTSEL    			0x00000040
#define CAN_MOCTRX_RXEN    				0x00000080
#define CAN_MOCTRX_RXPND    			0x00000001
#define CAN_MOCTRX_RXUPD    			0x00000004
#define CAN_MOCTRX_TXEN0    			0x00000200
#define CAN_MOCTRX_TXEN1    			0x00000400
#define CAN_MOCTRX_TXPND    			0x00000002
#define CAN_MOCTRX_TXRQ     			0x00000100
#define CAN_NFCR_CFCOV					0x00800000

/*Maximum number of message objects*/
#define CAN_HW_MAX_MSGOBJS 128
 
/* Structure for a single MultiCAN Message object
 A total of 128 (0 - 127) such object structures exist continuously  */
typedef struct
{
	IFX_VUINT32	MOFCR  ;	/* Function Control Register */
	IFX_VUINT32	MOFGPR ;	/* FIFO/Gateway Pointer Register */
	IFX_VUINT32	MOIPR  ;  	/* Interrupt Pointer Register */
	IFX_VUINT32	MOAMR  ;  	/* Acceptance Mask Register	*/
	IFX_VUINT8  MODATA[8] ; /* Message Data	   */
	IFX_VUINT32	MOAR   ;  	/* Arbitration Register	*/
	IFX_VUINT32	MOCTR  ;  	/* Control Register	*/ 		
}CAN_HW_stCanMsgObj;

#define CAN_MSGOBJ ((CAN_HW_stCanMsgObj volatile*) 0xF0004600) 

#if (IFX_COMPILER_GNU == 1)
/*
  GNU compiler dependant interrupt initialization routine.
*/
void CAN_HW_register_isr(void);					  
#endif

/*
 CAN message object transmit ISR 
*/
void CAN_TXMOBJ_ISR(IFX_UINT8 CAN_node_num);

/*
 CAN message object receive ISR 
*/
void CAN_RXMOBJ_ISR(IFX_UINT8 CAN_node_num);
/*
  Message frame transfer interrupt service routine
*/
void CAN_TRANSFER_ISR(IFX_UINT8 CAN_node);

/*
  CAN node protocol error ISR
*/
void CAN_LEC_ISR(IFX_UINT8 CAN_node);

/*
  CAN node alert ISR
*/
void CAN_ALERT_CFC_ISR(IFX_UINT8 CAN_node);

#endif /*__CAN_IDL_H*/
