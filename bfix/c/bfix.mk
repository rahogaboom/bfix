#!/bin/bash

# C build script

set -v

# add current directory to library path for shared libraries
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# build static library
rm -rf libbfix.a
gcc -c -fpic -g -ansi -pedantic -Wall -o bfix.o bfix.c
ar rcv libbfix.a bfix.o
ar ts libbfix.a

# build dynamic library and set up links
rm -rf libbfix.so.1.0.1
gcc -shared -Wl,-soname,libbfix.so.1 -o libbfix.so.1.0.1 bfix.o -lc
ln -sf libbfix.so.1.0.1 libbfix.so.1
ln -sf libbfix.so.1.0.1 libbfix.so

# compile test program
gcc -g -ansi -pedantic -Wall -o bfix_test bfix_test.c -L. -lbfix -lm

# run test program
./bfix_test 2> bfix_test.results

