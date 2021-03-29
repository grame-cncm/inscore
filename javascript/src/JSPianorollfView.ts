
///<reference path="JSPianorollView.ts"/>
///<reference path="TFileLoader.ts"/>

class JSPianoRollfView extends JSPianoRollView {

	toString() : string		    { return "JSPianoRollfView"; }

	updateSpecial(obj: INScoreObject)	: boolean {
		if (!this.checkGuido()) return false;
		let proll = obj.getPianorollInfos();
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return this.proll2svg(obj, proll, text);
			}
			else return false;
		});
		return false;
	}
}
