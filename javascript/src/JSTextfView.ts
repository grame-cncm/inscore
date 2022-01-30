
///<reference path="JSTextView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSTextfView extends JSTextView {

	toString() : string					{ return "JSTextfView"; }

	updateSpecial(obj: INScoreObject)	: boolean {
			this.setID (obj);
			TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.setHtml(obj, this.getText(text)); 
			}
			else return false;
		});
		return false;
	}
}