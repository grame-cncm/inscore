/*

  Copyright © Grame 1999-2005

  This library is free software; you can redistribute it and modify it under 
  the terms of the GNU Library General Public License as published by the 
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
 
*/

#ifndef __lffifo__
#define __lffifo__

/*****************************************************************
 *****************************************************************
                       LOCK FREE FIFO STACK 

 Implements a lock-free shared FIFO stack made of a list of cells
 linked together. A cell can be anything provided it starts with
 a pointer available to link together the cells of the stack. 
 
 ****************************************************************
                          OPERATIONS
 ****************************************************************


 void 	       	fifoinit(fifo* ff, fifocell * dummy);
 unsigned long 	fifosize (fifo * ff);
 void 	       	fifoput (fifo * ff, fifocell * cl);
 fifocell * 	fifoget (fifo * ff);
 fifocell * 	fifoavail (fifo * ff); 
 fifocell * 	fifoflush (fifo * ff);
 fifocell * 	fifoclear (fifo * ff);

 Warning : all operations expect non-null lifo and cell pointers.
 It is the caller responsability to check the arguments !
 *****************************************************************
 *****************************************************************/

#include "msAtomic.h"

/*****************************************************************
                           DATA STRUCTURES
 *****************************************************************/
#ifndef __ppc__
# define ffCount(name) unsigned long volatile name
#else
# define ffCount(name) long name[7]
#endif

typedef struct fifocell {
	struct fifocell* volatile link;	/* next cell in the list */
	void * msg;						/* a msg pointer */
	long unused[2];					/* padding */
	fifocell(void * m=0) : msg(m) {}
} fifocell;

typedef struct fifo {
	fifocell * volatile head;	/* pointer to the head cell */
	ffCount(oc);
    fifocell * volatile tail;	/* pointer to the tail cell */
	ffCount(ic);
	TAtomic	count;
	fifocell dummy;
} fifo;


#ifdef __cplusplus
extern "C" {
#endif

 void 	       	fifoinit(fifo* ff);
 unsigned long 	fifosize (fifo * ff);
 void 	       	fifoput (fifo * ff, fifocell * cl);
 fifocell * 	fifoget (fifo * ff);
 fifocell * 	fifoavail (fifo * ff); 
 fifocell * 	fifoflush (fifo * ff);

#ifdef __cplusplus
}
#endif


#endif
