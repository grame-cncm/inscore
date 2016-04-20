declare var INScoreParser;

class TILoader {
    
    constructor() {}
    
    process(buffer: string) {
        var parser = this.parse(buffer);
        for (var i = 0; i < parser.length; i++) {
            var address = parser[i].address.osc;
            var params = parser[i].params;
            var msg = new IMessage(address, params);
            
            var beg: string = OSCAddress.addressFirst(msg.address());
            var tail: string = OSCAddress.addressTail(msg.address());
            appl.processMsg(beg, "/scene1/obj2", msg);
        }    
    }
    
    load(file, loader: TILoader) {
        var reader: FileReader = new FileReader();
        reader.readAsText(file);
        
        reader.onloadend = function (e) {
            var data: string = reader.result;
            loader.process(data);
        };
        
    }
    
    parse(msg: string): Array<any> {
        INScoreParser.parse(msg);
        return INScoreParser.msgs;  
    }
}