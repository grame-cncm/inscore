///<reference path="IObject.ts"/>

class IText extends IObject {
    protected fText: string;
	protected fFontSize: number;
	protected fFontFamily: string;
	protected fFontWeight: string;
	protected fFontStyle: string;
	protected fFontModified: boolean
    
    //protected kTextType: string;

    // Constants for font style and font weight.
	static kStyleNormal = "normal" ;
	static kStyleItalic = "italic" ;
	static kStyleOblique = "oblique" ;
	static kWeightNormal = "normal" ;
	static kWeightLight = "light" ;
	static kWeightDemiBold = "demibold" ;
	static kWeightBold = "bold" ;
	static kWeightBlack = "black" ;
        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        //this.kTextType = 'txt';
        this.fTypeString = kTextType;
        
        //Default Parameters
        this.fColor.setRGB([0, 0, 0]);
        this.fColor.setA(255);
        this.fFontSize = 14;
        this.fFontFamily = "Arial"
        this.fFontWeight = IText.kWeightNormal;
	    this.fFontStyle = IText.kStyleNormal;
	    this.fFontModified = false;

     	this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText(this._getText());
        super.setHandlers();
        
        // Method to manage font
        this.fGetMsgHandlerMap[kfontSize_GetSetMethod]      = new TGetMsgHandlerNum(this._getFontSize());
        this.fMsgHandlerMap[kfontSize_GetSetMethod] 	    = new TMsgHandlerNum(this._setFontSize());

        this.fGetMsgHandlerMap[kfontFamily_GetSetMethod]	= new TGetMsgHandlerText(this._getFontFamily());
        this.fMsgHandlerMap[kfontFamily_GetSetMethod]	    = new TMsgHandlerText(this._setFontFamily());

        this.fGetMsgHandlerMap[kfontStyle_GetSetMethod]	    = new TGetMsgHandlerText(this._getFontStyle());
        this.fMsgHandlerMap[kfontStyle_GetSetMethod]	    = new TMethodHandler(this._setFontStyle());

        this.fGetMsgHandlerMap[kfontWeight_GetSetMethod]	= new TGetMsgHandlerText(this._getFontWeight());
        this.fMsgHandlerMap[kfontWeight_GetSetMethod]	    = new TMethodHandler(this._setFontWeight());
    }    

// GETS / SETS VALUES 
//--------------------------------------------------------------    
    fontModified(): boolean         { if(this.fFontModified == false)return this.fEffect.effectModified();else return this.fFontModified; }
    getText(): string               { return this.fText; }
    setText(txt: string): void      { this.fText = txt; }
    
    getFontSize(): number           { return this.fFontSize; }
    setFontSize(s: number): void    { this.fFontSize = s; this.fFontModified = true;}
    
    getFontFamily(): string         { return this.fFontFamily; }
    setFontFamily(f: string): void  { this.fFontFamily = f; this.fFontModified = true; }
    
    getFontStyle(): string          { return this.fFontStyle; } 
    setFontStyle(msg: IMessage): eMsgStatus {
        let n = msg.size();
        if (n == 2) {
            let fontStyle = msg.paramStr(1);
            if(fontStyle.correct) {
                if(fontStyle.value == IText.kStyleNormal || fontStyle.value == IText.kStyleItalic	|| fontStyle.value == IText.kStyleOblique) {
                    this.fFontStyle = fontStyle.value;
                    this.fFontModified = true;
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    }       
    
    getFontWeight(): string         { return this.fFontWeight; }
    setFontWeight(msg: IMessage): eMsgStatus {
        let n = msg.size();
        if (n == 2) {
            let fontWeight = msg.paramStr(1);
            if(fontWeight.correct) {
                if(fontWeight.value == IText.kWeightNormal || fontWeight.value == IText.kWeightLight
                        || fontWeight.value == IText.kWeightDemiBold || fontWeight.value == IText.kWeightBold || fontWeight.value == IText.kWeightBlack) {
                    this.fFontWeight = fontWeight.value;
                    this.fFontModified = true;
                    return eMsgStatus.kProcessed;
                }
            }
        }
        return eMsgStatus.kBadParameters;
    }
    
// GETS / SETS VALUES CLOSURES
//--------------------------------------------------------------    
    _getText(): GetStringMethod         { return () => this.fText; }
    
    _getFontSize() : GetNumMethod       { return () => this.fFontSize; }
    _setFontSize() : SetNumMethod       { return (n) => this.setFontSize(n); }
    
    _getFontFamily() : GetStringMethod  { return () => this.fFontFamily; }
    _setFontFamily() : SetStringMethod  { return (s) => this.setFontFamily(s); }
    
    _getFontStyle() : GetStringMethod   { return () => this.fFontStyle; }
    _setFontStyle() : SetMsgMethod   	{ return (m) => this.setFontStyle(m); }

    _getFontWeight() : GetStringMethod  { return () => this.fFontWeight; }
    _setFontWeight() : SetMsgMethod  	{ return (m) => this.setFontWeight(m); }

// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status; 

        let n = msg.size();
        if (n > 2) {
            let str = "";
            let sep = "";
            for (let i = 2 ; i < n ; i++) {
                str += sep;
            	str += msg.param(i);
            	sep = " ";
            }
            this.setText(str);
            this.newData(true);
            status = eMsgStatus.kProcessed;
        }
        else status = eMsgStatus.kBadParameters;
        return status;
    }

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.fTypeString];
    	return new IMessage(this.getOSCAddress(), a.concat (this.fText) ); 
    }
}