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


#ifndef __TSignal__
#define __TSignal__

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "RingBuffer.h"
#include "smartpointer.h"

namespace inscore
{
	
/*!
 \addtogroup ITLSignal Graphic signals
 @{
 */

class TSignal;
typedef libmapping::SMARTP<TSignal> STSignal;
//--------------------------------------------------------------------------
/*!
 \brief a simple signal base class 
 */
class TSignal : virtual public libmapping::smartable
{
	protected:
		std::string	fName;				///< the signal name
		RingBuffer	fData;				///< the signal data ring buffer
		float		fDefault;			///< a default value used when requested data is not available

				 TSignal(std::string name, unsigned short size, float def) : fName(name), fDefault(def) { fData.initialize(size);}
		virtual ~TSignal() {}
	
	public :
		static STSignal create(std::string name, unsigned short size, float def=0)	{ return new TSignal(name, size, def); }
		
		//!   done with available data
		const std::string&	name() const						{ return fName; }
		
		bool	isConst() const									{ return (size() == 1); }
		
		//!   done with available data
		void	done()											{ fData.done(); }
		
		//!   fix potential overrun issue
		void	fix()											{ fData.fix(); }
				
		/// \brief the signal buffer size
		virtual unsigned short size() const						{ return fData.size(); }

		/*! \brief sets the signal buffer size
		*/
		virtual bool size(unsigned short n)						{ return fData.initialize(n); }
		
		//!   reset the signal to no data state
		virtual void	reset()									{ fData.reset(); }

		/*! \brief sets the signal default value
		*/
		virtual void defaultValue(float val)					{ fDefault = val; }

		/*! \brief query the signal default value
		*/
		virtual float defaultValue() const						{ return fDefault; }

		/// \brief adds data
		/// \param value a float value
		virtual TSignal&  operator << (float value)				{ fData.write(value); return *this; }

		/// \brief gives the signal available data count
		virtual int available ()	const						{ return fData.available(); }

		//! gives all the signal data
		std::vector<float>	dump () const						{ return fData.dump(); }

		/// \brief get the signal data
		/// \param n an index into the signal data buffer
		/// \note when the index is larger than the available data, the default value is returned
		virtual float operator[](int n)	const					{ return ((unsigned)n < fData.wpos()) ? fData.read(n): fDefault; }

		/// \brief get the signal data
		/// \param n an index into the signal data buffer
		/// \note when the index is larger than the available data, the default value is returned
		virtual float get(int n) const							{ return ((unsigned)n < fData.wpos()) ? fData.read(n) : fDefault; }

		/// \brief signals comparison based on signal size
		/// \param sig a signal
		virtual bool  operator < (const TSignal& sig)			{ return size() < sig.size(); }
};

class		 ConstTSignal;
typedef libmapping::SMARTP<ConstTSignal> SConstTSignal;

//--------------------------------------------------------------------------
/*!
   \brief a simple signal optimized for constants  
 */
class ConstTSignal : public TSignal
{
	protected:
				 ConstTSignal(float value) : TSignal("", 1, value) {} // const signal have no name
		virtual ~ConstTSignal() {}
	
	public :
		static SConstTSignal create(float value)			{ return new ConstTSignal(value); }				
		/// \brief catch buffer size changes for constant signals
		virtual bool size(unsigned short n)				{ return true; }
		/// \brief changes the signal value
		virtual TSignal&  operator << (float value)		{ fDefault = value; return *this; }
		/// \brief gives the signal value
		virtual float operator[](int n)	const			{ return TSignal::fDefault; }
};


class ParallelSignal;
typedef libmapping::SMARTP<ParallelSignal>			SParallelSignal;
//--------------------------------------------------------------------------
/*!
 \brief a parallel signal 
 
      A parallel signal puts signals in parallel.
	  It is actually a vector of Signal and the value of a parallel signal
	  at time \c t is the vector of the values of its enclosed signals at \c t
 */
class ParallelSignal : virtual public libmapping::smartable
{
	protected:
		typedef	std::vector<STSignal> SigList;

		SigList fSignals;
		
	public :

				 ParallelSignal() {}
		virtual ~ParallelSignal() {}
	
		static SParallelSignal create()				{ return new ParallelSignal(); }		
		const SigList&	signalList() const			{ return fSignals; }
		const STSignal&	signal(int i) const			{ return signalList()[i]; }
			  STSignal	signal(int i)				{ return signalList()[i]; }

		/*! \brief the signal buffer size
			
			A parallel signal buffer size is the size of the largest enclosed signal.
		*/
		virtual int	size() const;

		/*! \brief sets the signal default value
		*/
		virtual void setDefaultValue(const std::vector<float>& val);

		/*! \brief gets the signal default value
		*/
		virtual void defaultValue(std::vector<float>& outVal) const;

		/*! \brief sets the signals buffer size
		*/
		virtual bool size(unsigned short n);

		/*! \brief gives the signal available data count
		
			the available data of a parallel signal is the max of the available data
			of the enclosed signals
		*/
		virtual int available ()	const;
		
		//!   clear the enclosed signals list
		virtual void	clear()								{ fSignals.clear(); }
		
		//!   reset the enclosed signals to no data state
		virtual void	reset();
		
		//!   done with available data
		virtual void	done();
		
		//!   fix potential overrun issue
		virtual void	fix();
		
		//!   check for potential x-run
		virtual bool	xrun();

		/* \brief the signal dimension
			
			The dimension of a parallel signal represents the number of parallelized signals i.e.
			the signals vector size.
		*/
		virtual int	dimension() const						{ return fSignals.size(); }

		/*! \brief write data to enclosed signals			
			\param values a vector of float values

			Values are distributed in sequence and in a loop to each signal.
		*/
		virtual void put(const std::vector<float>& values);

		/*! \brief the signal value at an index \c n			
			\param n an index into the signal buffer
			\return a frame value of type \c C

			Gives the signal value as an arbitrary type \c C, provided that \c C implements 
			a constructor taking a float vector as argument.
		*/
		template <typename C> C get(int n) const	{
														std::vector<float> value;
														for (int i = 0; i < dimension(); i++)
															value.push_back((*signal(i))[n]);
														return C(value);
													}

		/*! \brief the signal value at an index \c n
			\param n an index into the the signal buffer
			The value of a parallel signal is the vector of the parallelized signals values.
		*/
		std::vector<float> operator[] (int n) const		{ return get<std::vector<float> > (n); }


		/*! \brief gives the projection of a signal
			\param index the projeciton start index
			\param step the projection step
			\return a Parallel signal containing the projected signals
		*/
		virtual SParallelSignal	getProjection (int index, int step=0, int limit=0) const;

		/*! \brief adds a Signal to the parallel signal
			\param sig a Signal
		*/
		ParallelSignal& operator << (const STSignal& sig);

		/*! \brief adds a ConstSignal to the parallel signal
			\param value the ConstSignal value
		*/
		ParallelSignal& operator << (float value);

		/*! \brief adds a ParallelSignal to the parallel signal
			\param sig a ParallelSignal
		*/
		template <typename C> ParallelSignal& operator << (const libmapping::SMARTP<C>& sig) {
														for (int i = 0; i < sig->dimension(); i++)
															this->operator << (sig->signalList()[i]);
														return *this;
													}
};



/*! @} */
	
} // end namespace

#endif
