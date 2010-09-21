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

#include "QFileWatcher.h"

#include "ITLError.h"
#include "interlude.h"

#include <QFileSystemWatcher>
#include <QFile>
#include <QStringList>

#include <QtDebug>

namespace interlude
{

//----------------------------------------------------------------------
QFileWatcher::QFileWatcher(IObject * parent) : IFileWatcher(parent)
{
	mWatcher = new QFileSystemWatcher();

	connect( mWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChangedSlot(const QString&)) );
}

//----------------------------------------------------------------------
QFileWatcher::~QFileWatcher()
{
	delete mWatcher;
}

//----------------------------------------------------------------------
void QFileWatcher::add(const WatcherAssociation& association)
{
	if ( QFile::exists( association.mFileName.c_str() ) )
	{
		if ( !mFilesMap.contains(association.mFileName.c_str() , association.mMessage) )
		{
			mWatcher->addPath( association.mFileName.c_str() );
			mFilesMap.insert( association.mFileName.c_str() , association.mMessage );
		}
		else
		{
/*
			const char* msg = "fileWatcher: 'add': file already being watched :";
			std::cerr << msg << fileName << std::endl;
			oscerr << OSCWarn() << msg << fileName << OSCEnd();
*/
		}
	}
	else ITLErr << "fileWatcher: 'add': file doesn't exists: " << association.mFileName << ITLEndl;
}

//----------------------------------------------------------------------
void QFileWatcher::remove(const WatcherAssociation& association)
{
	if ( mFilesMap.contains( association.mFileName.c_str() , association.mMessage ) )
	{
		mFilesMap.remove( association.mFileName.c_str() , association.mMessage );

		if ( !mFilesMap.contains( association.mFileName.c_str() ) )
			mWatcher->removePath( association.mFileName.c_str() );
	}
	else
	{
/*
		const char* msg = "fileWatcher: 'remove': file";
		const char* msg2 = "wasn't being watched by :"; 
		std::cerr << msg << fileName << msg2 << oscAddress << std::endl;
		oscerr << OSCWarn() << msg << fileName << msg2 << oscAddress << OSCEnd();
*/
	}
}

//----------------------------------------------------------------------
void QFileWatcher::remove(const std::string& oscAddress)
{

	QMultiMap<QString,IMessage>::iterator i = mFilesMap.begin();
	while ( i != mFilesMap.end() )
	{
		if ( i.value().address() == oscAddress )
			i  = mFilesMap.erase(i);
		else
			i++;
	}
}

//----------------------------------------------------------------------
void QFileWatcher::clear()
{
	mFilesMap.clear();
	while ( mWatcher->files().size() )
		mWatcher->removePath( mWatcher->files()[0] );
}

//----------------------------------------------------------------------
void QFileWatcher::fileChangedSlot(const QString& fileName)
{	
	if ( QFile::exists( fileName ) )
	{
		// The file contents have changed
		QList<IMessage> messages = mFilesMap.values( fileName );
		for ( int i = 0 ; i < messages.size() ; i++ )
		{
			IMessage * msg = new IMessage( messages[i] );
			Interlude::postMessage( msg->address().c_str() , msg );
		}
		mWatcher->removePath( fileName );
		mWatcher->addPath( fileName );
	}
	else
	{
		// The file has been removed or renamed.	
		ITLErr << "fileWatcher: can't find file: " << fileName.toAscii().data() << ITLEndl;
	
		mWatcher->removePath( fileName );
		mFilesMap.remove( fileName );
	}
}

//----------------------------------------------------------------------
void QFileWatcher::getList(std::vector<WatcherAssociation>& outAssociations) const
{
	for ( QMultiMap<QString,IMessage>::const_iterator i = mFilesMap.begin() ; i != mFilesMap.end() ; i++ )
		outAssociations.push_back( WatcherAssociation( i.key().toAscii().data() , i.value() ) );
}

} // end namespoace
