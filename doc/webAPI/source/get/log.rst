.. index::
   single: log

Getting the INScore log
==========================

Request
##################
**With http server**

A http GET request with path ``log`` is used to get the INScore log. The message-body should by empty :
	| *serverUrl*/``log``

**With websocket server**

A JSON object with two keys : 
	* ``id`` : an arbitrary identifier for the request
	* ``method`` : the method (log) to identify the type of the request

Example:: 

   var logJsonObject = { id : "4894", method : "log"};
   exampleSocket.send(JSON.stringify(logJsonObject));

Response
#######################
**With http server**

A JSON object with a field ``log``.
   | Example : ``{log : "xxxc"}``

**With websocket server**

A JSON object with a field id for the request identifier, the response status and a field ``log``.
   | Example : ``{id : "4894", status : "OK", log : "xxxx"}``

