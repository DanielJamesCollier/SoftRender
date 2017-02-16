compilerFlags="-std=c++14 -stdlib=libc++ -Werror"
files="../../src/main.cpp ../../src/Window.cpp ../../src/Vec3.cpp"

frameworkPath="dependencies/"
frameworks="SDL2"

exeName="SoftRender"

frameworksFlags="-L $frameworkPath -framework $frameworks"
