	 /*****************************************************************************
* Product:  Uip_AO IPv6 ICMP + UDP + IPSEC"
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */

#include "bsp_at91.h"
#include "uip_ao.h"


void BSP_Init(void  );

void BSP_Delay(unsigned int  delay);
void BSP_Info_msg( char * msg);
void BSP_display(uint8_t timeout);
void BSP_LED_Toggle(int led);

void BSP_boom(void);
int BSP_kbhit(void) ;
int BSP_getch(void ) ;	  
int BSP_GET_CPSR(void);

void poll_phydev(void);
void initalise_uipv4(void);
void initalise_uipv6(void);

void process_data_from_event(NewDataEvent *e);
int  resolve_protocol_type(NewDataEvent *e);

#define IP_VERSION_NOT_SUPPORTED 0x00
#define IP_MULI_CAST_CHECK       0x01
