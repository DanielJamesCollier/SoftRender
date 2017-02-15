@echo off

::initialise generic build variables
call variables.bat

:: initialise bo.bat specific build variables 
SET boCompilerFlags=/O2 %compilerFlags%

echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo files: %files%
echo libs:  %libs%
echo flags: %boCompilerFlags%
echo:
echo compiling...
echo:
cl %files% %boCompilerFlags% %includeAndLibLocationFlags% /SUBSYSTEM:%system%
echo:
echo ------------------------
echo:
echo: