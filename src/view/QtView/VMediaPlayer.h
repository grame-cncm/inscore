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


#ifndef __VMediaPlayer__
#define __VMediaPlayer__

#include <QMediaPlayer>
#include <QString>


class QGraphicsVideoItem;

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class IMedia;
//--------------------------------------------------------------------------
/**
*	\brief a generic media player, used to play video and audio files
*/
class VMediaPlayer: public QObject
{
    Q_OBJECT
	public :
				 VMediaPlayer();
		virtual ~VMediaPlayer() { fMediaPlayer.stop(); }

	protected:
			QMediaPlayer* player()		{ return &fMediaPlayer; }

	virtual void connectVideo(QGraphicsVideoItem* v);		// used for native size change notifications

	virtual void mediaReady()			{}		// method called when the media is ready
	virtual void mediaEnd()				{}		// method called when the player reaches the end of the media
	virtual void posChanged(qint64 pos)	{}		// method called when the player position changes
	virtual void sizeChanged(const QSizeF & size) {}
	virtual void error(QString msg) {}

	virtual void setFile( const QString&  mediaFile );
	virtual void updatePlayer( const IMedia * media  );

	protected slots:
		void	error (QMediaPlayer::Error error);
		void	mediaStatusChanged (QMediaPlayer::MediaStatus status);
		void	stateChanged (QMediaPlayer::State state);
		void	seekableChanged(bool seekable);
		void	nativeSizeChanged(const QSizeF & size);
		void	durationChanged(qint64 duration);
		void	positionChanged(qint64 position);

	protected:
		int							fReady;

	private:
		QMediaPlayer				fMediaPlayer;
		QMediaPlayer::MediaStatus	fStatus;
};


/*!@} */

} // end namespoace

#endif
