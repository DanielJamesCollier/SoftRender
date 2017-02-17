compilerFlags="-std=c++14 -stdlib=libc++ -Werror"
files="../../src/main.cpp ../../src/Window.cpp ../../src/Vec3.cpp ../../src/Colour.cpp ../../src/Bitmap.cpp ../../src/StarField.cpp"

frameworkPath="dependencies/"
frameworks="SDL2"
includePath="dependencies/SDL2.framework/Versions/A/Headers/"

exeName="SoftRender"

dependencyFlags="-L $frameworkPath -framework $frameworks -I $includePath"
