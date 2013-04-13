/*****************************************************************************
* Product: Time Bomb Example with QEP
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 21, 2011
* Ported to Keil MCB 2300 - NXP 2378 Arm/TDMI STANDALONE
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
#include "qep_port.h"                /* the port of the QEP event processor */
#include "bsp.h"                                   /* board support package */

enum BombSignals {                          /* all signals for the Bomb FSM */
    UP_SIG = Q_USER_SIG,
    DOWN_SIG,
    ARM_SIG,
    TICK_SIG
};

typedef struct TickEvtTag {
    QEvent super;                       /* derive from the QEvent structure */
    uint8_t fine_time;                           /* the fine 1/10 s counter */
} TickEvt;

typedef struct Bomb4Tag {
    QFsm super;                                         /* derive from QFsm */
    uint8_t timeout;                    /* number of seconds till explosion */
    uint8_t code;              /* currently entered code to disarm the bomb */
    uint8_t defuse;                /* secret defuse code to disarm the bomb */
} Bomb4;

void Bomb4_ctor(Bomb4 *me, uint8_t defuse);

static QState Bomb4_initial(Bomb4 *me, QEvent const *e);
static QState Bomb4_setting(Bomb4 *me, QEvent const *e);
static QState Bomb4_timing (Bomb4 *me, QEvent const *e);

/*--------------------------------------------------------------------------*/
                                        /* the initial value of the timeout */
#define INIT_TIMEOUT   10

/*..........................................................................*/
void Bomb4_ctor(Bomb4 *me, uint8_t defuse) {
    QFsm_ctor(&me->super, (QStateHandler)&Bomb4_initial);/* superclass ctor */
    me->defuse = defuse;    /* the defuse code is assigned at instantiation */
}
/*..........................................................................*/
QState Bomb4_initial(Bomb4 *me, QEvent const *e) {
    (void)e;
    me->timeout = INIT_TIMEOUT;
    return Q_TRAN(&Bomb4_setting);
}
/*..........................................................................*/
QState Bomb4_setting(Bomb4 *me, QEvent const *e) {
    switch (e->sig) {
        case UP_SIG: {
            if (me->timeout < 60) {
                ++me->timeout;
                BSP_display(me->timeout);
            }
            return Q_HANDLED();
        }
        case DOWN_SIG: {
            if (me->timeout > 1) {
                --me->timeout;
                BSP_display(me->timeout);
            }
            return Q_HANDLED();
        }
        case ARM_SIG: {
            return Q_TRAN(&Bomb4_timing);         /* transition to "timing" */
        }
    }
    return Q_IGNORED();
}
/*..........................................................................*/
QState Bomb4_timing(Bomb4 *me, QEvent const *e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            me->code = 0;                          /* clear the defuse code */
            return Q_HANDLED();
        }
        case UP_SIG: {
            me->code <<= 1;
            me->code |= 1;
            return Q_HANDLED();
        }
        case DOWN_SIG: {
            me->code <<= 1;
            return Q_HANDLED();
        }
        case ARM_SIG: {
            if (me->code == me->defuse) {
                return Q_TRAN(&Bomb4_setting);
            }
            return Q_HANDLED();
        }
        case TICK_SIG: {
            if (((TickEvt const *)e)->fine_time == 0) {
                --me->timeout;
                BSP_display(me->timeout);
                if (me->timeout == 0) {
                    BSP_boom();                         /* destroy the bomb */
                }
            }
            return Q_HANDLED();
        }
    }
    return Q_IGNORED();
}

/* Test harness ------------------------------------------------------------*/
#include <stdio.h>


#include <stdlib.h>                                          /* for _exit() */

static Bomb4 l_bomb;                                       /* time bomb FSM */

/*..........................................................................*/
int bomb4main() {

    Bomb4_ctor(&l_bomb, 0x0D);       /* the secret defuse code, 1101 binary */

    printf("Time Bomb (QEP QFsm class)\n"
           "Press 'u'   for UP   event\n"
           "Press 'd'   for DOWN event\n"
           "Press 'a'   for ARM  event\n"
           "Press <Esc> to quit.\n");

    QFsm_init((QFsm *)&l_bomb, (QEvent *)0); /* take the initial transition */

    for (;;) {                                                /* event loop */
        static TickEvt tick_evt = { TICK_SIG, 0, 0};

        delay(100000);                                         /* 100 ms delay */

        if (++tick_evt.fine_time == 10) {
            tick_evt.fine_time = 0;
        }
        printf("T(%1d)%c", tick_evt.fine_time,
                             (tick_evt.fine_time == 0) ? '\n' : ' ');

        QFsm_dispatch((QFsm *)&l_bomb, (QEvent *)&tick_evt);

        if (kbhit()) {
            static QEvent const up_evt   = { UP_SIG,   0 };
            static QEvent const down_evt = { DOWN_SIG, 0 };
            static QEvent const arm_evt  = { ARM_SIG,  0 };
            QEvent const *e = (QEvent *)0;

            switch (getchar()) {
                case 'u': {                                     /* UP event */
                    printf("\nUP  : ");
                    e = &up_evt;                   /* generate the UP event */
                    break;
                }
                case 'd': {                                   /* DOWN event */
                    printf("\nDOWN: ");
                    e = &down_evt;               /* generate the DOWN event */
                    break;
                }
                case 'a': {                                    /* ARM event */
                    printf("\nARM : ");
                    e = &arm_evt;                 /* generate the ARM event */
                    break;
                }
                case '\33': {                                  /* <Esc> key */
                    printf("\nESC : Bye! Bye!");
                    fflush(stdout);
                 
                    _sys_exit(0);
                }
            }
            if (e != (QEvent *)0) {            /* keyboard event available? */
                QFsm_dispatch((QFsm *)&l_bomb, e);    /* dispatch the event */
            }
        }
    }

 
}
