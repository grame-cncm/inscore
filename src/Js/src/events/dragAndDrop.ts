
///<reference path="../controller/IGlue.ts"/>
///<reference path="../model/TILoader.ts"/>

declare var gGlue : IGlue;

function dropEvent(e) {
    dragOverEvent(e);

    var filelist =  e.dataTransfer.files;
    if (!filelist) { return; }  
  
    var filecount = filelist.length;
    if (filecount > 0) {                
        for (var i=0; i < filecount; i++) {
            var loader = new TILoader;
            loader.load(filelist[i], gGlue.getRoot());      
        } 
    } 
}

function dragOverEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}

