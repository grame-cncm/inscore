///<reference path="../model/IObject.ts"/>
///<reference path="../model/IApplStaticNodes.ts"/>
///<reference path="../view/VObjectView.ts"/>
///<reference path="../inscore.ts"/>

class VHtmlLog extends VObjectView {
	protected fWindow : Window;	
	protected fOpened : boolean;
	protected fPreviousX : number = -1; 		// used to detect window move
	protected fPreviousY : number = -1;
	protected fPreviousOX : number = -1; 		// used to handle window move
	protected fPreviousOY : number = -1;

	constructor() { super(); this.fOpened = false; }

	updateView ( obj: IObject) : void {
		if (obj.fPosition.getVisible()) {
			let pos		= obj.getPosition();
			let size 	= obj.getSize();
			let posChge = ((this.fPreviousOX < 0) ? true : (pos.x != this.fPreviousOX)) || 
						  ((this.fPreviousOY < 0) ? true : (pos.y != this.fPreviousOY));
			this.fPreviousOX = pos.x;
			this.fPreviousOY = pos.y;
			this.checkwindow (obj);
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
		else if (this.fWindow) {
			if (!this.fWindow.closed) this.fWindow.close();
			this.fOpened = false;
		}
	}

	writelog ( log: IApplLog ) : void {
		if (log.cleared())
			this.fWindow.document.body.innerHTML = "";

		let content = log.content();
		for (let i=0; i < content.length; i++)
			this.fWindow.document.write("<pre>" + content[i] + "</pre>");
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

	checkwindow ( obj: IObject ) : void {
		if (!this.fWindow || !this.fOpened) {
			let specs	= "menubar=no, titlebar=no, status=no, directories=no, location=no";
			this.fWindow = window.open("", "", specs);
			this.fWindow.document.write("<head><title>"+obj.getOSCAddress()+"</title>");
			this.fWindow.addEventListener("resize", this._resizeLog(obj));
			this.fOpened = true;
		}
		else this.checkwindowpos (obj);
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
//	updateLocalMapping (obj: IObject ): void		{ }
	initialize (obj: IObject ): void				{ }
}
