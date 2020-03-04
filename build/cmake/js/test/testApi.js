


//----------------------------------------------------------------------------
// Message methods
//----------------------------------------------------------------------------
function messages (inscore, log )
{
	log( "\nMessages:");
	log( "  newMessage:    " + inscore.newMessage());
	log( "  newMessageM:   " + inscore.newMessageM("get"));
	log( "  delMessage:    "); inscore.delMessage(inscore.newMessage());
	var msg = inscore.newMessage();
	log( "  msgAddStr:     "); inscore.msgAddStr(msg, "set");
	log( "  msgAddF:       "); inscore.msgAddF(msg, 1.1);
	log( "  msgAddI:       "); inscore.msgAddI(msg, 0);	
}

function post_messages (inscore, log )
{
	log( "\nPost messages:");
 	log( "  postMessage:       "); inscore.postMessage("/ITL", inscore.newMessage());	
 	log( "  postMessageStr:    "); inscore.postMessageStr("/ITL", "get");	
  	log( "  postMessageStrI:   "); inscore.postMessageStrI("/ITL", "get", 1);	
 	log( "  postMessageStrF:   "); inscore.postMessageStrF("/ITL/scene", "x", 1.1);	
 	log( "  postMessageStrStr: "); inscore.postMessageStrStr("/ITL",  "get", "rate");	
 	log( "  delayMessage: "); 	   inscore.delayMessage("/ITL", inscore.newMessage("reset"));	
}

//----------------------------------------------------------------------------
// infos
//----------------------------------------------------------------------------
function infos (inscore, log )
{
	log( "\nInformation:");
	log( "  version:         " + inscore.version());
	log( "  versionStr:      " + inscore.versionStr());
	log( "  guidoversion:    " + inscore.guidoversion());
	log( "  musicxmlversion: " + inscore.musicxmlversion());
	log( "  getRate:         " + inscore.getRate());
}

//----------------------------------------------------------------------------
// loading scripts
//----------------------------------------------------------------------------
function load (inscore, log )
{
	var scriptv1 = "/ITL/scene new; /ITL/scene/rect1 set rect 0.2 0.2;"
	scriptv1 += "/ITL/scene/rect1 x 0.5;"
	scriptv1 += "/ITL/scene/rect1 y 0.1;"

	var scriptv2 = "/ITL/scene new; /ITL/scene/label (set txt label), (yorigin 1.1), (y 0.5), (x 0), (fontSize 11);"

	log( "\nLoading scripts:");
	log( "  loadInscore:       "); inscore.loadInscore(scriptv1);
	log( "  loadInscore2:      "); inscore.loadInscore2(scriptv2);
}

//----------------------------------------------------------------------------
// inscore tasks
//----------------------------------------------------------------------------
function tasks (inscore, log )
{
	log( "\nINScore time tasks:");
	log( "  timeTask:        "); inscore.timeTask();
	log( "  sorterTask:      "); inscore.sorterTask();
}

//----------------------------------------------------------------------------
// Start & stop
//----------------------------------------------------------------------------
function start (inscore, log )
{
	log( "\nStart inscore:");
	log( "  start:     ");  
	inscore.start(7000, 7001, 7002);
}

function stop (inscore, log, glue )
{
	log( "\nStop inscore:");
	log( "  stop:     "); 
	inscore.stop ();
}

//----------------------------------------------------------------------------
function run (inscore, log) {
  	start (inscore, log);
   	infos (inscore, log);
   	messages (inscore, log);
   	post_messages (inscore, log);
   	load (inscore, log);
  	tasks (inscore, log);
  	stop  (inscore, log);
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
