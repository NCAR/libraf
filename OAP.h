/*
-------------------------------------------------------------------------
OBJECT NAME:    OAP.h

FULL NAME:      Optical Array Probe (OAP) and PMS2d.

DESCRIPTION:

COPYRIGHT:      University Corporation for Atmospheric Research, 2019
-------------------------------------------------------------------------
*/


#ifndef _OAP_OAP_H_
#define _OAP_OAP_H_

/* ADS image record types */
#define ADS_WORD	0x4144
#define HDR_WORD	0x5448
#define SDI_WORD	0x8681
#define AVAPS_WORD	0x4156

/* ID values for the id field in each record header.
 */
// Traditional 32 diode PMS2D probes.
#define PMS2DC1         0x4331
#define PMS2DC2         0x4332
#define PMS2DP1         0x5031
#define PMS2DP2         0x5032

// 64 diode Fast 2DC, 25um.
#define PMS2DC4         0x4334
#define PMS2DC5         0x4335
// 64 diode Fast 2DC, 10um.
#define PMS2DC6         0x4336
// 64 diode Fast 2DP, 200um.
#define PMS2DP4         0x5034

// 64 diode DMT CIP, 25um.
#define PMS2DC8         0x4338
// 64 diode DMT PIP, 100um.
#define PMS2DP8         0x5038

// Greyscale which we never flew.
#define PMS2DG1         0x4731
#define PMS2DG2         0x4732

// SPEC HVPS
#define HVPS1           0x4831
#define HVPS2           0x4832
// SPEC 3V-CPI
#define SPEC2D3H        0x3348
#define SPEC2D3V        0x3356
// SPEC 2DS
#define SPEC2DSH        0x5348
#define SPEC2DSV        0x5356

namespace OAP
{
enum ProbeType { UNKNOWN_T, PMS2D_T, HVPS_T, GREYSCALE_T, FAST2D_T, TWODS_T, CIP_T };

const size_t OAP_BUFF_SIZE = 4096;
const size_t nSlices_32bit = 1024;
const size_t nSlices_64bit = 512;
const size_t nSlices_128bit = 256;

// Header Structure from OAP File Format.  For SourceOAP.
struct P2d_hdr {
  int16_t id;				/* 'P1','C1','P2','C2', H1, H2 */
  int16_t hour;
  int16_t minute;
  int16_t second;
  int16_t year;
  int16_t month;
  int16_t day;
  int16_t tas;				/* true air speed */
  int16_t msec;				/* msec of this record */
  int16_t overld;			/* overload time, msec */
};

// Record Structure from OAP File Format.  For SourceOAP.
struct P2d_rec {
  int16_t id;				/* 'P1','C1','P2','C2', H1, H2 */
  int16_t hour;
  int16_t minute;
  int16_t second;
  int16_t year;
  int16_t month;
  int16_t day;
  int16_t tas;				/* true air speed */
  int16_t msec;				/* msec of this record */
  int16_t overld;			/* overload time, msec */
  unsigned char data[OAP_BUFF_SIZE];	/* image buffer */
};
}

#endif
