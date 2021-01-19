///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>

class IDate {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fModified : 	boolean; 
    protected fTempo: 		number;   
    protected fDate : 		Fraction;					
	protected fDuration : 	Fraction;   
    
// CONSTRUTOR
//--------------------------------------------------------------    
    constructor() { 
        this.fDate = new Fraction(0,1); 
        this.fDuration = new Fraction(1,1); 
        this.fModified = true;
        this.fTempo = 0;
    }
    
    modify() : void { this.fModified = true; }

// PROPERTIES COPY
//--------------------------------------------------------------    
    set (obj: IDate) {
        this.setDate (obj.fDate); 
        this.setDuration (obj.fDuration); 
        this.setTempo (obj.fTempo);
   }

// GETS VALUES
//--------------------------------------------------------------   
    getDate(): 		Fraction 		{ return this.fDate; } 
    getDuration(): 	Fraction 		{ return this.fDuration; } 
	getTempo() : number 			{ return this.fTempo;}

// SETS VALUES
//--------------------------------------------------------------  
    setDate (date:Fraction): void {
        if (date.getDenominator() == 0) return;
        if (this.fDate != date) {
           //handleTimeChange(this.fDate, date);
           this.fDate = date;
           this.modify();
        }    
    }

    setDuration (dur:Fraction): void {
        if (dur.getDenominator() == 0) return;
        if (this.fDuration != dur) {
            //handleDurChange(this.fDuration, dur);
            this.fDuration = dur;
           this.modify();
        }    
    }
    
    setTempo (tempo : number): void 	{ this.fTempo = tempo; this.modify(); }
    
    addDate (date:Fraction): void 		{ this.setDate(this.fDate.add(date)); }
    addDuration (dur:Fraction): void 	{ this.setDuration(this.fDuration.add(dur)); }
    addTempo (t: number): void 			{ this.setTempo (this.fTempo + t); }

// MODIFIED STATUS
//--------------------------------------------------------------
    modified(): boolean 			{ return this.fModified; }
    cleanup(): void 				{ this.fModified = false; }

// CLOCK
//--------------------------------------------------------------
    clockDur():Fraction { return new Fraction(1, 96); }
    clock():void 		{ this.addDate ( this.clockDur() ); }
    durclock(): void 	{ this.addDuration ( this.clockDur() ); }
}
