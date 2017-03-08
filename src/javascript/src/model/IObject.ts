
///<reference path="../controller/TGetMessageHandlers.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="../externals/fraction.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/ITLOut.ts"/>
///<reference path="../view/VObjectView.ts"/>

///<reference path="Constants.ts"/>
///<reference path="Methods.ts"/>
///<reference path="IColor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="IBrushStyle.ts"/>
///<reference path="IEffect.ts"/>
///<reference path="IPenControl.ts"/>

class TMsgHandler<T> 			{ [index: string]: T; }
class TGetMsgHandler<T> 		{ [index: string]: T; }
interface Tree<T>				{ getSubNodes() : Array<Tree<T> >; } 
interface TApplyFunction<T> 	{ (arg: T) : void; }
interface TreeApply<T>			{ apply (f: TApplyFunction<T>, t: Tree<T>) : void; } 
interface IObjectTreeApply extends TreeApply<IObject> {}


abstract class IObject implements Tree<IObject> {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fTypeString:	string;
    protected fName: 		string;
    protected fState: 		objState;
    protected fNewData: 	boolean;
    protected fDelete: 		boolean;
    protected fLock: 		boolean;
    protected fParent: 		IObject;
    protected fObjectView:	VObjectView;
    protected fSubNodes: Array<IObject> = new Array;
    
    protected fMsgHandlerMap : 		TMsgHandler<TSetHandler>; 
    protected fGetMsgHandlerMap : 	TGetMsgHandler<TGetHandler>; 
    
    fPosition: 	 IPosition;
    fDate: 		 IDate;
    fColor: 	 IColor;
    fPenControl: IPenControl;
    fBrushStyle: IBrushStyle;
    fEffect:     IEffect;

// CONSTRUCTOR
//--------------------------------------------------------------       
    constructor(name: string, parent?: IObject) {
        this.fName = name;
        this.fTypeString = 'obj'; 
        
        this.fDelete = false;
        this.fLock = false;
        this.fState = objState.kNewObject;
        this.fNewData = true;        
        this.fParent = parent; 

        this.fPosition = new IPosition;
        this.fDate = new IDate;
		this.fColor = new IColor([0,0,0]);
        
        this.fPenControl = new IPenControl(kObjType);
        this.fBrushStyle = new IBrushStyle();
        this.fEffect     = new IEffect();

        this.fMsgHandlerMap 	= new TMsgHandler<TSetHandler>();
		this.fGetMsgHandlerMap	= new TGetMsgHandler<TGetHandler>();
        this.setHandlers();
        this.createStaticNodes();
    }
    
    createStaticNodes() : void {}

// HANDLERS
//--------------------------------------------------------------  
    setHandlers(): void {
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler(this._set());
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(this._get());
        this.fMsgHandlerMap[ksave_SetMethod]= new TMethodHandler(this._save());
        this.fMsgHandlerMap[kdel_SetMethod] = new TMsgHandlerVoid(this._del());

 	    this.colorAble();
	    this.positionAble();
	    this.timeAble();
        this.penControlAble();
        this.effectAble();
    }

    // intended for ILine : the target is always the pen color
    getColorTarget(): IColor 				{ return this.fColor; };
    
