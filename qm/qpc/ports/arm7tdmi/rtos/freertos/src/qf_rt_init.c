/*****************************************************************************
* Port of FreeRtos to Keil MBC2300 NXP 2379
* Nov 11, 2011
* Dr. Ron Barker - Univ. Munich Event Driver Systems
*****************************************************************************/
#include "qep_port.h"
#include "qf_port.h"


void qf_rt_init( void ) {





}


  
/*..........................................................................*/
void QF_onIdle(void) {              /* NOTE: entered with interrupts LOCKED */
    QF_INT_UNLOCK(dummy);                /* must at least unlock interrupts */
}


/*..........................................................................*/
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
    printf("Assertion failed in %s, line %d", file, line);
    QF_stop();
}

/*..........................................................................*/
void QF_onCleanup(void) {
    
 	
    _sys_exit(0);                                                /* exit to DOS */
}



