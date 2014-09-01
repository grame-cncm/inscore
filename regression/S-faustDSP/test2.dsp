
db2linear1(x)	= pow(10.0, x/20.0);

smooth(c)		= *(1-c) : +~*(c);
vol 			= hslider("volume [unit:dB]", 0, -96, 0, 0.1) : db2linear : smooth(0.999) ;
freq 			= slider("freq [unit:Hz]", 1000, 20, 24000, 1);


process 		= vgroup("Oscillator", osc(freq) * vol);