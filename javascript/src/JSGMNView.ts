
///<reference path="JSSVGBase.ts"/>
///<reference path="lib/guidoengine.ts"/>
///<reference path="navigator.ts"/>

class JSGMNView extends JSSvgBase {

	private fGuido: GuidoEngine;
	private fAR: ARHandler = null;
	private fGR: GRHandler = null;
	private fPage = 0;
	private fScalingFactor = 2.3;
	private fViewBox : { width: number, height: number };
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
	private viewBox ()	: { width: number, height: number } { return this.fViewBox; }

	constructor(parent: JSObjectView, guido: GuidoEngine) {
		super(parent);
		this.getElement().className = "inscore-gmn";
		this.fGuido = guido;
		this.fGR = null;
		this.fAR = null;
		if (guido) this.fParser = guido.openParser();
		if (WindowsOS) 	 this.fScalingFactor = 1.7;
		else if (UnixOS) this.fScalingFactor = 1.7;
		else if (AndroidOS) this.fScalingFactor = 1.7;
	}
	clone (parent: JSObjectView) : JSObjectView { return new JSGMNView(parent, this.fGuido); }

	getSVGTarget() : SVGShape   { return this.fSVG; }
	toString() : string		    { return "JSGMNView"; }
	updateSVGDimensions(w: number, h: number) : void { }
	guido() : GuidoEngine		{ return this.fGuido; }
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

	// scaled to get a size similar to native app
	parentScale() : number { return this.getParent().parentScale() * this.fScalingFactor; }

	gmn2svg(obj: INScoreObject, gmn: string, page: number)	: boolean {
		let ret = false;
		let ar = this.string2Ar (obj, gmn);
		if (ar) {
			let gr = this.fGuido.ar2gr (ar);
			let svg = this.fGuido.gr2SVG (gr, page, false, 0);
			this.fSVG.innerHTML = svg;
			
			let innerSvg = this.fSVG.getElementsByTagName('svg');
			this.fViewBox = this.scanViewBox (innerSvg[0].getAttribute('viewBox'));	
			this.updateObjectSizeSync (obj, this.fViewBox.width, this.fViewBox.height);
			obj.updateTime2TimeMap (this.fGuido.getTimeMap (ar));

			if (this.fGR) {
				this.fGuido.freeGR(this.fGR);
				this.fGuido.freeAR(this.fAR);
			}
			this.fGR = gr;
			this.fAR = ar;
			this.fPage = page;
			ret = true;
		}
		else console.error (obj.getOSCAddress() + " failed to parse gmn code.")
		obj.ready();
		return ret;
	}

	checkGuido() : boolean {
		if (!this.fGuido) {
			console.log ("Guido engine is not available");
			return false;
		}
		return true;
	}
	
	updateSpecial(obj: INScoreObject)	: boolean {
		if (!this.checkGuido()) return false;
		let guido = obj.getGuidoInfos();
		return this.gmn2svg (obj, guido.code, guido.page);
    }
	
	// this method is called by the model to update the map synchronously
	static getMapping (mapname: string, id: number, oid: number) : void {
		let view = <JSGMNView>JSObjectView.getObjectView(id);
    	if (view) {
			let obj = INScore.objects().adapter(oid);
			let vb = view.viewBox();
			let w = vb.width; 
			let h = vb.height;
			let map = view.getMap (mapname, w, h);
			obj.updateGraphic2TimeMap (mapname, map, w, h);
		}
	}

	getMap (mapname: string, width: number, height: number) : string
	{
		if (mapname == "page")
			return this.fGuido.getPageMap(this.fGR, this.fPage, width, height );
		if (mapname == "system")
			return this.fGuido.getSystemMap(this.fGR, this.fPage, width, height );
		if (mapname == "") 
			return this.fGuido.getStaffMap (this.fGR, this.fPage, width, height, 1);

			let m = this.scanMap (mapname);
		if (m.name == "staff")
			return this.fGuido.getStaffMap (this.fGR, this.fPage, width, height, m.index);
		if (m.name == "voice") 
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
