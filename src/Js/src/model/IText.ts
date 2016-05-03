///<reference path="IObject.ts"/>

class IText extends IObject {
    protected fText: string;
	protected fFontSize: number;
	protected fFontFamily: string;
	protected fFontWeight: string;
	protected fFontStyle: string;
    
    protected kTextType: string;

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
        this.kTextType = 'txt';
        this.fTypeString = this.kTextType;
        
        //Default Parameters
        this.fColor.setRGB([0, 0, 0]);
        this.fColor.setA(255);
        this.fFontSize = 14;
        this.fFontFamily = "Arial"
        this.fFontWeight = IText.kWeightNormal;
	    this.fFontStyle = IText.kStyleNormal;

     	this.fGetMsgHandlerMap[""] = new TGetMsgHandlerText(this._getText());
        super.setHandlers();
        
        // Method to manage font
        this.fGetMsgHandlerMap[kfontSize_GetSetMethod]      = new TGetMsgHandlerNum(this._getFontSize());
        this.fMsgHandlerMap[kfontSize_GetSetMethod] 	    = new TMsgHandlerNum(this._setFontSize());

        this.fGetMsgHandlerMap[kfontFamily_GetSetMethod]	= new TGetMsgHandlerText(this._getFontFamily());
        this.fMsgHandlerMap[kfontFamily_GetSetMethod]	    = new TMsgHandlerText(this._setFontFamily());

        this.fGetMsgHandlerMap[kfontStyle_GetSetMethod]	    = new TGetMsgHandlerText(this._getFontStyle());
        this.fMsgHandlerMap[kfontStyle_GetSetMethod]	    = new TMsgHandlerText(this._setFontStyle());

        this.fGetMsgHandlerMap[kfontWeight_GetSetMethod]	= new TGetMsgHandlerText(this._getFontWeight());
        this.fMsgHandlerMap[kfontWeight_GetSetMethod]	    = new TMsgHandlerText(this._setFontWeight());
    }    

// GETS / SETS VALUES 
//--------------------------------------------------------------    
    getText(): string               { return this.fText; }
    setText(txt: string): void      { this.fText = txt; }
    
    getFontSize(): number           { return this.fFontSize; }
    setFontSize(s: number): void    { this.fFontSize = s; }
    
    getFontFamily(): string         { return this.fFontFamily; }
    setFontFamily(f: string): void  { this.fFontFamily = f; }
    
    getFontStyle(): string          { return this.fFontStyle; } 
    setFontStyle(msg: IMessage): msgStatus {
        let n = msg.size();
        if (n == 1) {
            let fontStyle = msg.paramStr(0);
            if(fontStyle.correct) {
                if(fontStyle.value == IText.kStyleNormal || fontStyle.value == IText.kStyleItalic	|| fontStyle.value == IText.kStyleOblique) {
                    this.fFontStyle = fontStyle.value;
                    return msgStatus.kProcessed;
                }
            }
        }
        return msgStatus.kBadParameters;
    }       
    
    getFontWeight(): string         { return this.fFontWeight; }
    setFontWeight(msg: IMessage): msgStatus {
        let n = msg.size();
        if (n == 1) {
            let fontWeight = msg.paramStr(0);
            if(fontWeight.correct) {
                if(fontWeight.value == IText.kWeightNormal || fontWeight.value == IText.kWeightLight
                        || fontWeight.value == IText.kWeightDemiBold || fontWeight.value == IText.kWeightBold || fontWeight.value == IText.kWeightBlack) {
                    this.fFontWeight = fontWeight.value;
                    return msgStatus.kProcessed;
                }
            }
        }
        return msgStatus.kBadParameters;
    }
    
// GETS / SETS VALUES CLOSURES
//--------------------------------------------------------------    
    _getText(): GetStringMethod         { return () => this.fText; }
    
    _getFontSize() : GetNumMethod       { return () => this.fFontSize; }
    _setFontSize() : SetNumMethod       { return () => this.fFontSize; }
    
    _getFontFamily() : GetStringMethod  { return () => this.fFontFamily; }
    _setFontFamily() : SetStringMethod  { return () => this.fFontFamily; }
    
    _getFontStyle() : GetStringMethod   { return () => this.fFontStyle; }
    _setFontStyle() : SetStringMethod   { return () => this.fFontStyle; }

    _getFontWeight() : GetStringMethod  { return () => this.fFontWeight; }
    _setFontWeight() : SetStringMethod  { return () => this.fFontWeight; }

// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): msgStatus { 
        let status = super.set(msg);
        
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        let n = msg.size();
        if (n > 2) {
            let data = '"';
            for (let i = 2 ; i < n ; i++) {
                if (msg.isNumber(i) || msg.isString(i)) {
                    data += msg.param(i);
                    data += ' ';
                }
            }
            console.log('taille de la chaine : ' + n )
            data = data.substr(0, data.lastIndexOf(" "));
            data += '"'; 
            this.setText(data);
            this.newData(true);
            status = msgStatus.kProcessed;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	let a: Array<any> = [kset_SetMethod, this.kTextType];
    	return new IMessage(this.getOSCAddress(), a.concat (this.fText) ); 
    }
}