    colorAble(): void {
        let target = this.getColorTarget();
        this.fMsgHandlerMap[kcolor_GetSetMethod] 		= new TMsgHandlerColor(target._setRGB());
        this.fMsgHandlerMap[khsb_SetMethod] 			= new TMsgHandlerColor(target._setHSB());
        this.fMsgHandlerMap[kred_GetSetMethod] 			= new TMsgHandlerNum(target._setR());
	    this.fMsgHandlerMap[kgreen_GetSetMethod] 		= new TMsgHandlerNum(target._setG());
	    this.fMsgHandlerMap[kblue_GetSetMethod]			= new TMsgHandlerNum(target._setB());
        this.fMsgHandlerMap[kalpha_GetSetMethod] 		= new TMsgHandlerNum(target._setA());
	    this.fMsgHandlerMap[khue_GetSetMethod] 			= new TMsgHandlerNum(target._setH());
	    this.fMsgHandlerMap[ksaturation_GetSetMethod]	= new TMsgHandlerNum(target._setS());
        this.fMsgHandlerMap[kbrightness_GetSetMethod]	= new TMsgHandlerNum(target._setV());

        this.fMsgHandlerMap[kdred_SetMethod] 			= new TMsgHandlerNum(target._dR());
	    this.fMsgHandlerMap[kdgreen_SetMethod] 			= new TMsgHandlerNum(target._dG());
	    this.fMsgHandlerMap[kdblue_SetMethod]			= new TMsgHandlerNum(target._dB());
        this.fMsgHandlerMap[kdalpha_SetMethod] 			= new TMsgHandlerNum(target._dA());
	    this.fMsgHandlerMap[kdhue_SetMethod] 			= new TMsgHandlerNum(target._dH());
	    this.fMsgHandlerMap[kdsaturation_SetMethod]		= new TMsgHandlerNum(target._dS());
        this.fMsgHandlerMap[kdbrightness_SetMethod]		= new TMsgHandlerNum(target._dV());

        this.fGetMsgHandlerMap[kcolor_GetSetMethod] 	= new TGetMsgHandlerArray(target._getRGB());
        this.fGetMsgHandlerMap[khsb_SetMethod] 			= new TGetMsgHandlerArray(target._getHSB());
        this.fGetMsgHandlerMap[kred_GetSetMethod] 		= new TGetMsgHandlerNum(target._getR());
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] 	= new TGetMsgHandlerNum(target._getG());
	    this.fGetMsgHandlerMap[kblue_GetSetMethod] 		= new TGetMsgHandlerNum(target._getB());
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] 	= new TGetMsgHandlerNum(target._getA());
        this.fGetMsgHandlerMap[khue_GetSetMethod] 		= new TGetMsgHandlerNum(target._getH());
	    this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetMsgHandlerNum(target._getS());
	    this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetMsgHandlerNum(target._getV());    
    }
    
    positionAble() {
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setXPos());
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setYPos());
        this.fMsgHandlerMap[kxorigin_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setXOrigin());
        this.fMsgHandlerMap[kyorigin_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setYOrigin());
        this.fMsgHandlerMap[kz_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setZOrder());
        this.fMsgHandlerMap[kangle_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setRotateZ());
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMsgHandlerNum(this._setScale());
//        this.fMsgHandlerMap[kshear_GetSetMethod] 	= new TSetMethodMsgHandler(this.fPosition._setShear());
        this.fMsgHandlerMap[krotatex_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setRotateX()); 
        this.fMsgHandlerMap[krotatey_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setRotateY()); 
        this.fMsgHandlerMap[krotatez_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setRotateZ()); 

        this.fMsgHandlerMap[kdx_SetMethod] 			= new TMsgHandlerNum(this.fPosition._addXPos());
        this.fMsgHandlerMap[kdy_SetMethod] 			= new TMsgHandlerNum(this.fPosition._addYPos());
        this.fMsgHandlerMap[kdxorigin_SetMethod] 	= new TMsgHandlerNum(this.fPosition._addXOrigin());
        this.fMsgHandlerMap[kdyorigin_SetMethod] 	= new TMsgHandlerNum(this.fPosition._addYOrigin());
        this.fMsgHandlerMap[kdz_SetMethod] 			= new TMsgHandlerNum(this.fPosition._addZOrder());
        this.fMsgHandlerMap[kdangle_SetMethod] 		= new TMsgHandlerNum(this.fPosition._addAngle());
        this.fMsgHandlerMap[kdscale_SetMethod] 		= new TMsgHandlerNum(this.fPosition._multScale());
        this.fMsgHandlerMap[kdrotatex_SetMethod]    = new TMsgHandlerNum(this.fPosition._addXAngle());
        this.fMsgHandlerMap[kdrotatey_SetMethod]    = new TMsgHandlerNum(this.fPosition._addYAngle());
        this.fMsgHandlerMap[kdrotatez_SetMethod]    = new TMsgHandlerNum(this.fPosition._addAngle());
        this.fMsgHandlerMap[kshow_GetSetMethod]		= new TMsgHandlerNum(this.fPosition._setVisible());

        this.fGetMsgHandlerMap[kx_GetSetMethod]			= new TGetMsgHandlerNum(this.fPosition._getXPos());
        this.fGetMsgHandlerMap[ky_GetSetMethod]			= new TGetMsgHandlerNum(this.fPosition._getYPos());
        this.fGetMsgHandlerMap[kxorigin_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getXOrigin());
        this.fGetMsgHandlerMap[kyorigin_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getYOrigin());
        this.fGetMsgHandlerMap[kz_GetSetMethod]			= new TGetMsgHandlerNum(this.fPosition._getZOrder());
        this.fGetMsgHandlerMap[kangle_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getRotateZ());
        this.fGetMsgHandlerMap[kscale_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getScale());
        this.fGetMsgHandlerMap[kshow_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getVisible());
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getWidth());
        this.fGetMsgHandlerMap[kheight_GetSetMethod] 	= new TGetMsgHandlerNum(this.fPosition._getHeight());
        this.fGetMsgHandlerMap[kshear_GetSetMethod]	 	= new TGetMsgHandlerArray(this.fPosition._getShear());
        this.fGetMsgHandlerMap[krotatex_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getRotateX());
        this.fGetMsgHandlerMap[krotatey_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getRotateY());
        this.fGetMsgHandlerMap[krotatez_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getRotateZ());
    }
    
    timeAble() {
        this.fMsgHandlerMap[kdate_GetSetMethod] 	= new TMsgHandlerTime(this.fDate._setDate());
        this.fMsgHandlerMap[kduration_GetSetMethod]	= new TMsgHandlerTime(this.fDate._setDuration);
        this.fMsgHandlerMap[kddate_SetMethod] 		= new TMsgHandlerTime(this.fDate._addDate());
        this.fMsgHandlerMap[kdduration_SetMethod] 	= new TMsgHandlerTime(this.fDate._addDuration());        
        this.fMsgHandlerMap[kclock_SetMethod] 		= new TMsgHandlerVoid(this.fDate._clock());
        this.fMsgHandlerMap[kdurClock_SetMethod] 	= new TMsgHandlerVoid(this.fDate._durclock());

        this.fGetMsgHandlerMap[kdate_GetSetMethod] 		= new TGetMsgHandlerTime(this.fDate._getDate());
        this.fGetMsgHandlerMap[kduration_GetSetMethod] 	= new TGetMsgHandlerTime(this.fDate._getDuration());
    }

    penControlAble() {
        this.fMsgHandlerMap[kpenWidth_GetSetMethod]     = new TMsgHandlerNum(this.fPenControl._setPenWidth());
        this.fMsgHandlerMap[kpenColor_GetSetMethod] 	= new TMsgHandlerColor(this.fPenControl._setPenColor());
        this.fMsgHandlerMap[kpenStyle_GetSetMethod] 	= new TMsgHandlerText(this.fPenControl._setPenStyle());
        this.fMsgHandlerMap[kpenAlpha_GetSetMethod] 	= new TMsgHandlerNum(this.fPenControl._setPenAlpha());

        this.fGetMsgHandlerMap[kpenWidth_GetSetMethod] 	= new TGetMsgHandlerNum(this.fPenControl._getPenWidth());
        this.fGetMsgHandlerMap[kpenColor_GetSetMethod] 	= new TGetMsgHandlerArray(this.fPenControl._getPenColor());
        this.fGetMsgHandlerMap[kpenStyle_GetSetMethod] 	= new TGetMsgHandlerText(this.fPenControl._getPenStyle());
        this.fGetMsgHandlerMap[kpenAlpha_GetSetMethod]  = new TGetMsgHandlerNum(this.fPenControl._getPenAlpha());
    }
    
    brushAble() {
        this.fGetMsgHandlerMap[kbrushStyle_GetSetMethod] = new TGetMsgHandlerText(this.fBrushStyle._getBrushStyle());
        this.fMsgHandlerMap[kbrushStyle_GetSetMethod]    = new TMsgHandlerText(this.fBrushStyle._setBrushStyle());
	}

	effectAble(){
        this.fGetMsgHandlerMap[keffect_GetSetMethod]     = new TGetMsgHandlerArray(this.fEffect._getEffect());
        this.fMsgHandlerMap[keffect_GetSetMethod]        = new TMsgHandlerAnyArray(this.fEffect._setEffect());
    }
    
