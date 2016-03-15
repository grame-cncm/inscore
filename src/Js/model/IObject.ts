///<reference path="/Users/margaillan/src/inscore/src/Js/libraries/fraction/fraction.ts"/>
///<reference path="Icolor.ts"/>
///<reference path="IDate.ts"/>
///<reference path="IPosition.ts"/>
///<reference path="OSCAddress.ts"/>
///<reference path="Tools.ts"/>
///<reference path="IProxy.ts"/>



class IObject {
    
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
    
    protected fParent: IObject;
    protected fSubNodes: Array<IObject>;
    
    //enum state { kClean, kNewObject=1, kModified=2, kSubModified=4, kMasterModified=8 };


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
        
        this.fSubNodes = new Array;
        
        if (parent) { this.fParent = parent; parent.addChild(this); }

        if (position) { this.fPosition = position; }
        else { this.fPosition = new IPosition; }
        
        if (date) { this.fDate = date; }
        else { this.fDate = new IDate; }
        
        if (color) { this.fColor = color; }
        else { this.fColor = new IColor(0,0,0); }   
    }

// ADD CHILD
//--------------------------------------------------------------    
    addChild(newObject: IObject): void { this.fSubNodes.push(newObject); } 
    
// METHODS
//--------------------------------------------------------------    
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

    exactfind(name:string, outlist: Array<IObject>): boolean
    {
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

    getDeleted(): boolean { return this.fDelete; }

    setState (s: state): void
    {
        this.fState |= s;
    }
    
    accept(address: string/*, const IMessage*/): boolean
    {
        return (this.fName == address);
        //return match(address);
    }
    
    /*match(adress: string): boolean
    {
        OSCRegexp r (regexp.c_str());
        return r.match(name().c_str());
    }*/
    
    execute (msg: IMessage): number
    {
        SMsgHandler handler = messageHandler(msg->message());
        if ( handler ) return (*handler)(msg);

        // no basic handler , try to find if there is a match
        handler = messageHandler(msg->message(), true);
        if ( handler ) return (*handler)(msg);

        // try to find a default handler
        handler = messageHandler("*");
        if ( handler ) return (*handler)(msg);
        return MsgHandler::kBadParameters;
    }
    
// MESSAGES PROCESSING
//--------------------------------------------------------------     
    processMsg (address: string, addressTail: string, msg: IMessage): number {
    
        var result: number = MsgHandler.kBadAddress;
        if (this.accept(address/*, msg*/)) {
            var beg: string = OSCAddress.addressFirst(addressTail);	
            var tail: string = OSCAddress.addressTail(addressTail);
                
            if (tail.length) {			
                var n: number = this.fSubNodes.length;
                for (var i: number = 0; i < n; i++) {
                    result |= this.fSubNodes[i].processMsg (beg, tail, msg);
                }
            }
            
            else {										
                var targets: Array<IObject> = new Array;
                if (this.find (beg, targets)) {				
                    var n: number = targets.length;
                    for (var i: number = 0; i < n; i++) {
                        var target: IObject = targets[i];
                        console.log(targets);
                        result |= target.execute(msg);	
                        if (result & MsgHandler.kProcessed) {
                            target.setState(state.kModified);		
                        }
                    }
                }
                    
                else if (Tools.regexp(beg)) { result = MsgHandler.kProcessedNoChange; }
                    
                else { result = IProxy.execute (msg, beg, this); } 
            }
        }  
            
        /*if (result & MsgHandler.kProcessed) {
        setState(IObject.kSubModified);
        }*/
            
    return result;     
    }
}
