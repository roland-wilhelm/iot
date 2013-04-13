#ifndef UART_H_
#define UART_H_

/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
**
** UART Header file.
**
** Defines UART Registers and Masks
*/


/*
 * UART Masks
 */
enum UARTFR_BITS {
  UARTFR_TXFIFOEMPTY = 1<<7,
  UARTFR_RXFIFOFULL = 1<<6,
  UARTFR_TXFIFOFULL = 1<<5,
  UARTFR_RXFIFOEMPTY = 1<<4,
  UARTFR_TXFIFONOTEMPTY = 1<<3
};
enum UARTLCR_H_BITS {
  UARTLCR_H_FIFOENABLE = 1<<4 // Select 16-deep rather than 1-deep fifo.
};

enum UARTCR_BITS {
  UARTCR_ENABLE = 1<<0,
  UARTCR_SIRENABLE = 1<<1, // Not implemented in ISSM.
  UARTCR_LOOPBACK = 1<<7,  // Not implemented in ISSM.
  UARTCR_TXENABLE = 1<<8,
  UARTCR_RXENABLE = 1<<9
};
enum UARTRIS_BITS {
  UARTRIS_RTINTR = 1<<6,   // Receive Timeout interrupt.
  UARTRIS_TXFIFOEMPTY = 1<<5,
  UARTRIS_RXINTR = 1<<4    // Fifo reaches tidemark.
};

enum UARTDMACR_BITS {
  UARTDMACR_TX = 1<<1,
  UARTDMACR_RX = 1<<0
};


/*
 * UART Registers
 */
typedef struct
{
    volatile unsigned int Data;
    volatile unsigned int RSR_ECR;
    volatile unsigned int zReserved008_014[4];
    volatile unsigned int Flags;
    volatile unsigned int zReserved01c;
    volatile unsigned int IPLR;
    volatile unsigned int IBRD;
    volatile unsigned int FBRD;
    volatile unsigned int LCR_H;
    volatile unsigned int Ctrl;
    volatile unsigned int IFLS;
    volatile unsigned int MSC;
    volatile unsigned int RIS;
    volatile unsigned int MIS;
    volatile unsigned int IRQClear;
    volatile unsigned int DMACR;
    volatile unsigned int zReserved080_FDC[(0xFE0-0x80)/4];
    volatile unsigned int PeriphID[4];
    volatile unsigned int CellID[4];
} UART_t;


extern UART_t uart0;

extern void UART_init(void);
extern char uart_getchar_polled(void);
extern void uart_putc_polled(char);

#endif /*UART_H_*/

