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

#include "QFileWatcher.h"

#include "ITLError.h"
#include "INScore.h"

#include <QFile>
#include <QStringList>
#include <QtDebug>

namespace inscore
{

//----------------------------------------------------------------------
QFileWatcher::QFileWatcher(IObject * parent) : IFileWatcher(parent)
{
	connect( &fWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChangedSlot(const QString&)) );
}

//----------------------------------------------------------------------
bool QFileWatcher::contains (const QString& filename)
{
	return fWatcher.files().contains (filename);
}

//----------------------------------------------------------------------
void QFileWatcher::set (const std::string& filename, SIMessageList msgs)
{
	QString qfile (filename.c_str());
	if (!QFile::exists( qfile )) return;

	if (!contains (qfile)) fWatcher.addPath( qfile );
	IFileWatcher::set(filename, msgs);
}

//----------------------------------------------------------------------
void QFileWatcher::add (const std::string& filename, SIMessageList msgs)
{
	QString qfile (filename.c_str());
	if (!QFile::exists( qfile )) return;

	if (!contains (qfile)) fWatcher.addPath( qfile );
	IFileWatcher::add(filename, msgs);
}

//----------------------------------------------------------------------
void QFileWatcher::clear (const std::string& filename)
{
	fWatcher.removePath( filename.c_str() );
	IFileWatcher::clear(filename);
}

//----------------------------------------------------------------------
void QFileWatcher::clear()
{
	if (fWatcher.files().size())
		fWatcher.removePaths (fWatcher.files() );
	IFileWatcher::clear();
}

//----------------------------------------------------------------------
void QFileWatcher::fileChangedSlot(const QString& filename)
{	
	// The file has changed (modified, renamed, deleted)
	if ( QFile::exists( filename ) )
		list().trigger (filename.toStdString());
	else
	{
		// The file has been removed or renamed.
		ITLErr << name() << ": can't find file: " << filename.toStdString() << ITLEndl;	
		fWatcher.removePath( filename );
	}
}

} // end namespoace
