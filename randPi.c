/**
   @file      randPi.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2006 by Mitch Richling.  All rights reserved.
   @brief     Compute Pi from random byte streams using GMP!@EOL
   @Keywords  none
   @Std       C89

              The probability that two integers picked at random are
              coprime, or relatively prime, is 6/pi**2.  Two integers A
              and B are coprime iff GCD(A,B)=1, where GCD(A,B) is the
              greatest positive integer that divides both A and B.

              By  reading in a byte  stream, breaking it into pairs of
              integers, and counting  the number of  coprime pairs, we
              compute an approximation  to Pi.  The better the  random
              sequence, the  better  the  approximation  to   Pi.  Try
              something like this:

                   openssl rand 100000000 | randPi

              Note that the counts are printed along with the
              approximate value of Pi.  This is done so that the
              results from multiple program runs may be combined to
              compute a total probability for the group.  In this way
              a compute ranch (a grid) of independent boxen may be
              used to compute Pi from billions and billions of random
              bits!  OK.  Fine!  I need a new hobby. :)

              On a serious note, this program makes a good test for
              random number generators.  I have never seen it used in
              the literature as a random number generator test;
              however, I doubt I'm the first person to think of it.
*/

#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdarg.h>             /* Variable args   ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */
#include <gmp.h>                /* GNU GMP Library       */

int main(void) {

  mpz_t n1, n2, g; /* Numbers to test, and GCD */
  mpf_t tpi, rpi;  /* True Pi, and Random Pi */
  mpf_t rp, nrp;   /* Number relatively prime, and number NOT relatively prime */
  int iCh;
  unsigned char uCh;
  int curDigit, curNumber;
  char hexNumberStrings[2][1024]; /* Our hex string numbers */
  int digitsPerNumber = 10;       /* Number of hex digits in each number to test */
  char *hexDigits = "0123456789ABCDEF";

  /* Two nibbles, hex digits, in a byte => digitsPerNumber must be even. */
  if( (digitsPerNumber % 2) != 0)
    digitsPerNumber += 3;
  
  // Read the bit stream and count coprime pairs
  mpz_init(n1);
  mpz_init(n2);
  mpz_init(g);
  mpf_set_default_prec(1000);
  mpf_init_set_si(rp,  0);
  mpf_init_set_si(nrp, 0);
  curDigit  = 0;
  curNumber = 0;
  while( (iCh = getchar()) >= 0) {
    uCh = (unsigned char)iCh;
    hexNumberStrings[curNumber][curDigit++] = hexDigits[(uCh&0xF0)>>4];
    hexNumberStrings[curNumber][curDigit++] = hexDigits[uCh&0x0F];
    if(curDigit == digitsPerNumber) { /* Filled number */
      hexNumberStrings[curNumber][curDigit] = '\0';
      curDigit = 0;
      curNumber = abs(curNumber-1);
      if(curNumber == 0) { /* Just filled second number */
        mpz_set_str(n1, hexNumberStrings[0], 16);
        mpz_set_str(n2, hexNumberStrings[1], 16);
        mpz_gcd(g, n1, n2);
        if(mpz_cmp_ui(g, 1) == 0) {
          mpf_add_ui(rp,  rp,  1);  /* They are coprime */
        } else {
          mpf_add_ui(nrp, nrp, 1); /* They are NOT coprime */
        } /* end if/else */
      } /* end if */
    } /* end if */
  } /* end while */

  /* Print out the counts */
  printf(" rp: ");
  mpf_out_str(NULL, 10, 100, rp);
  printf("\n");
  printf("nrp: ");
  mpf_out_str(NULL, 10, 100, nrp);
  printf("\n");

  /* Compute our "random pi" approximation : pi = sqrt(6*(rp+nrp)/rp) */
  mpf_init(rpi);
  mpf_add(rpi, rp, nrp);
  mpf_mul_ui(rpi, rpi, 6);
  mpf_div(rpi, rpi, rp);
  mpf_sqrt(rpi, rpi);
  printf("rpi: ");
  mpf_out_str(NULL, 10, 100, rpi);
  printf("\n");

  /* Print out a few digits of the real thing */
  mpf_init_set_str(tpi, 
                   "3.14159265358979323846264338327950288419716939937510582097494459230"
                   "7816406286208998628034825342117067982148086513282306647093844609550"
                   "5822317253594081284811174502841027019385211055596446229489549303819"
                   "6442881097566593344612847564823378678316527120190914564856692346034"
                   "8610454326648213393607260249141273724587006606315588174881520920962"
                   "8292540917153643678925903600113305305488204665213841469519415116094"
                   "3305727036575959195309218611738193261179310511854807446237996274956"
                   "7351885752724891227938183011949129833673362440656643086021394946395"
                   "2247371907021798609437027705392171762931767523846748184676694051320"
                   "0056812714526356082778577134275778960917363717872146844090122495343"
                   "0146549585371050792279689258923542019956112129021960864034418159813"
                   "6297747713099605187072113499999983729780499510597317328160963185950"
                   "2445945534690830264252230825334468503526193118817101000313783875288"
                   "6587533208381420617177669147303598253490428755468731159562863882353"
                   "7875937519577818577805321712268066130019278766111959092164201989",
                   10);
  printf("tpi: ");
  mpf_out_str(NULL, 10, 100, tpi);
  printf("\n");

  /* All done.  Bye! */
  return 0;
} /* end func main */
