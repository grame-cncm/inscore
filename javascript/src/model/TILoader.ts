
///<reference path="IObject.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../parser/MessageInterface.ts"/>
///<reference path="../scripting/TMessageEvaluator.ts"/>

declare var INScoreParser: any;

interface TLoadEndHandler 		{ (): void; }


class TILoader {
        
    protected parse(msg: string): Array<Message> {
        try {
	        INScoreParser.parse(msg);
        	return INScoreParser.get();  
	    }
	    catch (e) {
//	    	console.log("parse exception");
	    }
        return [];  
    }

	scanParam(param: any) : any {
		if (param.address) {
			// this a message
			console.log ("scanParam message: " + param);
			return new IMessage (param.address, this.scanParams (param.params));			
		}
		else if (param instanceof Array) {
			// this is a message list
			let msgs = new IMessageList();
			param.forEach ( (p: any) : void => { msgs.push(this.scanParam (p)); });
			return msgs;
		}
		return param;
	}

	// scan parameters to build high level objects as parameters
	// this is required for a message to appear as IMessage in the params list
	scanParams(params: Array<any>) : Array<any> {
		console.log ("scanParams : " + params);
		let out: Array<any> = [];
		params.forEach ( (p: any) : void => { out.push (this.scanParam(p)); } );
		return out;
	}

   process(buffer: string, root: IObject) {
        let msgs = this.parse(buffer);
        if (!msgs) return;
		let imsgs : IMessageList = [];
		msgs.forEach ( (msg: Message) : void =>  { //this.scanParams (msg.params); 
			imsgs.push(new IMessage(msg.address.osc, msg.params)) } );

/*
        for (let i = 0; i < msgs.length; i++) {
            let address = msgs[i].address.osc;
            let params = msgs[i].params;
            let msg = new IMessage(msgs[i].address.osc, msgs[i].params);
*/
/*
    	let m : TMouseEnv; let d: Fraction;
    	let env = new TEnv ("", m, d, d, []);
    	let me = new TMessageEvaluator(env);
    	imsgs = me.eval(imsgs);
*/
		imsgs.forEach ( function (msg: IMessage) { INScore.postMessage(msg.address(), msg.params()); } );
    	
//            INScore.checkStatus (root.process( msg), msg);
//        }    
    }

   protected _process(reader : FileReader, client: IObject) : TLoadEndHandler { 
   		return () => {
       		let data: string = reader.result;
   			this.process(data, client); 
   		}
   	}

    load (file: Blob, client: IObject): void {
        let reader: FileReader = new FileReader();
        reader.readAsText(file);
        reader.onloadend = this._process(reader, client);
    }    
}