#include "portable.h"

#if defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || defined(LITTLE_ENDIAN)

void SwapBytes(void *pv, size_t n)
{
  if (n == 0)
    return;

  char *p = pv;
  size_t lo, hi;
  for (lo = 0, hi = n-1; hi > lo; lo++, hi--)
  {
    char tmp=p[lo];
    p[lo] = p[hi];
    p[hi] = tmp;
  }
}

uint16_t ntohs(uint16_t s)
{
  SwapBytes(&s, 2);
  return s;
}

uint32_t ntohl(uint32_t l)
{
  SwapBytes(&l, 4);
  return l;
}

float ntohf(float f)
{
  SwapBytes(&f, 2);
  return f;
}

uint64_t ntohll(uint64_t *p)
{
  union {
    uint64_t v;
    char b[8];
  } u;

  const char* cp = (const char*)p;
  int i;
  for (i = 7; i >= 0; i--) u.b[i] = *cp++;
  return u.v;
}

#endif

