#ifndef BFIX_HPP
#define BFIX_HPP

/*
 * File: bfix.hpp
 *
 * Description:
 *     header file for bfix.cpp
 *
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
   long value);

   unsigned long
bfx(
   const unsigned char *cptr,
   unsigned long bit_offset,
   unsigned long bit_len);

#endif /* BFIX_HPP */

