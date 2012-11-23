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

#include "IGuidoCode.h"
#include "Updater.h"
#include "IMessage.h"
#include "IMessageHandlers.h"
#include "GUIDOEngine.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
const string IGuidoCode::kGuidoCodeType("gmn");

//--------------------------------------------------------------------------
IGuidoCode::IGuidoCode( const std::string& name, IObject * parent ) :
	IObject (name, parent) , fGRHandler(0), fPage(1), fPageFormat( 21.0f, 29.7f ), fPageCount(0),
	fNbOfPageColumns(2), fNbOfPageRows(1)
{
	fLocalMappings = TLocalMapping<rational,1>::create();

	fTypeString = kGuidoCodeType;

	fMsgHandlerMap["page"]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setPage);
	fMsgHandlerMap["dpage"]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setdPage);
	fMsgHandlerMap["pageFormat"]	= TSetMethodMsgHandler<IGuidoCode,TFloatSize>::create(this, &IGuidoCode::setPageFormat);
	fMsgHandlerMap["columns"]		= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setNbOfPageColumns);
	fMsgHandlerMap["rows"]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setNbOfPageRows);
	fMsgHandlerMap["map"]			= TMethodMsgHandler<IGuidoCode>::create(this, &IGuidoCode::mapMsg);

	fGetMsgHandlerMap["page"]		= TGetParamMsgHandler<int>::create(fPage);
	fGetMsgHandlerMap["pageCount"]	= TGetParamMsgHandler<int>::create(fPageCount);
	fGetMsgHandlerMap["pageFormat"]	= TGetParamMsgHandler<TFloatSize>::create(fPageFormat);
	fGetMsgHandlerMap["columns"]	= TGetParamMsgHandler<int>::create(fNbOfPageColumns);
	fGetMsgHandlerMap["rows"]		= TGetParamMsgHandler<int>::create(fNbOfPageRows);
	fGetMsgHandlerMap[""]			= TGetParamMsgHandler<std::string>::create(fGMN);

	requestMapping("");
}

//--------------------------------------------------------------------------
void IGuidoCode::accept (Updater* u)
{
	u->updateTo (SIGuidoCode(this));
}

//--------------------------------------------------------------------------
void IGuidoCode::setdPage( int dpage )
{ 
	int page = fPage + dpage;
	if (page < 1) page = 1;
	else if (page > fPageCount) page = fPageCount;
	if (fPage != page) {
		fPage = page;
		localMapModified(true); 
	}
}

//--------------------------------------------------------------------------
void IGuidoCode::print (ostream& out) const
{
	IObject::print (out);
	out << " GMN: " << getGMN() << endl;
	out << " page: " << getPage() << endl;
	out << " pageFormat: [" << getPageFormat().width() << " ; " << getPageFormat().height() << "]" << endl;
	out << " columns/rows: [" << getNbOfPageRows() << "/" << getNbOfPageColumns() << "]" << endl;
}

//--------------------------------------------------------------------------
rational IGuidoCode::getPageDate(int pagenum) const
{
	if (fGRHandler) {
		GuidoDate date;
		GuidoGetPageDate( fGRHandler, pagenum, &date);
		return rational (date.num, date.denom);
	}
	return rational(-1,1);
}

//--------------------------------------------------------------------------
void IGuidoCode::requestMapping(const std::string& mapName)
{
	for ( unsigned int i = 0 ; i < fRequestedMappings.size() ; i++ )
		if ( fRequestedMappings[i] == mapName )
			return;

	fRequestedMappings.push_back( mapName );
}

//--------------------------------------------------------------------------
void IGuidoCode::stopRequestMapping(const std::string& mapName)
{
	std::vector<std::string>::iterator i;
	for ( i = fRequestedMappings.begin() ; i != fRequestedMappings.end() ; i++ )
		if ( (*i) == mapName )
		{
			fRequestedMappings.erase( i );
			return;
		}
}

// message handling
//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoCode::set ( const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	if (msg->params().size() == 2) {
		const std::string err = "";
		string t = msg->params()[1]->value<std::string>(err);
		if ( t != getGMN() ) {
			setGMN( t );
			status = MsgHandler::kProcessed;
			newData(true);
		}
		else status = MsgHandler::kProcessedNoChange;

	}
	else status = MsgHandler::kBadParameters;
	return status;
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoCode::mapMsg (const IMessage* msg )
{
	if (msg->params().size() >= 1)
	{
		string mapName = msg->params()[0]->value<std::string>("");
		if ( mapName.size() )
		{
			bool doDel = false;
			// - "del" string can be first parameter, meaning "delete no-named mapping".
			if ( mapName == "del" )
			{
				doDel = true;
				mapName = "";
			}
			// - or "del" be second parameter, meaning "delete 'mapName' mapping".
			else if ( (msg->params().size() == 2) && ( msg->params()[1]->value<std::string>("") == "del" ) )
				doDel = true;

			if ( doDel )
			{
				stopRequestMapping( mapName );
				localMappings()->remove( mapName );
				removeMapping( mapName );
				return MsgHandler::kProcessed;
			}
			else
			{
				if (msg->params().size() == 2)	// 2 parameters but no "del" => error.
					return MsgHandler::kBadParameters;
				else
				{
					requestMapping(mapName);
					localMapModified(true);
					return MsgHandler::kProcessed;
				}
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
IMessageList IGuidoCode::getMsgs(const IMessage* msg) const
{
	IMessageList outMsgs;
	for ( unsigned int i = 0 ; i < msg->params().size() ; i++ )
	{
		string param = msg->params()[i]->value<string>("-");
		if ( param == "map" )
		{
			for ( std::vector<string>::const_iterator i = fRequestedMappings.begin() ; i != fRequestedMappings.end() ; i++ )
			{
				IMessage* msg = new IMessage(getOSCAddress(), "map");
				*msg << (*i);
				outMsgs += msg;
			}
			break;
		}
		else if ( param == "pageDate" )
		{
			i++;
			int pagenumber;
			if (i < msg->params().size() && msg->param(i, pagenumber) && (pagenumber <= fPageCount)) {
				IMessage* msg = new IMessage(getOSCAddress(), param);
				*msg << pagenumber << getPageDate(pagenumber);
				outMsgs += msg;
			}
		}
	}
	outMsgs += IObject::getMsgs(msg);
	return outMsgs;
}

}
