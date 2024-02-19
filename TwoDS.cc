/*
-------------------------------------------------------------------------
OBJECT NAME:	TwoDS.cc

FULL NAME:	SPEC TwoDS Probe Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2023
-------------------------------------------------------------------------
*/

#include "TwoDS.h"
#include "OAPUserConfig.h"

#include "portable.h"

using namespace OAP;


/* -------------------------------------------------------------------- */
TwoDS::TwoDS(UserConfig *cfg, const char xml_entry[], int recSize)
  : SpecProbe(TWODS_T, cfg, xml_entry, recSize)
{
  SetSampleArea();
printf("TwoDS::OAP id=%s, name=%s, resolution=%zu, armWidth=%f, eaw=%f\n", _code, _name.c_str(), _resolution, _armWidth, _eaw);
}

// END TWODS.CC
