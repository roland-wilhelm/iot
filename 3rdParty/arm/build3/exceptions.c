/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains the default exception handlers
** and exception table.
*/

#include "cortexm3.h"
#include "stack.h"

/* Linker-generated Stack Base addresses, Two Region and One Region */
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;
extern unsigned int Image$$ARM_LIB_STACKHEAP$$ZI$$Limit;

extern int __main(void);

/*
 * Exception Handlers
 */
__irq void NMIException(void)
{   while(1); }

__irq void HardFaultException(void)
{   while(1); }

__irq void MemManageException(void)
{   while(1); }

__irq void BusFaultException(void)
{   while(1); }

__irq void UsageFaultException(void)
{   while(1); }

__irq void DebugMonitor(void)
{   while(1); }

__irq void SVCHandler(void)
{   while(1); }

__irq void PendSVC(void)
{   while(1); }

/* Use handler in seperate file */
extern __irq void SysTickHandler(void);
/* void SysTickHandler(void)
{   while(1); } */

__irq void InterruptHandler(void)
{   while(1); }


/*
 * Exception Table, in seperate section so it can be correctly placed at 0x0
 */
#pragma arm section rodata="exceptions_area"

ExecFuncPtr exception_table[] = {
     /* Configure Initial Stack Pointer, using linker-generated symbols and stack.h */
#ifdef TWO_REGION
    #pragma import(__use_two_region_memory)
    (ExecFuncPtr)&Image$$ARM_LIB_STACK$$ZI$$Limit,
#endif
#ifdef ONE_REGION
    #pragma import(__use_one_region_memory)
    (ExecFuncPtr)&Image$$ARM_LIB_STACKHEAP$$ZI$$Limit,
#endif
    (ExecFuncPtr)__main, /* Initial PC, set to entry point  */
    NMIException,
    HardFaultException,
    MemManageException,
    BusFaultException,
    UsageFaultException,
    0, 0, 0, 0,             /* Reserved */
    SVCHandler,
    DebugMonitor,
    0,                      /* Reserved */
    PendSVC,
    SysTickHandler,

    /* Configurable interrupts start here...*/
    InterruptHandler,
    InterruptHandler,      /* Some dummy default interrupt handlers */
    InterruptHandler
    /*
    :
    */
};

#pragma arm section

