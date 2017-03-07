///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>

class IBrushStyle{

    fBrushModified: boolean;
    fBrush: brushStyle;

    constructor() {
        this.fBrush = brushStyle.solid;
        this.fBrushModified = false;
        IBrushStyle.buildBrushStyle();
    }

    static fBrushStyleStr2Num(str: string): { correct: boolean, val: number } {
        let val = IBrushStyle.fBrushStyleStr2Num[str];
        return { correct: (typeof val != "undefined"), val: val }
    }
    static fBrushStyleNum2Str(n: number): { correct: boolean, val: string } {
        let str = IBrushStyle.fBrushStyleNum2Str[n];
        return { correct: (typeof str != "undefined"), val: str }}

    static buildBrushStyle(): void {
        IBrushStyle.fBrushStyleStr2Num["solid"] = brushStyle.solid;
        IBrushStyle.fBrushStyleStr2Num["none"]  = brushStyle.none;

        IBrushStyle.fBrushStyleNum2Str[brushStyle.solid] = "solid";
        IBrushStyle.fBrushStyleNum2Str[brushStyle.none]  = "none";
    }

    // MODIFIED STATUS
//--------------------------------------------------------------
    cleanup() : void 	{ this.fBrushModified = false; }
    brushModified(): boolean { return this.fBrushModified; }
    modify()  : void 	{ this.fBrushModified = true; }

    getBrushStyle()  : brushStyle 				{ return this.fBrush;}
    _getBrushStyle() : GetStringMethod 			{ return () => IBrushStyle.fBrushStyleNum2Str[this.getBrushStyle()] }

    setBrushStyle (brushStyle : string): void 	{
        let style = IBrushStyle.fBrushStyleStr2Num(brushStyle);
        if (!style.correct) { ITLError.badParameter("brushStyle", brushStyle);}
        else { this.fBrush = style.val; this.fBrushModified = true; }}
    _setBrushStyle(): SetStringMethod 			{ return (brush : string) => this.setBrushStyle(brush) }
}