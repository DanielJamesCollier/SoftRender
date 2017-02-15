@echo off

::initialise generic build variables
call variables.bat

:: initialise bo.bat specific build variables 
SET bCompilerFlags=%compilerFlags%

echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo files: %files%
echo libs:  %libs%
echo flags: %bCompilerFlags%
echo:
echo compiling...
echo:
cl %files% %bCompilerFlags% %includeAndLibLocationFlags% /SUBSYSTEM:%system%
echo:
echo ------------------------
echo:
echo:
echo: