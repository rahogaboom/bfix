#!/bin/bash

# C++ build script

set -v

if [ "$1" == 'clean' ]
then
    rm -f bfix.o
    rm -f bfix_test
    rm -f bfix_test.results
    rm -f libbfix.a
    rm -f libbfix.so
    rm -f libbfix.so.1
    rm -f libbfix.so.1.0.1
    exit
fi

# pick compiler
#CC="clang"
#CC="clang++"
#CC="gcc"
CC="g++"

# pick language dialect
#LD="c11"
#LD="c++11"
#LD="gnu11"
#LD="gnu++11"
#LD="c++14"
LD="gnu++14"

# pick debug/optimize
O=g
#O=O

# add current directory to library path for shared libraries
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# compile
$CC -std=$LD -$O -c -fpic -ansi -pedantic -Wall -o bfix.o bfix.cpp

# build static library
rm -rf libbfix.a
ar rcv libbfix.a bfix.o
ar ts libbfix.a

# build dynamic library and set up links
rm -rf libbfix.so.1.0.1
$CC -std=$LD -$O -shared -Wl,-soname,libbfix.so.1 -o libbfix.so.1.0.1 bfix.o -lc
ln -sf libbfix.so.1.0.1 libbfix.so.1
ln -sf libbfix.so.1.0.1 libbfix.so

# compile test program
$CC -std=$LD -$O -ansi -pedantic -Wall -o bfix_test bfix_test.cpp -L. -lbfix -lm

# run test program
./bfix_test 2> bfix_test.results

