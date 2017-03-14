#!/bin/bash

#--------------COMPILE VARIABLES--------------#

    # file(s) to compile 
    # default directory is ../../src/
files="../../src/main.cpp ../../src/Window.cpp ../../src/Maths/Vec3.cpp ../../src/Colour.cpp ../../src/Bitmap.cpp ../../src/StarField.cpp ../../src/RenderContext.cpp ../../src/Maths/Mat4f.cpp ../../src/Input.cpp ../../src/Vertex.cpp ../../src/Maths/Vec4.cpp ../../src/Edge.cpp"

    # include lookup directory('s)
includePath="dependencies/SDL2.framework/Versions/A/Headers/"

    # compiler flag(s)
compilerFlags="-std=c++14"
#----------------------------------------------#


#----------------LINK VARIABLES----------------#
    # paths to your frameworks
frameworkPath="dependencies/"

    # framework names to link with
frameworks="SDL2"

    # name of the output executable
exeName="SoftRender"
#----------------------------------------------#


#------------------DO NOT EDIT-----------------#
includeFlags=-"I $includePath"
frameworkFlags="-L $frameworkPath -framework $frameworks"
#----------------------------------------------#
