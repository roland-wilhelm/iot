/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains UART Control Registers and simple
** UART I/O functions in ISSM
*/

#include "uart.h"

/*
 * UART Control Registers
 * in seperate section so it can be placed correctly using scatter file
 */

#pragma arm section zidata="uart0_registers"

UART_t uart0;

#pragma arm section


/* UART Init Function */
void UART_init(void)
{
    //Enable UART for Transmit and Receive
    uart0.Ctrl = UARTCR_ENABLE | UARTCR_TXENABLE | UARTCR_RXENABLE;

    uart0.LCR_H = UARTLCR_H_FIFOENABLE;

/*  UARTREGS[UARTIMSK] = UARTRIS_RTINTR | UARTRIS_RXINTR;
  Don't need to enable interrupts in this example */
}

/* UART Read Function */
char uart_getchar_polled(void)
{
    while (uart0.Flags & UARTFR_RXFIFOEMPTY) {
         // waiting to receive data!
    }
    return uart0.Data;
}

/* UART Write Function */
void uart_putc_polled(char c)
{
    while (uart0.Flags & UARTFR_TXFIFOFULL) {
      //  waiting to send data!
    }
    uart0.Data = c;
}

