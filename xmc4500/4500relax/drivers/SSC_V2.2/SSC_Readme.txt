SSC Release notes - Version 2.2 
----------------------------------------

1.   Required files
   
   The following files are in the Src directory.
   SSC_API.h,
   SSC_CFG.h,
   SSC_IDL.h,
   SSC_IIL.h,
   SSC_IDL.c, 
   SSC_IIL.c, 
   
   The following files are in the CedarLLD/System directory
   COMMON.H,
   COMPILER.H,
   SYS_API.H,
   SYS_CFG.H,
   SYS_IIL.c
   MAIN.H

   SSC_TEST.C -- This file can be used to test SSC driver.It is in the Test directory.

3. SSC driver not tested to communicate across dissimilar boards.  

4. IN order to ensure compilation in the GNU toolchain, the file name extensions (".c" 
   and ".h") should be in small case only.


A Note on the test set up:
----------------------------------------------------------------------------------
Test procedure
  This test file has 3 test cases ranges from 0 to 2. To execute particular 
  test case equate TEST_CASE define value with desired value.

  Note:
    TC1130-A does not support delays and FIFOs.
    To remove the LLD support for FIFOS equate the following macros to zero value
    in SSC_IDl.h file.
	  SSC_HW_FIFO_RX
	  SSC_HW_FIFO_TX  

	To remove the LLD support for delays equate the following macro to zero value
    in SSC_IDl.h file.
      SSC_HW_DEL_SUP

  Test case 0:
    Test carried between SSC0 and SSC1 for 8 bit data.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 and SSC1 start transmission and after some delay both SSC0 and SSC1 are
    aborted.
    
    After soem delay again they start transmission.
    
    At end observe data in buffer_rx1, buffer_rx2, buffer_rx3 and buffer_rx4
    buffers and read stat1 and stat2 variables to find the status. 
  

  Test case 1:
    Test carried between SSC0 and SSC1 for 16 bit data.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 and SSC1 start transmission and after some delay both SSC0 and SSC1 are
    terminated and re-initialized.
    
    SSC0 and SSC1 start transmission after re-initialization.
    
    At end observe data in buffer_rx1, buffer_rx2, buffer_rx3 and buffer_rx4
    buffers and read stat1 and stat2 variables to find the status. 


  Test case 2:

    Test carried between SSC0 and SSC1 for 8 bit data in slave select mode.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Master and slave transmit less data compared to expected receive data.
	Master transmits user configured data(SSC_CFG_DUMMY_DATA) in 
	SSC_CFG.H file when it want to read data without transmit data. 

	Slave transmits user configured data(SSC_CFG_DUMMY_DATA) in 
	SSC_CFG.H file when either it receive data from master or read 
	data when no transmit data. This only when 'SSC_CFG_SLAVE_DUMMY_DAT'
	define value is 1 and value of 'SSC_CFG_DUMMY_DATA' not equal to -1.

    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 selects SLSO7 ans SSC1 selects SLSI line, connect SLSO7 and SLSI, by 
    using run time control API.

    SLSO7 804/45   x6.9
	SLSI  801/78   x10.11

    SSC0 and SSC1 start transmission.    
    
    At end observe data in buffer_rx1 and buffer_rx2. 
