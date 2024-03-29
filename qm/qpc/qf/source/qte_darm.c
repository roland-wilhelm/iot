/*****************************************************************************
* Product: QF/C
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
#include "qf_pkg.h"

/**
* \file
* \ingroup qf
* \brief QTimeEvt_disarm() implementation.
*/

/*..........................................................................*/
/* NOTE: disarm a timer (no harm in disarming an already disarmed timer)    */
uint8_t QTimeEvt_disarm(QTimeEvt *me) {
    uint8_t wasArmed;
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (me->prev != (QTimeEvt *)0) {   /* is the time event actually armed? */
        wasArmed = (uint8_t)1;
        if (me == QF_timeEvtListHead_) {
            QF_timeEvtListHead_ = me->next;
        }
        else {
            if (me->next != (QTimeEvt *)0) {   /* not the last in the list? */
                me->next->prev = me->prev;
            }
            me->prev->next = me->next;
        }
        me->prev = (QTimeEvt *)0;        /* mark the time event as disarmed */

        QS_BEGIN_NOLOCK_(QS_QF_TIMEEVT_DISARM, QS_teObj_, me)
            QS_TIME_();                                        /* timestamp */
            QS_OBJ_(me);                          /* this time event object */
            QS_OBJ_(me->act);                          /* the active object */
            QS_TEC_(me->ctr);                        /* the number of ticks */
            QS_TEC_(me->interval);                          /* the interval */
        QS_END_NOLOCK_()
    }
    else {                                  /* the time event was not armed */
        wasArmed = (uint8_t)0;

        QS_BEGIN_NOLOCK_(QS_QF_TIMEEVT_DISARM_ATTEMPT, QS_teObj_, me)
            QS_TIME_();                                        /* timestamp */
            QS_OBJ_(me);                          /* this time event object */
            QS_OBJ_(me->act);                          /* the active object */
        QS_END_NOLOCK_()
    }
    QF_INT_UNLOCK_();
    return wasArmed;
}
