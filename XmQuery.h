/*
-------------------------------------------------------------------------
OBJECT NAME:	XmQuery.h

FULL NAME:	Motif Query Dialog

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1997
-------------------------------------------------------------------------
*/

#ifndef XMQUERY_H
#define XMQUERY_H

#define register
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>


/* -------------------------------------------------------------------- */
class XmQuery {

public:
	XmQuery(Widget parent);
  void	QueryUser(const char str[], int maxlen, void (*callBack)());
  void	ExtractAnswer(char *s);

private:
  Widget	queryBox;

};	/* END XMQUERY.H */

#endif
