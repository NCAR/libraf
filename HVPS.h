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


protected:

  void hvps_init();

  static const size_t lowerMask, upperMask;

};
}

#endif
