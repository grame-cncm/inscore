import socket, types, threading
import sched, time
import OSC

#####################################################
# a simple class deriving OSCMessage 
# to build inscore messages
#####################################################
class ITLMessage (OSC.OSCMessage):
	"A simple class deriving OSCMessage to build messages at once"
	def __init__(self, address, method, params):
		OSC.OSCMessage.__init__(self, address)
		OSC.OSCMessage.append (self, method)
		for p in params:
			OSC.OSCMessage.append (self, p)

#####################################################
# a basic function to send a message list
#####################################################
def sendMsgList (oscclient, msglist):
	"A tool to send inscore messages list"
	for msg in msglist:
		address, method, params = msg
		oscclient.send ( ITLMessage (address, method, params) )

#####################################################
# a blocking time task
#####################################################
class timetask :
	"A time task running arbitrary functions\
	takes a function, its args, a time interval \
	and an absolute duration as __init__ parameters\
	times are expressed in floating point seconds"
	fEndtime = 0
	def __init__(self, f, args, interval, duration=0):
		self.fEndtime = time.time() + duration
		self.run ( [f, args, interval] )

	def run(self, params):
		f, args, interval = params
		while time.time() <= self.fEndtime:
			args = f ( args )
			time.sleep (interval)


#####################################################
# a listener of incoming OSC messages
# may operate synchronously or via a callback
#####################################################
class ITLlistener (threading.Thread) :
	"A listener of incoming OSC messages. \
	The 'listen' method operates synchronously \
	and the 'start' method operates in a separate thread \
	calling a client callback."
	fRunning = False
	fCallback = 0
	def __init__ (self, port):
		threading.Thread.__init__ (self)
		self.fSocket = socket.socket (socket.AF_INET, socket.SOCK_DGRAM)
		self.fSocket.bind( ('', port) )
		self.fPort = port
		
	def listen (self):
		"Listens to incoming messages synchronously and \
		returns a sequence of the decoded OSC packet fields. \
		Note: index 1 of the resulting sequence contains the \
		packet types string."
		data, (ip,port) = self.fSocket.recvfrom (4096)
		if len (data) > 4:			# discriminate incorrect and termination packets  
			return OSC.decodeOSC(data)
		return []
		
	def close (self):
		self.fSocket.close()
		
	def start (self, callback):
		"Starts listening in a separate thread. \
		The 'callback' argument will receive the decoded OSC \
		packet as argument (see 'listen')."
		self.fCallback = callback;
		self.fRunning = True
		threading.Thread.start(self)
		
	def run (self):
		"Don't call 'run' directly (see threading doc). \
		It is actually called by the 'start' method."
		while self.fRunning:
			data = self.listen()
			if len (data) > 1:
				self.fCallback ( data )		
	def stop (self):
		"Stops the thread."
		self.fRunning = False
		self.fSocket.sendto(" ", ('localhost', self.fPort) )
