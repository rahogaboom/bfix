
A Generic API for Bit Manipulation in C - C/C++
   - insert(bfi()) or extract(bfx()) bit fields from an unsigned char array of arbitrary length
   - offset bit numbers are from 1(start of array) to unlimited
   - can handle 32 or 64 bit machines
   - use big endian if BFIX_BIG_ENDIAN set, use little endian if BFIX_LITTLE_ENDIAN set,
     otherwise do run time checking
   - bit fields inserted/extracted can be from <=32/64 to 25/57 depending on the offset bit
     number from the beginning of the array(see bfix.c Notes for details)
   - see article in Embedded Systems Programming, Jul. 1999, "A Generic API for Bit Manipulation in C"(included)
   - caveat: always make the unsigned char array 3(32 bit machines) or 7(64 bit machines) bytes
     longer to prevent read/write of bits beyond the logical end of array(see bfix.c Notes for details)

API:

```
/*
 *----------------------------------------------------------------------------------------------------------------------
 * bfi:
 *     bit field insertion
 *
 * Arguments:
 *     Bit field insert:
 *         bfi(cptr, bit_offset, bit_len, value);
 *
 *             cptr       - pointer to unsigned char array
 *             bit_offset - bit offset(starting from 1) from the start of
 *                          the char array
 *             bit_len    - bit length of field to insert
 *             value      - value to be inserted
 *
 * Returns:
 *     None if !BFIX_DEBUG
 *     int 1 if fail and 0 on success
 *----------------------------------------------------------------------------------------------------------------------
 */

#ifdef BFIX_DEBUG
    int
#else
    void
#endif
bfi(
    unsigned char *cptr,
    unsigned long bit_offset,
    unsigned long bit_len,
    long value)

/*
 *------------------------------------------------------------------------------
 * bfx:
 *     bit field extraction
 *
 * Arguments:
 *     Bit field extract:
 *         l = bfx(cptr, bit_offset, bit_len);
 *
 *             cptr       - pointer to unsigned char array
 *             bit_offset - bit offset(starting from 1) from the start of
 *                          the char array
 *             bit_len    - bit length of field to extract
 *
 * Returns:
 *     on success unsigned long extracted bit field, 0 on failure
 *------------------------------------------------------------------------------
 */

    unsigned long
bfx(
    const unsigned char *cptr,
    unsigned long bit_offset,
    unsigned long bit_len)

Common Usage:
   Insert bit fields:
      bfi(cp, 1, 1, 0); # in unsigned char array cp set bit 1 to 0
   Extract bit fields:
      i = bfx(cp, 1, 2); # in unsigned char array cp extracts two bit field starting at bit 1 and sets i
```
