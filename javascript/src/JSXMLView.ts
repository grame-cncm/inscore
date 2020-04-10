
///<reference path="JSGMNView.ts"/>
///<reference path="libmusicxml.ts"/>

class JSXMLView extends JSGMNView {

	private fXMLLib: libmusicxml;

	constructor(parent: JSObjectView, xmllib: libmusicxml, guido: GuidoEngine) {
		super(parent, guido);
		this.getElement().className = "inscore-gmn";
		this.fXMLLib = xmllib;
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSXMLView(parent, this.fXMLLib, this.guido()); }

	toString() : string		    { return "JSXMLView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (this.fXMLLib) {
			let xml = obj.getXMLInfos();
			let content = this.fXMLLib.string2guido (xml.code, true);
			return content.length ? this.gmn2svg (obj, content, xml.page) : false;
		}
		else console.log ("libMusicXML not available");
		return false;
    }
}
