

//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
interface TMessage     {}

interface INScore {

    initialise():Promise<any> ;

    //------------------------------------------------------------------------
    // INScore interface
    start() : void;
	stop()  : void;

	loadInscore	 (script: string, autoparse: boolean) : boolean;
	loadInscore2 (script: string) : boolean;

	postMessage	(adr: string, msg: TMessage)	: void;
	postMessageStr (adr: string, meth: string)	: void;
	postMessageStrI	(adr: string, meth: string, val: number) : void;
	postMessageStrF	(adr: string, meth: string, val: number) : void;
	postMessageStrStr(adr: string, meth: string, val: string): void;

    delayMessage (adr: string, msg: TMessage)   : void;
	newMessage ()                               : TMessage;
	newMessageM (meth: string)                  : TMessage;
	delMessage (msg: TMessage)                  : void;

    msgAddStr (msg: TMessage, str: string)      : void;
	msgAddF   (msg: TMessage, val: number)      : void;
	msgAddI   (msg: TMessage, val: number)      : void;

    version ()				: number; 
	versionStr ()			: string; 
	guidoversion ()			: string; 
	musicxmlversion ()		: string; 
        
    //------------------------------------------------------------------------
    // INScore glue interface
    getRate() 		: number;
	timeTask ()	    : void;
	sorterTask()	: void;
}

declare var inscore : INScore;
