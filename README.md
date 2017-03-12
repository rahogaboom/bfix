```
A Generic API for Bit Manipulation in C/C++
   - insert(bfi()) or extract(bfx()) bit fields from an unsigned char array of arbitrary length
   - compiles with gcc/g++/clang/clang++
   - offset bit numbers are from 1(start of array) to unlimited
   - can handle 32 or 64 bit machines
   - compiled in big endian if BFIX_BIG_ENDIAN defined, compiled in little endian if
     BFIX_LITTLE_ENDIAN defined, otherwise do run time checking
   - bit fields inserted/extracted can be from <=32/64 to 25/57 bits in length depending
     on the offset bit number from the beginning of the array(see bfix.cpp Note 3 for details)
   - see article in Embedded Systems Programming, Jul. 1999,
     "A Generic API for Bit Manipulation in C"(included)
   - caveat: always make the unsigned char array 3(32 bit machines) or 7(64 bit machines) bytes
     longer to prevent read/write of bits beyond the logical end of array
     (see bfix.cpp Note 8 for details)

API:

/*
 *==================================================================================================
 *
 * File Name:
 *     bfix.cpp
 *
 *==================================================================================================
 *
 * Functions:
 *
 *         #ifdef BFIX_DEBUG
 *             int
 *         #else
 *             void
 *         #endif
 *     bfi
 *         (
 *             unsigned char *cptr,
 *             unsigned long bit_offset,
 *             unsigned long bit_len,
 *             long value
 *         )
 *         e.g. void bfi(cptr, bit_offset, bit_len, value);
 *         e.g. #ifdef BFIX_DEBUG - int return = bfi(cptr, bit_offset, bit_len, value);
 *
 *
 *         unsigned long
 *     bfx
 *         (
 *             const unsigned char *cptr,
 *             unsigned long bit_offset,
 *             unsigned long bit_len
 *         )
 *         e.g. unsigned long l = bfx(cptr, bit_offset, bit_len);
 *
 *==================================================================================================
 *
 * Description:
 *
 *     bfi()/bfx() are used to insert and extract bit fields from an arbitrary length array
 *     of unsigned chars pointed to by an unsigned char* pointer.
 *
 *==================================================================================================
 *
 * Error Handling
 *
 *     1. Exceptions - None
 *     2. Debugging  - define BFIX_DEBUG for debugging output
 *     3. Returns    - bfi(): if defined BFIX_DEBUG, returns 0 on success and -1 on error
 *                     bfx(): if defined BFIX_DEBUG, returns value on success and -1 on error
 *                     bfx(): if not defined BFIX_DEBUG, returns value on success and -1 on error
 *
 *==================================================================================================
 *
 * Notes:
 *     1. in the following notes any annotation of the form n/m means n for 32 bit systems and
 *        m for 64 bit systems.  operation on 32 or 64 bit systems should be transparent.
 *
 *     2. normally, no checking for reasonable argument values is done.  if BFIX_DEBUG is defined
 *        then reasonable values for bit_offset and bit_len are checked.  a reasonable value for
 *        bit_len is dependent on the starting bit_offset value as explained in note 3.  a check
 *        if both BFIX_BIG_ENDIAN and BFIX_LITTLE_ENDIAN are defined at the same time is made.
 *        see the code for BFIX_DEBUG inclusions.
 *
 *     3. bit_len should be <=32/64 to 25/57. it depends on the value of bit_offset.  the method
 *        always uses a memmove() of 4/8 bytes to a long temporary storage in which logical
 *        operations can be performed.  this means that the bit_len can be at most 4/8 bytes,
 *        but in a case in which the start bit is not at the beginning of a byte, then the
 *        bit_len can only extend until the end of the 4/8'th byte.  if the start bit is the
 *        last bit of a byte this will limit bit_len to 25/57 bits - the last bit of the first
 *        byte plus the next 3/7 bytes.  a bit_len of zero is ok - with bfx() returning 0 and
 *        bfi() inserting nothing.
 *
 *     4. and bit_offset+bit_len should not overrun the array.
 *
 *     5. value should not be too long to fit into the bit field.  if it is, the high order bits
 *        in front of the low order bit_len bits will be truncated.
 *
 *     6. all bit_len bits will be set and no bit outside the bit field will be changed.
 *
 *     7. value may be negative and prefix 2's complement sign bits are truncated to fit into
 *        bit_len bits.
 *
 *     8. 4(32 bit machines)/8(64 bit machines) bytes are always read from the unsigned char
 *        array, modified and then written back.  this means that if you set the last bit of
 *        the array, then the next 3/7 bytes will be read and written back, thus seemingly
 *        overrunning the array.  if the 4/8 bytes does not overrun the array then no bits
 *        beyond the end of the array will be changed.  if the 4/8 bytes does overrun the
 *        array some provision must be made to deal with this possibility.  the array could
 *        be padded by 3/7 extra bytes.
 *
 *     9. there are three ways to handle endianness.  by default endianness is determined at run
 *        time.  this, however, introduces some run time penalty.  if BFIX_BIG_ENDIAN or
 *        BFIX_LITTLE_ENDIAN(but not both) is defined in bfix.h then that particular behavior
 *        will be compiled in.
 *
 *==================================================================================================
 *
 * Author: Richard Hogaboom
 *         richard.hogaboom@gmail.com
 *
 *==================================================================================================
 */
```
