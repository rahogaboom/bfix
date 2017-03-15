/*
 * test program for bfi() and bfx()
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bfix.hpp"


   int
main()
{
   long i, f1, f2, f3, f4, f5;
   unsigned int BYTES_PER_LONG;

   /* 16 bytes unsigned char array plus 7 bytes pad(3 needed for 32 bit systems and 7 needed for 64 bit systems)*/
   unsigned char c[16+7];


   for (i=0 ; i<16+7 ; i++)
   {
      c[i]  = 0x00;
   }

   f1 = f2 = f3 = f4 = f5 = 0;

   bfi(c, 1, 1, 1, 0);
   bfi(c, 5, 2, 3, 0);
   bfi(c, 17, 4, 15, 0);
   bfi(c, 97, 32, 0xffffffff, 0);
   bfi(c, 49, 8, 0xee, 0);
   bfi(c, 8, 8, 0xff, 0);

   fprintf(stderr, "Tests on 32 and 64 bit systems.\n");
   fprintf(stderr, "c(should be) = 8d fe f0 00 00 00 ee 00 00 00 00 00 ff ff ff ff\n");

   fprintf(stderr, "           c = %02x %02x %02x %02x %02x %02x %02x %02x ",
      c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
   fprintf(stderr, "%02x %02x %02x %02x %02x %02x %02x %02x\n",
      c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);

   f1 = bfx(c, 1, 1, 0);
   f2 = bfx(c, 5, 2, 0);
   f3 = bfx(c, 17, 4, 0);
   f4 = bfx(c, 113, 16, 0);
   f5 = bfx(c, 49, 8, 0);

   fprintf(stderr,
      "f1(should be 1) = %ld\n"
      "f2(should be 3) = %ld\n"
      "f3(should be 15) = %ld\n"
      "f4(should be 65535) = %ld\n"
      "f5(should be 238) = %ld\n",
      f1, f2, f3, f4, f5);

   BYTES_PER_LONG = sizeof(unsigned long);
   if (BYTES_PER_LONG == 8)
   {
      unsigned long ff, ee;


      fprintf(stderr, "\n\nTests on 64 bit systems.\n");
      for (i=0 ; i<16+7 ; i++)
      {
         c[i]  = 0x00;
      }

      for (i=0 ; i<BYTES_PER_LONG ; i++)
      {
         ((unsigned char *)&ff)[i] = 0xff;
         ((unsigned char *)&ee)[i] = 0xee;
      }

      bfi(c, 1, 64, ff, 0);
      bfi(c, 65, 64, ee, 0);

      fprintf(stderr, "c(should be) = ff ff ff ff ff ff ff ff ee ee ee ee ee ee ee ee\n");
      fprintf(stderr, "           c = %02x %02x %02x %02x %02x %02x %02x %02x ",
         c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
      fprintf(stderr, "%02x %02x %02x %02x %02x %02x %02x %02x\n",
         c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);

      f1 = bfx(c, 1, 64, 0);
      f2 = bfx(c, 65, 64, 0);
      f3 = bfx(c, 33, 64, 0);

      fprintf(stderr,
         "f1(should be ffffffffffffffff) = %016lx\n"
         "f2(should be eeeeeeeeeeeeeeee) = %016lx\n"
         "f3(should be ffffffffeeeeeeee) = %016lx\n",
         f1, f2, f3);
   }

   exit(0);
}

