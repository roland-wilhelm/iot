/**
*	Header file fot the common stuff
*/

#ifndef common_h
#define common_h

/* signals used by all active objects */
enum Base_AO_Signals {                                         /* all signals for the Base Active  state machine*/
  SER_DISPLAY_SIG = Q_USER_SIG,
	BASE_TIME_SIG,
	HEX_TO_MAC,
	ERROR_SIG,
	NEW_IP_PACKET,
	SET_NS_ADDRESS_SIG,
	SET_NORMAL_ADDRESS_SIG,
	COMPRESS_SIG,
	NO_COMPRESSION_SIG,
	SEND_PACKET_SIG,
	START_FRAGMENTATION_SIG,
	SET_SIZE_SIG,
	SET_TAG_SIG,
	SEND_SIG,
	SEND_CONSECUTIVE_FRAME_SIG,
	SEND_FIRST_FRAME_SIG,
	SEND_SOLO_FRAME_SIG,
	CONTINUE_SIG,
	SENT_PACKET_SIG,
	/* insert  */
	MAX_PUB_SIG,	/* the last published signal */
	/* insert all other signals here... */
	MAX_SIG	/* the last signal (keep always last) */
};

#endif

