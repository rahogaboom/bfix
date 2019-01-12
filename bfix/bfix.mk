#!/bin/bash

# build script

set -v

if [ "$1" == 'clean' ]
then
    rm -f bfix_test
    rm -f bfix_test.results
    exit
fi

# compiler
CC="clang++"
#CC="g++"

# debug/optimize
O=g
#O=O

# compile test program
$CC -$O -ansi -pedantic -Wall -o bfix_test bfix_test.cpp

# run test program
./bfix_test 2> bfix_test.results

