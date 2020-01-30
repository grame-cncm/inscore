/*
  INScore Project

  Copyright (C) 2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#pragma once

/**
*	\brief An interface to support the MusicXML format.
*/
class XMLImporter
{
	public:
		/// musicxml library : functions prototypes
		typedef int (* musicxml2guido)(const char *file, bool generateBars, std::ostream& out);
		typedef const char* (* musicxmlversion)();

		/// \return true when the conversion methods are available
		virtual bool musicxmlSupported() 			{ return false; }

		/// \return the musicxml lib version as a string
		virtual const char* musicxmlVersion() 		{ return 0; }

		/// \return the musicxml to guido converter version as a string
		virtual const char* musicxml2guidoVersion() { return 0; }

		/*! \brief converts a musicxml file to guido
		
			\param file the musicxml file name
			\param generateBars a boolean to force or inhibit measures bar generation
			\param out the output stream
			\return true when the conversion is successful
		*/
		virtual bool musicxmlFile2Guido   (const char *file, bool generateBars, std::ostream& out) { return false; }

		/*! \brief converts a musicxml string to guido
		
			\param str the musicxml string
			\param generateBars a boolean to force or inhibit measures bar generation
			\param out the output stream
			\return true when the conversion is successful
		*/
		virtual bool musicxmlString2Guido (const char *str, bool generateBars, std::ostream& out) { return false; }
};
