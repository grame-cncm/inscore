
///<reference path="../controller/TSetMessageHandlers.ts"/>

class IColor {

// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fR : number = 0;
    protected fG : number = 0;
    protected fB : number = 0;
    protected fH : number;
    protected fS : number;
    protected fV : number;
    protected fA : number = 255; 
    protected fModified : boolean; 
    
    public fSetColorMsgHandler: SetColorMsgHandler; 
    
// CONSTRUTOR
//--------------------------------------------------------------    
    constructor(r:number|IColor , g:number, b:number) {
        if (typeof r === "number") {
            this.fR = r;
            this.fG = g;
            this.fB = b;
        }
        
        else if (r instanceof IColor) {
            this.fR = r.fR;
            this.fG = r.fG;
            this.fB = r.fB;
            this.fA = r.fA;
        }

        this.fModified = true;
        this.updateHSV(); 
        
        this.fSetColorMsgHandler = new SetColorMsgHandler();    
    }
  
// MODIFIED STATUS
//--------------------------------------------------------------      
   cleanup(): void { this.fModified = false; }   
   

// GETS VALUES
//-------------------------------------------------------------- 
    getR(): number { return this.fR; }
    getG(): number { return this.fG; } 
    getB(): number { return this.fB; } 
       
    getH(): number { return this.fH; } 
    getS(): number { return this.fS; } 
    getV(): number { return this.fV; }      
        
    getA(): number { return this.fA; }
        
// SETS VALUES
//--------------------------------------------------------------         
    
    setParam( param: string , value:number , min:number , max:number , isHSV:boolean ) {
        
        if ( min <= value && value <= max ) {  
            switch(param) {
                case "fH" : this.fH = value; break;
                case "fS" : this.fS = value; break;
                case "fV" : this.fV = value; break;
                case "fR" : this.fR = value; break;
                case "fG" : this.fG = value; break;
                case "fB" : this.fB = value; break;
                case "fA" : this.fA = value; break;
            }
           
            this.fModified = true;
            if ( isHSV )
                this.updateRGB();
            else
                this.updateHSV();
        }
    }
    
    setH(h:number): void { this.setParam("fH" , Math.floor(h), 0, 360, true); }  
    setS(s:number): void { this.setParam("fS", Math.floor(s), 0, 100, true); }
    setV(v:number): void { this.setParam("fV", Math.floor(v), 0, 100, true); }

    setR(r:number): void { this.setParam("fR", Math.floor(r), 0, 255, false); }
    setG(g:number): void { this.setParam("fG", Math.floor(g), 0, 255, false); }
	setB(b:number): void { this.setParam("fB", Math.floor(b), 0, 255, false); }
				
	setA(a:number): void { this.setParam("fA", Math.floor(a), 0, 255, false); }	
		
	dA(a:number): void { this.setA( this.getA() + Math.floor(a) ); }	
	dR(r:number): void { this.setR( this.getR() + Math.floor(r) ); }
    dG(g:number): void { this.setG( this.getG() + Math.floor(g) ); }
    dB(b:number): void { this.setB( this.getB() + Math.floor(b) ); }
    dH(h:number): void { this.setH( this.getH() + Math.floor(h) ); }
    dS(s:number): void { this.setS( this.getS() + Math.floor(s) ); }
    dV(v:number): void { this.setV( this.getV() + Math.floor(v) ); }
  
    		
// UPDATE COLORS
//--------------------------------------------------------------
    updateRGB(): void { this.hsv2rgb(); }
	updateHSV(): void { this.rgb2hsv(); }

  
// CONVERSIONS COLORS
//--------------------------------------------------------------    
   hsv2rgb():void {
        var H:number = this.fH/360;
        var S:number = this.fS/100;  
        var V:number = this.fV/100; 
        
        var F:number; var M:number;  var N:number;  var K:number; var I:number; 
    
        if ( S == 0.0 ) {
            this.fR = V;
            this.fG = V;
            this.fB = V;
        } 
        
        else {
 
            if (H >= 1) { H = 0.0; } 
            else { H *= 6; } 
            
            I = Math.floor(H);   
            F = H - I;     

            M = V * (1 - S);
            N = V * (1 - S * F);
            K = V * (1 - S * (1 - F));
           
            switch(I) {
                case 0: this.fR = V; this.fG = K; this.fB = M; break;  
                case 1: this.fG = V; this.fR = N; this.fB = M; break;
                case 2: this.fR = M; this.fG = V; this.fB = K; break;
                case 3: this.fR = M; this.fG = N; this.fB = V; break;
                case 4: this.fR = K; this.fG = M; this.fB = V; break;
                case 5: this.fR = V; this.fG = M; this.fB = N; break;
            }
            
            this.fR = Math.floor(this.fR * 255); 
            this.fG = Math.floor(this.fG * 255); 
            this.fB = Math.floor(this.fB * 255);        
        } 
    }
   //-----------------------------  
   rgb2hsv():void {
        var r:number = this.fR/255;
        var g:number = this.fG/255;
        var b:number = this.fB/255;

        // Calculation of maxC and minC
        var maxC:number = Math.max(r, g, b);
        var minC:number = Math.min(r, g, b);

        // Calculation of delta
        var delta:number = maxC - minC;

        var H:number = 0; var S:number = 0; var V:number = maxC;


        if (delta == 0) { H=0; S=0;}
        
        else {
            S = delta / maxC;
            var dR:number = 60*(maxC - r)/delta + 180;
            var dG:number = 60*(maxC - g)/delta + 180;
            var dB:number = 60*(maxC - b)/delta + 180;
            
            if (r == maxC) { H = dB - dG; }
                
            else if (g == maxC) { H = 120 + dR - dB; }
                
            else { H = 240 + dG - dR; }            
        }

        if (H<0)
            H+=360;
        if (H>=360)
            H-=360;
            
        this.fH = Math.floor(H);
        this.fS = Math.floor(S * 100);
        this.fV = Math.floor(V * 100);   
    }   
}
