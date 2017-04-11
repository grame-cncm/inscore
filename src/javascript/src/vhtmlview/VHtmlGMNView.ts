
///<reference path="VHtmlSVGView.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

class VHtmlGMNView extends VHtmlSvgView {

	fMapScale: scaleMethod;

	constructor(parent: VHtmlView) {
		super(parent);
		this.getHtml().className = "inscore-gmn";
		this.fMapScale = null;
	}

	setMapScaleHandler	( f: scaleMethod ) : void { this.fMapScale = f; }

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

	//------------------------------------------------------------------------------------
	setPos(top: number, left: number, width: number, height: number): void {
		super.setPos (top, left, width, height);
		if (this.fMapScale) {
			let x = 1;
			let y = 1;
			if (this.fWidth > this.fHeight) 		y = this.fWidth / this.fHeight;
			else if (this.fWidth < this.fHeight) 	x =  this.fHeight / this.fWidth;
			this.fMapScale(x, y);
			this.fMapScale = null;
		}
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

	// updates the local mapping (do nothing at IObject level) 
	//	updateLocalMapping (obj: IObject ): void;
}
