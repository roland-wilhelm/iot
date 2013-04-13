
Thesycon Systemsoftware & Consulting GmbH

USBIO Development Kit Vendor-Specific Light Version
===================================================

USB Software Development Kit for Windows
Version 2.31, November 23, 2005

Release Notes



Contents
--------
  - Supported Operating Systems
  - USB 2.0 Support
  - Limitations of Vendor-Specific Light Version
  - Licensing Information
  - Directory Contents
  - Installation Instructions
  - Build Environment
  - Known Problems
  - Receiving Product News
  - Adobe Acrobat Reader
  - Contacting Thesycon



Supported Operating Systems
---------------------------
The USBIO device driver supports the following operating systems:

    Windows 98 SE (second edition)
    Windows ME (millennium edition)
    Windows 2000 SP4 (with service pack 4)
    Windows XP SP2 (with service pack 2)
    Windows XP x64 Edition on Intel EM64T architecture
    Windows XP x64 Edition on AMD x86-64 architecture
    Windows XP Embedded
    Windows Server 2003
    Windows Server 2003 x64 Edition

The driver will also work on older service pack releases. However, testing
at Thesycon has been performed on the service pack versions listed above.



USB 2.0 Support
---------------
The USBIO device driver supports USB 2.0 on Windows 2000 and Windows XP.
Refer to the USBIO Reference Manual (usbioman.pdf), section 2.4 for
detailed information on USB 2.0 support. The manual also provides
instructions for installing USB 2.0 host controller drivers.
For advanced information on USB 2.0 support in Windows XP SP1 see also
the following Microsoft Knowledge Base article:
http://support.microsoft.com/default.aspx?scid=KB;EN-US;Q329632&



Limitations of Vendor-Specific Light Version
--------------------------------------------
The Vendor-Specific Light Version of the USBIO Development Kit supports
several products from different vendors. The specific restrictions that
apply for each product are described below.
Please note that the Vendor-Specific Light Version cannot be used with any other
products than those listed below.


* USB08 Evaluation Kit by MCT Elektronikladen
---------------------------------------------
The following limitations apply:

1. The Vendor ID of your device has to match with the Vendor ID 0x0C70 of
   MCT Elektronikladen. You can contact MCT Elektronikladen to receive 
   a unique product ID.
   Possible error codes when this restriction is violated:
   USBIO_ERR_VID_RESTRICTION

2. Only one Interrupt IN endpoint and one Interrupt OUT endpoint is
   supported. If your device has more endpoints or other endpoint
   types, device configuration (SET_CONFIGURATION) will fail.
   Possible error codes when this restriction is violated:
   USBIO_ERR_PIPE_RESTRICTION
   USBIO_ERR_BULK_RESTRICTION
   USBIO_ERR_ISO_RESTRICTION

3. The maximum FIFO size of an endpoint is limited to 8 bytes.
   Possible error codes when this restriction is violated:
   USBIO_ERR_PIPE_SIZE_RESTRICTION

4. The maximum size of the Data stage for a Class or Vendor Request
   is limited to 8 bytes.
   Possible error codes when this restriction is violated:
   USBIO_ERR_EP0_RESTRICTION


* TMS320C5509 series DSP's by Texas Instruments
-----------------------------------------------
The following limitations apply:

1. The Vendor ID of your device has to match with the Vendor ID 0x0451
   of Texas Instruments.
   Possible error codes when this restriction is violated:
   USBIO_ERR_VID_RESTRICTION

2. The Light Version stops working after 12 hours. After this interval has 
   expired you will have to reboot the machine in order to use the driver.
   Disconnecting and reconnecting the USB device does not re-enable
   the driver.


* C165UTAH Evaluation Kit by Infineon Technologies AG
-----------------------------------------------------
The following limitations apply:

1. The Vendor ID of your device has to match with the Vendor ID 0x058B
   of Infineon Technologies AG.
   Possible error codes when this restriction is violated:
   USBIO_ERR_VID_RESTRICTION

2. The Light Version stops working after 12 hours. After this interval has
   expired you will have to reboot the machine in order to use the driver.
   Disconnecting and reconnecting the USB device does not re-enable
   the driver.


* M16C Evaluation Kit by Mitsubishi
-----------------------------------
The following limitations apply:

1. The Vendor ID of your device has to match with the Vendor ID 0x0452
   of Mitsubishi Electric.
   Possible error codes when this restriction is violated:
   USBIO_ERR_VID_RESTRICTION

2. The Light Version stops working after 12 hours. After this interval has
   expired you will have to reboot the machine in order to use the driver.
   Disconnecting and reconnecting the USB device does not re-enable
   the driver.


A full version of the USBIO Development Kit, without 
the restrictions described above, can be ordered directly from 
Thesycon Systemsoftware & Consulting GmbH. 
See Contacting Thesycon below.

Please refer to usbioman.pdf for information on installation
and usage of the USBIO device driver.

For most current information on USBIO, visit http://www.thesycon.de 
or e-mail USBIO@thesycon.de.



Licensing Information
---------------------
For detailed information on licensing conditions see
LICENSE.TXT or LICENSE.PDF (English),
LIZENZ.TXT or LIZENZ.PDF (German).



