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

#include "nucleus.h"                      /* nuc plus APSs */

Q_DEFINE_THIS_MODULE(qf_port)

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
                                 

    
    ;                               /* start Nuc+ multitasking */
}
/*..........................................................................*/
void QF_stop(void) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    QF_INT_UNLOCK_();
    QF_onCleanup();                                     /* cleanup callback */
}

#ifdef XXXX
/*..........................................................................*/
static void task_function(void *pdata) {         /* uC/OS-II task signature */
    ((QActive *)pdata)->running = (uint8_t)1;     /* enable the thread-loop */
    while (((QActive *)pdata)->running) {
        QEvent const *e = QActive_get_((QActive *)pdata);
        QF_ACTIVE_DISPATCH_(&((QActive *)pdata)->super, e);
        QF_gc(e);    /* check if the event is garbage, and collect it if so */
    }

    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
    OSTaskDel(OS_PRIO_SELF);        /* make uC/OS-II forget about this task */
}
/*..........................................................................*/
void QActive_start(QActive *me, uint8_t prio,
                   QEvent const *qSto[], uint32_t qLen,
                   void *stkSto, uint32_t stkSize,
                   QEvent const *ie)
{
    INT8U err;
    me->eQueue = OSQCreate((void **)qSto, qLen);
    Q_ASSERT(me->eQueue != (OS_EVENT *)0);        /* uC/OS-II queue created */
    me->prio = prio;                                /* save the QF priority */
    QF_add_(me);                     /* make QF aware of this active object */
    QF_ACTIVE_INIT_(&me->super, ie);          /* execute initial transition */

    QS_FLUSH();                       /* flush the trace buffer to the host */

                        /* uC/OS task is represented by its unique priority */
    me->thread = (uint8_t)(QF_MAX_ACTIVE - me->prio); /* map to uC/OS prio. */
    err = OSTaskCreateExt(&task_function,              /* the task function */
             me,                                   /* the 'pdata' parameter */
             &(((OS_STK *)stkSto)[(stkSize / sizeof(OS_STK)) - 1]), /* ptos */
             me->thread,                          /* uC/OS-II task priority */
             me->thread,                                         /* task id */
             (OS_STK *)stkSto,                                      /* pbos */
             stkSize/sizeof(OS_STK),   /* size of the stack in OS_STK units */
             (void *)0,                                             /* pext */
             (INT16U)OS_TASK_OPT_STK_CLR);                           /* opt */
    Q_ASSERT(err == OS_NO_ERR);                    /* uC/OS-II task created */
}
/*..........................................................................*/
void QActive_stop(QActive *me) {
    INT8U err;
    me->running = (uint8_t)0;                       /* stop the thread loop */
    OSQDel(me->eQueue, OS_DEL_ALWAYS, &err);           /* cleanup the queue */
    Q_ASSERT(err == OS_NO_ERR);
}
/*..........................................................................*/
void QActive_postFIFO(QActive *me, QEvent const *e) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
    QF_INT_UNLOCK_();
    Q_ALLEGE(OSQPost((OS_EVENT *)me->eQueue, (void *)e) == OS_NO_ERR);
}
/*..........................................................................*/
void QActive_postLIFO(QActive *me, QEvent const *e) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
    QF_INT_UNLOCK_();
    Q_ALLEGE(OSQPostFront((OS_EVENT *)me->eQueue, (void *)e) == OS_NO_ERR);
}
/*..........................................................................*/
QEvent const *QActive_get_(QActive *me) {
    INT8U err;
    QEvent const *e = (QEvent *)OSQPend((OS_EVENT *)me->eQueue, 0, &err);
    Q_ASSERT(err == OS_NO_ERR);
    return e;
}
#endif
