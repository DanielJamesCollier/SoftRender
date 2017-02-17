source variables.sh

bo_compilerFlags="-O3 $compilerFlags"

echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "compiler flags: $bo_compilerFlags"
echo "files:          $files"
echo "framework path: $frameworkPath"
echo "frameworks:     $frameworks"
echo "include path:   $includePath"
echo "exe name:       $exeName"
echo 
echo clang++ $bo_compilerFlags $dependencyFlags $files $exeName
clang++ $bo_compilerFlags $dependencyFlags $files -o $exeName
echo "------------------------"
echo -e "\n\n"