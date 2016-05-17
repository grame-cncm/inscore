
///<reference path="../model/ILine.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSvg.ts"/>

class VHtmlLineView extends VHtmlSvg {

    protected fLine: SVGLineElement;
    protected fPixWidth: number;		// the element width in pixels
    protected fPixHeight: number;		// the element height in pixels
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
    	this.getHtml().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }    

	updateView	( obj: IObject) : void {
		let line = <ILine>obj;
		let p = line.getPoint();
		let x = this.relative2SceneWidth( p.getX() );
		let y = this.relative2SceneHeight( p.getY() );
		let x1 = this.relative2SceneX( p.getX() );
		let y1 = this.relative2SceneX( p.getY() );
//console.log(`VHtmlLineView update: ${p.getX()} ${p.getY()} =>  ${x} ${y} : ${x1} ${y1}`);
    	let elt = this.getHtml();
    	this.fPixWidth = x; // ? x : 1;
    	this.fPixHeight = y; // ? y : 1;
        elt.style.height = this.fPixWidth.toString()+"px";
        elt.style.width  = this.fPixHeight.toString()+"px";
        this.fLine.setAttribute('width', x.toString());
        this.fLine.setAttribute('height', y.toString());
		this.fLine.setAttribute('x1', '0');
        this.fLine.setAttribute('y1', '0');
        this.fLine.setAttribute('x2', x.toString());
        this.fLine.setAttribute('y2', y.toString());
        this.fLine.style.stroke = obj.fColor.getRGBString();
		super.updateView(obj);
	}
	
	getTransform (obj: IObject): string {
		let hw = this.fPixWidth/2;
		let hh = this.fPixHeight/2;
		let dx = -(this.fPixWidth/2)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight/2) * (1 + obj.fPosition.getYOrigin());	
        return super.getTransform(obj) + ` translate(${dx}px, ${dy}px)`;
	}
}