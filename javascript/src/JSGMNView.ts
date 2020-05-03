
///<reference path="JSSVGBase.ts"/>
///<reference path="guidoengine.ts"/>

class JSGMNView extends JSSvgBase {

	private fGuido: GuidoEngine;
	private fAR: ARHandler = null;
	private fGR: GRHandler = null;
	private fPage = 0;
	protected fParser: GuidoParser;

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
	ready() : boolean			{ return this.fGR != null; }
	delete() : void	{ 
		if (this.fGR) {
			this.fGuido.freeGR(this.fGR);
			this.fGuido.freeAR(this.fAR);
			this.fGR = null;
			this.fAR = null;
		}
		this.fGuido.closeParser (this.fParser);
		this.fParser = null;
		super.delete();
	}

	updatePenControl(pen: OPen) : void {	this.updateRegularPen (pen); }

	parse(gmn: string)	: ARHandler { return this.fGuido.string2AR (this.fParser, gmn); }
	string2Ar (obj: INScoreObject, gmn: string) : ARHandler { return this.parse (gmn); }

	gmn2svg(obj: INScoreObject, gmn: string, page: number)	: boolean {
		let ar = this.string2Ar (obj, gmn);
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
			else {
				let address = obj.getOSCAddress();
				this.refresh (address);
			}
			this.fGR = gr;
			this.fAR = ar;
			this.fPage = page;
			return true;
		}
		else console.error (obj.getOSCAddress() + " failed to parse gmn code.")
		return false;
	}

	updateSpecial(obj: INScoreObject, oid: number)	: boolean {
		let guido = obj.getGuidoInfos();
		if (this.fGuido)
			return this.gmn2svg (obj, guido.code, guido.page);
		else console.log ("Guido engine is not available");
		return false;
    }
	
	// this method is called by the model to update the map synchronously
	static getMapping (mapname: string, id: number, oid: number) : void {
    	let view = <JSGMNView>JSObjectView.getObjectView(id);
    	if (view) {
			let obj = INScore.objects().create(oid);
			let w = view.getSVGTarget().clientWidth;
			let h = view.getSVGTarget().clientHeight;
			let map = view.getMap (mapname, w, h);
			obj.updateGraphic2TimeMap (mapname, map, w, h);
			INScore.objects().del (obj);
		}
	}

	getMap (mapname: string, width: number, height: number) : string
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
