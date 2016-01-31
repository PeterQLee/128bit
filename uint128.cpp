#include "uint128.h"
#include <stdio.h>

uint128_t multiply_128(uint128_t *a, uint128_t *b) {
  uint32_t mask_d=0xffffffff;
  uint128_t result;
  result.lower=0LL;
  result.upper=0LL;

  uint32_t a0,a1,a2,a3;
  uint32_t b0,b1,b2,b3;
  uint32_t cur,mult;
  

  a0=(uint32_t)((a->lower)&mask_d);
  a1=(uint32_t)((a->lower)>>32);
  a2=(uint32_t)((a->upper)&mask_d);
  a3=(uint32_t)((a->upper)>>32);
      
  b0=(uint32_t)((b->lower)&mask_d);
  b1=(uint32_t)((b->lower)>>32);
  b2=(uint32_t)((b->upper)&mask_d);
  b3=(uint32_t)((b->upper)>>32);
  

  cur=a0;
  mult=b0;
  uint64_t chr=cur*mult;
  uint128_t tmp1=convert_32_128((uint32_t)chr&mask_d,0);
  uint128_t tmp2=convert_32_128((uint32_t)(chr>>32),1);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);
  
  
  //b1
  mult=b1;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,1);
  tmp2=convert_32_128((uint32_t)(chr>>32),2);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);
  
  //b2
  mult=b2;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,2);
  tmp2=convert_32_128((uint32_t)(chr>>32),3);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  //b3
  mult=b3;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,3);
  //tmp2=convert_32_128((uint32_t)(chr>>32),4);
  //add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  cur=a1;
  
  mult=b0;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,1);
  tmp2=convert_32_128((uint32_t)(chr>>32),2);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);
  printf("%llx\n",tmp1.lower);

  mult=b1;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,2);
  tmp2=convert_32_128((uint32_t)(chr>>32),3);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  mult=b2;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,3);
  //  tmp2=convert_32_128((uint32_t)(chr>>32),3);
  //add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);
  //no point in b3, will overflow anyways

  cur=a2;
  mult=b0;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,2);
  tmp2=convert_32_128((uint32_t)(chr>>32),3);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  mult=b1;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,3);
  //tmp2=convert_32_128((uint32_t)(chr>>32),3);
  //add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  
  cur=a3;
  mult=b0;
  chr=cur*mult;
  tmp1=convert_32_128((uint32_t)chr&mask_d,3);
  //tmp2=convert_32_128((uint32_t)(chr>>32),3);
  add_partition(&tmp1,&tmp2);
  add_partition(&result,&tmp1);

  return result;
}

uint128_t convert_32_128(uint32_t num, unsigned int pos) {
  //0 ffffffff
  //1 00000000ffffffff
  //2 0000000000000000ffffffff
  //3 000000000000000000000000ffffffff
  uint128_t ret;
  if (pos<2) {
    unsigned int n=pos*32;
    ret.upper=0LL;
    ret.lower=(uint64_t)(num);
    ret.lower=ret.lower<<n;
  }
  else {
    unsigned int n=pos*32;
    ret.lower=0LL;
    ret.upper=(uint64_t)(num);
    ret.upper=ret.upper<<n;
  }
  return ret;
  
}

void add_partition(uint128_t *result,  uint128_t* other){
  int cur=0;
  int lim=128/32;
  uint32_t mask_d=0xffffffff;
  
  //add lower 32 bit portion
  result->lower+=(other->lower)&mask_d;
  
  //convert upper 32 bit of lower portion +add carry
  
  uint64_t tmp=(result->lower >>32 ) + ((other->lower) >> 32);
  result->upper+= (tmp >> 32);
  result->lower=(result->lower)&mask_d;
  result->lower+= ((tmp & mask_d) << 32);
  
  //add lower portion of upper
  result->upper+=other->upper;

}
uint128_t convert_64_128(uint64_t num) {
  uint128_t ret;
  ret.upper=0LL;
  ret.lower=num;
  return ret;
}
