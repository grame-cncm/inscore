
///<reference path="JSGMNView.ts"/>

class JSPianoRollView extends JSGMNView {

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent, guido);
		this.getElement().className = "inscore-pianoroll";
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSPianoRollView(parent, this.guido()); }

	toString() : string		    { return "JSPianoRollView"; }

	date2string (date: ODate) : string 			{ return date.num + "/" + date.denum; }
	getGmn (proll: OPianorollInfos) : string 	{ return proll.code; }

	proll2svg(obj: INScoreObject, proll: OPianorollInfos)	: boolean {
		let ar = this.parse (this.getGmn(proll));
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
			return true;
		}
		return false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		let proll = obj.getPianorollInfos();
		if (this.guido())  {
			if (this.proll2svg (obj, proll)) {
				let bb = this.fSVG.getBBox();
				this.updateObjectSizeSync (obj, bb.width + bb.x, bb.height + bb.y);
				return true;
			}
		}
		else console.log ("Guido engine not available");
		return false;
    }
}
