#!/bin/bash

source variables.sh

echo -e "\n\n"
echo "========================"
echo "======Clean Started====="
echo "========================"
echo "Deleting: Executable"
rm ./$exeName
echo "Deleting: *.o"
rm ./*.o
echo "========================"
echo "=====CLEAN FINISHED====="
echo "========================"
echo -e "\n\n"
