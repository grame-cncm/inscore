enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

class MsgHandler<C> {
    protected fObject: C;
    protected fMethod: string;    
    static fMsgStatus = msgStatus;
     
    constructor(obj:C, method:string) {
        this.fObject = obj;
        this.fMethod = method;    
    }
    
    executeHandler(msg: IMessage): msgStatus { 
        if ( msg.size() != 1 ) { return msgStatus.kBadParameters; } 
         
        var val: number;
        var castParam: Array<any> = msg.cast_param(0, val); 
	    if ( !castParam['status'] ) { return msgStatus.kBadParameters;}
        val = castParam['val'];
	    
        console.log(this.fObject);
        var method = this.fMethod + ''; 
        this.fObject[method](val);

        console.log(this.fObject);
        	    
        // fSlave->modify();
	    return msgStatus.kProcessed;   
    }    
}

class GetParamMsgHandler<C> {
    protected fObject: C;
    protected fMethod: string;    
     
    constructor(obj:C, method:string) {
        this.fObject = obj;
        this.fMethod = method;    
    }
    
    executeHandler(msg: IMessage): msgStatus { 
        if ( msg.size() != 1 ) { return msgStatus.kBadParameters; } 
         
        var val: number;
        var castParam: Array<any> = msg.cast_param(0, val); 
	    if ( !castParam['status'] ) { return msgStatus.kBadParameters;}
        val = castParam['val'];     
        
        var method = this.fMethod + ''; 
        this.fObject[method](val);

	    return msgStatus.kProcessed;   
    }    
}

//********************************************
class TGetParamMethodHandler<C> extends GetParamMsgHandler<C>  {
    protected fObject: C;
    protected fMethod: string;
    
    constructor(obj: C, method: string) {
        super(obj, method);    
    }
}    
    
class TMethodMsgHandler<C> extends MsgHandler<C> {
    
    constructor(obj: C, method: string) {
        super(obj, method);    
    }
}

class TSetMethodMsgHandler<C> extends MsgHandler<C> {
 
    constructor(obj: C, method: string) {
        super(obj, method);    
    }   
}
