Get data from the server
=========================

| This methods are used to query an existing score and doesn't modify it. 

First column is the path used with http server or the method field used with web socket server.
The GET method has to be used with http server for these requests.

=========== ================== ====================================================================
 HTTP path   WebSocket method   Description
=========== ================== ====================================================================
 version     version            Get the internal inscore screen version (see :doc:`get/version`).
 *empty*     image              Get the image of the score in png format (see :doc:`get/image`).
 file        file               Get a file from inscore application root path (see :doc:`get/file`).
=========== ================== ====================================================================

.. toctree::
   :maxdepth: 1

   get/version
   get/image
   get/file
