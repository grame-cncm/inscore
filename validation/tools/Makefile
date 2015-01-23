
system := $(shell uname -s)

ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../build/MacOS/Release -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack -loscpack
OPT := -mmacosx-version-min=10.6
else
 ifeq ($(system), MINGW32_NT-6.1)
 LIBINSCORE :=  -L../../cmake/build/win32/Release -lINScore
 LIBOSCPACK :=  -L../../lib/oscpack/cmake/Release -loscpack
 else
 LIBINSCORE :=  -L../../cmake -lINScore
 LIBOSCPACK :=  -L../../lib/oscpack/cmake -loscpack
endif
endif

tools :=  ../forcepdfdate ../SendOSC ../INScoreVersion
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
