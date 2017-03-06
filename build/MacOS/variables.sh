compilerFlags="-std=c++14"
files="../../src/main.cpp ../../src/Window.cpp ../../src/Maths/Vec3.cpp ../../src/Colour.cpp ../../src/Bitmap.cpp ../../src/StarField.cpp ../../src/RenderContext.cpp ../../src/Maths/Mat4f.cpp ../../src/Input.cpp ../../src/Vertex.cpp ../../src/Maths/Vec4.cpp"

frameworkPath="dependencies/"
frameworks="SDL2"
includePath="dependencies/SDL2.framework/Versions/A/Headers/"

exeName="SoftRender"

dependencyFlags="-L $frameworkPath -framework $frameworks -I $includePath"
