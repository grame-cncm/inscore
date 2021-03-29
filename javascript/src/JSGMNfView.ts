
///<reference path="JSGMNView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSGMNfView extends JSGMNView { 

	toString() : string		    { return "JSGMNfView"; }

	updateSpecial(obj: INScoreObject)	: boolean {
		if (!this.checkGuido()) return false;
		let guido = obj.getGuidoInfos();
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.gmn2svg(obj, text, guido.page);
			}
			return false;
		});
		return false;
	}
}
