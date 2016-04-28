
///<reference path="../externals/fraction/fraction.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="../view/VObjectView.ts"/>

///<reference path="Methods.ts"/>
///<reference path="Icolor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>

enum state {
    kClean,
    kNewObject = 1,
    kModified = 2,
    kSubModified = 4,
    kMasterModified = 8, 
}

class IHandlersMap<T> { [index: string]: T; }


abstract class IObject {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fPosition: 	IPosition;
    protected fDate: 		IDate;
    protected fColor: 		IColor;
    
    protected fTypeString:	string;
    protected fName: 		string;
    protected fState: 		state;
    protected fNewData: 	boolean;
    protected fDelete: 		boolean;
    protected fLock: 		boolean;
    protected fView: 		VObjectView;
    protected fParent: 		IObject;
    
    protected fSubNodes: Array<IObject> = new Array;
    
    protected fMsgHandlerMap = new IHandlersMap<SetMsgHandler>(); 
//    protected fGetMsgHandlerMap: Array<GetParamMsgHandler<any>> = new Array;
    
//    protected kDocument: HTMLElement; 
    protected fObjectView: VObjectView;
    protected fMotherSceneFocus: boolean;

    
// CONSTRUCTOR
//--------------------------------------------------------------       
    constructor(name: string, parent?: IObject) {
        this.fName = name;
        this.fTypeString = 'obj'; 
        
        this.fDelete = false;
        this.fLock = false;
        this.fState = state.kNewObject;
        this.fNewData = true;
        
//        this.kDocument = document.getElementById('document');
        
        this.fMotherSceneFocus = false; 

        if (parent) { 
            this.fParent = parent; 
            this.fParent.addChild(this); 
        }

        this.fPosition = new IPosition;
        this.fDate = new IDate;
		this.fColor = new IColor(0,0,0);
        
//        this.fMsgHandlerMap[kset_SetMethod] = new TMethodMsgHandler<IObject>(this, 'set');

        this.setHandlers(); 
    } 
    
// HANDLERS
//--------------------------------------------------------------  
    setHandlers() {
	    this.colorAble();
	    this.positionAble();
	    this.timeAble();
    }
    
    colorAble(): void {
        this.fMsgHandlerMap[kred_GetSetMethod] 			= new TMsgHandlerNum<IColor>(this.fColor, 'setR');
	    this.fMsgHandlerMap[kgreen_GetSetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'setG');
	    this.fMsgHandlerMap[kblue_GetSetMethod]			= new TMsgHandlerNum<IColor>(this.fColor, 'setB');
        this.fMsgHandlerMap[kalpha_GetSetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'setA');
	    this.fMsgHandlerMap[khue_GetSetMethod] 			= new TMsgHandlerNum<IColor>(this.fColor, 'setH');
	    this.fMsgHandlerMap[ksaturation_GetSetMethod]	= new TMsgHandlerNum<IColor>(this.fColor, 'setS');
        this.fMsgHandlerMap[kbrightness_GetSetMethod]	= new TMsgHandlerNum<IColor>(this.fColor, 'setV');

        this.fMsgHandlerMap[kdred_SetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'dR');
	    this.fMsgHandlerMap[kdgreen_SetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'dG');
	    this.fMsgHandlerMap[kdblue_SetMethod]		= new TMsgHandlerNum<IColor>(this.fColor, 'dB');
        this.fMsgHandlerMap[kdalpha_SetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'dA');
	    this.fMsgHandlerMap[kdhue_SetMethod] 		= new TMsgHandlerNum<IColor>(this.fColor, 'dH');
	    this.fMsgHandlerMap[kdsaturation_SetMethod]	= new TMsgHandlerNum<IColor>(this.fColor, 'dS');
        this.fMsgHandlerMap[kdbrightness_SetMethod]	= new TMsgHandlerNum<IColor>(this.fColor, 'dV');
/*        
        this.fGetMsgHandlerMap[kred_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getR');
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getG');
	    this.fGetMsgHandlerMap[kblue_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getB');
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getA');
        this.fGetMsgHandlerMap[khue_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getH');
	    this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getS');
	    this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getV');    
*/
    }
    
