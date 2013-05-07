/* Interrup locking for  Preemptive RT QK Kernel 
*  SVC Cortex Routines   
*  XMC4500 Relax Kit 
* Keil  ARM - µLink Environment */



void __svc(0)  disable_irq(int i);
void __svc(1)  enable_irq (int i);

void __SVC_0  (int i) {
	
	__disable_irq();
	
}
void __SVC_1  (int i) {
	
	 __enable_irq();
	
}

