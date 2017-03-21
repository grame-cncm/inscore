///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="IObject.ts"/>
///<reference path="Constants.ts"/>
///<reference path="IProxy.ts"/>
///<reference path="IApplStaticNodes.ts"/>

interface Document {
	mozCancelFullScreen(): void;
	msExitFullscreen(): void;
}

class IAppl extends IObject {

	protected kApplType: string;
	protected fReceivedMsgs: number;
	protected fRate: number;
	fFullScreen: boolean;

	constructor() {
		super('ITL');
		this.kApplType = kApplType;
		this.fTypeString = kApplType;
		this.fReceivedMsgs = 0;
		this.fRate = 100;

		this.fMsgHandlerMap[kfullscreen_GetSetMethod] = new TMsgHandlerNum(this._setFullScreen());
		this.fGetMsgHandlerMap[kfullscreen_GetSetMethod] = new TGetMsgHandlerNum(this._getFullScreen());
	}

	getFullScreen(): number {
		if (this.fFullScreen) return 1;
		else return 0;
	}
	_getFullScreen(): GetNumMethod { return () => this.getFullScreen(); }

	setFullScreen(full: number): eMsgStatus {
		switch (full) {
			case 0: this.fFullScreen = false;
				this.enableDisableFullScreen();
				return eMsgStatus.kProcessed
				break;
			case 1: this.fFullScreen = true;
				this.enableDisableFullScreen();
				return eMsgStatus.kProcessed;
				break;
			default: eMsgStatus.kBadParameters
		}
	};
	_setFullScreen(): SetNumMethod { return (full: number) => this.setFullScreen(full) }

	createStaticNodes(): void {
		let log = new IApplLog("log", this);
		this.addChild(log);
	}

	getAppl(): IObject { return this; }
	getSet(): IMessage { let msg: IMessage; return msg; }
	getOSCAddress(): string { return "/ITL"; }
	getRate(): number { return this.fRate; }
	setRate(rate: number): void { this.fRate = rate; }

	// prevent the output of color, position and time data at application level
	colorAble(): void { }
	positionAble(): void { }
	timeAble(): void { }

	processMsg(address: string, addressTail: string, msg: IMessage): eMsgStatus {
		this.fReceivedMsgs++;

		let status = eMsgStatus.kBadAddress;
		let head = address;
		let tail = addressTail;

		/*
				SIMessage msg = IMessage::create (*imsg);
				TAliasesMap::const_iterator i = fAliases.find(imsg->address());
				if (i != fAliases.end()) {
					msg->setAddress (i->second.first);
					if (i->second.second.size()) 
						msg->setMessage(i->second.second);
					head = OSCAddress.addressFirst(i->second.first);
					tail = OSCAddress.addressTail(i->second.first);
				}
		*/

		if (tail.length) {			// application is not the final destination of the message
			status = super.processMsg(head, tail, msg);
		}

		else if (this.match(head)) {		// the message is for the application itself
			status = this.execute(msg);
			if (status & eMsgStatus.kProcessed)
				this.setState(eObjState.kModified);
		}
		return status;
	}

	enableDisableFullScreen() {
		if (this.fFullScreen) this.launchFullscreen(document.documentElement);
		else this.exitFullscreen();
	}

	/*
		protected newObj (msg: IMessage, name: string): { status: eMsgStatus, obj?: IObject } 
						{ return this.proxy_create(msg, name, this); }                
		protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: eMsgStatus, obj?: IObject }	
						{ return IProxy.execute (msg, name, parent); }
	*/

	//-------------------FullScreenManagement---------------------

	// Find the right method, call on correct element
	launchFullscreen(element) {
		console.log("IAppl launchFullscreen fullscreenEnabled : " + document.fullscreenEnabled);
		if (element.requestFullscreen) {
			//Standard
			console.log("IAppl launchFullscreen requestFullscreen");
			element.requestFullscreen();
		} else if (element.mozRequestFullScreen) {
			//Mozilla
			console.log("IAppl launchFullscreen mozRequestFullScreen");
			element.mozRequestFullScreen();
		} else if (element.webkitRequestFullscreen) {
			//Chrome - Edge
			console.log("IAppl launchFullscreen webkitRequestFullscreen");
			element.webkitRequestFullscreen();
		} else if (element.msRequestFullscreen) {
			//IE
			console.log("IAppl launchFullscreen msRequestFullscreen");
			element.msRequestFullscreen();
		}
	}

	exitFullscreen() {
		if (document.exitFullscreen) {
			//Standard
			console.log("IAppl launchFullscreen exitFullscreen");
			document.exitFullscreen();
		} else if (document.mozCancelFullScreen) {
			//Mozilla
			console.log("IAppl launchFullscreen mozCancelFullScreen");
			document.mozCancelFullScreen();
		} else if (document.webkitExitFullscreen) {
			//Chrome - Edge
			console.log("IAppl launchFullscreen webkitExitFullscreen");
			document.webkitExitFullscreen();
		} else if (document.msExitFullscreen) {
			//IE
			console.log("IAppl launchFullscreen msExitFullscreen");
			document.msExitFullscreen();
		}
	}
}