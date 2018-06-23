@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by KUVEMPU.HPJ. >"hlp\Kuvempu.hm"
echo. >>"hlp\Kuvempu.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Kuvempu.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Kuvempu.hm"
echo. >>"hlp\Kuvempu.hm"
echo // Prompts (IDP_*) >>"hlp\Kuvempu.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Kuvempu.hm"
echo. >>"hlp\Kuvempu.hm"
echo // Resources (IDR_*) >>"hlp\Kuvempu.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Kuvempu.hm"
echo. >>"hlp\Kuvempu.hm"
echo // Dialogs (IDD_*) >>"hlp\Kuvempu.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Kuvempu.hm"
echo. >>"hlp\Kuvempu.hm"
echo // Frame Controls (IDW_*) >>"hlp\Kuvempu.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Kuvempu.hm"
REM -- Make help for Project KUVEMPU


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Kuvempu.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Kuvempu.hlp" goto :Error
if not exist "hlp\Kuvempu.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Kuvempu.hlp" Debug
if exist Debug\nul copy "hlp\Kuvempu.cnt" Debug
if exist Release\nul copy "hlp\Kuvempu.hlp" Release
if exist Release\nul copy "hlp\Kuvempu.cnt" Release
echo.
goto :done

:Error
echo hlp\Kuvempu.hpj(1) : error: Problem encountered creating help file

:done
echo.
