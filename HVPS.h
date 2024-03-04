/*
-------------------------------------------------------------------------
OBJECT NAME:	HVPS.h

FULL NAME:	SPEC HVPS Probe

COPYRIGHT:	University Corporation for Atmospheric Research, 2018-2024
-------------------------------------------------------------------------
*/

#ifndef _OAP_HVPS_H_
#define _OAP_HVPS_H_

#include "SpecProbe.h"

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
class HVPS : public SpecProbe
{

public:
  /**
   * Probe constructor for new PMS2D data files.  New means starting
   * in 2007 with PACDEX project.
   */
  HVPS(UserConfig *cfg, const char xml_string[], int recSize);


protected:

  virtual uint64_t timeWordDiff(uint64_t val1, uint64_t val2);

};
}

#endif
