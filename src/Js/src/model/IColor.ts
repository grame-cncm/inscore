
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="Constants.ts"/>

class IColor {

// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fRGB : Array<number>;
    protected fHSB : Array<number>;
    
    protected fA : number = 255; 
    protected fModified : boolean; 

// CONSTRUTOR
//--------------------------------------------------------------    
    constructor(input : Array<number>|IColor) {
        if (input instanceof Array) { 
        	this.fRGB = input; 
        }
        else if (input instanceof IColor) {
            this.fRGB = input.fRGB;
            this.fA = input.fA;
        }
        this.fHSB = new Array<number>();
        this.fModified = false;
        this.updateHSB();         
    }
  
// MODIFIED STATUS
//--------------------------------------------------------------      
   cleanup(): void { this.fModified = false; }   
   modified(): boolean { return this.fModified; }   
   

// GETS VALUES
//-------------------------------------------------------------- 
    getRGB(): Array<number> { return this.fRGB; }
    getHSB(): Array<number> { return this.fHSB; }
  
	getRGBAString(): string { return `rgba(${this.fRGB[0]}, ${this.fRGB[1]}, ${this.fRGB[2]}, ${this.fRGB[3]})`; }
	getRGBString(): string { return `rgb(${this.fRGB[0]}, ${this.fRGB[1]}, ${this.fRGB[2]})`; }

    
    getR(): number { return this.fRGB[0]; }
    getG(): number { return this.fRGB[1]; } 
    getB(): number { return this.fRGB[2]; } 
       
    getH(): number { return this.fHSB[0]; } 
    getS(): number { return this.fHSB[1]; } 
    getV(): number { return this.fHSB[2]; }      
        
    getA(): number { return this.fA; }

// GETS VALUES CLOSURES
//-------------------------------------------------------------- 
    _getRGB(): GetArrayMethod { return () => this.fRGB; }
    _getHSB(): GetArrayMethod { return () => this.fHSB; }
    
    _getR(): GetNumMethod { return () => this.fRGB[0]; }
    _getG(): GetNumMethod { return () => this.fRGB[1]; } 
    _getB(): GetNumMethod { return () => this.fRGB[2]; } 
       
    _getH(): GetNumMethod { return () => this.fHSB[0]; } 
    _getS(): GetNumMethod { return () => this.fHSB[1]; } 
    _getV(): GetNumMethod { return () => this.fHSB[2]; }      
        
    _getA(): GetNumMethod { return () => this.fA; }
        
// SETS VALUES
//--------------------------------------------------------------         
    
    setParam( param: string , value:number , min:number , max:number , isHSV:boolean ) {
        if ( min <= value && value <= max ) {  
            switch(param) {
                case kcolorHue      : this.fHSB[0] = value; break;
                case kcolorSat      : this.fHSB[1] = value; break;
                case kcolorVal      : this.fHSB[2] = value; break;
                case kcolorRed      : this.fRGB[0] = value; break;
                case kcolorGreen    : this.fRGB[1] = value; break;
                case kcolorBlue     : this.fRGB[2] = value; break;
                case kcolorAlpha    : this.fA = value; break;
                default: console.log ("IColor setParam " + param + " not found");
            }
            this.fModified = true;
            if ( isHSV )	this.updateRGB();
            else			this.updateHSB();
        }
    }
    
    setRGB(val: Array<number>): void 	{ this.fRGB = val; this.updateHSB(); this.fModified = true; }
    setHSB(val: Array<number>): void 	{ this.fHSB = val; this.updateRGB(); this.fModified = true; }
    _setRGB()	: SetColorMethod 		{ return (n) => this.setRGB(n); };
    _setHSB()	: SetColorMethod 		{ return (n) => this.setHSB(n); };
    
    setH(h:number): void 		{ this.setParam(kcolorHue , Math.floor(h), 0, 360, true); }  
    setS(s:number): void 		{ this.setParam(kcolorSat , Math.floor(s), 0, 100, true); }
    setV(b:number): void 		{ this.setParam(kcolorVal , Math.floor(b), 0, 100, true); }
    _setH()	: SetNumMethod 		{ return (n) => this.setH(n); };
    _setS()	: SetNumMethod 		{ return (n) => this.setS(n); };
    _setV()	: SetNumMethod 		{ return (n) => this.setV(n); };

    setR(r:number): void 		{ this.setParam(kcolorRed   , Math.floor(r), 0, 255, false); }
    setG(g:number): void 		{ this.setParam(kcolorGreen , Math.floor(g), 0, 255, false); }
	setB(b:number): void 		{ this.setParam(kcolorBlue  , Math.floor(b), 0, 255, false); }
    _setR()	: SetNumMethod 		{ return (n) => this.setR(n); };
    _setG()	: SetNumMethod 		{ return (n) => this.setG(n); };
    _setB()	: SetNumMethod 		{ return (n) => this.setB(n); };
				
