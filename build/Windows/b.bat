@echo off
echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo cl ../../src/main.cpp /EHsc /MD /std:c++14 /WX /I dependancies/SDL2/include /link /LIBPATH:dependancies/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
cl ../../src/main.cpp ../../src/Vec3.cpp ../../src/Window.cpp /EHsc /MD /std:c++14 /WX /I dependencies/SDL2/include /link /LIBPATH:dependencies/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
echo ------------------------
echo:
echo: