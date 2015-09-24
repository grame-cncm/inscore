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
#include <iostream>
using namespace std;

#include "RingBuffer.h"

using namespace std;
namespace inscore
{

//________________________________________________________________________
RingBuffer::RingBuffer() 
{
	fWritePos = fReadPos = 0;
	fBuffSize = 0;
	fBuffer = 0;
}

//________________________________________________________________________
RingBuffer::~RingBuffer() 
{
	delete fBuffer;
}

//________________________________________________________________________
vector<float> RingBuffer::dump () const 
{
	vector<float> data;
	unsigned int pos = (fWritePos > fBuffSize) ? fWritePos - fBuffSize : 0;
	while (pos < fWritePos)
		data.push_back(fBuffer[pos2index(pos++)]);
	return data;
}

//________________________________________________________________________
bool RingBuffer::initialize (unsigned short size) 
{
	if (size == fBuffSize) return true;

	float * newBuffer = new float[size];
	if (!newBuffer) return false;		// memory allocation failed

//	for (short i=0; i<size; i++) 
//		newBuffer[i] = 0;				// initializes the buffer data to 0
//
//	if (fBuffer ) {						// when there is an existing buffer		
//		int readpos = max(0, int(fWritePos - min(size,fBuffSize)));	// prepare to transfert size data
//		int i = 0;
//		while (readpos < fWritePos) {
//			newBuffer[i++] = fBuffer[pos2index(readpos++)];
//		}
//		fReadPos = fWritePos - i;
//	}
//	else {
//		fWritePos = 0;
//		fReadPos = 0;
//	}

	delete fBuffer;
	fBuffer = newBuffer;			// sets the new buffer pointer
	fBuffSize = size;				// sets the new size
	fWritePos = 0;
	fReadPos = 0;
	return true;
}

}
