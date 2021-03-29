
///<reference path="JSXMLView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSXMLfView extends JSXMLView {

	toString() : string		    { return "JSXMLfView"; }

	updateSpecial(obj: INScoreObject)	: boolean {
		if (!this.checkxml()) return false;
		let xml = obj.getXMLInfos();
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.xml2gmn(obj, text, xml.page);
			}
			else return false;
		});
		return false;
	}
}
