/*
-------------------------------------------------------------------------
OBJECT NAME:	OAProbeFactory.cc

COPYRIGHT:	University Corporation for Atmospheric Research, 2003-19
-------------------------------------------------------------------------
*/

#include "OAProbeFactory.h"
#include "OAP.h"

#include "PMS2D.h"
#include "Fast2D.h"
#include "TwoDS.h"
#include "F2DS.h"
#include "HVPS.h"
#include "CIP.h"

using namespace OAP;

OAProbeFactory *OAProbeFactory::_oapFactory = 0;


OAProbeFactory::OAProbeFactory()
{
}

/* -------------------------------------------------------------------- */
OAProbeFactory *OAProbeFactory::getFactory()
{
  if (_oapFactory == 0)
  {
    // Create the root factory, then populate the map with known factories.
    _oapFactory = new OAProbeFactory();
  }
  return(_oapFactory);

}

/* -------------------------------------------------------------------- */
Probe *OAProbeFactory::create(const char specifier[], UserConfig *cfg)
{
  char *id = strstr((char *)specifier, "id=") + 4;
  if (id == 0)
    return 0;

  size_t size = sizeof(OAP::P2d_rec);

  switch (probeType((const unsigned char *)id))
  {
    case OAP::PMS2D_T:
      return new PMS2D(cfg, specifier, size);
    case OAP::FAST2D_T:
      return new Fast2D(cfg, specifier, size);
    case OAP::TWODS_T:
      return new TwoDS(cfg, specifier, size);
    case OAP::HVPS_T:
      return new HVPS(cfg, specifier, size);
    case OAP::CIP_T:
      return new CIP(cfg, specifier, size);
    case OAP::F2DS_T:
      return new F2DS(cfg, specifier, sizeof(OAP::TwoDS_rec));
    default:
      fprintf(stderr, "OAProbeFactory: Unknown probe type, [%c%c]\n", id[0], id[1]);
      fprintf(stderr, "OAProbeFactory: [%s]\n", specifier);
  }
  return 0;
}


OAProbeFactory::
~OAProbeFactory()
{}
