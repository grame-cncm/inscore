
///<reference path="inscore.ts"/>
///<reference path="libraries.ts"/>

//----------------------------------------------------------------------------
class INScoreGlue {
	private fInscore : INScore;
	private fTimeTask : number = 0;
	private fSorterTask : number = 0;

    constructor() {
		this.fInscore = new INScore;
    }
		
    //------------------------------------------------------------------------
	// initialization
	async start():Promise<any> {
		return new Promise( (success: any, failure: any) => {
			this.fInscore.initialise ().then 
			(() => { 
				this.fInscore.start();
				inscorelibs.initialise().then 
					(() => { this.initialise(); success(this); })
			});
		});
	}

	initialise() : void {
		this.fTimeTask = window.setInterval( () => { this.fInscore.timeTask(); }, this.fInscore.getRate());
		this.fSorterTask = window.setInterval( () => { this.fInscore.sorterTask(); }, 1);
	}
}

var gGlue = new INScoreGlue();

// default function to show the log window (if any)
// should be overriden by client applications
function showlog (status: boolean) {}
