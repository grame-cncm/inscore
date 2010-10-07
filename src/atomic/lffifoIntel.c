/*

  Copyright © Grame 2001-2005

  This library is free software; you can redistribute it and modify it under 
  the terms of the GNU Library General Public License as published by the 
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/


#include "lffifo.h"

#define fifo_end(ff)	(fifocell *)ff

//----------------------------------------------------------------
void fifoinit (fifo* ff)
{
	ff->count.value = 0;
	ff->oc = ff->ic = 0;
	ff->dummy.link = fifo_end(ff);
	ff->head = ff->tail = &ff->dummy;
}


//----------------------------------------------------------------
unsigned long fifosize (fifo * ff)
{
    return ff->count.value;
}

//----------------------------------------------------------------
void fifoput (fifo * ff, fifocell * cl) 
{
    long ic;
	fifocell * volatile tail;

	cl->link = fifo_end(ff);	/* set the cell next pointer to the end marker */
	while (1) {
		ic = ff->ic;			/* read the tail modification count */
		tail = ff->tail;		/* read the tail cell */
		/* try to link the cell to the tail cell */
        if (CAS (&tail->link, fifo_end(ff), cl))
			break;
		else
		/* tail was not pointing to the last cell, try to set tail to the next cell */
            CAS2 (&ff->tail, tail, ic, tail->link, ic+1);
	} 
    /* enqeue is done, try to set tail to the enqueued cell */
	CAS2 (&ff->tail, tail, ic, cl, ic+1);
	msAtomicInc (&ff->count);
}

//----------------------------------------------------------------
fifocell *  fifoget(fifo * ff) 
{
	fifocell * volatile head;
	fifocell * next; 
	unsigned long ic, oc;
	short done = 0;
	
	do {
		oc = ff->oc;					/* read the head modification count */
		ic = ff->ic;					/* read the tail modification count */
		head = ff->head;				/* read the head cell */
		next = head->link;				/* read the next cell */
		if (oc == ff->oc) {				/* ensures that next is a valid pointer */
                                        /* to avoid failure when reading next value */
			if (head == ff->tail) {			/* is queue empty or tail falling behind? */
				if (next == fifo_end(ff))	/* is queue empty?             */
					return 0;				/* queue is empty; return NULL */
                /* tail is pointing to head in a non empty queue, */
                /* try to set tail to the next cell               */
				CAS2 (&ff->tail, head, ic, next, ic+1);
			}
			else if (next != fifo_end(ff)) { /* if we are not competing on the dummy cell */
                /* and we try to set head to the next cell */
				done = CAS2 (&ff->head, head, oc, next, oc+1);
			}
		}
	} while (!done);
	msAtomicDec (&ff->count);
	if (head == &ff->dummy) {
		fifoput(ff,head);
		head = fifoget(ff);
	}
	return (fifocell *)head;
}

//----------------------------------------------------------------
/*	fifoavail returns a pointer to the "first" cell in the fifo
	if it is not empty. This is meaningful if there is only one
	reader for the fifo. The pointer returned may actually be the 
	second cell of the fifo to skip the dummy cell.
	It ensures that : fifoavail(ff) == fifoget(ff)
*/
fifocell* fifoavail (fifo* ff) 
{
	/* simulated atomic read of the required fields*/
	while (1) {
		unsigned long count = ff->oc;
		fifocell * 	hd  = ff->head;
		fifocell*	n   = hd->link;
		fifocell*	tail= ff->tail;
		
		if ((hd == ff->head) && (count == ff->oc)) {
			/*	no cells were removed during reading, therefore
				we have coherent (but maybe outdated) data*/
			return (hd==tail) ? 0 : (hd==&ff->dummy) ? n : hd;
		}
	}
	return 0;	/* never used !*/
}

//----------------------------------------------------------------
fifocell* fifoflush (fifo* ff) 
{
	fifocell	*next, *cur;
	fifocell* first;
	if (ff->head==0) return 0;	
	
	first = fifoget(ff);
	if (first==0) return 0;	
	cur = first;	
	while ((next = fifoget(ff))) {
		cur->link = next;
		cur = next;
	}
	cur->link = 0;
	return first;
}

