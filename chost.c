/*
-------------------------------------------------------------------------
OBJECT NAME:	chost.c

FULL NAME:	Compute Host

ENTRY POINTS:	SetComputeHost()
		GetComputeHost()

STATIC FNS:	none

DESCRIPTION:	

INPUT:		

OUTPUT:		

REFERENCES:	none

REFERENCED BY:	WINDS/windComm/winput

COPYRIGHT:	University Corporation for Atmospheric Research, 1995
-------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

#include "constants.h"

static char ComputeHost[SYS_NMLN];	/* name of host running WINDS	*/
 
/* -------------------------------------------------------------------- */
int SetComputeHost()
{
  int rc;
  struct utsname name;
 
  ComputeHost[0] = '\0';

  if ((rc = uname(&name)) == ERROR)
    perror("uname");
  else
    {
    strcpy(ComputeHost, name.nodename);
    if (strchr(ComputeHost, '.'))
      *(strchr(ComputeHost, '.')) = '\0';
    }

  return rc;
}
 
/* -------------------------------------------------------------------- */
char *GetComputeHost()
{
  return ComputeHost;
}

/* END CHOST.C */
