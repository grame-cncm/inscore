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

#include <string>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkDiskCache>
#include <QDir>

#include "QFileDownloader.h"
#include "INScore.h"
#include "ITLError.h"
#include "Tools.h"
#include "TILoader.h"

#include "sourcefetcher.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
QFileDownloader::QFileDownloader(const char* urlprefix)
{
	if (urlprefix) fUrlPrefix = urlprefix;
}
 
//--------------------------------------------------------------------------
QFileDownloader::~QFileDownloader()
{
	if(fReply)
		fReply->deleteLater();
}

//--------------------------------------------------------------------------
std::string	QFileDownloader::location(const char * file)
{
	if (!Tools::isurl(file))
		return TILoader::makeAbsolutePath( fUrlPrefix, file );
	else
		return file;
}

//--------------------------------------------------------------------------
void QFileDownloader::getAsync (const char* what, const char* address)
{
	fOSCAddress = address;
	QUrl url (location(what).c_str());
    QNetworkRequest request(url);
	request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferNetwork);
	fReply = NetworkAccess::instance()->qNetAccess().get(request);
	QObject::connect(fReply, &QNetworkReply::finished, [this](){this->fileDownloaded();});
}

//--------------------------------------------------------------------------
bool QFileDownloader::get (const char* what)
{
	char *buff;
	int ret = http_fetch(location(what).c_str(), &buff);
	if (ret == -1) {			// there is an error
		ITLErr << "Can't access url \"" << what << "\": " << http_strerror() << ITLEndl;
		return false;
	}
	fData = buff;
	free (buff);
	return true;
}

//--------------------------------------------------------------------------
void QFileDownloader::fileDownloaded()
{
	if(!fReply->error())
    {
		fData = fReply->readAll();
		updateSucceded ();
    }
    else {

		///TODO better implementation of force loading from cache if error
		if(fReply->request().attribute(QNetworkRequest::CacheLoadControlAttribute) != QNetworkRequest::AlwaysCache){
			QNetworkRequest request = fReply->request();
			request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysCache);
			fReply->deleteLater();

			fReply = NetworkAccess::instance()->qNetAccess().get(request);
			QObject::connect(fReply, &QNetworkReply::finished, [this](){this->fileDownloaded();});
			ITLErr << "Url not accessible, trying to load ressource from cache..." << ITLEndl;
			return;
		}

		ITLErr << "Can't access url: " << fReply->errorString().toStdString() << ITLEndl;
		updateFailed ();
	}
	fReply->deleteLater();
	fReply = 0;

}

//--------------------------------------------------------------------------
void QFileDownloader::updateSucceded()
{
//	emit downloaded();
	INScore::MessagePtr msg = INScore::newMessage ("success");
	INScore::postMessage (fOSCAddress.c_str(), msg);
}

//--------------------------------------------------------------------------
void QFileDownloader::updateFailed()
{
//	emit failed(reply);
    INScore::MessagePtr msg = INScore::newMessage ("error");
	INScore::add (msg, fReply->errorString().toStdString().c_str());
	INScore::postMessage (fOSCAddress.c_str(), msg);
}



/***********************************************************
 *                    NetworkAccess                        *
 **********************************************************/

NetworkAccess* NetworkAccess::gNetworkAccess = 0;

NetworkAccess *NetworkAccess::instance()
{
	if(!gNetworkAccess)
		gNetworkAccess = new NetworkAccess();

	return gNetworkAccess;
}


//__________________________________________________

NetworkAccess::NetworkAccess()
{
	QNetworkDiskCache *cache = new QNetworkDiskCache(&fNetworkAccessManager);

	//Create temporary folders
	bool tmpCreated = true;
	QDir tmp = QDir::temp();
	if(!tmp.exists("INScore"))
		if(!tmp.mkdir("INScore")){
			//Impossible to create temporary folder
			ITLErr<<"Creation of temporary folder is impossible, URL cache won't be available."<<ITLEndl;
			tmpCreated = false;
		}
	if(tmpCreated){
		tmp.cd("INScore");
		cache->setCacheDirectory(tmp.absolutePath());
		fNetworkAccessManager.setCache(cache);
	}
}

void NetworkAccess::clearCache()
{
	fNetworkAccessManager.cache()->clear();
}




};  //end namespace
