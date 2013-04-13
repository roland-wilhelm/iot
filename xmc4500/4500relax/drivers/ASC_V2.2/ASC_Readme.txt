ASC Release notes - Version 2.2 
-------------------------------


1. ASC
   The required files are 

   The following files are in the Src directory   
   ASC_API.H,
   ASC_CFG.H,
   ASC_IDL.H,
   ASC_IIL.H,
   ASC_IDL.c,
   ASC_IIL.c
   
   
   The following files are in the TC1130_LLD_V4.00\SYSTEM_V3.0 directory
   COMMON.H,
   COMPILER.H,
   SYS_API.H,
   SYS_CFG.H,
   SYS_IIL.c
   MAIN.H

   ASC_TEST.c -- This file is used to test the ASC LLD it is in the Test Directory


A Note on the test set up:
------------------------------------------------------------------------
  There are two test cases which can be selected by the macro TEST_CASE (which 
  can be 0 or 1).

TEST CASE 0

A). Start 'Hyper terminal' in PC (Windows, Start->programs->Accessories->communication).

a. Set the follwing parameters
   baud rate: 38400
   data bits: 8
   parity   : None
   stop bits: 1
   Flow control: hardware

b. file->properties->settings->Ascii setup
   check 'echo typed characters locally' (To see characters as you type) 

B). Connect triboard ASC0 terminal to PC 9 - pin serial connector.

C). Include the files in project space as explained in point 1. above.

D). Compile, build and download the image to target board.

E). Wecome message appears on the hyper terminal asking to enter 20 characters.
    As soon as 20 characters are typed on hyper terminal they will be dispayed
    and the program exits.

TEST CASE 1:  
A)    This test case will test ASC0 and ASC1 for 9 bit data.
	Cross connect ASC0 and ASC1 receive and transmit pins.
	Data sent from ASC0 received by ASC1 and vice versa.

B)    Following are T2LA board extension configuration. 

              ASC0                  ASC1
    RX	    802/X4.5              802/X2.5

    TX 	    802/X4.3              802/X2.3  

C)   Data received can be observed in buffer_tx2 and buffer_tx4.
