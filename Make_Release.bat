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
md Release 2>nul
cd Release
del *.zip *.bin *.list 2>nul >nul

for /f "usebackq delims=" %%i in (`git rev-parse --short HEAD`) do set commitHash=%%i
CALL :COPYBIN "DXCHMEI_2020" "SSD1306"
CALL :COPYBIN "KSGER_GX_V2.1S" "SSD1306"
CALL :COPYBIN "XinYue_JBC_V2.1S" "SSD1306"

:: Create zips
for %%f in (*.bin) do (
  set FILE=%%~nf
  call :ZIP
)
goto :DONE

:: COPYBIN BOARDNAME SCREENTYPE
:COPYBIN
if exist "..\BOARDS\Custom\%~1\%~2.bin" (
  copy "..\BOARDS\Custom\%~1\%~2.bin"   "%~1_%commitHash%.bin"   >nul
  copy "..\BOARDS\Custom\%~1\%~2.list"  "%~1_%commitHash%.list"  >nul
  if exist "..\BOARDS\Custom\%~1\Docs\BackupTips.json" (
    python "..\backupTipTool.py" save -c "..\BOARDS\Custom\%~1\Docs\BackupTips.json" "%~1_%commitHash%.bin"
  )
)
exit /b

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

:ERROR
pause

:END
