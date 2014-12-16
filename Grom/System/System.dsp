# Microsoft Developer Studio Project File - Name="System" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=System - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "System.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "System.mak" CFG="System - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "System - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "System - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "System - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../../../../build/Release"
# PROP BASE Intermediate_Dir "../../../../../build/Release/obj/System"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../../build/Release"
# PROP Intermediate_Dir "../../../../../build/Release/obj/System"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /X /I "../.." /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"Grom/System/PrecompiledHeader.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /X /I "../.." /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"Grom/System/PrecompiledHeader.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "System - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../../../../../build/Debug"
# PROP BASE Intermediate_Dir "../../../../../build/Debug/obj/System"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../../build/Debug"
# PROP Intermediate_Dir "../../../../../build/Debug/obj/System"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /X /I "../.." /D "WIN32" /D "_DEBUG" /D "_MBCS" /Yu"Grom/System/PrecompiledHeader.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /X /I "../.." /D "WIN32" /D "_DEBUG" /D "_MBCS" /Yu"Grom/System/PrecompiledHeader.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "System - Win32 Release"
# Name "System - Win32 Debug"
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\ErrorMessages.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorMessages.h
# End Source File
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\Exception.h
# End Source File
# Begin Source File

SOURCE=.\FileUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\FileUtils.h
# End Source File
# Begin Source File

SOURCE=.\FundamentalTypes.h
# End Source File
# Begin Source File

SOURCE=.\Monitor.cpp
# End Source File
# Begin Source File

SOURCE=.\Monitor.h
# End Source File
# Begin Source File

SOURCE=.\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\Object.h
# End Source File
# Begin Source File

SOURCE=.\Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Array.h
# End Source File
# Begin Source File

SOURCE=.\PrecompiledHeader.cpp
# ADD CPP /Yc"Grom/System/PrecompiledHeader.h"
# End Source File
# Begin Source File

SOURCE=.\PrecompiledHeader.h
# End Source File
# Begin Source File

SOURCE=.\PropertyTree.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyTree.h
# End Source File
# Begin Source File

SOURCE=.\Rtti.cpp
# End Source File
# Begin Source File

SOURCE=.\Rtti.h
# End Source File
# Begin Source File

SOURCE=.\StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\StringUtils.h
# End Source File
# Begin Source File

SOURCE=.\Synchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\Synchronization.h
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueArray.h
# End Source File
# End Target
# End Project
