

//----------------------------------------------------------------------------
// INScore interface
//----------------------------------------------------------------------------
interface TMessage     {}

interface INScore {

    initialise():Promise<any> ;

    //------------------------------------------------------------------------
    // INScore interface

	/**
    * Loads an inscore script.
    *
    * @param {string} script - an inscore script
    * @param {boolean} autoparse - when true and when the application parse version is v2, parse the script as inscore v2 otherwise, inscre v1 syntax is expected.
    * @returns {boolean} returns false in case of failure (e.g. syntax error)
    */
	 loadInscore	 (script: string, autoparse: boolean) : boolean;

	/**
    * Loads an inscore script using v2 syntax.
    *
    * @param {string} script - an inscore script
    * @returns {boolean} returns false in case of failure (e.g. syntax error)
    */
	 loadInscore2 (script: string) : boolean;

	/**
    * Post a message.
    *
    * @param {string} adr - the destination object address
    * @param {TMessage} msg - the message to be posted
    * @note a posted message should not be deleted
    */
	postMessage	(adr: string, msg: TMessage)	: void;

	/**
    * Create and post a message with an associated method.
    *
    * @param {string} adr - the destination object address
    * @param {string} meth - the method as message parameter
    */
	postMessageStr (adr: string, meth: string)	: void;

	/**
    * Create and post a message with an associated method and an int value.
    *
    * @param {string} adr - the destination object address
    * @param {string} meth - the method as message parameter
    * @param {number} val - an int message parameter
    */
	postMessageStrI	(adr: string, meth: string, val: number) : void;

	/**
    * Create and post a message with an associated method and a float value.
    *
    * @param {string} adr - the destination object address
    * @param {string} meth - the method as message parameter
    * @param {number} val - a float message parameter
    */
	postMessageStrF	(adr: string, meth: string, val: number) : void;

	/**
    * Create and post a message with an associated method and a string value.
    *
    * @param {string} adr - the destination object address
    * @param {string} meth - the method as message parameter
    * @param {string} val - a string message parameter
    */
	postMessageStrStr(adr: string, meth: string, val: string): void;


	/**
    * Post a message, delayed by one time task.
    *
    * @param {string} adr - the destination object address
    * @param {TMessage} msg - the message to be posted
    */
	 delayMessage (adr: string, msg: TMessage)   : void;
    
	/**
    * Creates a new inscore message.
    *
    * @returns {TMessage} returns the message
    */
	newMessage ()                               : TMessage;

	/**
    * Creates a new inscore message with a method.
    *
    * @param {string} meth - the method name
    * @returns {TMessage} returns the message
    */
	newMessageM (meth: string)                  : TMessage;

	/**
    * Delete a message previoulsy created with newMesage or newMessageM.
    *
    * @param {TMessage} msg - the message to delete
    */
	delMessage (msg: TMessage)                  : void;

	/**
    * Add a string parameter to a message
    *
    * @param {TMessage} msg - the message
    * @param {string} str - a string to be appened to the message parameters
    */
	msgAddStr (msg: TMessage, str: string)      : void;

	/**
    * Add a float parameter to a message
    *
    * @param {TMessage} msg - the message
    * @param {number} val - a float value to be appened to the message parameters
    */
	msgAddF   (msg: TMessage, val: number)      : void;

	/**
    * Add a int parameter to a message
    *
    * @param {TMessage} msg - the message
    * @param {number} val - a int value to be appened to the message parameters
    */
	msgAddI   (msg: TMessage, val: number)      : void;

	/**
    * Gives inscore version as a float number

	* @return {number} - inscore version number
    */    
    version ()				: number; 

	/**
    * Gives inscore version as a string

	* @return {string} - inscore version string
    */    
	versionStr ()			: string; 

	/**
    * Gives the Guido engine version as a string (when available)

	* @return {string} - Guido engine version string
    */    
	guidoversion ()			: string; 

	/**
    * Gives the libMusicXML version as a string (when available)

	* @return {string} - libMusicXML version string
    */    
	musicxmlversion ()		: string; 
        
    //------------------------------------------------------------------------
    // INScore glue interface
    start() : void;
	stop()  : void;
    getRate() 		: number;
	timeTask ()	    : void;
	sorterTask()	: void;
}

declare var inscore : INScore;
