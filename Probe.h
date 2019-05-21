/*
-------------------------------------------------------------------------
OBJECT NAME:	Probe.h

TYPE:		Base Class Optical Array Probes (OAP).

FULL NAME:	Probe Information

COPYRIGHT:	University Corporation for Atmospheric Research, 1997-2018
-------------------------------------------------------------------------
*/

#ifndef _OAP_PROBE_H_
#define _OAP_PROBE_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <string>
#include <vector>

#include "OAP.h"
#include "Particle.h"

#ifndef M_PI
#define M_PI (3.14159265)
#endif

std::string XMLgetAttributeValue(const char s[], const char target[]);

class Header;
struct Pms2;

namespace OAP
{

class UserConfig;

/* -------------------------------------------------------------------- */
struct recStats
{
  unsigned long	thisTime;		// Time of this record in secs since midnight.
  int		DASelapsedTime;		// milliseconds.
  int		tBarElapsedtime;	// milliseconds.

  int		nTimeBars;		// n Particles.
  int		accum[1024];
  int		nonRejectParticles;	// n Particles not rejected.
  uint32_t	minBar, maxBar, meanBar;

  double	SampleVolume;		// Basic total sample volume: eaw * dof * tas * time.
  double	tas, concentration, lwc, dbz;
  float		frequency;		// TAS clock.
  int		area;

  std::vector<Particle *>	particles;

  // Return values in/for MainCanvas::draw()
  bool		duplicate;
  unsigned long	prevTime;
};


class Probe {

public:

  virtual ~Probe();

  const std::string & Name() const	{ return _name; }
  const std::string & SerialNum() const	{ return _serialNumber; }

  const char * Code() const		{ return _code; }

  /// @returns Number of Diodes.
  size_t Resolution() const	{ return _resolution; }
  /// @returns Probe resolution per diode.
  size_t nDiodes() const	{ return _nDiodes; }
  size_t nSlices() const	{ return _nSlices; }
  size_t NumberBins() const	{ return _numBins; }

  bool Display() const		{ return _displayed; }
  void setDisplay(bool b)	{ _displayed = b; }

  void setUserConfig(UserConfig *cfg)	{ _userConfig = cfg; }

  virtual struct recStats
  ProcessRecord(const OAP::P2d_rec * record, float version) = 0;

  virtual bool
  isSyncWord(const unsigned char *p) = 0;
  virtual bool
  isOverloadWord(const unsigned char *p)	{ return false; }
  virtual bool
  isBlankSlice(const unsigned char *p)	{ return memcmp(p, BlankSlice, nDiodes()/8) == 0; }

  ProbeType Type() const	{ return _type; }

  /**
   * Set sample area based on user selected calculation type Entire-in
   * vs Center-in, etc.  Output is sampleArea[] in mm^2
   */
  void SetSampleArea();

  /**
   * Probes with compressed data do not have a fixed number of slices (once
   * uncompressed).  Offer the ability to adjust on the fly, per record.
   */
  void Set_nSlices(size_t nSlices)	{ _nSlices = nSlices; }

  /// Crude sample area based on armWidth, nDiodes, and resolution.
  float SampleArea() const	{ return _sampleArea; }

  /// @returns Logical-record length.  Exabyte hangover.
  long lrLen() const		{ return _lrLen; }
  /// @returns Logical-records per physical record.  Exabyte hangover.
  int lrPpr() const		{ return _lrPpr; }

  static const unsigned char BlankSlice[16];

  /// Statistics and derived data from current ProcessRecord()
  /// @TODO this should be refactored out of public.
  struct recStats stats;

  /// Clear all particles from the stats.
  void clearParticles();


protected:
  /**
   * Probe conctructor for ADS2 header.  This will only ever have 32 diode
   * PMS2D probes an HVPS once.
   */
  Probe(ProbeType type, UserConfig *cfg, Header *hdr, const Pms2 *p, int cnt, size_t ndiodes);
  /**
   * Probe constructor for new PMS2D data files.  New means starting
   * in 2007 with PACDEX project.  These files follow the OAPfiles standard.
   */
  Probe(ProbeType type, UserConfig *cfg, const char xml_string[], int recSize, size_t ndiodes);
  /**
   * Probe constructor for no file header.  Univ Wyoming.
   */
  Probe(ProbeType type, UserConfig *cfg, const char hdr[], size_t ndiodes);

  /// Common initialization for all constructors.
  void init();

  void ClearStats(const OAP::P2d_rec *record);
  void checkEdgeDiodes(Particle * cp, const unsigned char *p);
  size_t area(const unsigned char *p);
  size_t height(const unsigned char *p);
  void computeDerived(double sv[], double liveTime);
  size_t checkRejectionCriteria(Particle * cp, recStats & stats);

  /// Keep a copy of user config.
  const UserConfig	*_userConfig;

  std::string	_name;
  std::string	_serialNumber;

  char		_code[4];
  ProbeType	_type;

  long	_lrLen;
  int	_lrPpr;

  /// Probe resolution per diode in micron
  size_t	_resolution;

  /// Number of diodes in the array
  size_t	_nDiodes;

  /**
   * Clock speed of the probe.  Not used by original PMS2D, but used by most modern
   * probes to decode the timing word.
   */
  float		_clockMhz;

  /**
   * Number of bins being output for size-distribution. Values are nDiodes for
   * entire-in, and nDiodes times two for center-in and reconstruction.
   */
  size_t	_numBins;

  /// Physical distance between the two probe arms in mm.
  float		_armWidth;

  /// Effective Area Width in mm.
  float		_eaw;

  /// Depth of Field constant.
  float		_dof_const;

  /// Number of slices per 4k buffer.
  size_t	_nSlices;


  /// IS this probe being displayed.
  bool		_displayed;


  // Store prevtime and hdr for ProcessRecord, so we can compute elapsed time.
  P2d_hdr	_prevHdr;
  int		_prevTime;
  unsigned long long _prevTimeWord;

  /// Crude sample area - as opposed to the 'per bin' sample area.
  float		_sampleArea;

  /// Sample area per bin in mm^2
  float *sampleArea;

  /// Current Particle data.  Class member because a particle can/will cross into next record.
  Particle	*cp;

  static const float diodeDiameter;

};
}

#endif
