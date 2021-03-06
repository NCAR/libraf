/*
-------------------------------------------------------------------------
OBJECT NAME:    Particle.h

FULL NAME:      Particle Information

COPYRIGHT:      University Corporation for Atmospheric Research, 1997-2018
-------------------------------------------------------------------------
*/

#ifndef _oap_particle_h_
#define _oap_particle_h_

#include <cstdint>
#include <sys/types.h>

namespace OAP
{

/**
 * Class for Opitical Array Probe (OAP) particle information.
 */
class Particle
{
public:
  Particle();

  long time;			// Seconds since mid-night
  long msec;

  size_t	w, h;		// Particle width and height
  size_t	area;		// Total diodes shadowed by this particle
  bool		vert_gap;	// Was there a blank slice (i.e. multiple parts)
  bool		horiz_gap;	//   and in the hozizontal dir?
  bool		reject;
  bool		dofReject;	// Depth of Field rejected.  Some probes have a flag for this.
  unsigned char	edge;		// particle touched either edge
  bool		timeReject;	// Nimbus will reject (because of bad timing bar)

  uint16_t	x1, x2;	// for particles that touch both edges.

  uint64_t	timeWord;	// Currently milliseconds.
  uint32_t	deltaTime;	// Amount of time between prev & this particle
  uint32_t	liveTime;	// Amount of time consumed by particle
};
}

#endif
