source variables.sh

b_compilerFlags="$compilerFlags"

echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "compiler flags: $b_compilerFlags"
echo "files:          $files"
echo "framework path: $frameworkPath"
echo "frameworks:     $frameworks"
echo "include path:   $includePath"
echo "exe name:       $exeName"
echo 
echo clang++ $b_compilerFlags $dependencyFlags $files $exeName
clang++ $b_compilerFlags $dependencyFlags $files -o $exeName
echo "------------------------"
echo -e "\n\n"