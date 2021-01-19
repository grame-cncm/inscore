
///<reference path="inscoreBase.ts"/>

//----------------------------------------------------------------------------
class BasicGlue extends INScoreBase {

	accept (event : DragEvent) : boolean {
		let items = event.dataTransfer.items;
		for (let i=0; i< items.length; i++) {
			switch (items[i].kind) {
				case "string":
				case "file":
					break;
				default:
					return false;
			}
		}
		return true;
	}

	dragEnter (event : DragEvent) : void { 
		event.preventDefault();
		let div = <HTMLElement>event.currentTarget;
		div.setAttribute('savedborder', div.style.border);
		div.style.border = "1px solid grey"; 
	}

	dragLeave (event : DragEvent) : void {
		event.preventDefault();
		let div = <HTMLElement>event.currentTarget;
		div.style.border = div.getAttribute('savedborder');
	}

}

var inscoreGlue = new BasicGlue();
inscoreGlue.start();
