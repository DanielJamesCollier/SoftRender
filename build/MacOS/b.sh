source variables.sh

bo_compilerFlags="$compilerFlags"

echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "compiler flags: $compilerFlags"
echo "files:          $files"
echo "framework path: $frameworkPath"
echo "frameworks:     $frameworks"
echo "exe name:       $exeName"
echo 
echo clang++ $compilerFlags $frameworksFlags $files $exeName
clang++ $compilerFlags $frameworksFlags $files -o $exeName
echo "------------------------"
echo -e "\n\n"