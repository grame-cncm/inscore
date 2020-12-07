
///<reference path="JSXMLView.ts"/>
///<reference path="TFileLoader.ts"/>
///<reference path="TASyncUpdate.ts"/>

class JSXMLfView extends JSXMLView {

	toString() : string		    { return "JSXMLfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (!this.checkxml()) return false;
		let xml = obj.getXMLInfos();
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return TASyncUpdate.update (oid, (obj) => this.xml2gmn(obj, text, xml.page));
			}
		});
		return false;
	}
}
