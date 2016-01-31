#include <stdlib.h>
#include <stdint.h>
#pragma once

typedef struct {
  uint64_t lower;
  uint64_t upper;
}uint128_t;




uint128_t multiply_128(uint128_t *a, uint128_t*b);
void add_partition(uint128_t *result, uint128_t *other);
uint128_t convert_32_128(uint32_t num,unsigned int pos);
uint128_t convert_64_128(uint64_t num);
