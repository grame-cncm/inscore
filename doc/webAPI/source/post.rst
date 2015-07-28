Post data to the server
=======================

| The POST requests are used to send data to the server to modify the score or to interact with it.

First column is the path used with http server or the method field used with web socket server.
The POST method has to be used with http server for these requests.

=========== ================== ===============================================
 HTTP path   WebSocket method   Description
=========== ================== ===============================================
 *empty*     post               Send an INScore script (see :doc:`post/post`).
 click       click              Send a mouse click event with mouse position (see :doc:`post/click`).
 hover       hover              Send a mouse hover event with mouse position (see :doc:`post/hover`).
=========== ================== ===============================================

.. toctree::
   :maxdepth: 1

   post/post 
   post/click
   post/hover


