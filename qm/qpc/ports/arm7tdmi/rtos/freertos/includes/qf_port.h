/*****************************************************************************
* Port of FreeRtos to Keil MBC2300 NXP 2379
* Nov 11, 2011
* Dr. Ron Barker - Univ. Munich Event Driver Systems
*****************************************************************************/

#ifndef qf_port_h
#define qf_port_h


									
#include "qep_port.h"                                           /* QEP port */
#include "qequeue.h"  
#include "qmpool.h"                       /* "Vanilla" cooperative kernel */
                /* QF platform-independent public interface */

#include "freertos.h"
#include "task.h"
#include "queue.h"


//#define QF_INT_KEY_TYPE


#define QF_THREAD_TYPE	 			xTaskHandle

#define QF_EQUEUE_TYPE	    		xQueueHandle *


#define portISR_ENTRY() do { \
 ++ulInterruptNesting; \
 ++ulCriticalNesting; \
} while (0)

                 /* The maximum number of active objects in the application */

#define QF_MAX_ACTIVE               8

#include "qf.h" 
                                         /* QF critical section entry/exit */
/* QF_INT_KEY_TYPE not defined: "unconditional interrupt unlocking" policy  */

 		
#define QF_INT_LOCK(dummy)    vPortEnterCritical (); //_disable_irq();    	
#define QF_INT_UNLOCK(dummy)  vPortExitCritical();   //__enable_irq();  





                                          /* Nuc+ event pool operations */
#define QF_EPOOL_TYPE_                QMPool


					                                         /* native QF event pool operations */
#define QF_EPOOL_TYPE_              QMPool
#define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) \
    QMPool_init(&(p_), poolSto_, poolSize_, evtSize_)
#define QF_EPOOL_EVENT_SIZE_(p_)    ((p_).blockSize)
#define QF_EPOOL_GET_(p_, e_)       ((e_) = (QEvent *)QMPool_get(&(p_)))
#define QF_EPOOL_PUT_(p_, e_)       (QMPool_put(&(p_), e_))



#endif                                                         /* qf_port_h */
