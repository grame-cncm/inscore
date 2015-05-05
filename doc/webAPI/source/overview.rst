Overview
===============================================

INScore scene can embed objects to provide web capabilities in order to make this score available to remote clients.

Two types of objects are available : 

• an HTTP server, which INScore type is httpd and that takes a listening port number as argument,
• a WebSocket server, which type is websocket and that takes a listening port number and a maximum rate for clients notification as arguments.

This objects can :doc:`get` (like score version and screen image) or :doc:`post` to update the score.
With it's bidirectional communication, the websocket server sends notifications with the screen version number when the score change.

Note that websocket responses are asynchronous.
