function cpu(n) {
    let start = Date.now();
    let a = Math.sqrt(2);
    for (let i = 0; i < n; i ++) {
        a = Math.sin(Math.sqrt(Math.sqrt(Math.log(Math.sqrt(a)))));
    }
    let end = Date.now();
    return (end - start)
}

onmessage = function(e) {
    // console.log ("receive message", e.data.id, e.data.msg);
    if (e.data.msg === "compute")
        postMessage({ "id" : e.data.id, "value": cpu(e.data.count)});    
}