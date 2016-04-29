
///<reference path="IObject.ts"/>
///<reference path="../parser/INScoreParser.js"/>
///<reference path="../../testHtml/Debug.ts"/>

declare var INScoreParser;

class TILoader {
        
    protected parse(msg: string): Array<any> {
        try {
	        INScoreParser.parse(msg);
	    }
	    catch (e) {
	    	
	    }
        return INScoreParser.msgs;  
    }

   process(buffer: string, root: IObject) {
        let parser = this.parse(buffer);
        for (let i = 0; i < parser.length; i++) {
            let address = parser[i].address.osc;
            let params = parser[i].params;
            let msg = new IMessage(parser[i].address.osc, parser[i].params);
            
            let beg: string = OSCAddress.addressFirst(msg.address());
            let tail: string = OSCAddress.addressTail(msg.address());
            root.processMsg(beg, tail, msg);
            debug();
        }    
    }

    load (file, client: IObject): void {
        let reader: FileReader = new FileReader();
        reader.readAsText(file);
        
        reader.onloadend = function (e) {
            let data: string = reader.result;
            this.process(data, client.getAppl());
        };      
    }    
}