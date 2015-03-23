/*

  INScore Project - libMapping
  Copyright (C) 2009-2012  Grame

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


#ifndef __TVariety__
#define __TVariety__

#include "TInterval.h"
#include "TSegment.h"
#include "lmtools.h"

namespace libmapping
{

/*!
\addtogroup SEGMENTS Segmentations
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief variety function base class (identity function).
*/
class TVFunction { 
	public :  
		virtual double operator () (double v) const				{ return v; }
		virtual bool  operator == (const TVFunction& ) const	{ return true; }
        		~TVFunction() {}
};

/*!
	\brief a variety function in the ax+b form.
*/
template<typename T> class TAXBFunction : public TVFunction { 
	protected:
		double fA, fB;
	public :  
				  TAXBFunction() : fA(1.f), fB(0.f) {}		///< empty constructor builds the identity function
				
				 /// Computes the coefficients to go from the \a a interval to the \c b interval.
				 /// The \c b interval should be enclosed in \c a
				 TAXBFunction(const TInterval<T>& a, const TInterval<T>&b)	{
																				TInterval<T> i = a & b;
																				fA = i.size() / double(a.size());
																				fB = (i.first() - a.first()) / double(a.size());
																			 }
                 TAXBFunction(const double A, const double B){fA = A; fB = B;}
        virtual ~TAXBFunction() {}
				 
		virtual float getA() const					{ return float(fA); }		///< gives the \c a coefficient
		virtual float getB() const					{ return float(fB); }		///< gives the \c b coefficient
		virtual double operator () (double v) const { return (fA*v) + fB; }		///< applies the function to the value v
        virtual TAXBFunction<T>* invert() const     { return new TAXBFunction(1/getA(), -getB()/getA());}

		/// equality operator : actually check for coefficients equality
		virtual bool  operator == (const TAXBFunction& f) const { return (fA==f.fA) && (fB==f.fB); }
		virtual bool  near (const TAXBFunction& f) const		{ return near::check(fA, f.fA) && near::check(fB, f.fB); }
    
};

//--------------------------------------------------------------------------
/*!
	\brief variety base class.
*/
class TVariety { 
	protected :
		static TVFunction	fIdentity;
	public :  
				~TVariety() {} 
		static const TVFunction* identity()  { return &fIdentity; }
};

//--------------------------------------------------------------------------
/*!
	\brief interval variety.
*/
template<typename T> class TIntervalVariety : public TVariety
{
	protected :
		const TVFunction*	fFunction;
		TInterval<T>		fInterval;
		
	public :
				 TIntervalVariety(const TInterval<T>& i, const TVFunction* f=identity()) : fFunction(f), fInterval(i) {}
		virtual ~TIntervalVariety() {}
		
		///< Gives a location from the interval variety.
		///< According to the variety specification, we must have 0 <= loc <= 1 
		inline virtual T	get(double loc)		{ return smartdouble<T>(fInterval.first()*(1-(*fFunction)(loc)) + fInterval.second()*(*fFunction)(loc)); }
    
		///< gives the interval variety
		inline TInterval<T>	get()				{ return TInterval<T>(get(T(0)), get(T(1))); }
		
		virtual bool operator == (const TIntervalVariety<T>& v) const	{ return fFunction == v.fFunction; }
		inline const TVFunction* function() const						{ return fFunction; }
};

//--------------------------------------------------------------------------
/*!
	\brief interval variety with f = a*x+b.
*/
template<typename T> class TIntervalAXBVariety : public TVariety
{
	bool fDelete;
	protected :
		const TAXBFunction<T>*	fFunction;
		TInterval<T>		fInterval;
        TInterval<T>        fVarietyInterval;
		
	public :
				 TIntervalAXBVariety(const TInterval<T>& i, const TAXBFunction<T>* f=identity()) : fDelete(false), fFunction(f), fInterval(i) {}
				 TIntervalAXBVariety(const TInterval<T>& i, const TInterval<T>& j) : fDelete(true), fInterval(i), fVarietyInterval(j)
							{ fFunction = new TAXBFunction<T>(i,j); }
		virtual ~TIntervalAXBVariety() { if (fDelete) delete fFunction; }
		
		///< Gives a location from the interval variety.
		///< According to the variety specification, we must have 0 <= loc <= 1 
		inline virtual T	get(double loc)		{ return smartdouble<T>(fInterval.first()*(1-(*fFunction)(loc)) + fInterval.second()*(*fFunction)(loc)); }
    
		///< gives the interval variety
		inline TInterval<T>	get()				{ return TInterval<T>(get(T(0)), get(T(1))); }
		
		virtual bool operator == (const TIntervalAXBVariety<T>& v) const	{ return fFunction == v.fFunction; }
		inline const TAXBFunction<T>* function() const						{ return fFunction; }
};

