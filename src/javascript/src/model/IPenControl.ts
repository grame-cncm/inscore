///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IColor.ts"/>

class IPenControl {
    fPenWidth: number;
    fPenColor: IColor;
    fPenStyle: ePenStyle;
    protected fModified : boolean; 
    
    private static fPenStyleStr2Num: { [id: string] : ePenStyle; } = {};
    private static fPenStyleNum2Str: { [id: number] : string; } = {};
    
    constructor(type: string) {
        this.fPenWidth = 0;
        if (type == kLineType) { this.fPenWidth = 1; }
        this.fPenColor = new IColor([0, 0, 0, 255]);
        this.fPenStyle = ePenStyle.kSolid;
        IPenControl.buildPenStyle();
    }
   
// MODIFIED STATUS
//--------------------------------------------------------------      
   	cleanup() : void 	{ this.fModified = false; }
   	modified(): boolean { return this.fModified; }   
   	modify()  : void 	{ this.fModified = true; }
   
    static buildPenStyle(): void {
        IPenControl.fPenStyleStr2Num["solid"]         = ePenStyle.kSolid;
        IPenControl.fPenStyleStr2Num["dash"]          = ePenStyle.kDash;
        IPenControl.fPenStyleStr2Num["dot"]           = ePenStyle.kDot;
        IPenControl.fPenStyleStr2Num["dashDot"]       = ePenStyle.kDashDot;
        IPenControl.fPenStyleStr2Num["dashDotDot"]    = ePenStyle.kDashDotDot;

        IPenControl.fPenStyleNum2Str[ePenStyle.kSolid]         = "solid";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDash]          = "dashed";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDot]           = "dotted";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDashDot]       = "dashDot";
        IPenControl.fPenStyleNum2Str[ePenStyle.kDashDotDot]    = "dashDotDot";
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

    setPenWidth(penWidth : number)  : void  { this.fPenWidth = penWidth; this.modify(); }
    setPenColor(penColor : IColor)  : void  { this.fPenColor.set(penColor); this.modify();}
    setPenStyle(ePenStyle : string)  : void  { 
        let style = IPenControl.penStyleStr2Num (ePenStyle);
        if (!style.correct) { ITLError.badParameter("ePenStyle", ePenStyle);}
        else { this.fPenStyle = style.val; this.modify(); }
    }
    setPenAlpha(penAlpha : number)  : void  { this.fPenColor.setA(penAlpha); this.modify(); }
}