.. index::
   single: notification

Score change notification
=========================

When using a websocket server, notifications are automatically sent for each new version of the graphic score. The maximum rate of notification is defined when creating websocket server object.

Notification content
####################

A notification is a JSON object with two fields, notification and version containing the score current version.
	``{notification : true, version : 456}``
