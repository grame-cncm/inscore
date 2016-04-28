
///<reference path="../controller/IGlue.ts"/>
///<reference path="../model/TILoader.ts"/>

declare var gGlue : IGlue;

function dropEvent(e) {
    dragOverEvent(e);

    let filelist =  e.dataTransfer.files;
    if (!filelist) { return; }  
  
    let filecount = filelist.length;
    if (filecount > 0) {                
        for (let i=0; i < filecount; i++) {
            let loader = new TILoader;
            loader.load(filelist[i], gGlue.getRoot());      
        } 
    } 
}

function dragOverEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}

