.. index::
   single: version; screen version

Getting the screen version
==========================

A screen version is maintained in INScore. It's a integer value, incremented at each score update.

Request
##################
**With http server**
   Send a request to the server with get method :
	| *serverUrl*/``version``

**With websocket server**
   Send a JSON object  : 
	| ``{ method : "version"}``
	| example : ``exampleSocket.send(JSON.stringify({ method : "version"}));``

Response
#######################

A JSON object with ``version`` as key. It's the same response with the two differents server.
	| Example : ``{version : 1542}``

