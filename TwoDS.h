/*
-------------------------------------------------------------------------
OBJECT NAME:	TwoDS.h

FULL NAME:	SPEC 2DS Prove Class

COPYRIGHT:	University Corporation for Atmospheric Research, 2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_TWODS_H_
#define _OAP_TWODS_H_

#include "Probe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/**
 * Probe sub-class for SPEC 2DS and 3V-CPI probes.
 */
class TwoDS : public Probe
{

public:
  /**
   * Probe constructor for new TwoDS data files.  New means starting
   * in 2007 with PACDEX project.
   */
  TwoDS(UserConfig *cfg, const char xml_string[], int recSize);


  struct recStats ProcessRecord(const P2d_rec * record, float version);

  bool isSyncWord(const unsigned char *p);
  bool isOverloadWord(const unsigned char *p);

  static const unsigned char SyncString[3];
  static const unsigned char OverldString[3];


protected:

  unsigned long long
  TimeWord_Microseconds(const unsigned char *p);

};
}

#endif
