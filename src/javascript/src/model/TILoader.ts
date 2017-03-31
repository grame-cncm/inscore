
///<reference path="IObject.ts"/>
///<reference path="../globals.ts"/>
///<reference path="../parser/MessageInterface.ts"/>

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

   process(buffer: string, root: IObject) {
        let msgs = this.parse(buffer);
        if (!msgs) return;
        for (let i = 0; i < msgs.length; i++) {
            let address = msgs[i].address.osc;
            let params = msgs[i].params;
            let msg = new IMessage(msgs[i].address.osc, msgs[i].params);         
            INScore.checkStatus (root.process( msg), msg);
        }    
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