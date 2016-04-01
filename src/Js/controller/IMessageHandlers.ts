enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

class MsgHandler {
    static fMsgStatus = msgStatus; 
    constructor() {};
    
    executeHandler(msg: IMessage): msgStatus {
        if ( msg.size() != 1 ) return msgStatus.kBadParameters;
	    var val: number;
	    //if ( !msg.cast_param(0, val) ) return msgStatus.kBadParameters;

	    //(fObject->*fMethod)( val );
	    // fSlave->modify();
	    return msgStatus.kProcessed;   
    }    
}

class TGetParamMethodHandler<C,T> extends MsgHandler {
    protected fObject: C;
    protected fMethod: T;
    
    super(obj: C, method: T) {
        this.fObject = obj;
        this.fMethod = method;    
    }
}    
    
class TMethodMsgHandler<C,T> extends MsgHandler {
    protected fObject: C;
    protected fMethod: T;
    
    super(obj: C, method: T) {
        this.fObject = obj;
        this.fMethod = method;    
    }
}
