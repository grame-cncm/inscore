class IPosition {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fXPos : number;
    protected fYPos : number;
    protected fXOrigin : number;
    protected fYOrigin : number;
    protected fWidth : number;
    protected fHeight : number;
    protected fZOrder : number;
    protected fVisible: boolean;
    protected fScale : number;
    protected fModified : boolean;
    protected fXAngle : number;
    protected fYAngle : number;
    protected fZAngle : number; 
    protected fShear : Array<number>;
    
    public kDefaultX : number = 0;
    public kDefaultY : number = 0;

// CONSTRUTOR
//--------------------------------------------------------------    
    constructor() {
        this.fXPos = this.kDefaultX; 
        this.fYPos = this.kDefaultY;
        this.fXOrigin = 0;
        this.fYOrigin = 0;
        this.fWidth = 0; 
        this.fHeight = 0;
        this.fZOrder = 0;
        this.fVisible = true; 
        this.fScale = 1.0;  
        this.fModified = true;
        this.fXAngle = 0;
        this.fYAngle = 0; 
        this.fZAngle = 0;
        this.fShear =  [0,0];
    } 
    
// MODIFIED STATUS
//--------------------------------------------------------------          
    modified(): boolean { return this.fModified; }
    modify(): void { this.fModified = true; }  
    cleanup():void { this.fModified = false; }
    
// GETS
//--------------------------------------------------------------
    getXPos(): number { return this.fXPos; }
    getYPos(): number { return this.fYPos; }
    getXOrigin(): number { return this.fXOrigin; }
    getYOrigin(): number { return this.fYOrigin; }
    getZOrder(): number { return this.fZOrder; }
    getScale(): number { return this.fScale; }
    getPos(): Array<number> { 
        var pos: Array<number> = new Array (this.fXPos , this.fYPos) 
        return pos 
        }
        
    getRotateX(): number { return this.fXAngle; }
    getRotateY(): number { return this.fYAngle; }
    getRotateZ(): number { return this.fZAngle; } 
       
    getWidth(): number { return this.fWidth; }
    getHeight(): number { return this.fHeight; }
    getDimension(): Array<number> { 
        var dimension: Array<number> = new Array (this.fWidth , this.fHeight) 
        return dimension 
        }
   
    getVisible(): boolean { return this.fVisible; }
    
    
// SETS 
//--------------------------------------------------------------    
    setPos(p:IPosition): void {
        this.setXPos( p.getXPos() );
        this.setYPos( p.getYPos() );
        this.setZOrder( p.getZOrder() );
        this.setScale( p.getScale() );
        this.setRotateX(p.getRotateX() );
        this.setRotateY( p.getRotateY() );
        this.setRotateZ( p.getRotateZ() );
        this.setWidth( p.getWidth() );
        this.setHeight( p.getHeight() );
        this.setVisible( p.getVisible() );
    }
    
    setWidth(width:number): void { this.fWidth = width; }
    setHeight(height:number): void { this.fHeight = height; }
    
    setXPos(x:number): void { this.fXPos = x; this.fModified = true; }
    addXpos(x:number): void { this.setXPos(this.fXPos + x); }
    
    setXOrigin(x:number): void { this.fXOrigin = x; this.fModified = true; }
    addXOrigin(x:number): void { this.setXOrigin (this.fXOrigin + x); }
    
    setYPos(y:number): void { this.fYPos = y; this.fModified = true; }
    addYpos(y:number): void { this.setYPos(this.fYPos + y); }
    
    setYOrigin(y:number): void { this.fYOrigin = y; this.fModified = true; }
    addXYrigin(y:number): void { this.setYOrigin (this.fYOrigin + y); }   
 
    setScale (scale:number): void { this.fScale = scale; this.fModified = true; }
    mulScale (scale:number): void { this.setScale(this.fScale * scale); }
        
    setVisible (vis:boolean): void { this.fVisible = vis; this.fModified = true; }

    setZOrder(z:number): void { this.fZOrder = z; this.fModified = true; }
    addZOrder(z:number): void { this.setZOrder(this.fZOrder + z); }
    
    addAngle(angle:number): void { this.setRotateZ(this.fZAngle + angle); }
    addXAngle(angle:number): void { this.setRotateX(this.fXAngle + angle); }
    addYAngle(angle:number): void { this.setRotateY(this.fYAngle + angle); }
        
    setRotateX(a:number): void { this.fXAngle = a; }
    setRotateY(a:number): void { this.fYAngle = a; }
    setRotateZ(a:number): void { this.fZAngle = a; }   
    
    setShear(s:Array<number>): void { this.fShear = s; }           
       
}