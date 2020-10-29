
///<reference path="lib/libINScore.d.ts"/>


class TConnection {
	fSocket: WebSocket = null;
	fEventSrc: EventSource = null;
	fUrl: string;
	
	constructor (url: string) {
console.log ("TConnection create new connection to " + url);
		// this.fUrl = url;
		this.fEventSrc = new EventSource (url);
		this.fEventSrc.onmessage = (event) => { this.processData (event.data) };
		this.fEventSrc.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		this.fEventSrc.onerror = (error: Event) => { console.log (`[http error] ${error}`); };

		// this.fSocket = new WebSocket(url);
		// this.fSocket.onopen = () => { console.log("Connection to " + this.fUrl + " established"); };
		// this.fSocket.onmessage = (event) => { this.processData (event.data) };
		// this.fSocket.onerror = (error: wserror) => { console.log (`[websocket error] ${error}`); };
	}

	close() { if (this.fSocket) this.fSocket.close(); this.fSocket =  null; }
	// close() { if (this.fEventSrc) this.fEventSrc.close(); this.fEventSrc =  null; }
	
	processData (data: any) {
console.log ("TConnection::processData received from " + this.fUrl + " data: " + data)
	}
}

class TConnections {
	static fCnx : Array<TConnection> = [];

	static connect (cnx: string, clear: boolean )	: boolean {
console.log ("TConnections::connect " + cnx + " clear: " + clear);
		if (clear) {
			this.fCnx.forEach ( (elt) => { elt.close(); } );
			this.fCnx= [];
		}
		this.fCnx.push (new TConnection (cnx));
		return true;
	}
}
