
///<reference path="lib/libINScore.d.ts"/>

class TConnection {
	fSocket: WebSocket = null;
	fEventSrc: EventSource = null;
	fUrl: string;
	
	constructor (url: string) {
		this.fUrl = url;
		this.connect (url);
	}
	
	connect (url: string) {
		this.fUrl = url;
		this.fEventSrc = new EventSource (url);
		this.fEventSrc.onmessage = (event) => { this.processData (event) };
		this.fEventSrc.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		this.fEventSrc.onerror = (error: Event) => { this.error(); };
	
		// this.fSocket = new WebSocket(url);
		// this.fSocket.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		// this.fSocket.onmessage = (event) => { this.processData (event.data) };
		// this.fSocket.onerror = (error: wserror) => { console.log (`[websocket error] ${error}`); };
	}
		
	close() { 
		if (this.fEventSrc) this.fEventSrc.close(); 
		this.fEventSrc =  null; 
		if (this.fSocket) this.fSocket.close(); 
		this.fSocket =  null; 
	}

	error() { 
		let delay = 5;
		console.log ("Connection to " + this.fUrl + " failed");
		console.log ("Retry to connect in " + delay + " seconds");
		setTimeout ( () => { if (this.fEventSrc) this.connect(this.fUrl); }, delay*1000 );
	}

	state() : number { 
		if (this.fEventSrc) return this.fEventSrc.readyState; 
		else if (this.fSocket) return this.fSocket.readyState;
		return 2;
	}

	url() : string { return this.fUrl; }
			
	processData (e: MessageEvent) {
		let data = atob(e.data);
		try {
			let json = JSON.parse(data);
			if (json['data'] && (json['method'] == "post")) {
				console.log ("inscore http: " + json['data']);
				inscore.loadInscore (json['data']);
			}
			else console.log ("Incorrect JSON message received from " + this.fUrl + ": " + json);
		}
		catch (err) { 
			if (e.data == "INScore")
				console.log ("Connected to INScore at " + this.fUrl)
			else {
				console.log ("Incorrect message received from " + this.fUrl + ": " + e.data);
				console.log (err);
			}
		}
	}
}

interface TCnxState { url: string, state: number }
class TConnections {
	static fCnx : Array<TConnection> = [];

	static connect (cnx: string, clear: boolean ) : boolean {
		if (clear) {
			this.fCnx.forEach ( (elt) => { elt.close(); } );
			this.fCnx= [];
		}
		if (cnx && cnx.length) this.fCnx.push (new TConnection (cnx));
		return true;
	}

	static state () : Array<TCnxState> {
		let out = new Array<TCnxState>();
		this.fCnx.forEach ( (elt) => { out.push ( {url: elt.url(), state: elt.state() } ); } );
		return out;
	}
}
