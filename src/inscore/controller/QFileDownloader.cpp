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
	fReply = 0;
}
 
//--------------------------------------------------------------------------
QFileDownloader::~QFileDownloader()
{
	if(fReply)
		delete fReply;
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
	fReply = NetworkAccess::instance()->get(request);
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

const char* QFileDownloader::getCachedAsync(const char *urlString, std::function<void ()> cbUpdate, std::function<void ()> cbFail)
{
	//Asynchronously update the cache
	QUrl url(urlString);
	QNetworkRequest request(url);
	fReply = NetworkAccess::instance()->get(request);

	std::function<void()> cb = [this, cbUpdate, cbFail, &cb, urlString]()
								{
									if(fReply->error() || !fReply->bytesAvailable()){
										//URL download failed
										if(!handleError(cb)){
											ITLErr << "Can't access url \"" << urlString << "\": " << fReply->errorString().toStdString() << ITLEndl;
											fReply->deleteLater();
											fReply = 0;
											cbFail();
										}
									}else
										if(!fReply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool()){
											//Cache wasn't up to date
											fReply->deleteLater();
											fReply = 0;
											cbUpdate();
										}
								};

	//Sending an error message if download failed or callback cbUpdate if the cache was updated
	QObject::connect(fReply, &QNetworkReply::finished, cb);

	//Retreiving the actual value stored in the cache (before the asynchronous update)
	QNetworkDiskCache* cache = NetworkAccess::instance()->cache();

	QIODevice* data = cache->data(url);

	if(data){
		char* d = new char[data->bytesAvailable()];
		strcpy(d, data->readAll().data());
		data->deleteLater();

		return d;
	}
	return 0;
}


//--------------------------------------------------------------------------
void QFileDownloader::fileDownloaded()
{
	QByteArray data = fReply->readAll();
	if(!fReply->error() && !data.isEmpty())
    {
		fData = data;
		updateSucceded ();
    }
    else {
		if( !handleError([this](){fileDownloaded();}) ){
			ITLErr << "Can't access url: " << fReply->errorString().toStdString();
			if(fReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt())
				ITLErr << "[Error " << fReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << "]";
			ITLErr << ITLEndl;
			updateFailed ();
		}
	}

}

//--------------------------------------------------------------------------
bool QFileDownloader::handleError(std::function<void ()> cbFinished)
{
	qDebug()<<"HEADERS: ";
	qDebug()<<fReply->rawHeaderPairs();

	//Test for redirection
	QUrl newUrl = fReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
	if(!newUrl.isEmpty() && fReply->rawHeaderList().contains("Location"))
		newUrl = QUrl(fReply->header(QNetworkRequest::LocationHeader).toString());

	if(!newUrl.isEmpty()){
			//Redirection needed
		if(newUrl == fReply->url()){
			ITLErr<< "URL redirection failed: "<<newUrl.toString().toStdString()<<ITLEndl;
			return false;
		}

		fReply->deleteLater();

		fReply = NetworkAccess::instance()->get(QNetworkRequest(newUrl));
		QObject::connect(fReply, &QNetworkReply::finished, [cbFinished]{cbFinished();});
		return true;
	}

	if(fReply->request().attribute(QNetworkRequest::CacheLoadControlAttribute) != QNetworkRequest::AlwaysCache){
			//If network error try to load from cache

		QNetworkRequest request = fReply->request();
		request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysCache);
		fReply->deleteLater();

		fReply = NetworkAccess::instance()->get(request);
		QObject::connect(fReply, &QNetworkReply::finished, [cbFinished]{cbFinished();});
		ITLErr << "Url not accessible, trying to load ressource from cache..." << ITLEndl;
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------
void QFileDownloader::updateSucceded()
{
//	emit downloaded();
	INScore::MessagePtr msg = INScore::newMessage ("success");
	INScore::postMessage (fOSCAddress.c_str(), msg);
	fReply->deleteLater();
	fReply = 0;
}

//--------------------------------------------------------------------------
void QFileDownloader::updateFailed()
{
//	emit failed(reply);
    INScore::MessagePtr msg = INScore::newMessage ("error");
	INScore::add (msg, fReply->errorString().toStdString().c_str());
	INScore::postMessage (fOSCAddress.c_str(), msg);
	fReply->deleteLater();
	fReply = 0;
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

QNetworkReply *NetworkAccess::get(const QNetworkRequest &request)
{
	QNetworkRequest r = request;
	r.setRawHeader("User-Agent", "INScore");
	return fNetworkAccessManager.get(r);
}


//__________________________________________________

NetworkAccess::NetworkAccess()
{
	fCache = new QNetworkDiskCache(&fNetworkAccessManager);

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
		fCache->setCacheDirectory(tmp.absolutePath());
		fNetworkAccessManager.setCache(fCache);
	}
}

NetworkAccess::~NetworkAccess()
{
	delete fCache;
}

void NetworkAccess::clearCache()
{
	fCache->clear();
}




};  //end namespace
