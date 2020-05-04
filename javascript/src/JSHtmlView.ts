
///<reference path="JSAutoSize.ts"/>

class JSHtmlView extends JSAutoSize {

    constructor(parent: JSObjectView) {
		super( document.createElement('div'), parent); 
		this.getElement().className = "inscore-html";
    }
	clone (parent: JSObjectView) : JSObjectView { return new JSHtmlView(parent); }

	toString() : string					{ return "JSHtmlView"; }

	// CSS weight are used as numbers
	static fontWeight2Num	( weight: string) : string {
		switch (weight) {
            case "normal": 		return "400";
			case "light":		return "50";
			case "demibold":	return "600";
			case "bold":		return "800";
			case "black":		return "1000";
			default: return "400";
		}
	}

	setFont	(font : OTextInfo) : void {
    	let elt = this.getElement();
        elt.style.fontSize 		= font.size+"px";
        elt.style.fontFamily 	= font.family;
        elt.style.fontStyle 	= font.style;
		elt.style.fontWeight 	= JSHtmlView.fontWeight2Num(font.weight);
    }

	removeEffect(elt: HTMLElement): void { 
		elt.style.filter = "blur(0px)";
		elt.style.textShadow = "0px 0px";
	}
	setBlur(elt: HTMLElement, val: number): void {
		elt.style.textShadow = "0px 0px";
		elt.style.filter = `blur(${val}px)`;
	}
	setShadow (elt: HTMLElement, val: OShadow) : void {
		elt.style.filter = "blur(0px)";
		elt.style.textShadow = `${val.color} ${val.xOffset}px ${val.yOffset}px ${val.blur}px`;
	}

	// don't update text dimensions
	updateDimensions(pos: OPosition) : void {}

	updateSpecific(obj: INScoreObject)	: void { 
		this.setFont (obj.getTextInfos());
	}

	getText (infos: OTextInfo) : string { return infos.text; }

	updateEvents(events: OEvents, dest: string): void {
		super.updateEvents (events, dest);
		let div = this.getElement();
		if (events.watchMouseEnter || events.watchMouseDown || events.watchMouseDClick) 
			this.getElement().style.cursor = "pointer";
		else 
			this.getElement().style.cursor = "default";
	}

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
		let infos = obj.getTextInfos();
		this.getElement().innerHTML  = this.getText(infos);
		this.setFont (infos);
		super.updateSpecial (obj, objid );
		return true;
	}
}