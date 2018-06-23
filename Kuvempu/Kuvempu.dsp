# Microsoft Developer Studio Project File - Name="Kuvempu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Kuvempu - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kuvempu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kuvempu.mak" CFG="Kuvempu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kuvempu - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Kuvempu - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kuvempu - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\output"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\output\*.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Kuvempu - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\KuvempuEXE"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\KuvempuEXE\*.lib shell32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Kuvempu - Win32 Release"
# Name "Kuvempu - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlreadyExist.cpp
# End Source File
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CauveryHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\HemavathiHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\Kuvempu.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\Kuvempu.hpj

!IF  "$(CFG)" == "Kuvempu - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help file...
OutDir=.\..\output
InputPath=.\hlp\Kuvempu.hpj
InputName=Kuvempu

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Kuvempu - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help file...
OutDir=.\..\KuvempuEXE
InputPath=.\hlp\Kuvempu.hpj
InputName=Kuvempu

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Kuvempu.rc
# End Source File
# Begin Source File

SOURCE=.\KuvempuDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetravathiHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\SharavathiHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\sinstance.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\TungaHelp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlreadyExist.h
# End Source File
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BmpButton.h
# End Source File
# Begin Source File

SOURCE=.\CauveryHelp.h
# End Source File
# Begin Source File

SOURCE=.\HemavathiHelp.h
# End Source File
# Begin Source File

SOURCE=.\Kuvempu.h
# End Source File
# Begin Source File

SOURCE=.\KuvempuDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetravathiHelp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "Kuvempu - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=Kuvempu
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Kuvempu - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=Kuvempu
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SharavathiHelp.h
# End Source File
# Begin Source File

SOURCE=.\sinstance.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\TungaHelp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BITMAPS\BACKGROUND.bmp
# End Source File
# Begin Source File

SOURCE=.\Khajana\BACKGROUND.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BACKGROUND2.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BACKGROUND3.bmp
# End Source File
# Begin Source File

SOURCE=.\Khajana\BACKGROUND_1.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button_1_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button_1_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button_1_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CAUVERY_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CAUVERY_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CAUVERY_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CLOSE_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CLOSE_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CLOSE_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CONVERTER_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CONVERTER_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_CONVERTER_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_HEMAVATHI_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_HEMAVATHI_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_HEMAVATHI_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_NETRAVATHI_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_NETRAVATHI_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_NETRAVATHI_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\button_s.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SHARAVATHI_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SHARAVATHI_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SHARAVATHI_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SYSTEMTRAY_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SYSTEMTRAY_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_SYSTEMTRAY_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_TUNGA_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_TUNGA_NORM.bmp
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\BUTTON_TUNGA_UP.bmp
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\Cauvery.bmp"
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\CauveryHlp.bmp"
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\Heamavathi.bmp"
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\HemavathiHelp.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icon00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\KBDHLP.bmp
# End Source File
# Begin Source File

SOURCE=.\Khajana\Khajana.bmp
# End Source File
# Begin Source File

SOURCE=".\BITMAPS\Kilimanegalu copy.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Kuvempu.ico
# End Source File
# Begin Source File

SOURCE=.\res\Kuvempu.rc2
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\Nethravathi.bmp"
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\NetravathiHelp.bmp"
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\Running.bmp
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\Sharavathi.bmp"
# End Source File
# Begin Source File

SOURCE=".\KeyBd Hlp\SharavathiHelp.bmp"
# End Source File
# Begin Source File

SOURCE=.\BITMAPS\Tunga.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxDlg.rtf

!IF  "$(CFG)" == "Kuvempu - Win32 Release"

!ELSEIF  "$(CFG)" == "Kuvempu - Win32 Debug"

# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Kuvempu.cnt

!IF  "$(CFG)" == "Kuvempu - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\output
InputPath=.\hlp\Kuvempu.cnt
InputName=Kuvempu

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "Kuvempu - Win32 Debug"

# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
