var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
"use strict";
var MsgParamRetVal = (function () {
    function MsgParamRetVal(check, val) {
        this.correct = check;
        this.value = val;
    }
    return MsgParamRetVal;
}());
var IMessage = (function () {
    function IMessage(input, params) {
        //if input is an adress
        if (typeof input === 'string') {
            this.fAddress = input;
            if (params) {
                if (typeof params === 'string')
                    this.fArguments = new Array(params);
                else
                    this.fArguments = params;
            }
            else
                this.fArguments = new Array();
        }
        if (typeof input === 'object') {
            this.fAddress = input.fAddress;
            this.fArguments = input.fArguments;
        }
    }
    // add a value to the parameters
    IMessage.prototype.add = function (val) { this.fArguments.push(val); };
    ;
    // add values to the parameters; arrays are checked and pushed as values
    IMessage.prototype.push = function (val) {
        if (Array.isArray(val)) {
            for (var i = 0; i < val.length; i++)
                this.add(val[i]);
        }
        else
            this.fArguments.push(val);
    };
    ;
    IMessage.prototype.address = function () { return this.fAddress; };
    IMessage.prototype.param = function (i) { return this.fArguments[i]; };
    IMessage.prototype.params = function () { return this.fArguments; };
    IMessage.prototype.paramStr = function (i) {
        return new MsgParamRetVal(this.isType(i, "string"), this.fArguments[i]);
    };
    IMessage.prototype.paramNum = function (i) {
        return new MsgParamRetVal(this.isType(i, "number"), this.fArguments[i]);
    };
    IMessage.prototype.paramArray = function (i) {
        return new MsgParamRetVal(this.isType(i, "object"), this.fArguments[i]);
    };
    IMessage.prototype.message = function () { return this.paramStr(0); };
    IMessage.prototype.isType = function (i, type) { return (typeof this.fArguments[i] === type); };
    IMessage.prototype.isString = function (i) { return this.isType(i, "string"); };
    IMessage.prototype.isNumber = function (i) { return this.isType(i, "number"); };
    IMessage.prototype.isArray = function (i) { return this.isType(i, "object"); };
    IMessage.prototype.size = function () { return this.fArguments.length; };
    IMessage.prototype.toString = function () {
        var out = this.fAddress;
        for (var i = 0; i < this.fArguments.length; i++) {
            if (this.isType(i, "object"))
                out += " ( " + this.fArguments[i].toString() + " )";
            else
                out += " " + this.fArguments[i].toString();
        }
        return out;
    };
    return IMessage;
}());
// declare a type for message lists
var IMessageList = (function (_super) {
    __extends(IMessageList, _super);
    function IMessageList() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return IMessageList;
}(Array));
// object types
var kArcType = "arc";
var kCurveType = "curve";
var kEllipseType = "ellipse";
var kGuidoCodeType = "gmn";
var kGuidoPianoRollType = "pianoroll";
var kFaustType = "faust";
var kFaustfType = "faustf";
var kHtmlType = "html";
var kImgType = "img";
var kLineType = "line";
var kPolygonType = "polygon";
var kRectType = "rect";
var kSvgfType = "svgf";
var kSvgType = "svg";
var kSyncType = "sync";
var kTextfType = "txtf";
var kTextType = "txt";
var kMusicxmlType = "musicxml";
var kVideoType = "video";
var kVerovioType = "verovio";
var kVeroviofType = "veroviof";
var kWebSocketType = "websocket";
var kDebugType = "debug";
var kObjType = "obj";
var kApplType = "IAppl";
var kSceneType = "scene";
// inscore type for inscore scripts
var kInscoreFile = "inscore";
var kDefaultRate = 10; // the default inscore time task rate in ms
var kObjectSize = 2; // an object size in internal representation
///<reference path="model/Constants.ts"/>
var gCreateView = true;
var gINScoreRealRate = kDefaultRate; // the current inscore time task real rate in ms
var eMsgStatus;
(function (eMsgStatus) {
    eMsgStatus[eMsgStatus["kBadAddress"] = 0] = "kBadAddress";
    eMsgStatus[eMsgStatus["kProcessed"] = 1] = "kProcessed";
    eMsgStatus[eMsgStatus["kProcessedNoChange"] = 2] = "kProcessedNoChange";
    eMsgStatus[eMsgStatus["kBadParameters"] = 4] = "kBadParameters";
    eMsgStatus[eMsgStatus["kCreateFailure"] = 8] = "kCreateFailure";
})(eMsgStatus || (eMsgStatus = {}));
var eObjState;
(function (eObjState) {
    eObjState[eObjState["kClean"] = 0] = "kClean";
    eObjState[eObjState["kNewObject"] = 1] = "kNewObject";
    eObjState[eObjState["kModified"] = 2] = "kModified";
    eObjState[eObjState["kSubModified"] = 4] = "kSubModified";
    eObjState[eObjState["kMasterModified"] = 8] = "kMasterModified";
})(eObjState || (eObjState = {}));
var ePenStyle;
(function (ePenStyle) {
    ePenStyle[ePenStyle["kSolid"] = 0] = "kSolid";
    ePenStyle[ePenStyle["kDash"] = 1] = "kDash";
    ePenStyle[ePenStyle["kDot"] = 2] = "kDot";
    ePenStyle[ePenStyle["kDashDot"] = 3] = "kDashDot";
    ePenStyle[ePenStyle["kDashDotDot"] = 4] = "kDashDotDot";
    ePenStyle[ePenStyle["kLast"] = 5] = "kLast";
})(ePenStyle || (ePenStyle = {}));
var eBrushStyle;
(function (eBrushStyle) {
    eBrushStyle[eBrushStyle["kNone"] = 0] = "kNone";
    eBrushStyle[eBrushStyle["kSolid"] = 1] = "kSolid";
})(eBrushStyle || (eBrushStyle = {}));
var eEffect;
(function (eEffect) {
    eEffect[eEffect["kNone"] = 0] = "kNone";
    eEffect[eEffect["kBlur"] = 1] = "kBlur";
    eEffect[eEffect["kColorize"] = 2] = "kColorize";
    eEffect[eEffect["kShadow"] = 3] = "kShadow";
})(eEffect || (eEffect = {}));
var eSyncModes;
(function (eSyncModes) {
    eSyncModes[eSyncModes["kRelative"] = 0] = "kRelative";
    eSyncModes[eSyncModes["kAbsolute"] = 1] = "kAbsolute";
})(eSyncModes || (eSyncModes = {}));
var eSyncPosition;
(function (eSyncPosition) {
    eSyncPosition[eSyncPosition["kSyncOver"] = 0] = "kSyncOver";
    eSyncPosition[eSyncPosition["kSyncTop"] = 1] = "kSyncTop";
    eSyncPosition[eSyncPosition["kSyncBottom"] = 2] = "kSyncBottom";
    eSyncPosition[eSyncPosition["kSyncFrame"] = 3] = "kSyncFrame";
})(eSyncPosition || (eSyncPosition = {}));
var eSyncStretch;
(function (eSyncStretch) {
    eSyncStretch[eSyncStretch["kSyncDate"] = 0] = "kSyncDate";
    eSyncStretch[eSyncStretch["kSyncV"] = 1] = "kSyncV";
    eSyncStretch[eSyncStretch["kSyncH"] = 2] = "kSyncH";
})(eSyncStretch || (eSyncStretch = {}));
var kNoPosition = 0xfffffff;
var eUIEvents;
(function (eUIEvents) {
    eUIEvents[eUIEvents["kMouseDown"] = 1] = "kMouseDown";
    eUIEvents[eUIEvents["kMouseMove"] = 2] = "kMouseMove";
    eUIEvents[eUIEvents["kMouseUp"] = 4] = "kMouseUp";
    eUIEvents[eUIEvents["kMouseEnter"] = 8] = "kMouseEnter";
    eUIEvents[eUIEvents["kMouseLeave"] = 16] = "kMouseLeave";
    eUIEvents[eUIEvents["kDoubleClick"] = 32] = "kDoubleClick";
    eUIEvents[eUIEvents["kTouchBegin"] = 64] = "kTouchBegin";
    eUIEvents[eUIEvents["kTouchEnd"] = 128] = "kTouchEnd";
    eUIEvents[eUIEvents["kTouchUpdate"] = 256] = "kTouchUpdate";
})(eUIEvents || (eUIEvents = {}));
var Fraction = (function () {
    // CONSTRUCTOR
    //-------------------------------------------------------------- 
    function Fraction(a, b) {
        if (a instanceof Fraction) {
            this.numerator = a.numerator;
            this.denominator = a.denominator;
        }
        else if (typeof a === "number") {
            if (b === undefined)
                this.rational2fraction(a);
            else {
                this.numerator = a;
                this.denominator = b;
            }
        }
        else if (typeof a === "string" && b === undefined) {
            var myRegex = /^([0-9]+)\/([0-9]+)$/.test(a);
            if (myRegex) {
                this.numerator = parseInt(RegExp.$1);
                this.denominator = parseInt(RegExp.$2);
            }
        }
        if (this.denominator == 0) {
            this.numerator = undefined;
            this.denominator = undefined;
        } // undefined if denominator = 0
    }
    // APPROXIMATE A RATIONAL AS A FRACTION
    //-------------------------------------------------------------- 
    Fraction.approximate = function (value, precision) {
        return new Fraction(Math.floor(value * precision), precision).reduce();
    };
    // CONVERTION RATIONAL TO A FRACTION
    //-------------------------------------------------------------- 
    Fraction.prototype.rational2fraction = function (value) {
        var cpt = 1;
        var test = 0;
        while (value * cpt != test) {
            cpt++;
            test = Math.floor(value * cpt);
        }
        this.numerator = value * cpt;
        this.denominator = cpt;
        this.reduce();
    };
    // CONVERT NUMERIC FRACTION TO A STRING
    //-------------------------------------------------------------- 
    Fraction.prototype.toString = function () { return this.numerator + "/" + this.denominator; };
    Fraction.prototype.toNum = function () { return this.numerator / this.denominator; };
    Fraction.prototype.toArray = function () { return [this.numerator, this.denominator]; };
    // OPERATORS FONCTIONS
    //-------------------------------------------------------------- 
    // fraction1 + fraction2 => var sum = fraction1.add(fraction2)
    Fraction.prototype.add = function (value) {
        var that = new Fraction(value);
        var denominator = this.denominator * that.denominator;
        that.numerator = this.numerator * that.denominator + that.numerator * this.denominator;
        that.denominator = denominator;
        return that.reduce();
    };
    // fraction1 * fraction2 => var result = fraction1.sum(fraction2)
    Fraction.prototype.mul = function (value) {
        var that = new Fraction(value);
        that.numerator = this.numerator * that.numerator;
        that.denominator = this.denominator * that.denominator;
        return that.reduce();
    };
    // fraction1 / fraction2 => var result = fraction1.div(fraction2)
    Fraction.prototype.div = function (value) {
        var that = new Fraction(value);
        _a = [that.denominator, that.numerator], that.numerator = _a[0], that.denominator = _a[1];
        return this.mul(that);
        var _a;
    };
    // fraction1 - fraction2 => var result = fraction1.sub(fraction2)
    Fraction.prototype.sub = function (value) {
        var that = new Fraction(value);
        that.numerator = -that.numerator;
        return this.add(that);
    };
    // inverse a fraction
    Fraction.prototype.inverse = function () {
        return new Fraction(this.denominator, this.numerator).reduce();
    };
    // comparisons
    Fraction.prototype.eq = function (f) {
        var f1 = new Fraction(this.denominator, this.numerator).reduce();
        var f2 = new Fraction(f).reduce();
        return (f1.denominator == f2.denominator) && (f1.numerator == f2.numerator);
    };
    Fraction.prototype.gt = function (f) { return this.toNum() > f.toNum(); };
    Fraction.prototype.geq = function (f) { return this.toNum() >= f.toNum(); };
    Fraction.prototype.lt = function (f) { return this.toNum() < f.toNum(); };
    Fraction.prototype.leq = function (f) { return this.toNum() <= f.toNum(); };
    //-----------------------------------------
    // quantification
    Fraction.prototype.quantize = function (num, dnum) {
        var d = this.denominator * num;
        if (!d)
            return new Fraction(this);
        var n = Math.floor(this.numerator * dnum / d);
        return new Fraction(num * n, dnum);
    };
    //-----------------------------------------
    // reduce a fraction : Euclide algorithme
    Fraction.prototype.reduce = function () {
        var a = Math.max(this.numerator, this.denominator);
        var b = Math.min(this.numerator, this.denominator);
        if ((a == 0) || (b == 0))
            return new Fraction(this);
        var rest = a % b;
        while (rest != 0) {
            a = b;
            b = rest; // var b is the PGCD if the rest is equal to 0
            rest = a % b;
        }
        return new Fraction(this.numerator / b, this.denominator / b);
    };
    // GETS AND SETS VALUES
    //--------------------------------------------------------------
    Fraction.prototype.getDenominator = function () { return this.denominator; };
    Fraction.prototype.getNumerator = function () { return this.numerator; };
    Fraction.prototype.setDenominator = function (value) { this.denominator = value; };
    Fraction.prototype.setNumerator = function (value) { this.numerator = value; };
    return Fraction;
}());
//export default Fraction; 
///<reference path="IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../externals/fraction.ts"/>
"use strict";
var SetMsgHandler = (function () {
    function SetMsgHandler(method) {
        this.fMethod = method;
    }
    return SetMsgHandler;
}());
var GetMsgHandler = (function () {
    function GetMsgHandler(method) {
        this.fMethod = method;
    }
    return GetMsgHandler;
}());
var GetMsgsHandler = (function () {
    function GetMsgsHandler(method) {
        this.fMethod = method;
    }
    return GetMsgsHandler;
}());
///<reference path="TTypes.ts"/>
var OSCAddress = (function () {
    function OSCAddress() {
    }
    // METHODS
    //--------------------------------------------------------------  
    OSCAddress.shift = function (address) {
        var head = address.replace(/\/([^\/]+)(\/..*|$)/, "$1");
        var tail = address.replace(/\/[^\/]*(.*)/, "$1");
        return { first: head, second: tail };
    };
    OSCAddress.last = function (address) {
        return address.replace(/.*\//, "");
    };
    OSCAddress.addressFirst = function (a) {
        if (a[0] == this.kAddressSep) {
            var n = a.indexOf(this.kAddressSep, 1);
            if (n == this.npos)
                n = a.length;
            return a.substr(1, n - 1);
        }
        return "";
    };
    OSCAddress.addressTail = function (a) {
        if (a[0] == this.kAddressSep) {
            var n = a.indexOf(this.kAddressSep, 1);
            if (n != this.npos) {
                return a.substr(n, a.length - n);
            }
        }
        return "";
    };
    return OSCAddress;
}());
// ATTRIBUTES
//--------------------------------------------------------------     
OSCAddress.kAddressSep = "/";
OSCAddress.npos = -1;
///<reference path="IMessage.ts"/>
///<reference path="THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>
"use strict";
// ------------------------------------------------------------------------------
// put a single number in a message
// ------------------------------------------------------------------------------
var TGetMsgHandlerNum = (function (_super) {
    __extends(TGetMsgHandlerNum, _super);
    function TGetMsgHandlerNum(method) {
        return _super.call(this, method) || this;
    }
    TGetMsgHandlerNum.prototype.fill = function (msg) {
        msg.add(this.fMethod());
        return msg;
    };
    return TGetMsgHandlerNum;
}(GetMsgHandler));
// ------------------------------------------------------------------------------
// put a single string in a message
// ------------------------------------------------------------------------------
var TGetMsgHandlerText = (function (_super) {
    __extends(TGetMsgHandlerText, _super);
    function TGetMsgHandlerText(method) {
        return _super.call(this, method) || this;
    }
    TGetMsgHandlerText.prototype.fill = function (msg) {
        msg.add(this.fMethod());
        return msg;
    };
    return TGetMsgHandlerText;
}(GetMsgHandler));
// ------------------------------------------------------------------------------
// put a date in a message
// ------------------------------------------------------------------------------
var TGetMsgHandlerTime = (function (_super) {
    __extends(TGetMsgHandlerTime, _super);
    function TGetMsgHandlerTime(method) {
        return _super.call(this, method) || this;
    }
    TGetMsgHandlerTime.prototype.fill = function (msg) {
        var d = this.fMethod();
        msg.add(d.getNumerator());
        msg.add(d.getDenominator());
        return msg;
    };
    return TGetMsgHandlerTime;
}(GetMsgHandler));
// ------------------------------------------------------------------------------
// put an array in a message
// ------------------------------------------------------------------------------
var TGetMsgHandlerArray = (function (_super) {
    __extends(TGetMsgHandlerArray, _super);
    function TGetMsgHandlerArray(method) {
        return _super.call(this, method) || this;
    }
    TGetMsgHandlerArray.prototype.fill = function (msg) {
        msg.push(this.fMethod());
        return msg;
    };
    return TGetMsgHandlerArray;
}(GetMsgHandler));
// ------------------------------------------------------------------------------
// return a message list 
// ------------------------------------------------------------------------------
var TGetMsgsHandler = (function (_super) {
    __extends(TGetMsgsHandler, _super);
    function TGetMsgsHandler(method) {
        return _super.call(this, method) || this;
    }
    TGetMsgsHandler.prototype.getMsgs = function () { return this.fMethod(); };
    return TGetMsgsHandler;
}(GetMsgsHandler));
///<reference path="IMessage.ts"/>
///<reference path="THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>
"use strict";
// ------------------------------------------------------------------------------
// a basic message handler: passes the whole message to the client object
// ------------------------------------------------------------------------------
var TMethodHandler = (function (_super) {
    __extends(TMethodHandler, _super);
    function TMethodHandler(method) {
        return _super.call(this, method) || this;
    }
    TMethodHandler.prototype.handle = function (msg) { return this.fMethod(msg); };
    return TMethodHandler;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// a no param message handler
// ------------------------------------------------------------------------------
var TMsgHandlerVoid = (function (_super) {
    __extends(TMsgHandlerVoid, _super);
    function TMsgHandlerVoid(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerVoid.prototype.handle = function (msg) {
        if (msg.size() != 1) {
            return eMsgStatus.kBadParameters;
        }
        this.fMethod();
        return eMsgStatus.kProcessed;
    };
    return TMsgHandlerVoid;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// a single number message handler: passes a number to the client object
// ------------------------------------------------------------------------------
var TMsgHandlerNum = (function (_super) {
    __extends(TMsgHandlerNum, _super);
    function TMsgHandlerNum(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerNum.prototype.handle = function (msg) {
        if (msg.size() != 2) {
            return eMsgStatus.kBadParameters;
        }
        var ret = msg.paramNum(1);
        if (!ret.correct) {
            return eMsgStatus.kBadParameters;
        }
        this.fMethod(ret.value);
        return eMsgStatus.kProcessed;
    };
    return TMsgHandlerNum;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// a single string message handler: passes a string to the client object
// ------------------------------------------------------------------------------
var TMsgHandlerText = (function (_super) {
    __extends(TMsgHandlerText, _super);
    function TMsgHandlerText(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerText.prototype.handle = function (msg) {
        if (msg.size() != 2) {
            return eMsgStatus.kBadParameters;
        }
        var ret = msg.paramStr(1);
        if (!ret.correct) {
            return eMsgStatus.kBadParameters;
        }
        this.fMethod(ret.value);
        return eMsgStatus.kProcessed;
    };
    return TMsgHandlerText;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// a color message handler: passes color values to the client object
// alpha value is optional and defaults to 1
// ------------------------------------------------------------------------------
var TMsgHandlerColor = (function (_super) {
    __extends(TMsgHandlerColor, _super);
    function TMsgHandlerColor(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerColor.prototype.getrgb = function (msg) {
        if (msg.size() < 4)
            return { err: true };
        var r = msg.paramNum(1);
        var g = msg.paramNum(2);
        var b = msg.paramNum(3);
        if (!r.correct || !g.correct || !b.correct)
            return { err: true };
        return { err: false, rgb: [r.value, g.value, b.value] };
    };
    TMsgHandlerColor.prototype.handle = function (msg) {
        if (msg.size() > 5)
            return eMsgStatus.kBadParameters;
        var color = this.getrgb(msg);
        if (color.err) {
            return eMsgStatus.kBadParameters;
        }
        if (msg.size() == 5) {
            var r = msg.paramNum(4);
            if (r.correct) {
                color.rgb.push(r.value);
                this.fMethod(color.rgb);
                return eMsgStatus.kProcessed;
            }
            else
                return eMsgStatus.kBadParameters;
        }
        this.fMethod(color.rgb);
        return eMsgStatus.kProcessed;
    };
    return TMsgHandlerColor;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// an array message handler: passes an array to the client object
// accepte any type as parameters
// ------------------------------------------------------------------------------
var TMsgHandlerAnyArray = (function (_super) {
    __extends(TMsgHandlerAnyArray, _super);
    function TMsgHandlerAnyArray(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerAnyArray.prototype.handle = function (msg) {
        return this.fMethod(msg.params());
    };
    return TMsgHandlerAnyArray;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// an array message handler: passes an array to the client object
// accepte only numbers as parameters
// ------------------------------------------------------------------------------
var TMsgHandlerNumArray = (function (_super) {
    __extends(TMsgHandlerNumArray, _super);
    function TMsgHandlerNumArray(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerNumArray.prototype.getnums = function (msg) {
        var out = [];
        for (var i = 1; i < msg.size(); i++) {
            var val = msg.paramNum(i);
            if (!val.correct)
                return { err: true };
            out.push(val.value);
        }
        return { err: false, numbers: out };
    };
    TMsgHandlerNumArray.prototype.handle = function (msg) {
        var nums = this.getnums(msg);
        if (nums.err) {
            return eMsgStatus.kBadParameters;
        }
        return this.fMethod(nums.numbers);
    };
    return TMsgHandlerNumArray;
}(SetMsgHandler));
// ------------------------------------------------------------------------------
// a time message handler: passes a date to the client object
// it supports the followinf date forms:
//    	- n d
//		- n
//		- a float value
//		- "n/d"
// ------------------------------------------------------------------------------
var TMsgHandlerTime = (function (_super) {
    __extends(TMsgHandlerTime, _super);
    function TMsgHandlerTime(method) {
        return _super.call(this, method) || this;
    }
    TMsgHandlerTime.prototype.handle = function (msg) {
        var n = msg.size();
        if (n > 3)
            return eMsgStatus.kBadParameters;
        if (n == 3) {
            var num = msg.paramNum(1);
            var denum = msg.paramNum(2);
            if (!num.correct || !denum.correct)
                return eMsgStatus.kBadParameters;
            this.fMethod(new Fraction(num.value, denum.value));
        }
        else if (n == 2) {
            var d = msg.paramNum(1);
            var dstr = msg.paramStr(1);
            if (d.correct)
                this.fMethod(new Fraction(d.value));
            else if (dstr.correct)
                this.fMethod(new Fraction(dstr.value));
            else
                return eMsgStatus.kBadParameters;
        }
        return eMsgStatus.kProcessed;
    };
    return TMsgHandlerTime;
}(SetMsgHandler));
///<reference path="../externals/fraction.ts"/>
///<reference path="../lib/TTypes.ts"/>
//-------------------------------------------------------------- 
// Environment for a message evaluation
//-------------------------------------------------------------- 
var TEnv = (function () {
    function TEnv(target, mouse, date, timepos, user) {
        this.fTarget = target;
        this.fMouse = mouse ? mouse : { rel: { x: 0, y: 0 }, abs: { x: 0, y: 0 }, parent: { x: 0, y: 0 } };
        this.fDate = date ? date : new Fraction(0, 1);
        this.fTimePos = timepos ? timepos : new Fraction(0, 1);
        this.fUser = user ? user : [];
        this.fSystem = []; // add the following keys: 
        //	OSName: "MacOS", "Windows", "Linux", "Android" or "iOS".
        //	OSId: 1 for Android, 2 for iOS, 3 for Linux, 4 for MacOS, 5 for Windows.
    }
    TEnv.prototype.toString = function () {
        var out = "Env: " + this.fTarget;
        out += "\n	mouse: " + this.fMouse;
        out += "\n	date: " + this.fDate;
        out += "\n	timepos: " + this.fTimePos;
        out += "\n	user: " + this.fUser;
        out += "\n	system: " + this.fSystem;
        return out;
    };
    return TEnv;
}());
;
///<reference path="lib/TEnums.ts"/>
///<reference path="controller/IMessage.ts"/>
var INScore;
var INScoreInterface = (function () {
    function INScoreInterface() {
    }
    return INScoreInterface;
}());
var OSCRegexp = (function () {
    function OSCRegexp(regexp) {
        this.fRegExp = new RegExp("^" + OSCRegexp.OSCRe2Re(regexp) + "$");
    }
    OSCRegexp.OSCRe2Re = function (re) {
        var outstr = "";
        var inlist = false;
        for (var i = 0; i < re.length; i++) {
            switch (re[i]) {
                case '{':
                    outstr += '(';
                    inlist = true;
                    break;
                case ',':
                    outstr += (inlist ? '|' : ',');
                    break;
                case '}':
                    outstr += ')';
                    inlist = false;
                    break;
                case '*':
                    outstr += ".*";
                    break;
                case '?':
                    outstr += '.';
                    break;
                default: outstr += re[i];
            }
        }
        return outstr;
    };
    OSCRegexp.prototype.match = function (str) {
        return this.fRegExp.test(str);
    };
    return OSCRegexp;
}());
///<reference path="TTypes.ts"/>
var Tools = (function () {
    function Tools() {
    }
    Tools.regexp = function (str) {
        var n = str.length;
        for (var i = 0; i < n; i++) {
            var c = str[i];
            if ((c == '*') || (c == '?') || (c == '[') || (c == '{'))
                return true;
        }
        return false;
    };
    // Read file content
    // Actually error does not catch anything
    Tools.readFile = function (src, success, error) {
        var content = "";
        var receiver = document.createElement("iframe");
        receiver.style.display = "none";
        receiver.onerror = function () { console.log('error: failed to load ' + src); };
        receiver.onabort = function () { console.log('abort: failed to load ' + src); };
        receiver.onload = function () {
            var doc = receiver.contentWindow || receiver.contentDocument;
            var title = doc.document.title;
            if (doc.document)
                doc = doc.document;
            content = doc.getElementsByTagName("body")[0].innerText;
            receiver.remove();
            if ((title === "404 Not Found") || (content.indexOf("Not Found") == 0))
                error(content);
            else
                success(content);
        };
        receiver.src = src;
        document.body.appendChild(receiver);
    };
    // Handling a set file message
    Tools.setFile = function (msg, success, error) {
        var n = msg.size();
        if (n == 3) {
            var file = msg.paramStr(2);
            if (file.correct) {
                Tools.readFile(file.value, success, error);
                return file.value;
            }
        }
        return null;
    };
    Tools.string2svg = function (str) {
        var n = str.length;
        var header = '<svg  width="' + n * 6 + '" height="14" ';
        return header + 'xmlns="http://www.w3.org/2000/svg"  version="1.1"> <g  font-family="courier" font-size="10"><text x="0" y="10">' + str + '</text></g></svg>';
    };
    Tools.error2svg = function () {
        return '<svg width="68" height="68" xmlns="http://www.w3.org/2000/svg"><g>' +
            '<rect rx="5" height="64" width="64" y="2" x="2" stroke-width="4" stroke="#000" fill="#e00"/>' +
            '<rect rx="4" height="14" width="34" y="26" x="17" stroke-width="0" fill="#fff"/></g></svg>';
        //		return '<svg width="128" height="128" xmlns="http://www.w3.org/2000/svg"><g>' +
        '<rect rx="5" height="124" width="124" y="2" x="2" stroke-width="4" stroke="#000" fill="#e00"/>' +
            '<rect rx="5" height="24" width="64" y="52" x="32" stroke-width="0" fill="#fff"/></g></svg>';
    };
    return Tools;
}());
///<reference path="../inscore-interface.ts"/>
var ITLError = (function () {
    function ITLError() {
    }
    ITLError.write = function (str) {
        var errmsg = "Error: " + str;
        console.log(errmsg);
        INScore.postMessage("/ITL/log", ["write", errmsg]);
    };
    ITLError.badParameter = function (msg, p) { this.write("bad parameter " + p + " in " + msg); };
    return ITLError;
}());
///<reference path="../inscore-interface.ts"/>
var ITLOut = (function () {
    function ITLOut() {
    }
    ITLOut.write = function (str) {
        console.log(str);
        INScore.postMessage("/ITL/log", ["write", str]);
    };
    return ITLOut;
}());
///<reference path="../externals/fraction.ts"/>
//--------------------------------------------------------------------
// an abstract class to represent intervals
//--------------------------------------------------------------------
var TInterval = (function () {
    function TInterval(first, second) {
        this.fFirst = first;
        this.fSecond = second;
    }
    TInterval.prototype.toString = function () { return "[" + this.fFirst + ", " + this.fSecond + "["; };
    TInterval.prototype.set = function (i) {
        this.fFirst = i.first();
        this.fSecond = i.second();
    };
    TInterval.prototype.first = function () { return this.fFirst; };
    TInterval.prototype.second = function () { return this.fSecond; };
    TInterval.prototype.neq = function (i) { return !this.eq(i); };
    ;
    TInterval.prototype.include = function (i) { return this.includeLocation(i.first()) && this.includeLocation(i.second()); };
    return TInterval;
}());
//--------------------------------------------------------------------
// numbers intervals
//--------------------------------------------------------------------
var NumberInterval = (function (_super) {
    __extends(NumberInterval, _super);
    function NumberInterval() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    NumberInterval.prototype.eq = function (i) { return (this.fFirst == i.first()) && (this.fSecond == i.second()); };
    NumberInterval.prototype.empty = function () { return this.fFirst == this.fSecond; };
    NumberInterval.prototype.includeLocation = function (loc) { return (this.fFirst <= loc) && (this.fSecond > loc); };
    NumberInterval.prototype.size = function () { return this.fSecond - this.fFirst; };
    NumberInterval.prototype.mult = function (n) { this.fFirst *= n; this.fSecond *= n; };
    NumberInterval.prototype.toArray = function () { return [this.fFirst, this.fSecond]; };
    return NumberInterval;
}(TInterval));
//--------------------------------------------------------------------
// time intervals
//--------------------------------------------------------------------
var TimeInterval = (function (_super) {
    __extends(TimeInterval, _super);
    function TimeInterval(first, second) {
        return _super.call(this, new Fraction(first), new Fraction(second)) || this;
    }
    TimeInterval.prototype.toNumInterval = function () { return new NumberInterval(this.fFirst.toNum(), this.fSecond.toNum()); };
    TimeInterval.prototype.eq = function (i) { return (this.fFirst.eq(i.first())) && (this.fSecond.eq(i.second())); };
    TimeInterval.prototype.empty = function () { return this.fFirst.eq(this.fSecond); };
    TimeInterval.prototype.size = function () { return this.fSecond.sub(this.fFirst); };
    TimeInterval.prototype.includeLocation = function (loc) { return this.fFirst.leq(loc) && this.fSecond.gt(loc); };
    TimeInterval.prototype.toArray = function () { return this.fFirst.toArray().concat(this.fSecond.toArray()); };
    return TimeInterval;
}(TInterval));
///<reference path="../lib/TInterval.ts"/>
///<reference path="../lib/TTypes.ts"/>
//--------------------------------------------------------------------
// Graphic segments class
//--------------------------------------------------------------------
var TGraphicSegment = (function () {
    function TGraphicSegment(xinterval, yinterval) {
        if (xinterval) {
            this.fXInterval = xinterval;
            this.fYInterval = yinterval ? yinterval : xinterval;
        }
        else {
            this.fXInterval = new NumberInterval(0, 0);
            this.fYInterval = new NumberInterval(0, 0);
        }
    }
    TGraphicSegment.prototype.toString = function () { return "[" + this.fXInterval + ", " + this.fYInterval + "]"; };
    TGraphicSegment.prototype.first = function () { return this.fXInterval; };
    TGraphicSegment.prototype.second = function () { return this.fYInterval; };
    TGraphicSegment.prototype.size = function () { return this.fXInterval.size() * this.fYInterval.size(); };
    TGraphicSegment.prototype.empty = function () { return this.fXInterval.empty() || this.fYInterval.empty(); };
    TGraphicSegment.prototype.scale = function (x, y) { this.fXInterval.mult(x); this.fYInterval.mult(y); };
    TGraphicSegment.prototype.eq = function (s) { return this.fXInterval.eq(s.fXInterval) && this.fYInterval.eq(s.fYInterval); };
    TGraphicSegment.prototype.neq = function (s) { return !this.eq(s); };
    ;
    TGraphicSegment.prototype.includeLocation = function (loc) { return this.fXInterval.includeLocation(loc.x) && this.fYInterval.includeLocation(loc.y); };
    TGraphicSegment.prototype.include = function (g) { return this.fXInterval.include(g.first()) && this.fYInterval.include(g.second()); };
    return TGraphicSegment;
}());
///<reference path="TSegment.ts"/>
///<reference path="../lib/TTypes.ts"/>
//--------------------------------------------------------------------
// A relation between a graphic segment and a time segment
//--------------------------------------------------------------------
var TTime2GraphicRelation = (function () {
    function TTime2GraphicRelation(time, graph) {
        this.fTime = time;
        this.fGraph = graph;
    }
    TTime2GraphicRelation.prototype.toString = function () { return this.fTime.toString() + " -> " + this.fGraph.toString(); };
    TTime2GraphicRelation.prototype.includeTime = function (loc) { return this.fTime.includeLocation(loc); };
    TTime2GraphicRelation.prototype.includePoint = function (loc) { return this.fGraph.includeLocation(loc); };
    return TTime2GraphicRelation;
}());
///<reference path="TTime2GraphicRelation.ts"/>
///<reference path="TSegment.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/TTypes.ts"/>
//--------------------------------------------------------------------
// Segmentation class
//--------------------------------------------------------------------
var TTime2GraphicMap = (function () {
    function TTime2GraphicMap() {
        this.fRelations = [];
    }
    TTime2GraphicMap.prototype.toString = function () {
        var out = "[\n";
        this.fRelations.forEach(function (elt) { out += " " + elt + ",\n"; });
        return out + "]";
    };
    TTime2GraphicMap.prototype.addElt = function (elt) { this.fRelations.push(elt); };
    TTime2GraphicMap.prototype.addElts = function (elts) { elts.forEach(function (elt) { this.fRelations.push(elt); }); };
    TTime2GraphicMap.prototype.forEach = function (f) { this.fRelations.forEach(f); };
    TTime2GraphicMap.prototype.clear = function () { this.fRelations = []; };
    TTime2GraphicMap.prototype.getRelations = function () { return this.fRelations; };
    TTime2GraphicMap.prototype.time2Relation = function (loc) {
        for (var i = 0; i < this.fRelations.length; i++)
            if (this.fRelations[i].includeTime(loc))
                return this.fRelations[i];
        return null;
    };
    TTime2GraphicMap.prototype.point2Relation = function (loc) {
        for (var i = 0; i < this.fRelations.length; i++)
            if (this.fRelations[i].includePoint(loc))
                return this.fRelations[i];
        return null;
    };
    TTime2GraphicMap.prototype.date2Relation = function (d) {
        for (var i = 0; i < this.fRelations.length; i++)
            if (this.fRelations[i].includeTime(d))
                return this.fRelations[i];
        return null;
    };
    TTime2GraphicMap.prototype.pos2IObjectPos = function (n) { return (n * 2) - 1; };
    TTime2GraphicMap.prototype.interval2IObjectInterval = function (i) {
        return new NumberInterval(this.pos2IObjectPos(i.first()), this.pos2IObjectPos(i.second()));
    };
    TTime2GraphicMap.prototype.date2MapLocation = function (date) {
        var relation = this.date2Relation(date);
        if (relation) {
            var timeinterval = relation.fTime;
            // compute the date offset inside the time interval
            var offset = date.toNum() - timeinterval.first().toNum();
            if (offset >= 0) {
                var relativepos = offset / (timeinterval.second().toNum() - timeinterval.first().toNum());
                var segx = relation.fGraph.first().first();
                var xpos = this.pos2IObjectPos(segx + (relation.fGraph.first().size() * relativepos));
                return { x: xpos, y: this.interval2IObjectInterval(relation.fGraph.second()) };
            }
            else
                console.log("Unexpected offset " + offset + " in TTime2GraphicMap.date2MapPoint");
        }
        return { x: kNoPosition, y: new NumberInterval(0, 0) };
    };
    TTime2GraphicMap.prototype.mapPoint2Date = function (point) {
        var relation = this.point2Relation(point);
        if (relation) {
            var xinterval = relation.fGraph.first();
            var offset = point.x - xinterval.first();
            if (offset >= 0) {
                var relativepos = offset / xinterval.size();
                var start = relation.fTime.first().toNum(); // computations on fractions are made on numeric values
                var end = relation.fTime.second().toNum();
                var timeoffset = (end - start) * relativepos;
                return Fraction.approximate(start + timeoffset, 1000000);
            }
            else
                console.log("Unexpected offset " + offset + " in TTime2GraphicMap.mapPoint2Date");
        }
        return null;
    };
    TTime2GraphicMap.prototype.size = function () { return this.fRelations.length; };
    return TTime2GraphicMap;
}());
///<reference path="../lib/TTypes.ts"/>
///<reference path="../model/IObject.ts"/>
var VObjectView = (function () {
    function VObjectView() {
    }
    VObjectView.prototype.setMapScaleHandler = function (scale) { };
    return VObjectView;
}());
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
var IBrushStyle = (function () {
    function IBrushStyle() {
        this.fBrush = eBrushStyle.kSolid;
        this.fBrushModified = false;
    }
    IBrushStyle.brushStyleStr2Num = function (str) {
        switch (str) {
            case "solid": return { correct: true, val: eBrushStyle.kSolid };
            case "none": return { correct: true, val: eBrushStyle.kNone };
        }
        return { correct: false, val: 0 };
    };
    IBrushStyle.brushStyleNum2Str = function (n) {
        switch (n) {
            case eBrushStyle.kSolid: return { correct: true, val: "solid" };
            case eBrushStyle.kNone: return { correct: true, val: "none" };
        }
        return { correct: false, val: "" };
    };
    // MODIFIED STATUS
    //--------------------------------------------------------------
    IBrushStyle.prototype.cleanup = function () { this.fBrushModified = false; };
    IBrushStyle.prototype.brushModified = function () { return this.fBrushModified; };
    IBrushStyle.prototype.modify = function () { this.fBrushModified = true; };
    IBrushStyle.prototype.getBrushStyle = function () { return this.fBrush; };
    IBrushStyle.prototype.getBrushStyleStr = function () { return IBrushStyle.brushStyleNum2Str(this.fBrush).val; };
    IBrushStyle.prototype.setBrushStyle = function (brushStyle) {
        var style = IBrushStyle.brushStyleStr2Num(brushStyle);
        if (!style.correct) {
            ITLError.badParameter("brushStyle", brushStyle);
        }
        else {
            this.fBrush = style.val;
            this.fBrushModified = true;
        }
    };
    return IBrushStyle;
}());
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="Constants.ts"/>
var color;
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="Constants.ts"/>
(function (color) {
    color[color["kHue"] = 0] = "kHue";
    color[color["kSat"] = 1] = "kSat";
    color[color["kVal"] = 2] = "kVal";
    color[color["kRed"] = 3] = "kRed";
    color[color["kGreen"] = 4] = "kGreen";
    color[color["kBlue"] = 5] = "kBlue";
    color[color["kAlpha"] = 6] = "kAlpha";
})(color || (color = {}));
var IColor = (function () {
    // CONSTRUTOR
    //--------------------------------------------------------------    
    function IColor(input) {
        this.fA = 255;
        if (input instanceof Array) {
            this.fRGB = input.slice(0, 3);
            if (input.length == 4)
                this.fA = input[3];
        }
        else if (input instanceof IColor) {
            this.set(input);
        }
        this.fHSB = new Array();
        this.updateHSB();
    }
    // MODIFIED STATUS
    //--------------------------------------------------------------      
    IColor.prototype.cleanup = function () { this.fModified = false; };
    IColor.prototype.modify = function () { this.fModified = true; };
    IColor.prototype.modified = function () { return this.fModified; };
    // PROPERTIES COPY
    //--------------------------------------------------------------    
    IColor.prototype.set = function (color) {
        this.fRGB = color.fRGB.slice(0);
        this.fHSB = color.fHSB.slice(0);
        this.fA = color.fA;
        this.fModified = true;
    };
    // GETS VALUES
    //-------------------------------------------------------------- 
    IColor.prototype.getRGB = function () { return this.fRGB.concat(this.fA); };
    IColor.prototype.getHSB = function () { return this.fHSB.concat(this.fA); };
    IColor.prototype.getRGBAString = function () { return "rgba(" + this.fRGB[0] + ", " + this.fRGB[1] + ", " + this.fRGB[2] + ", " + this.fA + ")"; };
    IColor.prototype.getCSSRGBAString = function () { return "rgba(" + this.fRGB[0] + ", " + this.fRGB[1] + ", " + this.fRGB[2] + ", " + this.getSVGA() + ")"; };
    IColor.prototype.getRGBString = function () { return "rgb(" + this.fRGB[0] + ", " + this.fRGB[1] + ", " + this.fRGB[2] + ")"; };
    IColor.prototype.getR = function () { return this.fRGB[0]; };
    IColor.prototype.getG = function () { return this.fRGB[1]; };
    IColor.prototype.getB = function () { return this.fRGB[2]; };
    IColor.prototype.getH = function () { return this.fHSB[0]; };
    IColor.prototype.getS = function () { return this.fHSB[1]; };
    IColor.prototype.getV = function () { return this.fHSB[2]; };
    IColor.prototype.getA = function () { return this.fA; };
    IColor.prototype.getSVGA = function () { return this.fA / 255; };
    // SETS VALUES
    //--------------------------------------------------------------         
    IColor.prototype.setParam = function (param, value, min, max, isHSV) {
        if (min <= value && value <= max) {
            switch (param) {
                case color.kHue:
                    this.fHSB[0] = value;
                    break;
                case color.kSat:
                    this.fHSB[1] = value;
                    break;
                case color.kVal:
                    this.fHSB[2] = value;
                    break;
                case color.kRed:
                    this.fRGB[0] = value;
                    break;
                case color.kGreen:
                    this.fRGB[1] = value;
                    break;
                case color.kBlue:
                    this.fRGB[2] = value;
                    break;
                case color.kAlpha:
                    this.fA = value;
                    break;
                default: console.log("IColor setParam " + param + " not found");
            }
            this.fModified = true;
            if (isHSV)
                this.updateRGB();
            else
                this.updateHSB();
        }
    };
    IColor.prototype.setRGB = function (val) {
        this.fRGB = val.slice(0, 3);
        if (val.length == 4)
            this.fA = val[3];
        this.updateHSB();
        this.fModified = true;
    };
    IColor.prototype.setHSB = function (val) {
        this.fHSB = val.slice(0, 3);
        if (val.length == 4)
            this.fA = val[3];
        this.updateRGB();
        this.fModified = true;
    };
    IColor.prototype.setH = function (h) { this.setParam(color.kHue, Math.floor(h), 0, 360, true); };
    IColor.prototype.setS = function (s) { this.setParam(color.kSat, Math.floor(s), 0, 100, true); };
    IColor.prototype.setV = function (b) { this.setParam(color.kVal, Math.floor(b), 0, 100, true); };
    IColor.prototype.setR = function (r) { this.setParam(color.kRed, Math.floor(r), 0, 255, false); };
    IColor.prototype.setG = function (g) { this.setParam(color.kGreen, Math.floor(g), 0, 255, false); };
    IColor.prototype.setB = function (b) { this.setParam(color.kBlue, Math.floor(b), 0, 255, false); };
    IColor.prototype.setA = function (a) { this.setParam(color.kAlpha, Math.floor(a), 0, 255, false); };
    IColor.prototype.dA = function (a) { this.setA(this.getA() + Math.floor(a)); };
    IColor.prototype.dR = function (r) { this.setR(this.getR() + Math.floor(r)); };
    IColor.prototype.dG = function (g) { this.setG(this.getG() + Math.floor(g)); };
    IColor.prototype.dB = function (b) { this.setB(this.getB() + Math.floor(b)); };
    IColor.prototype.dH = function (h) { this.setH(this.getH() + Math.floor(h)); };
    IColor.prototype.dS = function (s) { this.setS(this.getS() + Math.floor(s)); };
    IColor.prototype.dV = function (b) { this.setB(this.getB() + Math.floor(b)); };
    // UPDATE COLORS
    //--------------------------------------------------------------
    IColor.prototype.updateRGB = function () { this.hsb2rgb(); };
    IColor.prototype.updateHSB = function () { this.rgb2hsb(); };
    // CONVERSIONS COLORS
    //--------------------------------------------------------------    
    IColor.prototype.hsb2rgb = function () {
        var H = this.fHSB[0] / 360;
        var S = this.fHSB[1] / 100;
        var B = this.fHSB[2] / 100;
        var F;
        var M;
        var N;
        var K;
        var I;
        if (S == 0) {
            B = Math.floor(B);
            this.fRGB[0] = B;
            this.fRGB[1] = B;
            this.fRGB[2] = B;
        }
        else {
            if (H >= 1) {
                H = 0.0;
            }
            else {
                H *= 6;
            }
            I = Math.floor(H);
            F = H - I;
            M = B * (1 - S);
            N = B * (1 - S * F);
            K = B * (1 - S * (1 - F));
            switch (I) {
                case 0:
                    this.fRGB[0] = B;
                    this.fRGB[1] = K;
                    this.fRGB[2] = M;
                    break;
                case 1:
                    this.fRGB[1] = B;
                    this.fRGB[0] = N;
                    this.fRGB[2] = M;
                    break;
                case 2:
                    this.fRGB[0] = M;
                    this.fRGB[1] = B;
                    this.fRGB[2] = K;
                    break;
                case 3:
                    this.fRGB[0] = M;
                    this.fRGB[1] = N;
                    this.fRGB[2] = B;
                    break;
                case 4:
                    this.fRGB[0] = K;
                    this.fRGB[1] = M;
                    this.fRGB[2] = B;
                    break;
                case 5:
                    this.fRGB[0] = B;
                    this.fRGB[1] = M;
                    this.fRGB[2] = N;
                    break;
            }
            this.fRGB[0] = Math.floor(this.fRGB[0] * 255);
            this.fRGB[1] = Math.floor(this.fRGB[1] * 255);
            this.fRGB[2] = Math.floor(this.fRGB[2] * 255);
        }
    };
    //-----------------------------  
    IColor.prototype.rgb2hsb = function () {
        var r = this.fRGB[0] / 255;
        var g = this.fRGB[1] / 255;
        var b = this.fRGB[2] / 255;
        // Calculation of maxC and minC
        var maxC = Math.max(r, g, b);
        var minC = Math.min(r, g, b);
        // Calculation of delta
        var delta = maxC - minC;
        var H = 0;
        var S = 0;
        var B = maxC;
        if (delta == 0) {
            H = 0;
            S = 0;
        }
        else {
            S = delta / maxC;
            var dR = 60 * (maxC - r) / delta + 180;
            var dG = 60 * (maxC - g) / delta + 180;
            var dB = 60 * (maxC - b) / delta + 180;
            if (r == maxC) {
                H = dB - dG;
            }
            else if (g == maxC) {
                H = 120 + dR - dB;
            }
            else {
                H = 240 + dG - dR;
            }
        }
        if (H < 0)
            H += 360;
        if (H >= 360)
            H -= 360;
        this.fHSB[0] = Math.floor(H);
        this.fHSB[1] = Math.floor(S * 100);
        this.fHSB[2] = Math.floor(B * 100);
    };
    return IColor;
}());
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>
var IDate = (function () {
    // CONSTRUTOR
    //--------------------------------------------------------------    
    function IDate() {
        this.fDate = new Fraction(0, 1);
        this.fDuration = new Fraction(1, 1);
        this.fModified = true;
        this.fTempo = 0;
    }
    IDate.prototype.modify = function () { this.fModified = true; };
    // PROPERTIES COPY
    //--------------------------------------------------------------    
    IDate.prototype.set = function (obj) {
        this.setDate(obj.fDate);
        this.setDuration(obj.fDuration);
        this.setTempo(obj.fTempo);
    };
    // GETS VALUES
    //--------------------------------------------------------------   
    IDate.prototype.getDate = function () { return this.fDate; };
    IDate.prototype.getDuration = function () { return this.fDuration; };
    IDate.prototype.getTempo = function () { return this.fTempo; };
    // SETS VALUES
    //--------------------------------------------------------------  
    IDate.prototype.setDate = function (date) {
        if (date.getDenominator() == 0)
            return;
        if (this.fDate != date) {
            //handleTimeChange(this.fDate, date);
            this.fDate = date;
            this.modify();
        }
    };
    IDate.prototype.setDuration = function (dur) {
        if (dur.getDenominator() == 0)
            return;
        if (this.fDuration != dur) {
            //handleDurChange(this.fDuration, dur);
            this.fDuration = dur;
            this.modify();
        }
    };
    IDate.prototype.setTempo = function (tempo) { this.fTempo = tempo; this.modify(); };
    IDate.prototype.addDate = function (date) { this.setDate(this.fDate.add(date)); };
    IDate.prototype.addDuration = function (dur) { this.setDuration(this.fDuration.add(dur)); };
    IDate.prototype.addTempo = function (t) { this.setTempo(this.fTempo + t); };
    // MODIFIED STATUS
    //--------------------------------------------------------------
    IDate.prototype.modified = function () { return this.fModified; };
    IDate.prototype.cleanup = function () { this.fModified = false; };
    // CLOCK
    //--------------------------------------------------------------
    IDate.prototype.clockDur = function () { return new Fraction(1, 96); };
    IDate.prototype.clock = function () { this.addDate(this.clockDur()); };
    IDate.prototype.durclock = function () { this.addDuration(this.clockDur()); };
    return IDate;
}());
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/TEnums.ts"/>
var IEffect = (function () {
    function IEffect() {
        this.fEffectModified = false;
        this.fEffectType = eEffect.kNone;
        this.fEffectParams = [];
        IEffect.buildEffect();
    }
    IEffect.buildEffect = function () {
        IEffect.fEffectStr2Num["none"] = eEffect.kNone;
        IEffect.fEffectStr2Num["blur"] = eEffect.kBlur;
        IEffect.fEffectStr2Num["colorize"] = eEffect.kColorize;
        IEffect.fEffectStr2Num["shadow"] = eEffect.kShadow;
        IEffect.fEffectNum2Str[eEffect.kNone] = "none";
        IEffect.fEffectNum2Str[eEffect.kBlur] = "blur";
        IEffect.fEffectNum2Str[eEffect.kColorize] = "colorize";
        IEffect.fEffectNum2Str[eEffect.kShadow] = "shadow";
        IEffect.fEffectParamsNum[eEffect.kNone] = 0;
        IEffect.fEffectParamsNum[eEffect.kBlur] = 1;
        IEffect.fEffectParamsNum[eEffect.kColorize] = 4;
        IEffect.fEffectParamsNum[eEffect.kShadow] = 7;
    };
    IEffect.effectStr2Num = function (str) {
        var val = IEffect.fEffectStr2Num[str];
        return { correct: (typeof val != "undefined"), val: val };
    };
    IEffect.effectNum2Str = function (n) {
        var str = IEffect.fEffectNum2Str[n];
        return { correct: (typeof str != "undefined"), val: str };
    };
    // MODIFIED STATUS
    //--------------------------------------------------------------
    IEffect.prototype.type = function () { return this.fEffectType; };
    IEffect.prototype.params = function () { return this.fEffectParams; };
    IEffect.prototype.param = function (i) { return this.fEffectParams[i]; };
    IEffect.prototype.cleanup = function () { this.fEffectModified = false; };
    IEffect.prototype.effectModified = function () { return this.fEffectModified; };
    IEffect.prototype.modify = function () { this.fEffectModified = true; };
    IEffect.prototype.getEffect = function () {
        var out = new Array();
        out[0] = IEffect.fEffectNum2Str[this.fEffectType];
        return out.concat(this.fEffectParams);
    };
    IEffect.prototype.isNumberArray = function (a) {
        for (var i = 0; i < a.length; i++)
            if (typeof a[i] != "number")
                return false;
        return true;
    };
    IEffect.prototype.assignParams = function (type, params) {
        if (!this.isNumberArray(params))
            return eMsgStatus.kBadParameters;
        if (params.length != IEffect.fEffectParamsNum[type])
            return eMsgStatus.kBadParameters;
        this.fEffectType = type;
        this.fEffectParams = params;
        this.modify();
        return eMsgStatus.kProcessed;
    };
    IEffect.prototype.setEffect = function (params) {
        var style = IEffect.effectStr2Num(params[1]);
        if (!style.correct)
            return eMsgStatus.kBadParameters;
        else
            return this.assignParams(style.val, params.slice(2));
    };
    return IEffect;
}());
IEffect.fEffectStr2Num = {};
IEffect.fEffectNum2Str = {};
IEffect.fEffectParamsNum = []; // expected parameters count
/*

  INScore Project

  Copyright (C) 2016  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/
// WARNING ! this file is generated from Methods.cpp - DO NOT EDIT
var kabsolutexy_GetSetMethod = "absolutexy";
var kaccept_GetSetMethod = "accept";
var kalias_GetSetMethod = "alias";
var kalpha_GetSetMethod = "alpha";
var kanimate_GetSetMethod = "animate";
var kanimated_GetMethod = "animated";
var kangle_GetSetMethod = "angle";
var karrows_GetSetMethod = "arrows";
var kautoScale_SetMethod = "autoscale";
var kautoVoicesColoration_GetSetMethod = "autoVoicesColoration";
var kblue_GetSetMethod = "blue";
var kbrightness_GetSetMethod = "brightness";
var kbrowse_SetMethod = "browse";
var kcancel_SetMethod = "cancel";
var kcliptime_GetSetMethod = "clipTime";
var kclippitch_GetSetMethod = "clipPitch";
var kclock_SetMethod = "clock";
var kclose_GetSetMethod = "close";
var kcolor_GetSetMethod = "color";
var kcolumns_GetSetMethod = "columns";
var kcompatibility_GetSetMethod = "compatibility";
var kcount_GetMethod = "count";
var kconnect_GetSetMethod = "connect";
var kdalpha_SetMethod = "dalpha";
var kdangle_SetMethod = "dangle";
var kdate_GetSetMethod = "date";
var kdblue_SetMethod = "dblue";
var kdbrightness_SetMethod = "dbrightness";
var kdcolor_SetMethod = "dcolor";
var kddate_SetMethod = "ddate";
var kdduration_SetMethod = "dduration";
var kdebug_GetSetMethod = "debug";
var kdefault_GetSetMethod = "default";
var kdefaultShow_GetSetMethod = "defaultShow";
var kdel_SetMethod = "del";
var kdgreen_SetMethod = "dgreen";
var kdhsb_SetMethod = "dhsb";
var kdhue_SetMethod = "dhue";
var kdimension_GetMethod = "dimension";
var kdisconnect_SetMethod = "disconnect";
var kdpage_SetMethod = "dpage";
var kdred_SetMethod = "dred";
var kdrange_SetMethod = "drange";
var kdrotatex_SetMethod = "drotatex";
var kdrotatey_SetMethod = "drotatey";
var kdrotatez_SetMethod = "drotatez";
var kdsaturation_SetMethod = "dsaturation";
var kdscale_SetMethod = "dscale";
var kdstart_SetMethod = "dstart";
var kdtempo_SetMethod = "dtempo";
var kdurClock_SetMethod = "durClock";
var kduration_GetSetMethod = "duration";
var kdx_SetMethod = "dx";
var kdxorigin_SetMethod = "dxorigin";
var kdy_SetMethod = "dy";
var kdyorigin_SetMethod = "dyorigin";
var kdz_SetMethod = "dz";
var kedit_SetMethod = "edit";
var keffect_GetSetMethod = "effect";
var kend_GetSetMethod = "end";
var kerror_SetMethod = "error";
var kerrport_GetSetMethod = "errport";
var kexpression_GetMethod = "expr";
var keval_SetMethod = "eval";
var kevent_SetMethod = "event";
var kexport_SetMethod = "export";
var kexportAll_SetMethod = "exportAll";
var kfontSize_GetSetMethod = "fontSize";
var kfontFamily_GetSetMethod = "fontFamily";
var kfontStyle_GetSetMethod = "fontStyle";
var kfontWeight_GetSetMethod = "fontWeight";
var kforeground_SetMethod = "foreground";
var kforward_GetSetMethod = "forward";
var kframeless_GetSetMethod = "frameless";
var kframe_GetMethod = "frame";
var kfullscreen_GetSetMethod = "fullscreen";
var kget_SetMethod = "get";
var kgreen_GetSetMethod = "green";
var kheight_GetSetMethod = "height";
var khello_SetMethod = "hello";
var khsb_SetMethod = "hsb";
var khue_GetSetMethod = "hue";
var kin_GetMethod = "in";
var kkeyboard_GetSetMethod = "keyboard";
var klevel_GetSetMethod = "level";
var kload_SetMethod = "load";
var klock_GetSetMethod = "lock";
var kmap_GetSetMethod = "map";
var kmapplus_SetMethod = "map+";
var kmapf_SetMethod = "mapf";
var kmeasureBars_GetSetMethod = "measureBars";
var kmls_GetMethod = "mls";
var kmouse_SetMethod = "mouse";
var kname_GetSetMethod = "name";
var knew_SetMethod = "new";
var kopengl_GetSetMethod = "opengl";
var korder_GetSetMethod = "order";
var kosc_GetSetMethod = "osc";
var kout_GetMethod = "out";
var koutport_GetSetMethod = "outport";
var kpage_GetSetMethod = "page";
var kpageCount_GetMethod = "pageCount";
var kpitchLines_GetSetMethod = "pitchLines";
var kpath_GetSetMethod = "path";
var ksystemCount_GetMethod = "systemCount";
var kpageFormat_GetSetMethod = "pageFormat";
var kpenAlpha_GetSetMethod = "penAlpha";
var kpenColor_GetSetMethod = "penColor";
var kpenStyle_GetSetMethod = "penStyle";
var kpenWidth_GetSetMethod = "penWidth";
var kbrushStyle_GetSetMethod = "brushStyle";
var kpendAlpha_SetMethod = "pendAlpha";
var kpop_SetMethod = "pop";
var kplay_GetSetMethod = "play";
var kport_GetSetMethod = "port";
var kpreprocess_SetMethod = "preprocess";
var kpush_SetMethod = "push";
var kquit_SetMethod = "quit";
var kradius_GetSetMethod = "radius";
var krange_GetSetMethod = "range";
var krate_GetSetMethod = "rate";
var krcount_GetMethod = "rcount";
var kred_GetSetMethod = "red";
var kread_SetMethod = "read";
var kreject_GetSetMethod = "reject";
var krequire_SetMethod = "require";
var kreset_SetMethod = "reset";
var kresetBench_SetMethod = "resetBench";
var krootPath_GetSetMethod = "rootPath";
var krotatex_GetSetMethod = "rotatex";
var krotatey_GetSetMethod = "rotatey";
var krotatez_GetSetMethod = "rotatez";
var krows_GetSetMethod = "rows";
var krun_SetMethod = "run";
var ksaturation_GetSetMethod = "saturation";
var ksave_SetMethod = "save";
var kscale_GetSetMethod = "scale";
var kset_SetMethod = "set";
var kshear_GetSetMethod = "shear";
var kshow_GetSetMethod = "show";
//const char* ksignal_GetMethod		= "signal";
var ksize_GetSetMethod = "size";
var kstack_GetMethod = "stack";
var kstart_GetSetMethod = "start";
var kstatus_GetMethod = "status";
var kstartBench_SetMethod = "startBench";
var kstopBench_SetMethod = "stopBench";
var ksuccess_SetMethod = "success";
var ktempo_GetSetMethod = "tempo";
var ktime_GetSetMethod = "time";
var kticks_GetSetMethod = "ticks";
var kversion_GetMethod = "version";
var kguidoVersion_GetMethod = "guido-version";
var kmusicxmlVersion_GetMethod = "musicxml-version";
var kvideoMap_GetSetMethod = "videoMap";
var kvideoMapf_SetMethod = "videoMapf";
var kvoiceColor_GetSetMethod = "voiceColor";
var kvdate_GetSetMethod = "vdate";
var kvduration_GetMethod = "vduration";
var kvolume_GetSetMethod = "volume";
var kwatch_GetSetMethod = "watch";
var kwatchplus_SetMethod = "watch+";
var kwidth_GetSetMethod = "width";
var kwindowOpacity_GetSetMethod = "windowOpacity";
var kwrap_GetSetMethod = "wrap";
var kwriteBench_SetMethod = "writeBench";
var kwrite_SetMethod = "write";
var kx_GetSetMethod = "x";
var kxborder_GetSetMethod = "xborder";
var kxorigin_GetSetMethod = "xorigin";
var ky_GetSetMethod = "y";
var kyborder_GetSetMethod = "yborder";
var kyorigin_GetSetMethod = "yorigin";
var kz_GetSetMethod = "z";
var klearn_SetMethod = "learn";
var kfollow_SetMethod = "follow";
var kstop_SetMethod = "stop";
var klikelihoodwindow_GetSetMethod = "likelihoodwindow";
var klikelihoodthreshold_GetSetMethod = "likelihoodthreshold";
var ktolerance_GetSetMethod = "tolerance";
var kclear_SetMethod = "clear";
var kcalibrate_SetMethod = "calibrate";
var khasZ_GetMethod = "hasZ";
var kmax_GetSetMethod = "max";
var kmode_GetSetMethod = "mode";
var ksmooth_GetSetMethod = "smooth";
;
;
///<reference path="../controller/IMessage.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../model/Methods.ts"/>
///<reference path="../inscore-interface.ts"/>
///<reference path="../parser/MessageInterface.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="TEnv.ts"/>
//-------------------------------------------------------------- 
// Message evaluation:
// consists in:
// 	- evaluation of mouse position variables ($x, $y, $absx, $absy, $sx, $sy)
//	  supports scaling using a [x,y] suffix (position values are expected in the range [-1, 1])
// 	- evaluation of time variables ($date, $rdate)
//	  supports quantification using a [n,d] suffix 
//	  supports date output control using a %f suffix 
// 	- evaluation of the target variables : $name, $scene, $address
// 	- evaluation of variables inside the msg address: $self, $scene)
//-------------------------------------------------------------- 
var TMessageEvaluator = (function () {
    function TMessageEvaluator(env) {
        this.fEnv = env;
        this.fTargetName = this.getOSCName(env.fTarget);
        this.fTargetScene = this.getOSCScene(env.fTarget);
    }
    //----------------------------------------
    TMessageEvaluator.prototype.eval = function (msgs) {
        var out = new IMessageList();
        for (var i = 0; i < msgs.length; i++) {
            var msg = msgs[i];
            var addr = this.evalOSCAddr(msg.address(), this.fEnv);
            var params = this.evalParams(msg.params(), this.fEnv);
            //console.log ("eval: " + msg);
            var outmsg = new IMessage(addr, params);
            //console.log (" => size: " + outmsg.size() + " " + outmsg); 
            out.push(outmsg);
        }
        return out;
    };
    //----------------------------------------
    // private methods
    //----------------------------------------
    TMessageEvaluator.prototype.evalOSCAddr = function (addr, env) {
        return addr.replace("$self", this.fTargetName).replace("$scene", this.fTargetScene);
    };
    //----------------------------------------
    TMessageEvaluator.prototype.evalIndexedVar = function (p, env) {
        if (p.match(/[^0-9]/))
            return null; // check for non numeric chars
        var i = parseInt(p) - 1;
        return ((i >= 0) && (i < env.fUser.length)) ? env.fUser[i] : null;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.dateVar = function (env, scale, relative, float) {
        var d = env.fTimePos;
        if (relative)
            d = d.add(env.fDate);
        if (scale)
            d = d.quantize(scale.first, scale.second);
        return float ? d.toNum() : d.toArray();
    };
    //----------------------------------------
    TMessageEvaluator.prototype.evalParam = function (p, env) {
        if (typeof p === "string") {
            var str = p;
            if ((str.length < 2) || str[0] != '$')
                return p;
            str = str.slice(1); // remove the '$' char
            var user = this.evalIndexedVar(str, env);
            if (user)
                return user;
            var scale = this.getScaling(str); // get scaling option
            var f = this.getScalingFunction(scale);
            var float = str.match(/..*%f/) != null; // get the float option from the variable
            str = str.replace(/[\[%].*/, ""); // get the variable name only
            switch (str) {
                case "absx": return f(env.fMouse.abs.x);
                case "absy": return f(env.fMouse.abs.y);
                case "sx": return f(env.fMouse.parent.x);
                case "sy": return f(env.fMouse.parent.y);
                case "x": return f(env.fMouse.rel.x);
                case "y": return f(env.fMouse.rel.y);
                case "date": return this.dateVar(env, scale, false, float);
                case "rdate": return this.dateVar(env, scale, true, float);
            }
        }
        else if (p.address) {
            return this.evalGetMsg(p, env);
        }
        return p;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.getScaling = function (param) {
        var m = param.replace(/.*\[/, "").replace(/\](%f)?/, ""); // extract the part enclosed in []
        if (m.match(/[^0-9.,-]/))
            return null; // check for non numeric chars
        var t = m.split(',');
        var a = parseFloat(t[0]);
        var b = parseFloat(t[1]);
        if (!isNaN(a) && !isNaN(b))
            return { first: a, second: b };
        return null;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.getScalingFunction = function (p) {
        var identity = function (n) { return n; };
        if (p)
            return function (n) { return p.first + (n + 1) / 2 * (p.second - p.first); };
        return identity;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.evalGetMsg = function (msg, env) {
        var out = [];
        var params = msg.params;
        if ((params.length > 0) && (params[0] === kget_SetMethod)) {
            var addr = this.evalOSCAddr(msg.address.osc, this.fEnv);
            var msgs = INScore.getMessage(addr, params.slice(1));
            msgs.forEach(function (msg) {
                var p = msg.params();
                if (p.length > 1)
                    out = out.concat(p.slice((p[0] == kset_SetMethod) ? 2 : 1));
            });
        }
        return out;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.evalParams = function (params, env) {
        var out = [];
        for (var i = 0; i < params.length; i++) {
            var p = params[i];
            if (p instanceof Array)
                out.push(p); // this is a message list: don't eval now
            else {
                p = this.evalParam(p, env);
                if (p instanceof Array)
                    out = out.concat(p);
                else
                    out.push(p);
            }
        }
        return out;
    };
    //----------------------------------------
    TMessageEvaluator.prototype.getOSCName = function (addr) { return addr.replace(/^..*\//, ""); };
    TMessageEvaluator.prototype.getOSCScene = function (addr) { return addr.replace(/\/[^\/]*\//, "").replace(/\/..*/, ""); };
    return TMessageEvaluator;
}());
;
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/TInterval.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="../scripting/TEnv.ts"/>
///<reference path="../scripting/TMessageEvaluator.ts"/>
///<reference path="Methods.ts"/>
//-----------------------------------------------------------------------------------
var TTimeEvent = (function () {
    function TTimeEvent(interval, msgs) {
        this.fMsgs = [];
        this.fInterval = interval;
        this.fMsgs = msgs;
    }
    TTimeEvent.prototype.toMessage = function (addr, event) { return new IMessage(addr, [event,]); };
    return TTimeEvent;
}());
;
//-----------------------------------------------------------------------------------
var TTimeEventsTable = (function () {
    function TTimeEventsTable(arg) {
        if (typeof arg === "string") {
            this.fEvent = arg;
            this.fTable = [];
        }
        else {
            var tbl = arg;
            this.fEvent = tbl.fEvent;
            this.fTable = tbl.fTable.slice(0);
        }
    }
    TTimeEventsTable.prototype.clear = function () { this.fTable = []; };
    TTimeEventsTable.prototype.size = function () { return this.fTable.length; };
    TTimeEventsTable.prototype.getIndex = function (interval) {
        for (var i = 0; i < this.fTable.length; i++)
            if (interval.eq(this.fTable[i].fInterval))
                return { find: true, index: i };
        return { find: false };
    };
    TTimeEventsTable.prototype.set = function (interval, msgs) {
        var i = this.getIndex(interval);
        var te = new TTimeEvent(interval, msgs);
        if (i.find)
            this.fTable[i.index] = te;
        else
            this.fTable.push(te);
    };
    TTimeEventsTable.prototype.contains = function (d) {
        for (var i = 0; i < this.fTable.length; i++)
            if (this.fTable[i].fInterval.includeLocation(d))
                return { find: true, event: this.fTable[i] };
        return { find: false };
    };
    TTimeEventsTable.prototype.toMsgs = function (addr) {
        var out = [];
        for (var i = 0; i < this.fTable.length; i++) {
            var event_1 = this.fTable[i];
            if (event_1 && event_1.fMsgs.length) {
                for (var n = 0; n < event_1.fMsgs.length; n++) {
                    var msg = event_1.fMsgs[n];
                    var params = [kwatch_GetSetMethod, this.fEvent];
                    params = params.concat(event_1.fInterval.toArray());
                    params = params.concat(["(", msg.toString(), ");"]);
                    out.push(new IMessage(addr, params));
                }
            }
        }
        return out;
    };
    return TTimeEventsTable;
}());
;
//-----------------------------------------------------------------------------------
var InteractionState = (function () {
    //---------------------------------------------------------------
    function InteractionState(state) {
        if (typeof state === "undefined") {
            this.fTimeEnterEvents = new TTimeEventsTable("timeEnter");
            this.fTimeLeaveEvents = new TTimeEventsTable("timeLeave");
            this.fDurEnterEvents = new TTimeEventsTable("durEnter");
            this.fDurLeaveEvents = new TTimeEventsTable("durLeave");
            this.clear();
        }
        else {
            this.fUserEvents = {};
            this.fInternalEvents = {};
            this.fAttributeEvents = {};
            for (var key in state.fUserEvents)
                this.fUserEvents[key] = state.fUserEvents[key];
            for (var key in state.fInternalEvents)
                this.fInternalEvents[key] = state.fInternalEvents[key];
            for (var key in state.fAttributeEvents)
                this.fAttributeEvents[key] = state.fAttributeEvents[key];
            this.fTimeEnterEvents = new TTimeEventsTable(state.fTimeEnterEvents);
            this.fTimeLeaveEvents = new TTimeEventsTable(state.fTimeLeaveEvents);
            this.fDurEnterEvents = new TTimeEventsTable(state.fDurEnterEvents);
            this.fDurLeaveEvents = new TTimeEventsTable(state.fDurLeaveEvents);
        }
    }
    //---------------------------------------------------------------
    InteractionState.prototype.getAttributeMsgs = function (attribute) { return this.fAttributeEvents[attribute]; };
    InteractionState.prototype.getTimeEnter = function (d) { return this.fTimeEnterEvents.contains(d.toNum()); };
    InteractionState.prototype.getTimeLeave = function (d) { return this.fTimeLeaveEvents.contains(d.toNum()); };
    InteractionState.prototype.getDurEnter = function (d) { return this.fDurEnterEvents.contains(d.toNum()); };
    InteractionState.prototype.getDurLeave = function (d) { return this.fDurLeaveEvents.contains(d.toNum()); };
    InteractionState.prototype.getMouseMsgs = function (type) { return this.fInternalEvents[type]; };
    //---------------------------------------------------------------
    InteractionState.prototype.clear = function () {
        this.fUserEvents = {};
        this.fInternalEvents = {};
        this.fAttributeEvents = {};
        this.fAttributeEvents["watch"] = null; // this is for firefox !!!
        this.fTimeEnterEvents.clear();
        this.fTimeLeaveEvents.clear();
        this.fDurEnterEvents.clear();
        this.fDurLeaveEvents.clear();
    };
    //---------------------------------------------------------------
    InteractionState.prototype.event2TimeArray = function (event) {
        if (event === this.fTimeEnterEvents.fEvent)
            return { find: true, tbl: this.fTimeEnterEvents };
        if (event === this.fTimeLeaveEvents.fEvent)
            return { find: true, tbl: this.fTimeLeaveEvents };
        if (event === this.fDurEnterEvents.fEvent)
            return { find: true, tbl: this.fDurEnterEvents };
        if (event === this.fDurLeaveEvents.fEvent)
            return { find: true, tbl: this.fDurLeaveEvents };
        return { find: false };
    };
    //---------------------------------------------------------------
    InteractionState.prototype.getWatch = function (addr) {
        var out = [];
        out = out.concat(this.makeMsgs(this.fInternalEvents, addr));
        out = out.concat(this.makeMsgs(this.fAttributeEvents, addr));
        out = out.concat(this.makeMsgs(this.fUserEvents, addr));
        out = out.concat(this.fTimeEnterEvents.toMsgs(addr));
        out = out.concat(this.fTimeLeaveEvents.toMsgs(addr));
        out = out.concat(this.fDurEnterEvents.toMsgs(addr));
        out = out.concat(this.fDurLeaveEvents.toMsgs(addr));
        if (!out.length)
            out.push(new IMessage(addr, [kwatch_GetSetMethod]));
        return out;
    };
    //---------------------------------------------------------------
    InteractionState.prototype.hasUIEvents = function () {
        var efield = 0;
        for (var i = 0; i < IEventAble.fUIEvents.length; i++) {
            var msgs = this.fInternalEvents[IEventAble.fUIEvents[i]];
            if (msgs && msgs.length)
                efield |= 1 << i;
        }
        return efield;
    };
    //---------------------------------------------------------------
    InteractionState.prototype.makeMsgs = function (tbl, addr) {
        var out = [];
        for (var key in tbl) {
            var msg = tbl[key];
            if (msg) {
                var params = [kwatch_GetSetMethod, key, "(", msg.toString(), ");"];
                out.push(new IMessage(addr, params));
            }
        }
        return out;
    };
    return InteractionState;
}());
//-----------------------------------------------------------------------------------
var IEventAble = (function () {
    //---------------------------------------------------------------
    function IEventAble() {
        this.fAttributesNames = [];
        this.fSpecificEvents = ["newData"];
        this.fState = new InteractionState();
        this.fStatesStack = [];
    }
    IEventAble.prototype.specifics = function (evslist) { this.fSpecificEvents = this.fSpecificEvents.concat(evslist); };
    IEventAble.prototype.attributes = function (a) { for (var key in a)
        this.fAttributesNames.push(key); };
    //---------------------------------------------------------------
    // check the type of an event
    IEventAble.prototype.specificEvent = function (event) { return IEventAble.find(this.fSpecificEvents, event); };
    IEventAble.prototype.attributeEvent = function (event) { return IEventAble.find(this.fAttributesNames, event); };
    //---------------------------------------------------------------
    // give the active UI events as a bit field
    IEventAble.prototype.hasUIEvents = function () { return this.fState.hasUIEvents(); };
    //---------------------------------------------------------------
    // interface for triggering events 
    //---------------------------------------------------------------
    IEventAble.prototype.handleAttributeChange = function (attribute) {
        var msgs = this.fState.getAttributeMsgs(attribute);
        if (msgs && msgs.length)
            this.send(msgs);
    };
    IEventAble.prototype.checkTimeEvent = function (ev, d) {
        if (!ev.fInterval.includeLocation(d)) {
            var msgs = ev.fMsgs;
            if (msgs && msgs.length)
                this.send(msgs);
        }
    };
    IEventAble.prototype.handleTimeChange = function (d1, d2) {
        var t = this.fState.getTimeEnter(d2);
        if (t.find)
            this.checkTimeEvent(t.event, d1.toNum());
        else {
            t = this.fState.getTimeLeave(d1);
            if (t.find)
                this.checkTimeEvent(t.event, d2.toNum());
        }
    };
    IEventAble.prototype.handleDurChange = function (d1, d2) {
        var t = this.fState.getDurEnter(d2);
        if (t.find)
            this.checkTimeEvent(t.event, d1.toNum());
        else {
            t = this.fState.getDurLeave(d1);
            if (t.find)
                this.checkTimeEvent(t.event, d2.toNum());
        }
    };
    IEventAble.prototype.event2evStr = function (ev) {
        switch (ev) {
            case eUIEvents.kMouseDown: return IEventAble.fUIEvents[0];
            case eUIEvents.kMouseMove: return IEventAble.fUIEvents[1];
            case eUIEvents.kMouseUp: return IEventAble.fUIEvents[2];
            case eUIEvents.kMouseEnter: return IEventAble.fUIEvents[3];
            case eUIEvents.kMouseLeave: return IEventAble.fUIEvents[4];
            case eUIEvents.kDoubleClick: return IEventAble.fUIEvents[5];
            case eUIEvents.kTouchBegin: return IEventAble.fUIEvents[6];
            case eUIEvents.kTouchEnd: return IEventAble.fUIEvents[7];
            case eUIEvents.kTouchUpdate: return IEventAble.fUIEvents[8];
        }
        return "";
    };
    IEventAble.prototype.handleMouseEvent = function (type, env) {
        var str = this.event2evStr(type);
        var msgs = this.fState.getMouseMsgs(str);
        if (msgs && msgs.length)
            this.evalAndSend(msgs, env);
    };
    //---------------------------------------------------------------
    // interface for messages handling
    //---------------------------------------------------------------
    // WATCH METHOD
    //---------------------------------------------------------------
    IEventAble.prototype.watch = function (msg) {
        var n = msg.size() - 1; // first param is 'watch'
        if (!n) {
            this.fState.clear(); // no parameter: clear the interaction state
            return eMsgStatus.kProcessed;
        }
        var event = msg.paramStr(1);
        if (!event.correct)
            return eMsgStatus.kBadParameters;
        if (n == 1)
            return this.clear1Event(event.value); // clear the corresponding event
        if (n == 2) {
            var arg = msg.paramArray(2); // fetch the args list
            var a = this.event2StringArray(event.value); // get the target event array
            if (arg.correct && a.find) {
                var msgs = this.msg2msgsArray(arg.value); // converts the array 
                if (msgs.length) {
                    a.tbl[event.value] = msgs;
                    return eMsgStatus.kProcessed;
                }
            }
        }
        else
            return this.timewatch(event.value, msg);
        return eMsgStatus.kBadParameters;
    };
    //---------------------------------------------------------------
    // internal event msg handling
    IEventAble.prototype.ievent = function (ev, env) {
        var a = this.event2StringArray(ev); // look for the table containing the event
        if (a.find) {
            var msgs = a.tbl[ev];
            if (msgs && msgs.length) {
                this.evalAndSend(msgs, env); // request to eval and send the messages
            }
        }
        else
            return eMsgStatus.kBadParameters; // there is no support for time events at this level
        return eMsgStatus.kProcessedNoChange;
    };
    //---------------------------------------------------------------
    // EVENT METHOD
    //---------------------------------------------------------------
    IEventAble.prototype.event = function (msg) {
        var ui = this.hasUIEvents();
        if (msg.size() < 2)
            return eMsgStatus.kBadParameters;
        var event = msg.paramStr(1);
        if (!event.correct)
            return eMsgStatus.kBadParameters;
        var m;
        var d;
        var env = new TEnv(msg.address(), m, d, d, msg.params().slice(2));
        return this.ievent(event.value, env);
    };
    // GET WATCH METHOD
    //--------------------------------------------------------------    
    IEventAble.prototype.getWatch = function (addr) { return this.fState.getWatch(addr); };
    // PUSH & POP METHOD
    //--------------------------------------------------------------    
    IEventAble.prototype.push = function () {
        var copy = new InteractionState(this.fState);
        this.fStatesStack.push(copy);
    };
    IEventAble.prototype.pop = function () {
        if (this.fStatesStack.length)
            this.fState = this.fStatesStack.pop();
    };
    //--------------------------------------------------------------    
    // STATIC METHODS
    //--------------------------------------------------------------    
    IEventAble.find = function (a, s) {
        for (var i = 0; i < a.length; i++)
            if (a[i] === s)
                return true;
        return false;
    };
    //---------------------------------------------------------------
    // check if an event is a user defined event
    IEventAble.userEvent = function (event) {
        var regexp = new RegExp("^[A-Z][A-Z0-9]*$");
        return regexp.test(event);
    };
    IEventAble.uiEvent = function (event) { return IEventAble.find(IEventAble.fUIEvents, event); };
    // PRIVATE METHOD
    //--------------------------------------------------------------    
    //---------------------------------------------------------------
    IEventAble.prototype.send = function (msgs) {
        msgs.forEach(function (msg) { INScore.postMessage(msg.address(), msg.params()); });
    };
    IEventAble.prototype.evalAndSend = function (msgs, env) {
        var me = new TMessageEvaluator(env);
        msgs = me.eval(msgs);
        msgs.forEach(function (msg) { INScore.postMessage(msg.address(), msg.params()); });
    };
    //---------------------------------------------------------------
    IEventAble.prototype.event2StringArray = function (event) {
        if (IEventAble.uiEvent(event))
            return { find: true, tbl: this.fState.fInternalEvents };
        if (IEventAble.userEvent(event))
            return { find: true, tbl: this.fState.fUserEvents };
        if (this.attributeEvent(event))
            return { find: true, tbl: this.fState.fAttributeEvents };
        if (this.attributeEvent(event))
            return { find: true, tbl: this.fState.fAttributeEvents };
        return { find: false };
    };
    //---------------------------------------------------------------
    IEventAble.prototype.msg2msgsArray = function (list) {
        var out = [];
        for (var i = 0; i < list.length; i++) {
            var m = list[i];
            out.push(new IMessage(m.address.toString(), m.params));
        }
        return out;
    };
    //---------------------------------------------------------------
    // clear a single event
    IEventAble.prototype.clear1Event = function (event) {
        var a = this.event2StringArray(event);
        if (a.find)
            a.tbl[event] = []; // clear the corresponding entry
        else {
            var t = this.fState.event2TimeArray(event);
            if (t.find)
                t.tbl.clear(); // clear the corresponding table
            else
                return eMsgStatus.kBadParameters;
        }
        return eMsgStatus.kProcessed;
    };
    //---------------------------------------------------------------
    // look for time intervals in the message parameters
    IEventAble.prototype.params2intervals = function (msg) {
        var n = msg.size() - 2; // first param is watch, second is the event name
        // we're expecting a time interval sepcified as "n1/d1" "n2/d2" | start end | n1 d1 n2 d2
        // followed by an array that is actually the raw messages list
        // i.e. an args count of 3 or 5
        if (n == 5) {
            var n1 = msg.paramNum(2);
            var d1 = msg.paramNum(3);
            var n2 = msg.paramNum(4);
            var d2 = msg.paramNum(5);
            if (n1.correct && n2.correct && d1.correct && d2.correct)
                return { argi: 6, interval: new TimeInterval(new Fraction(n1.value, d1.value), new Fraction(n2.value, d2.value)) };
        }
        else if (n == 3) {
            var start = msg.paramNum(2);
            var end = msg.paramNum(3);
            var startStr = msg.paramStr(2);
            var endStr = msg.paramStr(3);
            if (start.correct && end.correct)
                return { argi: 4, interval: new TimeInterval(new Fraction(start.value, 1), new Fraction(end.value, 1)) };
            else if (startStr.correct && endStr.correct)
                return { argi: 4, interval: new TimeInterval(new Fraction(startStr.value), new Fraction(endStr.value)) };
        }
        return { argi: 0 };
    };
    //---------------------------------------------------------------
    // internal method for time watch msg  handling
    // param event: the event name, decoded by watch
    //---------------------------------------------------------------
    IEventAble.prototype.timewatch = function (event, msg) {
        var a = this.fState.event2TimeArray(event);
        var i = this.params2intervals(msg);
        if (a.find && i.argi) {
            var arg = msg.paramArray(i.argi);
            if (arg.correct) {
                var msgs = this.msg2msgsArray(arg.value);
                if (msgs.length) {
                    a.tbl.set(i.interval.toNumInterval(), msgs);
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    };
    return IEventAble;
}());
//---------------------------------------------------------------
// events definitions
//---------------------------------------------------------------
// WARNING: changing the events order requires to change the eUIEvents enum too
IEventAble.fUIEvents = ["mouseDown", "mouseMove", "mouseUp",
    "mouseEnter", "mouseLeave",
    "doubleClick",
    "touchBegin", "touchEnd", "touchUpdate"];
///<reference path="IObject.ts"/>
var IObjectFactory;
var IObjectFactoryInterface = (function () {
    function IObjectFactoryInterface() {
    }
    return IObjectFactoryInterface;
}());
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IColor.ts"/>
var IPenControl = (function () {
    function IPenControl(type) {
        this.fPenWidth = 0;
        if (type == kLineType) {
            this.fPenWidth = 1;
        }
        this.fPenColor = new IColor([0, 0, 0, 255]);
        this.fPenStyle = ePenStyle.kSolid;
        IPenControl.buildPenStyle();
    }
    // MODIFIED STATUS
    //--------------------------------------------------------------      
    IPenControl.prototype.cleanup = function () { this.fModified = false; };
    IPenControl.prototype.modified = function () { return this.fModified; };
    IPenControl.prototype.modify = function () { this.fModified = true; };
    IPenControl.buildPenStyle = function () {
        IPenControl.fPenStyleStr2Num["solid"] = ePenStyle.kSolid;
        IPenControl.fPenStyleStr2Num["dash"] = ePenStyle.kDash;
        IPenControl.fPenStyleStr2Num["dot"] = ePenStyle.kDot;
        IPenControl.fPenStyleStr2Num["dashDot"] = ePenStyle.kDashDot;
        IPenControl.fPenStyleStr2Num["dashDotDot"] = ePenStyle.kDashDotDot;
        IPenControl.fPenStyleNum2Str[ePenStyle.kSolid] = "solid";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDash] = "dashed";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDot] = "dotted";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDashDot] = "dashDot";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDashDotDot] = "dashDotDot";
    };
    IPenControl.penStyleStr2Num = function (str) {
        var val = IPenControl.fPenStyleStr2Num[str];
        return { correct: (typeof val != "undefined"), val: val };
    };
    IPenControl.penStyleNum2Str = function (n) {
        var str = IPenControl.fPenStyleNum2Str[n];
        return { correct: (typeof str != "undefined"), val: str };
    };
    IPenControl.prototype.getPenWidth = function () { return this.fPenWidth; };
    IPenControl.prototype.getPenColor = function () { return this.fPenColor; };
    IPenControl.prototype.getPenStyle = function () { return IPenControl.penStyleNum2Str(this.fPenStyle).val; };
    IPenControl.prototype.getPenStyleNum = function () { return this.fPenStyle; };
    IPenControl.prototype.getPenAlpha = function () { return this.fPenColor.getA(); };
    IPenControl.prototype.setPenWidth = function (penWidth) { this.fPenWidth = penWidth; this.modify(); };
    IPenControl.prototype.setPenColor = function (penColor) { this.fPenColor.set(penColor); this.modify(); };
    IPenControl.prototype.setPenStyle = function (ePenStyle) {
        var style = IPenControl.penStyleStr2Num(ePenStyle);
        if (!style.correct) {
            ITLError.badParameter("ePenStyle", ePenStyle);
        }
        else {
            this.fPenStyle = style.val;
            this.modify();
        }
    };
    IPenControl.prototype.setPenAlpha = function (penAlpha) { this.fPenColor.setA(penAlpha); this.modify(); };
    return IPenControl;
}());
IPenControl.fPenStyleStr2Num = {};
IPenControl.fPenStyleNum2Str = {};
///<reference path="../controller/THandlersPrototypes.ts"/>
var IPosition = (function () {
    // CONSTRUTOR
    //--------------------------------------------------------------    
    function IPosition() {
        this.kDefaultX = 0;
        this.kDefaultY = 0;
        this.fXPos = this.kDefaultX;
        this.fYPos = this.kDefaultY;
        this.fXOrigin = 0;
        this.fYOrigin = 0;
        this.fWidth = 0;
        this.fHeight = 0;
        this.fZOrder = 0;
        this.fVisible = 1;
        this.fScale = 1.0;
        this.fXAngle = 0;
        this.fYAngle = 0;
        this.fZAngle = 0;
        this.fShear = [0, 0];
        this.fModified = true;
    }
    // PROPERTIES COPY
    //--------------------------------------------------------------    
    IPosition.prototype.set = function (pos) {
        this.fXPos = pos.fXPos;
        this.fYPos = pos.fYPos;
        this.fXOrigin = pos.fXOrigin;
        this.fYOrigin = pos.fYOrigin;
        //        this.fWidth 	= pos.fWidth; 
        //        this.fHeight 	= pos.fHeight;
        this.fZOrder = pos.fZOrder;
        this.fVisible = pos.fVisible;
        this.fScale = pos.fScale;
        this.fXAngle = pos.fXAngle;
        this.fYAngle = pos.fYAngle;
        this.fZAngle = pos.fZAngle;
        this.fShear[0] = pos.fShear[0];
        this.fShear[1] = pos.fShear[1];
        this.fModified = true;
    };
    // MODIFIED STATUS
    //--------------------------------------------------------------          
    IPosition.prototype.modified = function () { return this.fModified; };
    IPosition.prototype.modify = function () { this.fModified = true; };
    IPosition.prototype.cleanup = function () { this.fModified = false; };
    // GETS
    //--------------------------------------------------------------
    IPosition.prototype.getXPos = function () { return this.fXPos; };
    IPosition.prototype.getYPos = function () { return this.fYPos; };
    IPosition.prototype.getXOrigin = function () { return this.fXOrigin; };
    IPosition.prototype.getYOrigin = function () { return this.fYOrigin; };
    IPosition.prototype.getZOrder = function () { return this.fZOrder; };
    IPosition.prototype.getScale = function () { return this.fScale; };
    IPosition.prototype.getPos = function () { return [this.fXPos, this.fYPos]; };
    IPosition.prototype.getShear = function () { return this.fShear; };
    IPosition.prototype.getRotateX = function () { return this.fXAngle; };
    IPosition.prototype.getRotateY = function () { return this.fYAngle; };
    IPosition.prototype.getRotateZ = function () { return this.fZAngle; };
    IPosition.prototype.getWidth = function () { return this.fWidth; };
    IPosition.prototype.getHeight = function () { return this.fHeight; };
    IPosition.prototype.getDimension = function () { return [this.fWidth, this.fHeight]; };
    IPosition.prototype.getVisible = function () { return this.fVisible; };
    // SETS 
    //--------------------------------------------------------------    
    IPosition.prototype.setPos = function (p) {
        this.setXPos(p.getXPos());
        this.setYPos(p.getYPos());
        this.setZOrder(p.getZOrder());
        this.setScale(p.getScale());
        this.setRotateX(p.getRotateX());
        this.setRotateY(p.getRotateY());
        this.setRotateZ(p.getRotateZ());
        this.setWidth(p.getWidth());
        this.setHeight(p.getHeight());
        this.setVisible(p.getVisible());
    };
    IPosition.prototype.setWidth = function (width) { this.fWidth = width; };
    IPosition.prototype.setHeight = function (height) { this.fHeight = height; };
    IPosition.prototype.setXPos = function (x) { this.fXPos = x; this.fModified = true; };
    IPosition.prototype.addXPos = function (x) { this.setXPos(this.fXPos + x); };
    IPosition.prototype.setXOrigin = function (x) { this.fXOrigin = x; this.fModified = true; };
    IPosition.prototype.addXOrigin = function (x) { this.setXOrigin(this.fXOrigin + x); };
    IPosition.prototype.setYPos = function (y) { this.fYPos = y; this.fModified = true; };
    IPosition.prototype.addYPos = function (y) { this.setYPos(this.fYPos + y); };
    IPosition.prototype.setYOrigin = function (y) { this.fYOrigin = y; this.fModified = true; };
    IPosition.prototype.addYOrigin = function (y) { this.setYOrigin(this.fYOrigin + y); };
    IPosition.prototype.setScale = function (scale) { this.fScale = scale; this.fModified = true; };
    IPosition.prototype.multScale = function (scale) { this.setScale(this.fScale * scale); };
    IPosition.prototype.setVisible = function (vis) { this.fVisible = vis; this.fModified = true; };
    IPosition.prototype.setZOrder = function (z) { this.fZOrder = z; this.fModified = true; };
    IPosition.prototype.addZOrder = function (z) { this.setZOrder(this.fZOrder + z); };
    IPosition.prototype.addAngle = function (angle) { this.setRotateZ(this.fZAngle + angle); };
    IPosition.prototype.addXAngle = function (angle) { this.setRotateX(this.fXAngle + angle); };
    IPosition.prototype.addYAngle = function (angle) { this.setRotateY(this.fYAngle + angle); };
    IPosition.prototype.setRotateX = function (a) { this.fXAngle = a; this.fModified = true; };
    IPosition.prototype.setRotateY = function (a) { this.fYAngle = a; this.fModified = true; };
    IPosition.prototype.setRotateZ = function (a) { this.fZAngle = a; this.fModified = true; };
    IPosition.prototype.setShear = function (a) {
        if (a.length != 2)
            return eMsgStatus.kBadParameters;
        this.fShear = a;
        this.fModified = true;
        return eMsgStatus.kProcessed;
    };
    return IPosition;
}());
///<reference path="../controller/IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="IObject.ts"/>
var IProxy;
var IProxyInterface = (function () {
    function IProxyInterface() {
    }
    return IProxyInterface;
}());
var kposition_GetSetMethod = "position";
///<reference path="../controller/IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
//--------------------------------------------------------------  
// synchronisation: 
//--------------------------------------------------------------  
var TSyncInfo = (function () {
    function TSyncInfo() {
        this.fMode = eSyncModes.kAbsolute;
        this.fPosition = eSyncPosition.kSyncOver;
        this.fStretch = eSyncStretch.kSyncDate;
    }
    //---------------------------------------------
    TSyncInfo.prototype.update = function (info) {
        this.fMode = info.fMode;
        this.fPosition = info.fPosition;
        this.fStretch = info.fStretch;
    };
    //---------------------------------------------
    TSyncInfo.prototype.set = function (msg) {
        for (var i = 2; i < msg.size(); i++) {
            var param = msg.paramStr(i);
            if (!param.correct)
                return false;
            switch (param.value) {
                case TSyncInfo.kSyncHStr:
                    this.fStretch = eSyncStretch.kSyncH;
                    break;
                case TSyncInfo.kSyncVStr:
                    this.fStretch = eSyncStretch.kSyncV;
                    break;
                case TSyncInfo.kSyncHVStr:
                    this.fStretch = eSyncStretch.kSyncH + eSyncStretch.kSyncV;
                    break;
                case TSyncInfo.kSyncOverStr:
                    this.fPosition = eSyncPosition.kSyncOver;
                    break;
                case TSyncInfo.kSyncTopStr:
                    this.fPosition = eSyncPosition.kSyncTop;
                    break;
                case TSyncInfo.kSyncBottomStr:
                    this.fPosition = eSyncPosition.kSyncBottom;
                    break;
                case TSyncInfo.kSyncFrameStr:
                    this.fPosition = eSyncPosition.kSyncFrame;
                    break;
                case TSyncInfo.kSyncRelativeStr:
                    this.fMode = eSyncModes.kRelative;
                    break;
                case TSyncInfo.kSyncAbsoluteStr:
                    this.fMode = eSyncModes.kAbsolute;
                    break;
                default: return false;
            }
        }
        return true;
    };
    //---------------------------------------------
    // conversion methods
    //---------------------------------------------
    TSyncInfo.prototype.toString = function () {
        return TSyncInfo.stretch2String(this.fStretch) + " " + TSyncInfo.mode2String(this.fMode)
            + " " + TSyncInfo.pos2String(this.fPosition);
    };
    TSyncInfo.prototype.toArray = function () {
        var out = [];
        if (this.fStretch != eSyncStretch.kSyncDate)
            out.push(TSyncInfo.stretch2String(this.fStretch));
        if (this.fMode == eSyncModes.kRelative)
            out.push(TSyncInfo.mode2String(this.fMode));
        if (this.fPosition != eSyncPosition.kSyncOver)
            out.push(TSyncInfo.pos2String(this.fPosition));
        return out;
    };
    //---------------------------------------------
    // static methods
    //---------------------------------------------
    TSyncInfo.mode2String = function (mode) { return mode == eSyncModes.kRelative ? "relative" : ""; };
    TSyncInfo.pos2String = function (pos) {
        switch (pos) {
            case eSyncPosition.kSyncOver: return ""; // default mode
            case eSyncPosition.kSyncTop: return "syncTop";
            case eSyncPosition.kSyncBottom: return "syncBottom";
            case eSyncPosition.kSyncFrame: return "syncFrame";
        }
        return "";
    };
    TSyncInfo.stretch2String = function (v) {
        var out = "";
        if (v & eSyncStretch.kSyncH)
            out += "h";
        if (v & eSyncStretch.kSyncV)
            out += "v";
        return out;
    };
    return TSyncInfo;
}());
TSyncInfo.kSyncHStr = "h";
TSyncInfo.kSyncVStr = "v";
TSyncInfo.kSyncHVStr = "hv";
TSyncInfo.kSyncOverStr = "syncOver";
TSyncInfo.kSyncTopStr = "syncTop";
TSyncInfo.kSyncBottomStr = "syncBottom";
TSyncInfo.kSyncFrameStr = "syncFrame";
TSyncInfo.kSyncAbsoluteStr = "absolute";
TSyncInfo.kSyncRelativeStr = "relative";
///<reference path="../controller/TGetMessageHandlers.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../scripting/TEnv.ts"/>
///<reference path="../inscore-interface.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/ITLOut.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../globals.ts"/>
///<reference path="Constants.ts"/>
///<reference path="IBrushStyle.ts"/>
///<reference path="IColor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IEffect.ts"/>
///<reference path="IEventAble.ts"/>
///<reference path="IObjectFactory-interface.ts"/>
///<reference path="IPenControl.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="IProxyInterface.ts"/>
///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>
///<reference path="TSyncInfo.ts"/>
var TMsgHandler = (function () {
    function TMsgHandler() {
    }
    return TMsgHandler;
}());
var TGetMsgHandler = (function () {
    function TGetMsgHandler() {
    }
    return TGetMsgHandler;
}());
//-------------------------------------------------------------- 
// IObject - the base class of inscore model
//-------------------------------------------------------------- 
var IObject = (function () {
    // CONSTRUCTOR
    //--------------------------------------------------------------       
    function IObject(name, parent) {
        this.fSubNodes = new Array;
        this.fName = name;
        this.fTypeString = 'obj';
        this.fObjectView = [];
        this.fDelete = false;
        this.fLock = false;
        this.fState = eObjState.kNewObject;
        this.fNewData = true;
        this.fParent = parent;
        this.fPosition = new IPosition;
        this.fDate = new IDate;
        this.fColor = new IColor([0, 0, 0]);
        this.fPenControl = new IPenControl(kObjType);
        this.fBrushStyle = new IBrushStyle();
        this.fEffect = new IEffect();
        this.fEvents = new IEventAble();
        this.fMsgHandlerMap = new TMsgHandler();
        this.fGetMsgHandlerMap = new TGetMsgHandler();
        this.fGetMsgsHandlerMap = new TGetMsgHandler();
        this.fMsgHandlerMap["watch"] = null; // !!! firefox hack
        this.fGetMsgHandlerMap["watch"] = null; // !!! firefox hack
        this.fGetMsgsHandlerMap["watch"] = null; // !!! firefox hack
        this.setHandlers();
        this.createStaticNodes();
        this.fEvents.attributes(this.fMsgHandlerMap);
        this.fMapping = this.createMapping();
    }
    IObject.prototype.createMapping = function () {
        var map = new TTime2GraphicMap();
        var defaultTimeSegment = new TimeInterval(new Fraction(0, 1), this.fDate.getDuration());
        var defaultGraphicSegment = new TGraphicSegment(new NumberInterval(0, 1), new NumberInterval(0, 1));
        map.addElt(new TTime2GraphicRelation(defaultTimeSegment, defaultGraphicSegment));
        return map;
    };
    IObject.prototype.createStaticNodes = function () {
        this.fDebug = IObjectFactory.createObj("debug", kDebugType, this);
        this.addChild(this.fDebug);
        this.fSync = IObjectFactory.createObj("sync", kSyncType, this);
        this.addChild(this.fSync);
    };
    // HANDLERS
    //--------------------------------------------------------------  
    IObject.prototype.setHandlers = function () {
        var _this = this;
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler(function (msg) { return _this.set(msg); });
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(function (msg) { return _this.get(msg); });
        this.fMsgHandlerMap[ksave_SetMethod] = new TMethodHandler(function (msg) { return _this.save(msg); });
        this.fMsgHandlerMap[kdel_SetMethod] = new TMsgHandlerVoid(function () { _this.del(); });
        this.eventAble();
        this.colorAble();
        this.positionAble();
        this.timeAble();
        this.penControlAble();
        this.effectAble();
    };
    // intended for ILine : the target is always the pen color
    IObject.prototype.getColorTarget = function () { return this.fColor; };
    ;
    IObject.prototype.eventAble = function () {
        var _this = this;
        this.fMsgHandlerMap[kwatch_GetSetMethod] = new TMethodHandler(function (msg) { return _this.fEvents.watch(msg); });
        this.fMsgHandlerMap[kevent_SetMethod] = new TMethodHandler(function (msg) { return _this.fEvents.event(msg); });
        this.fMsgHandlerMap[kpush_SetMethod] = new TMsgHandlerVoid(function () { _this.fEvents.push(); });
        this.fMsgHandlerMap[kpop_SetMethod] = new TMsgHandlerVoid(function () { _this.fEvents.pop(); });
        this.fGetMsgsHandlerMap[kwatch_GetSetMethod] = new TGetMsgsHandler(function () { var osc = _this.getOSCAddress(); return _this.fEvents.getWatch(osc); });
    };
    IObject.prototype.colorAble = function () {
        var target = this.getColorTarget();
        this.fMsgHandlerMap[kcolor_GetSetMethod] = new TMsgHandlerColor(function (a) { target.setRGB(a); });
        this.fMsgHandlerMap[khsb_SetMethod] = new TMsgHandlerColor(function (a) { target.setHSB(a); });
        this.fMsgHandlerMap[kred_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setR(n); });
        this.fMsgHandlerMap[kgreen_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setG(n); });
        this.fMsgHandlerMap[kblue_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setB(n); });
        this.fMsgHandlerMap[kalpha_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setA(n); });
        this.fMsgHandlerMap[khue_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setH(n); });
        this.fMsgHandlerMap[ksaturation_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setS(n); });
        this.fMsgHandlerMap[kbrightness_GetSetMethod] = new TMsgHandlerNum(function (n) { target.setV(n); });
        this.fMsgHandlerMap[kdred_SetMethod] = new TMsgHandlerNum(function (n) { target.dR(n); });
        this.fMsgHandlerMap[kdgreen_SetMethod] = new TMsgHandlerNum(function (n) { target.dG(n); });
        this.fMsgHandlerMap[kdblue_SetMethod] = new TMsgHandlerNum(function (n) { target.dB(n); });
        this.fMsgHandlerMap[kdalpha_SetMethod] = new TMsgHandlerNum(function (n) { target.dA(n); });
        this.fMsgHandlerMap[kdhue_SetMethod] = new TMsgHandlerNum(function (n) { target.dH(n); });
        this.fMsgHandlerMap[kdsaturation_SetMethod] = new TMsgHandlerNum(function (n) { target.dS(n); });
        this.fMsgHandlerMap[kdbrightness_SetMethod] = new TMsgHandlerNum(function (n) { target.dV(n); });
        this.fGetMsgHandlerMap[kcolor_GetSetMethod] = new TGetMsgHandlerArray(function () { return target.getRGB(); });
        this.fGetMsgHandlerMap[khsb_SetMethod] = new TGetMsgHandlerArray(function () { return target.getHSB(); });
        this.fGetMsgHandlerMap[kred_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getR(); });
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getG(); });
        this.fGetMsgHandlerMap[kblue_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getB(); });
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getA(); });
        this.fGetMsgHandlerMap[khue_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getH(); });
        this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getS(); });
        this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetMsgHandlerNum(function () { return target.getV(); });
    };
    IObject.prototype.positionAble = function () {
        var _this = this;
        this.fMsgHandlerMap[kx_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setXPos(n); });
        this.fMsgHandlerMap[ky_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setYPos(n); });
        this.fMsgHandlerMap[kxorigin_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setXOrigin(n); });
        this.fMsgHandlerMap[kyorigin_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setYOrigin(n); });
        this.fMsgHandlerMap[kz_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setZOrder(n); });
        this.fMsgHandlerMap[kangle_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setRotateZ(n); });
        this.fMsgHandlerMap[kscale_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setScale(n); });
        this.fMsgHandlerMap[krotatex_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setRotateX(n); });
        this.fMsgHandlerMap[krotatey_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setRotateY(n); });
        this.fMsgHandlerMap[krotatez_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setRotateZ(n); });
        this.fMsgHandlerMap[kshear_GetSetMethod] = new TMsgHandlerNumArray(function (a) { return _this.fPosition.setShear(a); });
        this.fMsgHandlerMap[kdx_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addXPos(n); });
        this.fMsgHandlerMap[kdy_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addYPos(n); });
        this.fMsgHandlerMap[kdxorigin_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addXOrigin(n); });
        this.fMsgHandlerMap[kdyorigin_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addYOrigin(n); });
        this.fMsgHandlerMap[kdz_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addZOrder(n); });
        this.fMsgHandlerMap[kdangle_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addAngle(n); });
        this.fMsgHandlerMap[kdscale_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.multScale(n); });
        this.fMsgHandlerMap[kdrotatex_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addXAngle(n); });
        this.fMsgHandlerMap[kdrotatey_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addYAngle(n); });
        this.fMsgHandlerMap[kdrotatez_SetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.addAngle(n); });
        this.fMsgHandlerMap[kshow_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setVisible(n); });
        this.fGetMsgHandlerMap[kx_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getXPos(); });
        this.fGetMsgHandlerMap[ky_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getYPos(); });
        this.fGetMsgHandlerMap[kxorigin_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getXOrigin(); });
        this.fGetMsgHandlerMap[kyorigin_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getYOrigin(); });
        this.fGetMsgHandlerMap[kz_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getZOrder(); });
        this.fGetMsgHandlerMap[kangle_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getRotateZ(); });
        this.fGetMsgHandlerMap[kscale_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getScale(); });
        this.fGetMsgHandlerMap[kshow_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getVisible(); });
        this.fGetMsgHandlerMap[kwidth_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getWidth(); });
        this.fGetMsgHandlerMap[kheight_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getHeight(); });
        this.fGetMsgHandlerMap[krotatex_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getRotateX(); });
        this.fGetMsgHandlerMap[krotatey_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getRotateY(); });
        this.fGetMsgHandlerMap[krotatez_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getRotateZ(); });
        this.fGetMsgHandlerMap[kshear_GetSetMethod] = new TGetMsgHandlerArray(function () { return _this.fPosition.getShear(); });
    };
    IObject.prototype.timeAble = function () {
        var _this = this;
        this.fMsgHandlerMap[kdate_GetSetMethod] = new TMsgHandlerTime(function (d) { _this.setDate(d); });
        this.fMsgHandlerMap[kduration_GetSetMethod] = new TMsgHandlerTime(function (d) { _this.setDuration(d); });
        this.fMsgHandlerMap[kddate_SetMethod] = new TMsgHandlerTime(function (d) { _this.addDate(d); });
        this.fMsgHandlerMap[kdduration_SetMethod] = new TMsgHandlerTime(function (d) { _this.addDuration(d); });
        this.fMsgHandlerMap[kclock_SetMethod] = new TMsgHandlerVoid(function () { _this.clock(); });
        this.fMsgHandlerMap[kdurClock_SetMethod] = new TMsgHandlerVoid(function () { _this.durclock(); });
        this.fMsgHandlerMap[ktempo_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fDate.setTempo(n); });
        this.fMsgHandlerMap[kdtempo_SetMethod] = new TMsgHandlerNum(function (n) { _this.fDate.addTempo(n); });
        this.fGetMsgHandlerMap[ktempo_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fDate.getTempo(); });
        this.fGetMsgHandlerMap[kduration_GetSetMethod] = new TGetMsgHandlerTime(function () { return _this.fDate.getDuration(); });
        this.fGetMsgHandlerMap[kdate_GetSetMethod] = new TGetMsgHandlerTime(function () { return _this.fDate.getDate(); });
    };
    IObject.prototype.penControlAble = function () {
        var _this = this;
        this.fMsgHandlerMap[kpenWidth_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPenControl.setPenWidth(n); });
        this.fMsgHandlerMap[kpenColor_GetSetMethod] = new TMsgHandlerColor(function (c) { _this.fPenControl.setPenColor(new IColor(c)); });
        this.fMsgHandlerMap[kpenStyle_GetSetMethod] = new TMsgHandlerText(function (s) { _this.fPenControl.setPenStyle(s); });
        this.fMsgHandlerMap[kpenAlpha_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPenControl.setPenAlpha(n); });
        this.fGetMsgHandlerMap[kpenWidth_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPenControl.getPenWidth(); });
        this.fGetMsgHandlerMap[kpenColor_GetSetMethod] = new TGetMsgHandlerArray(function () { return _this.fPenControl.getPenColor().getRGB(); });
        this.fGetMsgHandlerMap[kpenStyle_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.fPenControl.getPenStyle(); });
        this.fGetMsgHandlerMap[kpenAlpha_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPenControl.getPenAlpha(); });
    };
    IObject.prototype.brushAble = function () {
        var _this = this;
        this.fGetMsgHandlerMap[kbrushStyle_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.fBrushStyle.getBrushStyleStr(); });
        this.fMsgHandlerMap[kbrushStyle_GetSetMethod] = new TMsgHandlerText(function (s) { _this.fBrushStyle.setBrushStyle(s); });
    };
    IObject.prototype.effectAble = function () {
        var _this = this;
        this.fGetMsgHandlerMap[keffect_GetSetMethod] = new TGetMsgHandlerArray(function () { return _this.fEffect.getEffect(); });
        this.fMsgHandlerMap[keffect_GetSetMethod] = new TMsgHandlerAnyArray(function (e) { return _this.fEffect.setEffect(e); });
    };
    //--------------------------------------------------------------  
    // Special handlers
    //--------------------------------------------------------------  
    // size change requires the modification state to be 
    // recursively propagated to all subnodes
    //--------------------------------------------------------------  
    IObject.prototype.setWidth = function (width) { this.fPosition.setWidth(width); this.posPropagate(); };
    IObject.prototype.setHeight = function (height) { this.fPosition.setHeight(height); this.posPropagate(); };
    IObject.prototype.setScale = function (scale) { this.fPosition.setScale(scale); this.posPropagate(); };
    IObject.prototype.subModPropagate = function (obj) { if (obj) {
        obj.addState(eObjState.kSubModified);
        this.subModPropagate(obj.fParent);
    } };
    IObject.prototype.posPropagate = function () { var a = new IObjectTreeApply(); a.applyPosModified(this); };
    IObject.prototype.posModified = function () { this.fPosition.modify(); this.addState(eObjState.kModified + eObjState.kSubModified); };
    IObject.prototype.allModified = function () {
        this.addState(eObjState.kModified);
        this.fPosition.modify();
        this.fDate.modify();
        this.fColor.modify();
        this.fPenControl.modify();
        this.fBrushStyle.modify();
        this.fEffect.modify();
    };
    //-------------------------------------------------------------- 
    // decorate date and duration messages to handle time events
    //--------------------------------------------------------------  
    IObject.prototype.setDate = function (d) { this.fEvents.handleTimeChange(this.fDate.getDate(), d); this.fDate.setDate(d); };
    IObject.prototype.addDate = function (d) { this.setDate(this.fDate.getDate().add(d)); };
    IObject.prototype.clock = function () { this.setDate(this.fDate.getDate().add(this.fDate.clockDur())); };
    IObject.prototype.setDuration = function (d) { this.fEvents.handleDurChange(this.fDate.getDuration(), d); this.fDate.setDuration(d); };
    IObject.prototype.addDuration = function (d) { this.setDuration(this.fDate.getDuration().add(d)); };
    IObject.prototype.durclock = function () { this.setDuration(this.fDate.getDuration().add(this.fDate.clockDur())); };
    //-------------------------------------------------------------- 
    // UI events management
    //--------------------------------------------------------------  
    IObject.prototype.hasUIEvents = function () { return this.fEvents.hasUIEvents(); };
    IObject.prototype.handleMouseEvent = function (type, mouse, date) {
        var env = new TEnv(this.getOSCAddress(), mouse, this.fDate.getDate(), date);
        this.fEvents.handleMouseEvent(type, env);
    };
    //-------------------------------------------------------------- 
    // Mappings
    //--------------------------------------------------------------  
    IObject.prototype.mapPoint2Date = function (point) { return this.fMapping.mapPoint2Date(point); };
    IObject.prototype.date2MapLocation = function (date) { return this.fMapping.date2MapLocation(date); };
    IObject.prototype.date2FramePoint = function (date) {
        var dur = this.fDate.getDuration().toNum();
        var dnum = date.toNum();
        if (dnum > dur)
            return { x: kNoPosition, y: 0 };
        // the length corresponding to the date
        // 8 is 4 x 2 where 2 is the internal dimension of an object
        var dlen = kObjectSize * 4 * dnum / dur;
        if (dlen <= kObjectSize)
            return { x: dlen - 1, y: -1 };
        dlen -= kObjectSize;
        if (dlen <= kObjectSize)
            return { x: 1, y: dlen - 1 };
        dlen -= kObjectSize;
        if (dlen <= kObjectSize)
            return { x: 1 - dlen, y: 1 };
        dlen -= kObjectSize;
        return { x: -1, y: 1 - dlen };
    };
    // METHODS
    //--------------------------------------------------------------  
    IObject.prototype.addChild = function (obj) {
        this.fSubNodes.push(obj);
        this.addState(eObjState.kSubModified);
    };
    IObject.prototype.setParent = function (parent) { this.fParent = parent; };
    IObject.prototype.getParent = function () { return this.fParent; };
    IObject.prototype.getSubNodes = function () { return this.fSubNodes; };
    IObject.prototype.getSubNodesCount = function () { return this.fSubNodes.length; };
    IObject.prototype.getAppl = function () { return this.fParent.getAppl(); };
    IObject.prototype.getScene = function () { return this.fParent.getScene(); };
    // get the object scale recursively
    IObject.prototype.getRScale = function () { return this.fPosition.getScale() * this.fParent.getRScale(); };
    // get the object size as scale recursively - takes account of the smallest dimension
    IObject.prototype.getRSizeAsScale = function () {
        var size = Math.min(this.fPosition.getWidth(), this.fPosition.getHeight());
        return size / 2 * this.fParent.getRSizeAsScale();
    };
    IObject.prototype.getPosition = function () { return { x: this.fPosition.getXPos(), y: this.fPosition.getYPos() }; };
    IObject.prototype.getSize = function () { return { w: this.fPosition.getWidth(), h: this.fPosition.getHeight() }; };
    IObject.prototype.getRotate = function () { return { x: this.fPosition.getRotateX(), y: this.fPosition.getRotateY(), z: this.fPosition.getRotateZ() }; };
    IObject.prototype.getSlavePosition = function (master, syncparams) {
        if (syncparams.fPosition == eSyncPosition.kSyncFrame) {
            var pos_1 = this.date2FramePoint(this.fDate.getDate());
            return pos_1;
        }
        var pos = master.date2MapLocation(this.fDate.getDate());
        var y = 0;
        switch (syncparams.fPosition) {
            case eSyncPosition.kSyncTop:
                y = pos.y.first();
                break;
            case eSyncPosition.kSyncBottom:
                y = pos.y.second();
                break;
            case eSyncPosition.kSyncOver:
            default: y = pos.y.first() + pos.y.size() / 2;
        }
        return { x: pos.x, y: y };
    };
    IObject.prototype.toString = function () {
        var n = this.fSubNodes.length;
        var substr = "";
        if (n)
            substr = " [" + this.fSubNodes + "] ";
        return this.fName + substr;
    };
    //-----------------------------    
    IObject.prototype.getName = function () { return this.fName; };
    IObject.prototype.getTypeString = function () { return this.fTypeString; };
    //-----------------------------
    IObject.prototype.match = function (address) {
        var re = new OSCRegexp(address);
        return re.match(this.fName);
    };
    IObject.prototype.find = function (expr) {
        if (!Tools.regexp(expr))
            return this.exactfind(expr);
        var re = new OSCRegexp(expr);
        var out = [];
        this.fSubNodes.forEach(function (obj) { if (!obj.getDeleted() && re.match(obj.fName))
            out.push(obj); });
        return out;
    };
    //-----------------------------
    IObject.prototype.exactfind = function (name) {
        var out = [];
        this.fSubNodes.forEach(function (obj) { if (!obj.getDeleted() && (obj.fName == name))
            out.push(obj); });
        return out;
    };
    //-----------------------------    
    IObject.prototype.newData = function (state) { this.fNewData = state; /*triggerEvent(kNewData, true)*/ /*triggerEvent(kNewData, true)*/ ; };
    IObject.prototype.isNewData = function () { return this.fNewData; };
    IObject.prototype.setState = function (s) { this.fState = s; };
    IObject.prototype.addState = function (s) { this.fState |= s; };
    IObject.prototype.getState = function () { return this.fState; };
    IObject.prototype.getPos = function () { return this.fPosition; };
    IObject.prototype.getColor = function () { return this.fColor; };
    IObject.prototype.getOSCAddress = function () { return this.fParent.getOSCAddress() + "/" + this.fName; };
    IObject.prototype.transferAttributes = function (dest) {
        dest.fPosition.set(this.fPosition);
        dest.fColor.set(this.fColor);
        dest.fDate.set(this.fDate);
        //dest.fPosition.setPenWidth(getPenWidth());
        //dest.fPosition.setPenColor(getPenColor());
        //dest.fPosition.setPenStyle(getPenStyle());
        return dest;
    };
    //-----------------------------    
    // Views management
    //-----------------------------    
    IObject.prototype.setView = function (view) { this.fObjectView = [view]; };
    IObject.prototype.addView = function (view) { this.fObjectView.push(view); };
    IObject.prototype.addViews = function (views) { this.fObjectView = this.fObjectView.concat(views); };
    IObject.prototype.getViews = function () { return this.fObjectView; };
    IObject.prototype.removeView = function (view) {
        var i = this.fObjectView.indexOf(view);
        if (i >= 0) {
            view.remove();
            this.fObjectView.splice(i, 1);
        }
    };
    IObject.prototype.removeViews = function () {
        this.fObjectView.forEach(function (view) { view.remove(); });
        this.fObjectView = [];
    };
    //-----------------------------    
    // Msgs execution
    //-----------------------------
    IObject.prototype.execute = function (msg) {
        if (msg.size() == 0)
            return eMsgStatus.kBadParameters;
        var method = msg.message();
        if (method.correct) {
            var handler = this.messageHandler(method.value);
            if (handler) {
                var status_1 = handler.handle(msg);
                if (status_1 & (eMsgStatus.kProcessed | eMsgStatus.kProcessedNoChange))
                    this.fEvents.handleAttributeChange(method.value);
                return status_1;
            }
        }
        else {
        }
        return eMsgStatus.kBadParameters;
    };
    //-----------------------------
    IObject.prototype.messageHandler = function (msg, match) {
        var handler;
        if (!match) {
            return this.fMsgHandlerMap[msg];
        }
        /*else {
            msgMatchPredicat p(msg);
            map<string, SMsgHandler>::const_iterator h = find_if(this.fMsgHandlerMap.begin(), this.fMsgHandlerMap.end(), p);
            if (h != this.fMsgHandlerMap.end()) handler = h.second;
        }*/
        return handler;
    };
    // MESSAGES PROCESSING
    //--------------------------------------------------------------     
    // get objects by OSC address
    //--------------------------------------------------------------     
    // find objects that match an osc address
    // the address is provide as a head and a tail
    // tail is shifted to the left for subnodes
    //-----------------------------
    IObject.prototype.getTargetObjects = function (osc) {
        var out = [];
        if (this.match(osc.first)) {
            osc = OSCAddress.shift(osc.second);
            if (osc.second.length) {
                this.fSubNodes.forEach(function (obj) { out = out.concat(obj.getTargetObjects(osc)); });
            }
            else
                out = out.concat(this.find(osc.first));
        }
        return out;
    };
    //--------------------------------------------------------------     
    IObject.prototype.process = function (msg) {
        var osc = OSCAddress.shift(msg.address());
        return this.processMsg(osc.first, osc.second, msg);
    };
    IObject.prototype.propagateMsg = function (osc, msg) {
        var result = eMsgStatus.kBadAddress;
        this.fSubNodes.forEach(function (obj) { result |= obj.processMsg(osc.first, osc.second, msg); });
        return result;
    };
    IObject.prototype.processMsg = function (head, tail, msg) {
        var result = eMsgStatus.kBadAddress;
        if (this.match(head)) {
            var osc = OSCAddress.shift(tail);
            if (osc.second.length)
                result = this.propagateMsg(osc, msg);
            else {
                var targets = this.find(osc.first);
                var n = targets.length;
                if (n) {
                    targets.forEach(function (obj) {
                        result |= obj.execute(msg);
                        if (result & eMsgStatus.kProcessed)
                            obj.addState(eObjState.kModified);
                    });
                }
                else if (Tools.regexp(osc.first)) {
                    result = eMsgStatus.kProcessedNoChange;
                }
                else {
                    result = this.proxy_create(msg, osc.first, this).status;
                }
            }
        }
        if (result & (eMsgStatus.kProcessed + eObjState.kSubModified)) {
            this.addState(eObjState.kSubModified);
        }
        return result;
    };
    //-------------------------------------------------------------
    // the basic 'set' handler
    //-------------------------------------------------------------
    IObject.prototype.basicSet = function (msg) {
        var type = msg.paramStr(1);
        if (!type.correct) {
            return eMsgStatus.kBadParameters;
        }
        if (type.value != this.getTypeString()) {
            var out = this.proxy_create(msg, this.fName, this.getParent());
            if (out.status & eMsgStatus.kProcessed) {
                // todo: transfer this attributes to new object
                this.transferAttributes(out.obj);
                //				this.fParent.cleanupSync();
                this.del();
                return out.status;
            }
            return eMsgStatus.kProcessedNoChange;
        }
        return eMsgStatus.kBadParameters;
    };
    IObject.prototype.set = function (msg) {
        return this.basicSet(msg);
        /*
                let type = msg.paramStr(1);
                if (!type.correct) { return eMsgStatus.kBadParameters; }
        
                if (type.value != this.getTypeString()) {
                    let out = this.proxy_create (msg, this.fName, this.getParent());
                    if (out.status & eMsgStatus.kProcessed) {
                        // todo: transfer this attributes to new object
                        this.transferAttributes (out.obj);
        //				this.fParent.cleanupSync();
                        this.del();
                        return out.status;
                    }
                    
                    return eMsgStatus.kProcessedNoChange;
                }
                return eMsgStatus.kBadParameters;
        */
    };
    //-------------------------------------------------------------
    // internal 'get' : gives a messagelist as output
    //-------------------------------------------------------------
    IObject.prototype.getCall = function (msg) {
        var out = [];
        var n = msg.size();
        if (n == 1) {
            var msg_1 = this.getSet(); // get without param should give a 'set' msg	    
            if (msg_1)
                out.push(msg_1);
        }
        else
            for (var i = 1; i < n; i++) {
                var attribute = msg.paramStr(i);
                if (attribute.correct)
                    out = out.concat(this.get1AttributeMsg(attribute.value));
                else
                    ITLError.badParameter(msg.toString(), msg.param(i));
            }
        return out;
    };
    //-------------------------------------------------------------
    // the basic 'get' handler
    //-------------------------------------------------------------
    IObject.prototype.get = function (msg) {
        var msgs = this.getCall(msg);
        msgs.forEach(function (msg) { ITLOut.write(msg.toString() + ";"); });
        return eMsgStatus.kProcessedNoChange;
    };
    //-------------------------------------------------------------
    // the 'save' handler
    //-------------------------------------------------------------
    IObject.prototype.save = function (msg) {
        var msgs = this.getSetRecurse();
        msgs.forEach(function (msg) { ITLOut.write(msg.toString() + ";"); });
        return eMsgStatus.kProcessedNoChange;
    };
    //-------------------------------------------------------------
    // the specific 'get' methods - must be implemented by inherited objects
    //-------------------------------------------------------------
    IObject.prototype.getSet = function () { return null; };
    ;
    //-------------------------------------------------------------
    // get 1 message for 1 attribute
    IObject.prototype.get1AttributeMsg = function (attribute) {
        var h = this.fGetMsgHandlerMap[attribute];
        if (h) {
            var msg = new IMessage(this.getOSCAddress(), attribute);
            h.fill(msg);
            return [msg];
        }
        var hm = this.fGetMsgsHandlerMap[attribute];
        if (hm)
            return hm.getMsgs();
        return [];
    };
    //-------------------------------------------------------------
    // get a message for all attributes
    IObject.prototype.getAttributesMsg = function () {
        var out = new IMessageList();
        for (var key in this.fMsgHandlerMap) {
            var msg = this.get1AttributeMsg(key);
            if (msg)
                out = out.concat(msg);
        }
        return out;
    };
    //-------------------------------------------------------------
    // get objects state messages recursively
    IObject.prototype.getSetRecurse = function () {
        var out = new IMessageList();
        var msg = this.getSet(); // get the 'set' msg first
        if (msg)
            out.push(msg); // and push to the output list
        var p = this.getAttributesMsg(); // next all the messages for the object attributes
        for (var i = 0; i < p.length; i++)
            out.push(p[i]);
        var n = this.getSubNodesCount();
        for (var i = 0; i < n; i++) {
            var subout = this.fSubNodes[i].getSetRecurse();
            for (var i_1 = 0; i_1 < subout.length; i_1++)
                out.push(subout[i_1]);
        }
        return out;
    };
    //-----------------------------    
    IObject.prototype.proxy_create = function (msg, name, parent) { return IProxy.execute(msg, name, parent); };
    //-----------------------------    
    IObject.prototype.delNotify = function (obj) { };
    IObject.prototype.getDeleted = function () { return this.fDelete; };
    IObject.prototype.del = function () {
        this.fDelete = true;
        this.fParent.fSync.delNotify(this);
        this.removeViews();
        var array = this.fParent.getSubNodes();
        array.splice(array.indexOf(this), 1);
    };
    //-----------------------------    
    IObject.prototype.cleanup = function () {
        this.fPosition.cleanup();
        this.fDate.cleanup();
        this.fColor.cleanup();
        this.fPenControl.cleanup();
        this.setState(eObjState.kClean);
        this.fBrushStyle.cleanup();
        this.fEffect.cleanup();
        this.fNewData = false;
        if (this.fDate.getTempo())
            this.move();
    };
    //-----------------------------    
    IObject.prototype.move = function () { INScore.postMessage(this.getOSCAddress(), [kddate_SetMethod, gINScoreRealRate * this.fDate.getTempo(), 60000 * 4]); };
    //-----------------------------    
    IObject.timeTaskCleanup = function (obj) {
        var state = obj.getState();
        if (state & (eObjState.kNewObject + eObjState.kModified))
            obj.cleanup();
        if (state & eObjState.kSubModified) {
            obj.setState(eObjState.kClean);
            var nodes = obj.getSubNodes();
            for (var i = 0; i < nodes.length; i++) {
                IObject.timeTaskCleanup(nodes[i]);
            }
        }
    };
    return IObject;
}());
var IObjectTreeApply = (function () {
    function IObjectTreeApply() {
    }
    IObjectTreeApply.prototype.apply = function (f, t) {
        f(t);
        var sub = t.getSubNodes();
        for (var i = 0; i < sub.length; i++)
            this.apply(f, sub[i]);
    };
    IObjectTreeApply.prototype.cleanup = function (t) { t.cleanup(); };
    IObjectTreeApply.prototype.applyCleanup = function (t) {
        var _this = this;
        this.apply(function (o) { return _this.cleanup(o); }, t);
    };
    IObjectTreeApply.prototype.posModified = function (t) { t.posModified(); };
    IObjectTreeApply.prototype.applyPosModified = function (t) {
        var _this = this;
        this.apply(function (o) { return _this.posModified(o); }, t);
    };
    return IObjectTreeApply;
}());
///<reference path="VObjectView.ts"/>
///<reference path="IObject.ts"/>
//-------------------------------------------------------------- 
// Debug node of IObject
//-------------------------------------------------------------- 
var IDebug = (function (_super) {
    __extends(IDebug, _super);
    function IDebug(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kDebugType;
        _this.fShowMap = false;
        _this.fShowName = false;
        return _this;
    }
    IDebug.prototype.setHandlers = function () {
        var _this = this;
        this.fMsgHandlerMap[kname_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setShowName(n); });
        this.fMsgHandlerMap[kmap_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setShowMap(n); });
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(function (msg) { return _this.get(msg); });
        this.fGetMsgHandlerMap[kname_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getShowName(); });
        this.fGetMsgHandlerMap[kmap_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getShowMap(); });
    };
    IDebug.prototype.getShowMap = function () { return this.fShowMap ? 1 : 0; };
    IDebug.prototype.getShowName = function () { return this.fShowName ? 1 : 0; };
    IDebug.prototype.setShowMap = function (val) { this.fShowMap = val ? true : false; this.fParent.addState(eObjState.kModified); };
    IDebug.prototype.setShowName = function (val) { this.fShowName = val ? true : false; this.fParent.addState(eObjState.kModified); };
    IDebug.prototype.createStaticNodes = function () { };
    return IDebug;
}(IObject));
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="../model/IDebug.ts"/>
///<reference path="../model/IObject.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../mapping/TTime2GraphicRelation.ts"/>
var VHtmlView = (function (_super) {
    __extends(VHtmlView, _super);
    function VHtmlView(elt, parent) {
        var _this = _super.call(this) || this;
        //	static fClickTarget: IObject;
        _this.fDisplayMap = false;
        _this.fDisplayName = false;
        _this.fParent = parent;
        _this.setPos(0, 0, 100, 100);
        _this.fHtmlElt = elt;
        _this.fTranslateX = _this.fTranslateY = 0;
        _this.fPositionHandler = null;
        //		VHtmlView.fClickTarget = null;
        if (parent)
            parent.getHtml().appendChild(elt);
        _this.setDefaultPositionStyle();
        return _this;
    }
    VHtmlView.prototype.setPositionHandler = function (fpos) { this.fPositionHandler = fpos; };
    VHtmlView.prototype.setDefaultPositionStyle = function () { this.fHtmlElt.style.position = "absolute"; };
    VHtmlView.prototype.getParent = function () { return this.fParent; };
    VHtmlView.prototype.getHtml = function () { return this.fHtmlElt; };
    VHtmlView.prototype.remove = function () { this.fHtmlElt.parentNode.removeChild(this.fHtmlElt); };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.updateView = function (obj) {
        this.updatePos(obj);
        this.updateColor(obj);
        this.updatePenControl(obj);
        this.updateEffects(obj);
        this.updateEvents(obj);
        var debug = obj.fDebug;
        if (debug.fShowName)
            this.showName(obj);
        else if (this.fDisplayName)
            this.removeName();
        if (debug.fShowMap)
            this.showMap(obj);
        else if (this.fDisplayMap)
            this.removeMap();
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.showName = function (obj) {
        var div = document.createElement('div');
        div.className = "inscore-debug";
        div.id = "_name_";
        div.innerHTML = obj.getName();
        this.getHtml().appendChild(div);
        this.fDisplayName = true;
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.removeName = function () {
        var childs = this.getHtml().querySelectorAll('#_name_');
        if (childs && childs.length)
            this.getHtml().removeChild(childs[0]);
        this.fDisplayName = false;
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.addMap = function (seg, i) {
        var colors = ["DarkOrange", "ForestGreen"];
        var div = document.createElement('div');
        div.id = "_map_";
        div.style.position = "absolute";
        div.style.width = this.map2SceneX(seg.first().size()) + "px";
        div.style.height = this.map2SceneY(seg.second().size()) + "px";
        div.style.left = this.map2SceneX(seg.first().first()) + "px";
        div.style.top = this.map2SceneY(seg.second().first()) + "px";
        div.style.backgroundColor = colors[i % 2];
        div.style.opacity = "0.4";
        this.getHtml().appendChild(div);
        this.fDisplayMap = true;
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.removeMap = function () {
        var childs = this.getHtml().querySelectorAll('#_map_');
        var n = childs.length;
        for (var i = 0; i < n; i++)
            this.getHtml().removeChild(childs[i]);
        this.fDisplayMap = false;
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.showMap = function (obj) {
        var color = ["DarkOrange", "rgb(10 200 10)"];
        var map = obj.fMapping.getRelations();
        for (var i = 0; i < map.length; i++)
            this.addMap(map[i].fGraph, i);
    };
    //------------------------------------------------------------------------------------
    VHtmlView.prototype.mouseEvent = function (obj, type, ev) {
        ev.stopPropagation();
        var div = this.getHtml();
        var o = this.getRelativeCoord(ev, div);
        var mx = this.scene2MapX(o.abs.x) / obj.fPosition.getScale();
        var my = this.scene2MapY(o.abs.y) / obj.fPosition.getScale();
        var date = obj.mapPoint2Date({ x: mx, y: my });
        var p = this.getRelativeCoord(ev, div.parentElement);
        obj.handleMouseEvent(type, { rel: o.rel, abs: o.abs, parent: p.rel }, date);
    };
    // get coordinates relative to an HTMLElement
    VHtmlView.prototype.getRelativeCoord = function (ev, elt) {
        var r = elt.getBoundingClientRect();
        var x = ev.pageX - (r.left + window.scrollX);
        var y = ev.pageY - (r.top + window.scrollY);
        var ry;
        var body = document.body, html = document.documentElement;
        var height = Math.max(body.scrollHeight, body.offsetHeight, html.clientHeight, html.scrollHeight, html.offsetHeight);
        elt.tagName == "BODY" ? ry = y / (height / 2) - 1 : ry = y / (r.height / 2) - 1;
        return { abs: { x: x, y: y }, rel: { x: x / (r.width / 2) - 1, y: ry } };
    };
    VHtmlView.prototype.removeAllEvents = function (div) {
        div.onmousedown = null;
        div.onmouseup = null;
        div.onmouseenter = null;
        div.onmouseleave = null;
        div.ondblclick = null;
    };
    VHtmlView.prototype.updateEvents = function (obj) {
        var _this = this;
        var evs = obj.hasUIEvents();
        var div = this.getHtml();
        if (evs) {
            if (evs & eUIEvents.kMouseDown)
                div.onmousedown = function (ev) { /*if (!VHtmlView.fClickTarget) VHtmlView.fClickTarget = obj;*/ return _this.mouseEvent(obj, eUIEvents.kMouseDown, ev); };
            else
                div.onmousedown = null;
            if (evs & eUIEvents.kMouseMove)
                div.onmousemove = function (ev) { return (ev.buttons == 1) /*&& (VHtmlView.fClickTarget == obj)*/ ? _this.mouseEvent(obj, eUIEvents.kMouseMove, ev) : null; };
            else
                div.onmousemove = null;
            if (evs & eUIEvents.kMouseUp)
                div.onmouseup = function (ev) { /*VHtmlView.fClickTarget = null;*/ return _this.mouseEvent(obj, eUIEvents.kMouseUp, ev); };
            else
                div.onmouseup = null;
            if (evs & eUIEvents.kMouseEnter)
                div.onmouseenter = function (ev) { return _this.mouseEvent(obj, eUIEvents.kMouseEnter, ev); };
            else
                div.onmouseenter = null;
            if (evs & eUIEvents.kMouseLeave)
                div.onmouseleave = function (ev) { return _this.mouseEvent(obj, eUIEvents.kMouseLeave, ev); };
            else
                div.onmouseleave = null;
        }
        else
            this.removeAllEvents(div);
    };
    //------------------------------------------------------------------------------------
    // update color
    // target of color style depend on the html element implementation 
    VHtmlView.prototype.colorTarget = function () { return this.fHtmlElt; };
    VHtmlView.prototype.updateColor = function (obj) {
        if (obj.fColor.modified()) {
            var elt = this.colorTarget();
            elt.style.color = obj.fColor.getRGBString();
            var alpha = obj.fColor.getA() / 255;
            elt.style.opacity = alpha.toString();
        }
    };
    //------------------------------------------------------------------------------------
    // update pen
    VHtmlView.prototype.updatePenControl = function (obj) {
        var penWidth = obj.fPenControl.getPenWidth();
        var penColor = obj.fPenControl.getPenColor().getRGBString();
        var penStyle = VHtmlView.penStyle2Dash(obj.fPenControl.getPenStyleNum());
        var penAlpha = obj.fPenControl.getPenColor().getA();
        var elt = this.getHtml();
        elt.style.borderWidth = penWidth + 'px';
        elt.style.borderColor = penColor;
        elt.style.borderStyle = penStyle;
    };
    //------------------------------------------------------------------------------------
    // update position
    VHtmlView.prototype.getSize = function (obj) {
        var size = obj.getSize();
        var strokeWidth = obj.fPenControl.getPenWidth();
        var w = this.relative2SceneWidth(size.w) + strokeWidth;
        var h = this.relative2SceneHeight(size.h) + strokeWidth;
        return { w: (w ? w : 1), h: (h ? h : 1) };
    };
    VHtmlView.prototype.updatePos = function (obj) {
        var pos = this.fPositionHandler();
        if (pos.x == kNoPosition) {
            this.getHtml().style.visibility = "hidden";
            return;
        }
        var size = this.getSize(obj);
        var z = obj.fPosition.getZOrder();
        var left = this.relative2SceneX(pos.x);
        var top = this.relative2SceneY(pos.y);
        this.setPos(top, left, size.w, size.h); // store the metrics
        var shear = obj.fPosition.getShear();
        var elt = this.getHtml();
        elt.style.width = size.w + "px";
        elt.style.height = size.h + "px";
        elt.style.left = left + "px";
        elt.style.top = top + "px";
        elt.style.zIndex = z.toString();
        elt.style.transform = this.getTransform(obj) + " skewX(" + shear[0] + "rad) skewY(" + shear[1] + "rad)";
        elt.style.visibility = obj.fPosition.getVisible() ? "inherit" : "hidden";
    };
    // to be used for elts with auto width and height
    VHtmlView.prototype.updateObjectSize = function (obj) {
        var w = this.scene2RelativeWidth(this.fHtmlElt.clientWidth);
        var h = this.scene2RelativeHeight(this.fHtmlElt.clientHeight);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
    };
    VHtmlView.prototype.getParentsScale = function (obj) {
        var p = obj.getParent();
        if (p)
            return p.fPosition.getScale() * this.getParentsScale(p);
        return 1;
    };
    VHtmlView.prototype.getViewScale = function (obj) { return obj.fPosition.getScale() * this.getParentsScale(obj); };
    VHtmlView.prototype.getScale = function (obj) {
        var scale = this.getViewScale(obj);
        return (scale == 1) ? "" : "scale(" + scale + "," + scale + ") ";
    };
    VHtmlView.prototype.getTranslate = function (obj) {
        var scale = obj.fPosition.getScale();
        var xo = obj.fPosition.getXOrigin() * scale;
        var yo = obj.fPosition.getYOrigin() * scale;
        this.fTranslateX = -this.fWidth * (1 + xo) / 2.0;
        this.fTranslateY = -this.fHeight * (1 + yo) / 2.0;
        return (this.fTranslateX || this.fTranslateY) ? "translate(" + this.fTranslateX + "px," + this.fTranslateY + "px) " : " ";
    };
    VHtmlView.prototype.getRotateX = function (obj) {
        var rotate = obj.getRotate();
        return (rotate.x) ? "rotateX(" + rotate.x + "deg)" : "";
    };
    VHtmlView.prototype.getRotateY = function (obj) {
        var rotate = obj.getRotate();
        return (rotate.y) ? "rotateY(" + rotate.y + "deg)" : "";
    };
    VHtmlView.prototype.getRotateZ = function (obj) {
        var rotate = obj.getRotate();
        return (rotate.z) ? "rotateZ(" + rotate.z + "deg) " : "";
    };
    VHtmlView.prototype.getTransform = function (obj) {
        return this.getTranslate(obj) + this.getScale(obj) + this.getRotateX(obj) + this.getRotateY(obj) + this.getRotateZ(obj);
    };
    VHtmlView.prototype.setPos = function (top, left, width, height) {
        this.fTop = top;
        this.fLeft = left;
        this.fWidth = width;
        this.fHeight = height;
    };
    //------------------------------------------------------------------------------------
    // update effects
    VHtmlView.prototype.updateEffects = function (obj) {
        if (!obj.fEffect.fEffectModified)
            return;
        var elt = this.getHtml();
        switch (obj.fEffect.type()) {
            case eEffect.kNone:
                this.setNone();
                break;
            case eEffect.kBlur:
                this.setBlur(obj.fEffect.param(0));
                break;
            case eEffect.kShadow:
                this.setShadow(obj.fEffect.params());
                break;
        }
    };
    VHtmlView.prototype.setNone = function () { this.setBlur(0); };
    VHtmlView.prototype.setBlur = function (val) {
        this.getHtml().style.boxShadow = "(0px 0px)";
        this.getHtml().style.filter = "blur( " + val + "px)";
    };
    VHtmlView.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.getHtml().style.boxShadow = color.getCSSRGBAString() + params[0] + "px " + params[1] + "px " + params[6] + "px";
        this.getHtml().style.filter = "blur(0)";
    };
    VHtmlView.penStyle2Dash = function (style) {
        switch (style) {
            case 0: return "solid";
            case 1: return "dashed";
            case 2: return "dotted";
            default: return "solid";
        }
    };
    VHtmlView.prototype.positionString = function () { return "top: " + this.fTop + " left: " + this.fLeft + " w: " + this.fWidth + " h: " + this.fHeight; };
    // Maps the IObject [-1,1] y coordinate to the referenceRect().
    VHtmlView.prototype.relative2SceneY = function (y) { return this.fParent.fHeight * (y + 1.0) / 2.0; };
    // Maps the IObject [-1,1] x coordinate to the referenceRect().
    VHtmlView.prototype.relative2SceneX = function (x) { return this.fParent.fWidth * (x + 1.0) / 2.0; };
    // Maps the IObject [0,2] width value to the corresponding referenceRect() value.
    VHtmlView.prototype.relative2SceneWidth = function (width) { return Math.min(this.fParent.fWidth, this.fParent.fHeight) * width / 2.0; };
    // Maps the IObject [0,2] height value to the corresponding referenceRect() value.
    VHtmlView.prototype.relative2SceneHeight = function (height) { return Math.min(this.fParent.fWidth, this.fParent.fHeight) * height / 2.0; };
    // Maps the referenceRect() width value to the corresponding [0,2] value.
    VHtmlView.prototype.scene2RelativeWidth = function (width) { return (width * 2.0) / this.fParent.fWidth; };
    // Maps the referenceRect() height value to the corresponding [0,2] value.
    VHtmlView.prototype.scene2RelativeHeight = function (height) { return (height * 2.0) / this.fParent.fHeight; };
    // Maps the referenceRect() x value to the corresponding [-1,1] value.
    VHtmlView.prototype.scene2RelativeX = function (x) { return x / (this.fParent.fWidth / 2.0) - 1; };
    // Maps the referenceRect() y value to the corresponding [-1,1] value.
    VHtmlView.prototype.scene2RelativeY = function (y) { return y / (this.fParent.fHeight / 2.0) - 1; };
    // Maps the IObject map [0,1] x coordinate to the referenceRect().
    VHtmlView.prototype.map2SceneX = function (x) { return this.fWidth * x; };
    // Maps the IObject map [0,1] y coordinate to the referenceRect().
    VHtmlView.prototype.map2SceneY = function (y) { return this.fHeight * y; };
    //  Maps a pixel x value to the IObject map [0,1] coordinate.
    VHtmlView.prototype.scene2MapX = function (x) { return x / this.fWidth; };
    // Maps a pixel y value to the IObject map [0,1] coordinate.
    VHtmlView.prototype.scene2MapY = function (y) { return y / this.fHeight; };
    // updates the local mapping (do nothing at IObject level) 
    //	updateLocalMapping (obj: IObject ): void;
    // initialize an object view (do nothing at IObject level)
    VHtmlView.prototype.initialize = function (obj) { };
    return VHtmlView;
}(VObjectView));
///<reference path="../model/IObject.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="VHtmlView.ts"/>
var VHtmlSvg = (function (_super) {
    __extends(VHtmlSvg, _super);
    function VHtmlSvg(parent) {
        var _this = _super.call(this, document.createElement('div'), parent) || this;
        _this.fSVG = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
        _this.fSVG.setAttribute('xmlns', "http://www.w3.org/2000/svg");
        _this.fSVG.setAttribute('xmlns:xlink', "http://www.w3.org/1999/xlink");
        _this.fSVG.setAttribute('version', "1.1");
        _this.getHtml().appendChild(_this.fSVG);
        return _this;
    }
    VHtmlSvg.prototype.updateColor = function (obj) {
        var target = this.getSVGTarget();
        var modified = (obj.fColor.modified() || obj.fBrushStyle.brushModified()) && (obj.fBrushStyle.getBrushStyle() != eBrushStyle.kNone);
        if (obj.fBrushStyle.brushModified() && (obj.fBrushStyle.getBrushStyle() == eBrushStyle.kNone)) {
            target.style.fill = "none";
        }
        else if (modified) {
            target.style.fill = obj.fColor.getRGBAString();
            target.style.fillOpacity = obj.fColor.getSVGA().toString();
        }
    };
    VHtmlSvg.prototype.getInnerSize = function (obj) {
        var strokeWidth = obj.fPenControl.getPenWidth();
        var w = this.fWidth - strokeWidth;
        var h = this.fHeight - strokeWidth;
        return { w: (w ? w : 1), h: (h ? h : 1) };
    };
    VHtmlSvg.prototype.updateView = function (obj) {
        _super.prototype.updateView.call(this, obj);
        this.fSVG.style.width = this.fWidth + "px";
        this.fSVG.style.height = this.fHeight + "px";
        this.fSVG.style.verticalAlign = "top";
        this.fSVG.style.overflow = "visible";
    };
    VHtmlSvg.prototype.basePenControl = function (obj) {
        _super.prototype.updatePenControl.call(this, obj);
    };
    VHtmlSvg.prototype.updatePenControl = function (obj) {
        if (obj.fPenControl.modified()) {
            this.fSVG.style.strokeWidth = obj.fPenControl.getPenWidth().toString();
            this.fSVG.style.stroke = obj.fPenControl.getPenColor().getRGBString();
            this.fSVG.style.strokeOpacity = (obj.fPenControl.getPenAlpha() / 255).toString();
            this.fSVG.style.strokeDasharray = VHtmlSvg.penStyle2Dash(obj.fPenControl.getPenStyleNum());
        }
    };
    VHtmlSvg.prototype.getViewScale = function (obj) { return obj.fPosition.getScale(); };
    VHtmlSvg.prototype.updateCommonSVG = function (obj, w, h) {
        var target = this.getSVGTarget();
        target.setAttribute('width', w.toString());
        target.setAttribute('height', h.toString());
        target.style.transform = this.strokeTranslate(obj);
    };
    VHtmlSvg.prototype.innerTranslate = function (obj) {
        var w = obj.fPenControl.getPenWidth() / 2;
        return { x: w, y: w };
    };
    VHtmlSvg.prototype.strokeTranslate = function (obj) {
        var t = this.innerTranslate(obj);
        return (t.x || t.y) ? "translate(" + t.x + "px," + t.y + "px) " : "none";
    };
    VHtmlSvg.prototype.setNone = function () { this.fSVG.setAttribute("filter", "blur(0px)"); };
    VHtmlSvg.prototype.setBlur = function (val) { this.fSVG.setAttribute("filter", "blur(" + val + "px)"); };
    VHtmlSvg.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.fSVG.setAttribute("filter", "drop-shadow(" + color.getCSSRGBAString() + params[0] + "px " + params[1] + "px " + params[6] + "px)");
    };
    VHtmlSvg.penStyle2Dash = function (style) {
        switch (style) {
            case 1: return "4, 4";
            case 2: return "1, 5";
            case 3: return "4, 4, 1, 5";
            case 4: return "4, 4, 1, 5, 1, 5";
            default: return "";
        }
    };
    return VHtmlSvg;
}(VHtmlView));
var TPoint = (function () {
    function TPoint(x, y) {
        this.fX = x;
        this.fY = y;
    }
    TPoint.prototype.toArray = function () { return [this.fX, this.fY]; };
    TPoint.prototype.toString = function () { return this.toArray().toString(); };
    TPoint.prototype.getX = function () { return this.fX; };
    TPoint.prototype.getY = function () { return this.fY; };
    TPoint.prototype.equal = function (p) { return this.fX == p.fX && this.fY == p.fY; };
    return TPoint;
}());
///<reference path="IObject.ts"/>
var IRectShape = (function (_super) {
    __extends(IRectShape, _super);
    function IRectShape(name, parent) {
        return _super.call(this, name, parent) || this;
    }
    IRectShape.prototype.create = function (name, parent) { return new IRectShape(name, parent); };
    IRectShape.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.brushAble();
        this.fMsgHandlerMap[kwidth_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setWidth(n); });
        this.fMsgHandlerMap[kheight_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setHeight(n); });
    };
    IRectShape.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        // Cas ou le type est différent, le proxy est utilisé dans super.set()
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        // Vérification des paramêtres du message "set"
        if (msg.size() == 4) {
            var width = msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) {
                return eMsgStatus.kBadParameters;
            }
            // Si les valeurs des attributs ne sont pas les mêmes
            if ((width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight())) {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.newData(true);
                status = eMsgStatus.kProcessed;
            }
            else
                status = eMsgStatus.kProcessedNoChange;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    IRectShape.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight()]);
    };
    return IRectShape;
}(IObject));
///<reference path="Constants.ts"/>
///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>
var IArc = (function (_super) {
    __extends(IArc, _super);
    function IArc(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kArcType;
        _this.fStart = 0;
        _this.fRange = 0;
        _this.fClose = 0;
        _this.fPenControl.setPenWidth(1);
        _this.fBrushStyle.fBrush = eBrushStyle.kNone;
        return _this;
    }
    // HANDLERS
    //--------------------------------------------------------------  
    IArc.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.fMsgHandlerMap[kstart_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setStart(n); });
        this.fMsgHandlerMap[krange_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setRange(n); });
        this.fMsgHandlerMap[kclose_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setClose(n); });
        this.fMsgHandlerMap[kdrange_SetMethod] = new TMsgHandlerNum(function (n) { _this.setDRange(n); });
        this.fMsgHandlerMap[kdstart_SetMethod] = new TMsgHandlerNum(function (n) { _this.setDStart(n); });
        this.fGetMsgHandlerMap[kstart_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getStart(); });
        this.fGetMsgHandlerMap[krange_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getRange(); });
        this.fGetMsgHandlerMap[kclose_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getClose(); });
    };
    IArc.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg); // this is intended to handle type change at root level        
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() == 6) {
            var width = msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) {
                return eMsgStatus.kBadParameters;
            }
            var start = msg.paramNum(4), range = msg.paramNum(5);
            if (!start.correct || !range.correct) {
                return eMsgStatus.kBadParameters;
            }
            // Si les valeurs des attributs ne sont pas les mêmes
            if ((width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight())
                || ((start.value != this.fStart) || (range.value != this.fRange))) {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.fStart = start.value;
                this.fRange = range.value;
                this.newData(true);
                status = eMsgStatus.kProcessed;
            }
            else
                status = eMsgStatus.kProcessedNoChange;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    IArc.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight(), this.getStart(), this.getRange()]);
    };
    IArc.prototype.getStart = function () { return this.fStart; };
    IArc.prototype.getRange = function () { return this.fRange; };
    IArc.prototype.getClose = function () { return this.fClose; };
    IArc.prototype.setStart = function (start) { this.fStart = start; };
    IArc.prototype.setRange = function (range) { this.fRange = range; };
    IArc.prototype.setClose = function (close) { this.fClose = close; };
    IArc.prototype.setDRange = function (dRange) { this.setRange(this.fRange + dRange); };
    IArc.prototype.setDStart = function (dStart) { this.setStart(this.fStart + dStart); };
    return IArc;
}(IRectShape));
///<reference path="VHtmlSVG.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="../model/IArc.ts"/>
var VHtmlArcView = (function (_super) {
    __extends(VHtmlArcView, _super);
    function VHtmlArcView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fArc = document.createElementNS('http://www.w3.org/2000/svg', 'path');
        _this.getHtml().className = "inscore-arc";
        _this.fSVG.appendChild(_this.fArc);
        return _this;
    }
    VHtmlArcView.prototype.getSVGTarget = function () { return this.fArc; };
    VHtmlArcView.prototype.updateView = function (obj) {
        _super.prototype.updateView.call(this, obj);
        var size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);
        var arc = obj;
        var r1 = size.w / 2;
        var r2 = size.h / 2;
        var startAngle = this.normalize(arc.getStart());
        var endAngle = this.normalize(startAngle + VHtmlArcView.clip(arc.getRange()));
        var startPoint = VHtmlArcView.getPoint(r1, r2, startAngle);
        var endPoint = VHtmlArcView.getPoint(r1, r2, endAngle);
        var path = VHtmlArcView.getPath(VHtmlArcView.clip(arc.getRange()), startPoint, endPoint, r1, r2, arc.getClose() ? true : false);
        this.fArc.setAttribute('d', path);
    };
    // computes a point coordinates at a given angle
    VHtmlArcView.getPoint = function (r1, r2, angle) {
        angle = (angle * Math.PI / 180);
        var x = r1 * (Math.cos(angle) + 1);
        var y = r2 * (-Math.sin(angle) + 1);
        return new TPoint(x, y);
    };
    // gives the arc path string
    VHtmlArcView.getPath = function (arcRange, start, end, rx, ry, close) {
        //values setting
        arcRange = VHtmlArcView.clip(arcRange);
        var flag = VHtmlArcView.direction(arcRange);
        var arcStr = start + " A " + rx + "," + ry + ", 0," + flag.sup + "," + flag.dir + " " + end;
        if (close)
            return "M " + rx + "," + ry + " L " + arcStr + " Z ";
        else
            return "M " + arcStr;
    };
    // normalize the angle between 180 and - 180°
    VHtmlArcView.prototype.normalize = function (angle) {
        if (angle > 180)
            return this.normalize(angle - 360);
        else if (angle < -180)
            return this.normalize(angle + 360);
        return angle;
    };
    VHtmlArcView.clip = function (range) {
        if (range >= 360)
            return 359;
        if (range <= -360)
            return -359;
        return range;
    };
    // computes the arc directions: up or down, clockwise or counter clockwise
    VHtmlArcView.direction = function (arcRange) {
        var dir = arcRange > 0 ? 0 : 1;
        arcRange = Math.abs(arcRange);
        var sup = arcRange >= 180 ? 1 : 0;
        return { sup: sup, dir: dir };
    };
    return VHtmlArcView;
}(VHtmlSvg));
///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>
var BezierCurve = (function () {
    function BezierCurve(ax, ay, bx, by, cx, cy, dx, dy) {
        this.fPoints = new Array();
        this.fPoints.push(new TPoint(ax, ay));
        this.fPoints.push(new TPoint(bx, by));
        this.fPoints.push(new TPoint(cx, cy));
        this.fPoints.push(new TPoint(dx, dy));
    }
    BezierCurve.prototype.equal = function (other) {
        return this.fPoints.every(function (p, index) { return p.equal(other.fPoints[index]); });
    };
    BezierCurve.prototype.points = function () { return this.fPoints; };
    BezierCurve.prototype.toArray = function () {
        var a = new Array();
        for (var i = 1; i < this.fPoints.length; i++)
            a = a.concat(this.fPoints[i].toArray());
        return a;
    };
    return BezierCurve;
}());
var ICurve = (function (_super) {
    __extends(ICurve, _super);
    function ICurve(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kCurveType;
        _this.fPoints = new Array();
        _this.fPenControl.setPenWidth(1);
        return _this;
    }
    ICurve.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.brushAble();
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(function () { return _this.getPoints(); });
    };
    ICurve.prototype.setPoints = function (points) { this.fPoints = points; };
    ICurve.prototype.getPoints = function () { return this.fPoints; };
    ICurve.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if ((msg.size() > 1) && ((msg.size() % 8) == 2)) {
            //Build the vector of points reading the message.
            var curveData = new Array();
            for (var i = 2; i < msg.size(); i += 8) {
                var ax = msg.paramNum(i), ay = msg.paramNum(i + 1);
                var bx = msg.paramNum(i + 2), by = msg.paramNum(i + 3);
                var cx = msg.paramNum(i + 4), cy = msg.paramNum(i + 5);
                var dx = msg.paramNum(i + 6), dy = msg.paramNum(i + 7);
                if (!ax.correct || !ay.correct || !bx.correct || !by.correct ||
                    !cx.correct || !cy.correct || !dx.correct || !dy.correct) {
                    return eMsgStatus.kBadParameters;
                }
                var bezierCurve = new BezierCurve(ax.value, ay.value, bx.value, by.value, cx.value, cy.value, dx.value, dy.value);
                curveData.push(bezierCurve);
            }
            //Compares the points vector with the current one.
            if (curveData.length != this.getPoints().length) {
                this.setPoints(curveData);
                this.newData(true);
                return eMsgStatus.kProcessed;
            }
            for (var i = 0; i < curveData.length; i++) {
                if (curveData[i] != this.getPoints()[i]) {
                    this.setPoints(curveData);
                    this.newData(true);
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    };
    ICurve.prototype.toArray = function () {
        var a = new Array();
        for (var i = 0; i < this.fPoints.length; i++)
            a = a.concat(this.fPoints[i].toArray());
        return a;
    };
    ICurve.prototype.toString = function () {
        var str = "";
        for (var i = 0; i < this.fPoints.length; i++)
            str += this.fPoints[i].toString();
        return str;
    };
    ICurve.prototype.getSet = function () {
        var a = [kset_SetMethod, this.fTypeString];
        return new IMessage(this.getOSCAddress(), a.concat(this.toArray()));
    };
    return ICurve;
}(IObject));
///<reference path="VHtmlSVG.ts"/>
///<reference path="../model/ICurve.ts"/>
///<reference path="../lib/TPoint.ts"/>
var VHtmlCurveView = (function (_super) {
    __extends(VHtmlCurveView, _super);
    function VHtmlCurveView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fCurve = document.createElementNS('http://www.w3.org/2000/svg', 'path');
        _this.getHtml().className = "inscore-curve";
        _this.fSVG.appendChild(_this.fCurve);
        return _this;
    }
    VHtmlCurveView.prototype.getSVGTarget = function () { return this.fCurve; };
    VHtmlCurveView.prototype.getSize = function (obj) {
        var size = this.fCurve.getBBox();
        var strokeWidth = obj.fPenControl.getPenWidth();
        return { w: size.width + strokeWidth, h: size.height + strokeWidth };
    };
    VHtmlCurveView.prototype.relative2SceneCurve = function (curve) {
        var p = curve.points();
        var a1 = this.relative2SceneWidth(p[0].getX());
        var a2 = this.relative2SceneWidth(p[0].getY());
        var b1 = this.relative2SceneWidth(p[1].getX());
        var b2 = this.relative2SceneWidth(p[1].getY());
        var c1 = this.relative2SceneWidth(p[2].getX());
        var c2 = this.relative2SceneWidth(p[2].getY());
        var d1 = this.relative2SceneWidth(p[3].getX());
        var d2 = this.relative2SceneWidth(p[3].getY());
        var miny = Math.min(a2, d2);
        var minx = miny; //Math.min(a1, d1);
        return [a1 - minx, a2 - miny, b1 - minx, b2 - miny, c1 - minx, c2 - miny, d1 - minx, d2 - miny];
    };
    VHtmlCurveView.prototype.updateView = function (obj) {
        var curve = obj;
        if (obj.isNewData()) {
            var points = curve.getPoints();
            for (var i = 0; i < points.length; i++) {
                var p = points[i].points();
                var ps = this.relative2SceneCurve(points[i]);
                this.fStart = new TPoint(ps[0], ps[1]);
                this.fEnd = new TPoint(ps[6], ps[7]);
                var attributes = 'M' + this.fStart.getX() + ',' + this.fStart.getY() + ' ' + 'C' + ps[2] + ',' + ps[3] + ' ' + ps[4] + ',' + ps[5] + ' ' + this.fEnd.getX() + ',' + this.fEnd.getY();
                this.fCurve.setAttribute('d', attributes);
            }
            this.fCurve.style.transform = this.strokeTranslate(obj);
        }
        _super.prototype.updateView.call(this, obj);
    };
    // method is overriden to fit the object in its bounding box
    VHtmlCurveView.prototype.innerTranslate = function (obj) {
        var t = _super.prototype.innerTranslate.call(this, obj);
        var size = this.fCurve.getBBox();
        var startx = Math.min(this.fStart.getX(), this.fEnd.getX());
        var endx = Math.max(this.fStart.getX(), this.fEnd.getX());
        var starty = Math.min(this.fStart.getY(), this.fEnd.getY());
        var endy = Math.max(this.fStart.getY(), this.fEnd.getY());
        if ((startx > 0) && (endx > 0))
            t.x += -startx;
        else if ((startx < 0) && (endx < 0))
            t.x += -endx;
        else
            t.x += size.width - endx;
        if ((starty > 0) && (endy > 0))
            t.y += -starty;
        else if ((starty < 0) && (endy < 0))
            t.y += -endy;
        else
            t.y += size.height - endy;
        return t;
    };
    VHtmlCurveView.prototype.updateObjectSize = function (obj) {
        var w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        var h = this.scene2RelativeHeight(this.fSVG.clientHeight);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
    };
    return VHtmlCurveView;
}(VHtmlSvg));
///<reference path="IRectShape.ts"/>
var IEllipse = (function (_super) {
    __extends(IEllipse, _super);
    //protected kEllipseType: string;
    function IEllipse(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //this.kEllipseType = 'ellipse';
        _this.fTypeString = kEllipseType;
        return _this;
    }
    return IEllipse;
}(IRectShape));
///<reference path="VHtmlSVG.ts"/>
///<reference path="../model/IEllipse.ts"/>
var VHtmlEllipseView = (function (_super) {
    __extends(VHtmlEllipseView, _super);
    function VHtmlEllipseView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fEllipse = document.createElementNS('http://www.w3.org/2000/svg', 'ellipse');
        _this.getHtml().className = "inscore-ellipse";
        _this.fSVG.appendChild(_this.fEllipse);
        return _this;
    }
    VHtmlEllipseView.prototype.getSVGTarget = function () { return this.fEllipse; };
    VHtmlEllipseView.prototype.updateView = function (obj) {
        _super.prototype.updateView.call(this, obj);
        var size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);
        var rx = size.w / 2;
        var ry = size.h / 2;
        this.fEllipse.setAttribute('cx', rx.toString());
        this.fEllipse.setAttribute('cy', ry.toString());
        this.fEllipse.setAttribute('rx', rx.toString());
        this.fEllipse.setAttribute('ry', ry.toString());
    };
    return VHtmlEllipseView;
}(VHtmlSvg));
///<reference path="IObject.ts"/>
var ISVG = (function (_super) {
    __extends(ISVG, _super);
    function ISVG(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kSvgType;
        _super.prototype.setHandlers.call(_this);
        return _this;
    }
    ISVG.prototype.setSvg = function (svg) { this.fSvg = svg; };
    ISVG.prototype.getSvg = function () { return this.fSvg; };
    ISVG.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        var n = msg.size();
        if (n == 3) {
            var svg = msg.paramStr(2);
            if (!svg.correct) {
                return eMsgStatus.kBadParameters;
            }
            if (svg.value != this.getSvg()) {
                this.setSvg(svg.value);
                this.newData(true);
                status = eMsgStatus.kProcessed;
            }
            else
                status = eMsgStatus.kProcessedNoChange;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    ISVG.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.getSvg()]);
    };
    return ISVG;
}(IObject));
///<reference path="VHtmlView.ts"/>
///<reference path="../model/ISVG.ts"/>
var VHtmlSvgView = (function (_super) {
    __extends(VHtmlSvgView, _super);
    function VHtmlSvgView(parent) {
        var _this = _super.call(this, document.createElement('div'), parent) || this;
        _this.fClientWidth = 0;
        _this.fClientHeight = 0;
        _this.getHtml().className = "inscore-svg";
        return _this;
    }
    VHtmlSvgView.prototype.getSVGElement = function () {
        var nodes = this.getHtml().childNodes;
        if (nodes.length) {
            for (var i = 0; i < nodes.length; i++)
                if (nodes[i] instanceof SVGSVGElement)
                    return nodes[i];
        }
        return null;
    };
    VHtmlSvgView.prototype.updateView = function (obj) {
        if (obj.isNewData()) {
            //        	let svg = this.getSVGElement();
            //        	let target = svg ? svg : this.getHtml();
            var target = this.getHtml();
            target.innerHTML = this.getSVGCode(obj);
            this.updateObjectSize(obj);
        }
        _super.prototype.updateView.call(this, obj);
    };
    VHtmlSvgView.prototype.getSVGCode = function (obj) {
        var svg = obj;
        return svg.getSvg();
    };
    VHtmlSvgView.prototype.getsvg = function (root) {
        var g;
        var childs = root.childNodes;
        for (var i = 0; i < childs.length && !g; i++) {
            if (childs[i].nodeName == 'svg') {
                g = childs[i];
                break;
            }
        }
        return g;
    };
    VHtmlSvgView.prototype.getClientSize = function (obj) {
        if (!this.fClientWidth || obj.isNewData()) {
            var svg = this.getsvg(this.getHtml());
            var box = svg.viewBox.baseVal;
            if (box.width) {
                this.fClientWidth = box.width;
                this.fClientHeight = box.height;
                return { w: this.fClientWidth, h: this.fClientHeight };
            }
            box = svg.getBBox();
            var r = svg.getBoundingClientRect();
            if (r.width) {
                this.fClientWidth = r.width;
                this.fClientHeight = r.height;
                return { w: this.fClientWidth, h: this.fClientHeight };
            }
            console.log("VHtmlSvgView cannot get svg element size");
        }
        return { w: this.fClientWidth, h: this.fClientHeight };
    };
    VHtmlSvgView.prototype.getSize = function (obj) {
        var size = this.getClientSize(obj);
        var strokeWidth = obj.fPenControl.getPenWidth();
        var w = size.w + strokeWidth;
        var h = size.h + strokeWidth;
        return { w: (w ? w : 1), h: (h ? h : 1) };
    };
    VHtmlSvgView.prototype._updateView = function (obj) {
        var _this = this;
        return function () { return _this.updateView(obj); };
    };
    VHtmlSvgView.prototype.updateObjectSize = function (obj) {
        if (obj.fPosition.getWidth())
            return;
        var size = this.getClientSize(obj);
        var w = this.scene2RelativeWidth(size.w);
        var h = this.scene2RelativeHeight(size.h);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
        if (!w || !h)
            setTimeout(this._updateView(obj), 50);
    };
    VHtmlSvgView.prototype.relative2SceneSize = function (obj) {
        var size = obj.getSize();
        return { w: this.relative2SceneWidth(size.w), h: this.relative2SceneHeight(size.h) };
    };
    VHtmlSvgView.prototype.setNone = function () { this.getsvg(this.getHtml()).setAttribute("filter", "blur(0px)"); };
    VHtmlSvgView.prototype.setBlur = function (val) { this.getsvg(this.getHtml()).setAttribute("filter", "blur(" + val + "px)"); };
    VHtmlSvgView.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.getsvg(this.getHtml()).setAttribute("filter", "drop-shadow(" + color.getCSSRGBAString() + params[0] + "px " + params[1] + "px " + params[6] + "px)");
    };
    return VHtmlSvgView;
}(VHtmlView));
var GuidoMapping;
(function (GuidoMapping) {
    GuidoMapping[GuidoMapping["kNoMapping"] = 0] = "kNoMapping";
    GuidoMapping[GuidoMapping["kVoiceMapping"] = 1] = "kVoiceMapping";
    GuidoMapping[GuidoMapping["kStaffMapping"] = 2] = "kStaffMapping";
    GuidoMapping[GuidoMapping["kSystemMapping"] = 4] = "kSystemMapping";
})(GuidoMapping || (GuidoMapping = {}));
var GuidoErrCode;
(function (GuidoErrCode) {
    //! null is used to denote no error
    GuidoErrCode[GuidoErrCode["guidoNoErr"] = 0] = "guidoNoErr";
    //! error while parsing the Guido format
    GuidoErrCode[GuidoErrCode["guidoErrParse"] = -1] = "guidoErrParse";
    //! memory allocation error
    GuidoErrCode[GuidoErrCode["guidoErrMemory"] = -2] = "guidoErrMemory";
    //! error while reading or writing a file
    GuidoErrCode[GuidoErrCode["guidoErrFileAccess"] = -3] = "guidoErrFileAccess";
    //! the user cancelled the action
    GuidoErrCode[GuidoErrCode["guidoErrUserCancel"] = -4] = "guidoErrUserCancel";
    //! the music font is not available
    GuidoErrCode[GuidoErrCode["guidoErrNoMusicFont"] = -5] = "guidoErrNoMusicFont";
    //! the text font is not available
    GuidoErrCode[GuidoErrCode["guidoErrNoTextFont"] = -6] = "guidoErrNoTextFont";
    //! bad parameter used as argument
    GuidoErrCode[GuidoErrCode["guidoErrBadParameter"] = -7] = "guidoErrBadParameter";
    //! invalid handler used
    GuidoErrCode[GuidoErrCode["guidoErrInvalidHandle"] = -8] = "guidoErrInvalidHandle";
    //! required initialisation has not been performed
    GuidoErrCode[GuidoErrCode["guidoErrNotInitialized"] = -9] = "guidoErrNotInitialized";
    //! the action failed
    GuidoErrCode[GuidoErrCode["guidoErrActionFailed"] = -10] = "guidoErrActionFailed";
})(GuidoErrCode || (GuidoErrCode = {}));
var GuidoElementSelector;
(function (GuidoElementSelector) {
    GuidoElementSelector[GuidoElementSelector["kGuidoPage"] = 0] = "kGuidoPage";
    GuidoElementSelector[GuidoElementSelector["kGuidoSystem"] = 1] = "kGuidoSystem";
    GuidoElementSelector[GuidoElementSelector["kGuidoSystemSlice"] = 2] = "kGuidoSystemSlice";
    GuidoElementSelector[GuidoElementSelector["kGuidoStaff"] = 3] = "kGuidoStaff";
    /*kGuidoMeasure,*/
    GuidoElementSelector[GuidoElementSelector["kGuidoBar"] = 4] = "kGuidoBar";
    GuidoElementSelector[GuidoElementSelector["kGuidoEvent"] = 5] = "kGuidoEvent";
    GuidoElementSelector[GuidoElementSelector["kGuidoScoreElementEnd"] = 6] = "kGuidoScoreElementEnd";
})(GuidoElementSelector || (GuidoElementSelector = {}));
var GuidoElementType;
(function (GuidoElementType) {
    GuidoElementType[GuidoElementType["kNote"] = 1] = "kNote";
    GuidoElementType[GuidoElementType["kRest"] = 2] = "kRest";
    GuidoElementType[GuidoElementType["kEmpty"] = 3] = "kEmpty";
    GuidoElementType[GuidoElementType["kBar"] = 4] = "kBar";
    GuidoElementType[GuidoElementType["kRepeatBegin"] = 5] = "kRepeatBegin";
    GuidoElementType[GuidoElementType["kRepeatEnd"] = 6] = "kRepeatEnd";
    GuidoElementType[GuidoElementType["kStaff"] = 7] = "kStaff";
    GuidoElementType[GuidoElementType["kSystemSlice"] = 8] = "kSystemSlice";
    GuidoElementType[GuidoElementType["kSystem"] = 9] = "kSystem";
    GuidoElementType[GuidoElementType["kPage"] = 10] = "kPage";
})(GuidoElementType || (GuidoElementType = {}));
var PianoRollType;
(function (PianoRollType) {
    PianoRollType[PianoRollType["kSimplePianoRoll"] = 0] = "kSimplePianoRoll";
    PianoRollType[PianoRollType["kTrajectoryPianoRoll"] = 1] = "kTrajectoryPianoRoll";
})(PianoRollType || (PianoRollType = {}));
///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../externals/libGUIDOEngine.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>
var IGuidoCode = (function (_super) {
    __extends(IGuidoCode, _super);
    function IGuidoCode(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        if (!IGuidoCode.fGuidoEngine) {
            var module = GuidoModule();
            IGuidoCode.fGuidoEngine = new module.GuidoEngineAdapter();
            IGuidoCode.fGuidoMap = new module.GUIDOScoreMap();
            IGuidoCode.fPianoRoll = new module.GUIDOPianoRollAdapter();
            IGuidoCode.fGuidoEngine.init();
        }
        _this.fTypeString = kGuidoCodeType;
        _this.fCurrentPagesCount = 1;
        _this.fPage = 1;
        _this.fSVG = "";
        _this.fAR = null;
        //this.fPageFormat = [21.0f, 29.7f]; 
        _this.fPosition.setWidth(0);
        _this.fPosition.setHeight(0);
        _super.prototype.setHandlers.call(_this);
        return _this;
    }
    IGuidoCode.prototype.del = function () {
        if (this.fAR)
            IGuidoCode.fGuidoEngine.freeAR(this.fAR);
        _super.prototype.del.call(this);
    };
    IGuidoCode.prototype.setSVG = function (gmn) { this.fSVG = gmn; /*localMapModified(true);*/ };
    IGuidoCode.prototype.setPage = function (page) { this.fPage = page; /*localMapModified(true);*/ };
    IGuidoCode.prototype.setPageFormat = function (pageFormat) { this.fPageFormat = pageFormat; /*localMapModified(true);*/ };
    //setdPage(dpage: number): void                       {}
    IGuidoCode.prototype.getSVG = function (size) { return this.fSVG.length ? this.fSVG : this.AR2SVG(size); };
    IGuidoCode.prototype.getPage = function () { return this.fPage; };
    IGuidoCode.prototype.getPageFormat = function () { return this.fPageFormat; };
    //getPageCount(): number              {return}
    IGuidoCode.prototype.guidoMap2inscoreMap = function (json) {
        var _this = this;
        var map = eval(json);
        if (map.length)
            this.fMapping.clear();
        map.forEach(function (elt) {
            var timeSegment = new TimeInterval(new Fraction(elt.time.start), new Fraction(elt.time.end));
            var graphicSegment = new TGraphicSegment(new NumberInterval(elt.graph.left, elt.graph.right), new NumberInterval(elt.graph.top, elt.graph.bottom));
            _this.fMapping.addElt(new TTime2GraphicRelation(timeSegment, graphicSegment));
        });
    };
    IGuidoCode.prototype.getMap = function (gr) { this.guidoMap2inscoreMap(IGuidoCode.fGuidoMap.getSystemMap(gr, 1, 1, 1)); };
    ;
    IGuidoCode.prototype.str2AR = function (gmn) {
        var p = IGuidoCode.fGuidoEngine.openParser();
        var ar = IGuidoCode.fGuidoEngine.string2AR(p, gmn);
        if (!ar) {
            var error = IGuidoCode.fGuidoEngine.parserGetErrorCode(p);
            ITLError.write("Error line " + error.line + " column " + error.col + ": " + error.msg);
            return false;
        }
        this.fAR = ar;
        IGuidoCode.fGuidoEngine.closeParser(p);
        return true;
    };
    IGuidoCode.prototype.mapScale = function (xscale, yscale) {
        this.fMapping.forEach(function (elt) { elt.fGraph.scale(xscale, yscale); });
    };
    IGuidoCode.prototype.AR2SVG = function (size) {
        var _this = this;
        if (this.fAR) {
            var gr = IGuidoCode.fGuidoEngine.ar2gr(this.fAR);
            this.fSVG = IGuidoCode.fGuidoEngine.gr2SVG(gr, 1, false, 0);
            this.getMap(gr);
            this.getViews()[0].setMapScaleHandler(function (x, y) { _this.mapScale(x, y); });
            IGuidoCode.fGuidoEngine.freeGR(gr);
        }
        return this.fSVG;
    };
    IGuidoCode.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() != 3)
            return eMsgStatus.kBadParameters;
        var gmn = msg.paramStr(2);
        if (!gmn.correct)
            return eMsgStatus.kBadParameters;
        if (!this.str2AR(gmn.value))
            return eMsgStatus.kBadParameters;
        this.fGMN = gmn.value;
        this.fNewData = true;
        return eMsgStatus.kProcessed;
    };
    IGuidoCode.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fGMN]);
    };
    return IGuidoCode;
}(IObject));
///<reference path="VHtmlSVGView.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>
var VHtmlGMNView = (function (_super) {
    __extends(VHtmlGMNView, _super);
    function VHtmlGMNView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.getHtml().className = "inscore-gmn";
        _this.fMapScale = null;
        return _this;
    }
    VHtmlGMNView.prototype.setMapScaleHandler = function (f) { this.fMapScale = f; };
    VHtmlGMNView.prototype.getSVGCode = function (obj) {
        var gmn = obj;
        return gmn.getSVG(this.relative2SceneSize(obj));
    };
    VHtmlGMNView.prototype.getFirstSVGGroup = function (root) {
        var g;
        var childs = root.childNodes;
        for (var i = 0; i < childs.length && !g; i++) {
            if (childs[i].nodeName == 'g') {
                g = childs[i];
                break;
            }
            g = this.getFirstSVGGroup(childs[i]);
        }
        return g;
    };
    //------------------------------------------------------------------------------------
    VHtmlGMNView.prototype.setPos = function (top, left, width, height) {
        _super.prototype.setPos.call(this, top, left, width, height);
        if (this.fMapScale) {
            var x = 1;
            var y = 1;
            if (this.fWidth > this.fHeight)
                y = this.fWidth / this.fHeight;
            else if (this.fWidth < this.fHeight)
                x = this.fHeight / this.fWidth;
            this.fMapScale(x, y);
            this.fMapScale = null;
        }
    };
    VHtmlGMNView.prototype.updateColor = function (obj) {
        var color = obj.fColor.getRGBString();
        var alpha = obj.fColor.getSVGA();
        var g = this.getFirstSVGGroup(this.getHtml());
        if (g) {
            g.style.stroke = color;
            g.style.strokeOpacity = alpha.toString();
            g.style.fill = color;
            g.style.fillOpacity = alpha.toString();
        }
    };
    return VHtmlGMNView;
}(VHtmlSvgView));
///<reference path="../model/IObject.ts"/>
///<reference path="VHtmlView.ts"/>
var VHtmlAutoSize = (function (_super) {
    __extends(VHtmlAutoSize, _super);
    function VHtmlAutoSize(elt, parent) {
        var _this = _super.call(this, elt, parent) || this;
        _this.fClientWidth = 0;
        _this.fClientHeight = 0;
        return _this;
    }
    VHtmlAutoSize.prototype.updateView = function (obj) {
        var elt = this.getHtml();
        elt.style.height = "auto";
        elt.style.width = "auto";
        this.updateObjectSize(obj);
        _super.prototype.updateView.call(this, obj);
    };
    VHtmlAutoSize.prototype._updateView = function (obj) {
        var _this = this;
        return function () { return _this.updateView(obj); };
    };
    VHtmlAutoSize.prototype.updateObjectSize = function (obj) {
        var size = this.getClientSize(obj);
        var w = this.scene2RelativeWidth(size.w);
        var h = this.scene2RelativeHeight(size.h);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
        if (!w || !h)
            setTimeout(this._updateView(obj), 50);
    };
    VHtmlAutoSize.prototype.getClientSize = function (obj) {
        if (!this.fClientWidth || obj.isNewData()) {
            var target = this.getAutoElement();
            this.fClientWidth = target.clientWidth;
            this.fClientHeight = target.clientHeight;
        }
        return { w: this.fClientWidth, h: this.fClientHeight };
    };
    return VHtmlAutoSize;
}(VHtmlView));
///<reference path="IObject.ts"/>
var IText = (function (_super) {
    __extends(IText, _super);
    function IText(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //this.kTextType = 'txt';
        _this.fTypeString = kTextType;
        //Default Parameters
        _this.fColor.setRGB([0, 0, 0]);
        _this.fColor.setA(255);
        _this.fFontSize = 14;
        _this.fFontFamily = "Arial";
        _this.fFontWeight = IText.kWeightNormal;
        _this.fFontStyle = IText.kStyleNormal;
        _this.fFontModified = false;
        return _this;
    }
    IText.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.fMsgHandlerMap[kfontSize_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setFontSize(n); });
        this.fMsgHandlerMap[kfontFamily_GetSetMethod] = new TMsgHandlerText(function (s) { _this.setFontFamily(s); });
        this.fMsgHandlerMap[kfontStyle_GetSetMethod] = new TMethodHandler(function (msg) { return _this.setFontStyle(msg); });
        this.fMsgHandlerMap[kfontWeight_GetSetMethod] = new TMethodHandler(function (msg) { return _this.setFontWeight(msg); });
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText(function () { return _this.getText(); });
        this.fGetMsgHandlerMap[kfontSize_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getFontSize(); });
        this.fGetMsgHandlerMap[kfontFamily_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.getFontFamily(); });
        this.fGetMsgHandlerMap[kfontStyle_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.getFontStyle(); });
        this.fGetMsgHandlerMap[kfontWeight_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.getFontWeight(); });
    };
    // GETS / SETS VALUES 
    //--------------------------------------------------------------    
    IText.prototype.fontModified = function () { if (this.fFontModified == false)
        return this.fEffect.effectModified();
    else
        return this.fFontModified; };
    IText.prototype.getText = function () { return this.fText; };
    IText.prototype.setText = function (txt) { this.fText = txt; };
    IText.prototype.getFontSize = function () { return this.fFontSize; };
    IText.prototype.setFontSize = function (s) { this.fFontSize = s; this.fFontModified = true; };
    IText.prototype.getFontFamily = function () { return this.fFontFamily; };
    IText.prototype.setFontFamily = function (f) { this.fFontFamily = f; this.fFontModified = true; };
    IText.prototype.getFontStyle = function () { return this.fFontStyle; };
    IText.prototype.setFontStyle = function (msg) {
        var n = msg.size();
        if (n == 2) {
            var fontStyle = msg.paramStr(1);
            if (fontStyle.correct) {
                if (fontStyle.value == IText.kStyleNormal || fontStyle.value == IText.kStyleItalic || fontStyle.value == IText.kStyleOblique) {
                    this.fFontStyle = fontStyle.value;
                    this.fFontModified = true;
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    };
    IText.prototype.getFontWeight = function () { return this.fFontWeight; };
    IText.prototype.setFontWeight = function (msg) {
        var n = msg.size();
        if (n == 2) {
            var fontWeight = msg.paramStr(1);
            if (fontWeight.correct) {
                if (fontWeight.value == IText.kWeightNormal || fontWeight.value == IText.kWeightLight
                    || fontWeight.value == IText.kWeightDemiBold || fontWeight.value == IText.kWeightBold || fontWeight.value == IText.kWeightBlack) {
                    this.fFontWeight = fontWeight.value;
                    this.fFontModified = true;
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    };
    // SET HANDLER
    //--------------------------------------------------------------    
    IText.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        var n = msg.size();
        if (n > 2) {
            var str = "";
            var sep = "";
            for (var i = 2; i < n; i++) {
                str += sep;
                str += msg.param(i);
                sep = " ";
            }
            this.setText(str);
            this.newData(true);
            status = eMsgStatus.kProcessed;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    // GETSET METHOD
    //--------------------------------------------------------------    
    IText.prototype.getSet = function () {
        var a = [kset_SetMethod, this.fTypeString];
        return new IMessage(this.getOSCAddress(), a.concat(this.fText));
    };
    return IText;
}(IObject));
//protected kTextType: string;
// Constants for font style and font weight.
IText.kStyleNormal = "normal";
IText.kStyleItalic = "italic";
IText.kStyleOblique = "oblique";
IText.kWeightNormal = "normal";
IText.kWeightLight = "light";
IText.kWeightDemiBold = "demibold";
IText.kWeightBold = "bold";
IText.kWeightBlack = "black";
///<reference path="IText.ts"/>
var IHtml = (function (_super) {
    __extends(IHtml, _super);
    //protected kHtmlType: string;
    function IHtml(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //this.kHtmlType = 'html';
        _this.fTypeString = kHtmlType;
        return _this;
    }
    return IHtml;
}(IText));
///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IHtml.ts"/>
///<reference path="../model/IText.ts"/>
var VHtmlHtmlView = (function (_super) {
    __extends(VHtmlHtmlView, _super);
    function VHtmlHtmlView(parent) {
        var _this = _super.call(this, document.createElement('div'), parent) || this;
        _this.getHtml().className = "inscore-html";
        return _this;
    }
    VHtmlHtmlView.prototype.getText = function (obj) { return obj.getText(); };
    // CSS weight are used as numbers
    VHtmlHtmlView.fontWeight2Num = function (weight) {
        switch (weight) {
            case IText.kWeightNormal: return "400";
            case IText.kWeightLight: return "200";
            case IText.kWeightDemiBold: return "550";
            case IText.kWeightBold: return "700";
            case IText.kWeightBlack: return "900";
            default: return "400";
        }
    };
    VHtmlHtmlView.prototype.setFont = function (t) {
        var elt = this.getHtml();
        elt.style.fontSize = t.getFontSize() + "px";
        elt.style.fontFamily = t.getFontFamily();
        elt.style.fontStyle = t.getFontStyle();
        elt.style.fontWeight = VHtmlHtmlView.fontWeight2Num(t.getFontWeight());
    };
    VHtmlHtmlView.prototype.setNone = function () { this.getHtml().style.textShadow = "0px 0px 0px"; };
    VHtmlHtmlView.prototype.setBlur = function (val) { this.getHtml().style.textShadow = "0px 0px " + val + "px"; };
    VHtmlHtmlView.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.getHtml().style.textShadow = color.getCSSRGBAString() + params[0] + "px " + params[1] + "px " + params[6] + "px";
    };
    VHtmlHtmlView.prototype.updateView = function (obj) {
        var t = obj;
        var elt = this.getHtml();
        elt.innerHTML = this.getText(t);
        if (t.fontModified())
            this.setFont(t);
        _super.prototype.updateView.call(this, obj);
    };
    VHtmlHtmlView.prototype.getAutoElement = function () { return this.getHtml(); };
    return VHtmlHtmlView;
}(VHtmlAutoSize));
///<reference path="IObject.ts"/>
var IImage = (function (_super) {
    __extends(IImage, _super);
    function IImage(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //this.kImgType = 'img';
        _this.fTypeString = kImgType;
        return _this;
    }
    IImage.prototype.colorAble = function () { }; // color attributes are not available for images
    IImage.prototype.getFile = function () { return this.fFile; };
    IImage.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() == 3) {
            var file = msg.paramStr(2);
            if (!file.correct)
                return eMsgStatus.kBadParameters;
            this.fFile = file.value;
            this.newData(true);
            status = eMsgStatus.kProcessed;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    IImage.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, "'" + this.getFile() + "'"]);
    };
    return IImage;
}(IObject));
///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IImage.ts"/>
var VHtmlImageView = (function (_super) {
    __extends(VHtmlImageView, _super);
    function VHtmlImageView(parent) {
        var _this = this;
        var img = document.createElement('img');
        _this = _super.call(this, img, parent) || this;
        _this.fImage = img;
        _this.getHtml().className = "inscore-img";
        return _this;
    }
    VHtmlImageView.prototype.updateView = function (obj) {
        var img = obj;
        this.fImage.src = img.getFile();
        _super.prototype.updateView.call(this, obj);
    };
    VHtmlImageView.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " " + params[0] + "px " + params[1] + "px " + params[6] + "px)";
    };
    VHtmlImageView.prototype.getAutoElement = function () { return this.fImage; };
    return VHtmlImageView;
}(VHtmlAutoSize));
///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>
var ILine = (function (_super) {
    __extends(ILine, _super);
    function ILine(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kLineType;
        _this.fPenControl.setPenWidth(1);
        _this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(function () { return _this.fPoint.toArray(); });
        return _this;
    }
    ILine.prototype.setPoint = function (p) {
        this.fPoint = p;
        this.fPosition.setWidth(Math.abs(p.getX()));
        this.fPosition.setHeight(Math.abs(p.getY()));
    };
    ILine.prototype.getPoint = function () { return this.fPoint; };
    ILine.prototype.getColorTarget = function () { return this.fPenControl.fPenColor; };
    ;
    ILine.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() == 5) {
            var mode = msg.paramStr(2);
            var a = msg.paramNum(3), b = msg.paramNum(4);
            if (!mode.correct)
                return eMsgStatus.kBadParameters;
            if (!a.correct || !b.correct)
                return eMsgStatus.kBadParameters;
            if (mode.value == "xy") {
                this.fWAMode = false;
                this.setPoint(new TPoint(a.value, b.value));
            }
            else if (mode.value == "wa") {
                this.fWAMode = true;
                this.fLWidth = a.value;
                this.fLAngle = b.value;
                if (this.fLAngle < 0) {
                    this.fLAngle += 360;
                }
                if (180 <= Math.abs(this.fLAngle) && Math.abs(this.fLAngle) <= 360) {
                    this.fLAngle -= 180;
                }
                var x = Math.round(a.value * Math.cos(Math.PI * this.fLAngle / 180) * 1000) / 1000;
                var y = Math.round(a.value * Math.sin(Math.PI * this.fLAngle / 180) * 1000) / 1000;
                this.setPoint(new TPoint(x, y));
            }
            else
                return eMsgStatus.kBadParameters;
            this.newData(true);
            status = eMsgStatus.kProcessed;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    ILine.prototype.getSetLine = function (p) {
        return this.fWAMode ? ["wa", this.fLWidth, this.fLAngle] : ["xy", this.fPoint.getX(), this.fPoint.getY()];
    };
    ILine.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), this.getSetLine([kset_SetMethod, this.fTypeString]));
    };
    return ILine;
}(IObject));
///<reference path="../model/ILine.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSVG.ts"/>
var VHtmlLineView = (function (_super) {
    __extends(VHtmlLineView, _super);
    function VHtmlLineView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        _this.getHtml().className = "inscore-line";
        _this.fSVG.appendChild(_this.fLine);
        return _this;
    }
    VHtmlLineView.prototype.getSVGTarget = function () { return this.fLine; };
    VHtmlLineView.prototype.updateColor = function (obj) {
        if (obj.fPenControl.fPenColor.modified()) {
            this.fLine.style.stroke = obj.fPenControl.getPenColor().getRGBString();
            this.fLine.style.strokeOpacity = obj.fPenControl.getPenColor().getSVGA().toString();
        }
    };
    VHtmlLineView.prototype.updateView = function (obj) {
        _super.prototype.updateView.call(this, obj);
        var line = obj;
        var p = line.getPoint();
        var x = this.relative2SceneWidth(p.getX());
        var y = this.relative2SceneWidth(p.getY());
        var x0 = 0;
        var y0 = 0;
        if ((x < 0) && (y < 0)) {
            x = -x;
            y = -y;
        }
        else if (x < 0) {
            y0 = y;
            x = -x;
            y = 0;
        }
        else if (y < 0) {
            y0 = -y;
            y = 0;
        }
        this.fLine.setAttribute('x1', x0.toString());
        this.fLine.setAttribute('x2', x.toString());
        this.fLine.setAttribute('y1', y0.toString());
        this.fLine.setAttribute('y2', y.toString());
        this.fLine.style.transform = this.strokeTranslate(obj);
    };
    return VHtmlLineView;
}(VHtmlSvg));
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlGMNView.ts"/>
var VHtmlPianoRollView = (function (_super) {
    __extends(VHtmlPianoRollView, _super);
    function VHtmlPianoRollView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.getHtml().className = "inscore-pianoroll";
        return _this;
    }
    // avoid the VHtmlGMNView specific scaling
    VHtmlPianoRollView.prototype.getViewScale = function (obj) { return obj.fPosition.getScale() * this.getParentsScale(obj); };
    VHtmlPianoRollView.prototype.updateObjectSize = function (obj) { }; // do nothing, the size is user defined
    return VHtmlPianoRollView;
}(VHtmlGMNView));
///<reference path="IObject.ts"/>
///<reference path="../lib/TPoint.ts"/>
var IPolygon = (function (_super) {
    __extends(IPolygon, _super);
    function IPolygon(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //this.kPolygonType = 'polygon';
        _this.fTypeString = kPolygonType;
        _this.fPoints = new Array();
        return _this;
    }
    IPolygon.prototype.setHandlers = function () {
        _super.prototype.setHandlers.call(this);
        this.brushAble();
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerArray(this._getPoints());
    };
    IPolygon.prototype.setPoints = function (points) { this.fPoints = points; };
    IPolygon.prototype.getPoints = function () { return this.fPoints; };
    IPolygon.prototype._getPoints = function () {
        var _this = this;
        return function () { return _this.fPoints; };
    };
    IPolygon.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if ((msg.size() > 1) && (((msg.size() - 1) % 2) == 1)) {
            //Build the vector of points reading the message.
            var points = new Array();
            for (var i = 2; i < msg.size(); i += 2) {
                var a = msg.paramNum(i), b = msg.paramNum(i + 1);
                if (!a.correct || !b.correct) {
                    return eMsgStatus.kBadParameters;
                }
                points.push(new TPoint(a.value, b.value));
            }
            //Compares the points vector with the current one.
            if (points.length != this.getPoints().length) {
                this.setPoints(points);
                this.newData(true);
                return eMsgStatus.kProcessed;
            }
            for (var i = 0; i < points.length; i++) {
                if (points[i] != this.getPoints()[i]) {
                    this.setPoints(points);
                    this.newData(true);
                    return eMsgStatus.kProcessed;
                }
            }
            return eMsgStatus.kProcessedNoChange;
        }
        return eMsgStatus.kBadParameters;
    };
    IPolygon.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, 'todo']);
    };
    return IPolygon;
}(IObject));
///<reference path="../model/IPolygon.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSVG.ts"/>
var VHtmlPolygonView = (function (_super) {
    __extends(VHtmlPolygonView, _super);
    function VHtmlPolygonView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fPolygon = document.createElementNS('http://www.w3.org/2000/svg', 'polygon');
        _this.getHtml().className = "inscore-polygon";
        _this.fSVG.appendChild(_this.fPolygon);
        return _this;
    }
    VHtmlPolygonView.prototype.getSVGTarget = function () { return this.fPolygon; };
    VHtmlPolygonView.prototype.getSize = function (obj) {
        var strokeWidth = obj.fPenControl.getPenWidth();
        var size = this.fPolygon.getBBox();
        return { w: size.width + strokeWidth, h: size.height + strokeWidth };
    };
    VHtmlPolygonView.prototype.updateView = function (obj) {
        var polygon = obj;
        if (obj.isNewData()) {
            var points = polygon.getPoints();
            var minx = 0x1fffffff;
            var miny = 0x1fffffff;
            for (var i = 0; i < points.length; i++) {
                minx = Math.min(minx, points[i].getX());
                miny = Math.min(miny, points[i].getY());
            }
            var strPoints = '';
            for (var i = 0; i < points.length; i++) {
                var x = this.relative2SceneWidth(points[i].getX() - minx);
                var y = this.relative2SceneWidth(points[i].getY() - miny);
                strPoints += x + ',' + y + ' ';
            }
            this.fPolygon.setAttribute('points', strPoints);
        }
        this.fPolygon.setAttribute('fill', obj.fColor.getRGBString());
        _super.prototype.updateView.call(this, obj);
        var size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);
    };
    VHtmlPolygonView.prototype.updateObjectSize = function (obj) {
        var elt = this.getHtml();
        var w = this.scene2RelativeWidth(elt.clientWidth);
        var h = this.scene2RelativeHeight(elt.clientHeight);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
    };
    return VHtmlPolygonView;
}(VHtmlSvg));
///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>
var IRect = (function (_super) {
    __extends(IRect, _super);
    function IRect(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.kRectType = 'rect';
        _this.fTypeString = _this.kRectType;
        _this.fGetMsgHandlerMap[kradius_GetSetMethod] = new TGetMsgHandlerArray(_this._getRadius());
        _this.fMsgHandlerMap[kradius_GetSetMethod] = new TMsgHandlerNumArray(_this._setRadius());
        return _this;
    }
    IRect.prototype.getRadius = function () { return this.fRadius; };
    IRect.prototype.setRadius = function (radius) {
        if (radius.length != 2)
            return eMsgStatus.kBadParameters;
        this.fRadius = radius;
        return eMsgStatus.kProcessed;
    };
    IRect.prototype._getRadius = function () {
        var _this = this;
        return function () { return _this.getRadius(); };
    };
    IRect.prototype._setRadius = function () {
        var _this = this;
        return function (radius) { return _this.setRadius(radius); };
    };
    return IRect;
}(IRectShape));
///<reference path="VHtmlSVG.ts"/>
///<reference path="../model/IRect.ts"/>
var VHtmlRectView = (function (_super) {
    __extends(VHtmlRectView, _super);
    function VHtmlRectView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.fRect = document.createElementNS('http://www.w3.org/2000/svg', 'rect');
        _this.getHtml().className = "inscore-rect";
        _this.fSVG.appendChild(_this.fRect);
        return _this;
    }
    VHtmlRectView.prototype.getSVGTarget = function () { return this.fRect; };
    VHtmlRectView.prototype.updateView = function (obj) {
        _super.prototype.updateView.call(this, obj);
        var size = this.getInnerSize(obj);
        this.updateCommonSVG(obj, size.w, size.h);
        var rect = obj;
        var radius = rect.getRadius();
        if (radius) {
            this.fRect.setAttribute('rx', radius[0].toString());
            this.fRect.setAttribute('ry', radius[1].toString());
        }
    };
    return VHtmlRectView;
}(VHtmlSvg));
// -----------------------------------------------------------------
// tools based on typescript lib
// -----------------------------------------------------------------
var TWindow = (function () {
    function TWindow() {
    }
    TWindow.getSize = function () {
        /*
                let e = document.documentElement;
                let g = document.getElementsByTagName('body')[0];
                let w = window.innerWidth || e.clientWidth || g.clientWidth;
                let h = window.innerHeight|| e.clientHeight|| g.clientHeight;
                let width = window.innerWidth ;
                let height = window.innerHeight;
        */
        var width = Math.max(window.innerWidth, document.documentElement.clientWidth, document.body.clientWidth);
        var height = Math.max(window.innerHeight, document.documentElement.clientHeight, document.body.clientHeight);
        return { w: width, h: height };
    };
    return TWindow;
}());
///<reference path="IObject.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../parser/MessageInterface.ts"/>
///<reference path="../scripting/TMessageEvaluator.ts"/>
var TILoader = (function () {
    function TILoader() {
    }
    TILoader.prototype.parse = function (msg) {
        try {
            INScoreParser.parse(msg);
            return INScoreParser.get();
        }
        catch (e) {
        }
        return [];
    };
    TILoader.prototype.scanParam = function (param) {
        var _this = this;
        if (param.address) {
            // this a message
            console.log("scanParam message: " + param);
            return new IMessage(param.address, this.scanParams(param.params));
        }
        else if (param instanceof Array) {
            // this is a message list
            var msgs_1 = new IMessageList();
            param.forEach(function (p) { msgs_1.push(_this.scanParam(p)); });
            return msgs_1;
        }
        return param;
    };
    // scan parameters to build high level objects as parameters
    // this is required for a message to appear as IMessage in the params list
    TILoader.prototype.scanParams = function (params) {
        var _this = this;
        console.log("scanParams : " + params);
        var out = [];
        params.forEach(function (p) { out.push(_this.scanParam(p)); });
        return out;
    };
    TILoader.prototype.process = function (buffer, root) {
        var msgs = this.parse(buffer);
        if (!msgs)
            return;
        var imsgs = [];
        msgs.forEach(function (msg) {
            imsgs.push(new IMessage(msg.address.osc, msg.params));
        });
        /*
                for (let i = 0; i < msgs.length; i++) {
                    let address = msgs[i].address.osc;
                    let params = msgs[i].params;
                    let msg = new IMessage(msgs[i].address.osc, msgs[i].params);
        */
        /*
                let m : TMouseEnv; let d: Fraction;
                let env = new TEnv ("", m, d, d, []);
                let me = new TMessageEvaluator(env);
                imsgs = me.eval(imsgs);
        */
        imsgs.forEach(function (msg) { INScore.postMessage(msg.address(), msg.params()); });
        //            INScore.checkStatus (root.process( msg), msg);
        //        }    
    };
    TILoader.prototype._process = function (reader, client) {
        var _this = this;
        return function () {
            var data = reader.result;
            _this.process(data, client);
        };
    };
    TILoader.prototype.load = function (file, client) {
        var reader = new FileReader();
        reader.readAsText(file);
        reader.onloadend = this._process(reader, client);
    };
    return TILoader;
}());
///<reference path="inscore-interface.ts"/>
///<reference path="controller/IMessage.ts"/>
///<reference path="controller/IGlue.ts"/>
///<reference path="lib/ITLError.ts"/>
///<reference path="lib/ITLOut.ts"/>
///<reference path="lib/OSCAddress.ts"/>
///<reference path="lib/TEnums.ts"/>
///<reference path="model/IObject.ts"/>
///<reference path="model/TILoader.ts"/>
var INScoreImpl = (function (_super) {
    __extends(INScoreImpl, _super);
    // ------------------------------------------------------------
    function INScoreImpl() {
        var _this = _super.call(this) || this;
        _this.fVersion = 0.6;
        _this.fErrStrings = new Array();
        _this.fErrStrings[eMsgStatus.kBadAddress] = "bad OSC address";
        _this.fErrStrings[eMsgStatus.kProcessed] = "processed";
        _this.fErrStrings[eMsgStatus.kProcessedNoChange] = "processed without change";
        _this.fErrStrings[eMsgStatus.kBadParameters] = "bad parameter";
        _this.fErrStrings[eMsgStatus.kCreateFailure] = "create failed";
        return _this;
    }
    INScoreImpl.prototype.status2string = function (err) {
        var str = this.fErrStrings[err];
        return (str ? str : "unknown error " + err);
    };
    // ------------------------------------------------------------
    // static methods
    // ------------------------------------------------------------
    INScoreImpl.prototype.version = function () { return this.fVersion; };
    INScoreImpl.prototype.start = function (scene, position) {
        if (!this.fGlue) {
            this.fGlue = new IGlue();
            this.fGlue.initEventHandlers();
        }
        this.fGlue.start(scene, position ? position : "relative");
        ITLOut.write("INScoreJS version " + this.version());
    };
    INScoreImpl.prototype.checkStatus = function (status, msg) {
        if (!(status & eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            ITLError.write(msg.toString() + ": " + this.status2string(status));
    };
    INScoreImpl.prototype.getMessage = function (address, params) {
        var out = [];
        var msg = new IMessage(address, ["get"].concat(params));
        var targets = this.fGlue.getRoot().getTargetObjects(OSCAddress.shift(address));
        targets.forEach(function (obj) { out = out.concat(obj.getCall(msg)); });
        return out;
    };
    INScoreImpl.prototype.postMessage = function (address, params) {
        var msg = new IMessage(address, params);
        //    	this.checkStatus (this.fGlue.getRoot().process (msg), msg);
        this.fGlue.pushStack(msg);
    };
    INScoreImpl.prototype.load = function (data) {
        var loader = new TILoader;
        if (typeof data == "string") {
            loader.process(data, this.fGlue.getRoot());
        }
        else {
            loader.load(data, this.fGlue.getRoot());
        }
    };
    INScoreImpl.prototype.register = function (tag) {
        var elts = document.getElementsByTagName(tag);
        for (var i = 0; i < elts.length; i++) {
            var icode = elts[i].textContent;
            INScore.load(icode);
            elts[i].textContent = "";
        }
        while (elts.length)
            elts[0].parentElement.removeChild(elts[0]);
    };
    return INScoreImpl;
}(INScoreInterface));
INScore = new INScoreImpl();
///<reference path="../inscore.ts"/>
///<reference path="../model/Constants.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>
var dropLoader = (function () {
    function dropLoader(target) {
        this.fExtHandlers = {};
        this.fTarget = target;
        this.fTargetType = target.getAttribute("class");
        this.buildObjectExtensions();
    }
    dropLoader.prototype.buildObjectExtensions = function () {
        this.fExtHandlers["txt"] = kTextType;
        this.fExtHandlers["text"] = kTextType;
        this.fExtHandlers["mei"] = kVerovioType;
        this.fExtHandlers["xml"] = kMusicxmlType;
        this.fExtHandlers["svg"] = kSvgType;
        this.fExtHandlers["html"] = kHtmlType;
        this.fExtHandlers["htm"] = kHtmlType;
        this.fExtHandlers["gmn"] = kGuidoCodeType;
        this.fExtHandlers["dsp"] = kFaustType;
        this.fExtHandlers["jpg"] = kImgType;
        this.fExtHandlers["jpeg"] = kImgType;
        this.fExtHandlers["gif"] = kImgType;
        this.fExtHandlers["png"] = kImgType;
        this.fExtHandlers["bmp"] = kImgType;
        this.fExtHandlers["tiff"] = kImgType;
        this.fExtHandlers["wmv"] = kVideoType;
        this.fExtHandlers["avi"] = kVideoType;
        this.fExtHandlers["mpg"] = kVideoType;
        this.fExtHandlers["mpeg"] = kVideoType;
        this.fExtHandlers["mp4"] = kVideoType;
        this.fExtHandlers["m4v"] = kVideoType;
        this.fExtHandlers["mov"] = kVideoType;
        this.fExtHandlers["vob"] = kVideoType;
    };
    dropLoader.prototype.processLoader = function (e) {
        this.fTargetScene = this.targetScene();
        // check if text has been dropped
        var data = e.dataTransfer.getData("Text");
        if (data) {
            INScore.load(data);
        }
        else {
            var filelist = e.dataTransfer.files;
            if (!filelist)
                return;
            var filecount = filelist.length;
            for (var i = 0; i < filecount; i++) {
                var file = filelist[i];
                var fileName = filelist[i].name;
                var properties = this.getFileProperties(fileName);
                var name_1 = properties.name;
                var ext = properties.ext.toLocaleLowerCase();
                /*
                console.log("relative path: " + filelist[i].webkitRelativePath);
                console.log("doc url: " + document.URL);
                */
                if (ext == kInscoreFile) {
                    INScore.load(file);
                }
                else if ((this.fExtHandlers[ext] == kImgType)
                    || (this.fExtHandlers[ext] == kVideoType)
                    || (this.fExtHandlers[ext] == kFaustType)) {
                    INScore.postMessage("/ITL/" + this.fTargetScene + "/" + name_1, ["set", this.fExtHandlers[ext], fileName]);
                }
                else {
                    var reader = new FileReader();
                    reader.readAsText(file);
                    if (!this.fExtHandlers[ext]) {
                        this.fExtHandlers[ext] = kTextType;
                    }
                    reader.onloadend = this.postMessage(reader, this.fTargetScene, name_1, this.fExtHandlers[ext]);
                }
            }
        }
    };
    // take target scene
    dropLoader.prototype.targetScene = function () {
        var targetScene;
        var targetType = this.fTargetType;
        var target = this.fTarget;
        if (targetType == "inscore-scene") {
            targetScene = this.fTarget.getAttribute("name");
        }
        else {
            while (targetType != "inscore-scene") {
                target = target.parentNode;
                targetType = target.getAttribute("class");
            }
            targetScene = target.getAttribute("name");
        }
        return targetScene;
    };
    // take the name and the extension of the dropped file
    dropLoader.prototype.getFileProperties = function (file) {
        var ext = file.substring(file.lastIndexOf('.') + 1, file.length);
        var name = file.substring(0, file.lastIndexOf('.'));
        name = this.buildCorrectName(name);
        return { name: name, ext: ext };
    };
    // build a receivable name for an INScore object
    dropLoader.prototype.buildCorrectName = function (name) {
        var myRegex = /^[a-zA-Z-_][-_a-zA-Z0-9]+$/.test(name);
        if (!myRegex) {
            var first = name[0];
            var myRegex_1 = /^[0-9]$/.test(first);
            if (myRegex_1) {
                name = '_' + name;
            }
            for (var i = 1; i < name.length; i++) {
                var myRegex_2 = /^[-_a-zA-Z0-9]$/.test(name[i]);
                if (!myRegex_2) {
                    name = name.replace(name[i], "_");
                }
            }
        }
        return name;
    };
    dropLoader.prototype.postMessage = function (reader, targetScene, name, type) {
        return function () {
            var data = reader.result;
            INScore.postMessage("/ITL/" + targetScene + "/" + name, ["set", type, data]);
        };
    };
    return dropLoader;
}());
// Event functions
//--------------------------------
function inscore_dropEvent(e) {
    inscore_dragOverEvent(e);
    var loader = new dropLoader(e.target);
    loader.processLoader(e);
}
function inscore_dragOverEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}
function inscore_resizeDocument() { INScore.postMessage("/ITL/*", ["redraw"]); }
///<reference path="VHtmlView.ts"/>
///<reference path="VHtmlTools.ts"/>
///<reference path="../model/IObject.ts"/>
///<reference path="../events/documentEvents.ts"/>
//--------------------------------------------------
// VHtmlSceneContainer detects the current element 
// and provides it as a container to the scene
//--------------------------------------------------
var VHtmlSceneContainer = (function (_super) {
    __extends(VHtmlSceneContainer, _super);
    function VHtmlSceneContainer() {
        return _super.call(this, VHtmlSceneContainer.getHtml()) || this;
    }
    VHtmlSceneContainer.getHtml = function () {
        var scripts = document.getElementsByTagName('script');
        return (scripts[scripts.length - 1].parentNode);
    };
    VHtmlSceneContainer.prototype.setDefaultPositionStyle = function () { };
    VHtmlSceneContainer.prototype.updatePos = function () {
        var size = TWindow.getSize();
        var w = Math.min(size.w, size.h);
        this.setPos((size.h - w) / 2.0, (size.w - w) / 2.0, w, w);
    };
    return VHtmlSceneContainer;
}(VHtmlView));
var VHtmlSceneView = (function (_super) {
    __extends(VHtmlSceneView, _super);
    function VHtmlSceneView(name) {
        var _this = this;
        var parent = new VHtmlSceneContainer();
        _this = _super.call(this, document.createElement('div'), parent) || this;
        _this.fDoc = parent;
        var wsize = TWindow.getSize();
        _this.fReferenceWidth = Math.min(Math.max(screen.width, wsize.w), Math.max(screen.height, wsize.h));
        var div = _this.getHtml();
        div.className = "inscore-scene";
        div.setAttribute("name", name);
        div.addEventListener("drop", inscore_dropEvent, false);
        div.addEventListener("dragover", inscore_dragOverEvent, false);
        _this.fAbsolutePos = false;
        return _this;
        //		let style = window.getComputedStyle(div);
        //	    this.fAbsolutePos = (style.position === 'absolute');
    }
    VHtmlSceneView.prototype.setDefaultPositionStyle = function () { };
    VHtmlSceneView.prototype.getViewScale = function (obj) { return Math.min(obj.fPosition.getWidth(), obj.fPosition.getHeight()) * obj.fPosition.getScale(); };
    VHtmlSceneView.prototype.relative2SceneX = function (x) { return this.fParent.fLeft + _super.prototype.relative2SceneX.call(this, x); };
    VHtmlSceneView.prototype.relative2SceneY = function (y) { return this.fParent.fTop + _super.prototype.relative2SceneY.call(this, y); };
    VHtmlSceneView.prototype.relative2SceneWidth = function (width) { return this.fReferenceWidth * width / 2; };
    VHtmlSceneView.prototype.relative2SceneHeight = function (height) { return this.fReferenceWidth * height / 2; };
    VHtmlSceneView.prototype.getTranslate = function (obj) { return this.fAbsolutePos ? _super.prototype.getTranslate.call(this, obj) : ""; };
    VHtmlSceneView.prototype.scenePosition = function (obj) {
        var scene = obj;
        this.fAbsolutePos = scene.fAbsolutePos;
        if (this.fAbsolutePos)
            this.getHtml().style.position = IScene.kAbsolute;
    };
    VHtmlSceneView.prototype.updateColor = function (obj) {
        if (obj.fColor.modified()) {
            var elt = this.colorTarget();
            elt.style.backgroundColor = obj.fColor.getRGBString();
            var alpha = obj.fColor.getA() / 255;
            elt.style.opacity = alpha.toString();
        }
    };
    VHtmlSceneView.prototype.updateView = function (obj) {
        this.scenePosition(obj);
        this.fDoc.updatePos(); // not necessary
        this.fWidth = this.fHeight = this.fDoc.fWidth;
        _super.prototype.updateView.call(this, obj);
        if (!this.fAbsolutePos) {
            var elt = this.getHtml();
            elt.style.left = "";
            elt.style.top = "";
        }
        //   this.enableDisableFullScreen(obj);
    };
    return VHtmlSceneView;
}(VHtmlView));
///<reference path="IImage.ts"/>
var ISVGf = (function (_super) {
    __extends(ISVGf, _super);
    function ISVGf(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kSvgfType;
        return _this;
    }
    return ISVGf;
}(IImage));
///<reference path="VHtmlImageView.ts"/>
///<reference path="../model/ISVGf.ts"/>
var VHtmlSVGfView = (function (_super) {
    __extends(VHtmlSVGfView, _super);
    function VHtmlSVGfView(parent) {
        var _this = _super.call(this, parent) || this;
        _this.getHtml().className = "inscore-svgf";
        return _this;
    }
    return VHtmlSVGfView;
}(VHtmlImageView));
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="../model/IText.ts"/>
var VHtmlTextView = (function (_super) {
    __extends(VHtmlTextView, _super);
    function VHtmlTextView(parent) {
        var _this = _super.call(this, parent) || this;
        var elt = _this.getHtml();
        elt.className = "inscore-txt";
        elt.style.verticalAlign = "middle";
        return _this;
    }
    return VHtmlTextView;
}(VHtmlHtmlView));
///<reference path="IObject.ts"/>
var IVideo = (function (_super) {
    __extends(IVideo, _super);
    function IVideo(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kVideoType;
        _this.fPlay = 0;
        _this.fRate = 1;
        _this.fVolume = 1;
        _this.fVDate = new Fraction(0, 1);
        _this.fMLS = 0;
        _this.fVDuration = 0;
        _this.fMsgHandlerMap[kplay_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setPlay(n); });
        _this.fMsgHandlerMap[krate_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setRate(n); });
        _this.fMsgHandlerMap[kvolume_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setVolume(n); });
        _this.fMsgHandlerMap[kvdate_GetSetMethod] = new TMsgHandlerTime(function (n) { _this.setVDate(n); });
        _this.fGetMsgHandlerMap[kplay_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getPlay(); });
        _this.fGetMsgHandlerMap[krate_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getRate(); });
        _this.fGetMsgHandlerMap[kvolume_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getVolume(); });
        _this.fGetMsgHandlerMap[kvdate_GetSetMethod] = new TGetMsgHandlerTime(function () { return _this.getVDate(); });
        _this.fGetMsgHandlerMap[kmls_GetMethod] = new TGetMsgHandlerNum(function () { return _this.getMLS(); });
        _this.fGetMsgHandlerMap[kvduration_GetMethod] = new TGetMsgHandlerNum(function () { return _this.getVDuration(); });
        return _this;
    }
    // MODIFIED STATUS
    //--------------------------------------------------------------      
    IVideo.prototype.cleanup = function () { this.fModified = false; };
    IVideo.prototype.modified = function () { return this.fModified; };
    IVideo.prototype.modify = function () { this.fModified = true; };
    IVideo.prototype.colorAble = function () { }; // color attributes are not available for vidéos
    IVideo.prototype.getFile = function () { return this.fFile; };
    IVideo.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() == 3) {
            var file = msg.paramStr(2);
            if (!file.correct)
                return eMsgStatus.kBadParameters;
            this.fFile = file.value;
            this.newData(true);
            status = eMsgStatus.kProcessed;
        }
        else
            status = eMsgStatus.kBadParameters;
        return status;
    };
    IVideo.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, "'" + this.getFile() + "'"]);
    };
    IVideo.prototype.getPlay = function () { return this.fPlay; };
    IVideo.prototype.getVolume = function () { return this.fVolume; };
    IVideo.prototype.getRate = function () { return this.fRate; };
    IVideo.prototype.getVDate = function () { return this.fVDate; };
    IVideo.prototype.getMLS = function () { return this.fMLS; };
    IVideo.prototype.getVDuration = function () { return this.fVDuration; };
    IVideo.prototype.setPlay = function (play) { this.fPlay = play; this.modify(); };
    IVideo.prototype.setVolume = function (volume) { this.fVolume = volume; this.modify(); };
    IVideo.prototype.setRate = function (rate) { this.fRate = rate; this.modify(); };
    IVideo.prototype.setVDate = function (vDate) {
        if (vDate.getDenominator() == 0) {
            this.fVDate = new Fraction(this.fVDate.getNumerator() / 1000, 1);
            return;
        }
        if (this.fVDate != vDate) {
            this.fVDate = vDate;
            this.modify();
        }
    };
    return IVideo;
}(IObject));
///<reference path="VHtmlAutoSize.ts"/>
///<reference path="../model/IVideo.ts"/>
//interface RefreshMethod 	{ (): void; }
var VHtmlVideoView = (function (_super) {
    __extends(VHtmlVideoView, _super);
    function VHtmlVideoView(parent) {
        var _this = this;
        var video = document.createElement('video');
        _this = _super.call(this, video, parent) || this;
        _this.fVideo = video;
        _this.fFile = "";
        _this.getHtml().className = "inscore-video";
        return _this;
    }
    VHtmlVideoView.prototype.updateView = function (obj) {
        var video = obj;
        if (this.fFile != video.getFile() || this.fFile == "") {
            this.fVideo.src = video.getFile();
            this.fFile = video.getFile();
        }
        _super.prototype.updateView.call(this, obj);
        this.updateVideoControl(video);
    };
    VHtmlVideoView.prototype.setShadow = function (params) {
        var color = new IColor(params.slice(2, 6));
        this.getHtml().style.filter = "drop-shadow(" + color.getCSSRGBAString() + " " + params[0] + "px " + params[1] + "px " + params[6] + "px)";
    };
    VHtmlVideoView.prototype.getAutoElement = function () { return this.fVideo; };
    VHtmlVideoView.prototype.updateVideoControl = function (video) {
        if (video.modified()) {
            video.fPlay ? this.fVideo.play() : this.fVideo.pause();
            this.fVideo.volume = video.fVolume;
            this.fVideo.playbackRate = video.fRate;
            this.fVideo.currentTime += video.fVDate.getNumerator() / video.fVDate.getDenominator();
            video.fMLS = this.fVideo.duration * 1000;
            video.fVDuration = this.fVideo.duration / this.fVideo.playbackRate;
        }
    };
    VHtmlVideoView.prototype.getClientSize = function (video) {
        if (!this.fClientWidth) {
            this.fClientWidth = this.fVideo.videoWidth;
            this.fClientHeight = this.fVideo.videoHeight;
        }
        return { w: this.fClientWidth, h: this.fClientHeight };
    };
    return VHtmlVideoView;
}(VHtmlAutoSize));
///<reference path="../view/ViewFactory.ts"/>
///<reference path="VHtmlArcView.ts"/>
///<reference path="VHtmlCurveView.ts"/>
///<reference path="VHtmlEllipseView.ts"/>
///<reference path="VHtmlGMNView.ts"/>
///<reference path="VHtmlHtmlView.ts"/>
///<reference path="VHtmlImageView.ts"/>
///<reference path="VHtmlLineView.ts"/>
///<reference path="VHtmlPianoRollView.ts"/>
///<reference path="VHtmlPolygonView.ts"/>
///<reference path="VHtmlRectView.ts"/>
///<reference path="VHtmlSceneView.ts"/>
///<reference path="VHtmlSVGfView.ts"/>
///<reference path="VHtmlSVGView.ts"/>
///<reference path="VHtmlTextView.ts"/>
///<reference path="VHtmlVideoView.ts"/>
///<reference path="VHtmlView.ts"/>
var HtmlViewFactory = (function () {
    function HtmlViewFactory() {
    }
    HtmlViewFactory.prototype.create = function (type, parent, name) {
        switch (type) {
            case kEllipseType:
                return new VHtmlEllipseView(parent);
            case kRectType:
                return new VHtmlRectView(parent);
            case kCurveType:
                return new VHtmlCurveView(parent);
            case kLineType:
                return new VHtmlLineView(parent);
            case kPolygonType:
                return new VHtmlPolygonView(parent);
            case kTextType:
            case kTextfType:
                return new VHtmlTextView(parent);
            case kVerovioType:
            case kVeroviofType:
            case kMusicxmlType:
            case kGuidoCodeType:
                return new VHtmlGMNView(parent);
            case kHtmlType:
                return new VHtmlHtmlView(parent);
            case kSceneType:
                return new VHtmlSceneView(name);
            case kSvgfType:
                return new VHtmlSVGfView(parent);
            case kImgType:
                return new VHtmlImageView(parent);
            case kArcType:
                return new VHtmlArcView(parent);
            case kVideoType:
                return new VHtmlVideoView(parent);
            case kGuidoPianoRollType:
                return new VHtmlPianoRollView(parent);
            case kSvgType:
                return new VHtmlSvgView(parent);
            default:
                return null;
        }
    };
    return HtmlViewFactory;
}());
///<reference path="../externals/libfaust.d.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IObject.ts"/>
var IFaust = (function (_super) {
    __extends(IFaust, _super);
    function IFaust(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        //	private fFaustLibraries : string = "http://faust.grame.fr/modules/libraries/";
        _this.fFaustLibraries = "https://raw.githubusercontent.com/grame-cncm/faust/faust2/libraries/";
        _this.fTypeString = kFaustType;
        _this.fDspCode = "";
        _this.fFactory = null;
        _this.fDsp = null;
        _this.fBufferSize = 2048;
        _this.fUI = [];
        if (!IFaust.fAudio) {
            var isWebKitAudio = (typeof webkitAudioContext !== "undefined");
            IFaust.fAudio = (isWebKitAudio) ? new webkitAudioContext() : new AudioContext();
        }
        return _this;
    }
    IFaust.prototype.setHandlers = function () {
        var _this = this;
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler(function (msg) { return _this.set(msg); });
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(function (msg) { return _this.get(msg); });
        this.fMsgHandlerMap[ksave_SetMethod] = new TMethodHandler(function (msg) { return _this.save(msg); });
        this.fMsgHandlerMap[kdel_SetMethod] = new TMsgHandlerVoid(function () { _this.del(); });
        this.eventAble();
        this.fGetMsgsHandlerMap["*"] = new TGetMsgsHandler(function () { return _this.getAllItems(); });
    };
    IFaust.prototype.del = function () {
        this.delDSP();
        _super.prototype.del.call(this);
    };
    IFaust.prototype.delDSP = function () {
        if (this.fDsp) {
            this.fDsp.disconnect(IFaust.fAudio.destination);
            faust.deleteDSPInstance(this.fDsp);
            this.fDsp = null;
        }
        if (this.fFactory) {
            faust.deleteDSPFactory(this.fFactory);
            this.fFactory = null;
        }
    };
    IFaust.prototype.stripAddressHead = function (address) { return address.replace(/\/[^\/]*\//, ""); };
    IFaust.prototype.getAllItems = function () {
        var _this = this;
        var out = [];
        this.fUI.forEach(function (item) { out.push(_this.items2Message(item)); });
        return out;
    };
    IFaust.prototype.items2Message = function (item) {
        var params = [this.stripAddressHead(item.address)];
        if (item.init)
            params = params.concat([item.init, item.min, item.max]);
        return new IMessage(this.getOSCAddress(), params);
    };
    IFaust.prototype.item2array = function (item) {
        return item.init ? [item.init, item.min, item.max] : [];
    };
    IFaust.prototype.buildUIItem = function (i) {
        var _this = this;
        if (i.type.substr(1) == "group") {
            var group = i;
            this.buildUIItems(group.items);
        }
        else if (i.type == "attach") {
        }
        else {
            var item_1 = i;
            this.fUI.push(item_1);
            var shortaddress = this.stripAddressHead(item_1.address);
            this.fMsgHandlerMap[shortaddress] = new TMsgHandlerNum(function (n) { _this.fDsp.setParamValue(item_1.address, n); });
            this.fGetMsgHandlerMap[shortaddress] = new TGetMsgHandlerArray(function () { return _this.item2array(item_1); });
        }
    };
    IFaust.prototype.buildUIItems = function (items) {
        var _this = this;
        items.forEach(function (item) { _this.buildUIItem(item); });
    };
    IFaust.prototype.buildUIFromJSON = function (json) {
        var _this = this;
        var desc;
        eval("desc=" + json);
        this.fUI = [];
        desc.ui.forEach(function (elt) { _this.buildUIItems(elt.items); });
    };
    IFaust.prototype.instanceReady = function (dsp) {
        if (this.fDsp) {
            this.fDsp.disconnect(IFaust.fAudio.destination);
            faust.deleteDSPInstance(this.fDsp);
        }
        this.fDsp = dsp;
        //		if (dsp.getNumInputs() > 0) activateAudioInput();
        dsp.connect(IFaust.fAudio.destination);
        this.buildUIFromJSON(dsp.json());
    };
    IFaust.prototype.factoryReady = function (factory) {
        var _this = this;
        if (!factory)
            ITLError.write("Faust factory creation failed: " + faust.getErrorMessage());
        else {
            if (this.fFactory)
                faust.deleteDSPFactory(this.fFactory);
            this.fFactory = factory;
            faust.createDSPInstance(factory, IFaust.fAudio, this.fBufferSize, function (arg) { return _this.instanceReady(arg); });
        }
    };
    IFaust.prototype.createDsp = function (code) {
        var _this = this;
        this.fDspCode = code;
        faust.createDSPFactory(code, ["-I", this.fFaustLibraries], function (arg) { return _this.factoryReady(arg); });
        return true;
    };
    IFaust.prototype.objectset = function (msg) { return _super.prototype.set.call(this, msg); };
    // SET HANDLER
    //--------------------------------------------------------------    
    IFaust.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        var n = msg.size();
        if (n != 3)
            return eMsgStatus.kBadParameters;
        var code = msg.paramStr(2);
        if (!code.correct)
            return eMsgStatus.kBadParameters;
        if (this.createDsp(code.value))
            return eMsgStatus.kProcessed;
        ITLError.write("Faust dsp creation failed: " + faust.getErrorMessage());
        return eMsgStatus.kProcessed;
    };
    // GETSET METHOD
    //--------------------------------------------------------------    
    IFaust.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fDspCode]);
    };
    return IFaust;
}(IObject));
IFaust.fAudio = null;
///<reference path="../externals/libfaust.d.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="IFaust.ts"/>
var IFaustf = (function (_super) {
    __extends(IFaustf, _super);
    function IFaustf(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kFaustfType;
        _this.fFile = "";
        return _this;
    }
    // READER METHOD
    //--------------------------------------------------------------    
    IFaustf.prototype.success = function (content) {
        this.createDsp(content);
    };
    IFaustf.prototype.error = function (content) {
        console.log("Read file error !");
    };
    // SET HANDLER
    //--------------------------------------------------------------    
    IFaustf.prototype.set = function (msg) {
        var _this = this;
        var status = this.objectset(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        var n = msg.size();
        if (n != 3)
            return eMsgStatus.kBadParameters;
        var file = msg.paramStr(2);
        if (!file.correct)
            return eMsgStatus.kBadParameters;
        this.fFile = file.value;
        Tools.readFile(file.value, function (arg) { return _this.success(arg); }, function (arg) { return _this.error(arg); });
        return eMsgStatus.kProcessed;
    };
    // GETSET METHOD
    //--------------------------------------------------------------    
    IFaustf.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fFile]);
    };
    return IFaustf;
}(IFaust));
///<reference path="../externals/libGUIDOEngine.d.ts"/>
///<reference path="../vhtmlview/VHtmlTools.ts"/>
///<reference path="IGuidoCode.ts"/>
var kCLine = 1;
var kCSharpLine = 1 << 1;
var kDLine = 1 << 2;
var kDSharpLine = 1 << 3;
var kELine = 1 << 4;
var kFLine = 1 << 5;
var kFSharpLine = 1 << 6;
var kGLine = 1 << 7;
var kGSharpLine = 1 << 8;
var kALine = 1 << 9;
var kASharpLine = 1 << 10;
var kBLine = 1 << 11;
var kAutoLines = 0;
var kNoLine = -1;
var IGuidoPianoRoll = (function (_super) {
    __extends(IGuidoPianoRoll, _super);
    //std::map<int, IColor> fVoicesColor;
    function IGuidoPianoRoll(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kGuidoPianoRollType;
        _this.fKeyboard = false;
        _this.fAutoVoiceColor = false;
        _this.fMeasureBars = false;
        _this.fPitchLines = kAutoLines;
        //this.fLimits.lowPitch = -1;
        //this.fLimits.highPitch = -1;
        _this.setWidth(1);
        _this.setHeight(0.5);
        _super.prototype.setHandlers.call(_this);
        _this.fMsgHandlerMap[kwidth_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setWidth(n); });
        _this.fMsgHandlerMap[kheight_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setHeight(n); });
        return _this;
    }
    IGuidoPianoRoll.prototype.getPRollMap = function (pr) { this.guidoMap2inscoreMap(IGuidoCode.fGuidoMap.getPianoRollMap(pr, 1, 1)); };
    ;
    IGuidoPianoRoll.prototype.AR2SVG = function (size) {
        if (this.fAR) {
            var pr = IGuidoCode.fPianoRoll.ar2PianoRoll(PianoRollType.kSimplePianoRoll, this.fAR);
            this.fSVG = IGuidoCode.fPianoRoll.svgExport(pr, size.w, size.h);
            this.getPRollMap(pr);
            IGuidoCode.fPianoRoll.destroyPianoRoll(pr);
        }
        return this.fSVG;
    };
    return IGuidoPianoRoll;
}(IGuidoCode));
///<reference path="IGuidoCode.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libmusicxml.d.ts"/>
var IMusicXml = (function (_super) {
    __extends(IMusicXml, _super);
    function IMusicXml(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        if (!IMusicXml.fXMLLib) {
            var module = MusicXMLModule();
            IMusicXml.fXMLLib = new module.libMusicXMLAdapter();
            console.log("libmusicxml version " + IMusicXml.fXMLLib.libVersionStr() + " using gmn converter version " + IMusicXml.fXMLLib.musicxml2guidoVersionStr());
        }
        _this.fTypeString = kMusicxmlType;
        _this.fXML = null;
        return _this;
    }
    IMusicXml.prototype.xml2guido = function (xml) {
        var gmn = IMusicXml.fXMLLib.string2guido(xml, false);
        if (gmn.length) {
            this.fGMN = gmn;
            return true;
        }
        return false;
    };
    IMusicXml.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() != 3)
            return eMsgStatus.kBadParameters;
        var xml = msg.paramStr(2);
        if (!xml.correct)
            return eMsgStatus.kBadParameters;
        this.fXML = xml.value;
        if (!this.xml2guido(xml.value))
            return eMsgStatus.kBadParameters;
        if (!this.str2AR(this.fGMN))
            return eMsgStatus.kBadParameters;
        this.fNewData = true;
        return eMsgStatus.kProcessed;
    };
    IMusicXml.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fXML]);
    };
    return IMusicXml;
}(IGuidoCode));
///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>
///<reference path="IRectShape.ts"/>
var IScene = (function (_super) {
    __extends(IScene, _super);
    function IScene(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kSceneType;
        _this.fAbsolutePos = false;
        _this.fPosition.setWidth(1);
        _this.fPosition.setHeight(1);
        return _this;
    }
    IScene.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(function () { _this.newScene(); });
        this.fMsgHandlerMap["redraw"] = new TMsgHandlerVoid(function () { _this.redraw(); });
        this.fMsgHandlerMap[kposition_GetSetMethod] = new TMsgHandlerText(function (s) { _this.setPositionStyle(s); });
        this.fMsgHandlerMap[kfullscreen_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setFullScreen(n); });
        this.fGetMsgHandlerMap[kfullscreen_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getFullScreen(); });
        this.fGetMsgHandlerMap[kposition_GetSetMethod] = new TGetMsgHandlerText(function () { return _this.getPositionStyle(); });
    };
    IScene.prototype.getPositionStyle = function () { return this.fAbsolutePos ? IScene.kAbsolute : IScene.kRelative; };
    IScene.prototype.setPositionStyle = function (position) { this.fAbsolutePos = (position === IScene.kAbsolute); this.fPosition.modify(); };
    IScene.prototype.getRScale = function () { return this.fPosition.getScale(); };
    IScene.prototype.getRSizeAsScale = function () { return Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()) / 2; };
    IScene.prototype.timeAble = function () { };
    IScene.prototype.redraw = function () { this.posPropagate(); };
    IScene.prototype.newScene = function () { };
    IScene.prototype.getScene = function () { return this; };
    IScene.prototype.getSet = function () { return new IMessage(this.getOSCAddress(), knew_SetMethod); };
    //-----------------------FullScreen-GetSet---------------------------
    IScene.prototype.getFullScreen = function () { return this.fFullScreen ? 1 : 0; };
    IScene.prototype.setFullScreen = function (full) { this.fFullScreen = full ? true : false; };
    return IScene;
}(IRectShape));
IScene.kAbsolute = "absolute";
IScene.kRelative = "relative";
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="IObject.ts"/>
///<reference path="TSyncInfo.ts"/>
//--------------------------------------------------------------  
// glue between slave, master and sync params
//--------------------------------------------------------------  
var TSyncNode = (function () {
    function TSyncNode(slave, master, info, views) {
        this.fSlave = slave;
        this.fMaster = master;
        this.fInfos = new TSyncInfo();
        this.fViews = views;
        this.fInfos.update(info);
    }
    //---------------------------------------------
    TSyncNode.prototype.update = function (infos) { this.fInfos.update(infos); };
    //---------------------------------------------
    // conversion methods
    //---------------------------------------------
    TSyncNode.prototype.toString = function () { return this.fSlave.getName() + " " + this.fMaster.getName() + " " + this.fInfos; };
    ;
    TSyncNode.prototype.toArray = function () {
        var out = [this.fSlave.getName(), this.fMaster.getName()];
        out = out.concat(this.fInfos.toArray());
        return out;
    };
    return TSyncNode;
}());
//--------------------------------------------------------------  
// synchronisation management node
//--------------------------------------------------------------  
var ISync = (function (_super) {
    __extends(ISync, _super);
    function ISync(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kSyncType;
        _this.fSyncList = [];
        return _this;
    }
    //------------------------------------
    ISync.prototype.findSync = function (name, syncname) {
        var out = [];
        var f = function (sync) { if (syncname(sync) === name)
            out.push(sync); };
        if (Tools.regexp(name)) {
            var re_1 = new OSCRegexp(name);
            f = function (sync) { if (re_1.match(syncname(sync)))
                out.push(sync); };
        }
        this.fSyncList.forEach(f);
        return out;
    };
    //------------------------------------
    ISync.prototype.findSyncBySlaveName = function (name) {
        return this.findSync(name, function (sync) { return sync.fSlave.getName(); });
    };
    //------------------------------------
    ISync.prototype.findSyncByMasterName = function (name) {
        return this.findSync(name, function (sync) { return sync.fMaster.getName(); });
    };
    //------------------------------------
    ISync.prototype.findSyncNodes = function (slave, master) {
        var out = [];
        var sync = this.findSyncBySlaveName(slave);
        if (!sync.length)
            return out;
        var f = function (name) { return name === master; };
        if (Tools.regexp(master)) {
            var re_2 = new OSCRegexp(master);
            f = function (name) { return re_2.match(name); };
        }
        sync.forEach(function (node) { if (f(node.fMaster.getName()))
            out.push(node); });
        return out;
    };
    //------------------------------------
    ISync.prototype.restoreDefaultView = function (obj) {
        var views = IObjectFactory.createViews(obj, obj.getParent().getViews());
        views.forEach(function (view) { obj.setView(view); });
        obj.subModPropagate(obj.getParent());
        obj.allModified();
    };
    //------------------------------------
    ISync.prototype.removeSync = function (obj) { this.clearName(obj.getName()); };
    ISync.prototype.clearName = function (obj) {
        var _this = this;
        var targets = this.findSyncBySlaveName(obj);
        targets.forEach(function (sync) {
            var i = _this.fSyncList.indexOf(sync);
            if (i >= 0) {
                sync.fViews.forEach(function (view) { sync.fSlave.removeView(view); });
                if (!sync.fSlave.getViews().length)
                    _this.restoreDefaultView(sync.fSlave);
                _this.fSyncList.splice(i, 1);
            }
        });
        return eMsgStatus.kProcessedNoChange;
    };
    //------------------------------------
    ISync.prototype.updateSync = function (node, syncparams) {
        node.update(syncparams);
        var slave = node.fSlave;
        slave.subModPropagate(node.fMaster);
        slave.posModified();
    };
    //------------------------------------
    ISync.prototype.createSync = function (slave, master, syncparams) {
        var n = this.findSyncBySlaveName(slave.getName()).length;
        if (!n) {
            slave.removeViews(); // remove the standard view
        }
        var views = IObjectFactory.createViews(slave, master.getViews());
        var sync = new TSyncNode(slave, master, syncparams, views);
        this.fSyncList.push(sync);
        views.forEach(function (view) {
            slave.addView(view);
            view.setPositionHandler(function () { return slave.getSlavePosition(master, sync.fInfos); });
        });
        slave.subModPropagate(master);
        slave.allModified();
    };
    //------------------------------------
    ISync.prototype.getOne = function (name) {
        var _this = this;
        var out = [];
        var syncs = this.findSyncBySlaveName(name);
        syncs.forEach(function (sync) { out.push(new IMessage(_this.getOSCAddress(), sync.toArray())); });
        return out;
    };
    //------------------------------------
    ISync.prototype.getAll = function () {
        var _this = this;
        var out = [];
        this.fSyncList.forEach(function (sync) { out.push(new IMessage(_this.getOSCAddress(), sync.toArray())); });
        return out;
    };
    //------------------------------------
    ISync.prototype.setSync = function (msg) {
        var _this = this;
        var slaveName = msg.paramStr(0);
        var masterName = msg.paramStr(1);
        if (!slaveName.correct || !masterName.correct)
            return eMsgStatus.kBadParameters;
        var syncparams = new TSyncInfo();
        if (!syncparams.set(msg))
            return eMsgStatus.kBadParameters;
        var nodes = this.findSyncNodes(slaveName.value, masterName.value);
        if (nodes.length)
            nodes.forEach(function (node) { _this.updateSync(node, syncparams); });
        else {
            var slaves = this.fParent.find(slaveName.value);
            if (!slaves.length) {
                ITLError.write(slaveName.value + ": no such object!");
                return eMsgStatus.kBadParameters;
            }
            var masters = this.fParent.find(masterName.value);
            if (!masters.length) {
                ITLError.write(masterName.value + ": no such object!");
                return eMsgStatus.kBadParameters;
            }
            for (var i = 0; i < slaves.length; i++) {
                for (var j = 0; j < masters.length; j++)
                    if ((slaves[i].fTypeString != kSyncType) && (masters[j].fTypeString != kSyncType))
                        this.createSync(slaves[i], masters[j], syncparams);
            }
        }
        return eMsgStatus.kProcessedNoChange;
    };
    //------------------------------------
    ISync.prototype.getCall = function (msg) {
        var n = msg.size();
        if (n == 1)
            return this.getAll();
        var out = [];
        for (var i = 1; i < n; i++) {
            var arg = msg.paramStr(i);
            if (arg.correct) {
                var msgs = this.getOne(arg.value);
                if (msgs)
                    msgs.forEach(function (msg) { out.push(msg); });
            }
        }
        return out;
    };
    //------------------------------------
    // overrides execute: no standard message processing apart for 'get'
    //------------------------------------
    ISync.prototype.execute = function (msg) {
        var n = msg.size();
        if (!n)
            return eMsgStatus.kBadParameters;
        var p1 = msg.paramStr(0);
        if (!p1.correct)
            return eMsgStatus.kBadParameters;
        var get = (p1.value == kget_SetMethod); // is it a get message?        
        if (get)
            return this.get(msg);
        if (n == 1)
            return this.clearName(p1.value);
        return this.setSync(msg);
    };
    //------------------------------------
    // delNotify : notifications activated by nodes
    //------------------------------------
    ISync.prototype.delNotify = function (obj) {
        var _loop_1 = function () {
            var sync = this_1.fSyncList[i];
            if (sync.fSlave.getDeleted())
                this_1.fSyncList.splice(i, 1);
            else if (sync.fMaster.getDeleted()) {
                sync.fViews.forEach(function (view) { sync.fSlave.removeView(view); });
                if (!sync.fSlave.getViews().length)
                    this_1.restoreDefaultView(sync.fSlave);
                this_1.fSyncList.splice(i, 1);
            }
            else
                i++;
        };
        var this_1 = this;
        for (var i = 0; i < this.fSyncList.length;) {
            _loop_1();
        }
    };
    ISync.prototype.createStaticNodes = function () { };
    return ISync;
}(IObject));
///<reference path="IText.ts"/>
var ITextf = (function (_super) {
    __extends(ITextf, _super);
    function ITextf(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kTextfType;
        return _this;
    }
    ITextf.prototype.setHandlers = function () {
        var _this = this;
        _super.prototype.setHandlers.call(this);
        this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText(function () { return _this.getTextFile(); });
    };
    // GETS / SETS VALUES 
    //--------------------------------------------------------------    
    ITextf.prototype.getTextFile = function () { return this.fFile; };
    ITextf.prototype.setTextFile = function (file) { this.fFile = file; };
    // SET HANDLER
    //--------------------------------------------------------------    
    ITextf.prototype.set = function (msg) {
        var _this = this;
        var status = _super.prototype.set.call(this, msg);
        if (status != eMsgStatus.kProcessed)
            return status;
        var file = Tools.setFile(msg, function (arg) { return _this.success(arg); }, function (arg) { return _this.error(arg); });
        if (file) {
            this.fFile = file;
            return eMsgStatus.kProcessed;
        }
        return eMsgStatus.kBadParameters;
    };
    ITextf.prototype.getText = function () {
        if (this.fText !== "")
            return this.fText;
        else
            return this.fFile;
    };
    // GETSET METHOD
    //--------------------------------------------------------------    
    ITextf.prototype.getSet = function () {
        var a = [kset_SetMethod, this.fTypeString];
        return new IMessage(this.getOSCAddress(), a.concat("'" + this.fFile + "'"));
    };
    // READER METHOD
    //--------------------------------------------------------------    
    ITextf.prototype.success = function (content) {
        this.fText = content;
        this.newData(true);
        this.addState(eObjState.kModified);
        this.subModPropagate(this.fParent);
    };
    ITextf.prototype.error = function (content) {
        console.log("Text file error !");
    };
    return ITextf;
}(IText));
///<reference path="IObject.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/verovio-toolkit.d.ts"/>
///<reference path="../mapping/TTime2GraphicMap.ts"/>
var IVerovio = (function (_super) {
    __extends(IVerovio, _super);
    function IVerovio(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        if (!IVerovio.fVerovio) {
            IVerovio.fVerovio = new verovio.toolkit();
            console.log("Verovio " + IVerovio.fVerovio.getVersion());
        }
        _this.fTypeString = kVerovioType;
        _this.fPage = 1;
        _this.fSVG = "";
        _this.fPosition.setWidth(0);
        _this.fPosition.setHeight(0);
        _super.prototype.setHandlers.call(_this);
        return _this;
    }
    IVerovio.prototype.setSVG = function (gmn) { this.fSVG = gmn; /*localMapModified(true);*/ };
    IVerovio.prototype.setPage = function (page) { this.fPage = page; /*localMapModified(true);*/ };
    //setdPage(dpage: number): void                       {}
    IVerovio.prototype.mei2svg = function (data) {
        this.fMEI = data;
        this.fSVG = IVerovio.fVerovio.renderData(this.fMEI, {});
        this.fNewData = true;
    };
    IVerovio.prototype.getSVG = function (size) { return this.fSVG.length ? this.fSVG : ""; };
    IVerovio.prototype.getPage = function () { return this.fPage; };
    //getPageCount(): number              {return}
    IVerovio.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        if (msg.size() != 3)
            return eMsgStatus.kBadParameters;
        var mei = msg.paramStr(2);
        if (!mei.correct)
            return eMsgStatus.kBadParameters;
        this.mei2svg(mei.value);
        return eMsgStatus.kProcessed;
    };
    IVerovio.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fMEI]);
    };
    return IVerovio;
}(IObject));
///<reference path="IVerovio.ts"/>
///<reference path="../lib/Tools.ts"/>
var IVeroviof = (function (_super) {
    __extends(IVeroviof, _super);
    function IVeroviof(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kVeroviofType;
        _this.fFile = "";
        return _this;
    }
    IVeroviof.prototype.setSVG = function (gmn) { this.fSVG = gmn; /*localMapModified(true);*/ };
    IVeroviof.prototype.getSVG = function (size) { return this.fSVG.length ? this.fSVG : Tools.string2svg(this.fFile); };
    IVeroviof.prototype.set = function (msg) {
        var _this = this;
        var status = this.basicSet(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        var file = Tools.setFile(msg, function (arg) { return _this.success(arg); }, function (arg) { return _this.error(arg); });
        if (file) {
            this.fFile = file;
            return eMsgStatus.kProcessed;
        }
        return eMsgStatus.kBadParameters;
    };
    IVeroviof.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fFile]);
    };
    // READER METHOD
    //--------------------------------------------------------------    
    IVeroviof.prototype.success = function (content) {
        this.mei2svg(content);
        this.fNewData = true;
        this.addState(eObjState.kModified);
        this.subModPropagate(this.fParent);
    };
    IVeroviof.prototype.error = function (content) {
        console.log(content);
        this.fSVG = Tools.error2svg();
        this.fNewData = true;
        this.addState(eObjState.kModified);
        this.subModPropagate(this.fParent);
    };
    return IVeroviof;
}(IVerovio));
///<reference path="IObject.ts"/>
/*
interface TParseEnv {
    getJSEngine(): TJSEngine;
    getLUAEngine(): TLua;
    error(): void;
    parseEnv(): TParseEnv;
}
*/
var IWebSocket = (function (_super) {
    __extends(IWebSocket, _super);
    function IWebSocket(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = kWebSocketType;
        _super.prototype.setHandlers.call(_this);
        return _this;
    }
    IWebSocket.prototype.setControler = function (ctrl) { this.fWebServer = ctrl; };
    IWebSocket.prototype.getPort = function () { return this.fPort; };
    IWebSocket.prototype.getFrequency = function () { return this.fFrequency; };
    //getParseEnv()   : TParseEnv	{ return this.getAppl(); }
    IWebSocket.prototype.running = function () { return this.fWebServer.running(); };
    IWebSocket.prototype.status = function () { return this.running() ? "running" : "stopped"; };
    IWebSocket.prototype.start = function (port) { return this.fWebServer.start(port); };
    IWebSocket.prototype.set = function (msg) {
        var status = _super.prototype.set.call(this, msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange))
            return status;
        // Two parameters are mandatory : port and notification time.
        if (msg.size() != 3)
            return eMsgStatus.kBadParameters;
        var port = -1;
        var frequency = -1;
        var a = msg.paramNum(3), b = msg.paramNum(4);
        if (!a.correct || !b.correct) {
            return eMsgStatus.kBadParameters;
        }
        if (!a.value || !b.value) {
            return eMsgStatus.kBadParameters;
        }
        var restart = false;
        if (frequency != this.fFrequency) {
            this.fFrequency = frequency;
            restart = true;
        }
        if (port != this.fPort) {
            this.fPort = port;
            restart = true;
        }
        if (restart) {
            if (!this.start(port)) {
                //ITLErr << "Cannot create web socket server on port " << this.fPort << ITLEndl;
                return eMsgStatus.kCreateFailure;
            }
        }
        return eMsgStatus.kProcessed;
    };
    /*
        getMsgs(msg: IMessage): IMessageList {
            let outMsgs: IMessageList;
            for ( let i = 0 ; i < msg.size() ; i++ ) {
                let param: string = "-";
                msg.param(i, param);
    
                if ( param == "clients" ) {
                    let msg: IMessage = IMessage.create(getOSCAddress(), param);
                    msg << fWebServer.clients();
                    outMsgs.list().push_back (msg);
                }
            }
            outMsgs.list().push_back (IObject.getMsgs(msg).list());
            return outMsgs;
        }
    */
    IWebSocket.prototype.getSet = function () {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPort, this.fFrequency]);
    };
    return IWebSocket;
}(IObject));
///<reference path="../globals.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../vhtmlview/HtmlViewFactory.ts"/>
///<reference path="IArc.ts"/>
///<reference path="ICurve.ts"/>
///<reference path="IDebug.ts"/>
///<reference path="IEllipse.ts"/>
///<reference path="IFaust.ts"/>
///<reference path="IFaustf.ts"/>
///<reference path="IGuidoCode.ts"/>
///<reference path="IGuidoPianoRoll.ts"/>
///<reference path="IHtml.ts"/>
///<reference path="IImage.ts"/>
///<reference path="ILine.ts"/>
///<reference path="IMusicXml.ts"/>
///<reference path="IPolygon.ts"/>
///<reference path="IRect.ts"/>
///<reference path="IScene.ts"/>
///<reference path="ISVG.ts"/>
///<reference path="ISVGf.ts"/>
///<reference path="ISync.ts"/>
///<reference path="IText.ts"/>
///<reference path="ITextf.ts"/>
///<reference path="IVerovio.ts"/>
///<reference path="IVeroviof.ts"/>
///<reference path="IWebSocket.ts"/>
///<reference path="Methods.ts"/>
///<reference path="IObjectFactory-interface.ts"/>
var IObjectFactoryImpl = (function (_super) {
    __extends(IObjectFactoryImpl, _super);
    function IObjectFactoryImpl() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.fViewFactory = new HtmlViewFactory();
        return _this;
    }
    IObjectFactoryImpl.prototype.createView = function (obj) {
        var view = this.fViewFactory.create(obj.getTypeString(), null, obj.getName());
        view.setPositionHandler(function () { return obj.getPosition(); });
        return view;
    };
    IObjectFactoryImpl.prototype.createViews = function (obj, parent) {
        var out = [];
        if (gCreateView) {
            for (var i = 0; i < parent.length; i++) {
                var view = this.fViewFactory.create(obj.getTypeString(), parent[i], obj.getName());
                view.setPositionHandler(function () { return obj.getPosition(); });
                out.push(view);
            }
        }
        return out;
    };
    IObjectFactoryImpl.prototype.createObj = function (name, type, parent) {
        //        console.log("IObjetFactory createObj " + type);
        var obj;
        switch (type) {
            case kDebugType: return new IDebug(name, parent);
            case kSyncType: return new ISync(name, parent);
            case kFaustType: return new IFaust(name, parent);
            case kFaustfType: return new IFaustf(name, parent);
            case kSceneType:
                obj = new IScene(name, parent);
                obj.setView(this.createView(obj));
                return obj;
            case kEllipseType:
                obj = new IEllipse(name, parent);
                break;
            case kRectType:
                obj = new IRect(name, parent);
                break;
            case kCurveType:
                obj = new ICurve(name, parent);
                break;
            case kLineType:
                obj = new ILine(name, parent);
                break;
            case kGuidoCodeType:
                obj = new IGuidoCode(name, parent);
                break;
            case kGuidoPianoRollType:
                obj = new IGuidoPianoRoll(name, parent);
                break;
            case kPolygonType:
                obj = new IPolygon(name, parent);
                break;
            case kTextType:
                obj = new IText(name, parent);
                break;
            case kTextfType:
                obj = new ITextf(name, parent);
                break;
            case kHtmlType:
                obj = new IHtml(name, parent);
                break;
            case kImgType:
                obj = new IImage(name, parent);
                break;
            case kArcType:
                obj = new IArc(name, parent);
                break;
            case kVideoType:
                obj = new IVideo(name, parent);
                break;
            case kSvgType:
                obj = new ISVG(name, parent);
                break;
            case kSvgfType:
                obj = new ISVGf(name, parent);
                break;
            case kMusicxmlType:
                obj = new IMusicXml(name, parent);
                break;
            case kVerovioType:
                obj = new IVerovio(name, parent);
                break;
            case kVeroviofType:
                obj = new IVeroviof(name, parent);
                break;
            case kWebSocketType:
                obj = new IWebSocket(name, parent);
                break;
            default:
                ITLError.write("IObjectFactory: unknown object type: " + type);
                return null;
        }
        obj.addViews(this.createViews(obj, parent.getViews()));
        return obj;
    };
    return IObjectFactoryImpl;
}(IObjectFactoryInterface));
IObjectFactory = new IObjectFactoryImpl();
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="IObjectFactory.ts"/>
///<reference path="IProxyInterface.ts"/>
var IProxyImpl = (function (_super) {
    __extends(IProxyImpl, _super);
    function IProxyImpl() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    IProxyImpl.prototype.execute = function (msg, objName, parent) {
        if (Tools.regexp(objName)) {
            return { status: eMsgStatus.kBadAddress };
        }
        var objType;
        var method = msg.message();
        if (!method.correct)
            return { status: eMsgStatus.kBadParameters };
        // check if we try to create a scene
        if (parent && (parent.getTypeString() == 'IAppl')) {
            if (method.value != 'new')
                return { status: eMsgStatus.kBadAddress };
            if (msg.size() != 1)
                return { status: eMsgStatus.kBadParameters };
            objType = 'scene';
        }
        else {
            if (method.value != 'set')
                return { status: eMsgStatus.kBadAddress };
            if (msg.size() < 2)
                return { status: eMsgStatus.kBadParameters };
            var type = msg.paramStr(1);
            if (!type.correct)
                return { status: eMsgStatus.kBadParameters };
            objType = type.value;
        }
        // eventually create the new object
        var obj = IObjectFactory.createObj(objName, objType, parent);
        if (obj) {
            var ret = obj.execute(msg);
            if (ret & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) {
                parent.addChild(obj);
                obj.setState(eObjState.kModified);
                return { status: eMsgStatus.kProcessed, obj: obj };
            }
            return { status: ret };
        }
        return { status: eMsgStatus.kCreateFailure };
    };
    return IProxyImpl;
}(IProxyInterface));
IProxy = new IProxyImpl();
///<reference path="../model/IObject.ts"/>
///<reference path="../model/IApplStaticNodes.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../inscore.ts"/>
var VHtmlLog = (function (_super) {
    __extends(VHtmlLog, _super);
    function VHtmlLog() {
        var _this = _super.call(this) || this;
        _this.fPreviousX = -1; // the window previous position: used to detect window move
        _this.fPreviousY = -1;
        _this.fPreviousOX = -1; // the object previous position: used to handle window move
        _this.fPreviousOY = -1;
        return _this;
    }
    VHtmlLog.prototype.updateView = function (obj) {
        if (obj.fPosition.getVisible()) {
            var pos = obj.getPosition();
            var size = obj.getSize();
            var posChge = ((this.fPreviousOX < 0) ? true : (pos.x != this.fPreviousOX)) ||
                ((this.fPreviousOY < 0) ? true : (pos.y != this.fPreviousOY));
            this.fPreviousOX = pos.x;
            this.fPreviousOY = pos.y;
            if (this.checkwindow(obj)) {
                this.fWindow.focus();
                if (obj.fPosition.modified()) {
                    this.fWindow.resizeTo(this.relative2SceneWidth(size.w), this.relative2SceneHeight(size.h));
                    if (posChge) {
                        var top_1 = this.relative2SceneY(pos.y - (size.h / 2));
                        var left = this.relative2SceneX(pos.x - (size.w / 2));
                        this.fWindow.moveTo(left, top_1);
                    }
                }
                this.writelog(obj);
            }
        }
        else if (this.fWindow) {
            this.fWindow.close();
            this.close(obj);
        }
    };
    VHtmlLog.prototype.setPositionHandler = function (fpos) { };
    ;
    VHtmlLog.prototype.writelog = function (log) {
        if (log.cleared())
            this.fWindow.document.body.innerHTML = "";
        var content = log.content();
        for (var i = 0; i < content.length; i++) {
            this.fWindow.document.write(content[i] + "<br />\n");
            this.fWindow.window.scrollBy(0, 50);
        }
        log.done();
    };
    VHtmlLog.prototype.checkwindowpos = function (obj) {
        var size = obj.getSize();
        var wx = this.fWindow.screenX;
        if (wx != this.fPreviousX)
            obj.fPosition.setXPos(this.scene2RelativeX(wx) + (size.w / 2));
        var wy = this.fWindow.screenY;
        if (wy != this.fPreviousY)
            obj.fPosition.setYPos(this.scene2RelativeY(wy) + (size.h / 2));
        this.fPreviousX = wx;
        this.fPreviousY = wy;
    };
    VHtmlLog.prototype.close = function (obj) {
        this.checkwindowpos(obj); // update the last window position
        this.fWindow = undefined;
    };
    VHtmlLog.prototype.closeHandler = function (obj) {
        this.close(obj);
        obj.fPosition.setVisible(0);
    };
    VHtmlLog.prototype._close = function (o) {
        var _this = this;
        return function () { return _this.closeHandler(o); };
    };
    VHtmlLog.prototype.getCurrentStyleSheets = function () {
        var style = "";
        for (var i in document.styleSheets) {
            var href = document.styleSheets[i].href;
            if (href) {
                style += "<link href='" + href + "' rel='stylesheet'>\n";
            }
        }
        return style;
    };
    VHtmlLog.prototype.checkwindow = function (obj) {
        if (!this.fWindow) {
            var specs = "menubar=no, titlebar=no, status=no, directories=no, location=no";
            var style = this.getCurrentStyleSheets();
            this.fWindow = window.open("", obj.getOSCAddress(), specs);
            if (this.fWindow) {
                this.fWindow.document.write("<head><title>" + obj.getOSCAddress() + "</title>\n" + style + "</head>");
                this.fWindow.document.write("<body class='inscore-log'></body>");
                this.fWindow.addEventListener("resize", this._resizeLog(obj));
                this.fWindow.addEventListener("unload", this._close(obj));
                return true;
            }
            return false;
        }
        else {
            this.checkwindowpos(obj);
            this.fWindow.focus();
        }
        return true;
    };
    VHtmlLog.prototype.resizeLog = function (obj) {
        var w = this.scene2RelativeWidth(this.fWindow.outerWidth);
        var h = this.scene2RelativeHeight(this.fWindow.outerHeight);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
    };
    VHtmlLog.prototype._resizeLog = function (obj) {
        var _this = this;
        return function () { return _this.resizeLog(obj); };
    };
    VHtmlLog.prototype.updateObjectSize = function (obj) { };
    VHtmlLog.prototype.remove = function () { };
    VHtmlLog.prototype.relative2SceneX = function (x) { var w = screen.availWidth / 2; return w + (w * x); };
    VHtmlLog.prototype.relative2SceneY = function (y) { var h = screen.availHeight / 2; return h + (h * y); };
    VHtmlLog.prototype.relative2SceneWidth = function (width) { return screen.availWidth * width / 2; };
    VHtmlLog.prototype.relative2SceneHeight = function (height) { return screen.availHeight * height / 2; };
    VHtmlLog.prototype.scene2RelativeWidth = function (width) { return width * 2 / screen.availWidth; };
    VHtmlLog.prototype.scene2RelativeHeight = function (height) { return height * 2 / screen.availHeight; };
    VHtmlLog.prototype.scene2RelativeX = function (x) { var w = screen.availWidth / 2; return (x - w) / w; };
    VHtmlLog.prototype.scene2RelativeY = function (y) { var h = screen.availHeight / 2; return (y - h) / h; };
    VHtmlLog.prototype.initialize = function (obj) { };
    return VHtmlLog;
}(VObjectView));
///<reference path="IObject.ts"/>
var IStaticNode = (function (_super) {
    __extends(IStaticNode, _super);
    function IStaticNode(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = 'static';
        return _this;
    }
    IStaticNode.prototype.del = function () { }; // a static node cannot be deleted
    IStaticNode.prototype.getSet = function () { var m; return m; }; // and cannot be created using set
    return IStaticNode;
}(IObject));
///<reference path="../controller/IMessage.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../vhtmlview/VHtmlLog.ts"/>
///<reference path="IStaticNode.ts"/>
var IApplLog = (function (_super) {
    __extends(IApplLog, _super);
    function IApplLog(name, parent) {
        var _this = _super.call(this, name, parent) || this;
        _this.fTypeString = 'log';
        _this.fLog = new Array();
        _this.fClear = false;
        _this.fPosition.setVisible(0);
        _this.fPosition.setWidth(0.8);
        _this.fPosition.setHeight(0.5);
        _this.setView(new VHtmlLog());
        return _this;
    }
    IApplLog.prototype.setHandlers = function () {
        var _this = this;
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(function (msg) { return _this.get(msg); });
        this.fMsgHandlerMap[kclear_SetMethod] = new TMsgHandlerVoid(function () { _this.clear(); });
        this.fMsgHandlerMap[kwrite_SetMethod] = new TMethodHandler(function (msg) { return _this.write(msg); });
        this.fMsgHandlerMap[kforeground_SetMethod] = new TMsgHandlerVoid(function () { _this.foreground(); });
        this.fMsgHandlerMap[kwrap_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.wrap(n); });
        this.fMsgHandlerMap[ksave_SetMethod] = new TMsgHandlerText(function (s) { _this.savelog(s); });
        this.fMsgHandlerMap[kx_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setXPos(n); });
        this.fMsgHandlerMap[ky_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setYPos(n); });
        this.fMsgHandlerMap[kwidth_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setWidth(n); });
        this.fMsgHandlerMap[kheight_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setHeight(n); });
        this.fMsgHandlerMap[kshow_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.fPosition.setVisible(n); });
        // support the scale message due to the current strategy to handle window resize
        this.fMsgHandlerMap[kscale_GetSetMethod] = new TMethodHandler(function (m) { return eMsgStatus.kProcessedNoChange; });
        this.fGetMsgHandlerMap[kx_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getXPos(); });
        this.fGetMsgHandlerMap[ky_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getYPos(); });
        this.fGetMsgHandlerMap[kwidth_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getWidth(); });
        this.fGetMsgHandlerMap[kheight_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getHeight(); });
        this.fGetMsgHandlerMap[kshow_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.fPosition.getVisible(); });
    };
    IApplLog.prototype.content = function () { return this.fLog; };
    IApplLog.prototype.done = function () { this.fLog = []; this.fClear = false; };
    IApplLog.prototype.cleared = function () { return this.fClear; };
    IApplLog.prototype.clear = function () { this.fClear = true; this.fLog = []; };
    IApplLog.prototype.write = function (msg) {
        var p = msg.params();
        var s = "";
        for (var i = 1; i < p.length; i++)
            s += p[i].toString() + " ";
        this.fLog.push(s);
        return eMsgStatus.kProcessed;
    };
    IApplLog.prototype.foreground = function () { };
    IApplLog.prototype.wrap = function (n) { };
    IApplLog.prototype.savelog = function (file) { };
    return IApplLog;
}(IStaticNode));
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="IObject.ts"/>
///<reference path="Constants.ts"/>
///<reference path="IProxy.ts"/>
///<reference path="IApplStaticNodes.ts"/>
var IAppl = (function (_super) {
    __extends(IAppl, _super);
    function IAppl() {
        var _this = _super.call(this, 'ITL') || this;
        _this.fTypeString = kApplType;
        _this.fReceivedMsgs = 0;
        _this.fRate = kDefaultRate;
        return _this;
    }
    IAppl.prototype.createStaticNodes = function () {
        var log = new IApplLog("log", this);
        this.addChild(log);
    };
    IAppl.prototype.setHandlers = function () {
        var _this = this;
        this.eventAble();
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(function (msg) { return _this.get(msg); });
        this.fMsgHandlerMap[krate_GetSetMethod] = new TMsgHandlerNum(function (n) { _this.setRate(n); });
        this.fGetMsgHandlerMap[krate_GetSetMethod] = new TGetMsgHandlerNum(function () { return _this.getRate(); });
    };
    IAppl.prototype.getAppl = function () { return this; };
    IAppl.prototype.getSet = function () { var msg; return msg; };
    IAppl.prototype.getOSCAddress = function () { return "/ITL"; };
    IAppl.prototype.getRate = function () { return this.fRate; };
    IAppl.prototype.setRate = function (rate) { this.fRate = rate; };
    IAppl.prototype.processMsg = function (address, addressTail, msg) {
        this.fReceivedMsgs++;
        var status = eMsgStatus.kBadAddress;
        var head = address;
        var tail = addressTail;
        /*
                SIMessage msg = IMessage::create (*imsg);
                TAliasesMap::const_iterator i = fAliases.find(imsg->address());
                if (i != fAliases.end()) {
                    msg->setAddress (i->second.first);
                    if (i->second.second.size())
                        msg->setMessage(i->second.second);
                    head = OSCAddress.addressFirst(i->second.first);
                    tail = OSCAddress.addressTail(i->second.first);
                }
        */
        if (tail.length) {
            status = _super.prototype.processMsg.call(this, head, tail, msg);
        }
        else if (this.match(head)) {
            status = this.execute(msg);
            if (status & eMsgStatus.kProcessed)
                this.setState(eObjState.kModified);
        }
        return status;
    };
    return IAppl;
}(IObject));
///<reference path="../model/IObject.ts"/>
var ViewUpdater = (function () {
    function ViewUpdater() {
    }
    ViewUpdater.update = function (obj) {
        if (!obj.getDeleted()) {
            var state = obj.getState();
            if (state & (eObjState.kNewObject + eObjState.kModified)) {
                var views = obj.getViews();
                views.forEach(function (view) { view.updateView(obj); });
            }
            if (state & eObjState.kSubModified) {
                var subnodes = obj.getSubNodes();
                for (var i = 0; i < subnodes.length; i++) {
                    this.update(subnodes[i]);
                }
            }
        }
    };
    return ViewUpdater;
}());
///<reference path="../inscore.ts"/>
///<reference path="../controller/IMessage.ts"/>
///<reference path="IObject.ts"/>
var ModelUpdater = (function () {
    function ModelUpdater(root) {
        this.fRoot = root;
    }
    ModelUpdater.prototype.update = function (stack) {
        var n = stack.length;
        for (var i = 0; i < n; i++) {
            var msg = stack[i];
            INScore.checkStatus(this.fRoot.process(msg), msg);
        }
        /*
                let elt = stack.length;
                if (elt != 0) {
                    for (let i = elt; i > 0; i--) {
                        let msg = stack[i];
                        INScore.checkStatus ( this.fRoot.process(msg), msg)
                    }
                }
        */
    };
    return ModelUpdater;
}());
///<reference path="IMessage.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/documentEvents.ts"/>
///<reference path="../view/ViewUpdater.ts"/>
///<reference path="../model/ModelUpdater.ts"/>
///<reference path="../globals.ts"/>
var IGlue = (function () {
    function IGlue() {
        this.fAppl = new IAppl();
        this.fStack = new Array();
        this.fModelUpdater = new ModelUpdater(this.fAppl);
        this.fCurrentTime = 0;
    }
    IGlue.prototype.getStack = function () { return this.fStack; };
    IGlue.prototype.popStack = function () { return this.fStack.shift(); };
    IGlue.prototype.pushStack = function (msg) { this.fStack.push(msg); };
    IGlue.prototype.initEventHandlers = function () {
        window.addEventListener("resize", inscore_resizeDocument);
    };
    IGlue.prototype.start = function (scene, position) {
        var target = "/ITL/" + scene;
        INScore.postMessage(target, ["new"]);
        INScore.postMessage(target, ["position", position]);
        if (gCreateView)
            this.fTimer = setTimeout(this._timetask(), this.fAppl.getRate());
        window.onbeforeunload = function () { INScore.postMessage("/ITL/log", ["show", 0]); };
    };
    IGlue.prototype.stop = function () {
        INScore.postMessage("/ITL", ["quit"]);
        clearTimeout(this.fTimer);
    };
    IGlue.prototype.getRoot = function () { return this.fAppl; };
    IGlue.prototype.timetask = function () {
        var d = new Date();
        var now = d.getTime();
        if (this.fCurrentTime)
            gINScoreRealRate = now - this.fCurrentTime;
        this.fCurrentTime = now;
        var stack = this.fStack;
        this.fStack = [];
        try {
            this.fModelUpdater.update(stack);
            ViewUpdater.update(this.fAppl);
            IObject.timeTaskCleanup(this.fAppl);
        }
        catch (e) {
            console.log("Warning: " + e);
        }
        this.fTimer = setTimeout(this._timetask(), this.fAppl.getRate());
    };
    IGlue.prototype._timetask = function () {
        var _this = this;
        return function () { return _this.timetask(); };
    };
    ;
    return IGlue;
}());
/* parser generated by jison 0.4.17 */
/*
  Returns a Parser object of the following structure:

  Parser: {
    yy: {}
  }

  Parser.prototype: {
    yy: {},
    trace: function(),
    symbols_: {associative list: name ==> number},
    terminals_: {associative list: number ==> name},
    productions_: [...],
    performAction: function anonymous(yytext, yyleng, yylineno, yy, yystate, $$, _$),
    table: [...],
    defaultActions: {...},
    parseError: function(str, hash),
    parse: function(input),

    lexer: {
        EOF: 1,
        parseError: function(str, hash),
        setInput: function(input),
        input: function(),
        unput: function(str),
        more: function(),
        less: function(n),
        pastInput: function(),
        upcomingInput: function(),
        showPosition: function(),
        test_match: function(regex_match_array, rule_index),
        next: function(),
        lex: function(),
        begin: function(condition),
        popState: function(),
        _currentRules: function(),
        topState: function(),
        pushState: function(condition),

        options: {
            ranges: boolean           (optional: true ==> token location info will include a .range[] member)
            flex: boolean             (optional: true ==> flex-like lexing behaviour where the rules are tested exhaustively to find the longest match)
            backtrack_lexer: boolean  (optional: true ==> lexer regexes are tested in order and for each matching regex the action code is invoked; the lexer terminates the scan when a token is returned by the action code)
        },

        performAction: function(yy, yy_, $avoiding_name_collisions, YY_START),
        rules: [...],
        conditions: {associative list: name ==> set},
    }
  }


  token location info (@$, _$, etc.): {
    first_line: n,
    last_line: n,
    first_column: n,
    last_column: n,
    range: [start_number, end_number]       (where the numbers are indexes into the input string, regular zero-based)
  }


  the parseError function receives a 'hash' object with these members for lexer and parser errors: {
    text:        (matched text)
    token:       (the produced terminal token, if any)
    line:        (yylineno)
  }
  while parser (grammar) errors will also provide these members, i.e. parser errors deliver a superset of attributes: {
    loc:         (yylloc)
    expected:    (string describing the set of expected tokens)
    recoverable: (boolean: TRUE when the parser has a error recovery rule available for this particular error)
  }
*/
var INScoreParser = (function () {
    var o = function (k, v, o, l) { for (o = o || {}, l = k.length; l--; o[k[l]] = v)
        ; return o; }, $V0 = [1, 6], $V1 = [1, 9], $V2 = [1, 10], $V3 = [1, 14], $V4 = [1, 16], $V5 = [1, 17], $V6 = [1, 13], $V7 = [1, 9, 10, 21, 24, 27, 28, 31], $V8 = [6, 16, 19, 20], $V9 = [1, 32], $Va = [1, 26], $Vb = [1, 31], $Vc = [1, 35], $Vd = [1, 36], $Ve = [1, 34], $Vf = [1, 25], $Vg = [1, 27], $Vh = [1, 29], $Vi = [1, 30], $Vj = [2, 23], $Vk = [6, 10, 13, 14, 16, 19, 20, 26, 28, 31, 32, 34, 35, 36, 37, 38], $Vl = [6, 10, 14, 16, 19, 20, 26, 28, 31, 32, 34, 35, 36, 37, 38], $Vm = [1, 58], $Vn = [1, 59], $Vo = [16, 19, 20], $Vp = [21, 24, 27, 28, 31];
    var parser = { trace: function trace() { },
        yy: {},
        symbols_: { "error": 2, "inscore": 3, "expr": 4, "message": 5, "ENDEXPR": 6, "variabledecl": 7, "script": 8, "ENDSCRIPT": 9, "JSCRIPT": 10, "address": 11, "params": 12, "eval": 13, "LEFTPAR": 14, "messagelist": 15, "RIGHTPAR": 16, "variable": 17, "messagelistseparator": 18, "COMMA": 19, "COLON": 20, "OSCADDRESS": 21, "relativeaddress": 22, "urlprefix": 23, "POINT": 24, "hostname": 25, "UINT": 26, "IPNUM": 27, "HOSTNAME": 28, "varname": 29, "identifier": 30, "IDENTIFIER": 31, "REGEXP": 32, "param": 33, "VARSTART": 34, "INT": 35, "FLOAT": 36, "STRING": 37, "EXPRESSION": 38, "EQUAL": 39, "$accept": 0, "$end": 1 },
        terminals_: { 2: "error", 6: "ENDEXPR", 9: "ENDSCRIPT", 10: "JSCRIPT", 13: "eval", 14: "LEFTPAR", 16: "RIGHTPAR", 19: "COMMA", 20: "COLON", 21: "OSCADDRESS", 24: "POINT", 26: "UINT", 27: "IPNUM", 28: "HOSTNAME", 31: "IDENTIFIER", 32: "REGEXP", 34: "VARSTART", 35: "INT", 36: "FLOAT", 37: "STRING", 38: "EXPRESSION", 39: "EQUAL" },
        productions_: [0, [3, 1], [3, 2], [4, 2], [4, 2], [4, 1], [4, 1], [8, 1], [5, 1], [5, 2], [5, 5], [5, 3], [15, 1], [15, 3], [18, 1], [18, 1], [11, 1], [11, 1], [11, 2], [22, 2], [23, 3], [23, 3], [25, 1], [25, 1], [30, 1], [30, 1], [12, 1], [12, 1], [12, 2], [12, 2], [17, 2], [17, 2], [17, 4], [33, 1], [33, 1], [33, 1], [33, 1], [33, 1], [33, 1], [33, 1], [33, 3], [33, 1], [7, 3], [29, 1]],
        performAction: function anonymous(yytext, yyleng, yylineno, yy, yystate /* action[1] */, $$ /* vstack */, _$ /* lstack */) {
            /* this == yyval */
            var $0 = $$.length - 1;
            switch (yystate) {
                case 3:
                    parser.msgs.push($$[$0 - 1]);
                    break;
                case 4:
                case 5:
                    break;
                case 6:
                    debugyacc("expr ENDSCRIPT ");
                    return true;
                    break;
                case 7:
                    if ($$[$0].length)
                        rparse(array2string(context_eval($$[$0])));
                    break;
                case 8:
                    this.$ = new Message($$[$0], new Array());
                    break;
                case 9:
                    this.$ = new Message($$[$0 - 1], $$[$0]);
                    debugyacc(this.$.toString());
                    break;
                case 10:
                    $$[$0 - 1].unshift($$[$0 - 3]);
                    this.$ = new Message($$[$0 - 4], $$[$0 - 1]);
                    break;
                case 11:
                    $$[$0].unshift($$[$0 - 1]);
                    this.$ = new Message($$[$0 - 2], $$[$0]);
                    break;
                case 12:
                    this.$ = new Array();
                    this.$.push($$[$0]);
                    break;
                case 13:
                    $$[$0 - 2].push($$[$0]);
                    this.$ = $$[$0 - 2];
                    break;
                case 16:
                case 17:
                    this.$ = new Address("", 0, $$[$0]);
                    break;
                case 18:
                    $$[$0 - 1].osc = $$[$0];
                    this.$ = $$[$0 - 1];
                    break;
                case 19:
                    this.$ = $$[$0 - 1] + $$[$0];
                    break;
                case 20:
                case 21:
                    this.$ = new Address($$[$0 - 2], parseInt($$[$0]), "");
                    break;
                case 22:
                case 23:
                case 24:
                case 25:
                case 36:
                case 37:
                case 38:
                case 39:
                case 41:
                case 43:
                    this.$ = $$[$0];
                    break;
                case 26:
                case 27:
                    this.$ = [$$[$0]];
                    break;
                case 28:
                    this.$ = $$[$0 - 1].concat($$[$0]);
                    break;
                case 29:
                    $$[$0 - 1].push($$[$0]);
                    this.$ = $$[$0 - 1];
                    break;
                case 30:
                    this.$ = getvar($$[$0]);
                    break;
                case 31:
                    this.$ = "$" + $$[$0];
                    break;
                case 32:
                    this.$ = new Array($$[$0 - 1]);
                    break;
                case 33:
                case 34:
                    this.$ = parseInt($$[$0]);
                    break;
                case 35:
                    this.$ = parseFloat($$[$0]);
                    break;
                case 40:
                    this.$ = $$[$0 - 1];
                    break;
                case 42:
                    debugyacc("variabledecl: " + $$[$0 - 2] + " = " + $$[$0]);
                    parser.vars[$$[$0 - 2]] = $$[$0];
                    break;
            }
        },
        table: [{ 3: 1, 4: 2, 5: 3, 7: 4, 8: 5, 9: $V0, 10: $V1, 11: 7, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 8, 31: $V6 }, { 1: [3], 4: 18, 5: 3, 7: 4, 8: 5, 9: $V0, 10: $V1, 11: 7, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 8, 31: $V6 }, o($V7, [2, 1]), { 6: [1, 19] }, { 6: [1, 20] }, o($V7, [2, 5]), o($V7, [2, 6]), o($V8, [2, 8], { 12: 21, 33: 23, 17: 24, 30: 28, 8: 33, 10: $V1, 13: [1, 22], 14: $V9, 26: $Va, 28: $Vb, 31: $Vc, 32: $Vd, 34: $Ve, 35: $Vf, 36: $Vg, 37: $Vh, 38: $Vi }), { 20: $Vj, 39: [1, 37] }, o([1, 6, 9, 10, 14, 16, 19, 20, 21, 24, 26, 27, 28, 31, 32, 34, 35, 36, 37, 38], [2, 7]), o($Vk, [2, 16]), o($Vk, [2, 17]), { 21: [1, 38] }, o([6, 10, 14, 16, 19, 20, 26, 28, 31, 32, 34, 35, 36, 37, 38, 39], [2, 43]), { 21: [1, 39] }, { 20: [1, 40] }, { 20: [1, 41] }, { 20: [2, 22] }, o($V7, [2, 2]), o($V7, [2, 3]), o($V7, [2, 4]), o($V8, [2, 9], { 30: 28, 8: 33, 17: 42, 33: 43, 10: $V1, 14: $V9, 26: $Va, 28: $Vb, 31: $Vc, 32: $Vd, 34: $Ve, 35: $Vf, 36: $Vg, 37: $Vh, 38: $Vi }), { 14: [1, 44], 17: 45, 34: $Ve }, o($Vl, [2, 26]), o($Vl, [2, 27]), o($Vl, [2, 33]), o($Vl, [2, 34]), o($Vl, [2, 35]), o($Vl, [2, 36]), o($Vl, [2, 37]), o($Vl, [2, 38]), o($Vl, [2, 39]), { 5: 47, 11: 7, 15: 46, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 48, 31: $V6 }, o($Vl, [2, 41]), { 14: [1, 51], 26: [1, 50], 29: 49, 31: $V6 }, o($Vl, [2, 24]), o($Vl, [2, 25]), { 8: 33, 10: $V1, 12: 52, 14: $V9, 17: 24, 26: $Va, 28: $Vb, 30: 28, 31: $Vc, 32: $Vd, 33: 23, 34: $Ve, 35: $Vf, 36: $Vg, 37: $Vh, 38: $Vi }, o($Vk, [2, 18]), o($Vk, [2, 19]), { 26: [1, 53] }, { 26: [1, 54] }, o($Vl, [2, 28]), o($Vl, [2, 29]), { 5: 47, 11: 7, 15: 55, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 48, 31: $V6 }, o($V8, [2, 11]), { 16: [1, 56], 18: 57, 19: $Vm, 20: $Vn }, o($Vo, [2, 12]), { 20: $Vj }, o($Vl, [2, 30]), o($Vl, [2, 31]), { 5: 60, 11: 7, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 48, 31: $V6 }, { 6: [2, 42], 8: 33, 10: $V1, 14: $V9, 17: 42, 26: $Va, 28: $Vb, 30: 28, 31: $Vc, 32: $Vd, 33: 43, 34: $Ve, 35: $Vf, 36: $Vg, 37: $Vh, 38: $Vi }, { 21: [2, 20] }, { 21: [2, 21] }, { 16: [1, 61], 18: 57, 19: $Vm, 20: $Vn }, o($Vl, [2, 40]), { 5: 62, 11: 7, 21: $V2, 22: 11, 23: 12, 24: $V3, 25: 15, 27: $V4, 28: $V5, 29: 48, 31: $V6 }, o($Vp, [2, 14]), o($Vp, [2, 15]), { 16: [1, 63] }, o($V8, [2, 10]), o($Vo, [2, 13]), o($Vl, [2, 32])],
        defaultActions: { 17: [2, 22], 48: [2, 23], 53: [2, 20], 54: [2, 21] },
        parseError: function parseError(str, hash) {
            if (hash.recoverable) {
                this.trace(str);
            }
            else {
                function _parseError(msg, hash) {
                    this.message = msg;
                    this.hash = hash;
                }
                _parseError.prototype = Error;
                throw new _parseError(str, hash);
            }
        },
        parse: function parse(input) {
            var self = this, stack = [0], tstack = [], vstack = [null], lstack = [], table = this.table, yytext = '', yylineno = 0, yyleng = 0, recovering = 0, TERROR = 2, EOF = 1;
            var args = lstack.slice.call(arguments, 1);
            var lexer = Object.create(this.lexer);
            var sharedState = { yy: {} };
            for (var k in this.yy) {
                if (Object.prototype.hasOwnProperty.call(this.yy, k)) {
                    sharedState.yy[k] = this.yy[k];
                }
            }
            lexer.setInput(input, sharedState.yy);
            sharedState.yy.lexer = lexer;
            sharedState.yy.parser = this;
            if (typeof lexer.yylloc == 'undefined') {
                lexer.yylloc = {};
            }
            var yyloc = lexer.yylloc;
            lstack.push(yyloc);
            var ranges = lexer.options && lexer.options.ranges;
            if (typeof sharedState.yy.parseError === 'function') {
                this.parseError = sharedState.yy.parseError;
            }
            else {
                this.parseError = Object.getPrototypeOf(this).parseError;
            }
            function popStack(n) {
                stack.length = stack.length - 2 * n;
                vstack.length = vstack.length - n;
                lstack.length = lstack.length - n;
            }
            _token_stack: var lex = function () {
                var token;
                token = lexer.lex() || EOF;
                if (typeof token !== 'number') {
                    token = self.symbols_[token] || token;
                }
                return token;
            };
            var symbol, preErrorSymbol, state, action, a, r, yyval = {}, p, len, newState, expected;
            while (true) {
                state = stack[stack.length - 1];
                if (this.defaultActions[state]) {
                    action = this.defaultActions[state];
                }
                else {
                    if (symbol === null || typeof symbol == 'undefined') {
                        symbol = lex();
                    }
                    action = table[state] && table[state][symbol];
                }
                if (typeof action === 'undefined' || !action.length || !action[0]) {
                    var errStr = '';
                    expected = [];
                    for (p in table[state]) {
                        if (this.terminals_[p] && p > TERROR) {
                            expected.push('\'' + this.terminals_[p] + '\'');
                        }
                    }
                    if (lexer.showPosition) {
                        errStr = 'Parse error on line ' + (yylineno + 1) + ':\n' + lexer.showPosition() + '\nExpecting ' + expected.join(', ') + ', got \'' + (this.terminals_[symbol] || symbol) + '\'';
                    }
                    else {
                        errStr = 'Parse error on line ' + (yylineno + 1) + ': Unexpected ' + (symbol == EOF ? 'end of input' : '\'' + (this.terminals_[symbol] || symbol) + '\'');
                    }
                    this.parseError(errStr, {
                        text: lexer.match,
                        token: this.terminals_[symbol] || symbol,
                        line: lexer.yylineno,
                        loc: yyloc,
                        expected: expected
                    });
                }
                if (action[0] instanceof Array && action.length > 1) {
                    throw new Error('Parse Error: multiple actions possible at state: ' + state + ', token: ' + symbol);
                }
                switch (action[0]) {
                    case 1:
                        stack.push(symbol);
                        vstack.push(lexer.yytext);
                        lstack.push(lexer.yylloc);
                        stack.push(action[1]);
                        symbol = null;
                        if (!preErrorSymbol) {
                            yyleng = lexer.yyleng;
                            yytext = lexer.yytext;
                            yylineno = lexer.yylineno;
                            yyloc = lexer.yylloc;
                            if (recovering > 0) {
                                recovering--;
                            }
                        }
                        else {
                            symbol = preErrorSymbol;
                            preErrorSymbol = null;
                        }
                        break;
                    case 2:
                        len = this.productions_[action[1]][1];
                        yyval.$ = vstack[vstack.length - len];
                        yyval._$ = {
                            first_line: lstack[lstack.length - (len || 1)].first_line,
                            last_line: lstack[lstack.length - 1].last_line,
                            first_column: lstack[lstack.length - (len || 1)].first_column,
                            last_column: lstack[lstack.length - 1].last_column
                        };
                        if (ranges) {
                            yyval._$.range = [
                                lstack[lstack.length - (len || 1)].range[0],
                                lstack[lstack.length - 1].range[1]
                            ];
                        }
                        r = this.performAction.apply(yyval, [
                            yytext,
                            yyleng,
                            yylineno,
                            sharedState.yy,
                            action[1],
                            vstack,
                            lstack
                        ].concat(args));
                        if (typeof r !== 'undefined') {
                            return r;
                        }
                        if (len) {
                            stack = stack.slice(0, -1 * len * 2);
                            vstack = vstack.slice(0, -1 * len);
                            lstack = lstack.slice(0, -1 * len);
                        }
                        stack.push(this.productions_[action[1]][0]);
                        vstack.push(yyval.$);
                        lstack.push(yyval._$);
                        newState = table[stack[stack.length - 2]][stack[stack.length - 1]];
                        stack.push(newState);
                        break;
                    case 3:
                        return true;
                }
            }
            return true;
        } };
    function debugyacc(str) {
        //		typeof console !== 'undefined' ? console.log(str) : print(str);
    }
    function array2string(a) {
        if (typeof a == "string")
            return a;
        if (typeof a == "object") {
            var out = "";
            for (var i = 0; i < a.length; i++) {
                out += array2string(a[i]) + "\n";
            }
            return out;
        }
        return "";
    }
    function rparse(str) {
        if (!str.length)
            return;
        INScoreParser.parse(str);
    }
    function getvar(v) {
        var vars = parser.vars;
        var out = "";
        for (var key in vars)
            if (key === v)
                return vars[key];
        console.log("Warning! variable $" + v + " is undefined");
        return "$" + v;
    }
    function context_vars() {
        var vars = parser.vars;
        var out = "";
        for (var key in vars)
            out += "var " + key + "=" + vars[key][0].toString() + ";\n";
        return out;
    }
    function context_eval(str) {
        if (__testparser)
            return "";
        var gInscoreParserContext = this;
        this['print'] = function (s) { console.log(s); };
        return gInscoreParserContext.eval(context_vars() + str);
    }
    var __testparser = false;
    if (typeof ITLError === 'undefined') {
        ITLError = [];
        ITLError['write'] = function (s) { console.log(s); };
        function context_eval(str) { return ""; }
    }
    parser.msgs = new Array;
    parser.vars = new Array;
    function Address(ip, port, osc) {
        this.ip = ip; // a string
        this.port = port; // an integer
        this.osc = osc; // a string
        this.toString = function () { return this.ip + (this.port ? (":" + this.port) : "") + this.osc; };
    }
    function Message(addr, params) {
        this.address = addr; // a prototyped array (see below)
        this.params = params; // an array
        this.toString = function () { return this.address.toString() + " " + this.params.toString(); };
    }
    parser.get = (function () {
        var msgs = parser.msgs;
        parser.msgs = [];
        parser.vars = [];
        return msgs;
    });
    parser.parseError = function (str, hash) { ITLError.write(str); };
    /* generated by jison-lex 0.3.4 */
    var lexer = (function () {
        var lexer = ({
            EOF: 1,
            parseError: function parseError(str, hash) {
                if (this.yy.parser) {
                    this.yy.parser.parseError(str, hash);
                }
                else {
                    throw new Error(str);
                }
            },
            // resets the lexer, sets new input
            setInput: function (input, yy) {
                this.yy = yy || this.yy || {};
                this._input = input;
                this._more = this._backtrack = this.done = false;
                this.yylineno = this.yyleng = 0;
                this.yytext = this.matched = this.match = '';
                this.conditionStack = ['INITIAL'];
                this.yylloc = {
                    first_line: 1,
                    first_column: 0,
                    last_line: 1,
                    last_column: 0
                };
                if (this.options.ranges) {
                    this.yylloc.range = [0, 0];
                }
                this.offset = 0;
                return this;
            },
            // consumes and returns one char from the input
            input: function () {
                var ch = this._input[0];
                this.yytext += ch;
                this.yyleng++;
                this.offset++;
                this.match += ch;
                this.matched += ch;
                var lines = ch.match(/(?:\r\n?|\n).*/g);
                if (lines) {
                    this.yylineno++;
                    this.yylloc.last_line++;
                }
                else {
                    this.yylloc.last_column++;
                }
                if (this.options.ranges) {
                    this.yylloc.range[1]++;
                }
                this._input = this._input.slice(1);
                return ch;
            },
            // unshifts one char (or a string) into the input
            unput: function (ch) {
                var len = ch.length;
                var lines = ch.split(/(?:\r\n?|\n)/g);
                this._input = ch + this._input;
                this.yytext = this.yytext.substr(0, this.yytext.length - len);
                //this.yyleng -= len;
                this.offset -= len;
                var oldLines = this.match.split(/(?:\r\n?|\n)/g);
                this.match = this.match.substr(0, this.match.length - 1);
                this.matched = this.matched.substr(0, this.matched.length - 1);
                if (lines.length - 1) {
                    this.yylineno -= lines.length - 1;
                }
                var r = this.yylloc.range;
                this.yylloc = {
                    first_line: this.yylloc.first_line,
                    last_line: this.yylineno + 1,
                    first_column: this.yylloc.first_column,
                    last_column: lines ?
                        (lines.length === oldLines.length ? this.yylloc.first_column : 0)
                            + oldLines[oldLines.length - lines.length].length - lines[0].length :
                        this.yylloc.first_column - len
                };
                if (this.options.ranges) {
                    this.yylloc.range = [r[0], r[0] + this.yyleng - len];
                }
                this.yyleng = this.yytext.length;
                return this;
            },
            // When called from action, caches matched text and appends it on next action
            more: function () {
                this._more = true;
                return this;
            },
            // When called from action, signals the lexer that this rule fails to match the input, so the next matching rule (regex) should be tested instead.
            reject: function () {
                if (this.options.backtrack_lexer) {
                    this._backtrack = true;
                }
                else {
                    return this.parseError('Lexical error on line ' + (this.yylineno + 1) + '. You can only invoke reject() in the lexer when the lexer is of the backtracking persuasion (options.backtrack_lexer = true).\n' + this.showPosition(), {
                        text: "",
                        token: null,
                        line: this.yylineno
                    });
                }
                return this;
            },
            // retain first n characters of the match
            less: function (n) {
                this.unput(this.match.slice(n));
            },
            // displays already matched input, i.e. for error messages
            pastInput: function () {
                var past = this.matched.substr(0, this.matched.length - this.match.length);
                return (past.length > 20 ? '...' : '') + past.substr(-20).replace(/\n/g, "");
            },
            // displays upcoming input, i.e. for error messages
            upcomingInput: function () {
                var next = this.match;
                if (next.length < 20) {
                    next += this._input.substr(0, 20 - next.length);
                }
                return (next.substr(0, 20) + (next.length > 20 ? '...' : '')).replace(/\n/g, "");
            },
            // displays the character position where the lexing error occurred, i.e. for error messages
            showPosition: function () {
                var pre = this.pastInput();
                var c = new Array(pre.length + 1).join("-");
                return pre + this.upcomingInput() + "\n" + c + "^";
            },
            // test the lexed token: return FALSE when not a match, otherwise return token
            test_match: function (match, indexed_rule) {
                var token, lines, backup;
                if (this.options.backtrack_lexer) {
                    // save context
                    backup = {
                        yylineno: this.yylineno,
                        yylloc: {
                            first_line: this.yylloc.first_line,
                            last_line: this.last_line,
                            first_column: this.yylloc.first_column,
                            last_column: this.yylloc.last_column
                        },
                        yytext: this.yytext,
                        match: this.match,
                        matches: this.matches,
                        matched: this.matched,
                        yyleng: this.yyleng,
                        offset: this.offset,
                        _more: this._more,
                        _input: this._input,
                        yy: this.yy,
                        conditionStack: this.conditionStack.slice(0),
                        done: this.done
                    };
                    if (this.options.ranges) {
                        backup.yylloc.range = this.yylloc.range.slice(0);
                    }
                }
                lines = match[0].match(/(?:\r\n?|\n).*/g);
                if (lines) {
                    this.yylineno += lines.length;
                }
                this.yylloc = {
                    first_line: this.yylloc.last_line,
                    last_line: this.yylineno + 1,
                    first_column: this.yylloc.last_column,
                    last_column: lines ?
                        lines[lines.length - 1].length - lines[lines.length - 1].match(/\r?\n?/)[0].length :
                        this.yylloc.last_column + match[0].length
                };
                this.yytext += match[0];
                this.match += match[0];
                this.matches = match;
                this.yyleng = this.yytext.length;
                if (this.options.ranges) {
                    this.yylloc.range = [this.offset, this.offset += this.yyleng];
                }
                this._more = false;
                this._backtrack = false;
                this._input = this._input.slice(match[0].length);
                this.matched += match[0];
                token = this.performAction.call(this, this.yy, this, indexed_rule, this.conditionStack[this.conditionStack.length - 1]);
                if (this.done && this._input) {
                    this.done = false;
                }
                if (token) {
                    return token;
                }
                else if (this._backtrack) {
                    // recover context
                    for (var k in backup) {
                        this[k] = backup[k];
                    }
                    return false; // rule action called reject() implying the next rule should be tested instead.
                }
                return false;
            },
            // return next match in input
            next: function () {
                if (this.done) {
                    return this.EOF;
                }
                if (!this._input) {
                    this.done = true;
                }
                var token, match, tempMatch, index;
                if (!this._more) {
                    this.yytext = '';
                    this.match = '';
                }
                var rules = this._currentRules();
                for (var i = 0; i < rules.length; i++) {
                    tempMatch = this._input.match(this.rules[rules[i]]);
                    if (tempMatch && (!match || tempMatch[0].length > match[0].length)) {
                        match = tempMatch;
                        index = i;
                        if (this.options.backtrack_lexer) {
                            token = this.test_match(tempMatch, rules[i]);
                            if (token !== false) {
                                return token;
                            }
                            else if (this._backtrack) {
                                match = false;
                                continue; // rule action called reject() implying a rule MISmatch.
                            }
                            else {
                                // else: this is a lexer rule which consumes input without producing a token (e.g. whitespace)
                                return false;
                            }
                        }
                        else if (!this.options.flex) {
                            break;
                        }
                    }
                }
                if (match) {
                    token = this.test_match(match, rules[index]);
                    if (token !== false) {
                        return token;
                    }
                    // else: this is a lexer rule which consumes input without producing a token (e.g. whitespace)
                    return false;
                }
                if (this._input === "") {
                    return this.EOF;
                }
                else {
                    return this.parseError('Lexical error on line ' + (this.yylineno + 1) + '. Unrecognized text.\n' + this.showPosition(), {
                        text: "",
                        token: null,
                        line: this.yylineno
                    });
                }
            },
            // return next match that has a token
            lex: function lex() {
                var r = this.next();
                if (r) {
                    return r;
                }
                else {
                    return this.lex();
                }
            },
            // activates a new lexer condition state (pushes the new lexer condition state onto the condition stack)
            begin: function begin(condition) {
                this.conditionStack.push(condition);
            },
            // pop the previously active lexer condition state off the condition stack
            popState: function popState() {
                var n = this.conditionStack.length - 1;
                if (n > 0) {
                    return this.conditionStack.pop();
                }
                else {
                    return this.conditionStack[0];
                }
            },
            // produce the lexer rule set which is active for the currently active lexer condition state
            _currentRules: function _currentRules() {
                if (this.conditionStack.length && this.conditionStack[this.conditionStack.length - 1]) {
                    return this.conditions[this.conditionStack[this.conditionStack.length - 1]].rules;
                }
                else {
                    return this.conditions["INITIAL"].rules;
                }
            },
            // return the currently active lexer condition state; when an index argument is provided it produces the N-th previous condition state, if available
            topState: function topState(n) {
                n = this.conditionStack.length - 1 - Math.abs(n || 0);
                if (n >= 0) {
                    return this.conditionStack[n];
                }
                else {
                    return "INITIAL";
                }
            },
            // alias for begin(condition)
            pushState: function pushState(condition) {
                this.begin(condition);
            },
            // return the number of states currently on the stack
            stateStackSize: function stateStackSize() {
                return this.conditionStack.length;
            },
            options: { "flex": true },
            performAction: function anonymous(yy, yy_, $avoiding_name_collisions, YY_START) {
                function debuglex(str) {
                    //	typeof console !== 'undefined' ? console.log("  lex: " + str) : print("  lex: " + str);
                }
                // ----------------------------------------------------------------------------------------
                // strip escape char '\' from escaped characters
                function unescape(str) {
                    var n = str.length;
                    var outStr = "";
                    // browse the string:  'r' is an index to the current read location
                    //                     'w' is an index to the current write location
                    for (r = 0, w = 0; r < n; r++) {
                        if (str[r] == '\\') {
                            var next = str[r + 1];
                            if ((next != '\'') && (next != '"')) {
                                outStr += str[r]; // output the escape char 
                            }
                        }
                        else
                            outStr += str[r]; // no escape: put the current char at write location 
                    }
                    return outStr;
                }
                var YYSTATE = YY_START;
                switch ($avoiding_name_collisions) {
                    case 0:
                        return 26;
                        break;
                    case 1:
                        return 26;
                        break;
                    case 2:
                        return 35;
                        break;
                    case 3:
                        return 36;
                        break;
                    case 4:
                        return 36;
                        break;
                    case 5:
                        return 36;
                        break;
                    case 6:
                        debuglex("ENDSCRIPT : " + yy_.yytext);
                        return 9;
                        break;
                    case 7:
                        debuglex("IDENTIFIER: " + yy_.yytext);
                        return 31;
                        break;
                    case 8:
                        debuglex("HOSTNAME: " + yy_.yytext);
                        return 28;
                        break;
                    case 9:
                        debuglex("IPNUM: " + yy_.yytext);
                        return 27;
                        break;
                    case 10:
                        return 'EVAL';
                        break;
                    case 11:
                        this.begin('DQSTR');
                        break;
                    case 12:
                        debuglex("STRING: " + unescape(yy_.yytext));
                        return 37;
                        break;
                    case 13:
                        this.popState();
                        break;
                    case 14:
                        this.begin('QSTR');
                        break;
                    case 15:
                        debuglex("STRING: " + unescape(yy_.yytext));
                        return 37;
                        break;
                    case 16:
                        this.popState();
                        break;
                    case 17:
                        debuglex("FILE STRING: " + yy_.yytext);
                        return 37;
                        break;
                    case 18:
                        this.begin('JSECTION');
                        break;
                    case 19:
                        this.popState();
                        break;
                    case 20:
                        debuglex("JAVASCRIPT: " + yy_.yytext);
                        return 10;
                        break;
                    case 21:
                        debuglex("REGEXP: " + yy_.yytext);
                        return 32;
                        break;
                    case 22:
                        debuglex("REGEXP: " + yy_.yytext);
                        return 32;
                        break;
                    case 23:
                        debuglex("REGEXP: " + yy_.yytext);
                        return 32;
                        break;
                    case 24:
                        this.more();
                        this.begin('EXPRSECTION');
                        break;
                    case 25:
                        this.more();
                        this.popState();
                        if (this.topState() == 'INITIAL') {
                            debuglex("EXPRESSION " + yy_.yytext);
                            return 38;
                        }
                        break;
                    case 26:
                        this.more();
                        break;
                    case 27:
                        this.begin('EXPRSECTION');
                        this.more();
                        break;
                    case 28:
                        this.more();
                        this.begin('OSCSECTION');
                        break;
                    case 29:
                        this.more();
                        break;
                    case 30:
                        this.more();
                        break;
                    case 31:
                        this.more();
                        break;
                    case 32:
                        this.more();
                        break;
                    case 33:
                        this.more();
                        break;
                    case 34:
                        debuglex("OSCADDRESS " + yy_.yytext);
                        this.popState();
                        yy_.yytext = yy_.yytext.substring(0, yy_.yytext.length - 1);
                        return 21;
                        break;
                    case 35:
                        return 39;
                        break;
                    case 36:
                        return 6; /* end of expression */
                        break;
                    case 37:
                        return 34;
                        break;
                    case 38:
                        return 20;
                        break;
                    case 39:
                        return 19;
                        break;
                    case 40:
                        return 24;
                        break;
                    case 41:
                        return 14;
                        break;
                    case 42:
                        return 16;
                        break;
                    case 43:
                        debuglex("COMMENTLINE: " + yy_.yytext);
                        break;
                    case 44:
                        debuglex("COMMENTLINE: " + yy_.yytext);
                        break;
                    case 45:
                        ;
                        break;
                    case 46:
                        debuglex("BEGIN NESTED COMMENT");
                        this.begin('COMMENT');
                        break;
                    case 47:
                        debuglex("END COMMENT");
                        this.popState();
                        break;
                    case 48:
                        debuglex("BEGIN COMMENT");
                        this.begin('COMMENT');
                        break;
                    case 49:
                        ; /* eat up space */
                        break;
                    case 50:
                        ; /* yy_.yylloc->first_column=0; ignore */
                        break;
                    case 51:
                        return 9;
                        break;
                    case 52:
                        debuglex("ERR: " + yy_.yytext);
                        return 'ERR';
                        break;
                    case 53:
                        console.log(yy_.yytext);
                        break;
                }
            },
            rules: [/^(?:([0-9])+)/, /^(?:\+([0-9])+)/, /^(?:-([0-9])+)/, /^(?:[+-]?([0-9])+\.([0-9])*)/, /^(?:[+-]?([0-9])+\.([0-9])+e[-+]?([0-9])+)/, /^(?:[+-]?([0-9])+e[-+]?([0-9])+)/, /^(?:__END__)/, /^(?:([_a-zA-Z])([_a-zA-Z0-9])*)/, /^(?:(([-a-zA-Z0-9])(([-a-zA-Z0-9])*|\.))+)/, /^(?:([0-9])+\.([0-9])+\.([0-9])+\.([0-9])+)/, /^(?:eval)/, /^(?:")/, /^(?:(\\"|[^"])*)/, /^(?:")/, /^(?:')/, /^(?:(\\'|[^'])*)/, /^(?:')/, /^(?:(\/|(\.\.?\/)*)(([^ \t\\/?:*><|"'!#;=])+\/?)+\.[a-zA-Z]+)/, /^(?:<\?([ \t])*javascript)/, /^(?:\?>)/, /^(?:(([\x0a\x0d])|\?[^>]|[^?])*)/, /^(?:([-_a-zA-Z0-9?+*])+)/, /^(?:([-_a-zA-Z0-9?+*])*\[([-_a-zA-Z0-9^])+\]([-_a-zA-Z0-9?+*])*)/, /^(?:([-_a-zA-Z0-9?+*])*\{[_a-zA-Z0-9,]+\}([-_a-zA-Z0-9?+*])*)/, /^(?:\()/, /^(?:\))/, /^(?:[^()]*)/, /^(?:expr([ \t])*\()/, /^(?:\/)/, /^(?:\/)/, /^(?:\$?([_a-zA-Z])([_a-zA-Z0-9])*)/, /^(?:([-_a-zA-Z0-9?+*])+)/, /^(?:([-_a-zA-Z0-9?+*])*\[([-_a-zA-Z0-9^])+\]([-_a-zA-Z0-9?+*])*)/, /^(?:([-_a-zA-Z0-9?+*])*\{[_a-zA-Z0-9,]+\}([-_a-zA-Z0-9?+*])*)/, /^(?:([ \t])|([\x0a\x0d]))/, /^(?:=)/, /^(?:;)/, /^(?:\$)/, /^(?::)/, /^(?:,)/, /^(?:\.)/, /^(?:\()/, /^(?:\))/, /^(?:#.*)/, /^(?:!.*)/, /^(?:.|([\x0a\x0d])*)/, /^(?:\(\*)/, /^(?:\*\))/, /^(?:\(\*)/, /^(?:([ \t])+)/, /^(?:([\x0a\x0d]))/, /^(?:$)/, /^(?:.)/, /^(?:.)/],
            conditions: { "OSCSECTION": { "rules": [29, 30, 31, 32, 33, 34], "inclusive": false }, "EXPRSECTION": { "rules": [24, 25, 26], "inclusive": false }, "JSECTION": { "rules": [19, 20], "inclusive": false }, "COMMENT": { "rules": [45, 46, 47], "inclusive": false }, "QSTR": { "rules": [15, 16], "inclusive": false }, "DQSTR": { "rules": [12, 13], "inclusive": false }, "INITIAL": { "rules": [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 17, 18, 21, 22, 23, 27, 28, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 48, 49, 50, 51, 52, 53], "inclusive": true } }
        });
        return lexer;
    })();
    parser.lexer = lexer;
    function Parser() {
        this.yy = {};
    }
    Parser.prototype = parser;
    parser.Parser = Parser;
    return new Parser;
})();
if (typeof require !== 'undefined' && typeof exports !== 'undefined') {
    exports.parser = INScoreParser;
    exports.Parser = INScoreParser.Parser;
    exports.parse = function () { return INScoreParser.parse.apply(INScoreParser, arguments); };
    exports.main = function commonjsMain(args) {
        if (!args[1]) {
            console.log('Usage: ' + args[0] + ' FILE');
            process.exit(1);
        }
        var source = require('fs').readFileSync(require('path').normalize(args[1]), "utf8");
        return exports.parser.parse(source);
    };
    if (typeof module !== 'undefined' && require.main === module) {
        exports.main(process.argv.slice(1));
    }
}
