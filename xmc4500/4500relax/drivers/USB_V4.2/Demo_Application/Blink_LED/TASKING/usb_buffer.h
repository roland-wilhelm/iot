/* =============================================================================
** Copyright (C) 2005 Infineon Technologies.
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
** @FILENAME@:       usb_buffer.h
** @VERSION@:        4.0
** @DATE@:           02/12/2005  
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements the setup process interfaces as per USB1.1 
**              specification
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 26/10/2005     Jayashree               Created for Ring buffers and packet
**                                        descriptor details
** 2/12/2005    Jayashree (IFIN CSW AIM)  This file has been created for the ring 
**                                        buffers
**
** @CHANGE_HISTORY@
** =============================================================================
*/
#ifdef IFX_COMPILER_GNU
IFX_UINT8 main_buffer[600] __attribute__ ((aligned (4))); 
#else   /*for tasking*/
#pragma align 4
static IFX_UINT8 main_buffer[600];
#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif
#endif /* of IFX_COMPILER_GNU */

//Added for Testing Purpose
#define EXIT_SUCCESS 0
#define EXIT_FAULT -1

#define N_OUTPORTS  4  //# Endpoint ports
#define L_OUTBUFFER 256 //Length of output buffer for each endpoint port

struct pDescriptor  { /* generic packet descriptor */
  IFX_UINT8     rEP, wEP;   
  IFX_UINT16  	len;    	/* packet length in Octets*/
  IFX_UINT8  	*data;  	/* Byte pointer to the begin of the packet */   
}pD;

typedef struct rBuf
{
  IFX_UINT8             rArray[L_OUTBUFFER]; 
  IFX_UINT32 		    bufSize, nDesc;   
  IFX_UINT32   		    rPos , wPos ;      	
  IFX_UINT32        	full ;
  IFX_UINT32        	empty;             
}rB;             

    
struct	rBuf *USBD_initRBuf(IFX_UINT32 ep, unsigned);
void 	USBD_Init_Buffer(IFX_UINT32 ep); 
IFX_UINT32	USBD_pushRBuf( IFX_UINT8 ep, struct rBuf*,struct pDescriptor*);
IFX_UINT32	USBD_popRBuf( IFX_UINT8 ep, struct rBuf*,struct pDescriptor*);


