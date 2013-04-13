/*****************************************************************************
* Product:  QK/C Keil Compile 
* Last Updated for Version: 4.0.01
* Date of the Last Update:  Sept 2012
*
*                   
* 
*****************************************************************************/
#ifndef qk_port_h
#define qk_port_h

                                             /* QK interrupt entry and exit */
#define QK_ISR_ENTRY() do { \
   __disable_irq(); \
    ++QK_intNest_; \
    QF_QS_ISR_ENTRY(QK_intNest_, QK_currPrio_); \
    __enable_irq(); \
} while (0)

#define QK_ISR_EXIT()  do { \
    __disable_irq(); \
    QF_QS_ISR_EXIT(QK_intNest_, QK_currPrio_); \
    --QK_intNest_; \
       __enable_interrupt(); \
} while (0)

#include "qk.h"                 /* QK platform-independent public interface */

#endif                                                         /* qk_port_h */
