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
}

class TGetParamMethodHandler<C,T> {
    protected fObject: C;
    protected fMethod: T;
    
    constructor(obj: C, method: T) {
        this.fObject = obj;
        this.fMethod = method;    
    }     
}

		
