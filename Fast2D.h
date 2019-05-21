/*
-------------------------------------------------------------------------
OBJECT NAME:	Fast2D.h

FULL NAME:	NCAR/RAF Fast2D.

COPYRIGHT:	University Corporation for Atmospheric Research, 2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_FAST2D_H_
#define _OAP_FAST2D_H_

#include "Probe.h"

namespace OAP
{

/* -------------------------------------------------------------------- */
/*
 * Probe sub-class for NCAR/RAF Fast2D probes.
 */
class Fast2D : public Probe
{

public:
  Fast2D(UserConfig *cfg, const char xml_string[], int recSize);

  struct recStats ProcessRecord(const P2d_rec * record, float version);

  bool isSyncWord(const unsigned char *p);
  bool isOverloadWord(const unsigned char *p);

  static const unsigned char SyncString[3];
  static const unsigned char OverldString[3];


protected:

  void f2d_init();

  uint64_t
  TimeWord_Microseconds(const unsigned char *p);

  // Mask for timing word.  40 bits v1, 42 bits v2.
  uint64_t _timingMask;

  // DOF flag is in different position of sync byte 3 for v1 and v2 of probe.
  unsigned char _dofMask;

};
}

#endif
