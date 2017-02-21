///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>

class IArc extends IRectShape
{
    protected fStart    : number;     //element start position x,y
    protected fRange    : number;     //element size
    protected fClose    : number;     //draw the line to the center of the ellipse
    protected fDRange   : number;
    protected fDStart   : number;
    protected fPenColor : Array<number>;
    protected fPenWidth : number;
    protected fPenStyle : string;
    protected fPenAlpha : number;

    protected kArcType : string;

    constructor(name: string, parent: IObject)
    {
        super( name, parent );
        this.kArcType = "arc";
        this.fTypeString = this.kArcType;
        this.fStart  = 0;
        this.fRange  = 0;
        this.fClose  = 0;
        this.fDRange = 0;
        this.fDStart = 0;
        this.fPenControl.setPenWidth(1);
        this.fPenWidth =  1;
        this.fPenStyle = "";
        this.fPenAlpha =  0;
        this.fPenColor = [];

        this.fMsgHandlerMap[kstart_GetSetMethod]    = new TMsgHandlerNum  (this._setStart());
        this.fMsgHandlerMap[krange_GetSetMethod]    = new TMsgHandlerNum  (this._setRange());
        this.fMsgHandlerMap[kclose_GetSetMethod]    = new TMsgHandlerNum  (this._setClose());
        this.fMsgHandlerMap[kdrange_SetMethod]      = new TMsgHandlerNum  (this._setDRange());
        this.fMsgHandlerMap[kdstart_SetMethod]      = new TMsgHandlerNum  (this._setDStart());
        this.fMsgHandlerMap[kpenColor_GetSetMethod] = new TMsgHandlerColor(this._setPenColor());
        this.fMsgHandlerMap[kpenWidth_GetSetMethod] = new TMsgHandlerNum  (this._setPenWidth());
        this.fMsgHandlerMap[kpenStyle_GetSetMethod] = new TMsgHandlerText (this._setPenStyle());
        this.fMsgHandlerMap[kpenAlpha_GetSetMethod] = new TMsgHandlerNum  (this._setPenAlpha());
    }

    set(msg: IMessage): msgStatus
    {
        let status = super.set(msg);

        // Cas ou le type est différent, le proxy est utilisé dans super.set()
         if (status & (msgStatus.kProcessed + msgStatus.kProcessedNoChange)) return status;

        // Vérification des paramêtres du message "set"
        if (msg.size() == 6)
        {
            let width  =  msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) { return msgStatus.kBadParameters; }
            let start  =  msg.paramNum(4), range  = msg.paramNum(5);
            if (!start.correct || !range.correct) { return msgStatus.kBadParameters; }

            // Si les valeurs des attributs ne sont pas les mêmes
            if ( (width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight())
                || ( (start.value != this.fStart) || (range.value != this.fRange) ))
            {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.fStart = start.value;
                this.fRange = range.value;
                this.newData(true);
                status = msgStatus.kProcessed;
            }
            else status = msgStatus.kProcessedNoChange;
        }
        else status = msgStatus.kBadParameters;
        return status;
    }

    getSet(): IMessage
    {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight(), this.getStart(), this.getRange()]);
    }

    getStart ()   : number { return this.fStart    }
    getRange ()   : number { return this.fRange    }
    getClose ()   : number { return this.fClose    }
    getDRange()   : number { return this.fDRange   }
    getDStart()   : number { return this.fDStart   }
    getPenColor() : Array<number> { return this.fPenColor }
    getPenWidth() : number { return this.fPenWidth }
    getPenStyle() : string { return this.fPenStyle }
    getPenAlpha() : number { return this.fPenAlpha }

    setStart   (start     : number): void { this.fStart    = start     }
    setRange   (range     : number): void { this.fRange    = range     }
    setClose   (close     : number): void { this.fClose    = close     }
    setDRange  (dRange    : number): void { this.fDRange   = dRange    }
    setDStart  (dStart    : number): void { this.fDStart   = dStart    }
    setPenColor(PenColor  : Array<number>): void { this.fPenColor = PenColor }
    setPenWidth(PenWidth  : number): void { this.fPenWidth = PenWidth  }
    setPenStyle(PenStyle  : string): void { this.fPenStyle = PenStyle  }
    setPenAlpha(PenAlpha  : number): void { this.fPenAlpha = PenAlpha  }

    _getStart()     { return () => this.getStart()    }
    _getRange()     { return () => this.getRange()    }
    _getClose()     { return () => this.getClose()    }
    _getDRange()    { return () => this.getDRange()   }
    _getDStart()    { return () => this.getDStart()   }
    _getPenColor()  { return () => this.getPenColor() }
    _getPenWidth()  { return () => this.getPenWidth() }
    _getPenStyle()  { return () => this.getPenStyle() }
    _getPenAlpha()  { return () => this.getPenAlpha() }

    _setStart()     { return (start     : number) => this.setStart(start)        }
    _setRange()     { return (range     : number) => this.setRange(range)        }
    _setClose()     { return (close     : number) => this.setClose(close)        }
    _setDRange()    { return (dRange    : number) => this.setDRange(dRange)      }
    _setDStart()    { return (dStart    : number) => this.setDStart(dStart)      }
    _setPenColor()  { return (penColor  : Array<number>) => this.setPenColor(penColor)}
    _setPenWidth()  { return (penWidth  : number) => this.setPenWidth(penWidth)  }
    _setPenStyle()  { return (penStyle  : string) => this.setPenStyle(penStyle)  }
    _setPenAlpha()  { return (penAlpha  : number) => this.setPenAlpha(penAlpha)  }
}