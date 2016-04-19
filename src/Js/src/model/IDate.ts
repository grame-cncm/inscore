///<reference path="../externals/fraction/fraction.ts"/>

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
    getDate(): Fraction { return this.fDate; } 
    getDuration(): Fraction { return this.fDuration; } 

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

    setDuration (dur:Fraction): void {
        if (dur.getDenominator() == 0) return;
        if (this.fDuration != dur) {
            //handleDurChange(this.fDuration, dur);
            this.fDuration = dur;
            this.fDurationChanged = true;
        }    
    }
    
    addDate (date:Fraction): void { 
        this.setDate(this.fDate.add(date));
        this.fDateChanged = true;
        }
        
    addDuration (dur:Fraction): void { 
        this.setDuration(this.fDuration.add(dur)); 
        this.fDurationChanged = true;
        }

// MODIFIED STATUS
//--------------------------------------------------------------
    modified(): boolean { return this.fDateChanged || this.fDurationChanged; }
    dateModified(): boolean { return this.fDateChanged; }
    durationModified(): boolean { return this.fDurationChanged; }   

    cleanup(): void { this.fDateChanged = this.fDurationChanged = false; }

// CLOCK
//--------------------------------------------------------------
    clock():void { this.addDate ( new Fraction(1, 96) ); }
    durclock(): void { this.addDuration ( new Fraction(1, 96) ); }

}