
class JSHtmlView extends JSAutoSize {

    constructor(parent) {
		super( document.createElement('div'), parent); 
        this.getElement().className = "inscore-html";
    }

	toString()					{ return "JSHtmlView"; }

	// CSS weight are used as numbers
	static fontWeight2Num	( weight) {
		switch (weight) {
            case "normal": 		return "400";
			case "light":		return "200";
			case "demibold":	return "550";
			case "bold":		return "700";
			case "black":		return "900";
			default: return "400";
		}
	}

	setFont	(font) {
    	let elt = this.getElement();
        elt.style.fontSize 		= font.size+"px";
        elt.style.fontFamily 	= font.family;
        elt.style.fontStyle 	= font.style;
        elt.style.fontWeight 	= JSHtmlView.fontWeight2Num(font.weight);
    }

	setNone ()				{ this.getElement().style.textShadow = "0px 0px 0px";  }
	setBlur (val)  	        { this.getElement().style.textShadow = "0px 0px " + val + "px"; }
	// setShadow (params: Array<number>) : void {
	// 	let color = new IColor( params.slice(2,6) );
	// 	this.getHtml().style.textShadow = color.getCSSRGBAString() + params[0] +"px " + params[1] +"px " + params[6] +"px";
	// }

	updateSpecial ( obj, objid ) {		
        let text = obj.getTextInfos();
    	let elt = this.getElement();
        elt.innerHTML  = text.text;
		this.setFont (text);
		return super.updateSpecial (obj, objid );
	}
}