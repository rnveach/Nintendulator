# Microsoft Developer Studio Project File - Name="Nintendulator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Nintendulator - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Nintendulator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Nintendulator.mak" CFG="Nintendulator - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Nintendulator - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Nintendulator - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Nintendulator - Win32 Release ANSI" (based on "Win32 (x86) Application")
!MESSAGE "Nintendulator - Win32 Debug ANSI" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Nintendulator", PBAAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Nintendulator - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Unicode"
# PROP BASE Intermediate_Dir "Release Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\unicode\bin"
# PROP Intermediate_Dir "..\unicode\obj_emu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /Gr /W3 /GX /O2 /D "UNICODE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FAcs /Fa"..\unicode\asm\" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dinput.lib ddraw.lib winmm.lib vfw32.lib zlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib dsound.lib shlwapi.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Nintendulator - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Unicode"
# PROP BASE Intermediate_Dir "Debug Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\unicode\bin"
# PROP Intermediate_Dir "..\unicode\obj_emud"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /Gr /W3 /Gm /GX /ZI /Od /D "UNICODE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAcs /Fa"..\unicode\asm\" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dinput.lib ddraw.lib winmm.lib vfw32.lib zlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib dsound.lib shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"..\unicode\bin\Nintendulator-d.exe" /pdbtype:sept /libpath:"..\src\zlib\"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "Nintendulator - Win32 Release ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release ANSI"
# PROP BASE Intermediate_Dir "Release ANSI"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\ansi\bin"
# PROP Intermediate_Dir "..\ansi\obj_emu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /Gr /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FAcs /Fa"..\ansi\asm\" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dinput.lib ddraw.lib winmm.lib vfw32.lib zlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib dsound.lib shlwapi.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\src\zlib\"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Nintendulator - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug ANSI"
# PROP BASE Intermediate_Dir "Debug ANSI"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\ansi\bin"
# PROP Intermediate_Dir "..\ansi\obj_emud"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /Gr /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAcs /Fa"..\ansi\asm\" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dinput.lib ddraw.lib winmm.lib vfw32.lib zlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib dsound.lib shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"..\ansi\bin\Nintendulator-d.exe" /pdbtype:sept /libpath:"..\src\zlib\"

!ENDIF 

# Begin Target

# Name "Nintendulator - Win32 Release Unicode"
# Name "Nintendulator - Win32 Debug Unicode"
# Name "Nintendulator - Win32 Release ANSI"
# Name "Nintendulator - Win32 Debug ANSI"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Std Controllers"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\c_s_arkpad.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_fourscore.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_powpad.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_snescont.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_snesmouse.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_stdcont.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_unconnected.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_vszapper.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_s_zapper.cpp
# End Source File
# End Group
# Begin Group "Exp Controllers"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\c_e_arkpad.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_fam4play.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_famtrain.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_fbkey.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_suborkey.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_tablet.cpp
# End Source File
# Begin Source File

SOURCE=..\src\c_e_unconnected.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\APU.cpp
# End Source File
# Begin Source File

SOURCE=..\src\AVI.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BreakpointList.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Controllers.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CPU.cpp
# End Source File
# Begin Source File

SOURCE=..\src\DBInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Debugger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Genie.cpp
# End Source File
# Begin Source File

SOURCE=..\src\GFX.cpp
# End Source File
# Begin Source File

SOURCE=..\src\HeaderEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\MapperInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Movie.cpp
# End Source File
# Begin Source File

SOURCE=..\src\NES.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Nintendulator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PPU.cpp
# End Source File
# Begin Source File

SOURCE=..\src\States.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\APU.h
# End Source File
# Begin Source File

SOURCE=..\src\AVI.h
# End Source File
# Begin Source File

SOURCE=..\src\BreakpointList.h
# End Source File
# Begin Source File

SOURCE=..\src\Controllers.h
# End Source File
# Begin Source File

SOURCE=..\src\CPU.h
# End Source File
# Begin Source File

SOURCE=..\src\DBInterface.h
# End Source File
# Begin Source File

SOURCE=..\src\Debugger.h
# End Source File
# Begin Source File

SOURCE=..\src\Genie.h
# End Source File
# Begin Source File

SOURCE=..\src\GFX.h
# End Source File
# Begin Source File

SOURCE=..\src\HeaderEdit.h
# End Source File
# Begin Source File

SOURCE=..\src\MapperInterface.h
# End Source File
# Begin Source File

SOURCE=..\src\Movie.h
# End Source File
# Begin Source File

SOURCE=..\src\NES.h
# End Source File
# Begin Source File

SOURCE=..\src\Nintendulator.h
# End Source File
# Begin Source File

SOURCE=..\src\PPU.h
# End Source File
# Begin Source File

SOURCE=..\src\States.h
# End Source File
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\src\Nintendulator.ico
# End Source File
# Begin Source File

SOURCE=..\src\Nintendulator.rc
# End Source File
# Begin Source File

SOURCE=..\src\resource.h
# End Source File
# Begin Source File

SOURCE=..\src\small.ico
# End Source File
# End Group
# Begin Group "Zip"

# PROP Default_Filter "*"
# Begin Source File

SOURCE=..\src\unzip.c
# End Source File
# Begin Source File

SOURCE=..\src\unzip.h
# End Source File
# End Group
# End Target
# End Project
