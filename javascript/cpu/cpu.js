
var workers = [];
var cpus = new Map();
var cpuloop = 4000000;

if (window.Worker) {

for (let i = 1; i <= window.navigator.hardwareConcurrency; i++) {
    let worker = new Worker('cpuworker.js');
    worker.onmessage = function(e) {
        cpus.set(e.data.id, e.data.value);
    }
    workers.push(worker);
}
console.log("CPU tools: hardwareConcurrency is", window.navigator.hardwareConcurrency);

}
else {
    console.log ("CPU tools: Worker is not supported!")
}

function getCpus() {
    cpus = new Map();
    let i=1;
    workers.forEach((elem) => { elem.postMessage({ id: i++, msg: "compute", count: cpuloop }); });
}

function waitCpus(resolve, cpus) {
    if (cpus.size < window.navigator.hardwareConcurrency)
        setTimeout(() => { waitCpus(resolve, cpus); }, 50);
    else resolve(cpus);
}

function getCpusAsync() {
    getCpus();
    return new Promise((resolve, reject) => { waitCpus (resolve, cpus);});
}

function getCpusWithMain() {
    getCpus();
    let start = Date.now();
    let a = Math.sqrt(2);
    for (let i = 0; i < cpuloop; i ++)
        a = Math.sin(Math.sqrt(Math.sqrt(Math.log(Math.sqrt(a)))));
    let end = Date.now();
    cpus.set(window.navigator.hardwareConcurrency+1, (end-start));
    return new Promise((resolve, reject) => { waitCpus (resolve, cpus);});
}

function showCpus(result) {
    let txt = "";
    let min = 100000;
    let max = 0;
    for (let i = 1; i<= result.size; i++) {
        let val = result.get(i);
         txt += val + " ";
         if (val < min) min = val;
         if (val > max) max = val;
    }
    txt += " Min/Max: " + min + "/" + max;
    console.log(txt);
}
