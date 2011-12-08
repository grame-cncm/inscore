
system := $(shell uname -s)
ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../cmake/Release -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack/cmake/Release -loscpack
else
LIBINSCORE :=  -F../../cmake -lINScore
LIBOSCPACK :=  -L../../lib/oscpack/cmake -loscpack
endif

tools := ../INScoreVersion ../forcepdfdate ../SendOSC


all : $(tools)


../forcepdfdate: forcepdfdate.cpp
	g++ forcepdfdate.cpp -o ../forcepdfdate

../INScoreVersion: INScoreVersion.cpp
	g++ INScoreVersion.cpp -I../../src/interface $(LIBINSCORE) -o ../INScoreVersion

../SendOSC: SendOSC.cpp
	g++ SendOSC.cpp -I../../lib/oscpack $(LIBOSCPACK) -o ../SendOSC

clean:  
	rm -f $(tools)
