///<reference path="../model/IObject.ts"/>
///<reference path="../model/IApplStaticNodes.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../inscore.ts"/>

interface TCloseHandler  		{ (): void; }

class VHtmlLog extends VObjectView {
	protected fWindow : Window;
	protected fPreviousX : number = -1; 		// the window previous position: used to detect window move
	protected fPreviousY : number = -1;
	protected fPreviousOX : number = -1; 		// the object previous position: used to handle window move
	protected fPreviousOY : number = -1;

	constructor() { super(); } 

	updateView ( obj: IObject) : void {
		if (obj.fPosition.getVisible()) {
			let pos		= obj.getPosition();
			let size 	= obj.getSize();
			let posChge = ((this.fPreviousOX < 0) ? true : (pos.x != this.fPreviousOX)) || 
						  ((this.fPreviousOY < 0) ? true : (pos.y != this.fPreviousOY));
			this.fPreviousOX = pos.x;
			this.fPreviousOY = pos.y;
			if (this.checkwindow (obj)) {
				this.fWindow.focus();
				if (obj.fPosition.modified()) {
					this.fWindow.resizeTo (this.relative2SceneWidth (size.w), this.relative2SceneHeight (size.h));
					if (posChge) {
						let top 	= this.relative2SceneY (pos.y - (size.h/2));
						let left 	= this.relative2SceneX (pos.x - (size.w/2));
						this.fWindow.moveTo (left, top);
					}
				}
				this.writelog(<IApplLog>obj);
			}
		} 
		else if (this.fWindow) {
			this.fWindow.close();
			this.close(obj);
		}
	}

	setPositionHandler	( fpos: TPositionHandler) : void {};

	writelog ( log: IApplLog ) : void {
		if (log.cleared())
			this.fWindow.document.body.innerHTML = "";
		let content = log.content();
		for (let i=0; i < content.length; i++) {
			this.fWindow.document.write(content[i] + "<br />\n");
			this.fWindow.window.scrollBy(0, 50);
		}
		log.done();
	}

	checkwindowpos ( obj: IObject ) {		// check if the window position has been changed 
		let size 	= obj.getSize();
		let wx	= this.fWindow.screenX;
		if (wx != this.fPreviousX) obj.fPosition.setXPos (this.scene2RelativeX(wx) + (size.w/2));
		let wy 	= this.fWindow.screenY;
		if (wy != this.fPreviousY) obj.fPosition.setYPos (this.scene2RelativeY(wy) + (size.h/2));
		this.fPreviousX = wx;
		this.fPreviousY = wy;
	}

	close (obj: IObject) :  void  {			// cleanup the view and object state
		this.checkwindowpos ( obj );		// update the last window position
		this.fWindow = undefined;
	}
	
	closeHandler (obj: IObject) :  void  {	// set on window unload event
		this.close(obj);
		obj.fPosition.setVisible(0);
	}
	_close (o: IObject) :  TCloseHandler  	{ return () => this.closeHandler (o); }

	getCurrentStyleSheets () : string {		// get the current style sheets and build the corresponding links
  		var style = "";
  		for( var i in document.styleSheets ) {
  			let href = document.styleSheets[i].href;
		    if (href) {
		    	style += "<link href='" + href + "' rel='stylesheet'>\n";
		    }
		}
		return style;
	}

	checkwindow ( obj: IObject ) : boolean {	// checks if the window is opened and otherwise creates the window
		if (!this.fWindow) {
			let specs = "menubar=no, titlebar=no, status=no, directories=no, location=no";
			let style = this.getCurrentStyleSheets();
			this.fWindow = window.open("", obj.getOSCAddress(), specs);
			if (this.fWindow) {
				this.fWindow.document.write("<head><title>"+obj.getOSCAddress()+"</title>\n" + style + "</head>");
				this.fWindow.document.write("<body class='inscore-log'></body>");
				this.fWindow.addEventListener("resize", this._resizeLog(obj));
				this.fWindow.addEventListener("unload", this._close(obj));
				return true;
			}
			return false;
		}
		else {
			this.checkwindowpos (obj);
			this.fWindow.focus();
		}
		return true;
	}
	
	resizeLog(obj: IObject) {
		let w = this.scene2RelativeWidth(this.fWindow.outerWidth);
		let h = this.scene2RelativeHeight(this.fWindow.outerHeight);
		obj.fPosition.setWidth (w);
		obj.fPosition.setHeight (h);
	}
	_resizeLog (obj: IObject) : SetVoidMethod 				{ return () => this.resizeLog(obj); }

	updateObjectSize ( obj: IObject ) : void 	{}
	remove() : void								{}

	relative2SceneX(x: number) : number				{ let w = screen.availWidth/2; return w + (w * x); }
	relative2SceneY(y: number) : number				{ let h = screen.availHeight/2; return h + (h * y);}

	relative2SceneWidth(width: number) : number		{ return screen.availWidth * width / 2; }
	relative2SceneHeight(height: number) : number	{ return screen.availHeight * height / 2; }

	scene2RelativeWidth(width: number) : number		{ return width * 2 / screen.availWidth; }
	scene2RelativeHeight(height: number) : number	{ return height * 2 / screen.availHeight; }
	scene2RelativeX(x: number) : number				{ let w = screen.availWidth/2;  return (x - w) / w; }
	scene2RelativeY(y: number) : number				{ let h = screen.availHeight/2; return (y - h) / h; }
	initialize (obj: IObject ): void				{ }
}
