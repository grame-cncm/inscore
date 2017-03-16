///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/TEnums.ts"/>

class IEffect {
    fEffectModified: boolean;
    fEffectType  : eEffect;
    fEffectParams: Array<number>;

    private static fEffectStr2Num: { [id: string] : eEffect; } = {};
    private static fEffectNum2Str: { [id: number] : string; } = {};
    private static fEffectParamsNum: Array<number> = [];		// expected parameters count

    constructor() {
        this.fEffectModified = false;
        this.fEffectType = eEffect.kNone;
        this.fEffectParams= [];
        IEffect.buildEffect();
    }

    static buildEffect(): void {
        IEffect.fEffectStr2Num["none"]          = eEffect.kNone;
        IEffect.fEffectStr2Num["blur"]          = eEffect.kBlur;
        IEffect.fEffectStr2Num["colorize"]      = eEffect.kColorize;
        IEffect.fEffectStr2Num["shadow"]        = eEffect.kShadow;

        IEffect.fEffectNum2Str[eEffect.kNone]    = "none";
        IEffect.fEffectNum2Str[eEffect.kBlur]    = "blur";
        IEffect.fEffectNum2Str[eEffect.kColorize]= "colorize";
        IEffect.fEffectNum2Str[eEffect.kShadow]  = "shadow";

        IEffect.fEffectParamsNum[eEffect.kNone]    = 0;
        IEffect.fEffectParamsNum[eEffect.kBlur]    = 1;
        IEffect.fEffectParamsNum[eEffect.kColorize]= 4;
        IEffect.fEffectParamsNum[eEffect.kShadow]  = 7;
    }

    static effectStr2Num(str: string): { correct: boolean, val: number } {
        let val = IEffect.fEffectStr2Num[str];
        return { correct: (typeof val != "undefined"), val: val }
    }
    static effectNum2Str(n: number): { correct: boolean, val: string } {
        let str = IEffect.fEffectNum2Str[n];
        return { correct: (typeof str != "undefined"), val: str }
    }

    // MODIFIED STATUS
//--------------------------------------------------------------
    type(): eEffect 				{ return this.fEffectType; }
    params(): Array<number> 	{ return this.fEffectParams; }
    param(i: number): number 	{ return this.fEffectParams[i]; }

    cleanup(): void 			{ this.fEffectModified = false; }
    effectModified(): boolean 	{ return this.fEffectModified; }
    modify() : void 			{ this.fEffectModified = true; }

    getEffect()  : Array<any> 		 { 
    	let out = new Array<any>();
	    out[0] = IEffect.fEffectNum2Str[this.fEffectType];
    	return out.concat(this.fEffectParams); 
    }
    _getEffect() : GetArrayMethod 	 { return () => this.getEffect(); }

    isNumberArray(a: Array<any>): boolean 	{ 
    	for (let i=0; i< a.length; i++)
		  	if (typeof a[i] != "number") return false;
    	return true; 
    }
    
    assignParams (type: number, params: Array<any>) : eMsgStatus {
		if (! this.isNumberArray (params)) 						return eMsgStatus.kBadParameters;
		if (params.length != IEffect.fEffectParamsNum[type])  	return eMsgStatus.kBadParameters;
		this.fEffectType   = type;
		this.fEffectParams = params;
		this.modify();
		return eMsgStatus.kProcessed;
    }

    setEffect (params : Array<any>): eMsgStatus 	{
        let style = IEffect.effectStr2Num (params[1]);
        if (!style.correct) return eMsgStatus.kBadParameters;
        else return this.assignParams(style.val, params.slice(2));
    }
    _setEffect(): SetAnyArrayMethod { return (effect : Array<any>) => this.setEffect(effect) }
}
