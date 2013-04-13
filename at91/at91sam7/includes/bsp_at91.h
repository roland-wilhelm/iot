

//------------------------------------------------------------------------------
//       Atmel AT91 Lib   Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <pio/pio_it.h>
#include <pit/pit.h>
#include <aic/aic.h>
#include <tc/tc.h>
#include <utility/led.h>
#include <utility/trace.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  

void _sys_exit(int rtc); 



void BSP_AT91_Init_Debug( char * msg );
void BSP_AT91_Wait(unsigned long delay);
void BSP_AT91_ConfigurePit(void);
void BSP_AT91_LED_Toggle(int led);
void BSP_AT91_ConfigureLeds(void) ;
void BSP_AT91_ConfigureTc(void);


void BSP_SET_CPSR(int val);
int BSP_GET_CPSR(void);

//------------------------------------------------------------------------------
//       Quantum Framework / Real Time Disptacher Headers
//------------------------------------------------------------------------------



