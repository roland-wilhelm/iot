/*****************************************************************************
* Product:  QF/C, port to ARM7 TDMI Keil MCB2300 
* Last Updated for Version: 11.06.11
* Date of the Last Update:  11.06.11
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

#include "nucleus.h"                      /* NUC Plus APIs */

Q_DEFINE_THIS_MODULE(qf_port)

/* Local objects -----------------------------------------------------------*/
extern NU_MEMORY_POOL  USB_SRAM_MEM;

#define NUM_NUC_TASK		2				
#define STACK	 0x400
NU_TASK qf_task[NUM_NUC_TASK];
			

int get_task_idx (QActive *me  );



static  char * qf_task_name[]= {
		"QTASK1",
		"QTASK2",
		"QTASK3",  
		"QTASK4",
		"(char *) 0" };
 static  char * qf_queue_name[]= {
 		"QFQUE1",
		"QFQUE2",
		"QFQUE3",
		"QFQUE4" };


NU_QUEUE qf_queue[NUM_NUC_TASK];

struct qt_task_adm {
	
	NU_TASK *nu_qf;
	char ** qf_name;
	QActive *  qf_act_obj;
	};

struct qt_task_adm  qttask[4] = {
	
		{ &qf_task[0], &qf_task_name[0], ( QActive *)0},
		{ &qf_task[1], &qf_task_name[1],( QActive *) 0},
		{ &qf_task[2], &qf_task_name[2], ( QActive *)0},
		{ &qf_task[3], &qf_task_name[3],( QActive *) 0},
			  }	;


static int qf_tsk_nr= 0;;  

/*..........................................................................*/
char const Q_ROM * Q_ROM_VAR QF_getPortVersion(void) {
    static const char Q_ROM Q_ROM_VAR version[] =  "4.1.01";
    return version;
}
/*..........................................................................*/
void QF_init(void) {
   ;                                        /* initialize RTOS  */
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


/*..........................................................................*/
static void task_function(UNSIGNED argc, void *argv) {         /* uC/OS-II task signature */
  
	 int idx;
	 QActive * pdata = (QActive*)argv;
    ((QActive *)pdata)->running = (uint8_t)1;     /* enable the thread-loop */
 	 idx = 0;

    while (((QActive *)pdata)->running) { 
		
		QEvent const *e = QActive_get_((QActive *)pdata);
        QF_ACTIVE_DISPATCH_(&((QActive *)pdata)->super, e);
        QF_gc(e);    /* check if the event is garbage, and collect it if so */
 

    }
	idx = get_task_idx(pdata);
    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
    NU_Delete_Task(qttask[idx].nu_qf);	 /* make Nucleus forget about this task */

}



/*..........................................................................*/
void QActive_start(QActive *me, uint8_t prio,
                   QEvent const *qSto[], uint32_t qLen,
                   void *stkSto, uint32_t stkSize,
                   QEvent const *ie)
{
    INT8U err;
	void		  * my_pointer;

    me->eQueue=&qf_queue[qf_tsk_nr];
	qttask[qf_tsk_nr].qf_act_obj = me;


	err =  NU_Create_Queue(me->eQueue, *(&qf_queue_name[qf_tsk_nr]), (void **)qSto,qLen,NU_FIXED_SIZE, 1, NU_FIFO);
    Q_ASSERT(me->eQueue != ( NU_QUEUE *)0);         /* RTOS queue created */
    me->prio = prio;                                /* save the QF priority */
    QF_add_(me);                                    /* make QF aware of this active object */
    QF_ACTIVE_INIT_(&me->super, ie);                 /* execute initial transition */
    QS_FLUSH();                                      /* flush the trace buffer to the host */

               								          /* RTOS task is represented by its unique priority */
    me->thread = (uint8_t)(QF_MAX_ACTIVE - me->prio); /* map to RTOS prio. */

	err = NU_Allocate_Memory(&USB_SRAM_MEM, &my_pointer, STACK, NU_NO_SUSPEND);
    Q_ASSERT(err == NU_SUCCESS );    

	err = NU_Create_Task(qttask[qf_tsk_nr].nu_qf ,*(&qf_task_name[qf_tsk_nr]),&task_function, 1, me, 
	my_pointer,  STACK , QF_MAX_ACTIVE - me->prio  , 0,NU_PREEMPT,NU_START); 	  // NUC 254   me->thread

    Q_ASSERT(err == NU_SUCCESS );                    /* RTOS task created */
	qf_tsk_nr++;
}


/*..........................................................................*/
void QActive_stop(QActive *me) {
    INT8U err;
    me->running = (uint8_t)0;                       /* stop the thread loop */
	err= NU_Delete_Queue(me->eQueue);				  /* cleanup the queue */
    Q_ASSERT(err == NU_SUCCESS);
}
/*..........................................................................*/


void QActive_postFIFO(QActive *me, QEvent const *e) {
   
   
	unsigned err;
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
   

 	err=  NU_Send_To_Queue(me->eQueue, ( void *) &e, 1, NU_NO_SUSPEND);
	Q_ASSERT(err == NU_SUCCESS);
   QF_INT_UNLOCK_();
}


/*..........................................................................*/
void QActive_postLIFO(QActive *me, QEvent const *e) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
   
	
	NU_Send_To_Front_Of_Queue(me->eQueue,  (void *) &e, 1, NU_NO_SUSPEND);

	 QF_INT_UNLOCK_();
//    Q_ALLEGE(OSQPostFront((OS_EVENT *)me->eQueue, (void *)e) == OS_NO_ERR);
}
/*..........................................................................*/
QEvent const *QActive_get_(QActive *me) {
     INT8U err;
	 UNSIGNED actual_size;

    QEvent * e;  
	actual_size = 0x0;
	err= NU_Receive_From_Queue( me->eQueue, (VOID *) &e, 1 ,&actual_size, NU_SUSPEND);
    Q_ASSERT(err == NU_SUCCESS);

    return e;
}



   /* this function is used to determine the index of the NU TCB based on the AO Pointer */
int get_task_idx (QActive *me  )	 {

	int i;
    for ( i=0; i< NUM_NUC_TASK; i++) {

   	if ( qttask[i].qf_act_obj	 == me) 
		return(i);
   }
  		return (-1); 
}

	



