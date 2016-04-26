///<reference path="IObject.ts"/>

class IProxy {	

	static execute (msg: IMessage, objName: string, parent: IObject, newobj?: IObject, previousobj?: IObject): number {
        
        if (Tools.regexp(objName)) { return msgStatus.kBadAddress; }

	    var objType: string;
        
		let method = msg.message();
		if (!method.correct) return msgStatus.kBadParameters;

	    if (parent && (parent.getTypeString() == 'IAppl')) {
		    if (method.value != 'new') 	return msgStatus.kBadAddress;
		    if (msg.size() != 1) 		return msgStatus.kBadParameters;
		    objType = 'scene';
	    }
	
        else {
            if (method.value != 'set') 	return msgStatus.kBadAddress;
            if (msg.size() < 2)  		return msgStatus.kBadParameters;
			let type = msg.paramStr(1);
			if (!type.correct) 			return msgStatus.kBadParameters;
            objType = type.value;
        }

        let newmsg = new IMessage(msg);
        console.log(newmsg)
        var obj: IObject = IObjectFactory.createObj(objName, objType, parent)
        if (obj && obj.msgSet(msg.params())) {
		    var status: number = obj.execute(newmsg);
		    if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) {
			    parent.addChild(obj);
			    obj.setState(state.kModified);
			    return msgStatus.kProcessed;
		    }
		    return status;
	    }
	return msgStatus.kCreateFailure;
    }
}