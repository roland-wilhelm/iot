Information on using GNU compiler for USB LLD
---------------------------------------------

GNU_Target_Files Directory:
   This directory contain the linker files that is needed to build the USB LLD.
   There are different target files that are needed to build the code that target different memory.
     To build the code at external Flash               ==> Use: ext_flash_cache_target.ld
     To build the code at external sdram with cache    ==> Use: ext_ram_cache_target.ld
     To build the code at external sdram without cache ==> Use: ext_ram_target.ld
     To build the code at internal sram                ==> Use: int_ram_target.ld

Flash Directory:
      This directory contains the files to be included when you want to build the code to be
      burned into external flash in the TC1130 Triboard.
      The files are: crt0.S and EBUSettings.S
      Please see the readme.txt in this directory for the usage.

