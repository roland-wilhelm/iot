@echo off

setlocal


if "%JAVA_HOME%"=="" goto help

cd ..\..\bin\release

"%JAVA_HOME%\bin\java" -jar UsbIoJavaApp.jar

cd ..\.\..\USBIOJAVA

goto exit


:help
echo.
echo The environment variable JAVA_HOME is not defined but
echo required by this script.
echo Please set JAVA_HOME in your environment to point to the
echo root directory of the Sun Java SDK.
echo.
:exit

pause
