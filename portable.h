/*
 * Windows/MinGW does not have the typical byte swapping routines, so roll our
 * own.  I suppose we could try and use boost, but that library gets dragged
 * in everywhere.  Not happy about this....
 *
 * Since we are defining our own routines that will take the place of any
 * system ntoh?(), make sure this include file comes AFTER netinet/in.h or
 * arpa/inet.h
 */

#ifndef _PORTABLE_H_
#define _PORTABLE_H_

#include <sys/types.h>
#include <stdint.h>

#undef ntohs
#undef htons
#undef ntohl
#undef htonl
#undef ntohll
#undef htonll

#if defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || defined(LITTLE_ENDIAN) || defined(_WIN64)

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
