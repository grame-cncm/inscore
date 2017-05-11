///<reference path="IObject.ts"/>

class IVideo extends IObject {
    
    protected fFile: string;
    fPlay: number;
    fRate: number;
    fVolume: number;
    fVDate: Fraction;
    fModified: boolean;
    fMLS: number;
    fVDuration: number;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kVideoType;   
        this.fPlay = 0;
        this.fRate = 1;
        this.fVolume = 1;
        this.fVDate = new Fraction(0,1);
        this.fMLS = 0;
        this.fVDuration = 0;

        this.fMsgHandlerMap[kplay_GetSetMethod]      = new TMsgHandlerNum ((n: number)  : void => { this.setPlay(n)  });
        this.fMsgHandlerMap[krate_GetSetMethod]      = new TMsgHandlerNum ((n: number)  : void => { this.setRate(n)  });
        this.fMsgHandlerMap[kvolume_GetSetMethod]    = new TMsgHandlerNum ((n: number)  : void => { this.setVolume(n)});
        this.fMsgHandlerMap[kvdate_GetSetMethod]     = new TMsgHandlerTime((n: Fraction): void => { this.setVDate(n) });

        this.fGetMsgHandlerMap[kplay_GetSetMethod]   = new TGetMsgHandlerNum ( () : number   => { return this.getPlay  ()});
        this.fGetMsgHandlerMap[krate_GetSetMethod]   = new TGetMsgHandlerNum ( () : number   => { return this.getRate  ()});
        this.fGetMsgHandlerMap[kvolume_GetSetMethod] = new TGetMsgHandlerNum ( () : number   => { return this.getVolume()});
        this.fGetMsgHandlerMap[kvdate_GetSetMethod]  = new TGetMsgHandlerTime( () : Fraction => { return this.getVDate ()});
        this.fGetMsgHandlerMap[kmls_GetMethod]       = new TGetMsgHandlerNum ( () : number   => { return this.getMLS()   });
        this.fGetMsgHandlerMap[kvduration_GetMethod] = new TGetMsgHandlerNum ( () : number   => { return this.getVDuration()});
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
    getVDate()    : Fraction           { return this.fVDate }
    getMLS()      : number             {return this.fMLS   }
    getVDuration(): number             {return this.fVDuration }

    setPlay  (play   : number )  : void  { this.fPlay   = play;   this.modify()}
    setVolume(volume : number )  : void  { this.fVolume = volume; this.modify()}
    setRate  (rate   : number )  : void  { this.fRate   = rate;   this.modify()}
    setVDate (vDate  : Fraction ): void  {       
          if (vDate.getDenominator() == 0) {this.fVDate = new Fraction (this.fVDate.getNumerator()/1000, 1);return}
          if (this.fVDate != vDate) {
           this.fVDate = vDate;
           this.modify();
          }
    }
}