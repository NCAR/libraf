
#ifndef PORTABLE_H
#define PORTABLE_H

#include <sys/types.h>
#include <netinet/in.h>

#undef ntohll
#undef htonll

#if defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || defined(LITTLE_ENDIAN)

#ifdef __cplusplus
extern "C" {
#endif

float		ntohf(float);
long long	ntohll(long long *);

#ifdef __cplusplus
}
#endif


#else

#define ntohf(x)	(x)
#define ntohll(x)	(x)

#endif

#define htonf		ntohf
#define htonll		ntohll

#endif
