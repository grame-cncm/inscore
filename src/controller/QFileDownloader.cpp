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
#include "INScore.h"

namespace inscore
{

//--------------------------------------------------------------------------
QFileDownloader::QFileDownloader(QUrl Url, const char* address) : QThread()
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), SLOT(fileDownloaded(QNetworkReply*)));
    connect(this, SIGNAL(downloaded()), SLOT(updateSucceded()));
    connect(this, SIGNAL(failed(QNetworkReply*)), SLOT(updateFailed(QNetworkReply*)));
    fOSCAddress = address;
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
    {
        m_DownloadedData = pReply->readAll();
        emit downloaded();
    }
    else
    {
        emit failed(pReply);
    }
    pReply->deleteLater();
}
 
//--------------------------------------------------------------------------
QByteArray QFileDownloader::downloadedData() const
{
    return m_DownloadedData;
}

//--------------------------------------------------------------------------
void QFileDownloader::updateSucceded()
{
    INScore::MessagePtr msg = INScore::newMessage ("success");
	INScore::postMessage (fOSCAddress.c_str(), msg);
}

//--------------------------------------------------------------------------
void QFileDownloader::updateFailed(QNetworkReply* pReply)
{
    INScore::MessagePtr msg = INScore::newMessage ("error");
    const char* s = pReply->errorString().toStdString().c_str();
	INScore::add (msg, s);
	INScore::postMessage (fOSCAddress.c_str(), msg);
}


};