# Microsoft Developer Studio Project File - Name="XmlUtils" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=XmlUtils - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XmlUtils.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XmlUtils.mak" CFG="XmlUtils - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XmlUtils - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XmlUtils - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XmlUtils - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../../../../build/Release"
# PROP BASE Intermediate_Dir "../../../../../build/Release/obj/XmlUtils"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../../build/Release"
# PROP Intermediate_Dir "../../../../../build/Release/obj/XmlUtils"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /X /I "../.." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "XML_STATIC" /Yu"Grom/XmlUtils/PrecompiledHeader.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /X /I "../.." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "XML_STATIC" /Yu"Grom/XmlUtils/PrecompiledHeader.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "XmlUtils - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../../../../../build/Debug"
# PROP BASE Intermediate_Dir "../../../../../build/Debug/obj/XmlUtils"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../../build/Debug"
# PROP Intermediate_Dir "../../../../../build/Debug/obj/XmlUtils"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /X /I "../.." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "XML_STATIC" /Yu"Grom/XmlUtils/PrecompiledHeader.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /X /I "../.." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "XML_STATIC" /Yu"Grom/XmlUtils/PrecompiledHeader.h" /FD /GZ /c
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

# Name "XmlUtils - Win32 Release"
# Name "XmlUtils - Win32 Debug"
# Begin Source File

SOURCE=.\PrecompiledHeader.cpp
# ADD CPP /Yc"Grom/XmlUtils/PrecompiledHeader.h"
# End Source File
# Begin Source File

SOURCE=.\PrecompiledHeader.h
# End Source File
# Begin Source File

SOURCE=.\XmlUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlUtils.h
# End Source File
# End Target
# End Project
