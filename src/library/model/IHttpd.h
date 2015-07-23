/*

  INScore Project

  Copyright (C) 2015  Grame

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

#ifndef IHTTPD_H
#define IHTTPD_H

#include <string>
#include "IObject.h"

namespace inscore
{

class IHttpd;
typedef class libmapping::SMARTP<IHttpd>	SIHttpd;

class WebApi;
class HTTPDServer;

//--------------------------------------------------------------------------
/*!
 * \brief The IHttpd class. a Http server object.
 */
class IHttpd : public IObject
{
	public:
		static const std::string kIHttpdType;

	protected:
		IHttpd(const std::string &name, IObject *parent);

	public:
		static SIHttpd create(const std::string& name, IObject * parent)	{ return new IHttpd(name, parent); }

		SIMessageList getSetMsg () const;

		/*!
		 * \brief set
		 * \param msg Message must contain the server http port.
		 * \return
		 */
		MsgHandler::msgStatus set (const IMessage* msg);


		std::string status() const;

		/*!
		 * \brief ~IHttpd Delete plugin instance.
		 */
		virtual ~IHttpd();
	
		void	del();
		void	stop();

	private :
		/*!
		 * \brief fHttpdServer HttpServer instance.
		 */
		HTTPDServer * fHttpdServer;

		/*!
		 * \brief fApi Web api object to execute action from server
		 */
		WebApi * fApi;

		/*!
		 * \brief fHttpPort Http port used by the server.
		 */
		int fHttpPort;

		/*!
		 * \brief init Create the plugin instance and start the http server on port fHttpPort
		 * \return true if server is running.
		 */
		bool init(int port);

};

} // end namespoace

#endif // IHTTPD_H
