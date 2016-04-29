class ITLError {
    
    static write (str: string) 					{ console.log ("Error: " + str); }
    static badParameter (msg: string, p: any) 	{ this.write ("bad parameter " + p + " in " + msg); }

}