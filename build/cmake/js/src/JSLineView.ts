
///<reference path="JSSVGView.ts"/>

class JSLineView extends JSSvgView {

    protected fLine: SVGLineElement;
	fWidth: number;
	fHeight: number;

	constructor(parent: JSObjectView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
        this.getElement().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }    

    getSVGTarget() : SVGShape  { return this.fLine; }
	toString() : string		   { return "JSLineView"; }

	updateSVGDimensions(w: number, h: number) : void { }

	updateDimensions(pos: OPosition) : void {
    	// let w = this.relative2SceneWidth(pos.width);
		// let h = this.relative2SceneHeight(pos.height);
		// this.updateSVGDimensions (w, h);
		let strokewidth = pos.pen.penWidth;
		this.fSVG.style.width  = (this.fWidth + strokewidth) + "px";
		this.fSVG.style.height = (this.fHeight + strokewidth) + "px";
	  }

	getPos(pos: OPosition) : Point {
	console.log (this + " obj dims: " + pos.width + " " + pos.height);
		let p = super.getPos (pos);
		console.log (this + " pos: " + p.x + " " + p.y);
		return p;
	}

// 	updateObjectSize (objid : number) : void {
// 		let obj = INScore.objects().create(objid);
// 		let r = this.fLine.getBoundingClientRect();
// console.log(this + " updateObjectSize: w:" + r.width + " vs " + this.fWidth + " h: " + r.height + " vs " + this.fHeight);
// 		obj.updateWidth  (this.scene2RelativeWidth  (this.fWidth)); 
// 		obj.updateHeight (this.scene2RelativeHeight (this.fHeight)); 
// 		// obj.updateWidth  (this.scene2RelativeWidth  (this.fWidth)); 
// 		// obj.updateHeight (this.scene2RelativeHeight (this.fHeight)); 
// 		INScore.objects().del (obj);		
// 	}

	updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
		let line = obj.getLineInfos();
		let x1 = this.relative2SceneWidth (line.x1);
		let y1 = this.relative2SceneHeight (line.y1);
		let x2 = this.relative2SceneWidth (line.x2);
		let y2 = this.relative2SceneHeight (line.y2);

		this.fLine.setAttribute('x1', x1.toString());
		this.fLine.setAttribute('x2', x2.toString());
		this.fLine.setAttribute('y1', y1.toString());
		this.fLine.setAttribute('y2', y2.toString());
		return super.updateSpecial (obj, objid );
	}

	// updateSpecial ( obj: INScoreObject, objid: number)	: boolean {		
	// 	let line = obj.getLineInfos();
	// 	let x = this.relative2SceneWidth (line.x);
	// 	let y = this.relative2SceneWidth (line.y);
	// 	this.fWidth = x ? x : 1;
	// 	this.fHeight = y ? y : 1;
	// 	let x0 = 0;
	// 	let y0 = 0;

	// 	if ((x < 0) && (y < 0)) {
	// 		x = -x;
	// 		y = -y;
	// 	} else if (x < 0) {
	// 		y0 = y;
	// 		x = -x;
	// 		y = 0;
	// 	}
	// 	else if (y < 0) {
	// 		y0 = -y;
	// 		y = 0;
	// 	}

	// 	this.fLine.setAttribute('x1', x0.toString());
	// 	this.fLine.setAttribute('x2', x.toString());
	// 	this.fLine.setAttribute('y1', y0.toString());
	// 	this.fLine.setAttribute('y2', y.toString());

	// 	let infos = obj.getUpdateInfos();
	// 	// obj.updateWidth  (this.scene2RelativeWidth  (this.fWidth)); 
	// 	// obj.updateHeight (this.scene2RelativeHeight (this.fHeight)); 
	// 	return super.updateSpecial (obj, objid );
	// }

}