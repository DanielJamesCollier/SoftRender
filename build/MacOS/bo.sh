#!/bin/bash

# initialise generic build variables
source variables.sh

# build specific compiler flags + generic
bo_compilerFlags="-O3 $compilerFlags"
echo -e '\n\n'
echo "========================"
echo "======Build Started====="
echo "========================"
echo -e '\n'
echo "=========inputs========="
echo -e '\n'
echo "-----------------------"
echo "struct CompilerInputs {"
echo -e '\n'
echo "  files[] = {"
for one_thing in $files; do
    echo "      "${one_thing##*/} 
done
echo "  }"
echo -e '\n'
echo "  includePaths[] = {"
for one_thing in $includePath; do
    echo "      "$one_thing
done
echo "  }"
echo -e '\n'
echo "  compilerFlags[] = {"
for one_thing in $bo_compilerFlags; do
    echo "      "$one_thing
done
echo "  }"
echo '}'
echo -e '\n'
echo "-----------------------"
echo "struct LinkerInputs {"
echo -e '\n'
echo "  frameworkPaths[] = {"
for one_thing in $frameworkPath; do
    echo "      "$one_thing
done
echo "  }"
echo -e '\n'
echo "  frameworks[] = {"
for one_thing in $frameworks; do
    echo "      "$one_thing
done
echo "  }"
echo '}'
echo "========================"
echo -e '\n'
echo "========compiler========"
echo "compiling..."
echo -e '\n'
clang++ -c $bo_compilerFlags $includeFlags $files
echo "========================"
echo -e '\n'
echo "=========linker========="
echo -e '\n'
echo "struct thingsToLink {"
for one_thing in *.o; do
    echo "      "${one_thing##*/} 
done
for one_thing in $frameworks; do
    echo "      "$one_thing".framework"
done
echo '}'
echo -e '\n'
echo "linking..."
echo -e '\n'
clang++ *.o $frameworkFlags -o $exeName
echo "========================"
echo -e '\n'
echo "========================"
echo "=====Build Finished====="
echo "========================"
echo -e '\n\n'