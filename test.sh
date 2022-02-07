#!/bin/sh

clear
#echo Compiling...
echo ________________________________________________________________________________________________
echo
cd Model/Pieces
make
./test.out
cd ../..
echo
