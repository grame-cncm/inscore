
///<reference path="JSXMLView.ts"/>
///<reference path="TFileBased.ts"/>

class JSXMLfView extends JSXMLView {

	fContent = new TFileBased;

	toString() : string		    { return "JSXMLfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (this.fContent.getData (obj.getFile(), this.getElement())) 
			return super.updateSpecial (obj, oid);
		return false;
	}

	getXml (unused: OScore) : string {
		let xml = this.fContent.get(); 
		return xml ? xml : ""; 
	}
}
