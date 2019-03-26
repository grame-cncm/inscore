/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale,
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#pragma once

//-------------------------------------------------------------------
template <typename T> class TFifo {

	class TFifoAble {
		TFifoAble* 	fNext;
		T*			fElt;
		public:
				 TFifoAble(T* e) : fNext(0), fElt(e) {}
		virtual ~TFifoAble() {}
		inline void 		setNext( TFifoAble* next ) 	{ fNext = next; }
		inline TFifoAble*	getNext() const				{ return fNext; }
		inline T*			element() const				{ return fElt; }
	};

	TFifoAble*	fFirst;
	TFifoAble*	fLast;

	public:
				 TFifo() { init(); }
		virtual ~TFifo() {}

		inline void 		init()		{ fFirst=0; fLast=(TFifoAble*)this; }
		inline void 		push(T* e)	{ TFifoAble* f = new TFifoAble(e); fLast->setNext(f); fLast=f; }
		inline T* 			pop()
		{
			TFifoAble* f = fFirst;
			if (f) {
				fFirst = f->getNext();
				if (!fFirst) fLast=(TFifoAble*)this;
				T* e = f->element();
				delete f;
				return e;
			}
			return 0;
		}
};
