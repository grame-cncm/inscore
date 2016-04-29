
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="IObjectFactory.ts"/>

class IProxy {	

	static execute (msg: IMessage, objName: string, parent: IObject): { status: msgStatus, obj?: IObject } {
        
        if (Tools.regexp(objName)) { return { status: msgStatus.kBadAddress }; }

	    let objType: string;
        
		let method = msg.message();
		if (!method.correct) return { status: msgStatus.kBadParameters };

	    // check if we try to create a scene
	    if (parent && (parent.getTypeString() == 'IAppl')) {
		    if (method.value != 'new') 	return { status: msgStatus.kBadAddress };
		    if (msg.size() != 1) 		return { status: msgStatus.kBadParameters };
		    objType = 'scene';
	    }
	
	    // for regular objects, fetch the object type from the 1st argument
        else {
            if (method.value != 'set') 	return { status: msgStatus.kBadAddress };
            if (msg.size() < 2)  		return { status: msgStatus.kBadParameters };
			let type = msg.paramStr(1);
			if (!type.correct) 			return { status: msgStatus.kBadParameters };
            objType = type.value;
        }

		// eventually create the new object
		let obj = IObjectFactory.createObj(objName, objType, parent)
        if ( obj ) {
		    let ret = obj.execute(msg);
		    if (ret & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) {
			    parent.addChild(obj);
			    obj.setState(objState.kModified);
			    return { status: msgStatus.kProcessed, obj: obj};
		    }
		    return { status: ret };
	    }
		return { status: msgStatus.kCreateFailure };
    }
}
