
///<reference path="JSSVGBase.ts"/>
///<reference path="guidoengine.ts"/>

interface SArray {
	[index: string]: string;
}

class JSGMNView extends JSSvgBase {

	private fGuido: GuidoEngine;
	private fParser: GuidoParser;
	private fAR: ARHandler;
	private fGR: GRHandler;
	private fPage = 0;
	private fMaps: SArray = {};

	private scanMap (name: string)	: { name: string, index: number } { 
		let n = name.match(/([a-z]+)(\d+)/);
		if (!n) return { name: "", index: 0 };
		return {name: n[1], index: parseInt(n[2]) };
	}

	private scanViewBox (vbox: string)	: { width: number, height: number } { 
		let n = vbox.match(/(\d+) (\d+) (\d+) (\d+)/);
		if (!n) return { width: 0, height: 0 };
		return {width: parseInt(n[3]), height: parseInt(n[4]) };
	}

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent);
		this.getElement().className = "inscore-gmn";
		this.fGuido = guido;
		this.fGR = null;
		this.fAR = null;
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
			
			let innerSvg = this.fSVG.getElementsByTagName('svg');
			let viewbox = this.scanViewBox (innerSvg[0].getAttribute('viewBox'));	
			this.updateObjectSizeSync (obj, viewbox.width, viewbox.height);
			obj.updateTime2TimeMap (this.fGuido.getTimeMap (ar));

			if (this.fGR) {
				this.fGuido.freeGR(this.fGR);
				this.fGuido.freeAR(this.fAR);
			}
			this.fMaps = {};
			this.fGR = gr;
			this.fAR = ar;
			this.fPage = page;
			return true;
		}
		return false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		let guido = obj.getGuidoInfos();
		if (this.fGuido)
			return this.gmn2svg (obj, guido.code, guido.page);
		else console.log ("Guido engine not available");
		return false;
    }

	private getMap (mapname: string, width: number, height: number) : string
	{
		if (mapname == "page")
			return this.fGuido.getPageMap(this.fGR, this.fPage, width, height );
		if (mapname == "system")
			return this.fGuido.getSystemMap(this.fGR, this.fPage, width, height );
		let m = this.scanMap (mapname);
		if (m.name == "staff") 
			return this.fGuido.getStaffMap (this.fGR, this.fPage, width, height, m.index);
		else if (m.name == "voice") 
			return this.fGuido.getVoiceMap (this.fGR, this.fPage, width, height, m.index);
		return null;
	}

	updateSpecific (obj: INScoreObject)	: void { 
		if (!this.fGR) return;

		let guido = obj.getGuidoInfos();
		let maps = guido.mappings;
		for (let i=0; i< maps.size(); i++) {
			let mapname = maps.get(i);
			if (mapname.length) {
				if (this.fMaps[mapname]) continue;		// already done;
				
				let w = this.fSVG.clientWidth;
				let h = this.fSVG.clientHeight;
				let map = this.getMap (mapname, w, h);
				if (map && map.length) {
					obj.updateGraphic2TimeMap (mapname, map, w, h);
					this.fMaps[mapname] = map;
				}
			}
		}		
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
	// getFirstGroup(root: Node): SVGSVGElement {
	getFirstGroup(root: SVGSVGElement): SVGSVGElement {
		let g = root.getElementsByTagName('g');
		return <SVGSVGElement>g[0];
	}
}
