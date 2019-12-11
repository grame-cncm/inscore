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


#pragma once

#include <QByteArray>

#include "FileDownloader.h"

class QNetworkReply;

namespace inscore
{

class QFileDownloader : public FileDownloader
{
	public:
				 QFileDownloader(const char* urlprefix = 0);
		virtual ~QFileDownloader();
	 
		/// \brief asynchronous download of an url
		void	getAsync (const char* url, const char* address) override;

		/// \brief synchronous download of an url
		bool	get (const char* url) override;

		/*!
		 * \brief synchronously return the cached value of an url, while asynchronously update the cache and triggering a callback if it changed
		 * \param url url from which the value is read
		 * \param cbUpdate callback function triggered asynchronously if the cache is updated
		 * \param cbFail callback function triggered asynchronously if the download fails
		 * \return the actual data stored in the cache
		 */
		 const char* getCachedAsync(const char *url, std::function<void()> cbUpdate, std::function<void()> cbFail = []{}) override;

		virtual int			dataSize() const override	{ return fData.size(); }
		virtual const char*	data() const override		{ return fData.data(); }
		QByteArray&			byteArray()					{ return fData; }
	 
	private:
	 
		void fileDownloaded();
		bool handleError(bool &success, const std::function<void ()> &cbFinished);

		void updateSucceded();
		void updateFailed();

		void cbCachedASync(const std::function<void ()> &cbUpdate, const std::function<void ()> &cbFail);

		void printErrors() const;
		
	private:
		std::string				location(const char * file);

		QString					fInitialURL;
		QNetworkReply*			fReply;
		QByteArray				fData;
		std::string				fOSCAddress;
		std::string				fUrlPrefix;
};
 
} // end namespace
