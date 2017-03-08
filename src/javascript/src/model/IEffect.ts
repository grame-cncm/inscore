///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/TEnums.ts"/>

class IEffect {
    protected fEffectModified: boolean;
    fEffectName : effect;
    fEffect     : Array<any>;
    fShadow     : Array<number>;  //set shadow x and y
    fBlur       : number;         //set blur
    fColorize   : IColor;         //set color of shadow

    private static fEffectStr2Num: { [id: string] : effect; } = {};
    private static fEffectNum2Str: { [id: number] : string; } = {};

    constructor() {
        this.fEffectModified = false;
        this.fEffectName = effect.kNone;
        this.fShadow     = [0, 0];
        this.fBlur       = 0;
        this.fColorize   = new IColor([0, 0, 0, 255]);
        this.fEffect     = [this.fShadow, this.fColorize, this.fBlur];
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

    effectCraft(shadow : Array<number>, color : IColor, blur : number)
    {
        this.fEffect = [shadow, color.getRGBAString(), blur];
    }
    // MODIFIED STATUS
//--------------------------------------------------------------
    cleanup(): void 			{ this.fEffectModified = false; }
    effectModified(): boolean 	{ return this.fEffectModified; }
    modify() : void 			{ this.fEffectModified = true; }

    getEffect()  : Array<any> 		 { return this.fEffect;}
    _getEffect() : GetArrayMethod 	 { return () => this.getEffect(); }
/*
    set(msg: IMessage): msgStatus {
       switch (msg.params()[1]) {
           case effect.kNone : break;
           case effect.kBlur : this.fBlur = msg.params()[2]; break;
           case effect.kColorize: this.fColorize = new IColor([msg.params()[2],msg.params()[3],msg.params()[4],msg.params()[5]]); break;
           case effect.kShadow :
               this.fShadow = [msg.params()[2],msg.params()[3]];
               this.fColorize = new IColor([msg.params()[4],msg.params()[5],msg.params()[6],msg.params()[7]]);
               this.fBlur = msg.params()[8];
               break;
           default: return msgStatus.kBadParameters;
       }
    }
*/
    setEffect (effect : Array<any>): msgStatus 	{
        console.log("IEffect setEffect " + effect);
        return msgStatus.kProcessed;
/*
        let style = IEffect.effectStr2Num(effect[1]);
        if (!style.correct) { ITLError.badParameter("effect", effect);}
        else { return msgStatus.kProcessed; this.fEffectModified = true; }
*/
    }
    _setEffect(): SetAnyArrayMethod { return (effect : Array<any>) => this.setEffect(effect) }
}