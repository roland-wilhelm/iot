/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains the SCS registers,
** and SCS register initialisation example.
*/

#include "scs.h"
#include "stack.h"
#include "pseudo_intrinsics.h"
/*
 * SCS Control Registers
 * in seperate section so it can be placed correctly using scatter file
 */

#pragma arm section zidata="scs_registers"

SCS_t SCS;

#pragma arm section

extern unsigned int Image$$PROCESS_STACK$$ZI$$Base;

/*
 * SCS initialisation, Setup basic regions and non execute for stack/heap
 */
void SCS_init(void)
{
    /* Configure region 1 to cover ROM (Executable, Read-only) */
    /* Start address, Region field valid, Region number */
    SCS.MPU.RegionBaseAddr = 0x00000000 | REGION_Valid | 1;
    /* Access control bits, Size, Enable 0x06030000 */
    SCS.MPU.RegionAttrSize = RO | CACHEABLE | BUFFERABLE
                            | REGION_2M | REGION_Enabled;

    /* Configure a region to cover RAM (Executable, Read-Write) */
    SCS.MPU.RegionBaseAddr = 0x20000000 | REGION_Valid | 2;
    //0x03030000
    SCS.MPU.RegionAttrSize = FULL_ACCESS | CACHEABLE | BUFFERABLE
                            | REGION_1M | REGION_Enabled;

#ifdef TWO_REGION
    /* Two Region Stack and Heap MPU settings */
    /* Configure a region to cover Stack (Not Executable, Read-Write) */
    SCS.MPU.RegionBaseAddr = STACK_BASE - STACK_SIZE | REGION_Valid | 3;
    //0x13030000
    SCS.MPU.RegionAttrSize = NOT_EXEC | FULL_ACCESS | CACHEABLE
                            | BUFFERABLE | REGION_32K | REGION_Enabled;

    /* Configure a region to cover Heap (Not Executable, Read-Write) */
    SCS.MPU.RegionBaseAddr = HEAP_BASE | REGION_Valid | 4;
    SCS.MPU.RegionAttrSize = NOT_EXEC | FULL_ACCESS | CACHEABLE | BUFFERABLE
                            | REGION_1M | REGION_Enabled;
#endif /* TWO_REGION */

#ifdef ONE_REGION
    /* One Region Stack/Heap Settings */
    /* Configure a region to cover Stack and Heap (Not Executable, Read-Write) */
    SCS.MPU.RegionBaseAddr = STACK_HEAP_BASE | REGION_Valid | 3;
    SCS.MPU.RegionAttrSize = NOT_EXEC | FULL_ACCESS | CACHEABLE | BUFFERABLE
                            | REGION_1M | REGION_Enabled;
#endif /* ONE_REGION */

    /* Configure a region to cover UART Registers (Not Executable, Read-Write) */
    SCS.MPU.RegionBaseAddr = 0x40018000 | REGION_Valid | 5;
    SCS.MPU.RegionAttrSize = NOT_EXEC | FULL_ACCESS | REGION_4K | REGION_Enabled;

    /* Enable the MPU */
    SCS.MPU.Ctrl |= 1;

    /* If we are using Cortex-M3 rev1 or later, enable hardware stack alignment */
#if defined __TARGET_CPU_CORTEX_M3 && !defined __TARGET_CPU_CORTEX_M3_REV0
    SCS.ConfigCtrl |= 0x200;
#endif

    /* Force Memory Writes before continuing */
    __DSB();
    /* Flush and refill pipline with updated permissions */
    __ISB();
}

void NVIC_enableISR(unsigned isr)
{
    /* No need to do a read-modify-write; writing a 0 to the enable register does nothing */
    SCS.NVIC.Enable[ (isr/32) ] = 1<<(isr % 32);
}

