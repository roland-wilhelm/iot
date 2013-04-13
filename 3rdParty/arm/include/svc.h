/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** SuperVisor Call Header file
*/

#ifndef SVC_H_
#define SVC_H_

#define SVC_MESSAGE  0x10
#define SVC_PRINT_80 0x20

void SVCHandler(void);
void SVCHandler_main(unsigned int * svc_args);

void __svc(SVC_MESSAGE) svc_message(const char *string);
void __svc(SVC_PRINT_80) svc_print_80(const char *string);

#endif /*SVC_H_*/

