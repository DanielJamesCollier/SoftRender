echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "clang++ -Werror  -L dependancies/ -stdlib=libc++ -std=c++14 -o main ../../src/main.cpp"
clang++ -Werror  -L dependancies/ -stdlib=libc++ -std=c++14 -o main ../../src/main.cpp
echo "------------------------"
echo -e "\n\n"
