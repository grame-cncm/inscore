
///<reference path="VHtmlSvg.ts"/>
///<reference path="../model/ICurve.ts"/>

class VHtmlCurveView extends VHtmlSvg {
    protected fCurve: SVGPathElement;
    
    constructor(parent: VHtmlView) {
		super(parent);
        this.fCurve = document.createElementNS('http://www.w3.org/2000/svg','path'); 
        this.getHtml().className = "inscore-curve";
    	this.fSVG.appendChild(this.fCurve) 
    } 

	updateView	( obj: IObject) : void {
		let curve = <ICurve>obj;
        let BezierCurves: Array<BezierCurve> = curve.getPoints();
        for (let i = 0; i < BezierCurves.length; i++) {
            let points: Array<number> = BezierCurves[i].points()
            let a1 = this.relative2SceneX(points[0]);
            let a2 = this.relative2SceneY(points[1]);
            let b1 = this.relative2SceneX(points[2]);
            let b2 = this.relative2SceneY(points[3]);
            let c1 = this.relative2SceneX(points[4]);
            let c2 = this.relative2SceneY(points[5]);
            let d1 = this.relative2SceneX(points[6]);
            let d2 = this.relative2SceneY(points[7]);

            this.fCurve.setAttribute('d', 'M' + a1 + ',' + a2 + ' '
                                        + 'q' + b1 + ',' + b2 + ' '    
                                              + c1 + ',' + c2 + ' ' 
                                        + 't' + d1 + ',' + d2);
        }

            let curveSize = this.fCurve.getBBox();
            this.updateSvgPos (curveSize.x, curveSize.y);  
            this.updateSvgSize (curveSize.width, curveSize.height);
       
        for (let i = 0; i < BezierCurves.length; i++) {
            let points: Array<number> = BezierCurves[i].points()
            let a1 = this.relative2SceneX(points[0]) - curveSize.x;
            let a2 = this.relative2SceneY(points[1]) - curveSize.y;
            let b1 = this.relative2SceneX(points[2]) - curveSize.x;
            let b2 = this.relative2SceneY(points[3]) - curveSize.y;
            let c1 = this.relative2SceneX(points[4]) - curveSize.x;
            let c2 = this.relative2SceneY(points[5]) - curveSize.y;
            let d1 = this.relative2SceneX(points[6]) - curveSize.x;
            let d2 = this.relative2SceneY(points[7]) - curveSize.y;

            this.fCurve.setAttribute('d', 'M' + a1 + ',' + a2 + ' '
                                        + 'q' + b1 + ',' + b2 + ' '    
                                              + c1 + ',' + c2 + ' ' 
                                        + 't' + d1 + ',' + d2);
        }        
            this.updateObjectSize (obj);
            this.fCurve.style.fill = obj.fColor.getRGBString();        
            
      /*  
        let scale = obj.fPosition.getScale();
		let w = this.relative2SceneWidth( obj.fPosition.getWidth() ) * scale;
		let h = this.relative2SceneHeight( obj.fPosition.getHeight() ) * scale;
    	this.updateSvgSize (w, h);
      
        this.fCurve.setAttribute('width', w.toString());
        this.fCurve.setAttribute('height', h.toString());
        this.fCurve.style.fill = obj.fColor.getRGBString();
		let rx = w/2;
		let ry = h/2;
        //this.fCurve.setAttribute('cx', rx.toString());
        //this.fCurve.setAttribute('cy', ry.toString());
        //this.fCurve.setAttribute('rx', rx.toString());
        //this.fCurve.setAttribute('ry', ry.toString());
		this.updatePos(obj);
    */ 
	}  

	updateSvgPos (x: number, y: number): void { 
        console.log(x+ ' '+y)
    	let elt = this.getHtml();		
		elt.style.left = x +"px";
        elt.style.top  = y +"px";
		this.fSVG.style.left = x +"px";
        this.fSVG.style.top  = y +"px";
	}  

	updateObjectSize ( obj: IObject) : void {
        let w = this.scene2RelativeWidth(this.fSVG.clientWidth);
        let h = this.scene2RelativeHeight(this.fSVG.clientHeight);
        let x = this.scene2RelativeHeight(this.fSVG.clientLeft);
        let y = this.scene2RelativeHeight(this.fSVG.clientTop);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
		obj.fPosition.setXPos (x);
		obj.fPosition.setYPos (y);
    }	            
}