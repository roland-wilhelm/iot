/*****************************************************************************
* Port of FreeRtos to Keil MBC2300 NXP 2379
* Nov 11, 2011
* Dr. Ron Barker - Univ. Munich Event Driver Systems
*****************************************************************************/
#include "qf_pkg.h"
#include "qassert.h"

#include "freertos.h"                      /* FreeRtos APSs */
#include "task.h"


Q_DEFINE_THIS_MODULE(qf_port)

extern int ulCriticalNesting;


char * task_name[]= {
	{	"QFTASK1" },
	{	"QFTASK2" },
	{	"QFTASK3" },
	{	"QFTASK4" },
	{	"QFTAS5" },
	{	"QFTASK6" } };

/* Local objects -----------------------------------------------------------*/

static int task_idx;
/*..........................................................................*/
char const Q_ROM * Q_ROM_VAR QF_getPortVersion(void) {
    static const char Q_ROM Q_ROM_VAR version[] =  "4.1.01";
    return version;
}
/*..........................................................................*/
void QF_init(void) {
 
 	task_idx = 0;
   ;                                        /* initialize RTOS */
}
/*..........................................................................*/
void QF_run(void) {
                                 
   vTaskStartScheduler();
    
                                  /* start multitasking */
}
/*..........................................................................*/
void QF_stop(void) {
    QF_INT_LOCK_KEY_
    QF_INT_LOCK_();
    QF_INT_UNLOCK_();
    QF_onCleanup();                                     /* cleanup callback */
}


/*..........................................................................*/
static void task_function(void *pdata) {         /*  task signature */
    ((QActive *)pdata)->running = (uint8_t)1;     /* enable the thread-loop */

    while (((QActive *)pdata)->running) {
          QEvent const *e = QActive_get_((QActive *)pdata);
          QF_ACTIVE_DISPATCH_(&((QActive *)pdata)->super, e);
          QF_gc(e);    /* check if the event is garbage, and collect it if so */

    }

    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
   
}


/*..........................................................................*/
void QActive_start(QActive *me, uint8_t prio,
                   QEvent const *qSto[], uint32_t qLen,
                   void *stkSto, uint32_t stkSize,
                   QEvent const *ie)
{
   
	int err;

	me->eQueue = xQueueCreate( qLen , sizeof(QEvent*) );

    Q_ASSERT(me->eQueue != (void *)0);        /*  queue created */
    me->prio = prio;                                /* save the QF priority */
    QF_add_(me);                     /* make QF aware of this active object */
    QF_ACTIVE_INIT_(&me->super, ie);          /* execute initial transition */

    QS_FLUSH();                       /* flush the trace buffer to the host */
 //  	vTaskDelay( 0x32 );
                        /* task is represented by its unique priority */
//    me->thread = (uint8_t)(QF_MAX_ACTIVE - me->prio); /* map to OSprio. */	   

    err= xTaskCreate( task_function, task_name[task_idx] , 0x100 * 3, me,tskIDLE_PRIORITY+me->prio, &me->thread);

    Q_ASSERT(me->thread !=  (xTaskHandle) NULL );
	 task_idx++;
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
#ifdef YYY
    QF_INT_LOCK_();
    if (e->dynamic_ != (uint8_t)0) {
        ++((QEvent *)e)->dynamic_;
    }
    QF_INT_UNLOCK_();
#endif
 //  	 err = xQueueSendToBack(me->eQueue, &e, (portTickType)0);
#define XXX
#ifdef XXX
	if (ulCriticalNesting == (unsigned portLONG)0) { /* task level? */
		     QF_INT_LOCK_();
  			  if (e->dynamic_ != (uint8_t)0) {
      		  ++((QEvent *)e)->dynamic_;
 			   }
  			  QF_INT_UNLOCK_();
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

