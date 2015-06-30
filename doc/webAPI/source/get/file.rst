.. index::
   single: file

Get a file from INScore server
==============================

Files in INScore application rootPath folder can be download from the web API. This service is intended for files of saved or exported scenes and objects, but it can be all kind of files.

Request
##################
**With http server**

A http GET request with path the relative path of the file in the application rootPath. The message-body should by empty :
	| *serverUrl*/``realtivePath``/filename.extension

**With websocket server**

A JSON object with three keys : 
	* ``id`` : an arbitrary identifier for the request
	* ``method`` : the method (file) to identify the type of the request
	* ``path`` : the relative path of the file in the application rootPath

Example:: 

   var fileJsonObject = { id : "4894", method : "file", path : "saveFolder/myScene.inscore"};
   exampleSocket.send(JSON.stringify(fileJsonObject));

Response
#######################
**With http server**
	* In case of success :

	*Response code :* 200("success")

	*Response body :* The file is returned with a mime type corresponding to the file extension.

	* In case of error :

	*Response code :* 404("Not found")

	*Response body :* empty.

**With websocket server**
	* In case of success :

A JSON object with an 'id' containing the request identifier, the response status and a field ``file`` with the file data encoded in a base64 string.
   | Example : ``{id : "4894", status : "OK", file : "A5Nh63dsB..."}``

	* In case of error :

A JSON object with a field id for the request identifier, the response status and a field ``error`` with the cause af error.
   | Example : ``{id : "4894", status : "ERROR", "error" : "Not found"}``
