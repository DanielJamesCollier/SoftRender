#!/bin/bash

source variables.sh

echo "------------------------"
echo "------Clean Started-----"
echo "------------------------"
echo "Deleting: Executable"
rm ./$exeName
echo "Deleting: *.o"
rm ./*.o
echo "------------------------"
echo -e "\n\n"
