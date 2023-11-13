@echo off

:: Adjust this to 7-Zip executable

set ZIP="C:\Program Files\7-Zip\7z.exe"

:: Check that 7-Zip exists        

if not exist %ZIP% (
  echo 7-Zip not installed or wrong path set!
  echo You might need to modify "ZIP" variable in this bat file.
  GOTO :ERROR
)


:: Copy files

mkdir Release & cd Release
del *.zip *.bin *.list 2>nul >nul

for /f "usebackq delims=" %%i in (`git rev-parse --short HEAD`) do set commitHash=%%i
copy "..\BOARDS\Custom\DXCHMEI_2020\SSD1306.bin"		"DXCHMEI_2020_%commitHash%.bin" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\Custom\DXCHMEI_2020\SSD1306.list"		"DXCHMEI_2020_%commitHash%.list" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\Custom\KSGER_GX_V2.1S\SSD1306.bin"		"KSGER_GX_V2.1S_%commitHash%.bin" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\Custom\KSGER_GX_V2.1S\SSD1306.list"		"KSGER_GX_V2.1S_%commitHash%.list" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\Custom\XinYue_JBC_V2.1S\SSD1306.bin"	"XinYue_JBC_V2.1S_%commitHash%.bin" >nul		&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\Custom\XinYue_JBC_V2.1S\SSD1306.list"	"XinYue_JBC_V2.1S_%commitHash%.list" >nul		&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES

:: Create zips
for %%f in (*.bin) do (
  set FILE=%%~nf
  call :ZIP
)
goto :DONE

:ZIP
echo %FILE%
%ZIP% a -mx=9 -tzip %FILE%.zip %FILE%.* -y >nul
IF %ERRORLEVEL% NEQ 0 echo Unknown 7-ZIP Error! && GOTO :ERROR
exit /B


:DONE
echo.
echo Done!
TIMEOUT 3 >NUL
GOTO :END


:NO_FILES
echo Missing bin files!
echo First run Building_script.bat and select "Compile all"

:ERROR
pause

:END


