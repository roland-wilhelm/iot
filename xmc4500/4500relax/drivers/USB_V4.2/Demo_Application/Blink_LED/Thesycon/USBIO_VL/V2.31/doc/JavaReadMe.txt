
Thesycon Systemsoftware & Consulting GmbH

USBIO Development Kit
=====================

USB Software Development Kit for Windows
Version 2.31, November 23, 2005

USBIOJAVA Source Code
Release Notes



Licensing Information
---------------------
The conditions of use for this source code are defined by the
USBIO License Agreement. Please refer to LICENSE.TXT or 
LICENSE.PDF (English) or to LIZENZ.TXT or LIZENZ.PDF (German)
for the complete terms of the license.



Releated Directory Contents
---------------------------
  .\doc\Java
    UsbIo Java Api Documentation

  .\source\Java
    build.cmd      -- script (batch file), used to compile
                      the usbiojava.dll, Java samples and
                      the Java class library.
                      The Java SDK Path must be set in this file, see below.

  .\source\Java\JNI_DLL
    *.cpp, *.h     -- source code of the usbiojava.dll
    USBIOJAVA.dsw  -- Visual C++ 6.0 project file.
                      can be used to build the usbiojava.dll

  .\source\Java\LIRARY
    Source code of the UsbIo Java class library

  .\source\USBIOJAVA\DEMOS
    Java Samples using the UsbIo Java class library.



Development Environment
-----------------------
Microsoft Visual C++ 6.0 Service Pack 3 is required to build the 
USBIOJAVA component usbiojava.dll. Please install this tool on 
your machine.
JAVA SDK is required to build the Java samples and UsbIo Java class library.



Build Instructions
------------------
Add the STLport library V4.6 to the project. You can download this, if necessary,
from http://www.stlport.org/download.html.
Open the workspace file usbiojava.dsw with Visual C++. Set the include
path to the STLport library. Make sure USBIOJAVA is the active project. 
Choose Build / Rebuild All from the menu bar. The workspace defines 
dependencies. Therefore usbiolib.lib will be created before the DLL is 
built.
JAVA_HOME points to the root directory of the Sun Java SDK.
JAVA_HOME should be set in the environment on the build machine.
Alternatively, it can be set in build.cmd. 


