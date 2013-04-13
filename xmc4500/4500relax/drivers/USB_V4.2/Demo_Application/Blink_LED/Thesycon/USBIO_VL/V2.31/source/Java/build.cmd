@echo off
setlocal

rem *********************************************************** 
rem *
rem * JAVA_HOME points to the root directory of the Sun Java SDK.
rem * JAVA_HOME should be set in the environment on the build machine.
rem * Alternatively, it can be set in this file.
rem *
rem *********************************************************** 

rem *** uncomment the following line to set the variable JAVA_HOME
rem set JAVA_HOME=d:\Dev\j2sdk1.4.2_01


if "%JAVA_HOME%"=="" goto help


del /F ..\..\bin\debug\*.jar
del /F ..\..\bin\release\*.jar

cd .\LIBRARY\src
"%JAVA_HOME%\bin\javac" -d ..\..\..\..\bin\release .\de\thesycon\usbio\*.java .\de\thesycon\usbio\structs\*.java
"%JAVA_HOME%\bin\javac" -d ..\..\..\..\bin\debug -g .\de\thesycon\usbio\*.java .\de\thesycon\usbio\structs\*.java
"%JAVA_HOME%\bin\jar" cf ..\..\..\..\bin\debug\UsbIoJava.jar -C ..\..\..\..\bin\debug de\thesycon\usbio
"%JAVA_HOME%\bin\jar" cf ..\..\..\..\bin\release\UsbIoJava.jar -C ..\..\..\..\bin\release de\thesycon\usbio
cd ..\..

cd .\DEMOS\src
"%JAVA_HOME%\bin\javac" -classpath ..\..\..\..\bin\release -d ..\..\..\..\bin\release .\de\thesycon\usbiodemo\usbioapp\*.java
"%JAVA_HOME%\bin\jar" cfm ..\..\..\..\bin\release\UsbIoJavaApp.jar .\de\thesycon\usbiodemo\usbioapp\mainClass -C ..\..\..\..\bin\release de\thesycon\usbiodemo\usbioapp
"%JAVA_HOME%\bin\javac" -classpath ..\..\..\..\bin\debug -d ..\..\..\..\bin\release -g .\de\thesycon\usbiodemo\usbioapp\*.java
"%JAVA_HOME%\bin\jar" cfm ..\..\..\..\bin\debug\UsbIoJavaApp.jar .\de\thesycon\usbiodemo\usbioapp\mainClass -C ..\..\..\..\bin\release de\thesycon\usbiodemo\usbioapp
cd ..\..

cd .\DEMOS\src
"%JAVA_HOME%\bin\javac" -classpath ..\..\..\..\bin\release -d ..\..\..\..\bin\release .\de\thesycon\usbiodemo\mousesimple\*.java
"%JAVA_HOME%\bin\jar" cfm ..\..\..\..\bin\release\MouseSimple.jar .\de\thesycon\usbiodemo\mousesimple\mainClass -C ..\..\..\..\bin\release de\thesycon\usbiodemo\mousesimple
"%JAVA_HOME%\bin\javac" -classpath ..\..\..\..\bin\debug -d ..\..\..\..\bin\debug -g .\de\thesycon\usbiodemo\mousesimple\*.java
"%JAVA_HOME%\bin\jar" cfm ..\..\..\..\bin\debug\MouseSimple.jar .\de\thesycon\usbiodemo\mousesimple\mainClass -C ..\..\..\..\bin\release de\thesycon\usbiodemo\mousesimple
cd ..\..

goto exit


:help
echo.
echo The environment variable JAVA_HOME is not defined but
echo required by this script.
echo Please set JAVA_HOME in your environment to point to the
echo root directory of the Sun Java SDK.
echo.
pause

:exit
