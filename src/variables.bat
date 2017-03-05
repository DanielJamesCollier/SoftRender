::--------------COMPILE VARIABLES::--------------::
    :: file(s) to compile 
    :: default directory is ../../src/
SET files=../../src/main.cpp ../../src/Window.cpp ../../src/Maths/Vec3.cpp ../../src/Colour.cpp ../../src/Bitmap.cpp ../../src/StarField.cpp ../../src/RenderContext.cpp ../../src/Maths/Mat4f.cpp ../../src/Input.cpp
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
    SET includeFlags=/I %incPaths%
)

IF [%libs]==[] (
   SET libs=no libs
) ELSE (
    SET libraryFlags=/LIBPATH:%libPaths% %libs%
)

:: TODO
:: allow the files var to no have to have ../../src/ on every file

::----------------------------------------------::

:: origional file var
:: new file var
::get filename + exetension
::new files var += filename + extension