
///<reference path="../externals/fraction/fraction.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/ITLOut.ts"/>
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="../controller/TGetMessageHandlers.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../view/VObjectView.ts"/>

///<reference path="Methods.ts"/>
///<reference path="Icolor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>


class TMsgHandler<T> 	{ [index: string]: T; }
class TGetMsgHandler<T> { [index: string]: T; }


abstract class IObject {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fPosition: 	IPosition;
    protected fDate: 		IDate;
    protected fColor: 		IColor;
    
    protected fTypeString:	string;
    protected fName: 		string;
    protected fState: 		objState;
    protected fNewData: 	boolean;
    protected fDelete: 		boolean;
    protected fLock: 		boolean;
    protected fView: 		VObjectView;
    protected fParent: 		IObject;
    
    protected fSubNodes: Array<IObject> = new Array;
    
    protected fMsgHandlerMap : 		TMsgHandler<TSetHandler>; 
    protected fGetMsgHandlerMap : 	TGetMsgHandler<TGetHandler>; 
//    protected fGetMsgHandlerMap: Array<GetParamMsgHandler<any>> = new Array;
    
    protected fObjectView: VObjectView;

    
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

        this.fMsgHandlerMap 	= new TMsgHandler<TSetHandler>();
		this.fGetMsgHandlerMap	= new TGetMsgHandler<TGetHandler>();
        this.setHandlers(); 
    } 
    
