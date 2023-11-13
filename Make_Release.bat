@echo off

:: Adjust this to 7-Zip executable

set ZIP=	"C:\Program Files\7-Zip\7z.exe"

:: Check that 7-Zip exists        

if not exist %ZIP% (
  echo 7-Zip not installed or wrong path set!
  echo You might need to modify "ZIP" variable in this bat file.
  GOTO :ERROR
)


:: Copy files

mkdir Release & cd Release
del *.zip *.bin 2>nul >nul

for /f "usebackq delims=" %%i in (`git rev-parse --short HEAD`) do set commitHash=%%i
copy "..\BOARDS\DXCHMEI\SSD1306.bin"	"DXCHMEI_2020_%commitHash%.bin" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES
copy "..\BOARDS\XinYue\SSD1306.bin"	"XinYue_2.1S_%commitHash%.bin" >nul			&& IF %ERRORLEVEL% NEQ 0 GOTO :NO_FILES

:: Create zips

for %%f in (*.bin) do (
  if not exist %%~f 		GOTO :NO_FILES
  echo %%~f
  %ZIP% a -tzip %%~nf.zip %%~f -y >nul

  IF %ERRORLEVEL% NEQ 0		echo Unknown 7-ZIP Error!	&& GOTO :ERROR
)

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

