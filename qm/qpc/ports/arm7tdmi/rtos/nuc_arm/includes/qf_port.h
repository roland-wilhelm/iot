/*****************************************************************************
* Product:  QF/C, Cortex-M3, Vanilla port, IAR compiler
* Last Updated for Version: 4.0.00
* Date of the Last Update:  Apr 07, 2008
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2008 Quantum Leaps, LLC. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Alternatively, this software may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GPL and are specifically designed for licensees interested in
* retaining the proprietary status of their code.
*
* Contact information:
* Quantum Leaps Web site:  http://www.quantum-leaps.com
* e-mail:                  info@quantum-leaps.com
*****************************************************************************/
#ifndef qf_port_h
#define qf_port_h


									
#include "qep_port.h"                                           /* QEP port */
#include "qequeue.h"                       /* "Vanilla" cooperative kernel */
                /* QF platform-independent public interface */

#define QF_MAX_ACTIVE               8

#define QF_THREAD_TYPE	 			INT8

#define QF_EQUEUE_TYPE	    		 NU_QUEUE *

                 /* The maximum number of active objects in the application */
#define QF_MAX_ACTIVE               8
                                          /* QF critical section entry/exit */
/* QF_INT_KEY_TYPE not defined: "unconditional interrupt unlocking" policy  */

 		
#define QF_INT_LOCK(dummy)       __disable_irq();    	
#define QF_INT_UNLOCK(dummy)    __enable_irq();  



#include "qf.h" 

typedef struct NucOSMemPartTag {      /* Nuc+ memory pool and block-size */
    NU_PARTITION_POOL pool;                                   /* Nuc+ pointer to  memory pool */
    QEventSize block_size;                    /* the block size of the pool */
} NucOSMemPart;

                                          /* Nuc+ event pool operations */
#define QF_EPOOL_TYPE_                 NucOSMemPart


										/* todo...dynamic NUC POOL name to allow more than one pool */
#define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) do { \
    INT8U err; \
	char * name="QFPOOL";\
    (p_).block_size = (evtSize_); \
   	  err=NU_Create_Partition_Pool ( &((p_).pool),name, poolSto_, \
	  	  (INT32U)((poolSize_)), (INT32U)(evtSize_),NU_FIFO); \
    Q_ASSERT(err == NU_SUCCESS); \
} while (0)


#ifdef CCC
#define QF_EPOOL_GET_(p_, e_) do { \
    INT8U err; \
	NU_Allocate_Partition((p_).pool,( (void *) &e_),NU_NO_SUSPEND); \
    Q_ASSERT(err == NU_SUCCESS); \
 } while (0)

#endif 

#define QF_EPOOL_EVENT_SIZE_(p_)    ((p_).block_size)


 #define QF_EPOOL_GET_(p_, e_) do { \
    INT8U err; \
	unsigned int *edat;	\
	err= NU_Allocate_Partition((&(p_).pool),( (void *) &edat),NU_NO_SUSPEND); \
	(void *) e= (void*) edat; \
	Q_ASSERT(err == NU_SUCCESS); \
 } while (0)


 


#define QF_EPOOL_PUT_(p_, e_) { \
	  INT8U err; \
	  err =  NU_Deallocate_Partition((e_)); \
	   	Q_ASSERT(err == NU_SUCCESS); \
   }

#endif                                                         /* qf_port_h */
