#include "uip-nd6.h"
// #include "uip6.h"
#include "uip.h"
#include <string.h>
#include <stdio.h>
#include "neighbor_ao.h"
//#include "phy_dev.h"
#include "uip_ao.h"





/**
 * \brief Initialise Neighbor Discovery Cache
 *
 * \param QEvent ** evtStorage
 */
void
uip_nd6_init(const QEvent ** evtStorage)
{
	u8_t i;
	
  /* INITIALIZE NEIGHBOR DISCOVERY*/
  for(i = 0; i < UIP_CONF_ND6_MAX_NEIGHBORS; i ++) {
		Neighbor_AO_ctor(&(nd6_neighbor_cache[i]));
		QActive_start((QActive *)&(nd6_neighbor_cache[i]),       /* Neighbor AO */
								i+2,                      /* priority */
								evtStorage, Q_DIM(evtStorage),/*queue */
								(void *)0, 0,/*uC/OS-II stack */
								(QEvent *)0);         /* initialization event */
  }
}
