/*
-------------------------------------------------------------------------
OBJECT NAME:	queue.c

FULL NAME:	

ENTRY POINTS:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1995
-------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "raf_queue.h"

char *GetMemory(size_t);

/* -------------------------------------------------------------------- */
Queue *CreateQueue()
{
	Queue	*qp;

	qp = (Queue *)GetMemory(sizeof(Queue));

	qp->head = qp->tail = NULL;

	return(qp);

}	/* END CREATEQUEUE */

/* -------------------------------------------------------------------- */
void EnQueue(Queue *q, void *datum)
{
	struct dat	*dp;

	dp = (struct dat *)GetMemory(sizeof(struct dat));
	dp->datum = datum;
	dp->next = NULL;

	if (q->tail != NULL)
		q->tail->next = dp;

	q->tail = dp;

	if (q->head == NULL)
		q->head = dp;

}	/* END ENQUEUE */

/* -------------------------------------------------------------------- */
void *FrontQueue(Queue *q)
{
	if (q && q->head)
		return(q->head->datum);
	else
		return(NULL);

}	/* END FRONTQUEUE */

/* -------------------------------------------------------------------- */
void *DeQueue(Queue *q)
{
	struct dat	*dp;
	void		*datum;

	dp = q->head;
	datum = dp->datum;

	q->head = dp->next;

	if (q->head == NULL)
		q->tail = NULL;

	free(dp);

	return(datum);

}	/* END DEQUEUE */

/* END QUEUE.C */
