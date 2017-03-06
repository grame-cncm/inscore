///<reference path="../lib/TEnums.ts"/>
///<reference path="IObject.ts"/>

class IRectShape extends IObject {

    fBrushStyle : brushStyle;
    protected fModified : boolean;

    fBrushStyleStr2Num: { [id: string] : brushStyle; } = {};
    fBrushStyleNum2Str: { [id: number] : string; } = {};


    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fBrushStyle = brushStyle.solid;
        this.buildBrushStyle();
    }

    buildBrushStyle(): void {
        this.fBrushStyleStr2Num["solid"] = brushStyle.solid;
        this.fBrushStyleStr2Num["none"]  = brushStyle.none;

        this.fBrushStyleNum2Str[brushStyle.solid] = "solid";
        this.fBrushStyleNum2Str[brushStyle.none]  = "none";
    }

    create(name: string, parent: IObject): IRectShape { return new IRectShape(name, parent); }

    setHandlers() {
    	super.setHandlers(); 
        this.fMsgHandlerMap[kwidth_GetSetMethod]  = new TMsgHandlerNum(this._setWidth());
        this.fMsgHandlerMap[kheight_GetSetMethod] = new TMsgHandlerNum(this._setHeight());

        this.fGetMsgHandlerMap[kbrushStyle_GetSetMethod] = new TGetMsgHandlerText(this._getBrushStyle());
        this.fMsgHandlerMap[kbrushStyle_GetSetMethod]    = new TMsgHandlerText(this._setBrushStyle());
    }
   
    set(msg: IMessage): msgStatus {
        let status = super.set(msg);
       
        // Cas ou le type est différent, le proxy est utilisé dans super.set()
        if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status; 

        // Vérification des paramêtres du message "set"
        if (msg.size() == 4) {
            let width = msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) { return msgStatus.kBadParameters; }

            // Si les valeurs des attributs ne sont pas les mêmes
            if ( (width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight()) ) {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.newData(true);
                status = msgStatus.kProcessed;
            }
            else status = msgStatus.kProcessedNoChange;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }  

    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight()]); 
    }
   
    //accept (Updater*): void
    // virtual MsgHandler::msgStatus set (const IMessage* msg);

    getBrushStyle () : string {return this.fBrushStyleNum2Str[this.fBrushStyle];}
    _getBrushStyle() : GetStringMethod { return () => this.getBrushStyle() }
    setBrushStyle (brushStyle : string): void {
        let style = this.fBrushStyleStr2Num[brushStyle];
        this.fBrushStyle = style;}
    _setBrushStyle(): SetStringMethod { return (brush : string) => this.setBrushStyle(brush) }
}