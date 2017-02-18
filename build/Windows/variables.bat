::--------------COMPILE VARIABLES::--------------::
    :: file(s) to compile 
SET files=../../src/main.cpp ../../src/Window.cpp ../../src/Vec3.cpp ../../src/Colour.cpp ../../src/Bitmap.cpp ../../src/StarField.cpp

    :: include lookup directory('s)
SET incPaths=dependencies/SDL2/include

    :: compiler flag(s)
SET compilerFlags=/std:c++14 /WX /EHsc /MD
::----------------------------------------------::


::----------------LINK VARIABLES::--------------::
    :: path(s) to your libraries
SET libPaths=dependencies/SDL2/libs

    :: libraries to link with .obj(s)
SET libs=SDL2.lib SDL2main.lib 

    :: output .exe name
SET exeName=main.exe

    ::
SET system=CONSOLE
::----------------------------------------------::


::------------------DO NOT EDIT-----------------::
SET libraryFlags=""
SET includeFlags=""

IF [%incPaths]==[] (
    SET incPaths=no includes
) ELSE (
    echo working
    SET includeFlags=/I %incPaths%
)

IF [%libs]==[] (
   SET libs=no libs
) ELSE (
    echo working
    SET libraryFlags=/LIBPATH:%libPaths% %libs%
)


::todo - append ../../ if files do not have it at the front


::----------------------------------------------::


