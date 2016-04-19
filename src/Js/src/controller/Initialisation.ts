///<reference path="IGlue.ts"/>
///<reference path="../events/dragAndDrop.ts"/>


var appl: IAppl = IGlue.initialize()

document.addEventListener("drop", dropEvent, false);
document.addEventListener("dragover", dragOverEvent, false);
