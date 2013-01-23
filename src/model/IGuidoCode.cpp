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

	fMsgHandlerMap[kpage_GetSetMethod]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setPage);
	fMsgHandlerMap[kdpage_SetMethod]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setdPage);
	fMsgHandlerMap[kpageFormat_GetSetMethod]	= TSetMethodMsgHandler<IGuidoCode,TFloatSize>::create(this, &IGuidoCode::setPageFormat);
	fMsgHandlerMap[kcolumns_GetSetMethod]		= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setNbOfPageColumns);
	fMsgHandlerMap[krows_GetSetMethod]			= TSetMethodMsgHandler<IGuidoCode,int>::create(this, &IGuidoCode::setNbOfPageRows);
	fMsgHandlerMap[kmap_GetSetMethod]			= TMethodMsgHandler<IGuidoCode>::create(this, &IGuidoCode::mapMsg);

	fGetMsgHandlerMap[kpage_GetSetMethod]		= TGetParamMsgHandler<int>::create(fPage);
	fGetMsgHandlerMap[kpageCount_GetMethod]		= TGetParamMsgHandler<int>::create(fPageCount);
	fGetMsgHandlerMap[kpageFormat_GetSetMethod]	= TGetParamMsgHandler<TFloatSize>::create(fPageFormat);
	fGetMsgHandlerMap[kcolumns_GetSetMethod]	= TGetParamMsgHandler<int>::create(fNbOfPageColumns);
	fGetMsgHandlerMap[krows_GetSetMethod]		= TGetParamMsgHandler<int>::create(fNbOfPageRows);
	fGetMsgHandlerMap[""]						= TGetParamMsgHandler<std::string>::create(fGMN);

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

	string t;
	if ((msg->size() == 2) && msg->param(1, t)) {
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
	string mapName;
	if ((msg->size() >= 1) && msg->param(0, mapName))
	{
		if ( mapName.size() )
		{
			bool doDel = false;
			// - "del" string can be first parameter, meaning "delete no-named mapping".
			if ( mapName == kdel_SetMethod )
			{
				doDel = true;
				mapName = "";
			}
			// - or "del" be second parameter, meaning "delete 'mapName' mapping".
			else if ( (msg->size() == 2) && ( msg->param(1)->value<std::string>("") == kdel_SetMethod ) )
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
				if (msg->size() == 2)	// 2 parameters but no "del" => error.
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
SIMessageList IGuidoCode::getMsgs(const IMessage* msg) const
{
	SIMessageList outMsgs = IMessageList::create();
	for ( int i = 0 ; i < msg->size() ; i++ )
	{
		string param = "-";
		msg->param(i, param);
		if ( param == kmap_GetSetMethod )
		{
			for ( std::vector<string>::const_iterator i = fRequestedMappings.begin() ; i != fRequestedMappings.end() ; i++ )
			{
				SIMessage msg = IMessage::create(getOSCAddress(), kmap_GetSetMethod);
				*msg << (*i);
				outMsgs->list().push_back (msg);
			}
			break;
		}
		else if ( param == "pageDate" )
		{
			i++;
			int pagenumber;
			if (i < msg->size() && msg->param(i, pagenumber) && (pagenumber <= fPageCount)) {
				SIMessage msg = IMessage::create(getOSCAddress(), param);
				*msg << pagenumber << getPageDate(pagenumber);
				outMsgs->list().push_back (msg);
			}
		}
	}
	outMsgs->list().push_back (IObject::getMsgs(msg)->list());
	return outMsgs;
}

}
