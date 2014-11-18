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

#include "QFileDownloader.h"
#include "VObjectView.h"

namespace inscore
{

//--------------------------------------------------------------------------
QFileDownloader::QFileDownloader(QUrl Url, IUrlIntermediateObject * temp) : QThread()
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), SLOT(fileDownloaded(QNetworkReply*)));
    connect(this, SIGNAL(downloaded()), SLOT(update()));
    fTempUrl = temp;
    QNetworkRequest request(Url);
    m_WebCtrl.get(request);
}
 
//--------------------------------------------------------------------------
QFileDownloader::~QFileDownloader()
{
    quit(), wait(50);
}
 
//--------------------------------------------------------------------------
void QFileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    if(!pReply->error())
        m_DownloadedData = pReply->readAll();
    else
        ITLErr << pReply->errorString().toStdString() << ITLEndl;
    pReply->deleteLater();
    emit downloaded();
}
 
//--------------------------------------------------------------------------
QByteArray QFileDownloader::downloadedData() const
{
    return m_DownloadedData;
}

//--------------------------------------------------------------------------
void QFileDownloader::update()
{
    fTempUrl->updateFile();
}


};