//--------------------------------------------------------------  
// Special position handlers
// size change requires the modification state to be 
// recursively propagated to all subnodes
//--------------------------------------------------------------  
	setWidth (width: number) : void { this.fPosition.setWidth( width ); this.posPropagate(); }
	setHeight(height:number): void 	{ this.fPosition.setHeight( height); this.posPropagate(); }
    setScale (scale:number): void 	{ this.fPosition.setScale( scale); this.posPropagate(); }
    _setWidth()	: SetNumMethod 		{ return (n) => this.setWidth(n); };
    _setHeight(): SetNumMethod 		{ return (n) => this.setHeight(n); };
    _setScale(): SetNumMethod 		{ return (n) => this.setScale(n); };
	posPropagate() : void 			{ let a = new IObjectTreeApply(); a.applyPosModified(this); }
	posModified() : void 			{ this.fPosition.modify(); this.addState (objState.kModified + objState.kSubModified); }
   
    
// METHODS
//--------------------------------------------------------------  
    addChild(obj: IObject): void { 
        this.fSubNodes.push(obj);
        this.setState(objState.kSubModified);
    } 
    
    setParent(parent: IObject): void { this.fParent = parent; }    
    getParent(): IObject 			{ return this.fParent; }    
    getSubNodes(): Array<IObject> 	{ return this.fSubNodes }
    getSubNodesCount(): number 		{ return this.fSubNodes.length; }
    getAppl() : IObject				{ return this.fParent.getAppl(); }
    getScene(): IObject 			{ return this.fParent.getScene(); }
	// get the object scale recursively
    getRScale(): number 			{ return this.fPosition.getScale() * this.fParent.getRScale(); }
	// get the object size as scale recursively - takes account of the smallest dimension
    getRSizeAsScale(): number 		{ 
    	let size = Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()); 
    	return size / 2 * this.fParent.getRSizeAsScale(); 
    }

    getPosition(): {x: number, y: number } 		     { return { x: this.fPosition.getXPos(), y: this.fPosition.getYPos() }; }
    getSize():     {w: number, h: number } 			 { return { w: this.fPosition.getWidth(), h: this.fPosition.getHeight() }; }
    getRotate():   {x: number, y: number, z: number} { return { x: this.fPosition.getRotateX(), y: this.fPosition.getRotateY(), z: this.fPosition.getRotateZ() }; }

    toString(): string 				{ 
    	let n=this.fSubNodes.length; 
    	let substr = ""; 
    	if (n) substr= " [" + this.fSubNodes + "] "; 
    	return this.fName + substr; 
    }
   
    //-----------------------------    
    getName(): string 				{ return this.fName; }
    getTypeString(): string 		{ return this.fTypeString; }        
    
    
    //-----------------------------
    match(address: string): boolean
    {
        let re = new OSCRegexp(address);
        return re.match (this.fName);
    }

    find(expr: string): Array<IObject> {
        if (!Tools.regexp(expr)) {
            return this.exactfind(expr);
        }
        else {
        	let re = new OSCRegexp(expr);
	        let out: Array<IObject> = [];
            let n 	 = this.getSubNodesCount();
            for (let i = 0; i < n; i++) {
                let elt = this.fSubNodes[i];
                if (!elt.getDeleted() && re.match(elt.fName)) { out.push(elt); }       
            }
            return out;
        }
    }
    
    //-----------------------------
    exactfind(name:string): Array<IObject> {
        let out: Array<IObject> = [];
        let n: number = this.fSubNodes.length;
        for (let i = 0; i < n; i++) {
            let elt = this.fSubNodes[i];
            if ((!elt.getDeleted()) && (elt.fName == name))
                out.push(this.fSubNodes[i]);
        }
        return out;
    }
    
    //-----------------------------    
    newData     (state: boolean): void  { this.fNewData = state; /*triggerEvent(kNewData, true)*/; }
    isNewData   (): boolean             { return this.fNewData; }
    
    setState (s: objState): void 	{ this.fState = s; }
    addState (s: objState): void 	{ this.fState |= s; }
    getState(): objState 			{ return this.fState; }
    
    getPos(): IPosition 		{ return this.fPosition; }
    getColor(): IColor 			{ return this.fColor; }
    getOSCAddress(): string 	{ return this.fParent.getOSCAddress() + "/" + this.fName; }

    transferAttributes(dest: IObject): IObject {
        dest.fPosition.set	( this.fPosition );
        dest.fColor.set 	( this.fColor );
        dest.fDate.set 		( this.fDate );

        //dest.fPosition.setPenWidth(getPenWidth());
        //dest.fPosition.setPenColor(getPenColor());
        //dest.fPosition.setPenStyle(getPenStyle());
        return dest;
    }   

    // View
    //-----------------------------    
    setView(view: VObjectView): void 	{ this.fObjectView = view }
    getView(): VObjectView 				{ return this.fObjectView }
    
    //-----------------------------
    execute (msg: IMessage): number {
    	if (msg.size() == 0) return msgStatus.kBadParameters;
    	let method = msg.message();
    	if (method.correct) {
       		let handler = this.messageHandler(method.value);
        	if (handler) { return handler.handle(msg) }

	        //handler = this.messageHandler(msg.message(), true);
	        //if (handler) return ;

	        //handler = this.messageHandler("*");
	        //if (handler) return ;
	        //return msgStatus.kBadParameters;		
    	}
    	else {			// sig handler 
    	}
		return msgStatus.kBadParameters;
    }
    
    //-----------------------------
    messageHandler(msg: string, match?: boolean): TSetHandler {
        let handler: TSetHandler;
        if (!match) {
            return this.fMsgHandlerMap[msg]; 
        }
        
        /*else {
            msgMatchPredicat p(msg);
            map<string, SMsgHandler>::const_iterator h = find_if(this.fMsgHandlerMap.begin(), this.fMsgHandlerMap.end(), p);
            if (h != this.fMsgHandlerMap.end()) handler = h.second;
        }*/       
        return handler;
    }
    
