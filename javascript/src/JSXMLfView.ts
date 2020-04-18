
///<reference path="JSXMLView.ts"/>
///<reference path="TFileBased.ts"/>

class JSXMLfView extends JSXMLView {

	fContent = new TFileBased;

	toString() : string		    { return "JSXMLfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
        let address = obj.getOSCAddress();
        let inscore = gGlue.inscore();
        let pending = (): void => { inscore.postMessageStr (address, "refresh"); };
		if (this.fContent.getData (obj.getFile(), this.getElement(), pending)) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	getXml (unused: OScore) : string {
		let xml = this.fContent.get(); 
		return xml ? xml : ""; 
	}
}
