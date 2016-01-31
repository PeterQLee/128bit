#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uint128.h"

int main(int argc, char **argv) {
  uint64_t a,b;
  a=0xfeed0dad1234567;
  b=0x1;
  
  uint128_t at=convert_64_128(a);
  uint128_t bt=convert_64_128(b);
  
  uint128_t ret=multiply_128(&at,&bt);
  add_partition(&at,&bt);
  printf("%llx \n%llx \n",ret.lower,ret.upper);
  printf("%llx \n%llx \n",at.lower,at.upper);

}
