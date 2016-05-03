
///<reference path="IObject.ts"/>
///<reference path="../parser/INScoreParser.js"/>

declare var INScoreParser: any;

interface TLoadEndHandler 		{ (): void; }


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
            root.process( msg);
        }    
    }
   protected _process(reader : FileReader, client: IObject) : TLoadEndHandler { 
   		return () => {
       		let data: string = reader.result;
   			this.process(data, client); 
   		}
   	}

    load (file, client: IObject): void {
        let reader: FileReader = new FileReader();
        reader.readAsText(file);
        reader.onloadend = this._process(reader, client);
    }    
}