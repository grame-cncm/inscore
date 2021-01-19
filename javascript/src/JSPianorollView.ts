
///<reference path="JSGMNView.ts"/>

class JSPianoRollView extends JSGMNView {

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent, guido);
		this.getElement().className = "inscore-pianoroll";
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSPianoRollView(parent, this.guido()); }

	toString() : string		    { return "JSPianoRollView"; }

	proll2svg(obj: INScoreObject, proll: OPianorollInfos, gmn: string)	: boolean {
		let ar = this.parse (gmn); //(this.getGmn(proll));
		if (ar) {
			let guido = this.guido();
			let pr = guido.ar2PianoRoll (PianoRollType.kSimplePianoRoll, ar);
			guido.prEnableKeyboard (pr, proll.keyboard);
			guido.prEnableMeasureBars (pr, proll.bars);
			guido.prEnableAutoVoicesColoration (pr, proll.autovoicecolor);
			let l = proll.limits;
			let limits = { 	startDate: {num: l.start.num, denom: l.start.denum }, 
							endDate: {num: l.end.num, denom: l.end.denum }, 
							lowPitch: l.lowpitch, highPitch: l.highpitch };
			guido.prSetLimits( pr, limits );
			let svg = this.guido().proll2svg (pr, 400, 200);
			this.fSVG.innerHTML = svg;
			this.guido().destroyPianoRoll(pr);
			this.guido().freeAR(ar);
			obj.ready();
			return true;
		}
		return false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		if (!this.checkGuido()) return false;
		let proll = obj.getPianorollInfos();
		return this.proll2svg (obj, proll, proll.code);
    }
}
