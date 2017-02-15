:: generic build variables
:: {
    :: generic compiler flags - see b.bat & bo.bat for build specific flags
    SET compilerFlags=/std:c++14 /WX /EHsc /MD

    :: files to compile 
    SET files=../../src/main.cpp ../../src/Vec3.cpp ../../src/Window.cpp

    :: external dependancies - includes & libraries
    SET incPaths=dependencies/SDL2/include
    SET libPaths=dependencies/SDL2/libs
    SET libs=SDL2.lib SDL2main.lib 
    
    :: the subsystem - console means a console will be opened with the program even if it's windowed
    SET system=CONSOLE
    
    :: the compiler flags for setting the include and library locations
    SET includeAndLibLocationFlags=/I %incPaths% /link /LIBPATH:%libPaths% %libs%
::}
