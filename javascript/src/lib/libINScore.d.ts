
declare var INScoreModule : any;
interface TMessage     {}
        
//------------------------------------------------------------------------
// INScore glue interface 
interface INScoreGlue {
    getRate(): 		 number; 
	timeTask ():	 void;
	sorterTask():	 void;
 }

//----------------------------------------------------------------------------
interface INScoreAdapter {
    constructor: INScoreAdapter;

    start(udpport: number, outport: number, errport: number):  INScoreGlue;
	stop(glue: INScoreGlue):  void;

	loadInscore	(script:  string, autoparse:  boolean):  boolean;
	loadInscore2 (script:  string):	                     boolean;

	postMessage	(adr: string, msg: TMessage):	 void;
	postMessageStr (adr: string, meth: string):	 void;
	postMessageStrI	(adr: string, meth: string, val: number):	 void;
	postMessageStrF	(adr: string, meth: string, val: number):	 void;
	postMessageStrStr(adr: string, meth: string, val: string):	 void;

    delayMessage (adr: string, msg: TMessage):    void;
	newMessage ():                                TMessage;
	newMessageM (meth: string):                   TMessage;
	delMessage (msg: TMessage):                   void;

    msgAddStr (msg: TMessage, str: string):       void;
	msgAddF   (msg: TMessage, val: number):       void;
	msgAddI   (msg: TMessage, val: number):       void;

    version ():				 number;
	versionStr ():			 string;
	guidoversion ():		 string;
	musicxmlversion ():		 string;

    	// restartNetwork ():    void;
    	// stopNetwork ():       void;
}        

//------------------------------------------------------------------------
// INScore javascript glue interface 
interface INScoreJSGlue {
	showMouse(state: boolean): void;
	openUrl(url: string):      boolean;
	startView():               void;
	viewVersion():             string;
	getIP():                   string;
}


//------------------------------------------------------------------------
// INScore objects interface 

interface RectVector	{ size(): number; get(i: number) : number; }
interface FloatVector	{ size(): number; get(i: number) : number; }
interface StringVector	{ size(): number; get(i: number) : string; }
interface IntVector 	{ size(): number; get(i: number) : number; }
interface FaustParamValue 	{ address: string; value : number; type: number }
interface FaustParamValuesVector 	{ size(): number; get(i: number) : FaustParamValue; }
interface FaustKeyValue 	{ type : number; chan: number; pitch: number; vel: number; }
interface FaustKeyValuesVector 	{ size(): number; get(i: number) : FaustKeyValue; }

interface OSceneInfo { fullscreen: boolean; }

interface OLineInfo {
	x1: number;
	y1: number;
	x2: number;
	y2: number;
	x: number;
	y: number;
	angle: number;
	width: number;
	arrowLeft: 	number;
	arrowRight: number;
	arrowSizeLeft: number;
	arrowSizeRight: number;
}

interface OTextInfo { text: string; size: number; family: string; weight: string; style: string; }
interface OColor { rgb: string; rgba: string; alpha: number; }

interface OPen {
	penWidth:   number;
	penColor:   string;
	penStyle:   number;
	brushStyle: number;
	color: string;
	alpha: number;
}

interface OBlur 	{ radius: number; hint: number; }
interface OColorize { strength: number; color: string; }
interface OShadow 	{ xOffset: number; yOffset: number; color: string; blur: number; }
interface OEffect 	{ type: number; blur: OBlur; colorize: OColorize; shadow: OShadow; }

interface OEvents {
	watchMouseEnter  : boolean;
	watchMouseLeave  : boolean;
	watchMouseMove   : boolean;
	watchMouseDown   : boolean;
	watchMouseUp     : boolean;
	watchMouseDClick : boolean;
}

interface OPosition {
	x:   number;
	y:   number;
	width:    number;
	height:   number;
	xorigin:  number;
	yorigin:  number;
	scale:    number;
	hidden:   boolean;
	xangle:    number;
	yangle:    number;
	zangle:    number;
	zorder:    number;
	pen: 	OPen;
}

interface OUpdateInfos {
	position:  OPosition;
	color:     OColor;
	effect:    OEffect;
	events:	   OEvents;
	classNames:	string;
	updatepos:  boolean;
	updatebrush:  boolean;
	updatecolor:  boolean;
	updateeffect: boolean;
	updateevents: boolean;
	showmap:      boolean;
	deleted:      boolean;
	newdata:      boolean;
	newclass:      boolean;
}

interface OArc {
	width: number;
	height: number;
	start:  number;
	range:  number;
	closed: boolean;
}

interface OMedia { playing: boolean; volume: number; rate:  number; mdate:  number; }
interface OScore 	{ code: string; page: number; mappings: StringVector }
interface ORadius 	{ x:  number; y:  number; }
interface ODate 	{ num:   number; denum: number; }

interface OPRollLimits {
	start : ODate;
	end   : ODate;
	lowpitch : number;
	highpitch: number;
}

interface OPianorollInfos {
	code	: string;
	keyboard		: boolean;
	autovoicecolor	: boolean;
	bars			: boolean;
	limits			: OPRollLimits;
}

interface OGMNStreamInfos {
	stream		: string;
	reset		: boolean;
}

interface OAudioNodeInfos {
	connect		: IntVector;
	disconnect	: IntVector;
}

interface OFaustInfos {
	playing		: boolean;
	voices		: number;
	code		: string;
	values		: FaustParamValuesVector;
	keys		: FaustKeyValuesVector;
}

interface INScoreObject {
    // create(id: number):        INScoreObject;
    // del(obj: INScoreObject):   void;
    adapter(id: number):  INScoreObject;

    newData():   	   boolean;
	deleted():   	   boolean;
	ready():	       void;
    getMasters():      IntVector;
    getOSCAddress():   string;
    getUpdateInfos(masterId: number):  OUpdateInfos;
    getTextInfos():    OTextInfo;
	getLineInfos():    OLineInfo;
	getFile():         string;
	getRadius():       ORadius;
	getArcInfos():     OArc;
	getPolygonInfos(): FloatVector;
	getCurveInfos():   FloatVector;
	getGuidoInfos():   OScore;
	getGuidoStream():  OGMNStreamInfos;
	getPianorollInfos():   OPianorollInfos;
	getXMLInfos():     OScore;
	getMediaInfos():   OMedia;
	getSceneInfos():   OSceneInfo;
	getSVGInfos():     string;
	getFaustInfos(getvalues: boolean, getcode: boolean):  OFaustInfos;
	getAudioInfos():   OAudioNodeInfos;
	getMaps():     	   RectVector;

	updateWidth (w: number):  void;
	updateHeight(h: number):  void;
	updateViewBoundingRect(x: number, y: number, w: number, h: number): void;
	// next method is intended to media objects (audio, video)
	updateDuration(duration: number): void;

	// trigger the event given as parameter
	event(name: string): void;

	// next methods should only be called by guido score, otherwise ignored
	updateGraphic2TimeMap(name: string, map: string, width: number, height: number): void;
	updateTime2TimeMap(map: string): void;

	setFaustInOut (inputs: number, output: number): void;
	setFaustUI (type: string, label: string, address: string, init: number, min: number, max: number, step: number): void;
}
