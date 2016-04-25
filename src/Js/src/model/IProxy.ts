///<reference path="IObject.ts"/>

class IProxy {	

	static execute (msg: IMessage, objName: string, parent: IObject): number {
        
        if (Tools.regexp(objName)) { return MsgHandler.fMsgStatus.kBadAddress; }

	    var objType: string;
        
	    if (parent && (parent.getTypeString() == 'IAppl')) {
		    if (msg.message() != 'new') {
                return MsgHandler.fMsgStatus.kBadAddress;
            }
		    if (msg.size() != 1) { 
                return MsgHandler.fMsgStatus.kBadParameters; }
                
		    objType = 'scene';
	    }
	
        else {
            if (msg.message() != 'set') { 
                return MsgHandler.fMsgStatus.kBadAddress; 
            }   
            if (msg.size() == 0) {
                return MsgHandler.fMsgStatus.kBadParameters;
            }
            objType = msg.param(1);
        }

        var newmsg: IMessage = new IMessage(msg);
        
        var obj: IObject = IObjectFactory.createObj(objName, objType, parent)
        if (obj) {
		    var status: number = obj.execute(newmsg);
		    if (status & (MsgHandler.fMsgStatus.kProcessed + MsgHandler.fMsgStatus.kProcessedNoChange)) {
			    parent.addChild(obj);
			    obj.setState(state.kModified);
			    return MsgHandler.fMsgStatus.kProcessed;
		    }
		    return status;
	    }
	return MsgHandler.fMsgStatus.kCreateFailure;
    }
}