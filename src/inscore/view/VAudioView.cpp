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

#include <cstdlib>

#include <QFile>
#include <QDebug>
#include <QGraphicsPathItem>

#include "INScore.h"
#include "ITLError.h"
#include "VAudioView.h"
#include "VApplView.h"

namespace inscore
{

//----------------------------------------------------------------------
TAudioReader::TAudioReader()
{
	fAudioProbe = new QAudioProbe();
    connect(fAudioProbe, SIGNAL(audioBufferProbed(const QAudioBuffer&)),this, SLOT(processBuffer(const QAudioBuffer&)));
}

//----------------------------------------------------------------------
void TAudioReader::setSource (QMediaPlayer* player)
{
	if (!fAudioProbe->setSource(player))
		qDebug() << "TAudioReader::setSource FAILED: audio probe not supported";
}

//----------------------------------------------------------------------
void TAudioReader::processBuffer (const QAudioBuffer& buffer)
{
qDebug() << "TAudioReader::processBuffer frames:" << buffer.frameCount();
}


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
VAudioView::VAudioView(QGraphicsScene * scene, const IAudio* audio)
 :	VMappedShapeView( scene , new MouseEventAble<QGraphicsPathItem>(audio)), fAudio(0)
{
	fCacheW = fCacheH = 0;
}

//----------------------------------------------------------------------
void VAudioView::mediaReady() {
	fAudio->setMediaDuration(player()->duration());
	fAudio->mediaReady();
}
void VAudioView::posChanged(qint64 pos)		{ fAudio->setIDate(pos); }
void VAudioView::mediaEnd()					{ fAudio->mediaEnd(); }

//----------------------------------------------------------------------
void VAudioView::error(QString msg)
{
	ITLErr << fAudio->getOSCAddress().c_str() << "error" << msg.toStdString() << ITLEndl;
}

//----------------------------------------------------------------------
void VAudioView::initialize( IAudio * audio  )
{
	fAudio = audio;
	QString file = VApplView::toQString( audio->getPath().c_str() );
	if ( QFile::exists(  file  ) ) {
		setFile (file);
		fReader.setSource(player());
	}
}

//----------------------------------------------------------------------
void VAudioView::updateView( IAudio * audio  )
{
	audio->cleanupSync();

	updatePlayer (audio);

	float w = audio->getWidth();
	float h = audio->getHeight();
	bool sizeChanged = (fCacheW != w) || (fCacheH != h);
	if (item()->path().isEmpty() || sizeChanged || audio->newData()) {
		fCacheW = w; fCacheH = h;
		QRectF r( 0,0,  relative2SceneWidth(w),relative2SceneHeight(h) );
		QPainterPath path;
		int w = r.width()-1;
		int wfade = w / 10;			// range for fade in fade out simulation
		int x = 0;
		int h2 = r.height()/2;
		path.moveTo(x++, r.height()/2);
		for (int i = 0; i<w; i+=2) {
			int range = h2;
			if (i < wfade)				range = h2 * i / wfade;
			else if (i > (w - wfade))	range = h2 * (w - i) / wfade;
			int v = range? rand() % range : 0;
			path.lineTo(x++, h2 - v);
			path.lineTo(x++, h2 + v);
		}
		path.lineTo(x, h2);
		item()->setPath (path);
	}

	itemChanged();
	VShapeView::updateView( audio );
}


} // end namespace
