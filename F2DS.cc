/*
-------------------------------------------------------------------------
OBJECT NAME:	F2DS.cc

FULL NAME:	SPEC Fast2DS Probe Class

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 2018-2023
-------------------------------------------------------------------------
*/

#include "F2DS.h"
#include "OAPUserConfig.h"

#include "portable.h"

using namespace OAP;

// This is start of particle in the SPEC compressed world.
const uint16_t F2DS::SyncWord = 0x5332;

// Standard sync word in the OAP file format world.
const unsigned char F2DS::SyncString[] = { 0xaa, 0xaa, 0xaa };


/* -------------------------------------------------------------------- */
F2DS::F2DS(UserConfig *cfg, const char xml_entry[], int recSize) : Probe(F2DS_T, cfg, xml_entry, recSize, 128)
{
  _lrLen = recSize;

//  std::string id = ::XMLgetAttributeValue(xml_entry, "id");
  std::string id("S1");
  strcpy(_code, id.c_str());

//  _name = ::XMLgetAttributeValue(xml_entry, "type");
//  _name += ::XMLgetAttributeValue(xml_entry, "suffix");
  _name = "Fast2DS";

//  _resolution = atoi(::XMLgetAttributeValue(xml_entry, "resolution").c_str());
  _resolution = 10;
  _armWidth = 50.8;
  _dof_const = 5.13;
  _clockMhz = 20;

  SetSampleArea();
printf("F2DS::OAP id=%s, name=%s, resolution=%zu, armWidth=%f, eaw=%f\n", _code, _name.c_str(), _resolution, _armWidth, _eaw);
}


/* -------------------------------------------------------------------- */
uint64_t F2DS::TimeWord_Microseconds(const unsigned char *p)
{
  // SPEC Type48 uses a 48 bit timing word.
  return (ntohll((uint64_t *)p) & 0x0000ffffffffffffLL) / _clockMhz;
}

/* -------------------------------------------------------------------- */
bool F2DS::isSyncWord(const unsigned char *p)
{
  return memcmp(p, (void *)&SyncString, 3) == 0;
}

/* -------------------------------------------------------------------- */
struct recStats F2DS::ProcessRecord(const P2d_rec *in_rec, float version)
{
  const TwoDS_rec *record = (const TwoDS_rec *)in_rec;

  int		startTime, overload = 0;
  unsigned long startMilliSec;
  double	sampleVolume[(nDiodes()<<1)+1], totalLiveTime;

  uint64_t	firstTimeWord = 0;

  ClearStats(record);
  stats.DASelapsedTime = stats.thisTime - _prevTime;
  stats.SampleVolume = SampleArea() * stats.tas;

  if (version == -1)    // This means set time stamp only
  {
    _prevTime = stats.thisTime;
    memcpy((char *)&_prev2dsHdr, (char *)record, sizeof(TwoDS_hdr));
    return(stats);
  }

#ifdef DEBUG
  printf("S1 %02d:%02d:%02d.%d - ", record->hour, record->minute, record->second, record->msec);
#endif

  totalLiveTime = 0.0;

  switch (_userConfig->GetConcentration()) {
    case CENTER_IN:
    case RECONSTRUCTION:	_numBins = 256; break;
    default:			_numBins = nDiodes();
    }

  for (size_t i = 0; i < NumberBins(); ++i)
    sampleVolume[i] = stats.tas * sampleArea[i] * 0.001;


  // Scan record, compute tBarElapsedtime and stats.
  const unsigned char *p = record->data;

  startTime = _prevTime / 1000;
  startMilliSec = _prev2dsHdr.msec;

  // Loop through all slices in record.
  for (size_t i = 0; i < nSlices(); ++i, p += 16)
  {
    /* Have particle, will travel.
     */
    if (isSyncWord(p))
    {
      uint64_t thisTimeWord = TimeWord_Microseconds(&p[8]);

      if (firstTimeWord == 0)
        firstTimeWord = thisTimeWord;

      // Close out particle.  Timeword belongs to previous particle.
      if (cp)
      {
        cp->timeWord = thisTimeWord;
        unsigned long msec = startMilliSec + ((thisTimeWord - firstTimeWord) / 1000);
        cp->time = startTime + (msec / 1000);
        cp->msec = msec % 1000;
        cp->deltaTime = cp->timeWord - _prevTimeWord;
        cp->timeWord /= 1000;	// Store as millseconds for this probe, since this is not a 48 bit word
        totalLiveTime += checkRejectionCriteria(cp, stats);
        stats.particles.push_back(cp);
        cp = new Particle();
      }

      _prevTimeWord = thisTimeWord;

      ++stats.nTimeBars;
      stats.minBar = std::min(stats.minBar, cp->deltaTime);
      stats.maxBar = std::max(stats.maxBar, cp->deltaTime);
      continue;
    }


    if (isBlankSlice(p))
      continue;

    ++cp->w;

    checkEdgeDiodes(cp, p);
    cp->area += area(p);
    cp->h = std::max(height(p), cp->h);

    /* If the particle becomes rejected later, we need to now much time the
     * particle consumed, so we can add it to the deadTime, so sampleVolume
     * can be reduced accordingly.
     */
    cp->liveTime = (unsigned long)((float)(cp->w) * stats.frequency);

#ifdef DEBUG
  printf("%06x %zu %zu\n", cp->timeWord, cp->w, cp->h);
#endif
  }



  stats.SampleVolume *= (stats.DASelapsedTime - overload) * 0.001;
  stats.tBarElapsedtime = (_prevTimeWord - firstTimeWord);

  if (stats.nTimeBars > 0)
    stats.meanBar = stats.tBarElapsedtime / stats.nTimeBars;

  stats.tBarElapsedtime /= 1000;
  stats.frequency /= 1000;


  // Compute "science" data.
  totalLiveTime /= 1000000;     // convert to seconds

  computeDerived(sampleVolume, totalLiveTime);

  // Save time for next round.
  _prevTime = stats.thisTime;
  memcpy((char *)&_prev2dsHdr, (char *)record, sizeof(TwoDS_hdr));

  return(stats);

}	// END PROCESSRECORD

/* -------------------------------------------------------------------- */
void F2DS::ClearStats(const TwoDS_rec *record)
{
  stats.tBarElapsedtime = 0;
  stats.nTimeBars = 0;
  stats.nonRejectParticles = 0;
  stats.minBar = 10000000;
  stats.maxBar = 0;
  stats.area = 0;
  stats.duplicate = false;
  clearParticles();
//  stats.tas = (float)record->tas;
  stats.tas = 150;
  stats.frequency = Resolution() / stats.tas;
  stats.prevTime = stats.thisTime;
  stats.thisTime = (record->hour * 3600 + record->minute * 60 + record->second) * 1000 + record->msec; // in milliseconds
  memset(stats.accum, 0, sizeof(stats.accum));
}

// END TWODS.CC
