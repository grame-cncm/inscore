///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IColor.ts"/>

class IPenControl {
    fPenWidth: number;
    fPenColor: IColor;
    fPenStyle: penStyle;
    fPenAlpha: number;
    protected fModified : boolean; 
    
    fPenStyleStr2Num: { [id: string] : penStyle; } = {};
    fPenStyleNum2Str: { [id: number] : string; } = {};
    
    constructor(type: string) {
        this.fPenWidth = 0;
        if (type == kLineType) { this.fPenWidth = 1; }
        this.fPenColor = new IColor([0, 0, 0, 255])
        this.fPenStyle = penStyle.solid;
        this.fPenAlpha = 1;
        
        this.buildPenStyle();
    }
   
// MODIFIED STATUS
//--------------------------------------------------------------      
   	cleanup(): void 	{ this.fModified = false; }   
   	modified(): boolean { return this.fModified; }   
   	modify(): void 		{ this.fModified = true; }   
   
    buildPenStyle(): void {
        this.fPenStyleStr2Num["solid"]         = penStyle.solid;
        this.fPenStyleStr2Num["dash"]          = penStyle.dash;
        this.fPenStyleStr2Num["dot"]           = penStyle.dot;
        this.fPenStyleStr2Num["dashDot"]       = penStyle.dashDot;
        this.fPenStyleStr2Num["dashDotDot"]    = penStyle.dashDotDot;

        this.fPenStyleNum2Str[penStyle.solid]         = "solid";
        this.fPenStyleNum2Str[penStyle.dash]          = "dashed";
        this.fPenStyleNum2Str[penStyle.dot]           = "dotted";
        this.fPenStyleNum2Str[penStyle.dashDot]       = "dashDot";
        this.fPenStyleNum2Str[penStyle.dashDotDot]    = "dashDotDot";        
    }
    
    getAlphaString(): string { return 'rgba(' + this.fPenColor.getR() + ', ' +
                                                this.fPenColor.getG() + ', ' +
                                                this.fPenColor.getB() + ', ' +
                                                this.fPenAlpha        + ')' 
    }
    
    getPenWidth(): number   { return this.fPenWidth; }
    getPenColor(): IColor   { return this.fPenColor; }
    getPenStyle(): string   { return this.fPenStyleNum2Str[this.fPenStyle]; }
    getPenStyleNum(): number { return this.fPenStyle; }
    getPenAlpha(): number   { return this.fPenAlpha; }

    _getPenWidth(): GetNumMethod    { return () => this.fPenWidth; }
    _getPenColor(): GetArrayMethod  { return () => this.fPenColor.getRGB(); }
    _getPenStyle(): GetStringMethod    { return () => this.fPenStyleNum2Str[this.fPenStyle]; }
    _getPenAlpha(): GetNumMethod    { return () => this.fPenAlpha; }

    setPenWidth(penWidth : number)  : void  { this.fPenWidth = penWidth; this.modify(); }
    setPenColor(penColor : IColor)  : void  { this.fPenColor = penColor; this.modify(); }
    setPenStyle(penStyle : string)  : void  { 
        let style = this.fPenStyleStr2Num[penStyle]; 
        if (!style && style != 0) { ITLError.badParameter("penStyle", penStyle);}
        else { this.fPenStyle = style; this.modify(); }
    }
    setPenAlpha(penAlpha : number)  : void  { this.fPenAlpha = penAlpha; this.modify(); }

    _setPenWidth(): SetNumMethod    { return (n) => this.setPenWidth(n); }
    _setPenColor(): SetColorMethod  { return (n) => this.fPenColor.setRGB(n); }
    _setPenStyle(): SetStringMethod { return (n) => this.setPenStyle(n); }
    _setPenAlpha(): SetNumMethod    { return (n) => this.setPenAlpha(n); }
}