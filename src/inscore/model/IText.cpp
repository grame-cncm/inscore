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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <sstream>
#include <map>

#include "IAppl.h"
#include "IText.h"
#include "IMessage.h"
#include "Tools.h"
#include "Updater.h"
#include "VObjectView.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string IText::kTextType("txt");

// Font style and font weight constants
const string IText::kStyleNormal("normal");
const string IText::kStyleItalic("italic");
const string IText::kStyleOblique("oblique");
const string IText::kWeightNormal("normal");
const string IText::kWeightLight("light");
const string IText::kWeightDemiBold("demibold");
const string IText::kWeightBold("bold");
const string IText::kWeightBlack("black");

//--------------------------------------------------------------------------
IText::IText( const std::string& name, IObject * parent ) : IGraphicBasedObject(name, parent)
{ 
	fTypeString = kTextType;
	setColor( IColor(0,0,0,255) );

	// Default font parameters
#if 0
	fFontSize = 13;				// this was the previous setting, before a default font has been embedded in the appl ressources
	fFontFamily = "Arial";
#else
	fFontSize = 14;
	fFontFamily = IAppl::defaultFontName();
#endif
	fFontWeight = kWeightNormal;
	fFontStyle = kStyleNormal;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(fText);

	// Method to manage font
	fGetMsgHandlerMap[kfontSize_GetSetMethod]	= TGetParamMethodHandler<IText, int (IText::*)() const>::create(this, &IText::getFontSize);
	fMsgHandlerMap[kfontSize_GetSetMethod]		= TSetMethodMsgHandler<IText, int>::create(this, &IText::setFontSize);

	fGetMsgHandlerMap[kfontFamily_GetSetMethod]	= TGetParamMethodHandler<IText, string (IText::*)() const>::create(this, &IText::getFontFamily);
	fMsgHandlerMap[kfontFamily_GetSetMethod]	= TSetMethodMsgHandler<IText, string>::create(this, &IText::setFontFamily);

	fGetMsgHandlerMap[kfontStyle_GetSetMethod]	= TGetParamMethodHandler<IText, string (IText::*)() const>::create(this, &IText::getFontStyle);
	fMsgHandlerMap[kfontStyle_GetSetMethod]		= TMethodMsgHandler<IText>::create(this, &IText::setFontStyle);

	fGetMsgHandlerMap[kfontWeight_GetSetMethod]	= TGetParamMethodHandler<IText, string (IText::*)() const>::create(this, &IText::getFontWeight);
	fMsgHandlerMap[kfontWeight_GetSetMethod]	= TMethodMsgHandler<IText>::create(this, &IText::setFontWeight);

	fMsgHandlerMap[kwrite_SetMethod]			= TMethodMsgHandler<IText, MsgHandler::msgStatus (IText::*)(const IMessage*)>::create(this, &IText::writeMsg);

#ifdef EMCC
	setPending();
#endif
}

//--------------------------------------------------------------------------
void IText::positionAble() {
	IObject::positionAble();
	// disable width and height methods for text. Use fontSize instead.
	fMsgHandlerMap[kwidth_GetSetMethod]		= nullptr;
	fMsgHandlerMap[kheight_GetSetMethod]	= nullptr;
	fGetMsgHandlerMap[kwidth_GetSetMethod]	= nullptr;
	fGetMsgHandlerMap[kheight_GetSetMethod]	= nullptr;
}

//--------------------------------------------------------------------------
void IText::accept (Updater* u)
{
	u->updateTo (SIText(this));
}

//--------------------------------------------------------------------------
void IText::print (ostream& out) const
{
	IObject::print (out);
	out << "  \"" << getText() << "\"";
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
MsgHandler::msgStatus IText::set( const IMessage* msg )
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	int n = msg->size();
	if (n >= 2) {
		stringstream stream;
		const char * sep = "";
		for (int i = 1; i < n ; i++) {
			string text; int itext; float ftext;
			stream << sep;
			if (msg->param(i, itext))			stream << itext;
			else if (msg->param(i, ftext))		stream << Tools::ensurefloat(ftext);
			else if (msg->param(i, text))		stream << text;
			sep = " ";
		}
		setText( stream.str() );
		newData(true);
		status = MsgHandler::kProcessed;
		getView()->initView (this);
	}
	else status = MsgHandler::kBadParameters;
	return status;
}


//--------------------------------------------------------------------------
void IText::setFontSize(int fontSize)
{
	fFontSize = fontSize;
	getView()->initView (this);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IText::writeMsg (const IMessage* msg)
{
	if ((msg->size() >= 1)) {
		stringstream sstr;
		
		for (int i=0; i < msg->size(); i++) {
			sstr << " ";
			msg->print (sstr, i, 1, " ");
		}
		setText( fText + sstr.str() );
		newData(true);
		getView()->initView (this);
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IText::setFontWeight(const IMessage *msg)
{
	int n = msg->size();
	if (n == 1) {
		string fontWeight;
		if(msg->param(0, fontWeight)) {
			if(fontWeight == IText::kWeightNormal || fontWeight == IText::kWeightLight
					|| fontWeight == IText::kWeightDemiBold || fontWeight == IText::kWeightBold || fontWeight == IText::kWeightBlack) {
				fFontWeight = fontWeight;
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IText::setFontStyle(const IMessage *msg)
{
	int n = msg->size();
	if (n == 1) {
		string fontStyle;
		if(msg->param(0, fontStyle)) {
			if(fontStyle == IText::kStyleNormal || fontStyle == IText::kStyleItalic	|| fontStyle == IText::kStyleOblique) {
				fFontStyle = fontStyle;
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

}
