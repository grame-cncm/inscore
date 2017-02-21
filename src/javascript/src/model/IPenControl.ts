///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="IColor.ts"/>

class IPenControl {
    fPenWidth: number;
    fPenColor: IColor;
    fPenStyle: penStyle;
    fPenAlpha: number;
    
    fPenStylesList_set: { [id: string] : penStyle; } = {};
    fPenStylesList_get: { [id: number] : string; } = {};
    
    constructor(type: string) {
        this.fPenWidth = 0;
        if (type == kLineType) { this.fPenWidth = 1; }
        this.fPenColor = new IColor([0, 0, 0, 255])
        this.fPenStyle = penStyle.solid;
        this.fPenAlpha = 1;
        
        this.buildPenStyle();
    }
    
    buildPenStyle(): void {
        this.fPenStylesList_set["solid"]         = penStyle.solid;
        this.fPenStylesList_set["dash"]          = penStyle.dash;
        this.fPenStylesList_set["dot"]           = penStyle.dot;
        this.fPenStylesList_set["dashDot"]       = penStyle.dashDot;
        this.fPenStylesList_set["dashDotDot"]    = penStyle.dashDotDot;

        this.fPenStylesList_get[penStyle.solid]         = "solid";
        this.fPenStylesList_get[penStyle.dash]          = "dashed";
        this.fPenStylesList_get[penStyle.dot]           = "dotted";
        this.fPenStylesList_get[penStyle.dashDot]       = "dashDot";
        this.fPenStylesList_get[penStyle.dashDotDot]    = "dashDotDot";        
    }
    
    getAlphaString(): string { return 'rgba(' + this.fPenColor.getR() + ', ' +
                                                this.fPenColor.getG() + ', ' +
                                                this.fPenColor.getB() + ', ' +
                                                this.fPenAlpha        + ')' 
    }
    
    getPenWidth(): number   { return this.fPenWidth; }
    getPenColor(): IColor   { return this.fPenColor; }
    getPenStyle(): string   { return this.fPenStylesList_get[this.fPenStyle]; }
    getPenAlpha(): number   { return this.fPenAlpha; }

    _getPenWidth(): GetNumMethod    { return () => this.fPenWidth; }
    _getPenColor(): GetArrayMethod  { return () => this.fPenColor.getRGB(); }
    _getPenStyle(): GetStringMethod    { return () => this.fPenStylesList_get[this.fPenStyle]; }
    _getPenAlpha(): GetNumMethod    { return () => this.fPenAlpha; }

    setPenWidth(penWidth : number)  : void  { this.fPenWidth = penWidth; }
    setPenColor(penColor : IColor)  : void  { this.fPenColor = penColor; }
    setPenStyle(penStyle : string)  : void  { 
        this.fPenStyle = this.fPenStylesList_set[penStyle]; 
        if (!this.fPenStyle && this.fPenStyle != 0) { ITLError.badParameter("penStyle", penStyle);}
    }
    setPenAlpha(penAlpha : number)  : void  { this.fPenAlpha = penAlpha; }

    _setPenWidth(): SetNumMethod    { return (n) => this.setPenWidth(n); }
    _setPenColor(): SetColorMethod  { return (n) => this.fPenColor.setRGB(n); }
    _setPenStyle(): SetStringMethod { return (n) => this.setPenStyle(n); }
    _setPenAlpha(): SetNumMethod    { return (n) => this.setPenAlpha(n); }
}