
///<reference path="JSGMNView.ts"/>
///<reference path="lib/libmusicxml.ts"/>

class JSXMLView extends JSGMNView {

	private fXMLLib: libmusicxml;

	constructor(parent: JSObjectView, xmllib: libmusicxml, guido: GuidoEngine) {
		super(parent, guido);
		this.getElement().className = "inscore-gmn";
		this.fXMLLib = xmllib;
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSXMLView(parent, this.fXMLLib, this.guido()); }

	toString() : string		    	{ return "JSXMLView"; }

	checkxml() { 
		if (this.fXMLLib) return true;
		console.log ("libMusicXML is not available");
		return false;
	}
	
	xml2gmn (obj: INScoreObject, content: string, page: number) : boolean
	{
		let gmn = this.fXMLLib.string2guido (content, true);
		return gmn.length ? this.gmn2svg (obj, gmn, page) : false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (this.checkxml()) {
			let xml = obj.getXMLInfos();
			return this.xml2gmn (obj, xml.code, xml.page);
		}
		return false;
    }
}
