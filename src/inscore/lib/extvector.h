#ifndef __extvector__
#define __extvector__

/*
	Interlude Library
	Copyright (C) 2012  Grame

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

 */

#include <ostream>
#include <string>
#include <vector>

namespace inscore
{

template <typename T> class extvector : public std::vector<T>
{
	std::string fPrefix;
	std::string fSuffix;
	
	public:
				 extvector() : fSuffix(", ") {}
		virtual ~extvector() {}

		void  set (const char* prefix, const char* suffix) {
			fPrefix = prefix;
			fSuffix = suffix;
		}
	
		void  print (std::ostream& out) const {
			for (unsigned int i=0; i < this->size()-1; i++)
				out << fPrefix << (*this)[i] << fSuffix;
			out << fPrefix << (*this)[this->size()-1];
		}
	
		// specific method to print messages list
		// could be called with different type provided it supports the print interface
		void  printMsgs (std::ostream& out) const {
			int n = int(this->size()-1);
			if (n >= 0) {
				for (int i=0; i < n; i++) {
					out << fPrefix;
					(*this)[i]->print(out, 1, ",");
					out << fSuffix;
				}
				out << fPrefix;
				(*this)[n]->print(out, 1, ",");
			}
		}

		void push_back( const extvector<T>& l) {
			for (unsigned int i=0; i < l.size(); i++)
				std::vector<T>::push_back(l[i]);
		}
		void push_back( extvector<T>& l) {
			for (unsigned int i=0; i < l.size(); i++)
				std::vector<T>::push_back(l[i]);
		}
		void push_back( const extvector<T>* l) {
			for (unsigned int i=0; i < l->size(); i++)
				std::vector<T>::push_back((*l)[i]);
		}
		void push_back( extvector<T>* l) {
			for (unsigned int i=0; i < l->size(); i++)
				std::vector<T>::push_back((*l)[i]);
		}
		void push_back( const T& val) {
			std::vector<T>::push_back(val);
		}
		void push_back( T& val) {
			std::vector<T>::push_back(val);
		}
};

template <typename T> std::ostream& operator << (std::ostream& out, const extvector<T>& l)
{
	l.print (out);
	return out;
}

}

#endif
