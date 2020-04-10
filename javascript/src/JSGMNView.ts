
///<reference path="JSSVGBase.ts"/>
///<reference path="guidoengine.ts"/>

class JSGMNView extends JSSvgBase {

	private fGuido: GuidoEngine;
	private fParser: GuidoParser;

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent);
		this.getElement().className = "inscore-gmn";
		this.fGuido = guido;
		if (guido) this.fParser = guido.openParser();
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSGMNView(parent, this.fGuido); }

	getSVGTarget() : SVGShape   { return this.fSVG; }
	toString() : string		    { return "JSGMNView"; }
	updateSVGDimensions(w: number, h: number) : void { }
	guido() : GuidoEngine		{ return this.fGuido; }


	parse(gmn: string)	: ARHandler { return this.fGuido.string2AR (this.fParser, gmn); }

	gmn2svg(obj: INScoreObject, gmn: string, page: number)	: boolean {
		let ar = this.parse (gmn);
		if (ar) {
			let gr = this.fGuido.ar2gr (ar);
			let svg = this.fGuido.gr2SVG (gr, page, false, 0);
			this.fSVG.innerHTML = svg;
			this.fGuido.freeGR(gr);
			this.fGuido.freeAR(ar);

			let bb = this.fSVG.getBBox();
			this.updateObjectSizeSync (obj, bb.width + bb.x, bb.height + bb.y);
			return true;
		}
		return false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		let guido = obj.getGuidoInfos();
		if (this.fGuido)  return this.gmn2svg (obj, guido.code, guido.page);
		else console.log ("Guido engine not available");
		return false;
    }

	updateColor(color: OColor) : void {
		let g = this.getFirstGroup(this.fSVG);
		if (g) {
			g.style.stroke = color.rgb;
			g.style.strokeOpacity = color.alpha.toString();
			g.style.fill = color.rgb;
			g.style.fillOpacity = color.alpha.toString();
		}
	}

	//------------------------------------------------------------------------------------
	// utilities
	getFirstGroup(root: Node): SVGSVGElement {
		let g: Node;
		let childs = root.childNodes;
		for (let i = 0; i < childs.length && !g; i++) {
			if (childs[i].nodeName == 'g') {
				g = childs[i];
				break;
			}
			g = this.getFirstGroup(childs[i]);
		}
		return <SVGSVGElement>g;
	}
}
