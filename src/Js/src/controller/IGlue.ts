
///<reference path="../model/IAppl.ts"/>
///<reference path="../events/dragAndDrop.ts"/>

class IGlue {
	protected fAppl: IAppl;
	
    constructor() 			{ this.fAppl = new IAppl(); }
	getRoot() : IAppl		{ return this.fAppl; }

    initDragAndDrop(): void {
		document.addEventListener("drop", dropEvent, false);
		document.addEventListener("dragover", dragOverEvent, false);
    }
}
