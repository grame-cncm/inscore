///<reference path="Constants.ts"/>
///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>

class IArc extends IRectShape
{
    protected fStart    : number;     //element start position x,y
    protected fRange    : number;     //element size
    protected fClose    : number;     //draw the line to the center of the ellipse
    protected fDRange   : number;
    protected fDStart   : number;

    constructor(name: string, parent: IObject)
    {
        super( name, parent );
        this.fTypeString = kArcType;
        this.fStart  = 0;
        this.fRange  = 0;
        this.fClose  = 0;
        this.fPenControl.setPenWidth(1);
        this.fBrushStyle.fBrush = eBrushStyle.kNone;
    }

// HANDLERS
//--------------------------------------------------------------  
    setHandlers(): void {
		super.setHandlers();
        this.fMsgHandlerMap[kstart_GetSetMethod]    = new TMsgHandlerNum  (this._setStart());
        this.fMsgHandlerMap[krange_GetSetMethod]    = new TMsgHandlerNum  (this._setRange());
        this.fMsgHandlerMap[kclose_GetSetMethod]    = new TMsgHandlerNum  (this._setClose());
        this.fMsgHandlerMap[kdrange_SetMethod]      = new TMsgHandlerNum  (this._setDRange());
        this.fMsgHandlerMap[kdstart_SetMethod]      = new TMsgHandlerNum  (this._setDStart());
    }

    set(msg: IMessage): eMsgStatus
    {
        let status = super.set(msg);
        // Cas ou le type est différent, le proxy est utilisé dans super.set()
         if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

        // Vérification des paramêtres du message "set"
        if (msg.size() == 6)
        {
            let width  =  msg.paramNum(2), height = msg.paramNum(3);
            if (!width.correct || !height.correct) { return eMsgStatus.kBadParameters; }
            let start  =  msg.paramNum(4), range  = msg.paramNum(5);
            if (!start.correct || !range.correct) { return eMsgStatus.kBadParameters; }

            // Si les valeurs des attributs ne sont pas les mêmes
            if ( (width.value != this.fPosition.getWidth()) || (height.value != this.fPosition.getHeight())
                || ( (start.value != this.fStart) || (range.value != this.fRange) ))
            {
                this.fPosition.setWidth(width.value);
                this.fPosition.setHeight(height.value);
                this.fStart = start.value;
                this.fRange = range.value;
                this.newData(true);
                status = eMsgStatus.kProcessed;
            }
            else status = eMsgStatus.kProcessedNoChange;
        }
        else status = eMsgStatus.kBadParameters;
        return status;
    }

    getSet(): IMessage
    {
        return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPosition.getWidth(), this.fPosition.getHeight(), this.getStart(), this.getRange()]);
    }

    getStart ()   : number { return this.fStart    }
    getRange ()   : number { return this.fRange    }
    getClose ()   : number { return this.fClose    }

    setStart   (start     : number): void { this.fStart    = start     }
    setRange   (range     : number): void { this.fRange    = range     }
    setClose   (close     : number): void { this.fClose    = close     }
    setDRange  (dRange    : number): void { this.setRange(this.fRange + dRange); }
    setDStart  (dStart    : number): void { this.setStart(this.fStart + dStart); }

    _getStart()     { return () => this.getStart()    }
    _getRange()     { return () => this.getRange()    }
    _getClose()     { return () => this.getClose()    }

    _setStart()     { return (start     : number) => this.setStart(start)        }
    _setRange()     { return (range     : number) => this.setRange(range)        }
    _setClose()     { return (close     : number) => this.setClose(close)        }
    _setDRange()    { return (dRange    : number) => this.setDRange(dRange)      }
    _setDStart()    { return (dStart    : number) => this.setDStart(dStart)      }
}