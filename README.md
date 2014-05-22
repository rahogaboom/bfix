
A Generic API for Bit Manipulation in C - C/C++
   - 

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
