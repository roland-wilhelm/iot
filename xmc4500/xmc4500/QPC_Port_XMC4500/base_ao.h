/**
*	Header file fot the BaseAO active object
*/

#ifndef base_ao_h
#define base_ao_h

#include "qp_port.h"                /* the port of the QEP event processor */
#include <stdlib.h>   
#include "common.h"

/* Active object class -----------------------------------------------------*/

#define MAX_DATA_LEN	103

typedef struct BaseTimEvtTag {
  QTimeEvt  super;	/* extend the QEvent class */
	uint8_t   clk_ctr;
} BaseTimEvt;

typedef struct BasePrintEvtTag {
	QEvent  super;	/* extend the QEvent class */
} BasePrintEvt;

/**
 * First attempt for the event used by the Hex_O_PAN layer to send 
 * packets to the MAC layer
 */
typedef struct BaseReceiveEvtTag {
	QEvent		super;	/* extend the QEvent class */
	uint8_t		data[MAX_DATA_LEN];	/* data to be sent */
	uint8_t 	len;								/* data length */
	uint16_t	address;						/* destination address */
} BaseReceiveEvt;

typedef struct BaseAOTag {
  QActive super;	/* extend the AQctive class */
} BaseAO;

    
/* signals used by the active object */
//enum Base_AO_Signals {                                         /* all signals for the Base Active  state machine*/
//  SER_DISPLAY_SIG = Q_USER_SIG,
//	BASE_TIME_SIG,
	/* insert other signals here... */
//	MAC_RECEIVE_SIG,
//	MAX_SIG	/* the last signal (keep always last) */
//};

/* active objects constructors */
void BaseAO_ctor(BaseAO *me);

//extern BaseTimEvt BaseTimer;  

/* opaque pointer to the active object in the application */
extern QActive* const Base;
extern BaseAO l_BaseAO;

#endif
