Overview
===============================================

INScore scene can embed objects to provide web capabilities in order to make this score available to remote clients.

Two types of objects are available : 

• an HTTP server, which INScore type is httpd and that takes a listening port number as argument,
• a WebSocket server, which type is websocket and that takes a listening port number and a maximum rate for clients notification as arguments.

This objects can :doc:`get` (like score version and screen image) or :doc:`post` to update the score.

**Websocket specificities:**

With it's bidirectional communication, the websocket server sends notifications with the screen version number when the score change. Note that websocket responses are asynchronous that's why an id is introduct in JSON object for the request and retreived in the response.

Websocket doesn't have a response code like http. The status field is always present in response object with one of this two values :
	* ``OK`` in case of error
	* ``ERROR`` in case of success.

If an non-existing method or more generally, an incorrect json object is send to the server, the response is a generic json object error with the id if it can be read in the request object or an empty id if it cannot be read.

Example: ``{ id: "45612", status: "ERROR", "error" : "Bad request" }``




