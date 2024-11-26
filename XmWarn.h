/*
-------------------------------------------------------------------------
OBJECT NAME:	XmWarn.h

FULL NAME:	Motif Warning dialog.

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef XMWARN_H
#define XMWARN_H

#define register
#include <Xm/Xm.h>
#include <Xm/MessageB.h>

/* -------------------------------------------------------------------- */
class XmWarn {

public:
  XmWarn(Widget parent, const char warning[], XtCallbackProc okCB, XtCallbackProc cancelCB);

private:
  Widget	warnBox;

};	/* END XMWARN.H */

#endif
