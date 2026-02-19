/**********************************/
// memory.c
// basic memory utils
// for BIOS & UEFI

/**********************************/
// system includes

#include <stddef.h>
#include <stdint.h>

/**********************************/

// Copy contents of src region to dst
void *memcpy(void *dst, const void *src, size_t n) {
  uint8_t *d = dst;
  const uint8_t *s = src;
  for (size_t i = 0; i < n; i++)
    d[i] = s[i];
  return dst;
}

// Set the bits for a memory region
void *memset(void *dst, int val, size_t n) {
  uint8_t *d = dst;
  for (size_t i = 0; i < n; i++)
    d[i] = (uint8_t)val;
  return dst;
}

// Compares to memory regions
int memcmp(const void *a, const void *b, size_t n) {
  const uint8_t *x = a;
  const uint8_t *y = b;
  for (size_t i = 0; i < n; i++) {
    if (x[i] != y[i])
      return x[i] - y[i];
  }
  return 0;
}