// HANDLERS
//--------------------------------------------------------------  
    setHandlers() {
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler(this._set());
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler(this._get());
        this.fMsgHandlerMap[ksave_SetMethod]= new TMethodHandler(this._save());

 	    this.colorAble();
	    this.positionAble();
	    this.timeAble();
    }
    
    colorAble(): void {
        this.fMsgHandlerMap[kcolor_GetSetMethod] 		= new TMsgHandlerColor(this.fColor._setRGB());
        this.fMsgHandlerMap[khsb_SetMethod] 			= new TMsgHandlerColor(this.fColor._setHSB());

        this.fMsgHandlerMap[kred_GetSetMethod] 			= new TMsgHandlerNum(this.fColor._setR());
	    this.fMsgHandlerMap[kgreen_GetSetMethod] 		= new TMsgHandlerNum(this.fColor._setG());
	    this.fMsgHandlerMap[kblue_GetSetMethod]			= new TMsgHandlerNum(this.fColor._setB());
        this.fMsgHandlerMap[kalpha_GetSetMethod] 		= new TMsgHandlerNum(this.fColor._setA());
	    this.fMsgHandlerMap[khue_GetSetMethod] 			= new TMsgHandlerNum(this.fColor._setH());
	    this.fMsgHandlerMap[ksaturation_GetSetMethod]	= new TMsgHandlerNum(this.fColor._setS());
        this.fMsgHandlerMap[kbrightness_GetSetMethod]	= new TMsgHandlerNum(this.fColor._setV());

        this.fMsgHandlerMap[kdred_SetMethod] 			= new TMsgHandlerNum(this.fColor._dR());
	    this.fMsgHandlerMap[kdgreen_SetMethod] 			= new TMsgHandlerNum(this.fColor._dG());
	    this.fMsgHandlerMap[kdblue_SetMethod]			= new TMsgHandlerNum(this.fColor._dB());
        this.fMsgHandlerMap[kdalpha_SetMethod] 			= new TMsgHandlerNum(this.fColor._dA());
	    this.fMsgHandlerMap[kdhue_SetMethod] 			= new TMsgHandlerNum(this.fColor._dH());
	    this.fMsgHandlerMap[kdsaturation_SetMethod]		= new TMsgHandlerNum(this.fColor._dS());
        this.fMsgHandlerMap[kdbrightness_SetMethod]		= new TMsgHandlerNum(this.fColor._dV());

        this.fGetMsgHandlerMap[kcolor_GetSetMethod] 	= new TGetMsgHandlerArray(this.fColor._getRGB());
        this.fGetMsgHandlerMap[khsb_SetMethod] 			= new TGetMsgHandlerArray(this.fColor._getHSB());
        this.fGetMsgHandlerMap[kred_GetSetMethod] 		= new TGetMsgHandlerNum(this.fColor._getR());
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] 	= new TGetMsgHandlerNum(this.fColor._getG());
	    this.fGetMsgHandlerMap[kblue_GetSetMethod] 		= new TGetMsgHandlerNum(this.fColor._getB());
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] 	= new TGetMsgHandlerNum(this.fColor._getA());
        this.fGetMsgHandlerMap[khue_GetSetMethod] 		= new TGetMsgHandlerNum(this.fColor._getH());
	    this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetMsgHandlerNum(this.fColor._getS());
	    this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetMsgHandlerNum(this.fColor._getV());    
    }
    
    positionAble() {
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setXPos());
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setYPos());
        this.fMsgHandlerMap[kxorigin_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setXOrigin());
        this.fMsgHandlerMap[kyorigin_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setYOrigin());
        this.fMsgHandlerMap[kz_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setZOrder());
        this.fMsgHandlerMap[kangle_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setRotateZ());
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMsgHandlerNum(this.fPosition._setScale());
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
    
    
// METHODS
//--------------------------------------------------------------  
    addChild(newObject: IObject): void { 
        this.fSubNodes.push(newObject);
        this.setState(objState.kSubModified);
    } 
    
    setParent(parent: IObject): void { this.fParent = parent; }    
    getParent(): IObject 			{ return this.fParent; }    
    getSubNodes(): Array<IObject> 	{ return this.fSubNodes }
    getSubNodesCount(): number 		{ return this.fSubNodes.length; }
    getAppl() : IObject				{ return this.fParent.getAppl(); }
    getScene(): IObject 			{ return this.fParent.getScene(); }

    toString(): string 				{ return this.fName + ": " + this.fSubNodes; }
   
    //-----------------------------    
    getName(): string 				{ return this.fName; }
    getTypeString(): string 		{ return this.fTypeString; }        
    
    find(expr: string, outlist: Array<IObject>): boolean {
        if (!Tools.regexp(expr)) {
            return this.exactfind(expr, outlist);
        }
        else {
            let size = outlist.length;
            let n 	 = this.getSubNodesCount();
            
            for (let i = 0; i < n; i++) {
                let elt: IObject = this.fSubNodes[i];
                if (!elt.getDeleted()) { outlist.push(elt); }       
            }
            
            return outlist.length > size;
        }
    }
    
    //-----------------------------
    exactfind(name:string, outlist: Array<IObject>): boolean {
        let n: number = this.fSubNodes.length;
        let ret: boolean = false;
        for (let i: number = 0; i < n; i++) {
            let elt: IObject = this.fSubNodes[i];
            if ((!elt.getDeleted()) && (elt.fName == name)) {
                outlist.push(this.fSubNodes[i]);
                ret = true;
            }
        }
        return ret;
    }
    
    //-----------------------------    
    newData(state: boolean): void { this.fNewData = state; /*triggerEvent(kNewData, true)*/; }
    
    setState (s: objState): void 	{ this.fState = s; }
    getState(): objState 			{ return this.fState; }
    
    getPos(): IPosition 		{ return this.fPosition; }
    getColor(): IColor 			{ return this.fColor; }
    getOSCAddress(): string 	{ return this.fParent.getOSCAddress() + "/" + this.fName; }

    transferAttributes(dest: IObject): IObject {
        dest.fPosition 	= this.fPosition;
        dest.fColor		= this.fColor;
        dest.fDate		= this.fDate;

        //dest.fPosition.setPenWidth(getPenWidth());
        //dest.fPosition.setPenColor(getPenColor());
        //dest.fPosition.setPenStyle(getPenStyle());
        
        return dest;
    }   
    
    //-----------------------------
    accept(address: string/*, const IMessage*/): boolean {
        return (this.fName == address);
        //return match(address);
    }

    // View
    //-----------------------------    
    setView(view: VObjectView): void 	{ this.fObjectView = view }
    getView(): VObjectView 				{ return this.fObjectView }
    
    //-----------------------------
    /*match(adress: string): boolean
    {
        OSCRegexp r (regexp.c_str());
        return r.match(name().c_str());
    }*/
    
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
    processMsg (address: string, addressTail: string , msg: IMessage): number {
        let result: number = msgStatus.kBadAddress;
        if (this.accept(address/*, msg*/)) {
            let beg: string = OSCAddress.addressFirst(addressTail);	
            let tail: string = OSCAddress.addressTail(addressTail);
                
            if (tail.length) {
                let n: number = this.fSubNodes.length;
                for (let i: number = 0; i < n; i++) { result |= this.fSubNodes[i].processMsg (beg, tail, msg); }
            }

            else {										
                let targets: Array<IObject> = new Array;
                if (this.find (beg, targets)) {	
                    let n: number = targets.length;
                    for (let i: number = 0; i < n; i++) {
                        let target: IObject = targets[i];
//                        console.log(target);
                        result |= target.execute(msg);	
                        if (result & msgStatus.kProcessed) { target.setState(objState.kModified); }
                    }
                }               
                else if (Tools.regexp(beg)) { result = msgStatus.kProcessedNoChange; }                    
                else { result = this.newObj (msg, beg).status; }
            }
        }  
            
        if (result & msgStatus.kProcessed) { this.setState(objState.kSubModified); }
    	return result;     
    }
    
    //-------------------------------------------------------------
    // the basic 'set' handler
    //-------------------------------------------------------------
    set(msg: IMessage): msgStatus	{
        let type = msg.paramStr(1);
        if (!type.correct) { return msgStatus.kBadParameters; }
        
        if (type.value != this.getTypeString()) {
			let out = this.newObj (msg, this.fName);
            if (out.status & msgStatus.kProcessed) {
	            // todo: transfer this attributes to new object
	            this.transferAttributes (out.obj);
            	this.del();
//				this.fParent.cleanupSync();
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
			ITLOut.write (outmsg.toString());
        }
        else for (let i=1; i< n; i++) {
        	let attribute = msg.paramStr(i);
        	if (attribute.correct) {
        		let outmsg = this.get1AttributeMsg (attribute.value);
//        		let h = this.fGetMsgHandlerMap[attribute.value];
        		if (outmsg) { 
//        			let outmsg = new IMessage (this.getOSCAddress(), attribute.value);
//        			h.fill (outmsg);
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
    // the specific 'get' methods
    //-------------------------------------------------------------
    abstract getSet(): IMessage;
      
    //-------------------------------------------------------------
    // get 1 message for 1 attribute
    get1AttributeMsg(attribute: string): IMessage {
        let outmsg : IMessage
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
    	out.push (this.getSet ());
    	let p = this.getAttributesMsg();
	    for (let i=0; i < p.length; i++)
		    out.push (p[i]);
    	
        let n 	 = this.getSubNodesCount();
		for (let i = 0; i < n; i++) {
	    	let subout = this.fSubNodes[i].getSetRecurse ();
	    	for (let i=0; i < subout.length; i++)
		    	out.push (subout[i]);
		}
		return out;
    }
 
    //-----------------------------    
    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: msgStatus, obj?: IObject } 
    				{ return this.getAppl().proxy_create(msg, name, parent); }                
    protected newObj (msg: IMessage, name: string): { status: msgStatus, obj?: IObject } 
    				{ return this.proxy_create(msg, name, this); }                
    
    //-----------------------------    
    getDeleted(): boolean 	{ return this.fDelete; }
    del(): void {
        if(this.fLock){
//            console.log("ITLErr : Impossible to delete " + this.getOSCAddress() + ", the object is locked.");
            this.fDelete = false;
            return;
	    }
        if(this.fDelete) {
//            let scene = this.fObjectView.getMotherScene();
//            let obj = this.fObjectView.getScene();
//            scene.removeChild(obj);
            
            let array = this.fParent.getSubNodes();
            array.splice(array.indexOf(this),1);
            delete this;    
            
        }
    }
}
