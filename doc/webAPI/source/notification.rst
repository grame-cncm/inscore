.. index::
   single: notification

Score change notification
=========================

When using a websocket server, notification are received when the score change. The maximum rate of notification is defined when creating websocket server object.

Notification content
####################

A notification is a JSON object with two fields, notification and version, the internal score version of INScore.
	``{notification : true, version : 456}``
