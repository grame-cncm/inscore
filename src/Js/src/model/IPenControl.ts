///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="IColor.ts"/>
///<reference path="../lib/TEnums.ts"/>

class IPenControl {
    fPenWidth: number;
    fPenColor: IColor;
    fPenStyle: penStyle;
    fPenAlpha: number;
    
    constructor(type: string) {
        this.fPenWidth = 0;
        if (type == kLineType) { this.fPenWidth = 1; }
        this.fPenColor = new IColor([0, 0, 0, 255])
        this.fPenStyle = penStyle.solid;
        this.fPenAlpha = 255;
    }
    
    getPenWidth(): number   { return this.fPenWidth; }
    getPenColor(): IColor   { return this.fPenColor; }
    getPenStyle(): penStyle { return this.fPenStyle; }
    getPenAlpha(): number   { return this.fPenAlpha; }

    _getPenWidth(): GetNumMethod    { return () => this.fPenWidth; }
    _getPenColor(): GetArrayMethod  { return () => this.fPenColor.getRGB(); }
    _getPenStyle(): GetNumMethod    { return () => this.fPenStyle; }
    _getPenAlpha(): GetNumMethod    { return () => this.fPenAlpha; }

    setPenWidth(penWidth : number)  : void  { this.fPenWidth = penWidth; }
    setPenColor(penColor : IColor)  : void  { this.fPenColor = penColor; }
    setPenStyle(penStyle : penStyle): void  { this.fPenStyle = penStyle; }
    setPenAlpha(penAlpha : number)  : void  { this.fPenAlpha = penAlpha; }

    _setPenWidth(): SetNumMethod    { return (n) => this.setPenWidth(n); }
    _setPenColor(): SetColorMethod  { return (n) => this.fPenColor.setRGB(n); }
    _setPenStyle(): SetNumMethod    { return (n) => this.setPenStyle(n); }
    _setPenAlpha(): SetNumMethod    { return (n) => this.setPenAlpha(n); }
}