//--------------------------------------------------------------------------
/*!
	\brief interval inverted variety.
*/
template<typename T> class TIntervalInvertedVariety
{
	protected :
		const TAXBFunction<T>*	fFunction;
        const TAXBFunction<T>*  fInvertedFunction;
		TInterval<T>		fInterval;
		
	public :
				 TIntervalInvertedVariety(const TInterval<T>& i, const TAXBFunction<T>* f) : fFunction(f), fInterval(i){ fInvertedFunction = f->invert();}
		virtual ~TIntervalInvertedVariety() { delete fInvertedFunction; }
		
		///< Gives a location from the interval variety.
		///< According to the variety specification, we must have 0 <= loc <= 1 
		inline virtual T	get(double loc)		{ return smartdouble<T>(fInterval.first()*(1-(*fInvertedFunction)(loc)) + fInterval.second()*(*fInvertedFunction)(loc)); }
    
		///< gives the interval variety
		inline TInterval<T>	get()				{ return TInterval<T>(get(T(0)), get(T(1))); }
		
		virtual bool operator == (const TIntervalInvertedVariety<T>& v) const	{ return fInvertedFunction == v.fInvertedFunction; }
		inline const TAXBFunction<T>* function() const						{ return fInvertedFunction; }
};

//--------------------------------------------------------------------------
/*!
	\brief segments variety.
*/
template<typename T, unsigned int D> class TSegmentVariety : public TVariety {};

//--------------------------------------------------------------------------
/*!
	\brief segments inverted variety.
*/
template<typename T, unsigned int D> class TSegmentInvertedVariety;


//--------------------------------------------------------------------------
/*!
	\brief segments inverted variety.
*/
template<typename T, unsigned int D> class TSegmentAXBVariety;


//--------------------------------------------------------------------------
/*!
	\brief 1D segments variety.
*/
template<typename T> class TSegmentVariety<T, 1>
{
	protected :
		TIntervalVariety<T>	fIntervalVar;
		
	public :
				 TSegmentVariety(const TSegment<T,1>& s, const TVFunction* f=TVariety::identity()) : fIntervalVar(s.interval(), f) {}
				 TSegmentVariety(const TSegment<T,1>& s, const TSegment<T,1>& s2) : fIntervalVar(s.interval(), s2.interval()) {}
    
		virtual ~TSegmentVariety() {}
		
		inline T				get(double loc)	{ return fIntervalVar.get(loc); }
        inline TSegment<T,1>	get()			{ return TSegment<T,1>(fIntervalVar.get()); }
		
		inline bool operator == (const TSegmentVariety<T,1>& v) const { return fIntervalVar == v.fIntervalVar; }
		inline const TVFunction* function() const						{ return fIntervalVar.function(); }
};


//--------------------------------------------------------------------------
/*!
	\brief 2D segments variety.
*/
template<typename T> class TSegmentVariety<T, 2>
{
	protected :
		TIntervalVariety<T>	fXIntervalVar;
		TIntervalVariety<T>	fYIntervalVar;
		
	public :
				 TSegmentVariety(const TSegment<T,2>& s, const TVFunction* f=TVariety::identity())
						: fXIntervalVar(s.xinterval(), f), fYIntervalVar(s.yinterval(), TVariety::identity()) {}
				 TSegmentVariety(const TSegment<T,2>& s, const TVFunction* f1, const TVFunction* f2)	
						: fXIntervalVar(s.xinterval(), f1), fYIntervalVar(s.yinterval(), f2) {}
		virtual ~TSegmentVariety() {}
		
		inline T				getx(double loc)	{ return fXIntervalVar.get(loc); }
		inline T				gety(double loc)	{ return fYIntervalVar.get(loc); }
		inline TSegment<T,2>	get()				{ return TSegment<T,2>(fXIntervalVar.get(), fYIntervalVar.get()); }
		
		inline bool operator == (const TSegmentVariety<T,2>& v) const 
				{ return (fXIntervalVar == v.fXIntervalVar) && (fYIntervalVar == v.fYIntervalVar); }

		/// gives the variety function on the \c x axis
		inline const TVFunction* xfunction() const	{ return fXIntervalVar.function(); }
		/// gives the variety function on the \c y axis
		inline const TVFunction* yfunction() const	{ return fYIntervalVar.function(); }
};


