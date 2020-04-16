
///<reference path="JSGMNView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSGMNfView extends JSGMNView {
	fContent = "";

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent, guido);
		console.log (this + " constructor");
	}
	toString() : string		    { return "JSGMNfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (this.fContent) return super.updateSpecial (obj, oid);
		let file = obj.getFile();
		let address = obj.getOSCAddress();
		TFileLoader.load (this.getElement(), obj.getFile()).then ((text: string) => { 
            this.fContent = text;
            gGlue.inscore().postMessageStr (address, "refresh");
		});
		return false;
	}

	gmn2svg (obj: INScoreObject, gmn: string, page: number)	: boolean {
		let content = this.fContent;
		this.fContent = "";
		return super.gmn2svg (obj, content, page);
	}

}
