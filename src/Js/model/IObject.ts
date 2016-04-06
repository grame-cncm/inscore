///<reference path="../externals/fraction/fraction.ts"/>
///<reference path="Icolor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="IProxy.ts"/>
///<reference path="../externals/fraction/fraction.ts"/>

enum state {
    kClean,
    kNewObject = 1,
    kModified = 2,
    kSubModified = 4,
    kMasterModified = 8, 
}

abstract class IObject {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fPosition: IPosition;
    protected fDate: IDate;
    protected fColor: IColor;
    
    protected fName: string;
    protected fDispStart: number;
    protected fDispEnd: number; 
    protected fState: state;
    protected fNewData: boolean;
    protected fDelete: boolean;
    protected fLock: boolean;
    protected fView: number;
    
    protected fTypeString: string;
    
    protected fParent: IObject;
    protected fSubNodes: Array<IObject> = new Array;
    
    protected fMsgHandlerMap: Array<MsgHandler<any>> = new Array;
    protected fGetMsgHandlerMap: Array<GetParamMsgHandler<any>> = new Array;
    
    protected kDocument: HTMLElement; 
    protected fObjectView: VObjectView;
    protected fMotherSceneFocus: boolean;

    
// CONSTRUCTOR
//--------------------------------------------------------------       
    constructor(name: string, parent?: IObject, position?: IPosition, date?: IDate, color?: IColor) {
        this.fName = name;
        
        this.fDispStart = 0;
        this.fDispEnd = 1;
        this.fDelete = false;
        this.fLock = false;
        this.fState = state.kNewObject;
        this.fNewData = true;
        this.fView = 0;
        
        this.fTypeString = 'obj'; 
        
        this.kDocument = document.getElementById('document');
        
        this.fMotherSceneFocus = false; 

        if (parent) { 
            this.fParent = parent; parent.addChild(this); }

        if (position) { this.fPosition = position; }
        else { this.fPosition = new IPosition; }
        
        if (date) { this.fDate = date; }
        else { this.fDate = new IDate; }
        
        if (color) { this.fColor = color; }
        else { this.fColor = new IColor(0,0,0); }  
        
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
        this.fMsgHandlerMap[kred_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setR');
	    this.fMsgHandlerMap[kgreen_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setG');
	    this.fMsgHandlerMap[kblue_GetSetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'setB');
        this.fMsgHandlerMap[kalpha_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setA');
	    this.fMsgHandlerMap[khue_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setH');
	    this.fMsgHandlerMap[ksaturation_GetSetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'setS');
        this.fMsgHandlerMap[kbrightness_GetSetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'setV');

        this.fMsgHandlerMap[kdred_SetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'dR');
	    this.fMsgHandlerMap[kdgreen_SetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'dG');
	    this.fMsgHandlerMap[kdblue_SetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'dB');
        this.fMsgHandlerMap[kdalpha_SetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'dA');
	    this.fMsgHandlerMap[kdhue_SetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'dH');
	    this.fMsgHandlerMap[kdsaturation_SetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'dS');
        this.fMsgHandlerMap[kdbrightness_SetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'dV');
        
        this.fGetMsgHandlerMap[kred_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getR');
        this.fGetMsgHandlerMap[kgreen_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getG');
	    this.fGetMsgHandlerMap[kblue_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getB');
        this.fGetMsgHandlerMap[kalpha_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getA');
        this.fGetMsgHandlerMap[khue_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getH');
	    this.fGetMsgHandlerMap[ksaturation_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getS');
	    this.fGetMsgHandlerMap[kbrightness_GetSetMethod] = new TGetParamMethodHandler<IColor> (this.fColor, 'getV');    
    }
    
    positionAble() {
        this.fMsgHandlerMap[kx_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setXPos');
        this.fMsgHandlerMap[ky_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setYPos');
        this.fMsgHandlerMap[kxorigin_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setXOrigin');
        this.fMsgHandlerMap[kyorigin_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setYOrigin');
        this.fMsgHandlerMap[kz_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setZOrder');
        this.fMsgHandlerMap[kangle_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setRotateZ');
        this.fMsgHandlerMap[kscale_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setScale');
        this.fMsgHandlerMap[kshear_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setShear');
        this.fMsgHandlerMap[krotatex_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setRotateX'); 
        this.fMsgHandlerMap[krotatey_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setRotateY'); 
        this.fMsgHandlerMap[krotatez_GetSetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'setRotateZ'); 
        
        this.fMsgHandlerMap[kdx_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addXPos');
        this.fMsgHandlerMap[kdy_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addYPos');
        this.fMsgHandlerMap[kdxorigin_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addXOrigin');
        this.fMsgHandlerMap[kdyorigin_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addYOrigin');
        this.fMsgHandlerMap[kdz_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addZOrder');
        this.fMsgHandlerMap[kdangle_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'addAngle');
        this.fMsgHandlerMap[kdscale_SetMethod] = new TSetMethodMsgHandler<IPosition>(this.fPosition, 'multScale');
        
        this.fGetMsgHandlerMap[kx_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getXPos');
        this.fGetMsgHandlerMap[ky_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getYPos');
        this.fGetMsgHandlerMap[kxorigin_GetSetMethod]= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getXOrigin');
        this.fGetMsgHandlerMap[kyorigin_GetSetMethod]= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getYOrigin');
        this.fGetMsgHandlerMap[kz_GetSetMethod]		= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getZOrder');
        this.fGetMsgHandlerMap[kangle_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getZAngle');
        this.fGetMsgHandlerMap[kscale_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getScale');
        this.fGetMsgHandlerMap[kshow_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getVisible');
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getWidth');
        this.fGetMsgHandlerMap[kheight_GetSetMethod] = new TGetParamMethodHandler<IPosition>(this.fPosition, 'getHeight');
        this.fGetMsgHandlerMap[kshear_GetSetMethod]	= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getShear');
        this.fGetMsgHandlerMap[krotatex_GetSetMethod]= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getXAngle');
        this.fGetMsgHandlerMap[krotatey_GetSetMethod]= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getYAngle');
        this.fGetMsgHandlerMap[krotatez_GetSetMethod]= new TGetParamMethodHandler<IPosition>(this.fPosition, 'getZAngle');
    }
    
    timeAble() {
        this.fMsgHandlerMap[kdate_GetSetMethod] = new TSetMethodMsgHandler<IDate>(this.fDate, 'setDate');
        this.fMsgHandlerMap[kduration_GetSetMethod]	= new TSetMethodMsgHandler<IDate>(this.fDate, 'setDuration');
        this.fMsgHandlerMap[kddate_SetMethod] = new TSetMethodMsgHandler<IDate>(this.fDate, 'addDate');
        this.fMsgHandlerMap[kdduration_SetMethod] = new TSetMethodMsgHandler<IDate>(this.fDate, 'addDuration');
        
        this.fMsgHandlerMap[kclock_SetMethod] = new TMethodMsgHandler<IDate>(this.fDate, 'clock');
        this.fMsgHandlerMap[kdurClock_SetMethod] = new TMethodMsgHandler<IDate>(this.fDate, 'durclock');
        
        this.fGetMsgHandlerMap[kdate_GetSetMethod] = new TGetParamMethodHandler<IDate>(this.fDate, 'getDate');
        this.fGetMsgHandlerMap[kduration_GetSetMethod] = new TGetParamMethodHandler<IDate>(this.fDate, 'getDuration');
    }
    
    
// METHODS
//--------------------------------------------------------------  
 
    addChild(newObject: IObject): void { this.fSubNodes.push(newObject); } 
    
    setParent(parent: IObject):void { this.fParent = parent; }
    
    getSubNodes(): Array<IObject> { return this.fSubNodes }
    
    //-----------------------------    
    getTypeString(): string {
        return this.fTypeString;
    }        
    
    find(expr: string, outlist: Array<IObject>): boolean {
        if (!Tools.regexp(expr)) {
            return this.exactfind(expr, outlist);
        }
        else {
            var size: number = outlist.length;
            var n: number = this.fSubNodes.length;
            
            for (var i: number = 0; i < n; i++) {
                var elt: IObject = this.fSubNodes[i];
                if (!elt.getDeleted()) { outlist.push(elt); }       
            }
            
            return outlist.length > size;
        }
    }
    
    //-----------------------------
    
    exactfind(name:string, outlist: Array<IObject>): boolean {
        var n: number = this.fSubNodes.length;
        var ret: boolean = false;
        for (var i: number = 0; i < n; i++) {
            var elt: IObject = this.fSubNodes[i];
            if ((!elt.getDeleted()) && (elt.fName == name)) {
                outlist.push(this.fSubNodes[i]);
                ret = true;
            }
        }
        return ret;
    }
    
    //-----------------------------    

    getDeleted(): boolean { return this.fDelete; }
    
    //-----------------------------    

    setState (s: state): void {
        this.fState |= s;
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
   
    getScene(): HTMLDivElement {
        var scenes = appl.getSubNodes();
        var n = scenes.length;
        
        for (var i: number=0; i < n; i++) {
            if (scenes[i].fMotherSceneFocus == true) {
                scenes[i].fMotherSceneFocus = false;
                return scenes[i].fObjectView.getMotherScene();    
            }
        }     
    } 
    
    // View
    //-----------------------------    
    
    setView(view: VObjectView): void { this.fObjectView = view }
    
    getView(): VObjectView { return this.fObjectView }
    
    afficheView(): void {
        var cible = this.fObjectView.getScene();
        if (this.fTypeString == 'scene') { this.kDocument.appendChild(cible) }
        
        else { 
        var parent = this.fParent.fObjectView.getMotherScene();
        parent.appendChild(cible);
        }
    }
    
    //-----------------------------
    
    /*match(adress: string): boolean
    {
        OSCRegexp r (regexp.c_str());
        return r.match(name().c_str());
    }*/
    
    //-----------------------------
    
    execute (msg: IMessage): number {
        var handler: MsgHandler<any> = this.messageHandler(msg.message());
        if (handler) {return handler.executeHandler(msg) };

        //handler = this.messageHandler(msg.message(), true);
        //if (handler) return ;

        //handler = this.messageHandler("*");
        //if (handler) return ;
        //return MsgHandler.fMsgStatus.kBadParameters;
    }
    
    //-----------------------------
    
    messageHandler(msg: string, match?: boolean): MsgHandler<any> {
        var handler: MsgHandler<any>;
        if (!match) {
            handler = this.fMsgHandlerMap[msg];
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
    
        var result: number = MsgHandler.fMsgStatus.kBadAddress;
        if (this.accept(address/*, msg*/)) {
            var beg: string = OSCAddress.addressFirst(addressTail);	
            var tail: string = OSCAddress.addressTail(addressTail);
                
            if (tail.length) {
                var n: number = this.fSubNodes.length;
                for (var i: number = 0; i < n; i++) { result |= this.fSubNodes[i].processMsg (beg, tail, msg); }
            }

            else {										
                var targets: Array<IObject> = new Array;
                if (this.find (beg, targets)) {				
                    var n: number = targets.length;
                    for (var i: number = 0; i < n; i++) {
                        var target: IObject = targets[i];
                        console.log(target);
                        result |= target.execute(msg);	
                        if (result & MsgHandler.fMsgStatus.kProcessed) { target.setState(state.kModified); }
                    }
                }
                    
                //else if (Tools.regexp(beg)) { result = MsgHandler.kProcessedNoChange; }
                    
                //else { result = IProxy.execute (msg, beg, this); } 
            }
        }  
            
        //if (result & MsgHandler.kProcessed) { this.setState(state.kSubModified); }
            
    return result;     
    }
}
