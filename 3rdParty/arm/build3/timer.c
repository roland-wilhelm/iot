/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains the Systick Initialisation function and
** Systick exception handler.
*/

#include "cortexm3.h"
#include "scs.h"
#include "timer.h"
#include <stdio.h>

#define MAGIC_VALUE 299999

void SysTick_init(void)
{
#ifndef ISSM /* Configure SysTick for real Hardware */
    
    /*for Real Hardware, 1ms */
    int onems = ((SCS.SysTick.Calibration) & 0x00ffffff);
    int reload = 999;  // Supposed to be once a second (999+1 ms)

    /* If the calibration value is non 0 then we can use it as a more accurate value for 1ms */
    if(onems != 0)
    {
        reload = ((onems+1) * 1000)-1;
    }

    *SysTickLoad = reload;
#else  /* Configure SysTick for ISSM */
    *SysTickLoad = MAGIC_VALUE; /* Found to be more realistic on ISSM */
#endif  /* ISSM */

#ifdef SYSTICK_INTERRUPT
    *SysTickCtrl = SysTickEnable | SysTickInterrupt; /* Start, with interrupts enabled */
#else
    *SysTickCtrl = SysTickEnable; /* Start, without interrupts enabled */
#endif  /* SYSTICK_INTERRUPT */
}

__irq void SysTickHandler(void)
{
    printf("----- SysTick Interrupt -----");
}

