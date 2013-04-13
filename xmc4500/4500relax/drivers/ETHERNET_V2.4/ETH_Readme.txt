Ethernet Release notes Version 2.4
---------------------------------------------------------------

1. Ethernet
   The required files are 

   The following files are in the Src directory
   ETH_IDL.c,
   ETH_IIL.c, 
   ETH_IIL_DMUR.c, 
   ETH_IIL_DMUT.c,
   ETH_IIL_RB.c, 
   ETH_IIL_TB.c,    
   ETH_IIL_MAC.c,
   ETH_API.h,
   ETH_CFG.h,
   ETH_IDL.h,
   ETH_IIL.h,  
   cache.h


   The following files are in the TC1130_LLD_V4.00\SYSTEM_V3.0 directory
   COMMON.H,
   COMPILER.H,
   SYS_API.H,
   SYS_CFG.H,
   SYS_IIL.c
   MAIN.H

   ETH_main.c -- This file is used to test the Ethernet driver. It is in the Test directory. 


2. All the source files of the Ethernet LLD should be placed in the same directory of the
   project space.

3. Target files have for cache and non cache to support GNU 3.3.7.3. 
These target files can be found in TC1130_LLD_V4.00\ETHERNET_V2.4\Target_files_Ethernet directory


----------------------------------------------------------------------------------------
Limitations:

1. Only GNU would be supported for data cache problem: Data Cache Limitation on TC1130 - B
 step has been fixed with TC1130 BB Step board: The transmit and receive data buffers should not
 be allocated in the cache-able segments( Segment - 0xC0000000 and 0x80000000).

The usage of the Cache memory is not recommended for the device with BA-step.
In order to use the Cache memory with BB Step, DMI12 workaround should not be used !!
==============================================================================================================
Note: The problem with CACHE lies on TC1130 BA-step. 
With GNU compiler, it is STILL possible to use CACHE memory on TC1130 BA-step, as long as DMI12 workaround is switched ON.
(But this is not recommended)
With Tasking compiler, it is not possible to use CACHE memory on TC1130 BA-step, because there is no workaround available.
With TC1130 BB-step, ALL compiler can be used.  Especially for GNU compiler, workaround DMI12 should be disabled, 
so that the performance is not reduced by the workaround.
===============================================================================================================     

The flag ETH_CFG_USE_CACHE in eth_cfg.h need to be defined for data cache workaround.

A Note on the test setup:
----------------------------------------------------------------------------------------
a). Connect a crossed Cat 5 cable from the triboard to the PC.
   OR if a crossed Cat 5 cable is unavailable
   Connect the triboard to the host PC using an ethernet hub. If a hub is used make sure 
   to set the speed, duplex and autonegotiation settings in the ETH_CFG.H file.
   Note that a layer 3 switch should not be used as we want to capture packets at
   the "MAC layer".
   When selecting 10Mbps speed setting, make sure that the autonegotiation is enabled in 
   the ETH_CFG.H.
   
b). Start a packet sniffer program on the host computer to monitor the packets.
    If there is no access to a packet sniffer program the Ethernet LLD can be configured in
    the MAC or PHY loopback mode (by using the macros in the ETH_CFG.H file).

c). The ETH_MAIN.C file shows how to transmit an ARP packet, the user can change the 
    contents of the ARP packet so suit his requirement.

d). Compile the Ethernet LLD by making a project space and including the files as mentioned
    in Step 1. above.Download the program on the triboard and start it.
e). The program transmits 2000 ARP packets
f). The program then waits in an infinite loop.
g). For successful test : the variable "tx_frames_dropped" should be zero (indicates that
                                                          there are no transmit failures)
                       & the variable "rx_packets" should be equal to the number of packets 
                                                               received.
                       & the variable "tx_frames" should be equal to the number of
                                                              frames transmitted.
h). In case of loopback tests, the variable "rx_packets" should be equal to the number of
   frames transmitted.
    