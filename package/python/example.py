import ITL
import OSC
import os


#####################################################
# the OSC client
oscDest = ('127.0.0.1', 7000)
client = OSC.OSCClient()
client.connect(oscDest)


#####################################################
itlAddress = "/ITL"
titleAddress = "/ITL/scene/title"
clockAddress = "/ITL/scene/clock"
carsAddress = "/ITL/scene/car*"

def itlprint (data):
	print "ITL ", data[0], data[2:]
err = ITL.ITLlistener (7002)	
err.start( itlprint ) 

# force an error message from the viewer
# client.send ( ITL.ITLMessage (itlAddress, "load", [ "toto" ]) )


messages = [
	["/ITL/scene/*", "del", [] ],
	[ titleAddress, "set", ["txt", "Interlude Score Viewer"] ],
	[ titleAddress, "scale", [2.5] ],
	[ titleAddress, "y", [-0.5] ]
]

ITL.sendMsgList (client, messages)

# send a query to the viewer and print
client.send ( ITL.ITLMessage (titleAddress, "get", []) )
print ( ITL.ITLlistener (7001).listen())

inittime = [
	[clockAddress, "set", ["txt", " "] ],
	[clockAddress, "scale", [3.0] ],
	[clockAddress, "color", [255, 50, 50, 255] ]
]

def timeMsg (time):
	client.send ( ITL.ITLMessage (clockAddress, "set", ["txt", '%d' % time]) )
	return time-1

def clockMsg (time):
	client.send ( ITL.ITLMessage (carsAddress, "clock", []) )
	return time

def scaleMsg (scale):
	client.send ( ITL.ITLMessage (titleAddress, "scale", [scale]) )
	return scale+0.02

ITL.sendMsgList (client, inittime)
ITL.timetask (timeMsg, 5, 1, 5.0)
ITL.timetask (scaleMsg, 2., 0.02, 3)

client.send ( ITL.ITLMessage (itlAddress, "rootPath", [ os.getcwd() ]) )
client.send ( ITL.ITLMessage (itlAddress, "load", [ "sync.interlude" ]) )
ITL.timetask (clockMsg, 0, 0.02, 20.0)

err.stop()
