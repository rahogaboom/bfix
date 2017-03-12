```
 bfix-1.0.2.tar.gz - changes related to:
     a. add HISTORY.md file
     b. update license to Boost Software License, Version 1.0.
     c. remove bfix.README file(incorporated into README.md)
     d. rewrite README.md
     e. coding format changes
     f. fix g++ warning about possible uninitialized variable -
        some unneeded code - not a bug
     g. modified bfix.mk build script:
            a. add clean target
            b. add compile clang/gcc/clang++/g++ option
            c. add language dialect option
            d. add debug/optimize option
     h. eliminated the C version.  the C++ version will now compile with
        clang/gcc/clang++/g++ - older versions of the compilers would not.
     i. eliminate .h headers from the C++ version
     j. verify code correct operation with latest:
        1. gcc/g++       - gcc (GCC) 6.3.1 20161221 (Red Hat 6.3.1-1)
        2. clang/clang++ - clang version 3.8.1 (tags/RELEASE_381/final)
     k. change error return for bfx() - was 0 on error - now is -1 on error.
        this was a bug - 0 return is a valid value.

 bfix-1.0.1.tar.gz - changes related to:
     a. delete bfix.tar.xz file

 bfix-1.0.0.tar.gz - changes related to:
     a. initial versioned release - the code has been on GitHub for some time without
        versioning.  in future, releases will be versioned.
     b. see article at www.embedded.com:
        http://www.embedded.com/design/other/4219600/A-Generic-API-for-Bit-Manipulation-in-C

 Why are there no releases beyond the latest three on GitHub?  For now, I only intend to
 maintain and answer questions about the most recent releases.  This may change in future.

```
