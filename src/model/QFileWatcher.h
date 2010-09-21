/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __QFileWatcher__
#define __QFileWatcher__

#include "IFileWatcher.h"
#include <QObject>
#include <QMultiMap>

class QFileSystemWatcher;

namespace interlude
{

/*!
\addtogroup ITLView
@{
*/

class QFileWatcher;
typedef class SMARTP<QFileWatcher>	SQFileWatcher;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IText.
*/
class QFileWatcher: public QObject, public IFileWatcher
{
	Q_OBJECT

	QFileSystemWatcher* mWatcher;

	QMultiMap<QString,IMessage>	mFilesMap;	// fileName -> msg map.

	public:
		
		static SQFileWatcher create(IObject * parent) { return new QFileWatcher(parent); }

	protected:
	
		QFileWatcher(IObject * parent);
		virtual ~QFileWatcher();
	
		/*! \brief IFileWatcher implementation */
		virtual void add(const WatcherAssociation& association);
		/*! \brief IFileWatcher implementation */
		virtual void remove(const WatcherAssociation& association);
		/*! \brief IFileWatcher implementation */
		virtual void remove(const std::string& oscAddress);
		/*! \brief IFileWatcher implementation */
		virtual void clear();		
			
		virtual void getList(std::vector<WatcherAssociation>& outAssociations) const;

	protected slots:
		void fileChangedSlot(const QString& fileName);

};

/*!@} */

} // end namespoace

#endif
