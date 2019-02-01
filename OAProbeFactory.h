/* -*- C++ -*-
-------------------------------------------------------------------------
OBJECT NAME:	OAProbeFactory.h

FULL NAME:	Create Probe

TYPE:		Factory Method

COPYRIGHT:	University Corporation for Atmospheric Research, 2003-19
-------------------------------------------------------------------------
*/

#ifndef _oap_OAPROBEFACTORY_h_
#define _oap_OAPROBEFACTORY_h_

#include <string>


/* -------------------------------------------------------------------- */
namespace OAP
{
class Probe;
class UserConfig;

/**
 * A single OAProbeFactory is responsible for instantiating a Probe
 * from a given spec, but it is not a singleton.  There is actually a
 * federation of factories, different factories to handle different specs.
 */
class OAProbeFactory
{
public:
  static OAProbeFactory* getFactory();

  /**
   * Create Probe based on specifier string.
   * @param specifier is a multiple field string separated by ':' (e.g.
   * 'sql:rt-onboard', 'netcdf:post-processing').  For some Probe
   * classes, there may be just a source type, with no ':'.
   * @returns a subclass of Probe pointer.
   * @see Probe for specifier values.
   */
  virtual Probe*
  create(const char specifier[], OAP::UserConfig *cfg = 0);

  virtual ~OAProbeFactory();

protected:
  OAProbeFactory();

private:
  static OAProbeFactory* _oapFactory;
};

}	// END NAMESPACE

#endif
