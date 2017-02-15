@echo off
echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo cl /std:c++14 /WX /O2 /SUBSYSTEM:CONSOLE /Femain ../../src/main.cpp 
cl /std:c++14 /WX /O2 /SUBSYSTEM:CONSOLE /Femain ../../src/main.cpp 
echo ------------------------
echo:
echo:
