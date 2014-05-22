#!/bin/bash

# C++ build script

set -v

# add current directory to library path for shared libraries
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# build static library
rm -rf libbfix.a
g++ -c -fpic -g -ansi -pedantic -Wall -o bfix.o bfix.cpp
ar rcv libbfix.a bfix.o
ar ts libbfix.a

# build dynamic library and set up links
rm -rf libbfix.so.1.0.1
g++ -shared -Wl,-soname,libbfix.so.1 -o libbfix.so.1.0.1 bfix.o -lc
ln -sf libbfix.so.1.0.1 libbfix.so.1
ln -sf libbfix.so.1.0.1 libbfix.so

# compile test program
g++ -g -ansi -pedantic -Wall -o bfix_test bfix_test.cpp -L. -lbfix -lm

# run test program
./bfix_test 2> bfix_test.results

