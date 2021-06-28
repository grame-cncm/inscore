/*

  INScore Library
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

#include <algorithm>
#include <sstream>

#include "AudioIO.h"
#include "AudioNode.h"
#include "HTMLObjectView.h"
#include "IArc.h"
#include "ICurve.h"
#include "IEffect.h"
#include "IFaustProcessor.h"
#include "IFaustwProcessor.h"
#include "IGraphicBasedObject.h"
#include "IGuidoCode.h"
#include "IGuidoPianoRoll.h"
#include "IGuidoStream.h"
#include "IMedia.h"
#include "IMusicXMLCode.h"
#include "IObjectAdapter.h"
#include "IObjectSync.h"
#include "IPolygon.h"
#include "ISVG.h"
#include "IScene.h"
#include "ISync.h"
#include "IText.h"
#include "MapBuilder.h"
#include "TFile.h"
#include "TMessageEvaluator.h"


using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
string IObjectAdapter::color2htmlColor (const IColor& color, bool withalpha) {
	std::stringstream sstr;
	sstr << "#" << std::setfill('0') << std::hex << std::setw(2) << color.getR() << std::setw(2) << color.getG() << std::setw(2) << color.getB();
	if (withalpha)
		sstr << std::setw(2) << color.getA();
	return sstr.str();
}

//--------------------------------------------------------------------------
string IObjectAdapter::color2RGBAColor (const IColor& color) {
	std::stringstream sstr;
	sstr << "rgba("
		<< color.getR() << ", " << color.getG() << ", " << color.getB() << ", " << color.getA()
		<< ")";
	return sstr.str();
}

//--------------------------------------------------------------------------
void IObjectAdapter::_updateWidth (IPosition* pos, float w) {
	const IGraphicBasedObject* gobj = dynamic_cast<const IGraphicBasedObject*>(pos);
	if (gobj && gobj->userDims()) return;
	pos->_setWidth (w);
}
	
//--------------------------------------------------------------------------
void IObjectAdapter::_updateHeight (IPosition* pos, float h) {
	const IGraphicBasedObject* gobj = dynamic_cast<const IGraphicBasedObject*>(pos);
	if (gobj && gobj->userDims()) return;
	pos->_setHeight (h);
}

//--------------------------------------------------------------------------
void IObjectAdapter::updateViewBoundingRect(float x, float y, float w, float h) {
	IGraphicBasedObject* gobj = dynamic_cast<IGraphicBasedObject*>((IObject*)fObject);
	if (gobj)
		gobj->setBoundingRect (x, y, w, h);
}

//--------------------------------------------------------------------------
void IObjectAdapter::updateDuration(float duration) {
	IMedia* obj = dynamic_cast<IMedia*>((IObject*)fObject);
	if (obj)
		obj->setMediaDuration (long(duration));
	else cerr << obj->getOSCAddress() << ": unexpected updateDuration called for non media object." << endl;
}

//--------------------------------------------------------------------------
void IObjectAdapter::event(string event) {
	if (fObject) {
		EventContext context (fObject);
		fObject->checkEvent (event.c_str(), context);
	}
}

//--------------------------------------------------------------------------
void IObjectAdapter::keyEvent (std::string ev, std::string key)
{
	if (fObject) {
		bool down = ev == "keyDown";
		fObject->keyPressEvent (key, down);
	}
}

//--------------------------------------------------------------------------
void IObjectAdapter::midiEvent (int status, int data1, int data2)
{
	if (fObject)
		fObject->midiEvent (status, data1, data2);
}

//--------------------------------------------------------------------------
void IObjectAdapter::updateTime2TimeMap (std::string jsonmap)
{
	IGuidoCode* obj = dynamic_cast<IGuidoCode*>((IObject*)fObject);
	if (obj) {
		MapBuilder mb;
		mb.updateTime2TimeMap (obj, jsonmap);
	}
	else cerr << "unexpected updateTime2TimeMap received by: " << fObject->getOSCAddress() << endl;
}

//--------------------------------------------------------------------------
void IObjectAdapter::updateGraphic2TimeMap (string name, string jsonmap, float width, float height)
{
	IGuidoCode* obj = dynamic_cast<IGuidoCode*>((IObject*)fObject);
	if (obj && jsonmap.size()) {
		MapBuilder mb;
		mb.updateGraphic2TimeMap (obj, name, jsonmap, width, height);
	}
	else cerr << "unexpected updateGraphic2TimeMap received by: " << fObject->getOSCAddress() << endl;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getColor (const IColor* obj, JSColor& color)
{
	if (obj->modified()) {
		color.rgb		= color2htmlColor(*obj, false);
		color.rgba		= color2htmlColor(*obj, true);
		color.alpha		= obj->getA() / 255.f;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getPenBrush (const IShape* obj, JSPen& pen)
{
	pen.penWidth = obj->getPenWidth();
	pen.penColor = color2htmlColor(obj->getPenColor(), true);
	pen.penStyle = fPenStyles[obj->getPenStyle()];
	pen.brushStyle = fBrushStyles[obj->getBrushStyle()];
	return obj->modified();
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getSyncPosition (IObject* obj, const IObject* master, JSPosition& pos)
{
	for (auto sync: obj->getMasters()) {
		const SIObject m = sync->getMaster();
		if (m == master) {
			float vstretch;
			TFloatPoint p = getSyncPosition (obj, sync, vstretch);
			pos.x 		= p.fX;
			pos.y 		= p.fY;
			if (vstretch) pos.height = vstretch;
			return sync->modified() || ((IDate*)(obj))->modified();
		}
	}
	return false;
}

//--------------------------------------------------------------------------
vector<JSMaster> IObjectAdapter::getMasters () const
{
	vector<JSMaster> masters;
	for (auto m: fObject->getMasters()) {
		HTMLObjectView* view = dynamic_cast<HTMLObjectView*>(m->getMaster()->getView());
		if (view) {
			JSMaster jm;
			jm.viewid = view->getID();
			jm.vstretch = m->getStretch () & Master::kStretchV;
			masters.push_back(jm);
		}
		else
			cerr << "IObjectAdapter::getMasters: master " << m->getMaster()->name() << " has no view." << endl;
	}
	return masters;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getPosition (const IPosition* obj, JSPosition& pos)
{
	pos.x 		= obj->getXPos();
	pos.y 		= obj->getYPos();
	pos.width 	= obj->getWidth();
	pos.height 	= obj->getHeight();
	pos.xorigin	= obj->getXOrigin();
	pos.yorigin	= obj->getYOrigin();
	pos.zorder	= obj->getZOrder();
	pos.scale	= obj->getScale();
	pos.hidden	= !obj->getVisible();
	pos.xangle	= obj->getRotateX();
	pos.yangle	= obj->getRotateY();
	pos.zangle	= obj->getRotateZ();
	return obj->modified();
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getText (const IText* obj, JSTextInfos& infos)
{
	if (obj) {
		infos.text 	 = obj->getText();
		infos.size 	 = obj->getFontSize();
		infos.family = obj->getFontFamily();
		infos.weight = obj->getFontWeight();
		infos.style	 = obj->getFontStyle();
		return true;
	}
	return false;
}


//--------------------------------------------------------------------------
bool IObjectAdapter::_getLine (ILine* obj, JSLineInfos& infos)
{
	if (obj) {
		float xo = 0;
		float yo = 0;
		TFloatPoint p = obj->getPoint();
		TFloatPoint wa = obj->getWA();
		float x = p.x();
		float y = p.y();
		if ((x < 0) && (y < 0)) {
			x = -x;
			y = -y;
		} else if (x < 0) {
			yo = y;
			x = -x;
			y = 0;
		}
		else if (y < 0) {
			yo = -y;
			y = 0;
		}
		float w = std::abs(x - xo);
		float h = std::abs(y - yo);
		obj->setWidth (w);
		obj->setHeight(h);
		
		infos.x = p.x();
		infos.y = p.y();
		infos.x1 = xo;
		infos.y1 = yo;
		infos.x2 = x;
		infos.y2 = y;
		infos.angle = wa.x();
		infos.width = wa.y();
		infos.arrowLeft		= obj->getArrowLeft();
		infos.arrowRight	= obj->getArrowRight();
		infos.arrowLeftSize = obj->getArrowSizeLeft();
		infos.arrowRightSize= obj->getArrowSizeRight();
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getEffect  (const IEffect* effect, JSEffect& infos)
{
	if (effect) {
		infos.type = effect->effectType();
		switch (infos.type) {
			case IEffect::kBlur:
				infos.blur.radius = effect->fBlur.fRadius;
				infos.blur.hint = effect->fBlur.fHint;
				break;
			case IEffect::kColorize:
				infos.colorize.strength = effect->fColorize.fStrength;
				infos.colorize.color = color2RGBAColor (effect->fColorize.fColor);
				break;
			case IEffect::kShadow:
				infos.shadow.xOffset = effect->fShadow.fXOffset;
				infos.shadow.yOffset = effect->fShadow.fYOffset;
				infos.shadow.color   = color2RGBAColor (effect->fShadow.fColor);
				infos.shadow.blur    = effect->fShadow.fBlur;
				break;
		}
		return effect->modified();
	}
	return false;
}

extern const char* kMouseMoveEvent;
extern const char* kMouseDownEvent;
extern const char* kMouseUpEvent;
extern const char* kMouseEnterEvent;
extern const char* kMouseLeaveEvent;
extern const char* kMouseDoubleClickEvent;

//--------------------------------------------------------------------------
bool IObjectAdapter::_getEvents (const EventsAble* obj, JSEvents& infos)
{
	infos.watchMouseEnter		= obj->countMouseMsgs (kMouseEnterEvent);
	infos.watchMouseLeave		= obj->countMouseMsgs (kMouseLeaveEvent);
	infos.watchMouseMove		= obj->countMouseMsgs (kMouseMoveEvent);
	infos.watchMouseDown		= obj->countMouseMsgs (kMouseDownEvent);
	infos.watchMouseUp			= obj->countMouseMsgs (kMouseUpEvent);
	infos.watchMouseDClick 		= obj->countMouseMsgs (kMouseDoubleClickEvent);
	return obj->modified();
}

//--------------------------------------------------------------------------
JSRadius IObjectAdapter::getRadius () const
{
	JSRadius r;
//	r.x = r.y = 0;
	const IRect* rect = dynamic_cast<const IRect*>((IObject*)fObject);
	if (rect) {
		TFloatSize size = rect->getRadius();
		r.x = size.width();
		r.y = size.height();
	}
	return r;
}

//--------------------------------------------------------------------------
JSArcInfos IObjectAdapter::getArcInfos() const
{
	JSArcInfos infos;
	const IArc* arc = dynamic_cast<const IArc*>((IObject*)fObject);
	if (arc) {
		infos.width = arc->getWidth();
		infos.height = arc->getHeight();
		infos.start = arc->getStartAngle();
		infos.range = arc->getAngularRange();
		infos.closed= arc->closed();
	}
	return infos;
}

//--------------------------------------------------------------------------
std::vector<float> IObjectAdapter::getPolygonInfos() const
{
	std::vector<float> data;
	const IPolygon* poly = dynamic_cast<const IPolygon*>((IObject*)fObject);
	if (poly) {
		for (auto a: poly->getPoints()) {
			data.push_back (a.x());
			data.push_back (a.y());
		}
	}
	return data;
}

//--------------------------------------------------------------------------
JSGMNStreamInfos IObjectAdapter::getGuidoStream() const
{
	JSGMNStreamInfos infos;
	const IGuidoStream* obj = dynamic_cast<const IGuidoStream*>((IObject*)fObject);
	if (obj) {
		infos.stream = obj->getStream();
		infos.reset = obj->getReset();
	}
	else cerr << "IObjectAdapter::getGuidoStream: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
string IObjectAdapter::getFile () const
{
	const TFile* file = dynamic_cast<const TFile*>((IObject*)fObject);
	return file ? file->getFile() : "";
}

std::map<string, int> IObjectAdapter::fPenStyles;
std::map<string, int> IObjectAdapter::fBrushStyles;
//--------------------------------------------------------------------------
// public methods
//--------------------------------------------------------------------------
IObjectAdapter::IObjectAdapter() : fObject(0)
{
	if (fPenStyles.empty()) {
		fPenStyles[SOLID_STYLE] 		= kSolid;
		fPenStyles[DASH_STYLE] 			= kDash;
		fPenStyles[DOT_STYLE] 			= kDot;
		fPenStyles[DASH_DOT_STYLE] 		= kDashDot;
		fPenStyles[DASH_DOT_DOT_STYLE]	= kDashDotDot;

		fBrushStyles[DENSE1_BRUSH_STYLE]	= kDense1;
		fBrushStyles[DENSE2_BRUSH_STYLE]	= kDense2;
		fBrushStyles[DENSE3_BRUSH_STYLE]	= kDense3;
		fBrushStyles[DENSE4_BRUSH_STYLE]	= kDense4;
		fBrushStyles[DENSE5_BRUSH_STYLE]	= kDense5;
		fBrushStyles[DENSE6_BRUSH_STYLE]	= kDense6;
		fBrushStyles[DENSE7_BRUSH_STYLE]	= kDense7;
		fBrushStyles[NO_BRUSH_STYLE]	= kNoBrush;
		fBrushStyles[HOR_BRUSH_STYLE]	= kBrushHor;
		fBrushStyles[VER_BRUSH_STYLE]	= kBrushVer;
		fBrushStyles[CROSS_BRUSH_STYLE]	= kCross;
		fBrushStyles[BDIAG_BRUSH_STYLE]	= kBDiag;
		fBrushStyles[FDIAG_BRUSH_STYLE]	= kFDiag;
		fBrushStyles[DIAG_CROSS_BRUSH_STYLE] = kDiagCross;
	}
}

//--------------------------------------------------------------------------
JSTextInfos IObjectAdapter::getTextInfos () const
{
	JSTextInfos infos;
	if (!_getText (dynamic_cast<const IText*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getTextInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSLineInfos IObjectAdapter::getLineInfos () const
{
	JSLineInfos infos;
	if (!_getLine (dynamic_cast<ILine*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getLineInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getCurve  (const ICurve* obj, std::vector<float>& infos)
{
	if (obj) {
		const ICurve::CurveData& data = obj->getPoints();
		for (auto elt: data) {
			infos.push_back (elt.fPointA.first);
			infos.push_back (elt.fPointA.second);

			infos.push_back (elt.fPointB.first);
			infos.push_back (elt.fPointB.second);

			infos.push_back (elt.fPointC.first);
			infos.push_back (elt.fPointC.second);

			infos.push_back (elt.fPointD.first);
			infos.push_back (elt.fPointD.second);
		}
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getGuido  (const IGuidoCode* obj, JSScoreInfos& infos)
{
	if (obj) {
		infos.code 	= obj->getGMN();
		infos.page 	= obj->getPage();
		infos.mappings = obj->requestedMappings();
		return true;
	}
	else return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getXML (const IMusicXMLCode* obj, JSScoreInfos& infos)
{
	if (obj) {
		infos.code 	= obj->getMusicXML();
		infos.page 	= obj->getPage();
		infos.mappings = obj->requestedMappings();
		return true;
	}
	else return false;
}

//--------------------------------------------------------------------------
JSScoreInfos IObjectAdapter::getGuidoInfos() const
{
	JSScoreInfos infos;
	if (!_getGuido (dynamic_cast<IGuidoCode*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getGuidoInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getPianoroll  (const IGuidoPianoRoll* obj, JSPianorollInfos& infos)
{
	if (obj) {
		infos.code 	= obj->getGMN();
		infos.keyboard = obj->keybordEnabled();
		infos.autovoicecolor = obj->autoVoiceColor();
		infos.bars = obj->measureBars();
		std::vector<int> pc = obj->getClipPitch();
		if (pc.size() == 2) {
			infos.limits.lowpitch = pc[0];
			infos.limits.highpitch = pc[1];
		}
		std::vector<int> tc = obj->getClipTime();
		if (tc.size() == 4) {
			infos.limits.start.num 		= tc[0];
			infos.limits.start.denum 	= tc[1];
			infos.limits.end.num   		= tc[2];
			infos.limits.end.denum   	= tc[3];
		}
		return true;
	}
	else return false;
}

//--------------------------------------------------------------------------
JSPianorollInfos IObjectAdapter::getPianorollInfos() const
{
	JSPianorollInfos infos;
	if (!_getPianoroll (dynamic_cast<IGuidoPianoRoll*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getPianorollInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getMedia (const IMedia* obj, JSMediaInfos& infos)
{
	if (obj) {
		infos.playing	= obj->playing();
		infos.volume	= obj->volume();
		infos.rate		= obj->rateModified()  ? obj->rate() : -1;
		infos.mdate		= obj->vdateModified() ? obj->vDate() : -1;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
JSMediaInfos IObjectAdapter::getMediaInfos() const
{
	JSMediaInfos infos;
	if (!_getMedia(dynamic_cast<IMedia*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getMediaInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSIOInfos IObjectAdapter::getIOInfos() const
{
	JSIOInfos out;
	const AudioIO* obj = dynamic_cast<AudioIO*>((IObject*)fObject);
	if (!obj)
		cerr << "IObjectAdapter::getIOInfos: unexpected null object!" << endl;
	else {
		out.inputs = obj->getInputs();
		out.outputs = obj->getOutputs();
	}
	return out;
}

//--------------------------------------------------------------------------
std::string IObjectAdapter::getSVGInfos () const
{
	const ISVG* obj = dynamic_cast<ISVG*>((IObject*)fObject);
	if (!obj)
		cerr << "IObjectAdapter::getSVG: unexpected null object!" << endl;
	else return obj->getText();
	return "";

}

//--------------------------------------------------------------------------
static void putID (const IObject* obj, vector<int>& dest)
{
	const VObjectView* view = obj->getView();
	const HTMLObjectView * htmlview = dynamic_cast<const HTMLObjectView*>(view);
	if (htmlview)
		dest.push_back (htmlview->getID());
}

//--------------------------------------------------------------------------
JSAudioNodeInfos IObjectAdapter::getAudioInfos () const
{
	JSAudioNodeInfos infos;
	AudioNode* obj = dynamic_cast<AudioNode*>((IObject*)fObject);
	if (obj) {
		for (auto elt: obj->newConnections())
			putID (elt, infos.connect);
		for (auto elt: obj->delConnections())
			putID (elt, infos.disconnect);
		obj->resetNotifications();
	}
	else
		cerr << "IObjectAdapter::getAudioInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSFaustInfos IObjectAdapter::getFaustInfos (bool getvalues, bool getcode) const
{
	JSFaustInfos infos;
	IFaustProcessor* obj = dynamic_cast<IFaustProcessor*>((IObject*)fObject);
	if (obj) {
//		infos.playing = obj->playing();
		infos.voices = obj->getVoices();
		if (getcode) {
			infos.code = obj->getCode();
			const IFaustwProcessor* fw = obj->wasmBased();
			if (fw) infos.json = fw->json();
		}
		if (getvalues) {
			for (auto elt: obj->getChangedValues ()) {
				JSFaustParamValue pv;
				pv.address = elt.address;
				pv.value = elt.value;
				pv.type = elt.type;
				infos.values.push_back (pv);
			}
			for (auto elt: obj->getKeyValues ()) {
				JSFaustKeyValue k;
				k.type = elt.type;
				k.chan = elt.chan;
				k.pitch = elt.pitch;
				k.vel   = elt.velocity;
				infos.keys.push_back (k);
			}
			infos.wasmExport = (obj->wasmFlag() ? obj->name() : "");
			obj->clearChangedValues();
		}
	}
	else
		cerr << "IObjectAdapter::getFaustInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
void IObjectAdapter::setAudioInOut (int inputs, int outputs)
{
	AudioNode* obj = dynamic_cast<AudioNode*>((IObject*)fObject);
	if (obj)
		obj->setIONums (inputs, outputs);
	else
		cerr << "IObjectAdapter::setAudioInOut: unexpected null object!" << endl;
}

//--------------------------------------------------------------------------
void IObjectAdapter::setFaustUI (std::string type, std::string label, std::string address, float init, float min, float max, float step)
{
	IFaustProcessor* obj = dynamic_cast<IFaustProcessor*>((IObject*)fObject);
	if (obj)
		obj->setFaustUI (type, label, address, init, min, max, step);
	else
		cerr << "IObjectAdapter::setFaustUI: unexpected null object!" << endl;
}

//--------------------------------------------------------------------------
JSScoreInfos IObjectAdapter::getXMLInfos() const
{
	JSScoreInfos infos;
	if (!_getXML (dynamic_cast<IMusicXMLCode*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getXMLInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
std::vector<float> IObjectAdapter::getCurveInfos() const
{
	std::vector<float> infos;
	if (!_getCurve (dynamic_cast<ICurve*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getCurveInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
std::vector<JSRect> IObjectAdapter::getMaps () const
{
	std::vector<JSRect> out;
	const TMapable::namedMapping& named = fObject->namedMappings();
	bool acceptnoname = named.size() == 1;
	for (auto m: named) {

		SRelativeTime2GraphicMapping g2t = m.second;
		const Graphic2RelativeTimeRelation& rel = g2t->reverse();
		if (m.first.size() || acceptnoname) {
			for (auto seg: m.second->reverse()) {
				const GraphicSegment& gs = seg.first;
				JSRect rect;
				rect.x = gs.xinterval().first();
				rect.y = gs.yinterval().first();
				rect.width  = gs.xinterval().size();
				rect.height = gs.yinterval().size();
				out.push_back (rect);
			}
		}
	}
	return out;
}

//--------------------------------------------------------------------------
JSSceneInfos  IObjectAdapter::getSceneInfos () const
{
	JSSceneInfos infos;
	const IScene* scene = dynamic_cast<const IScene*>((IObject*)fObject);
	if (scene)
		infos.fullscreen = scene->getFullScreen();
	else
		cerr << "IObjectAdapter::getCurveInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSUpdateInfos IObjectAdapter::getUpdateInfos (int masterId) const
{
	JSUpdateInfos infos;
	if (fObject->getDeleted())
		infos.deleted = true;
	else {
		infos.newdata = fObject->newData();
		infos.newclass = fObject->classChanged()	;
		infos.classNames = fObject->getClass();
		infos.updatepos = _getPosition (fObject, infos.position);
		const IObjectAdapter* mptr = (const IObjectAdapter*)masterId;
		infos.updatepos |= _getSyncPosition (fObject, mptr->getObject(), infos.position);
		infos.updatebrush = _getPenBrush (fObject, infos.position.pen);
		infos.position.pen.color = color2htmlColor(*fObject, false);
		infos.position.pen.alpha = fObject->getA() / 255.f;
		if (infos.updatebrush) infos.updatepos = true;
		infos.updatecolor 	= _getColor (fObject, infos.color);
		infos.updateeffect	= _getEffect (fObject->getEffect(), infos.effect);
		infos.updateevents	= _getEvents (fObject, infos.events);
		infos.showmap		= fObject->mapDebug();
	}
	return infos;
}

}
