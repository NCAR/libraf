/*
-------------------------------------------------------------------------
OBJECT NAME:	TwoDS.h

FULL NAME:	SPEC 2DS Probe Class

COPYRIGHT:	University Corporation for Atmospheric Research, 2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_TWODS_H_
#define _OAP_TWODS_H_

#include "SpecProbe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/**
 * Probe sub-class for SPEC 2DS and 3V-CPI probes.  Data is in OAP
 * format.  e.g run through translate2ds(1).
 */
class TwoDS : public SpecProbe
{

public:
  /**
   * Probe constructor for new TwoDS data files.  New means starting
   * in 2007 with PACDEX project.
   */
  TwoDS(UserConfig *cfg, const char xml_string[], int recSize);


protected:


};
}

#endif
