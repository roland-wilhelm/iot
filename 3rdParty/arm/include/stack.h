/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains Stack and Heap settings
** used for scatter file and MPU config.
**/

/**
** For One Region ensure ONE_REGION is defined here,
** For Two Region ensure ONE_REGION is not defined (Default)
**/

/*---------------------------------------------------------------------------*/
// #define ONE_REGION
/*---------------------------------------------------------------------------*/


/*
 * Two Region - Stack and Heap Addresses and sizes
 */
#ifndef ONE_REGION /* If ONE_REGION Not specified default to TWO_REGION */
#define TWO_REGION

/* Two region Stack and heap settings  */
#define STACK_BASE  0x20200000      /* Stack start address */
#define STACK_SIZE  0x8000          /* length stack grows downwards */

#define HEAP_BASE   0x20100000       /* Heap starts address */
#define HEAP_SIZE   0x100000-0x8000  /* Heap Length */

#endif /* NOT ONE_REGION */

/*
 * One Region - Stack and Heap Addresses and sizes
 */
#ifdef ONE_REGION  /* One Region Stack/Heap Settings */

#define STACK_HEAP_BASE  0x20100000  /* Stack/heap base address */
#define STACK_HEAP_SIZE  0x100000    /* Stack/Heap size */

#endif

#define PROCESS_STACK_SIZE 0x4000
