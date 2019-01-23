#include "portable.h"

#if defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || defined(LITTLE_ENDIAN)

float ntohf(float inF)
{
  union
    {
    float       f;
    char        s[4];
    } tmp;

  char  sc;

  tmp.f = inF;

  sc = tmp.s[0];
  tmp.s[0] = tmp.s[3];
  tmp.s[3] = sc;

  sc = tmp.s[1];
  tmp.s[1] = tmp.s[2];
  tmp.s[2] = sc;

  return(tmp.f);

}


long long ntohll(long long *p)
{
  union {
    long long v;
    char b[8];
  } u;

  const char* cp = (const char*)p;
  int i;
  for (i = 7; i >= 0; i--) u.b[i] = *cp++;
  return u.v;
}

#endif

