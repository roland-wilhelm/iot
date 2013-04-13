
__asm void SVC_Handler (void) {
      PRESERVE8
	  TST     LR,#4                   ; Called from Handler Mode?
	  MRSNE   R12,PSP                 ; Yes, use PSP
    MOVEQ   R12,SP                  ; No, use MSP
	  B  SVCHandler_main
	
		IMPORT SVCHandler_main 
}


#define SVC_00 0x00
#define SVC_01 0x01


void SVCHandler_main(unsigned int * svc_args)

{    unsigned int svc_number;    /*    * Stack contains:    * r0, r1, r2, r3, r12, r14, the return address and xPSR    * First argument (r0) is svc_args[0]    */   
	   svc_number = ((char *)svc_args[6])[-2];    
		switch(svc_number)    {       
		case SVC_00:            /* Handle SVC 00 */           
		break;       
		case SVC_01:            /* Handle SVC 01 */           
		break;        
		default:            /* Unknown SVC */           
		break;    }
	}

	

	void __svc(SVC_00) svc_zero(const char *string);
	void __svc(SVC_01) svc_one(const char *string);
	int call_system_func(void){    
		svc_zero("String to pass to SVC handler zero");    
		svc_one("String to pass to a different OS function");
		
		
}
