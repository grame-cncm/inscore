.. index::
   single: image; score image

Get the score image
========================

Get a image of the score in *png* format. The screen version is associated with the image.

Request
##################
**With http server**
	Send a request to server with get method :
		| *serverUrl*/

**With websocket server**
	Send a JSON object  : 
		| ``{ method : "get"}``
		| example : ``exampleSocket.send(JSON.stringify({ method : "get"}));``

Response
#######################
		| A JSON object with two keys : a ``version`` and an ``image`` which contains the image in an ``ArrayBuffer``. It's the same response with the two differents server.
		| Example : ``{version : 1542, image : [xxx]}``

