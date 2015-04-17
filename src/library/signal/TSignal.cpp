/*
 
 INScore Project
 Copyright (C) 2009,2010  Grame
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 
 Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
 research@grame.fr
 
 */


#include "TSignal.h"

namespace inscore
{

//--------------------------------------------------------------------------
void ParallelSignal::done ()	
{ 
	for (int i = 0; i < dimension(); i++)
		signal(i)->done();
}

//--------------------------------------------------------------------------
void ParallelSignal::reset ()	
{ 
	for (int i = 0; i < dimension(); i++)
		signal(i)->reset();
}

//--------------------------------------------------------------------------
void ParallelSignal::fix ()	
{ 
	for (int i = 0; i < dimension(); i++)
		signal(i)->fix();
}

//--------------------------------------------------------------------------
SParallelSignal	ParallelSignal::getProjection (int index, int step, int limit) const
{
	SParallelSignal outSig = ParallelSignal::create();
	if (outSig) {
		if (index < dimension())
			*outSig << signal(index);
		if (step) {
			if (!limit) limit = dimension();
			for (index += step; index < limit; index += step)
				*outSig << signal(index);
		}
	}
	return outSig;
}
//--------------------------------------------------------------------------
void ParallelSignal::put(const std::vector<float>& values)
{
	int d = dimension();
	if (d) {
		int i = 0;
		int size = values.size();
		while (true) {
			for (int s=0; s < d; s++) {
				if (i < size) *signal(s) << values[i++];
				else return;	// done with values
			}
		}
	}
}

//--------------------------------------------------------------------------
bool ParallelSignal::xrun ()	
{ 
	bool result = false;
	for (int i = 0; i < dimension(); i++) {
		int avail = signal(i)->available();
		result &= (avail < 0) || (avail > signal(i)->size());
	}
	return result;
}

//--------------------------------------------------------------------------
void ParallelSignal::setDefaultValue(const std::vector<float>& values)
{
	for ( int i = 0 ; i < dimension() ; i++ )
		signal(i)->defaultValue(values[i]);
}

//--------------------------------------------------------------------------
void ParallelSignal::defaultValue(std::vector<float>& outVal) const
{
	for ( int i = 0 ; i < dimension() ; i++ )
		outVal.push_back( signal(i)->defaultValue() );
}

//--------------------------------------------------------------------------
int	ParallelSignal::size() const
{
	int result = 0;
	for (int i = 0; i < dimension(); i++) {
		int size = signal(i)->size();
		if (size > result) result = size;
	}
	return result;
}

//--------------------------------------------------------------------------
bool ParallelSignal::size(unsigned short n)
{
	for (int i = 0; i < dimension(); i++) {
		if (!signal(i)->size(n)) 
			return false;
	}
	return true;
}

//--------------------------------------------------------------------------
int ParallelSignal::available ()	const	
{ 
	int count=0; 
	for (int i = 0; i < dimension(); i++) {
		int n = signal(i)->available();
		if (n > count) count = n;
	}
	return count; 
}

//--------------------------------------------------------------------------
ParallelSignal& ParallelSignal::operator << (const STSignal& sig)	
{ 
	fSignals.push_back(sig); 
	return *this; 
}

//--------------------------------------------------------------------------
ParallelSignal& ParallelSignal::operator << (float value)
{ 
	fSignals.push_back(ConstTSignal::create(value)); 
	return *this;
}
	
} // end namespace

