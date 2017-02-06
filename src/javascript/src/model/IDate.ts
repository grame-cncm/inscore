///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../externals/fraction.ts"/>

class IDate {
    
// ATTRIBUTES
//-------------------------------------------------------------- 
    protected fDateChanged : boolean; 
    protected fDurationChanged : boolean;
    
    protected fDate : Fraction;					
	protected fDuration : Fraction;   
    
// CONSTRUTOR
//--------------------------------------------------------------    
    constructor(/*h:EventsAble*/) { 
        // TimeEventAble(h), 
        this.fDate = new Fraction(0,1); 
        this.fDuration = new Fraction(1,1); 
        this.fDateChanged = true; 
        this.fDurationChanged= true;  
    }
 
// GETS VALUES
//--------------------------------------------------------------   
    getDate(): 		Fraction 		{ return this.fDate; } 
    getDuration(): 	Fraction 		{ return this.fDuration; } 
    _getDate(): 	GetTimeMethod 	{ return () => this.fDate; } 
    _getDuration(): GetTimeMethod 	{ return () => this.fDuration; } 

// SETS VALUES
//--------------------------------------------------------------  
    setDate (date:Fraction): void {
        if (date.getDenominator() == 0) return;
        if (this.fDate != date) {
            //handleTimeChange(this.fDate, date);
            this.fDate = date;
            this.fDateChanged = true;
        }    
    }
    _setDate (): SetTimeMethod  	{ return (d) => this.setDate(d); };

    setDuration (dur:Fraction): void {
        if (dur.getDenominator() == 0) return;
        if (this.fDuration != dur) {
            //handleDurChange(this.fDuration, dur);
            this.fDuration = dur;
            this.fDurationChanged = true;
        }    
    }
    _setDuration (): SetTimeMethod  { return (d) => this.setDuration(d); };
    
    addDate (date:Fraction): void { 
        this.setDate(this.fDate.add(date));
        this.fDateChanged = true;
        }
    _addDate (): SetTimeMethod  { return (d) => this.addDate(d); };
        
    addDuration (dur:Fraction): void { 
        this.setDuration(this.fDuration.add(dur)); 
        this.fDurationChanged = true;
        }
    _addDuration (): SetTimeMethod  { return (d) => this.addDuration(d); };

// MODIFIED STATUS
//--------------------------------------------------------------
    modified(): boolean { return this.fDateChanged || this.fDurationChanged; }
    dateModified(): boolean { return this.fDateChanged; }
    durationModified(): boolean { return this.fDurationChanged; }   

    cleanup(): void { this.fDateChanged = this.fDurationChanged = false; }

// CLOCK
//--------------------------------------------------------------
    clock():void { this.addDate ( new Fraction(1, 96) ); }
    _clock ()	: SetVoidMethod  { return () => this.clock(); };
    durclock(): void { this.addDuration ( new Fraction(1, 96) ); }
    _durclock (): SetVoidMethod  { return () => this.durclock(); };

}