
system := $(shell uname -s)
ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../build/MacOS/Release -F../../cmake -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack/cmake/Release -L../../lib/oscpack -loscpack
else
LIBINSCORE :=  -F../../cmake -lINScore
LIBOSCPACK :=  -L../../lib/oscpack/cmake -loscpack
endif

tools := ../INScoreVersion ../forcepdfdate ../SendOSC
G++   := g++

all : $(tools)


../forcepdfdate: forcepdfdate.cpp
	$(G++) forcepdfdate.cpp -o ../forcepdfdate

../INScoreVersion: INScoreVersion.cpp
	$(G++) INScoreVersion.cpp -I../../src/interface $(LIBINSCORE) -o ../INScoreVersion

../SendOSC: SendOSC.cpp
	$(G++) SendOSC.cpp -I../../lib/oscpack $(LIBOSCPACK) -o ../SendOSC

clean:  
	rm -f $(tools)
