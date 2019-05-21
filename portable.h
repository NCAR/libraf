
#ifndef PORTABLE_H
#define PORTABLE_H

#include <sys/types.h>
#include <stdint.h>

#undef ntohll
#undef htonll

#if defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || defined(LITTLE_ENDIAN)

#ifdef __cplusplus
extern "C" {
#endif

uint16_t	ntohs(uint16_t);
uint32_t	ntohl(uint32_t);
uint64_t	ntohll(uint64_t *);
float		ntohf(float);

#ifdef __cplusplus
}
#endif


#else

#define ntohs(x)	(x)
#define ntohl(x)	(x)
#define ntohf(x)	(x)
#define ntohll(x)	(*x)

#endif

#define htons		ntohs
#define htonl		ntohl
#define htonf		ntohf
#define htonll		ntohll

#endif