//--------------------------------------------------------------------------
/*!
	\brief 2D segments variety with f=a*x+b.
*/
template<typename T> class TSegmentAXBVariety<T, 2>
{
	protected :
		TIntervalAXBVariety<T>	fXIntervalVar;
		TIntervalAXBVariety<T>	fYIntervalVar;
		
	public :
				 TSegmentAXBVariety(const TSegment<T,2>& s, const TAXBFunction<T>* f=TVariety::identity())
						: fXIntervalVar(s.xinterval(), f), fYIntervalVar(s.yinterval(), TVariety::identity()) {}
				 TSegmentAXBVariety(const TSegment<T,2>& s, const TAXBFunction<T>* f1, const TAXBFunction<T>* f2)
						: fXIntervalVar(s.xinterval(), f1), fYIntervalVar(s.yinterval(), f2) {}
				 TSegmentAXBVariety(const TSegment<T,2>& s, const TSegment<T,2>& s2)
						: fXIntervalVar(s.xinterval(), s2.xinterval()), fYIntervalVar(s.yinterval(), s2.yinterval()) {}
		virtual ~TSegmentAXBVariety() {}
		
		inline T				getx(double loc)	{ return fXIntervalVar.get(loc); }
		inline T				gety(double loc)	{ return fYIntervalVar.get(loc); }
		inline TSegment<T,2>	get()				{ return TSegment<T,2>(fXIntervalVar.get(), fYIntervalVar.get()); }
		
		inline bool operator == (const TSegmentVariety<T,2>& v) const 
				{ return (fXIntervalVar == v.fXIntervalVar) && (fYIntervalVar == v.fYIntervalVar); }

		/// gives the variety function on the \c x axis
		inline const TAXBFunction<T>* xfunction() const	{ return fXIntervalVar.function(); }
		/// gives the variety function on the \c y axis
		inline const TAXBFunction<T>* yfunction() const	{ return fYIntervalVar.function(); }
};


//--------------------------------------------------------------------------
/*!
	\brief 2D segments inverted variety.
*/
template<typename T> class TSegmentInvertedVariety<T, 2>
{
	protected :
		TIntervalInvertedVariety<T>	fXIntervalVar;
		TIntervalInvertedVariety<T>	fYIntervalVar;
		
	public :
				 TSegmentInvertedVariety(const TSegment<T,2>& s, const TAXBFunction<T>* f1, const TAXBFunction<T>* f2)
						: fXIntervalVar(s.xinterval(), f1), fYIntervalVar(s.yinterval(), f2) {}
		virtual ~TSegmentInvertedVariety() {}
		
		inline T				getx(double loc)	{ return fXIntervalVar.get(loc); }
		inline T				gety(double loc)	{ return fYIntervalVar.get(loc); }
		inline TSegment<T,2>	get()				{ return TSegment<T,2>(fXIntervalVar.get(), fYIntervalVar.get()); }
		
		inline bool operator == (const TSegmentInvertedVariety<T,2>& v) const
				{ return (fXIntervalVar == v.fXIntervalVar) && (fYIntervalVar == v.fYIntervalVar); }

		/// gives the variety function on the \c x axis
		inline const TAXBFunction<T>* xfunction() const	{ return fXIntervalVar.function(); }
		/// gives the variety function on the \c y axis
		inline const TAXBFunction<T>* yfunction() const	{ return fYIntervalVar.function(); }
};

/*! @} */

} // end namespoace

#endif