// MESSAGES PROCESSING
//--------------------------------------------------------------     
    process (msg: IMessage): number {
		let beg: string = OSCAddress.addressFirst(msg.address());
		let tail: string = OSCAddress.addressTail(msg.address());
		return this.processMsg(beg, tail, msg);
    }

    processMsg (address: string, addressTail: string , msg: IMessage): msgStatus {

        let result: number = msgStatus.kBadAddress;
        if (this.match(address)) {
            let beg: string = OSCAddress.addressFirst(addressTail);	
            let tail: string = OSCAddress.addressTail(addressTail);
                
            if (tail.length) {
                let n: number = this.fSubNodes.length;
                for (let i: number = 0; i < n; i++) { result |= this.fSubNodes[i].processMsg (beg, tail, msg); }
            }

            else {										
                let targets = this.find (beg);
                let n = targets.length;
                if (n) {	
                    for (let i = 0; i < n; i++) {
                        let target = targets[i];
                        result |= target.execute(msg);	
                        if (result & msgStatus.kProcessed) { target.addState(objState.kModified); }
                    }
                }               
                else if (Tools.regexp(beg)) { result = msgStatus.kProcessedNoChange; }                    
                else { result = this.proxy_create (msg, beg, this).status; }
            }
        }
            
        if (result & msgStatus.kProcessed + objState.kSubModified) { this.addState(objState.kSubModified); }
    	return result;     
    }
    
    //-------------------------------------------------------------
    // the basic 'set' handler
    //-------------------------------------------------------------
    set(msg: IMessage): msgStatus	{
        let type = msg.paramStr(1);
        if (!type.correct) { return msgStatus.kBadParameters; }

        if (type.value != this.getTypeString()) {
//debugger;
			let out = this.proxy_create (msg, this.fName, this.getParent());
            if (out.status & msgStatus.kProcessed) {
	            // todo: transfer this attributes to new object
	            this.transferAttributes (out.obj);
//				this.fParent.cleanupSync();
            	this.del();
                return out.status;		
            }
            
            return msgStatus.kProcessedNoChange;
        }
        return msgStatus.kBadParameters;
    }
    _set(): SetMsgMethod	{ return (m) => this.set(m); }
    
     //-------------------------------------------------------------
    // the basic 'get' handler
    //-------------------------------------------------------------
    get(msg: IMessage): msgStatus {
        let n = msg.size();
        if ( n == 1 ) {				// get without param should give a 'set' msg
			let outmsg = this.getSet();
			if (outmsg) ITLOut.write (outmsg.toString() + ";");
        }
        else for (let i=1; i< n; i++) {
        	let attribute = msg.paramStr(i);
        	if (attribute.correct) {
        		let outmsg = this.get1AttributeMsg (attribute.value);
        		if (outmsg) { 
        			ITLOut.write (outmsg.toString());
        		}
        	}
        	else {
        		ITLError.badParameter (msg.toString(), msg.param(i));
         		return msgStatus.kBadParameters;
       		}        	
        }
        return msgStatus.kProcessedNoChange;
    }
    _get(): SetMsgMethod	{ return (m) => this.get(m); }
    
     //-------------------------------------------------------------
    // the 'save' handler
    //-------------------------------------------------------------
    save(msg: IMessage): msgStatus {
    	let out = this.getSetRecurse();
	    for (let i=0; i < out.length; i++)
        	ITLOut.write (out[i].toString() + ";");
    	return msgStatus.kProcessedNoChange;
    }
    _save(): SetMsgMethod	{ return (m) => this.save(m); }

    //-------------------------------------------------------------
    // the specific 'get' methods - must be implemented by inherited objects
    //-------------------------------------------------------------
    abstract getSet(): IMessage;
      
    //-------------------------------------------------------------
    // get 1 message for 1 attribute
    get1AttributeMsg(attribute: string): IMessage {
        let outmsg : IMessage;
        let h = this.fGetMsgHandlerMap[attribute];
        if (h) { 
        	outmsg = new IMessage (this.getOSCAddress(), attribute);
        	h.fill (outmsg);
        }
        return outmsg;
    }

    //-------------------------------------------------------------
    // get a message for all attributes
    getAttributesMsg(): Array<IMessage> {
    	let out = new Array<IMessage>();
		for (let key in this.fMsgHandlerMap) {
			let msg = this.get1AttributeMsg(key);
	    	if (msg) out.push (msg);
		}
		return out;
    }

    //-------------------------------------------------------------
    // get objects state messages recursively
    getSetRecurse(): Array<IMessage> {
    	let out = new Array<IMessage>();
    	let msg =  this.getSet ();			// get the 'set' msg first
    	if (msg) out.push (msg);			// and push to the output list
    	let p = this.getAttributesMsg();	// next all the messages for the object attributes
	    for (let i=0; i < p.length; i++)
		    out.push (p[i]);
    	
        let n 	 = this.getSubNodesCount();	
		for (let i = 0; i < n; i++) {		// and propagate to the subnodes
	    	let subout = this.fSubNodes[i].getSetRecurse ();
	    	for (let i=0; i < subout.length; i++)
		    	out.push (subout[i]);
		}
		return out;
    }
 
    //-----------------------------    
    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: msgStatus, obj?: IObject } 
    				{ return this.getAppl().proxy_create(msg, name, parent); }                
    
    //-----------------------------    
    getDeleted(): boolean 	{ return this.fDelete; }
    del(): void {
    	this.fDelete = true;
        if (this.getView()) this.getView().remove();
        let array = this.fParent.getSubNodes();
        array.splice(array.indexOf(this), 1);
    }
    _del() : SetVoidMethod { return () => this.del(); }

	//-----------------------------    
	cleanup() : void { 
		this.fPosition.cleanup(); 
		this.fDate.cleanup(); 
		this.fColor.cleanup();
		this.fPenControl.cleanup();
		this.setState(objState.kClean);
        this.fBrushStyle.cleanup();
        this.fEffect.cleanup();
    }

	//-----------------------------    
	static timeTaskCleanup(obj: IObject) : void { 
		let state = obj.getState();
		if (state & (objState.kNewObject + objState.kModified)) obj.cleanup();		
		if (state & objState.kSubModified) {
			obj.setState (objState.kClean);
			let nodes = obj.getSubNodes();
			for (let i=0; i<nodes.length; i++) {
				IObject.timeTaskCleanup(nodes[i]);
			}
		}
	}
}

class IObjectTreeApply implements TreeApply<IObject> {
	apply (f: TApplyFunction<IObject>, t: IObject) {
		f (t);
		let sub = t.getSubNodes();
		for (let i=0; i<sub.length; i++)
			this.apply (f, sub[i]);
	}
	cleanup (t: IObject) : void 			{ t.cleanup(); }
	applyCleanup (t: IObject): void 		{ this.apply ((o) => this.cleanup (o), t); }
	posModified (t: IObject) : void 		{ t.posModified(); }
	applyPosModified (t: IObject): void 	{ this.apply ((o) => this.posModified (o), t); }
}
