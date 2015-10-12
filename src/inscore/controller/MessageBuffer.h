/*
  Copyright (C) 2005  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License 
  as published by the Free Software Foundation; either version 2.1 
  of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License 
  along with this library; if not, write to the Free Software Foundation, 
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __MessageBuffer__
#define __MessageBuffer__

#include "smartpointer.h"

namespace inscore
{
	
/*!
 \addtogroup ITLCtrl Controller
 @{
 */

class IMessage;
typedef libmapping::SMARTP<IMessage>		SIMessage;

//________________________________________________________________________
/*!
\brief a Message buffer to manage Messages storage

	The RingBuffer object automatically wrap the read and write indexes.
	It's the client responsability to check for overrun and underrun. 
	The \c available() method is provided both for getting the count of available data 
	and for overrun and underrun checking, indicated by an available data count
	greater than the buffer size or less than 0.
	
	Available data are fetched using the [] operator which expects indexes in the range
	\c [0,n[ where \c n is the count of available data. In case \c n is outside this range, 
	the ring buffer reads the available data in loop.
	
	When done with the new data, the \c done() method should be called to reset the
	count of available data to 0.	
*/
class MessageBuffer  {
		
    public:
				 MessageBuffer();
        virtual ~MessageBuffer();
		
		/*!   initializes the Message buffer
			\param size the total size of the Message buffer in frames.
		*/
		bool	resize (unsigned short size);
		
		//!   gives the Message buffer size
		unsigned short	size () const					{ return fBuffSize; }

		//!   gives the count of available data from the Message buffer
		int		available()	const						{ return  fWritePos - fReadPos; }

		//! writes a float value to the Message buffer
		void	write (SIMessage* msg);

		/// \brief read the signal data at an index \c n
		/// \param n an index that should be less than the buffer size
		virtual SIMessage* read()						{ return (fReadPos < fWritePos) ? fBuffer[pos2index(fReadPos++)] : 0; }

    private:
		unsigned long	fWritePos, fReadPos;   ///< the read and write positions
		unsigned short  fBuffSize;
		SIMessage**		fBuffer;
		
		unsigned short  pos2index (unsigned long pos) const	{ return (unsigned short)(pos % fBuffSize); }
};

/*! @} */

}

#endif

