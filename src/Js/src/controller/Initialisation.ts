///<reference path="IGlue.ts"/>
///<reference path="../events/dragAndDrop.ts"/>
///<reference path="../model/IAppl.ts"/>



var appl: IAppl = IGlue.initialize();

// Drag and Drop event
document.addEventListener("drop", dropEvent, false);
document.addEventListener("dragover", dragOverEvent, false);

// Timer's initialisation
var timerID = setTimeout(mainLoop, 10);

function mainLoop(): void {
    verifModif(appl);
    setTimeout(mainLoop, 10);  
}

function verifModif(obj: IObject): void {
    var child = obj.getSubNodes(); 
    if (child.length != 0) {
        for (var i=0; i < child.length; i++) {
            var s = child[i].getState();
            if (s == 2) { child[i].getView().updateView(); }
            verifModif(child[i]);    
        }       
    }
}