Directory Contents
------------------
  .\
    version.txt   -- USBIO Development Kit version information

  .\doc
    This directory contains the USBIO documentation and the license agreement.
		Additional the seperate readme file for Java (JavaReadMe.txt) is located here.

  .\usbio
    This directory contains the USBIO driver executables and .inf files.


  .\apps
    Contains USBIO demo applications.

  .\tools
    Contains tools needed to customize the driver.

  .\source
    usbioapp.dsw  -- Visual C++ 6.0 workspace file that includes the USBIOAPP 
                     and USBIOLIB projects. Open this file to build usbioapp.exe.

  .\source\USBIOAPP
    source code of the USBIO Test and Demo Application usbioapp.exe

  .\source\USBIOLIB
    source code of the USBIO Class Library

  .\source\inc
    usbio_i.h     -- include file, defines the USBIO application
                     programming interface (API)
    usberr.h      -- include file, defines USBIO error codes

    usbspec.h     -- include file, contains general definitions
                     taken from the USB specification
    usbiover.h    -- include file, defines USBIO version and 
                     copyright information

  .\source\VendSpec
    Vendor specific demo applications.
    This directory is optional and may not be present in your USBIO package.

  .\source\samples\ReadPipe
    C source code of a simple console application that demonstrates
    how to read from an IN endpoint using the USBIO API

  .\source\samples\PnPDemo
    C++ source code of a sample application that demonstrates
    how to scan for USBIO devices and to handle PnP add/remove events.

  .\source\samples\ReaderCpp
    C++ source code of a simple example application that demonstrates
    how to read from an IN endpoint using the USBIO Class Library USBIOLIB

  .\source\samples\WriterCpp
    C++ source code of a simple example application that demonstrates
    how to write to an OUT endpoint using the USBIO Class Library USBIOLIB

  .\source\Delphi
    contains unit definitions allowing you to access the 
    USBIO programming interface from Delphi

  .\source\Java
    for mor information about this directory please have a look 
		at the JavaReadMe.txt in the directory doc

  .\COMobj
    usbiocom.dll  -- The USBIOCOM component implementation.
                     This file is registered on your machine during 
                     installation of the USBIO Development Kit.

  .\COMobj\debug
    usbiocom.dll  -- A debug build of the USBIOCOM component implementation.
                     This is provided to allow advanced debugging and 
                     analysis. See usbiocom.pdf for more information on 
                     how to use this file.

  .\COMobj\inc
    usbiocom.idl  -- USBIO COM interface definition

  .\COMobj\samples\VisualBasicSimple
    A very simple example program that demonstrates how to use the 
    USBIO COM object with Visual Basic.

  .\COMobj\samples\VisualBasicDemo
    A more complex example program that demonstrates how to use the 
    USBIO COM object with Visual Basic.

  .\COMobj\samples\DelphiSimple
    A very simple example program that demonstrates how to use the 
    USBIO COM object with Delphi.

  .\COMobj\samples\DelphiDemo
    A more complex example program that demonstrates how to use the 
    USBIO COM object with Delphi.

  .\COMobj\samples\CSharpMouseSample
    A very simple C# example program that demonstrates how to use the 
    USBIO COM object with C#.

  .\_uninst
    Contains information required to uninstall the kit.
    Please do not modify this directory.



Installation Instructions
-------------------------
On Windows 2000 and XP, administrator privileges are required to install 
the USBIO device driver. Once the USBIO driver is installed standard user
privileges are sufficient to load the driver and to use the programming 
interface provided by the driver.

There are two ways to install the USBIO driver for a particular
USB device: using the USBIO Installation Wizard or by preparing a 
setup information (INF) file manually.

The USBIO Installation Wizard is recommended because it is the quickest and 
easiest way to install the driver. The wizard performs the driver 
installation automatically, taking the user through a step-by-step procedure.
Run the USBIO Installation Wizard from the Start menu and follow the 
instructions shown on screen.

Please refer to the USBIO Reference Manual (usbioman.pdf), Chapter 7, for 
detailed instructions and for a description of the steps the wizard
performs.

In order to manually install the USBIO driver using Device Manager, a proper 
INF file needs to be prepared. The INF file included is intended as 
a starting point. You have to edit it for use with your device.
Please refer to USBIO Reference Manual (usbioman.pdf), Chapter 7, for 
detailed instructions on how to do so.

Note that the USBIO Installation Wizard will generate a device-specific
INF file that can be used for future manual installations.



Build Environment
-----------------
Microsoft Visual C++ 6.0 SP3 (or better) is required to build the 
USBIO Class Library and the USBIO Demo Application. The appropriate 
project files (.dsp) and workspace files (.dsw) are included.

Applications that use the USBIO Class Library need to be linked
with USBIOLIB.LIB and SETUPAPI.LIB.
USBIOLIB.LIB must be built from the sources in the USBIOLIB subdirectory.
Open usbiolib.dsp with VC++ and choose "Rebuild All".
If your application uses USBIOLIB you are recommended to insert usbiolib.dsp
into your VC++ workspace.
SETUPAPI.LIB is required because USBIOLIB uses Win32 SetupDiXxx functions.



Known Problems
--------------
Refer to the file doc\Problems.txt for a list of known problems
and recommended work-arounds.



Receiving Product News
----------------------
In order to receive up-to-date news on USBIO products, 
you may subscribe to the Thesycon newsletter mailing list.
Check out http://www.thesycon.de/eng/newsletter.htm for more information.



Adobe Acrobat Reader
--------------------
Adobe Acrobat Reader is required to read the electronic product
documentation which is available in Acrobat (.pdf) format.
Acrobat Reader is free software and can be downloaded from the Internet
at the following location: http://www.adobe.com/acrobat/



Contacting Thesycon
-------------------
If you have purchase or upgrade needs or technical questions
please contact Thesycon.

Thesycon Systemsoftware & Consulting GmbH
Werner-von-Siemens-Str. 2
98693 Ilmenau
Germany

Phone: +49 3677 8462 0
Fax:   +49 3677 8462 18

email: USBIO@thesycon.de
http://www.thesycon.de
