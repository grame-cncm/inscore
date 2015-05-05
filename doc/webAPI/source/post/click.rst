.. index::
   single: mouse; click event

Post mouse click
===================

A mouse click event and its position can be send to interact with the score. The coordinates of the click are in pixels, with top left corner of coordinate (0, 0). The data should be a position in an image previously retrieved with a get message. The score may be modified and its current version number is increased.

Request
##################

**With http server**

Send a request to server at the url *serverUrl/click* with post method. Mouse coordinates are in field ``x`` and ``y``. 

Example::

   <html>
     <body>
       <form action="serverUrl/click" method="post">
         <input type="text" name="x" value="152" />
	 <input type="text" name="x" value="354" />
         <input type="submit" value="Submit" />
       </form>
     </body>
   </html>

**With websocket server**

Send a JSON object with three key ``method``, ``x`` and ``y``: 
		| ``{ method : "click", x : 152, y : 354 }``
		| example : ``exampleSocket.send(JSON.stringify({ method : "click", x : 152, y : 354 }));``

Response
#######################

**With http server**
	* 200 ("Success")

**With websocket server**
	No answer


