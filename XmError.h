/*
-------------------------------------------------------------------------
OBJECT NAME:	XmError.h

FULL NAME:	Motif Error dialog.

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef XMERROR_H
#define XMERROR_H

#define register
#include <Xm/Xm.h>
#include <Xm/MessageB.h>


/* -------------------------------------------------------------------- */
class XmError {

public:
  XmError(Widget parent, const char str[]);

private:
  Widget	errorBox;

};	/* END XMERROR.H */

#endif
