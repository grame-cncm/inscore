///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/ITLError.ts"/>

class IBrushStyle {

    protected fBrushModified: boolean;
    fBrush: brushStyle;

    constructor() {
        this.fBrush = brushStyle.kSolid;
        this.fBrushModified = false;
    }

    static brushStyleStr2Num(str: string): { correct: boolean, val: number } {
        switch (str) {
        	case "solid": 	return { correct: true, val: brushStyle.kSolid }
        	case "none": 	return { correct: true, val: brushStyle.kNone }
        } 
        return { correct: false, val: 0 };
    }

    static brushStyleNum2Str(n: number): { correct: boolean, val: string } {
        switch (n) {
        	case brushStyle.kSolid: 	return { correct: true, val: "solid" }
        	case brushStyle.kNone: 	return { correct: true, val: "none" }
        } 
        return { correct: false, val: "" };
    }

    // MODIFIED STATUS
//--------------------------------------------------------------
    cleanup() : void 			{ this.fBrushModified = false; }
    brushModified(): boolean 	{ return this.fBrushModified; }
    modify()  : void 			{ this.fBrushModified = true; }

    getBrushStyle()  : brushStyle 				{ return this.fBrush;}
    _getBrushStyle() : GetStringMethod 			{ return () => IBrushStyle.brushStyleNum2Str(this.getBrushStyle()).val; }

    setBrushStyle (brushStyle : string): void 	{
        let style = IBrushStyle.brushStyleStr2Num(brushStyle);
        if (!style.correct) { ITLError.badParameter("brushStyle", brushStyle);}
        else { this.fBrush = style.val; this.fBrushModified = true; }}
    _setBrushStyle(): SetStringMethod 			{ return (brush : string) => this.setBrushStyle(brush) }
}