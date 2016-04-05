///<reference path="../externals/fraction/fraction.ts"/>
///<reference path="Icolor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="IProxy.ts"/>

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
    
    protected fMsgHandlerMap: Array<MsgHandler<any,any>> = new Array;
    protected fGetMsgHandlerMap: Array<MsgHandler<any,any>> = new Array;
    
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
	    //positionAble();
	    //shapeAble();
	    //timeAble();
    }
    
    colorAble(): void {
        this.fMsgHandlerMap[kred_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setR');
	    this.fMsgHandlerMap[kgreen_GetSetMethod] = this.fColor.fSetColorMsgHandler.create(this.fColor, 'setG');
	    this.fMsgHandlerMap[kblue_GetSetMethod]	= this.fColor.fSetColorMsgHandler.create(this.fColor, 'setB');
        
        this.fGetMsgHandlerMap[kred_GetSetMethod] = new TGetParamMethodHandler<IColor, any> (this.fColor, this.fColor.getR);
        //this.fGetMsgHandlerMap[kgreen_GetSetMethod] = new TGetParamMethodHandler<IColor, any> (this.fColor, this.fColor.getG);
	    //this.fGetMsgHandlerMap[kblue_GetSetMethod] = new TGetParamMethodHandler<IColor, any> (this.fColor, this.fColor.getB);
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
        var handler: MsgHandler<any,any> = this.messageHandler(msg.message());
        if (handler) {return handler.executeHandler(msg) };

        //handler = this.messageHandler(msg.message(), true);
        //if (handler) return ;

        //handler = this.messageHandler("*");
        //if (handler) return ;
        //return MsgHandler.fMsgStatus.kBadParameters;
    }
    
    //-----------------------------
    
    messageHandler(msg: string, match?: boolean): MsgHandler<any,any> {
        var handler: MsgHandler<any,any>;
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
