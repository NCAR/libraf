/*
-------------------------------------------------------------------------
OBJECT NAME:	HVPS.h

FULL NAME:	SPEC HVPS Probe

COPYRIGHT:	University Corporation for Atmospheric Research, 2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_HVPS_H_
#define _OAP_HVPS_H_

#include "Probe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/**
 * Probe sub-class for SPEC HVPS probe.
 *
 * Original version (up to 8/1/2023) was for the HVPS-1, a 200um 256 diode
 * probe.  We flew that once or twice as far as I can remember.
 *
 * As of 8/1/2023 I am converting this to support the HVPS-3, which is what
 * RAF owns at this time.  150um 128 diode probe.
 */
class HVPS : public Probe
{

public:
  /**
   * Probe conctructor for ADS2 header.
   */
  HVPS(UserConfig *cfg, Header *hdr, const Pms2 *p, int cnt);
  /**
   * Probe constructor for new PMS2D data files.  New means starting
   * in 2007 with PACDEX project.
   */
  HVPS(UserConfig *cfg, const char xml_string[], int recSize);
  /**
   * Probe constructor for no file header.  Univ Wyoming.
   */
  HVPS(UserConfig *cfg, const char hdr[]);


  struct recStats ProcessRecord(const P2d_rec * record, float version);

  bool isSyncWord(const unsigned char *p);

  static const uint16_t SyncWord;
  static const unsigned char SyncString[3];


protected:

  void hvps_init();

  uint64_t
  TimeWord_Microseconds(const unsigned char *p);

  static const size_t lowerMask, upperMask;

};
}

#endif
