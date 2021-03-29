
///<reference path="JSHtmlView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSHtmlfView extends JSHtmlView {

	toString() : string					{ return "JSHtmlfView"; }

	updateSpecial(obj: INScoreObject)	: boolean {
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.setHtml(obj, text); 
			}
			else return false;
		});
		return false;
	}
}