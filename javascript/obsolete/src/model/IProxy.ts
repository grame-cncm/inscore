
///<reference path="../controller/TSetMessageHandlers.ts"/>
///<reference path="IObjectFactory.ts"/>
///<reference path="IProxyInterface.ts"/>

class IProxyImpl extends IProxyInterface {	

	execute (msg: IMessage, objName: string, parent: IObject): { status: eMsgStatus, obj?: IObject } {
        
        if (Tools.regexp(objName)) { return { status: eMsgStatus.kBadAddress }; }

	    let objType: string;
        
		let method = msg.message();
		if (!method.correct) return { status: eMsgStatus.kBadParameters };

	    // check if we try to create a scene
	    if (parent && (parent.getTypeString() == 'IAppl')) {
		    if (method.value != 'new') 	return { status: eMsgStatus.kBadAddress };
		    if (msg.size() != 1) 		return { status: eMsgStatus.kBadParameters };
		    objType = 'scene';
	    }
	
	    // for regular objects, fetch the object type from the 1st argument
        else {
            if (method.value != 'set') 	return { status: eMsgStatus.kBadAddress };
            if (msg.size() < 2)  		return { status: eMsgStatus.kBadParameters };
			let type = msg.paramStr(1);
			if (!type.correct) 			return { status: eMsgStatus.kBadParameters };
            objType = type.value;
        }

		// eventually create the new object
		let obj = IObjectFactory.createObj(objName, objType, parent)
        if ( obj ) {
		    let ret = obj.execute(msg);
		    if (ret & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) {
			    parent.addChild(obj);
			    obj.setState(eObjState.kModified);
			    return { status: eMsgStatus.kProcessed, obj: obj};
		    }
		    return { status: ret };
	    }
		return { status: eMsgStatus.kCreateFailure };
    }
}

IProxy = new IProxyImpl();
