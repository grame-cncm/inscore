.. index::
   single: send INScore script

Post INScore script
===================

This method is used to post script to server to update the score. The score may be modified and its current version number is increased.

Request
##################

**With http server**

Send a request to server with post method. The content of the INScore script is in the field ``data``. 

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

Send a JSON object with two key ``method`` and ``data`` : 
		| ``{ method : "post", data : "/ITL/scene/rect set 1 1;"}``
		| example : ``exampleSocket.send(JSON.stringify({ method : "post", data : "/ITL/scene/rect set 1 1;"}));``

Response
#######################

The server answers with a status
message which is between OK or ERROR. In case of
error, details on the failure reason are provided.	
return log ?

**With http server**
	* 200 ("Success")

**With websocket server**
	No answer

