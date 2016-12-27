/* deterministic prime tester for under 32-bit using Miller-Rabin Algorithm

    USAGE
    Ä±nsigned char = miller_rabin(unsigned long n); returns 0 if the 32-bit
    number n is composite, returns 1 if not

    341
    561
    645
    1105
    1387
    1729
    1905
    2047
    2465
    2701
*/

#include "32-bit_det_MR.h"
#include "bali_rand.h"
#define WN 3  //Witness array size

//  1 = prime, 0 = composite
unsigned char miller_rabin (unsigned long n) {
  const unsigned char a[WN] = {2, 7, 61};   //bases for test to be deterministic under 32-bit
  unsigned char result = 1;

  if ((n == 2) || (n == 3)) {
	  result = 1;
	  return result;
  }

  else if ((n < 3) || (n % 2 == 0)) {
	  result = 0;
	  return result;
  }

  else {
      unsigned long d = n - 1;
      unsigned char s = 0;  //s can at most be 32

      //  write nâˆ’1 as 2^s * d by factoring powers of 2 from nâˆ’1
      while (d % 2 == 0) {
        d = d>>1;
        s++;
      }
      unsigned char i;
      unsigned char r;
      //  test1 checking if a^d is congruent to 1 in mod n, thus not composite
      for (i = 0; i < WN; i++) {
        if(pow_mod(a[i], d, n) != 1){
          //  test2 checking if a^((2^r)*d) is congruent to -1 mod n, thus not composite
          result = 0;
          for (r = 0; r < s; r++){
            if(pow_mod(a[i], powb2(r)*d, n) == n-1){
              result = 1;
              break;
            }
          }
        }
      }
      return result;   //it is not composite, it is an spsp
    }
}

//  a^d % n
unsigned long long pow_mod (unsigned long long a, unsigned long long d, unsigned long long n)
{
    unsigned long long result = 1;      // Initialize result

    a = a % n;  // Update a if it is more than or equal to n

    while (d > 0)
    {
        // If d is odd, multiply a with result
        if (d & 1)
            result = (result*a) % n;

        // d must be even now
        d = d>>1; // d = d/2
        a = (a*a) % n;
    }
    return result;
}

//  2^e under 32-bit, e>0
unsigned long powb2 (unsigned char e){
  unsigned long result = 1;
  while (e != 0) {
    result = result<<1;
    e--;
  }
  return result;
}

unsigned long rsaprime_gen(unsigned long e){
  unsigned long n = 0;
  while (!(miller_rabin(n))) {
    n = oprng();
  }
  return n;
}

unsigned long gcd (unsigned long a, unsigned long b){
  unsigned long temp;
  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}
