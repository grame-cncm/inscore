
///<reference path="JSPianoRollView.ts"/>
///<reference path="TFileLoader.ts"/>
///<reference path="TASyncUpdate.ts"/>

class JSPianoRollfView extends JSPianoRollView {

	toString() : string		    { return "JSPianoRollfView"; }

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (!this.checkGuido()) return false;
		let proll = obj.getPianorollInfos();
		TFileLoader.load (this.getElement(), obj.getFile()).then ( (text) => {
			if (text) {
				return TASyncUpdate.update (oid, (obj) => this.proll2svg(obj, proll, text));
			}
		});
		return false;
	}
}
