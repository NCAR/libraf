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

  SetSampleArea();
printf("HVPS::OAP id=%s, name=%s, resolution=%zu, armWidth=%f, eaw=%f\n", _code, _name.c_str(), _resolution, _armWidth, _eaw);
}


/* -------------------------------------------------------------------- */
uint64_t HVPS::TimeWord_Microseconds(const unsigned char *p)
{
  // SPEC Type32 uses a 32 bit timing word.
  return (ntohll((uint64_t *)p) & 0x00000000ffffffffLL) / _clockMhz;
}

// END HVPS.CC
