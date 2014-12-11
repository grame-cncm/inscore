
system := $(shell uname -s)
ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../build/MacOS/Release -F../../cmake -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack -loscpack
OPT := -mmacosx-version-min=10.6
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
	$(G++) SendOSC.cpp  $(OPT) -I../../lib/oscpack $(LIBOSCPACK) -o ../SendOSC

clean:  
	rm -f $(tools)
