
///<reference path="JSTextView.ts"/>
///<reference path="TFileLoader.ts"/>
///<reference path="TASyncUpdate.ts"/>

class JSTextfView extends JSTextView {

	toString() : string					{ return "JSTextfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
			TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return TASyncUpdate.update (oid, (obj) => { this.setHtml(obj, this.getText(text)); return true;} );
			}
			else return false;
		});
		return false;
	}
}