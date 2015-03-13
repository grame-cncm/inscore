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

#include <QDebug>
#include <QNetworkRequest>

#include "QFileDownloader.h"
#include "INScore.h"
#include "ITLError.h"

#include "sourcefetcher.h"


namespace inscore
{

//--------------------------------------------------------------------------
QFileDownloader::QFileDownloader()
{
    connect(&fNetworkAccess, SIGNAL(finished(QNetworkReply*)), SLOT(fileDownloaded(QNetworkReply*)));
}
 
//--------------------------------------------------------------------------
QFileDownloader::~QFileDownloader()
{
    quit();
	wait(50);
}

//--------------------------------------------------------------------------
void QFileDownloader::getAsync (const char* what, const char* address)
{
    fOSCAddress = address;
	QUrl url (what);
    QNetworkRequest request(url);
    fNetworkAccess.get(request);
	start();
}

//--------------------------------------------------------------------------
bool QFileDownloader::get (const char* what)
{
	char *buff;
	int ret = http_fetch(what, &buff);
	if (ret == -1) {			// there is an error
		ITLErr << "Can't access url \"" << what << "\": " << http_strerror() << ITLEndl;
		return false;
	}
	fData = buff;
	free (buff);
	return true;
}

//--------------------------------------------------------------------------
void QFileDownloader::fileDownloaded(QNetworkReply* reply)
{
    if(!reply->error())
    {
        fData = reply->readAll();
		updateSucceded ();
    }
    else {
		ITLErr << "Can't access url: " << reply->errorString().toStdString() << ITLEndl;
		updateFailed (reply);
	}
    reply->deleteLater();
}

//--------------------------------------------------------------------------
void QFileDownloader::updateSucceded()
{
    INScore::MessagePtr msg = INScore::newMessage ("success");
	INScore::postMessage (fOSCAddress.c_str(), msg);
}

//--------------------------------------------------------------------------
void QFileDownloader::updateFailed(QNetworkReply* reply)
{
    INScore::MessagePtr msg = INScore::newMessage ("error");
 	INScore::add (msg, reply->errorString().toStdString().c_str());
	INScore::postMessage (fOSCAddress.c_str(), msg);
}


};