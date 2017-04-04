
///<reference path="VHtmlSvgView.ts"/>
///<reference path="../model/IGuidoCode.ts"/>
///<reference path="../externals/libGUIDOEngine.d.ts"/>

interface RefreshMethod { (): void; }

class VHtmlGMNView extends VHtmlSvgView {
	static fGMNScale = 2.3;		// scaling applied to get homogeneous size with inscore app

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

/*    updateView(obj: IObject): void {
        super.updateView(obj);
        if (obj.isNewData()) {
        	
        }
    }
*/
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
}
