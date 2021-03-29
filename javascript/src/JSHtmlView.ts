
///<reference path="JSAutoSize.ts"/>

class JSHtmlView extends JSAutoSize {

    constructor(parent: JSObjectView) {
		super( document.createElement('div'), parent); 
		this.getElement().className = "inscore-html";
    }
	clone (parent: JSObjectView) : JSObjectView { 
		let obj = new JSHtmlView(parent); 
		obj.getElement().innerHTML = this.getElement().innerHTML;
		return obj;
	}

	toString() : string					{ return "JSHtmlView"; }

	// CSS weight are numbers
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

	updateDimensions(pos: OPosition) {}

	setFont	(font : OTextInfo) : boolean {
		let elt = this.getElement();
		let prev = elt.style.fontSize;
        elt.style.fontSize 		= font.size+"px";
        elt.style.fontFamily 	= font.family;
        elt.style.fontStyle 	= font.style;
		elt.style.fontWeight 	= JSHtmlView.fontWeight2Num(font.weight);
		return elt.style.fontSize != prev;
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

	updateSpecific(obj: INScoreObject)	: void { 
		if (this.setFont (obj.getTextInfos())) {
			this.updateSizeSync (obj);
		}
	}

	updateEvents(events: OEvents, dest: string): void {
		super.updateEvents (events, dest);
		let div = this.getElement();
		if (events.watchMouseEnter || events.watchMouseDown || events.watchMouseDClick) 
			this.getElement().style.cursor = "pointer";
		else 
			this.getElement().style.cursor = "default";
	}

	setHtml (obj: INScoreObject, content: string) : boolean {
		this.getElement().innerHTML = content;
		return this.updateSizeSync(obj);
	}

	getText (text: string) : string { return text }

	updateSpecial ( obj: INScoreObject)	: boolean {		
		let infos = obj.getTextInfos();
		this.setHtml (obj, this.getText(infos.text));
		return true;
	}
}