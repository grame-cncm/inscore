/*

  INScore Project
  Copyright (C) 2010  Grame

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


#ifndef __MapTools__
#define __MapTools__

#include <vector>
#include <set>

#include "rational.h"
#include "maptypes.h"
#include "TInterval.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "TMapping.h"

namespace inscore
{

/*!
\addtogroup ITLMapping Ressources mapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief tools for intervals and segments
*/
class MapTools
{
	public :
		struct Relation { 
			rational r, p; 
			Relation(rational a, rational b)	: r(a), p(b) {}
		};
		class SegmRelation : public std::vector<Relation > {};

		//--------------------------------------------------------------------------------
		// location relative position to intervals
		//--------------------------------------------------------------------------------
		/*!
			\brief gives the relative position of a location in an interval
			\param loc a location expressed in the interval coordinates
			\param i a non empty interval
			\return a double value in the interval [0, 1] when the location is included in the interval
			\warning it's the caller responsibility to check for empty intervals
		*/
		template <typename T> static rational relativepos (const T& loc, const TInterval<T>& i)				
											{ return rational(loc - i.first(), i.size()); }

		//--------------------------------------------------------------------------------
		// intervals relations and related intervals
		//--------------------------------------------------------------------------------
		/*!
			\brief gives the relation between two intervals
			\param i1 an interval
			\param i2 an interval
			\return a pair of values \c (r,p) where \c r if the ratio between the intervals 
					and \c p the relative position of \c i2 to \c i1
		*/
		template <typename T> static Relation relation(const TInterval<T>& i1, const TInterval<T>& i2)	
			{
				T w(i1.size());
				return w ? Relation( rational(i2.size(), w), relativepos(i2.first(), i1)) 
						 : Relation(0,0);
			}

		/*!
			\brief gives an interval related to another interval according to a given relation
			\param i an interval
			\param r a relation
			\return an interval related to \c i according to the relation \c r
		*/
		template <typename T>	static TInterval<T> related(const TInterval<T>& i, const Relation& r)	
			{
				T w(i.size());
				T a = T(r.p * w) + i.first();
				return TInterval<T> (a, a + T(r.r * w));
			}

		//--------------------------------------------------------------------------------
		// segments relations and related segments
		//--------------------------------------------------------------------------------
		/*!
			\brief gives the relation between two 1D segments
			\param s1 a segment
			\param s2 a segment
			\return a list of relations, one for each segment dimension
		*/
		template <typename T> SegmRelation static relation (const TSegment<T,1>& s1, const TSegment<T,1>& s2) 
			{ 
				SegmRelation r; 
				r.push_back( relation( s1.interval(), s2.interval() ) );
				return r;
			}

		/*!
			\brief gives a segment related to another segment according to a given relation 
			\param i a segment
			\param r a relations list
			\return a segment related to \c s according to the relation list \c r
		*/
		template <typename T> TSegment<T,1>	static related (const TSegment<T,1>& s, SegmRelation& r)
			{ 
				if (r.size() < 1) r.push_back(Relation(1,0));
				return TSegment<T,1> (related (s.interval(), r[0])); 
			}

		/*!
			\brief gives the relation between two 2D segments
			\param s1 a segment
			\param s2 a segment
			\return a list of relations, one for each segment dimension
		*/
		template <typename T> SegmRelation static relation (const TSegment<T,2>& s1, const TSegment<T,2>& s2) 
			{
				SegmRelation r; 
				r.push_back( relation( s1.xinterval(), s2.xinterval() ) );
				r.push_back( relation( s1.yinterval(), s2.yinterval() ) );
				return r;
			}

		/*!
			\brief gives a 2D segment related to another segment according to a given relation 
			\param s a 2D segment
			\param r a relations list
			\return a 2D segment related to \c s according to the relation list \c r
		*/
		template <typename T> TSegment<T,2>	static related (const TSegment<T,2>& s, SegmRelation& r)
			{ 
				while (r.size() < 2) r.push_back(Relation(1,0));
				return TSegment<T,2> (related (s.xinterval(), r[0]), related (s.yinterval(), r[1]));
			}

		//--------------------------------------------------------------------------------
		// segments sets union
		//--------------------------------------------------------------------------------
		template <typename T> static std::set<T> unite (const std::set<T>& s1, const std::set<T>& s2 )
		{
			std::set<T> outset;
			if (s1.size() != s2.size()) return outset;

			typedef typename std::set<T>::const_iterator const_iterator;
			const_iterator i1 = s1.begin(), i2 = s2.begin();
			while (i1 != s1.end()) {
				T  inter = *i1 & *i2;
				T  u = i1->unite(*i2, 0.00001);
				if (u.empty() || inter.size()) {
					outset.clear();
					break;
				}
				outset.insert (u);
				i1++; i2++;
			}
			return outset;
		}

