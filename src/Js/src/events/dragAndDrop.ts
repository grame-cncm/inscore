function dropEvent(e) {
    dragOverEvent(e);

    var filelist =  e.dataTransfer.files;
    if (!filelist) { return; }  
  
    var filecount = filelist.length;
    if (filecount > 0) {                
        for (var i=0; i < filecount; i++) {
            var loader = new TILoader;
            loader.load(filelist[i], loader);      
        } 
    } 
}

function dragOverEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}

