
///<reference path="JSHtmlView.ts"/>
///<reference path="TFileLoader.ts"/>
///<reference path="TASyncUpdate.ts"/>

class JSHtmlfView extends JSHtmlView {

	toString() : string					{ return "JSHtmlfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return TASyncUpdate.update (oid, (obj) => { this.setHtml(obj, text); return true;} );
			}
			else return false;
		});
		return false;
	}
}