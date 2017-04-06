
///<reference path="VHtmlSVGView.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod { (): void; }

class VHtmlGMNView extends VHtmlSvgView {
	static fGMNScale = 2.3;		// scaling applied to get homogeneous size with inscore app

	fMapScaleX: number = 1;
	fMapScaleY: number = 1;

	constructor(parent: VHtmlView) {
		super(parent);
		this.getHtml().className = "inscore-gmn";
	}

	getViewScale(obj: IObject): number {
		// apply scaling to get a size similar to native application
		return super.getViewScale(obj) * VHtmlGMNView.fGMNScale;
	}

	getSVGCode(obj: IObject): string {
		let gmn = <IGuidoCode>obj;
		return gmn.getSVG();
	}

	getFirstSVGGroup(root: Node): SVGSVGElement {
		let g: Node;
		let childs = root.childNodes;
		for (let i = 0; i < childs.length && !g; i++) {
			if (childs[i].nodeName == 'g') {
				g = childs[i];
				break;
			}
			g = this.getFirstSVGGroup(childs[i]);
		}
		return <SVGSVGElement>g;
	}

	updateView(obj: IObject): void {
		super.updateView (obj);
		this.fMapScaleX = (this.fWidth >= this.fHeight) ? 1 : this.fHeight / this.fWidth;
		this.fMapScaleY = (this.fWidth >= this.fHeight) ? this.fWidth / this.fHeight : 1;
		
	}

	updateColor(obj: IObject): void {
		let color = obj.fColor.getRGBString();
		let alpha = obj.fColor.getSVGA();
		let g = this.getFirstSVGGroup(this.getHtml());
		if (g) {
			g.style.stroke = color;
			g.style.strokeOpacity = alpha.toString();
			g.style.fill = color;
			g.style.fillOpacity = alpha.toString();
		}
	}
	
	//  specific map functions: on model side, a guido map is computed as a square box.
	//  while rendering is not almost never square.
	map2SceneX(x: number): number 		{ return this.fWidth  * x * this.fMapScaleX; }
	map2SceneY(y: number): number 		{ return this.fHeight * y * this.fMapScaleY; }

	scene2MapX(x: number): number 		{ return x / this.fWidth / this.fMapScaleX / VHtmlGMNView.fGMNScale; }
	scene2MapY(y: number): number 		{ return y / this.fHeight/ this.fMapScaleY / VHtmlGMNView.fGMNScale; }

	// updates the local mapping (do nothing at IObject level) 
	//	updateLocalMapping (obj: IObject ): void;
}
