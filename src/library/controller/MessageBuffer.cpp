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

#include <algorithm>
#include "MessageBuffer.h"
#include "ITLError.h"

using namespace std;
namespace inscore
{

//________________________________________________________________________
MessageBuffer::MessageBuffer()
{
	fWritePos = fReadPos = 0;
	fBuffSize = 0;
	fBuffer = 0;
}

//________________________________________________________________________
MessageBuffer::~MessageBuffer()
{
	delete[] fBuffer;
}

//________________________________________________________________________
void MessageBuffer::write (SIMessage* msg)
{
	unsigned short w = pos2index(fWritePos);
	unsigned short r = pos2index(fReadPos) - 1;
	if (w == r) {
		ITLErr << "Message buffer overflow: an incoming OSC message has been lost" << ITLEndl;
	}
	else {
		fBuffer[w] = msg;
		fWritePos++;
	}
}

//________________________________________________________________________
bool MessageBuffer::resize (unsigned short size)
{
	if (size < fBuffSize) return false;
	if (size == fBuffSize) return true;


	SIMessage** newBuffer = new SIMessage*[size];
	if (!newBuffer) return false;		// memory allocation failed

	for (int i=0; i<fBuffSize; i++) newBuffer[i] = fBuffer[i];

	SIMessage** oldBuffer = fBuffer;
	fBuffer = newBuffer;			// sets the new buffer pointer
	delete[] oldBuffer;
	fBuffSize = size;				// sets the new size
	return true;
}

}
