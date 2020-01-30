/*

  INScore Project

  Copyright (C) 2014  Grame

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

#include "IMusicXMLCode.h"
#include "Updater.h"
#include "IMessage.h"
#include "IMessageHandlers.h"
#if !defined(NOVIEW) && !defined(MODELONLY)
#include "QGuidoImporter.h"
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
const string IMusicXMLCode::kMusicXMLCodeType("musicxml");

//--------------------------------------------------------------------------
IMusicXMLCode::IMusicXMLCode( const std::string& name, IObject * parent ) : IGuidoCode (name, parent)
{
	fTypeString = kMusicXMLCodeType;
}

//--------------------------------------------------------------------------
void IMusicXMLCode::accept (Updater* u)
{
	u->updateTo (SIMusicXMLCode(this));
}

//--------------------------------------------------------------------------
bool IMusicXMLCode::convert (const string& xml, string& converted) const
{
#if !defined(NOVIEW) && !defined(MODELONLY)
    std::stringstream sstr;
	if ( QGuidoImporter::musicxmlString2Guido ( xml.c_str(), true, sstr) ) {
		converted = sstr.str();
		return true;
	}
#endif
	return false;
}

// message handling
//--------------------------------------------------------------------------
MsgHandler::msgStatus IMusicXMLCode::set ( const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

#if defined(NOVIEW) || defined(MODELONLY)
	if (true) {
#else
	if (!QGuidoImporter::musicxmlSupported()) {
#endif
		ITLErr << "MusicXML import is not available" << ITLEndl;
		return MsgHandler::kCreateFailure;
	}

	string t;
	if ((msg->size() == 2) && msg->param(1, t)) {
		if ( t != getMusicXML() ) {
			string converted;
																// first convert musicxml to guido
//			if ( QGuidoImporter::musicxmlString2Guido ( t.c_str(), true, converted) ) {
			if ( convert ( t, converted) ) {
				setGMN( converted );
				status = MsgHandler::kProcessed;
				newData(true);
			}
			else {
				ITLErr << "Cannot convert MusicXML code" << ITLEndl;
				status = MsgHandler::kBadParameters;
			}
		}
		else status = MsgHandler::kProcessedNoChange;

	}
	else status = MsgHandler::kBadParameters;
	return status;
}


//--------------------------------------------------------------------------
//SIMessageList IGuidoCode::getMsgs(const IMessage* msg) const
//{
//	SIMessageList outMsgs = IMessageList::create();
//	for ( int i = 0 ; i < msg->size() ; i++ )
//	{
//		string param = "-";
//		msg->param(i, param);
//		if ( param == kmap_GetSetMethod )
//		{
//			for ( std::vector<string>::const_iterator i = fRequestedMappings.begin() ; i != fRequestedMappings.end() ; i++ )
//			{
//				SIMessage msg = IMessage::create(getOSCAddress(), kmap_GetSetMethod);
//				*msg << (*i);
//				outMsgs->list().push_back (msg);
//			}
//			break;
//		}
//		else if ( param == "pageDate" )
//		{
//			i++;
//			int pcount = getPageCount();
//			int pagenumber;
//			if (i < msg->size() && msg->param(i, pagenumber) && (pagenumber <= pcount)) {
//				SIMessage msg = IMessage::create(getOSCAddress(), param);
//				*msg << pagenumber << getPageDate(pagenumber);
//				outMsgs->list().push_back (msg);
//			}
//		}
//	}
//	outMsgs->list().push_back (IObject::getMsgs(msg)->list());
//	return outMsgs;
//}

}
