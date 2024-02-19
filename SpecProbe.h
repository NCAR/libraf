/*
-------------------------------------------------------------------------
OBJECT NAME:	SpecProbe.h

FULL NAME:	SPEC 2DS Probe Class

COPYRIGHT:	University Corporation for Atmospheric Research, 2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_SPEC_PROBE_H_
#define _OAP_SPEC_PROBE_H_

#include "Probe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/**
 * Probe sub-class for SPEC probes.  Data is in OAP * format.  i.e. run
 * through extract2ds(1) or translate2ds(1).
 */
class SpecProbe : public Probe
{

public:
  /**
   * Probe constructor for new SPEC data files. Type32 or Type48, but not
   * anything older.
   */
  SpecProbe(ProbeType type, UserConfig *cfg, const char xml_string[], int recSize);


  virtual struct recStats ProcessRecord(const P2d_rec * record, float version);

  virtual bool isSyncWord(const unsigned char *p);
  virtual bool isOverloadWord(const unsigned char *p);

  static const unsigned char SyncString[4];
  static const unsigned char OverldString[3];


protected:

  virtual uint64_t
  TimeWord_Microseconds(const unsigned char *p);

};
}

#endif
