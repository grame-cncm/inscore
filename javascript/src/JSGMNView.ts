
///<reference path="JSSVGView.ts"/>
///<reference path="guidoengine.ts"/>

class JSGMNView extends JSSvgView {

	private fGuido: GuidoEngine;
	private fParser: GuidoParser;

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent);
		this.getElement().className = "inscore-gmn";
		this.fGuido = guido;
		if (guido) this.fParser = guido.openParser();
	}

	getSVGTarget() : SVGShape   { return this.fSVG; }
	toString() : string		    { return "JSGMNView"; }
	updateSVGDimensions(w: number, h: number) : void { }

	// gives the size of the element from it's viewport
	getSize (svg: string) : Point { 
		let w = svg.replace (/^..*="0 0 ([0-9]+)..*/, "$1");
		let h = svg.replace (/^..*="0 0 [0-9]+ ([0-9]+)..*/, "$1");
		return { x: parseInt(w), y: parseInt(h) };
	}

	gmn2svg(obj: INScoreObject, gmn: string, page: number)	: boolean {
		let ar = this.fGuido.string2AR (this.fParser, gmn);
		if (ar) {
			let gr = this.fGuido.ar2gr (ar);
			let svg = this.fGuido.gr2SVG (gr, page, false, 0);
			this.fSVG.innerHTML = svg;
			this.fGuido.freeGR(gr);
			this.fGuido.freeAR(ar);

			// update object size
			let p = this.getSize(svg.substr(svg.indexOf ("viewBox"), 50));
			this.updateObjectSizeSync (obj, p.x, p.y);
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
