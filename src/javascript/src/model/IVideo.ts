///<reference path="IObject.ts"/>

class IVideo extends IObject {
    
    protected fFile: string;
    fPlay: number;
    fRate: number;
    fVolume: number;
    fVDate: number;
    fModified: boolean;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kVideoType;   
        this.fPlay = 0;
        this.fRate = 1;
        this.fVolume = 1;
        this.fVDate = 0;   

        this.fMsgHandlerMap[kplay_GetSetMethod]          = new TMsgHandlerNum((n: number): void => { this.setPlay(n)  });
        this.fMsgHandlerMap[krate_GetSetMethod]          = new TMsgHandlerNum((n: number): void => { this.setRate(n)  });
        this.fMsgHandlerMap[kvolume_GetSetMethod]        = new TMsgHandlerNum((n: number): void => { this.setVolume(n)});
        this.fMsgHandlerMap[kvdate_GetSetMethod]         = new TMsgHandlerNum((n: number): void => { this.setVDate(n) });

        this.fGetMsgHandlerMap[kplay_GetSetMethod]       = new TGetMsgHandlerNum( () : number => { return this.fPlay  });
        this.fGetMsgHandlerMap[krate_GetSetMethod]       = new TGetMsgHandlerNum( () : number => { return this.fRate  });
        this.fGetMsgHandlerMap[kvolume_GetSetMethod]     = new TGetMsgHandlerNum( () : number => { return this.fVolume});
        this.fGetMsgHandlerMap[kvdate_GetSetMethod]      = new TGetMsgHandlerNum( () : number => { return this.fVDate });
    }    

    // MODIFIED STATUS
    //--------------------------------------------------------------      
   	cleanup() : void 	{ this.fModified = false; }
   	modified(): boolean { return this.fModified; }   
   	modify()  : void 	{ this.fModified = true; }

    colorAble(): void { }		// color attributes are not available for vidéos
    getFile(): string { return this.fFile; }
    
    set(msg:IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;
        
        if (msg.size() == 3) {
            let file = msg.paramStr(2);
            if (!file.correct) return eMsgStatus.kBadParameters;
        	this.fFile = file.value;
            this.newData(true);
        	status = eMsgStatus.kProcessed;
        }
        else status = eMsgStatus.kBadParameters;
        return status;
    }

    getSet(): IMessage	{
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, "'" + this.getFile() + "'"]); 
    }    

    getPlay()     : number             { return this.fPlay  }
    getVolume()   : number             { return this.fVolume}    
    getRate()     : number             { return this.fRate  }
    getVDate()    : number             { return this.fVDate }

    setPlay  (play   : number ): void  { this.fPlay   = play;   this.modify()}
    setVolume(volume : number ): void  { this.fVolume = volume; this.modify()}
    setRate  (rate   : number ): void  { this.fRate   = rate;   this.modify()}
    setVDate (vDate  : number ): void  { this.fVDate  = vDate;  this.modify()}
}

