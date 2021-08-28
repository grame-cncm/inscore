 var w =   
"onmessage = function(e) {" +
"     postMessage(" +
"        (e && e.data &&" +
"          ((typeof e.data.a === 'function' && e.data.a()) ||" +
"            e.data" +
"          )" +
"        ) + 1" +
"      )" +
"    }"


console.log (btoa(w));