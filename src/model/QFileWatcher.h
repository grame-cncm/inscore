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


#ifndef __QFileWatcher__
#define __QFileWatcher__

#include "IFileWatcher.h"
#include <QObject>
#include <QMultiMap>
#include <QFileSystemWatcher>

class QFileSystemWatcher;

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class QFileWatcher;
typedef class libmapping::SMARTP<QFileWatcher>	SQFileWatcher;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IText.
*/
class QFileWatcher: public QObject, public IFileWatcher
{
	Q_OBJECT

	QFileSystemWatcher fWatcher;
//	QMultiMap<QString, SIMessage>	mFilesMap;	// fileName -> msg map.

	public:
		static SQFileWatcher create(IObject * parent) { return new QFileWatcher(parent); }

	protected:
				 QFileWatcher(IObject * parent);
		virtual ~QFileWatcher()		{}
	
		/// \brief overrides IFileWatcher method
		virtual void set (const std::string& file, SIMessageList );
		/// \brief overrides IFileWatcher method
		virtual void add (const std::string& file, SIMessageList );
		/// \brief overrides IFileWatcher method
		virtual void clear (const std::string& file);
		/// \brief overrides IFileWatcher method
		virtual void clear();
		
	private:
		bool contains (const QString& filename);

	protected slots:
		void fileChangedSlot(const QString& fileName);

};

/*!@} */

} // end namespoace

#endif
