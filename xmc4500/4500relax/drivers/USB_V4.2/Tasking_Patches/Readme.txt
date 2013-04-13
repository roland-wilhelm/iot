Information on using USB LLD with Tasking compiler.
---------------------------------------------------

The USB LLD is working fine with Tasking 2.2r2 and Tasking 2.2r3
with the MMU library off with the following workaround defined below.

MMU libraries
====================================================
Special MMU libraries have been added for derivatives that have a MMU on board. 
These libraries can be found in the subdirectory lib/tc1_mmu/ and lib/tc2_mmu. 
The MMU hardware workaround is triggered by the --mmu-present option. This option 
is automatically set when targets are specified (with the -C option) which have a MMU. 
So -Ctc1130 also sets the --mmu-present option, removing the -Ctc1130 is the only option
 to check this, but this has some side effects. These MMU libraries contain a natural 
alignment for data objects. These additional MMU libraries are required, as the MMU 
requires natural alignment. This is causing alignment issues in the low level driver code.
Concerning this MMU matter, please have a look at the errata sheet of the TC1130, silicon 
bug CPU_TC052. Here the problem is described and further information is given.
When this library is enabled, the MMU library alignment is overwriting the data alignment 
in the low level driver code due to which the transmission and reception of data is failing

[Workaround] - Select user CPU type EDE will use '-Cuserdef113' to identify a user CPU type. 
Its corresponding register file only contains the default CPU registers. The assembler still
requires the register definitions for TC1130 which can be explicitly added to the 'include
this file before source' EDITBOX of the assembler 'preprocessing' PAGE. Attached you will 
find an option file (nommu.opt) in the patches which can be imported into project to make this happen.
This option file will also setup your 'script file' PAGE such that it uses external LSL file 
nommu.lsland just a definition addition in cstart.asm will make it work.
Even if the MMU library is enabled with this option file code would still work fine(Hence MMU library and USB can 
still be integrated in case if required), and hence this workaround does not have any side effects, 
only thing is we need use the .opt file, .lsl and cstart.asm as in this folder
with the package for Tasking 2.2r2 onwards. 
User need to make sure to include the correct def files, as well as the correct LSL file for the linker. 
These files are all automatically included by the -Ctc1130 option (you can verify this by using the -v option for
 the control program, this allows you to see which options are passed to the tools).

Copy the sources required for compilation(for ex: into C:\usb_tasking\source) where usb_tasking is the project workspace
,also copy the nommu.opt, nommu.lst and cstart.asm 
into the project workspace. Note that cstart.asm as in the Tasking_Patches folder needs to be read only.
Goto Project->Load options and load c:\usb_tasking\project\nommu.optwhich has been copied from patches folder.
Click on project setting -> Linker -> Script File -> and set path to nommu.lsl,
 as given as example: c:\usb_tasking\project\nommu.lsl
Compile the code and download it onto hardware. Plug and play the USB Cable
Run the testbench to check the results.
