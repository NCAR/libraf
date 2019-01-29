// Helper functions.

#include "OAP.h"
#include "portable.h"


/* -------------------------------------------------------------------- */
void OAP::swapPMS2D(OAP::P2d_rec *buff)
{
  // Perform byte swapping on whole [data] record if required.
  if (1 != ntohs(1))
  {
//    uint32_t            *p;
    unsigned short      *sp = (unsigned short *)buff;

    for (int i = 1; i < 10; ++i)
      sp[i] = ntohs(sp[i]);

   if (OAP::probeType((unsigned char *)buff) == OAP::TWODS_T)
    {
      unsigned char tmp[16], *cp = (unsigned char *)buff->data;
      // 256 slices at 16 bytes each.
      for (size_t i = 0; i < OAP::nSlices_128bit; ++i, cp += 16)
      {
        for (size_t j = 0; j < 16; ++j)
          tmp[j] = cp[15-j];
        memcpy(cp, tmp, 16);
      }
    }
    else
    if (OAP::probeType((unsigned char *)buff) == OAP::HVPS_T)
    {
      sp = (unsigned short *)buff->data;
      for (size_t i = 0; i < 2048; ++i, ++sp)
        *sp = ntohs(*sp);
    }
  }
}


/* -------------------------------------------------------------------- */
OAP::ProbeType OAP::probeType(const unsigned char *id)
{
  if (id[0] == 'C' || id[0] == 'P')
  {
    if (id[1] >= '4' && id[1] <= '7')
      return OAP::FAST2D_T;

    if (id[1] == '8')
      return OAP::CIP_T;

    return OAP::PMS2D_T;
  }

  if (id[0] == '2' || id[0] == '3' || id[0] == 'S')
    return OAP::TWODS_T;

  if (id[0] == 'H')
    return OAP::HVPS_T;

  if (id[0] == 'G')
    return OAP::GREYSCALE_T;

  return OAP::UNKNOWN_T;
}
