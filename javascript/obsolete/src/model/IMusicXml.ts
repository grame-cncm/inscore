
///<reference path="IGuidoCode.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../externals/libmusicxml.d.ts"/>

class IMusicXml extends IGuidoCode {
	static fXMLLib: libMusicXMLAdapter;
    protected fXML: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        if (!IMusicXml.fXMLLib) {
        	var module = MusicXMLModule();
        	IMusicXml.fXMLLib = new module.libMusicXMLAdapter();
        	console.log ("libmusicxml version " + IMusicXml.fXMLLib.libVersionStr() + " using gmn converter version " + IMusicXml.fXMLLib.musicxml2guidoVersionStr());
        }
        this.fTypeString = kMusicxmlType;
        this.fXML = null;
    }
   
    xml2guido(xml: string): boolean {
    	let gmn = IMusicXml.fXMLLib.string2guido(xml, false);
    	if (gmn.length) {
    		this.fGMN = gmn;
    		return true;
    	}
    	return false;
    }
   
    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

		if (msg.size() != 3) return eMsgStatus.kBadParameters;
        let xml = msg.paramStr(2);
		if (!xml.correct) return eMsgStatus.kBadParameters;

		this.fXML = xml.value;
       	if (!this.xml2guido (xml.value))
			return eMsgStatus.kBadParameters;
      	if (!this.str2AR (this.fGMN))
			return eMsgStatus.kBadParameters;
		
		this.fNewData = true;
        return eMsgStatus.kProcessed;
    }
    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fXML]); 
    }    
}