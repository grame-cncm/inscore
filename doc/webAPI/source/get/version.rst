.. index::
   single: version; screen version

Getting the screen version
==========================

A screen version is maintained in INScore. It's a integer value, incremented at each score update.

Request
##################
**With http server**

A http GET request with path ``version`` is used to get the version. The message-body should by empty :
	| *serverUrl*/``version``

**With websocket server**

A JSON object with two keys : 
	* ``id`` : an arbitrary identifier for the request
	* ``method`` : the method (version) to identify the type of the request

Example:: 

   var versionJsonObject = { id : "4894", method : "version"};
   exampleSocket.send(JSON.stringify(versionJsonObject));

Response
#######################
**With http server**

A JSON object with a field ``version``.
   | Example : ``{version : 1542}``

**With websocket server**

A JSON object with a field id for the request identifier and a field ``version``.
   | Example : ``{id : "4894", version : 1542}``

