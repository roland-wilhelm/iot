/*****************************************************************************
* Product:  QF/C, port to 80x86, uC/OS-II v2.86, Open Watcom compiler
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Nov 03, 2009
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2009 Quantum Leaps, LLC. All rights reserved.
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
#include "qf_pkg.h"
#include "qassert.h"

#include "freertos.h"                      /* nuc plus APSs */
#include "task.h"


Q_DEFINE_THIS_MODULE(qf_port)

extern int ulCriticalNesting;


/* Local objects -----------------------------------------------------------*/


/*..........................................................................*/
char const Q_ROM * Q_ROM_VAR QF_getPortVersion(void) {
    static const char Q_ROM Q_ROM_VAR version[] =  "4.1.01";
    return version;
}
/*..........................................................................*/
void QF_init(void) {
   ;                                        /* initialize uC/OS-II */
}
/*..........................................................................*/
void QF_run(void) {
                                 
   vTaskStartScheduler();
    
                                  /* start Nuc+ multitasking */
}
/*..........................................................................*/
void QF_stop(void) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    QF_INT_UNLOCK_();
    QF_onCleanup();                                     /* cleanup callback */
}


/*..........................................................................*/
static void task_function(void *pdata) {         /* uC/OS-II task signature */
    ((QActive *)pdata)->running = (uint8_t)1;     /* enable the thread-loop */

    while (((QActive *)pdata)->running) {
          QEvent const *e = QActive_get_((QActive *)pdata);
          QF_ACTIVE_DISPATCH_(&((QActive *)pdata)->super, e);
          QF_gc(e);    /* check if the event is garbage, and collect it if so */

    }

    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
   // OSTaskDel(OS_PRIO_SELF);        /* make uC/OS-II forget about this task */
}


/*..........................................................................*/
void QActive_start(QActive *me, uint8_t prio,
                   QEvent const *qSto[], uint32_t qLen,
                   void *stkSto, uint32_t stkSize,
                   QEvent const *ie)
{
   
	 int err;
//    me->eQueue = OSQCreate((void **)qSto, qLen);
	me->eQueue = xQueueCreate( qLen , sizeof(QEvent*) );

    Q_ASSERT(me->eQueue != (void *)0);        /* uC/OS-II queue created */
    me->prio = prio;                                /* save the QF priority */
    QF_add_(me);                     /* make QF aware of this active object */
    QF_ACTIVE_INIT_(&me->super, ie);          /* execute initial transition */

    QS_FLUSH();                       /* flush the trace buffer to the host */

                        /* uC/OS task is represented by its unique priority */
//    me->thread = (uint8_t)(QF_MAX_ACTIVE - me->prio); /* map to uC/OS prio. */	   

    err= xTaskCreate( task_function, "QFTASK" , 1024, me,tskIDLE_PRIORITY+2, &me->thread);

    Q_ASSERT(me->thread !=  (xTaskHandle) NULL );

}


/*..........................................................................*/
void QActive_stop(QActive *me) {

    me->running = (uint8_t)0;                       /* stop the thread loop */
	vQueueDelete(me->eQueue); /* cleanup the queue */
              /* cleanup the queue */
//    Q_ASSERT(err == OS_NO_ERR);
}
/*..........................................................................*/	  

void QActive_postFIFO(QActive *me, QEvent const *e) {
	portBASE_TYPE err;
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
    QF_INT_UNLOCK_();
 //  	 err = xQueueSendToBack(me->eQueue, &e, (portTickType)0);
#define XXX
#ifdef XXX
	if (ulCriticalNesting == (unsigned portLONG)0) { /* task level? */
			 err = xQueueSendToBack(me->eQueue, &e, (portTickType)0);
	}
	else { /* must be ISR level */
		portBASE_TYPE xHigherPriorityTaskWoken;
		err = xQueueSendToBackFromISR(me->eQueue, &e,&xHigherPriorityTaskWoken);
	}

#endif
   Q_ASSERT(err == pdPASS);
}


/*..........................................................................*/
void QActive_postLIFO(QActive *me, QEvent const *e) {
    portBASE_TYPE err;
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
   	 }
    QF_INT_UNLOCK_();

//  	err = xQueueSendToFront(me->eQueue, &e, (portTickType)0);
#define XXX
#ifdef XXX
	if (ulCriticalNesting == (unsigned portLONG)0) { /* task level? */
			err = xQueueSendToFront(me->eQueue, &e, (portTickType)0);
	}
	else  { /* must be ISR level */
		portBASE_TYPE xHigherPriorityTaskWoken;
		err = xQueueSendToFrontFromISR(me->eQueue, &e,&xHigherPriorityTaskWoken);
	}

#endif
	Q_ASSERT(err == pdPASS);

 }



/*..........................................................................*/
QEvent const *QActive_get_(QActive *me) {
  
	 QEvent const *e;
	 Q_ALLEGE(xQueueReceive(me->eQueue, &e, portMAX_DELAY) == pdPASS);
    
    return e;
}

