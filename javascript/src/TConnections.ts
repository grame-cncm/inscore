
///<reference path="lib/libINScore.d.ts"/>
///<reference path="inscore.ts"/>

//-----------------------------------------------------------------------------------
abstract class TConnection {
	// fSocket: WebSocket = null;
	// fEventSrc: EventSource = null;
	fUrl: string;
	
	constructor (url: string) {
		this.fUrl = url;
	}
	
	abstract connect (url: string) : void;		
	abstract close() : void;

	state() : number 	{ return 2; }
	get url() : string	{ return this.fUrl; }
			
	processData (e: MessageEvent) {
		// console.log ("TConnection.processData")
		// console.log (e.data)
		let data = atob(e.data);
		try {
			let json = JSON.parse(data);
			if (json['data'] && (json['method'] == "post")) {
				console.log ("Remote msg from " + e.origin + ": " + json['data']);
				inscore.loadInscore (json['data']);
			}
			else console.log ("Incorrect JSON message received from " + e.origin + ": " + json);
		}
		catch (err) { 
			if (e.data == "INScore")
				console.log ("Connected to INScore at " + this.fUrl)
			else {
				console.log ("Incorrect remote message received from " + e.origin + ": " + e.data);
				console.log (err);
			}
		}
	}
}

//-----------------------------------------------------------------------------------
class THTTPConnection extends TConnection {
	private fEventSrc: EventSource = null;
	
	constructor (url: string) {
		super(url);
		this.connect (url);
	}
	
	connect (url: string) {
		this.fEventSrc = new EventSource (url);
		this.fEventSrc.onmessage = (event) => { this.processData (event) };
		this.fEventSrc.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		this.fEventSrc.onerror = (error: Event) => { console.log ("Waiting for connection to " + this.fUrl + " ..."); };
	}
		
	close() { 
		if (this.fEventSrc) this.fEventSrc.close(); 
		this.fEventSrc =  null; 
	}

	state() : number { 
		if (this.fEventSrc) return this.fEventSrc.readyState; 
		return 2;
	}
}

//-----------------------------------------------------------------------------------
class TWSConnection extends TConnection {
	private fSocket: WebSocket = null;
	
	constructor (url: string) {
		super(url);
		this.connect (url);
	}
	
	connect (url: string) {
		this.fSocket = new WebSocket(url);
		this.fSocket.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		this.fSocket.onmessage = (event) => { this.processData (event.data) };
		this.fSocket.onerror = (error: Event) => { console.log ("Waiting for connection to " + this.fUrl + " ...") };
	}
		
	close() { 
		if (this.fSocket) this.fSocket.close(); 
		this.fSocket =  null; 
	}

	state() : number { 
		if (this.fSocket) return this.fSocket.readyState; 
		return 2;
	}
}

//-----------------------------------------------------------------------------------
interface TCnxState { url: string, state: number }
//-----------------------------------------------------------------------------------
// handle connect calls from inscore
// manages the list of connections
//-----------------------------------------------------------------------------------
class TConnections {
	static fCnx : Array<TConnection> = [];

	static connect (cnx: string, clear: boolean ) : boolean {
		if (clear) {
			this.fCnx.forEach ( (elt) => { elt.close(); } );
			this.fCnx= [];
		}

		if (cnx && cnx.length) {
			let proto = cnx.replace (/([a-z]+):\/\/..*/, "$1");
			switch (proto) {
				case "http":
					this.fCnx.push (new THTTPConnection (cnx));
					break;
				case "ws":
					this.fCnx.push (new TWSConnection (cnx));
					break;
				default:
					console.log ("Cannot connect to " + cnx + ": unknown protocol " + proto);
					return false;
			}
		}
		return true;
	}

	static state () : Array<TCnxState> {
		let out = new Array<TCnxState>();
		this.fCnx.forEach ( (elt) => { out.push ( {url: elt.url, state: elt.state() } ); } );
		return out;
	}
}
