///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IColor.ts"/>

class IPenControl {
    fPenWidth: number;
    fPenColor: IColor;
    fPenStyle: penStyle;
    protected fModified : boolean; 
    
    private static fPenStyleStr2Num: { [id: string] : penStyle; } = {};
    private static fPenStyleNum2Str: { [id: number] : string; } = {};
    
    constructor(type: string) {
        this.fPenWidth = 0;
        if (type == kLineType) { this.fPenWidth = 1; }
        this.fPenColor = new IColor([0, 0, 0, 255]);
        this.fPenStyle = penStyle.kSolid;
        IPenControl.buildPenStyle();
    }
   
// MODIFIED STATUS
//--------------------------------------------------------------      
   	cleanup() : void 	{ this.fModified = false; }
   	modified(): boolean { return this.fModified; }   
   	modify()  : void 	{ this.fModified = true; }
   
    static buildPenStyle(): void {
        IPenControl.fPenStyleStr2Num["solid"]         = penStyle.kSolid;
        IPenControl.fPenStyleStr2Num["dash"]          = penStyle.kDash;
        IPenControl.fPenStyleStr2Num["dot"]           = penStyle.kDot;
        IPenControl.fPenStyleStr2Num["dashDot"]       = penStyle.kDashDot;
        IPenControl.fPenStyleStr2Num["dashDotDot"]    = penStyle.kDashDotDot;

        IPenControl.fPenStyleNum2Str[penStyle.kSolid]         = "solid";
        IPenControl.fPenStyleNum2Str[penStyle.kDash]          = "dashed";
        IPenControl.fPenStyleNum2Str[penStyle.kDot]           = "dotted";
        IPenControl.fPenStyleNum2Str[penStyle.kDashDot]       = "dashDot";
        IPenControl.fPenStyleNum2Str[penStyle.kDashDotDot]    = "dashDotDot";
    }

    static penStyleStr2Num(str: string): { correct: boolean, val: number } {
    	let val = IPenControl.fPenStyleStr2Num[str];
    	return { correct: (typeof val != "undefined"), val: val }
    }
    static penStyleNum2Str(n: number): { correct: boolean, val: string } {
    	let str = IPenControl.fPenStyleNum2Str[n];
    	return { correct: (typeof str != "undefined"), val: str }
    }
    
    getPenWidth()   : number   { return this.fPenWidth; }
    getPenColor()   : IColor   { return this.fPenColor; }
    getPenStyle()   : string   { return ""; } //this.fPenStyleNum2Str[this.fPenStyle]; }
    getPenStyleNum(): number   { return this.fPenStyle; }
    getPenAlpha()   : number   { return this.fPenColor.getA(); }

    _getPenWidth(): GetNumMethod    { return () => this.getPenWidth(); }
    _getPenColor(): GetArrayMethod  { return () => this.getPenColor().getRGB(); }
    _getPenStyle(): GetStringMethod { return () => this.getPenStyle(); }
    _getPenAlpha(): GetNumMethod    { return () => this.getPenAlpha(); }

    setPenWidth(penWidth : number)  : void  { this.fPenWidth = penWidth; this.modify(); }
    setPenColor(penColor : IColor)  : void  { this.fPenColor.set(penColor); this.modify();}
    setPenStyle(penStyle : string)  : void  { 
        let style = IPenControl.penStyleStr2Num (penStyle);
        if (!style.correct) { ITLError.badParameter("penStyle", penStyle);}
        else { this.fPenStyle = style.val; this.modify(); }
    }
    setPenAlpha(penAlpha : number)  : void  { this.fPenColor.setA(penAlpha); this.modify(); }

    _setPenColor(): SetColorMethod  	{ return (n) => this.setPenColor(new IColor(n)); }
    _setPenAlpha(): SetNumMethod    	{ return (n) => this.setPenAlpha(n); }
    _setPenWidth(): SetNumMethod    	{ return (n) => this.setPenWidth(n); }
    _setPenStyle(): SetStringMethod 	{ return (n) => this.setPenStyle(n); }
}