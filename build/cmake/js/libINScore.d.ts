
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
interface OLineInfo {
	x1: number;
	y1: number;
	x2: number;
	y2: number;
	arrowLeft: 	number;
	arrowRight: number;
	arrowSizeLeft: number;
	arrowSizeRight: number;
}

interface OTextInfo {
    text:   string;
	size:   number;
	family: string;
	weight: string;
	style:  string;
}

interface OColor {
    rgb:     string;
    rgba:    string;
	alpha:   number;
}

interface OPen {
	penWidth:   number;
	penColor:   string;
	penStyle:   number;
	brushStyle: number;
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
	updatepos:  boolean;
	updatebrush:  boolean;
	updatecolor:  boolean;
	deleted:      boolean;
	newdata:      boolean;
}

interface INScoreObject {
    create(id: number):        INScoreObject;
    del(obj: INScoreObject):   void;

    getUpdateInfos():  OUpdateInfos;
    getTextInfos():    OTextInfo;
	getLineInfos():    OLineInfo;
	updateWidth (w: number):  void;
	updateHeight(h: number):  void;

}
