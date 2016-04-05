enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

class MsgHandler<C,T> {
    protected fObject: C;
    protected fMethod: T;    
    static fMsgStatus = msgStatus;
     
    constructor(obj:C, method:T) {
        this.fObject = obj;
        this.fMethod = method;    
    }
    
    executeHandler(msg: IMessage): msgStatus { 
        if ( msg.size() != 1 ) { return msgStatus.kBadParameters; } 
         
        var val: number;
        var castParam: Array<any> = msg.cast_param(0, val); 
	    if ( !castParam['status'] ) { return msgStatus.kBadParameters;}
        val = castParam['val'];
	    
        //console.log(this.fObject.)
        console.log(this.fObject);       
        
        var method = this.fMethod + ''; 
        this.fObject[method](val);

        console.log(this.fObject);
        	    
        // fSlave->modify();
	    return msgStatus.kProcessed;   
    }    
}


//********************************************
class TGetParamMethodHandler<C,T> {
    protected fObject: C;
    protected fMethod: T;
    
    constructor(obj: C, method: T) {
        this.fObject = obj;
        this.fMethod = method;    
    }
}    
    
class TMethodMsgHandler<C,T> extends MsgHandler<C,T> {
    
    constructor(obj: C, method: T) {
        super(obj, method);    
    }
}

class TSetMethodMsgHandler<C,T> extends MsgHandler<C,T> {
 
    constructor(obj: C, method: T) {
        super(obj, method);    
    }   
}
