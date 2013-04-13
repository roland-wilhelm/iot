/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains supervisor call handler function.
**
** This example prints text to the console.
*/

#include "cortexm3.h"
#include "pseudo_intrinsics.h"
#include "svc.h"
#include <stdio.h>

extern void Display_80(const char*);

__asm void SVCHandler(void)
{
    MRS    r0, MSP
    B      __cpp(SVCHandler_main)
}

void SVCHandler_main(unsigned int * svc_args)
{
	unsigned int svc_number;

    /*
     * Stack contains:
     * r0, r1, r2, r3, r12, r14, the return address and xPSR
     * First argument (r0) is svc_args[0]
     */
	svc_number = ((char *)svc_args[6])[-2];
    switch(svc_number)
    {
        case SVC_MESSAGE:
            printf("%s\n\r", (const char *) svc_args[0]);
        break;
        case SVC_PRINT_80:
            Display_80( (const char *) svc_args[0]);
        break;

        default:
            /* Unknown SVC */
        break;
    }
}
