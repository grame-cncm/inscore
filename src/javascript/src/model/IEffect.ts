///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/TEnums.ts"/>

class IEffect {
    fEffectModified: boolean;
    fEffectName  : effect;
    fEffectArray : Array<any>;
    fShadow      : Array<number>;  //set shadow x and y
    fShadowBlur   : number;
    fBlur        : number;         //set blur
    fColorize    : IColor;         //set color of shadow
    fColorPerCent: number;         //set color perCent for colorize

    private static fEffectStr2Num: { [id: string] : effect; } = {};
    private static fEffectNum2Str: { [id: number] : string; } = {};

    constructor() {
        this.fEffectModified = false;
        this.resetSetting();
        IEffect.buildEffect();
    }

    static buildEffect(): void {
        IEffect.fEffectStr2Num["none"]          = effect.kNone;
        IEffect.fEffectStr2Num["blur"]          = effect.kBlur;
        IEffect.fEffectStr2Num["colorize"]      = effect.kColorize;
        IEffect.fEffectStr2Num["shadow"]        = effect.kShadow;

        IEffect.fEffectNum2Str[effect.kNone]    = "none";
        IEffect.fEffectNum2Str[effect.kBlur]    = "blur";
        IEffect.fEffectNum2Str[effect.kColorize]= "colorize";
        IEffect.fEffectNum2Str[effect.kShadow]  = "shadow";
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
    cleanup(): void 			{ this.fEffectModified = false; }
    effectModified(): boolean 	{ return this.fEffectModified; }
    modify() : void 			{ this.fEffectModified = true; }

    getEffect()  : Array<any> 		 {  return this.fEffectArray}
    _getEffect() : GetArrayMethod 	 { return () => this.getEffect(); }

    assignParams(effectArray: Array<any>) {
       switch (effectArray[1]) {
           case IEffect.effectNum2Str(effect.kNone).val :
               if(effectArray.length  == 2) {
                   this.fEffectName   = effect.kNone;
                   this.resetSetting();
               }else ITLError.badParameter("effect", effectArray);
               break;
           case IEffect.effectNum2Str(effect.kBlur).val :
               if(effectArray.length == 3) {
                   this.fEffectName = effect.kBlur;
                   this.fBlur = effectArray[2];
                   this.fEffectArray = [this.fBlur];
               }else ITLError.badParameter("effect", effectArray);
               break;
           case IEffect.effectNum2Str(effect.kColorize).val :
               if(effectArray.length == 6) {
                   this.fEffectName  = effect.kColorize;
                   this.fColorPerCent= effectArray[2];
                   this.fColorize    = new IColor([effectArray[3], effectArray[4], effectArray[5]]);
                   this.fEffectArray = [this.fColorPerCent,this.fColorize];
               }else ITLError.badParameter("effect", effectArray);
               break;
           case IEffect.effectNum2Str(effect.kShadow).val :
               if(effectArray.length == 9) {
                   this.fEffectName = effect.kShadow;
                   this.fShadow = [effectArray[2], effectArray[3]];
                   this.fColorize = new IColor([effectArray[4], effectArray[5], effectArray[6], effectArray[7]/255]);
                   this.fShadowBlur = effectArray[8];
                   this.fEffectArray = [this.fColorize,this.fShadow,this.fShadowBlur];
               }else ITLError.badParameter("effect", effectArray);
               break;
           default: ITLError.badParameter("effect", effectArray);
       }
    }

    resetSetting(){
        this.fEffectName = effect.kNone;
        this.fEffectArray= [];
        this.fShadow     = [0, 0];
        this.fShadowBlur = 0;
        this.fBlur       = 0;
        this.fColorPerCent= 0;
        this.fColorize   = new IColor([0, 0, 0, 1]);
    }

    setEffect (effect : Array<any>): msgStatus 	{
        let style = IEffect.effectStr2Num(effect[1]);
        if (!style.correct) { ITLError.badParameter("effect", effect);}
        else this.modify(); this.assignParams(effect); return msgStatus.kProcessed;
    }
    _setEffect(): SetAnyArrayMethod { return (effect : Array<any>) => this.setEffect(effect) }
}