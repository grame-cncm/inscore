
/////<reference path="../parser/INScoreParser.ts"/>



/*var input:string = 'aaaaaaaaaaa';
import parser = require("../parser/./INScoreParser");
parser.parser;
var test = parser.parse(input); 
console.log(test);*/







function createMessage(msg:string) {
    
}

function dropEvent(e) {
    dragOverEvent(e);

    var filelist =  e.dataTransfer.files;
    if (!filelist) { return; }  
  
    var filecount = filelist.length;
    if (filecount > 0) {                
        for (var i=0; i < filecount; i++) {
            var reader: FileReader = new FileReader();
            var file = filelist[i]; 
            reader.readAsText(file);  
                      
            reader.onloadend = function (e) {
                var data: string = reader.result;
                console.log(data);    
            };        
        } 
    } 
}

function dragOverEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}

