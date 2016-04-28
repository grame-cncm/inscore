
///<reference path="IObject.ts"/>

declare var INScoreParser;

class TILoader {
        
    protected process(buffer: string, root: IObject) {
        let parser = this.parse(buffer);
        for (var i = 0; i < parser.length; i++) {
            var address = parser[i].address.osc;
            var params = parser[i].params;
            let msg = new IMessage(parser[i].address.osc, parser[i].params);
            
            var beg: string = OSCAddress.addressFirst(msg.address());
            var tail: string = OSCAddress.addressTail(msg.address());
            root.processMsg(beg, tail, msg);
        }    
    }
    
    protected parse(msg: string): Array<any> {
        INScoreParser.parse(msg);
        return INScoreParser.msgs;  
    }

    load (file, client: IObject): void {
        var reader: FileReader = new FileReader();
        reader.readAsText(file);
        
        reader.onloadend = function (e) {
            var data: string = reader.result;
            this.process(data, client.getAppl());
        };      
    }    
}