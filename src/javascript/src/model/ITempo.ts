///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/ITLError.ts"/>

class ITempo {

    protected fTempoModified: boolean;
    fTempo: number;

    constructor() {
        this.fTempoModified = false;
        this.fTempo = 0;
    }

// MODIFIED STATUS
//--------------------------------------------------------------
    cleanup() : void 			{ this.fTempoModified = false; }
    tempoModified(): boolean 	{ return this.fTempoModified; }
    modify()  : void 			{ this.fTempoModified = true; }

// Get Set Methods
//--------------------------------------------------------------
     getTempo() : number 			    { return this.fTempo;}
    _getTempo() : GetNumMethod      	{ return () => this.getTempo(); }

    setTempo (tempo : number): void 	{ this.fTempo = tempo; this.modify(); }
    _setTempo(): SetNumMethod 		    { return (tempo : number) => this.setTempo(tempo); }

    addTempo (t:number): void { 
        this.setTempo(this.fTempo + t);
        this.modify();
        }
    _addTempo (): SetNumMethod  { return (t) => this.addTempo(t); };
}