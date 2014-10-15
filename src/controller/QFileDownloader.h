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


#ifndef __INScore__QFileDownloader__
#define __INScore__QFileDownloader__

#include "VImageView.h"
#include <iostream>
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDir>


namespace inscore
{


class QFileDownloader : public QObject
{
    Q_OBJECT
 
public:
    QFileDownloader(const QUrl &downloadUrl, const QDir &storageLocation);
 
    QFileDownloader() : QObject() {}
 
    inline QFile* file() const { return pFile; }
    
    inline void setView(VObjectView * v) { fView = v; }
 
signals:
    void fileDownloadFinished();
 
public slots:
    void beginDownload();
    void downloadFinished();
    void downloadReadyRead();
    void updateImage();
 
private:
    QFile *pFile;
    QDir mStorageLocation;
    QUrl mDownloadUrl;
 
    QNetworkReply *pNetworkReply;
    QNetworkAccessManager mNetworkManager;
    
    VObjectView * fView;
};

}

#endif
