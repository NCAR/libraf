/*
-------------------------------------------------------------------------
OBJECT NAME:	HVPS.cc

FULL NAME:	HVPS Probe Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2024
-------------------------------------------------------------------------
*/

#include "HVPS.h"
#include "OAPUserConfig.h"

#include "portable.h"

using namespace OAP;



/* -------------------------------------------------------------------- */
HVPS::HVPS(UserConfig *cfg, const char xml_entry[], int recSize)
  : SpecProbe(HVPS_T, cfg, xml_entry, recSize)
{
  _armWidth = 203.0;

  // SPEC Type32 uses a 32 bit timing word.
  _packetFormat = Type32;
  _timingMask = 0x00000000ffffffffLL;

  SetSampleArea();
printf("HVPS::OAP id=%s, name=%s, resolution=%zu, armWidth=%f, eaw=%f\n", _code, _name.c_str(), _resolution, _armWidth, _eaw);
}

/* -------------------------------------------------------------------- */
uint64_t HVPS::timeWordDiff(uint64_t val1, uint64_t val2)
{
  if (val1 < val2)
    val2 = 4294967296 - val2;
  return val1 - val2;
}

// END HVPS.CC
