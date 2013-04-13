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
** @FILENAME@:       CAN_IIL.h
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: Contains the bit positions and bit masks related to the CAN module.
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

#ifndef __CAN_IIL_H
#define __CAN_IIL_H

#include "compiler.h"
#include "can_idl.h"

/*
  This function marks the selected message object as not valid. This means that
  this object cannot be sent or receive data. If the selected object is by 
  (meaning the object is transmitting a message or has received a new message)
  this function returns the value "0" and the object is not deleted.
*/
IFX_UINT8	CAN_DelMsgObj( IFX_UINT8 ObjNr ) ;

/*
 This function fills the forwarded SW message object with the content of the
 chosen HW message object. 
*/
void		CAN_vGetMsgObj( IFX_UINT8 ObjNr, CAN_MESSAGE_OBJECT *pstObj ) ;

/*
  This function sets up the message objects. This includes the 8 data bytes,
  the identifier (11- or 29-bit), the acceptance mask (11- or 29-bit), the 
  data number (0-8 bytes), the frame counter value and the EDE-bit (standard 
  or extended identifier).  The direction bit (DIR) can not be changed. The
  message is not sent; for this the function CAN_vTransmit mt be called.
*/
void		CAN_vConfigMsgObj( IFX_UINT8 ObjNr, CAN_MESSAGE_OBJECT *pstObj ) ;



/*
  Sets the interrupt priority and enable the indivadual interrupts.
*/
void		CAN_ISR_INIT(void);

/*
  Disable specified node
*/
void 		CAN_Disable_Node(CAN_DEVICE can_device);

/*
  Initialise CAN node
*/
CAN_STATUS	CAN_Init_Node(CAN_DEVICE can_device, CAN_COM_PARMS* can_init_parms);


/*
  Command to list controller.
*/
#define SET_LISTCOMMAND(Node, MsgObj)	(	\
											CAN_HW_PANCTR = \
											(	(	(IFX_UINT32)( Node + 1 ) << 24	)	|	\
												(	(IFX_UINT32)( MsgObj   ) << 16	)	|	\
												0x00000002 	\
											)	\
										); while( CAN_HW_PANCTR & CAN_PANCTR_BUSY );


#endif /*__CAN_IIL_H*/
