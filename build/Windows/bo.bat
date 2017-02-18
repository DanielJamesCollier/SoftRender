@echo off

::initialise generic build variables
call variables.bat

:: initialise bo.bat specific build variables 
SET boCompilerFlags=/O2 %compilerFlags%

echo:
echo:
echo ========================
echo ======Build Started=====
echo ========================
echo:
echo:
echo =========inputs=========
echo:
:: compiler inputs
echo -----------------------
echo struct CompilerInputs {
echo:

echo    files[] = {
(for %%a in (%files%) do ( 
   echo         %%~na%%~xa  
))
echo    }
echo:

echo    includePaths[] = {
(for %%a in (%incPaths%) do ( 
   echo         %%a 
))
echo    }
echo:

echo    compilerFlags[] = {
(for %%a in (%boCompilerFlags%) do ( 
   echo         %%a 
))
echo    }
echo:

echo }
echo:
:: end compiler inputs

:: linker inputs
echo -----------------------
echo struct LinkerInputs {
echo:

echo    libraryPaths[] = {
(for %%a in (%libPaths%) do ( 
   echo         %%a 
))
echo    }
echo:

echo    libraries[] = {
(for %%a in (%libs%) do ( 
   echo         %%a 
))
echo    }
echo:
    
echo }
echo:
:: end of linker inputs
echo =======================

echo:
echo =======compiler========
cl /c %files% %boCompilerFlags% %includeFlags%
echo =======================
echo:

echo ========linker=========
echo:
echo thingsToLink[] = {
(for %%a in (%libs%) do ( 
echo    %%a 
))
for %%i in (*.obj) do echo    %%i
echo }
echo:
LINK *.obj %libraryFlags% /SUBSYSTEM:%system% /out:%exeName%
echo ========================
echo:
echo:
echo ========================
echo =====Build Finished=====
echo ========================
echo:
echo: