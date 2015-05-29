.. index::
   single: image; score image

Get the score image
========================

Get a image of the score in *png* format. The screen version is associated with the image.

Request
##################
**With http server**

A http GET request at root of the server is used to get the image. The message-body should by empty :
	path : *serverUrl*/

**With websocket server**

A JSON object with two fields is used to get the image :
	* ``id`` : an arbitrary id for the request
	* ``method`` : the method is ``image``. This field is used to identified the request

Example:: 

   var getJsonObject = { id : "145678", method : "image"};
   exampleSocket.send(JSON.stringify(getJsonObject));

Response
#######################
**With http server**

The server send the image with the ``Cache-Control`` directive set to ``no-cache``. A `If-Modified-Since directive <http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.25/>`_ with a date can be used to avoid unnecessary data transfer. If the score has not been modified since the specified date, a 304 (Not modified) response is returned.

In other case, a normal GET response is return :

	The format of the image is defined by the Mime type in the Content-type header of the response. The only value return is "image/png".
	A custom header ``X-Inscore-version`` is added, it contains the internal INScore version of the score.

	*Response code :* 200("success")

	*Response body :* the image of the score in the format define in the Content-type header.

**With websocket server**

A JSON object with five keys :
	* ``id`` : the id of the request
	* ``status`` : OK in case of success or ERROR in case of error.
	* ``version`` : the score version.
	* ``mimeType`` : the mime-type of the image.
	* ``image`` : an ``ArrayBuffer`` which contains the image.

The only image format returned is the png format (mimeType "image/png")

	| Example : ``{id : "145678", status : "OK", version : 1542, mimeType : "image/png", image : [xxx]}``

