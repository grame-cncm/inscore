///<reference path="IObject.ts"/>

class IProxy {	

	static execute (msg: IMessage, objName: string, parent: IObject, newobj?: IObject, previousobj?: IObject): { status: number, newobj?: IObject } {
        
        if (Tools.regexp(objName)) { return { status: msgStatus.kBadAddress, newobj: newobj }; }

	    var objType: string;
        
		let method = msg.message();
		if (!method.correct) return { status: msgStatus.kBadParameters, newobj: newobj };

	    if (parent && (parent.getTypeString() == 'IAppl')) {
		    if (method.value != 'new') 	return { status: msgStatus.kBadAddress, newobj: newobj };
		    if (msg.size() != 1) 		return { status: msgStatus.kBadParameters, newobj: newobj };
		    objType = 'scene';
	    }
	
        else {
            if (method.value != 'set') 	return { status: msgStatus.kBadAddress, newobj: newobj };
            if (msg.size() < 2)  		return { status: msgStatus.kBadParameters, newobj: newobj };
			let type = msg.paramStr(1);
			if (!type.correct) 			return { status: msgStatus.kBadParameters, newobj: newobj };
            objType = type.value;
        }

        let newmsg = new IMessage(msg);
        var obj: IObject = IObjectFactory.createObj(objName, objType, parent);
        if (obj) {
			console.log("L'objet suivant a bien été créé // from proxy.execute()");
			console.log(obj);
			if (previousobj) { 
				obj = previousobj.transferAttributes(obj);
				console.log("transfert d'attributs effectué") }
		    var status: number = obj.execute(newmsg);
			console.log("le status : " + status)
		    if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) {
				//parent.addChild(obj);
			    obj.setState(state.kModified);
				if (newobj) { newobj = obj; }
			    return { status: msgStatus.kProcessed, newobj: newobj };
		    }
		    return { status: status, newobj: newobj };
	    }
	return { status: msgStatus.kCreateFailure, newobj: newobj };
    }
}