    positionAble() {
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum<IPosition>(this.fPosition, 'setXPos');
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum<IPosition>(this.fPosition, 'setYPos');
        this.fMsgHandlerMap[kxorigin_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setXOrigin');
        this.fMsgHandlerMap[kyorigin_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setYOrigin');
        this.fMsgHandlerMap[kz_GetSetMethod] 		= new TMsgHandlerNum<IPosition>(this.fPosition, 'setZOrder');
        this.fMsgHandlerMap[kangle_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setRotateZ');
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setScale');
//        this.fMsgHandlerMap[kshear_GetSetMethod] 	= new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setShear');
        this.fMsgHandlerMap[krotatex_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setRotateX'); 
        this.fMsgHandlerMap[krotatey_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setRotateY'); 
        this.fMsgHandlerMap[krotatez_GetSetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'setRotateZ'); 
        
        this.fMsgHandlerMap[kdx_SetMethod] 			= new TMsgHandlerNum<IPosition>(this.fPosition, 'addXPos');
        this.fMsgHandlerMap[kdy_SetMethod] 			= new TMsgHandlerNum<IPosition>(this.fPosition, 'addYPos');
        this.fMsgHandlerMap[kdxorigin_SetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'addXOrigin');
        this.fMsgHandlerMap[kdyorigin_SetMethod] 	= new TMsgHandlerNum<IPosition>(this.fPosition, 'addYOrigin');
        this.fMsgHandlerMap[kdz_SetMethod] 			= new TMsgHandlerNum<IPosition>(this.fPosition, 'addZOrder');
        this.fMsgHandlerMap[kdangle_SetMethod] 		= new TMsgHandlerNum<IPosition>(this.fPosition, 'addAngle');
        this.fMsgHandlerMap[kdscale_SetMethod] 		= new TMsgHandlerNum<IPosition>(this.fPosition, 'multScale');
/*        
        this.fGetMsgHandlerMap[kx_GetSetMethod]			= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getXPos');
        this.fGetMsgHandlerMap[ky_GetSetMethod]			= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getYPos');
        this.fGetMsgHandlerMap[kxorigin_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getXOrigin');
        this.fGetMsgHandlerMap[kyorigin_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getYOrigin');
        this.fGetMsgHandlerMap[kz_GetSetMethod]			= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getZOrder');
        this.fGetMsgHandlerMap[kangle_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getRotateZ');
        this.fGetMsgHandlerMap[kscale_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getScale');
        this.fGetMsgHandlerMap[kshow_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getVisible');
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getWidth');
        this.fGetMsgHandlerMap[kheight_GetSetMethod] 	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getHeight');
        this.fGetMsgHandlerMap[kshear_GetSetMethod]	 	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getShear');
        this.fGetMsgHandlerMap[krotatex_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getRotateX');
        this.fGetMsgHandlerMap[krotatey_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getRotateY');
        this.fGetMsgHandlerMap[krotatez_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getRotateZ');
*/
    }
    
    timeAble() {
        this.fMsgHandlerMap[kdate_GetSetMethod] 	= new TMsgHandlerTime<IDate>(this.fDate, 'setDate');
        this.fMsgHandlerMap[kduration_GetSetMethod]	= new TMsgHandlerTime<IDate>(this.fDate, 'setDuration');
        this.fMsgHandlerMap[kddate_SetMethod] 		= new TMsgHandlerTime<IDate>(this.fDate, 'addDate');
        this.fMsgHandlerMap[kdduration_SetMethod] 	= new TMsgHandlerTime<IDate>(this.fDate, 'addDuration');        
        this.fMsgHandlerMap[kclock_SetMethod] 		= new TMsgHandlerVoid<IDate>(this.fDate, 'clock');
        this.fMsgHandlerMap[kdurClock_SetMethod] 	= new TMsgHandlerVoid<IDate>(this.fDate, 'durclock');

/*        
        this.fGetMsgHandlerMap[kdate_GetSetMethod] = new TGetParamMethodHandler<IDate>(this.fDate, 'getDate');
        this.fGetMsgHandlerMap[kduration_GetSetMethod] = new TGetParamMethodHandler<IDate>(this.fDate, 'getDuration');
*/
    }
    
    
// METHODS
//--------------------------------------------------------------  
    addChild(newObject: IObject): void { 
        this.fSubNodes.push(newObject);
        this.setState(state.kSubModified);
    } 
    
    setParent(parent: IObject): void { this.fParent = parent; }    
    getParent(): IObject 			{ return this.fParent; }    
    getSubNodes(): Array<IObject> 	{ return this.fSubNodes }
    getAppl() : IObject				{ return this.fParent.getAppl(); }
    getScene(): IObject 			{ return this.fParent.getScene(); }
   
    //-----------------------------    
    getName(): string 				{ return this.fName; }
    getTypeString(): string 		{ return this.fTypeString; }        
    
    find(expr: string, outlist: Array<IObject>): boolean {
        if (!Tools.regexp(expr)) {
            return this.exactfind(expr, outlist);
        }
        else {
            let size: number = outlist.length;
            let n: number = this.fSubNodes.length;
            
            for (let i: number = 0; i < n; i++) {
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
    
    setState (s: state): void { this.fState = s; }
    getState(): state { return this.fState; }
    
    getPos(): IPosition { return this.fPosition; }
    getColor(): IColor { return this.fColor; }

     transferAttributes(dest: IObject): IObject {
        dest.fPosition.setXPos (this.fPosition.getXPos());
        dest.fPosition.setYPos (this.fPosition.getYPos());
        dest.fPosition.setXOrigin (this.fPosition.getXOrigin());
        dest.fPosition.setYOrigin (this.fPosition.getYOrigin());
        dest.fPosition.setScale (this.fPosition.getScale());
        dest.fPosition.setVisible (this.fPosition.getVisible());
        dest.fPosition.setZOrder (this.fPosition.getZOrder());
        dest.fPosition.setShear (this.fPosition.getShear());

        dest.fPosition.setRotateX (this.fPosition.getRotateX());
        dest.fPosition.setRotateY (this.fPosition.getRotateY());
        dest.fPosition.setRotateZ (this.fPosition.getRotateZ());

        dest.fColor.setR(this.fColor.getR());
        dest.fColor.setG(this.fColor.getG());
        dest.fColor.setB(this.fColor.getB());
        dest.fColor.setA(this.fColor.getA());

        //dest.fPosition.setPenWidth(getPenWidth());
        //dest.fPosition.setPenColor(getPenColor());
        //dest.fPosition.setPenStyle(getPenStyle());
        
        dest.fDate.setDate (this.fDate.getDate());
        dest.fDate.setDuration (this.fDate.getDuration());
             
        return dest;
    }   
    
    //-----------------------------
    accept(address: string/*, const IMessage*/): boolean {
        return (this.fName == address);
        //return match(address);
    }
  
    // Récupération de la scene mère
    //----------------------------- 
    checkScene(): void {
        if (this.fParent.fName != 'ITL') {
            this.fParent.checkScene();
        }
        else { this.fMotherSceneFocus = true }   
    }
   

    // View
    //-----------------------------    
    setView(view: VObjectView): void 	{ this.fObjectView = view }
    getView(): VObjectView 				{ return this.fObjectView }
    
/*
    afficheView(): void {
        let cible = this.fObjectView.getScene();
        if (this.fTypeString == 'scene') { this.kDocument.appendChild(cible) }
        
        else { 
            let parent = this.fParent.fObjectView.getMotherScene();
            parent.appendChild(cible);
        }
    }
*/
    
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
            console.log("Le message '" + method.value + "' est donné à : // from IObject.execute()");
            console.log(this);   
        	if (handler) { 
                console.log("Le handler correspondant est appelé : // from IObject.execute()");
                console.log(handler);
                return handler.handle(msg) 
            }

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
    
    messageHandler(msg: string, match?: boolean): SetMsgHandler {
        let handler: SetMsgHandler;
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
                        console.log(target);
                        result |= target.execute(msg);	
                        if (result & msgStatus.kProcessed) { target.setState(state.kModified); }
                    }
                }               
                else if (Tools.regexp(beg)) { result = msgStatus.kProcessedNoChange; }                    
                else { result = this.proxy_create (msg, this.fName, this.fParent).status; }
            }
        }  
            
        if (result & msgStatus.kProcessed) { this.setState(state.kSubModified); }
    	return result;     
    }
    
    set(msg: IMessage): msgStatus	{
        let type: string = typeof msg.param(1);
        if (typeof type != "string") { return msgStatus.kBadParameters; }
        
        if (typeof type != this.getTypeString()) {
			let out = this.proxy_create (msg, this.fName, this.fParent);
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
    
    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: msgStatus, obj?: IObject } 
    				{ return this.getAppl().proxy_create(msg, this.fName, this.fParent); }                
    
    //-----------------------------    
    getDeleted(): boolean 	{ return this.fDelete; }
    del(): void {
        if(this.fLock){
//            console.log("ITLErr : Impossible to delete " + this.getOSCAddress() + ", the object is locked.");
            this.fDelete = false;
            return;
	    }
        if(this.fDelete) {
            console.log("supression de l'ancien objet");
            console.log(this)
//            let scene = this.fObjectView.getMotherScene();
//            let obj = this.fObjectView.getScene();
//            scene.removeChild(obj);
            
            let array = this.fParent.getSubNodes();
            array.splice(array.indexOf(this),1);
            delete this;    
            
        }
    }
}
