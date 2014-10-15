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
#include <qpixmap.h>
#include <qdebug.h>

namespace inscore
{

//--------------------------------------------------------------------------
QFileDownloader::QFileDownloader(const QUrl &downloadUrl, const QDir &storageLocation) : QObject(), mStorageLocation(storageLocation), mDownloadUrl(downloadUrl)
{
    fView = 0;
    beginDownload();
}
 
//--------------------------------------------------------------------------
void QFileDownloader::beginDownload()
{
    // Make our strings for the File
    QString downloadFileName = QFileInfo(mDownloadUrl.path()).fileName();
    QString absoluteFileAddress = mStorageLocation.path() + "/" + downloadFileName;
    pFile = new QFile(absoluteFileAddress);
    
    // Check if we have the file open for writing
    if (!pFile->open(QIODevice::WriteOnly))
    {
        // Delete file
        if (pFile)
        {
            delete pFile;
            pFile = NULL;
        }
        return; // Break, failed
    }
 
    // Get the data from our request on the URL
    pNetworkReply = mNetworkManager.get(QNetworkRequest(mDownloadUrl));
    
    // Setup signals/slots
    connect(pNetworkReply, SIGNAL(finished()), this, SLOT(downloadFinished()));
    connect(pNetworkReply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
}
 
 
//--------------------------------------------------------------------------
void QFileDownloader::downloadFinished()
{
    // Make sure everything is written before we continue
    downloadReadyRead();
    pFile->flush();
    pFile->close();
 
    pNetworkReply->deleteLater(); // Very important that we use deleteLater()!
    pNetworkReply = NULL;
 
    delete pFile;
    pFile = NULL;
 
    emit fileDownloadFinished();
 
}
 
//--------------------------------------------------------------------------
void QFileDownloader::downloadReadyRead()
{
    // If pFile exists, dump all reply data to disk to save memory
    if (pFile)
    {
        pFile->write(pNetworkReply->readAll());
    }
}

//--------------------------------------------------------------------------
void QFileDownloader::updateImage()
{
    VImageView * imgView = fView ? dynamic_cast<VImageView*>(fView) : 0;
    if(imgView)
        imgView->setImage();
}

};