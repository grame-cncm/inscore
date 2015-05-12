.. index::
   single: notification

Score change notification
=========================

When using a websocket server, notification are received when the score change. The maximum rate of notification is defined when creating websocket server object.

Notification content
####################

A notification is the same JSON object as the object received after :doc:`get/version`.
	``{version : 456}``