	setA(a:number): void 		{ this.setParam(kcolorAlpha , Math.floor(a), 0, 255, false); }	
    _setA()	: SetNumMethod 		{ return (n) => this.setA(n); };
		
	dA(a:number): void 			{ this.setA( this.getA() + Math.floor(a) ); }	
	dR(r:number): void 			{ this.setR( this.getR() + Math.floor(r) ); }
    dG(g:number): void 			{ this.setG( this.getG() + Math.floor(g) ); }
    dB(b:number): void 			{ this.setB( this.getB() + Math.floor(b) ); }
    dH(h:number): void 			{ this.setH( this.getH() + Math.floor(h) ); }
    dS(s:number): void 			{ this.setS( this.getS() + Math.floor(s) ); }
    dV(b:number): void 			{ this.setB( this.getB() + Math.floor(b) ); }
    _dA()	: SetNumMethod 		{ return (n) => this.dA(n); };
    _dR()	: SetNumMethod 		{ return (n) => this.dR(n); };
    _dG()	: SetNumMethod 		{ return (n) => this.dG(n); };
    _dB()	: SetNumMethod 		{ return (n) => this.dB(n); };
    _dH()	: SetNumMethod 		{ return (n) => this.dH(n); };
    _dS()	: SetNumMethod 		{ return (n) => this.dS(n); };
    _dV()	: SetNumMethod 		{ return (n) => this.dV(n); };
  
    		
// UPDATE COLORS
//--------------------------------------------------------------
    updateRGB(): void { this.hsb2rgb(); }
	updateHSB(): void { this.rgb2hsb(); }

  
// CONVERSIONS COLORS
//--------------------------------------------------------------    
   hsb2rgb():void {
        let H = this.fHSB[0]/360;
        let S = this.fHSB[1]/100;  
        let B = this.fHSB[2]/100; 
        
        let F:number; let M:number;  let N:number;  let K:number; let I:number; 
        if ( S == 0 ) {
            this.fRGB[0] = B;
            this.fRGB[1] = B;
            this.fRGB[2] = B;
        }       
        else {
            if (H >= 1) { H = 0.0; } 
            else { H *= 6; } 
            
            I = Math.floor(H);   
            F = H - I;     

            M = B * (1 - S);
            N = B * (1 - S * F);
            K = B * (1 - S * (1 - F));
           
            switch(I) {
                case 0: this.fRGB[0] = B; this.fRGB[1] = K; this.fRGB[2] = M; break;  
                case 1: this.fRGB[1] = B; this.fRGB[0] = N; this.fRGB[2] = M; break;
                case 2: this.fRGB[0] = M; this.fRGB[1] = B; this.fRGB[2] = K; break;
                case 3: this.fRGB[0] = M; this.fRGB[1] = N; this.fRGB[2] = B; break;
                case 4: this.fRGB[0] = K; this.fRGB[1] = M; this.fRGB[2] = B; break;
                case 5: this.fRGB[0] = B; this.fRGB[1] = M; this.fRGB[2] = N; break;
            }            
            this.fRGB[0] = Math.floor(this.fRGB[0] * 255); 
            this.fRGB[1] = Math.floor(this.fRGB[1] * 255); 
            this.fRGB[2] = Math.floor(this.fRGB[2] * 255);        
        }
    }

   //-----------------------------  
   rgb2hsb():void {
        let r = this.fRGB[0]/255;
        let g = this.fRGB[1]/255;
        let b = this.fRGB[2]/255;

        // Calculation of maxC and minC
        let maxC = Math.max(r, g, b);
        let minC = Math.min(r, g, b);

        // Calculation of delta
        let delta = maxC - minC;
        let H = 0; let S = 0; let B = maxC;

        if (delta == 0) { H=0; S=0;}
        else {
            S = delta / maxC;
            let dR = 60*(maxC - r)/delta + 180;
            let dG = 60*(maxC - g)/delta + 180;
            let dB = 60*(maxC - b)/delta + 180;
            
            if (r == maxC) { H = dB - dG; }
            else if (g == maxC) { H = 120 + dR - dB; }
            else { H = 240 + dG - dR; }            
        }

        if (H<0)	H+=360;
        if (H>=360) H-=360;

        this.fHSB[0] = Math.floor(H);
        this.fHSB[1] = Math.floor(S * 100);
        this.fHSB[2] = Math.floor(B * 100);   
    }   
}
