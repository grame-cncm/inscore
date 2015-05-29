.. index::
   single: mouse; hover event

Post mouse hover
===================

A mouse hover event and its position can be send to interact with the score. The coordinates of the mouse are in pixels, with top left corner of coordinate (0, 0). The data should be a position in an image previously retrieved with a get message. The score may be modified and its current version number is increased.

Request
##################

**With http server**

The POST method is used to send mouse hover event. The request must have a entity-body with the entities ``x`` and ``y`` which contains the mouse coordinates.
The path of the request is *serverUrl*/``hover``.

Example::

   <html>
     <body>
       <form action="serverUrl/hover" method="post">
         <input type="text" name="x" value="152" />
	 <input type="text" name="y" value="354" />
         <input type="submit" value="Submit" />
       </form>
     </body>
   </html>

**With websocket server**

A JSON object with four fields is used to send the mouse coordinate :
	* ``id`` : an arbitrary id for the request
	* ``method`` : the method is "hover". This field is used to identified the type of the request.
	* ``x`` : the X axis mouse coordinate.
	* ``y`` : the Y axis mouse coordinate.

Example::

   var hoverJsonObject = { id : 8954, method : "hover", x : 152, y : 354 };
   exampleSocket.send(JSON.stringify(hoverJsonObject));

Response
#######################

**With http server**
	* In case of success : a response with a code 200 ("Success") and no response body.
	* In case of error : a response with a code 400 ("Bad request") and in the response body, the error message in a JSON object.
		| Example: ``{ "error" : "unknown object type: xxxx" }``

**With websocket server**

The response is a JSON object with three fields :
	* ``id`` : the id of the request
	* ``status`` : OK in case of success or ERROR in case of error.
	* ``error`` : An error message in case of error.

Example: ``{ id: "45612", status: "ERROR", "error" : "unknown object type: xxxx" }``

The response is asynchronous, other messages can be received before the response.

