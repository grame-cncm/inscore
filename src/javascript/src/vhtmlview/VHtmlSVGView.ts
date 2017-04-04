
///<reference path="VHtmlView.ts"/>
///<reference path="../model/ISVG.ts"/>

interface RefreshMethod { (): void; }

class VHtmlSvgView extends VHtmlView {

    protected fClientWidth = 0;
    protected fClientHeight = 0;

    constructor(parent: VHtmlView) {
        super(document.createElement('div'), parent);
        this.getHtml().className = "inscore-svg";
    }

    updateView(obj: IObject): void {
        if (obj.isNewData()) {
            this.getHtml().innerHTML = this.getSVGCode(obj);
            this.updateObjectSize(obj);
        }
        super.updateView(obj);
    }

    getSVGCode(obj: IObject): string {
        let svg = <ISVG>obj;
        return svg.getSvg();
    }

    getsvg(root: Node): SVGSVGElement {
        let g: Node;
        let childs = root.childNodes;
        for (let i = 0; i < childs.length && !g; i++) {
            if (childs[i].nodeName == 'svg') {
                g = childs[i];
                break;
            }
        }
        return <SVGSVGElement>g;
    }

    getClientSize(obj: IObject): { w: number, h: number } {
        if (!this.fClientWidth) {
            let svg = this.getsvg(this.getHtml());
            let box = svg.viewBox.baseVal;
            this.fClientWidth = box.width;
            this.fClientHeight = box.height;
        }
        return { w: this.fClientWidth, h: this.fClientHeight };
    }


    getSize(obj: IObject): { w: number, h: number } {
        let size = this.getClientSize(obj);
        let strokeWidth = obj.fPenControl.getPenWidth();
        let w = size.w + strokeWidth;
        let h = size.h + strokeWidth;
        return { w: (w ? w : 1), h: (h ? h : 1) };
    }
    _updateView(obj: IObject): RefreshMethod { return () => this.updateView(obj); }

    updateObjectSize(obj: IObject): void {
        if (obj.fPosition.getWidth()) return;

        let size = this.getClientSize(obj);
        let w = this.scene2RelativeWidth(size.w);
        let h = this.scene2RelativeHeight(size.h);
        obj.fPosition.setWidth(w);
        obj.fPosition.setHeight(h);
        if (!w || !h) setTimeout(this._updateView(obj), 50);
    }
}