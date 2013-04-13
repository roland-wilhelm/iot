/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** Systick Header file.
**
** Defines Systick Registers and Masks
*/

#ifndef TIMER_H_
#define TIMER_H_

void SysTick_init(void);
__irq void SysTickHandler(void);

//SysTick Registers
#define SysTickCtrl  (volatile int*)0xE000E010
#define SysTickLoad  (volatile int*)0xE000E014
#define SysTickValue (volatile int*)0xE000E018
#define SysTickCalib (volatile int*)0xE000E01C

//SysTick Masks
#define SysTickCountFlag (1<<16)
#define SysTickClkSource (1<<2)
#define SysTickInterrupt (1<<1)
#define SysTickEnable    (1<<0)

#endif /*TIMER_H_*/

