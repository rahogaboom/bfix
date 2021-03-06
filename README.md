```

Library:
    bfix.hpp

A Generic API for Bit Manipulation in C/C++

    - insert(bfi()) or extract(bfx()) bit fields from an unsigned char array of arbitrary length

    - can handle 32 or 64 bit machines

    - big endian, little endian or run time checking

    - a C++ header file only library

    - simple library, two routines bfi()(insert bit field) and bfx()(extract bit field)

    - no library dependencies(except standard header files)

    - offset bit numbers are from 1(start of array) to unlimited

    - verification tests that show code usage examples, see bfix_test.cpp

    - see cut/paste Examples section and API(bfi(), bfx()) section below

    - a bfix-compile.tar file is provided with a non-header compiled(clang, clang++, gcc, g++) version

    - compiles with clang++/g++

    - see article in Embedded Systems Programming, Jul. 1999,
      "A Generic API for Bit Manipulation in C"(included)

    - this file is the entire documentation needed to use the library

    - Author: Richard Hogaboom, richard.hogaboom@gmail.com

Usage:

    see Examples: below

Files:

    bfix-compile.tar - non-header compiled(clang, clang++, gcc, g++) version
    bfix.doc         - documentation for library
    bfix.hpp         - header only C++ implementation
    bfix.mk          - build script, compiles/executes test code
    bfix_test.cpp    - test code

Examples:

    /* 16 bytes unsigned char array plus 7 bytes pad(3 needed for 32 bit systems and 7 needed for 64 bit systems) */
    unsigned char c[16+7];

    bfi(c, 1, 1, 1, 0);
    bfi(c, 5, 2, 3, 0);
    bfi(c, 17, 4, 15, 0);
    bfi(c, 97, 32, 0xffffffff, 0);
    bfi(c, 49, 8, 0xee, 0);
    bfi(c, 8, 8, 0xff, 0);

    bitfield1 = bfx(c, 1, 1, 0);
    bitfield2 = bfx(c, 5, 2, 0);
    bitfield3 = bfx(c, 17, 4, 0);
    bitfield4 = bfx(c, 113, 16, 0);
    bitfield5 = bfx(c, 49, 8, 0);

API:

/*
 * File: bfix.hpp
 *
 *     Based on article in Embedded Systems Programming, Jul. 1999,
 *     "A Generic API for Bit Manipulation in C" by Richard Hogaboom
 *
 * Description:
 *
 *     bfi()/bfx() are used to insert and extract bit fields from an arbitrary length array
 *     of unsigned chars pointed to by an unsigned char* pointer.
 *
 * Functions:
 *
 *         int
 *     bfi
 *         (
 *             unsigned char *cptr,
 *             unsigned long bit_offset,
 *             unsigned long bit_len,
 *             long value,
 *             unsigned int endian
 *         )
 *         e.g. int return = bfi(cptr, bit_offset, bit_len, value, endian);
 *
 *
 *         long
 *     bfx
 *         (
 *             const unsigned char *cptr,
 *             unsigned long bit_offset,
 *             unsigned long bit_len,
 *             unsigned int endian
 *         )
 *         e.g. long value = bfx(cptr, bit_offset, bit_len, endian);
 *
 * Error Handling:
 *
 *     1. Exceptions - None
 *     2. Debugging  - const int DEBUG = true for debugging output
 *     3. Returns
 *
 *            bfi():
 *                bit_offset < 1     - error, return -1
 *                bit_len < 1        - error, return -2
 *                bit_len > too long - error, return -3
 *                endian not 0-2     - error, return -4
 *                return 0           - success
 *
 *            bfx():
 *                bit_offset < 1     - error, return -1
 *                bit_len < 1        - error, return -2
 *                bit_len > too long - error, return -3
 *                endian not 0-2     - error, return -4
 *                return value       - success
 *
 * Notes:
 *     1.  in the following notes any annotation of the form n/m means n for 32 bit systems and
 *         m for 64 bit systems.  operation on 32 or 64 bit systems should be transparent.
 *
 *     2.  bit_len should be <=32/64 to 25/57. it depends on the value of bit_offset.  the method
 *         always uses a memmove() of 4/8 bytes to a long temporary storage in which logical
 *         operations can be performed.  this means that the bit_len can be at most 4/8 bytes,
 *         but in a case in which the start bit is not at the beginning of a byte, then the
 *         bit_len can only extend until the end of the 4/8'th byte.  if the start bit is the
 *         last bit of a byte this will limit bit_len to 25/57 bits - the last bit of the first
 *         byte plus the next 3/7 bytes.
 *
 *     3.  4(32 bit machines)/8(64 bit machines) bytes are always read from the unsigned char
 *         array, modified and then written back.  this means that if you set the last bit of
 *         the array, then the next 3/7 bytes will be read and written back, thus seemingly
 *         overrunning the array.  if the 4/8 bytes does not overrun the array then no bits
 *         beyond the end of the array will be changed.  if the 4/8 bytes does overrun the
 *         array some provision must be made to deal with this possibility.  the array could
 *         be padded by 3/7 extra bytes.
 *
 *     4.  bit_offset+bit_len should not overrun the array.
 *
 *     5.  value should not be too long to fit into the bit field.  if it is, the high order bits
 *         in front of the low order bit_len bits will be truncated.
 *
 *     6.  all bit_len bits will be set and no bit outside the bit field will be changed.
 *
 *     7.  value may be negative and prefix 2's complement sign bits are truncated to fit into
 *         bit_len bits.
 *
 *     8.  use the lscpu cmd to determine 32/64 bit and endianness:
 *         $ lscpu
 *         Architecture:          x86_64
 *         CPU op-mode(s):        32-bit, 64-bit
 *         Byte Order:            Little Endian
 *
 *     9.  use lscpu to determine 32/64 bit machine and big or little endian
 *
 *     10. since bit_offset is unsigned long it cannot have negative values - however no
 *         check for too large is done
 *
 * Author: Richard Hogaboom
 *         richard.hogaboom@gmail.com
 *
 */

/*
 * Name:
 *     bfi()
 *
 * Purpose: 
 *     extract bit field from an array of chars pointed to by an unsigned char* pointer
 *
 * Usage:
 *     unsigned char *cptr
 *     unsigned long bit_offset
 *     unsigned long bit_len
 *     long value
 *     unsigned int endian
 *
 *     int return = bfi(cptr, bit_offset, bit_len, value, endian);
 *
 * Returns:
 *     bit_offset < 1     - error, return -1
 *     bit_len < 1        - error, return -2
 *     bit_len > too long - error, return -3
 *     endian not 0-2     - error, return -4
 *     return 0           - success
 *
 * Parameters:
 *     unsigned char *cptr      - pointer to unsigned char array
 *     unsigned long bit_offset - bit offset(starting from 1) from the start of the char array
 *     unsigned long bit_len    - bit length of field to insert
 *     long value               - value to insert
 *     unsigned int endian      - endian enum, 0(run time checking), 1(big endian), 2(little endian)
 *
 * Comments:
 *     4(32 bit machines)/8(64 bit machines) bytes are always read from the unsigned char
 *     array, modified and then written back.  this means that if you set the last bit of
 *     the array, then the next 3/7 bytes will be read and written back, thus seemingly
 *     overrunning the array.  if the 4/8 bytes does not overrun the array then no bits
 *     beyond the end of the array will be changed.  if the 4/8 bytes does overrun the
 *     array some provision must be made to deal with this possibility.  the array could
 *     be padded by 3/7 extra bytes.
 */

    inline int
bfi
    (
        unsigned char *cptr,
        unsigned long bit_offset,
        unsigned long bit_len,
        long value,
        unsigned int endian
    )

/*
 * Name:
 *     bfx()
 *
 * Purpose: 
 *     extract bit field from an array of chars pointed to by an unsigned char* pointer
 *
 * Usage:
 *     const unsigned char *cptr
 *     unsigned long bit_offset
 *     unsigned long bit_len
 *     unsigned int endian
 *
 *     long value = bfx(cptr, bit_offset, bit_len, endian);
 *
 * Returns:
 *     bit_offset < 1     - error, return -1
 *     bit_len < 1        - error, return -2
 *     bit_len > too long - error, return -3
 *     endian not 0-2     - error, return -4
 *     return value       - success
 *
 * Parameters:
 *     const unsigned char *cptr - const pointer to unsigned char array
 *     unsigned long bit_offset  - bit offset(starting from 1) from the start of the char array
 *     unsigned long bit_len     - bit length of field to extract
 *     unsigned int endian       - endian enum, 0(run time checking), 1(big endian), 2(little endian)
 *
 * Comments:
 */

    inline long
bfx
    (
        const unsigned char *cptr,
        unsigned long bit_offset,
        unsigned long bit_len,
        unsigned int endian
    )

```
