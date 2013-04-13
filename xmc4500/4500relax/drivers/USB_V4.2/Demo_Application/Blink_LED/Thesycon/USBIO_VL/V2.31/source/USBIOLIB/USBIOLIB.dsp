# Microsoft Developer Studio Project File - Name="UsbioLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=UsbioLib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UsbioLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UsbioLib.mak" CFG="UsbioLib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UsbioLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "UsbioLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UsbioLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin\release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "UsbioLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "UsbioLib - Win32 Release"
# Name "UsbioLib - Win32 Debug"
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\inc\usbio_i.h
# End Source File
# Begin Source File

SOURCE=..\inc\usbioerr.h
# End Source File
# Begin Source File

SOURCE=..\inc\usbiover.h_
# End Source File
# Begin Source File

SOURCE=..\inc\usbspec.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PnPNotificator.cpp
# End Source File
# Begin Source File

SOURCE=.\PnPNotificator.h
# End Source File
# Begin Source File

SOURCE=.\SetupApiDll.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupApiDll.h
# End Source File
# Begin Source File

SOURCE=.\UsbIo.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIo.h
# End Source File
# Begin Source File

SOURCE=.\UsbIoBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIoBuf.h
# End Source File
# Begin Source File

SOURCE=.\UsbIoPipe.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIoPipe.h
# End Source File
# Begin Source File

SOURCE=.\UsbIoReader.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIoReader.h
# End Source File
# Begin Source File

SOURCE=.\UsbIoThread.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIoThread.h
# End Source File
# Begin Source File

SOURCE=.\UsbIoWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbIoWriter.h
# End Source File
# End Target
# End Project