		//--------------------------------------------------------------------------------
		// mapping reduction i.e. segments union when possible
		//--------------------------------------------------------------------------------
		template <typename T1, typename T2> static SMARTP<TMapping<T1,T2> > reduce (const SMARTP<TMapping<T1,T2> >& map)
		{
			SMARTP<TMapping<T1,T2> > outmap = TMapping<T1,T2>::create();
			const TRelation<T1,T2>& rel = map->direct();
			typedef typename TRelation<T1,T2>::const_iterator const_iterator;

			T1 seg;
			std::set<T2> related;
			for (const_iterator i = rel.begin(); i != rel.end(); i++) {
				if (!related.size()) {		// first time (just entering the loop)
					seg = i->first;
					related = i->second;
				}
				else {
					T1 u1 = seg.unite(i->first);
					std::set<T2> u2 = MapTools::unite (related, i->second);
					if (u1.empty() || !u2.size()) {
						outmap->add (seg, related);
						seg = i->first;
						related = i->second;
					}
					else {
						seg = u1;
						related = u2;
					}
				}
			}
			if (related.size())
				outmap->add (seg, related);
			return outmap;
		}
		

		//--------------------------------------------------------------------------------
		// segmentations intersection
		//--------------------------------------------------------------------------------
		template <typename T1, typename T2, typename T3> static void intersect (const TRelation<T1,T2>& r1, const TRelation<T1,T3>& r2, std::set<T1>& outlist)
		{
			typedef typename TRelation<T1,T2>::const_iterator const_iterator1;
			typedef typename TRelation<T1,T3>::const_iterator const_iterator2;
			for (const_iterator1 i = r1.begin(); i != r1.end(); i++) {
				for (const_iterator2 j = r2.begin(); j != r2.end(); j++) {
					T1 inter = i->first & j->first;
					if (inter.size() || (inter == i->first) || (inter == j->first))
						outlist.insert(inter);
				}
			}
		}

//		template <typename T> SMARTP<TSegmentation<T> > static intersect (const SMARTP<TSegmentation<T> >& seg1, const SMARTP<TSegmentation<T> >& seg2)
//			{
//				typedef typename TSegmentation<T>::const_iterator const_iterator;
//				const SMARTP<TSegmentation<T> > segi = TSegmentation<T>::create (seg1->getResource() & seg2->getResource());
//				if (segi->getResource().size()) {
//					for (const_iterator i = seg1->getSegmentation().begin(); i != seg1->getSegmentation().end(); i++) {
//						for (const_iterator j = seg2->getSegmentation().begin(); j != seg2->getSegmentation().end(); j++) {
//							T inter = *i & *j;
//							if (inter.size() || (inter == *i) || (inter == *j))
//								segi->add(inter);
//						}
//					}
//				}
//				return segi;
//			}


		template <typename T> RelativeTimeSegment static find (const rational& date, const TRelation<RelativeTimeSegment,T>& rel)
			{
				typedef typename TRelation<RelativeTimeSegment,T>::const_iterator const_iterator;
				for (const_iterator i = rel.begin(); i != rel.end(); i++)
					if ( i->first.interval().include(date) ) return i->first;
				return RelativeTimeSegment (rational(0), rational(0));
			}

		
//		template <typename I, typename T> static intersect (I::const_iterator s1beg, I::const_iterator s1end, 
//															I::const_iterator s2beg, I::const_iterator s2end, std::set<T>& outlist)

//		template <typename T, typename I> static void intersect (I s1beg, I s1end, I s2beg, I s2end, std::set<T>& outlist)
//			{
//				for (I i = s1beg; i != s1end; i++) {
//					for (I j = s2beg; j != s2end; j++) {
//						T inter = *i & *j;
//						if (inter.size() || (inter == *i) || (inter == *j))
//							outlist.insert(inter);
//					}
//				}
//			}
//		template <typename T, typename I> static void intermaps (I s1beg, I s1end, I s2beg, I s2end, std::set<T>& outlist)
//			{
//				for (I i = s1beg; i != s1end; i++) {
//					for (I j = s2beg; j != s2end; j++) {
//						T inter = i->first & j->first;
//						if (inter.size() || (inter == i->first) || (inter == j->first))
//							outlist.insert(inter);
//					}
//				}
//			}
//
//		template <typename T> static SMARTP<TMapping<TSegment<rational,1>, T> > translate (const SMARTP<TMapping<TSegment<rational,1>, T> >& map, const rational& date)
//			{
//				SMARTP<TMapping<TSegment<rational,1>, T> > smap =  TMapping<TSegment<rational,1>, T>::create();
//				typedef typename TRelation<TSegment<rational,1>, T>::const_iterator const_iterator;
//				
//				for (const_iterator i = map->direct().begin(); i != map->direct().end(); i++) {
//						TSegment<rational,1> shifted (i->first.interval() + date);
//						smap->add ( shifted, i->second);
//				}
//				return smap;
//			}
};


/*! @} */

} // end namespoace

#endif
