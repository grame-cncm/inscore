

tools := ../INScoreVersion ../forcepdfdate ../SendOSC


all : $(tools)


../forcepdfdate: forcepdfdate.cpp
	g++ forcepdfdate.cpp -o ../forcepdfdate

../INScoreVersion: INScoreVersion.cpp
	g++ INScoreVersion.cpp -I../../src/interface -F../../cmake/Release -framework INScore -o ../INScoreVersion

../SendOSC: SendOSC.cpp
	g++ SendOSC.cpp -I../../lib/oscpack -L../../lib/oscpack/cmake/Release -loscpack -o ../SendOSC

clean:  
	rm -f $(tools)
