/*
-------------------------------------------------------------------------
OBJECT NAME:	SpecProbe.h

FULL NAME:	SPEC 2DS Probe Class

COPYRIGHT:	University Corporation for Atmospheric Research, 2018-2024
-------------------------------------------------------------------------
*/

#ifndef _OAP_SPECPROBE_H_
#define _OAP_SPECPROBE_H_

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
   * Older SPEC data used a 32 bit timing word, which can roll over about
   * once an hour at turboprop speed, every half hour with a jet.
   * Newer files have a 48 bit timing word.
   */
  enum PacketFormatType { Type32, Type48 };

  /**
   * Probe constructor for new SPEC data files. Type32 or Type48, but not
   * anything older.
   */
  SpecProbe(ProbeType type, UserConfig *cfg, const char xml_string[], int recSize);

  enum PacketFormatType FilePacketFormat() { return _packetFormat; }

  virtual struct recStats ProcessRecord(const P2d_rec * record, float version);

  virtual bool isSyncWord(const unsigned char *p);
  virtual bool isOverloadWord(const unsigned char *p);

  static const unsigned char SyncString[4];
  static const unsigned char OverldString[3];


protected:

  virtual uint64_t
  TimeWord_Microseconds(const unsigned char *p);

  /**
   * For type48 probes, this is a straight diff.
   * For type32 probes, this needs to handle a 32 bit rollover once an hour
   */
  virtual uint64_t timeWordDiff(uint64_t val1, uint64_t val2);

  PacketFormatType _packetFormat;
};
}

#endif
