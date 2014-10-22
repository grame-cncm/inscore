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

#include <QThread>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "TFile.h"

namespace inscore
{
 
class QFileDownloader : public QThread
{
    Q_OBJECT
    
public:
    explicit QFileDownloader(QUrl Url, TFile * file);
 
    virtual ~QFileDownloader();
 
    QByteArray downloadedData() const;
    
signals:
    void downloaded();
 
private slots:
 
    void fileDownloaded(QNetworkReply* pReply);
    void update();
    
private:
 
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
    QUrl fUrl;
    TFile * fFile;
};
 
}

#endif
