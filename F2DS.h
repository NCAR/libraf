/*
-------------------------------------------------------------------------
OBJECT NAME:	F2DS.h

FULL NAME:	SPEC Fast2DS Probe Class

COPYRIGHT:	University Corporation for Atmospheric Research, 2018-2022
-------------------------------------------------------------------------
*/

#ifndef _OAP_F2DS_H_
#define _OAP_F2DS_H_

#include "Probe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/**
 * Probe sub-class for SPEC Fast2DS and 3V-CPI probes.  Reads SPEC data
 * format, not OAP format.
 */
class F2DS : public Probe
{

public:
  /**
   * Probe constructor for new F2DS data files.  New means starting in
   * 2007 with PACDEX project.
   */
  F2DS(UserConfig *cfg, const char xml_string[], int recSize);


  struct recStats ProcessRecord(const P2d_rec * record, float version);

  bool isSyncWord(const unsigned char *p);

  static const uint16_t SyncWord;
  static const unsigned char SyncString[3];


protected:

  void ClearStats(const OAP::TwoDS_rec *record, float tas);

  uint64_t
  TimeWord_Microseconds(const unsigned char *p);

  TwoDS_hdr	_prev2dsHdr;

};
}

#endif
