echo off

set PORT=COM2

rem echo ====== for testing ======
rem echo ProgramFiles(x86)  %ProgramFiles(x86)%
rem echo ProgramFiles       %ProgramFiles%
rem echo LocalAppData       %LocalAppData%
rem echo CurrentDirectory   %CD%
rem echo UserProfile    %UserProfile%
rem echo UserName       %UserName%
rem echo AppData        %AppData%
rem echo CD             %CD%
rem echo SELF           %0
rem echo ====== for testing ======

rem https://stackoverflow.com/questions/17279114/split-path-and-take-last-folder-name-in-batch-script
set MYDIR=%CD%\
if "%MYDIR:~-1%" == "\" set "MYDIR1=%MYDIR:~0,-1%"
for %%f in ("%MYDIR1%") do set "FOLDER=%%~nxf"
echo PROJ   %FOLDER%

set TOOL=\bin\avrdude.exe
set CONF=\etc\avrdude.conf
set ROOT=%ProgramFiles(x86)%\Arduino\hardware\tools\avr

if not exist "%ROOT%%TOOL%" (
    echo not found TOOL "%ROOT%"
    set ROOT=%LocalAppData%\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17
    echo change ROOT to "%ROOT%"
)
echo ROOT   %ROOT%

set HEX=%CD%\dist\default\production\%FOLDER%.production.hex
if not exist "%HEX%" goto not_found_hex
echo HEX    %HEX%

echo PORT   %PORT%

set CMD="%ROOT%%TOOL%" -C "%ROOT%%CONF%" -patmega328p -carduino -P%PORT% -b115200 -D -U flash:w:"%HEX%":i
echo CMD    %CMD%
%CMD%
if %ERRORLEVEL% neq 0 goto exec_err_avrdude
goto :OK



:not_found_exe
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo  ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo not found avrdude.exe
echo --
echo Please install avrdude.exe with Arduino IDE.
goto :EOF

:not_found_hex
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo  ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo not found hex file
echo --
echo Please re-build with **NOT DEBUG** option.
goto :EOF

:exec_err_avrdude
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo  ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo execute error of avrdude.exe
echo error level:   %ERRORLEVEL%
echo error message: "can't open %PORT%".
echo --
echo Please check yourself!!
echo   1. COM port number
echo   2. USB cable connection
echo     :
echo   etc...
goto :EOF

:OK
echo OK done.
goto :EOF

:EOF
pause
