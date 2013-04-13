/*****************************************************************************
* Product: QHsmTst Example, DOS, Large model
* Last Updated for Version: 4.0.00
*  Date of the Last Update:  Oct 21, 2011
* Ported to Keil MCB 2300 - NXP 2378 Arm/TDMI STANDALONE
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

#include "bsp.h"

#include "qep_port.h"


#include "qassert.h"
#include "qhsmtst.h"


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Q_DEFINE_THIS_FILE

/* local objects -----------------------------------------------------------*/
static FILE *l_outFile = (FILE *)0;
static void dispatch(QSignal sig);

/*..........................................................................*/
int qhsmtst_main(int argc, char *argv[]) {
    QHsmTst_ctor();                       /* instantiate the QHsmTst object */

    if (argc > 1) {                                  /* file name provided? */
        l_outFile = fopen(argv[1], "w");
    }

    if (l_outFile == (FILE *)0) {                   /* interactive version? */
        l_outFile = stdout;            /* use the stdout as the output file */

        printf("QHsmTst example, built on %s at %s,\n"
               "QEP: %s.\nPress ESC to quit...\n",
               __DATE__, __TIME__, QEP_getVersion());

        QHsm_init(the_hsm, (QEvent *)0);      /* the top-most initial tran. */

        for (;;) {                                            /* event loop */
            QEvent e;
            int c;

//            printf("\n>;");
//			   delay(1000);
            c = getchar();    /* get a character from the console with echo */
//            printf(": ");
	  	 
            if ('a' <= c && c <= 'i') {                        /* in range? */
                e.sig = (QSignal)(c - 'a' + A_SIG);
            }
            else if ('A' <= c && c <= 'I') {                   /* in range? */
                e.sig = (QSignal)(c - 'A' + A_SIG);
            }
            else if (c == '\33') {                          /* the ESC key? */
                e.sig = TERMINATE_SIG;    /* terminate the interactive test */
            }
            else {
                e.sig = IGNORE_SIG;
            }

            QHsm_dispatch(the_hsm, &e);               /* dispatch the event */
        }
    }
    else {                                                 /* batch version */
        printf("QHsmTst example, built on %s at %s, QEP %s\n"
               "output saved to %s\n",
               __DATE__, __TIME__, QEP_getVersion(),
               argv[1]);

        fprintf(l_outFile, "QHsmTst example, QEP %s\n",
                QEP_getVersion());

        QHsm_init(the_hsm, (QEvent *)0);      /* the top-most initial tran. */

                                       /* testing of dynamic transitions... */
        dispatch(A_SIG);
        dispatch(B_SIG);
        dispatch(D_SIG);
        dispatch(E_SIG);
        dispatch(I_SIG);
        dispatch(F_SIG);
        dispatch(I_SIG);
        dispatch(I_SIG);
        dispatch(F_SIG);
        dispatch(A_SIG);
        dispatch(B_SIG);
        dispatch(D_SIG);
        dispatch(D_SIG);
        dispatch(E_SIG);
        dispatch(G_SIG);
        dispatch(H_SIG);
        dispatch(H_SIG);
        dispatch(C_SIG);
        dispatch(G_SIG);
        dispatch(C_SIG);
        dispatch(C_SIG);

        fclose(l_outFile);
    }

    return 0;
}
/*..........................................................................*/

/*..........................................................................*/
static void dispatch(QSignal sig) {
    QEvent e;
    Q_REQUIRE((A_SIG <= sig) && (sig <= I_SIG));
    e.sig = sig;
    fprintf(l_outFile, "\n%c:", 'A' + sig - A_SIG);
    QHsm_dispatch(the_hsm, &e);                       /* dispatch the event */
}

