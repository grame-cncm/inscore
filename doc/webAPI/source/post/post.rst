.. index::
   single: send INScore script

Post INScore script
===================

This method is used to post script to the server to update the score. The score may be modified and its current version number is increased.

Request
##################

**With http server**

The POST method is used to send the content of the INScore script. The request must have a entity-body with the entity ``data`` which contains the INScore script.

Example::

   <html>
     <body>
       <form action="serverUrl" method="post">
         <input type="text" name="data" value="/ITL/scene/rect set 1 1;" />
         <input type="submit" value="Submit" />
       </form>
     </body>
   </html>

**With websocket server**

A JSON object is used to send the INScore script. The object has three fields :
	* ``id`` : an arbitrary id for the request
	* ``method`` : the method is "post". This field is used to identified the type of the request
	* ``data`` : The INScore script.

Example:: 

   var postJsonObject = { id: "45612", method : "post", data : "/ITL/scene/rect set 1 1;"};
   exampleSocket.send(JSON.stringify(postJsonObject));

Response
#######################

The server answers with a status message which is between OK or ERROR. In case of
error, details on the failure reason are provided. When errors occur, The score can be modified : all INScore orders without errors are executed.

**With http server**
	* In case of success : a response with a code 200 ("Success") and no response body.
	* In case of error : a response with a code 400 ("Bad request") and the error message in a JSON object.
		| Example: ``{ "error" : "error: incorrect OSC address: /ITL/scene/text" }``

**With websocket server**

The response is a JSON object with three fields :
	* ``id`` : the id of the request
	* ``status`` : OK in case of success or ERROR in case of error.
	* ``error`` : An error message in case of error.

Example: ``{ id: "45612", status: "ERROR", "error" : "error: incorrect OSC address: /ITL/scene/text" }``

The response is asynchronous, other messages can be received before the response.

