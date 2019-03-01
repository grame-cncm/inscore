
system := $(shell uname -s)

ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../build/bin -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack -loscpack
OPT := -mmacosx-version-min=10.9
else
 ifeq ($(system), MINGW32_NT-6.1)
 LIBINSCORE :=  -L../../cmake/build/bin -lINScore
 LIBOSCPACK :=  -L../../lib/oscpack/cmake/Release -loscpack
 else
 DEPLINUX := ../libINScore.so.1
 LIBINSCORE :=  -L../../build/bin -lINScore -lmicrohttpd
 LIBOSCPACK :=  -L../../lib/oscpack/cmake -loscpack
endif
endif

tools :=  ../forcepdfdate ../SendOSC ../INScoreVersion ../ReceiveOSC
CXX   := g++ 

all : $(tools)

../forcepdfdate: forcepdfdate.cpp
	$(CXX) forcepdfdate.cpp -o ../forcepdfdate

../INScoreVersion: INScoreVersion.cpp $(DEPLINUX)
	$(CXX) INScoreVersion.cpp -I../../src/inscore/interface $(LIBINSCORE) -o ../INScoreVersion

../SendOSC: SendOSC.cpp
	$(CXX) SendOSC.cpp  $(OPT) -I../../lib/oscpack $(LIBOSCPACK) -o ../SendOSC

../ReceiveOSC: ReceiveOSC.cpp
	$(CXX) ReceiveOSC.cpp  $(OPT) -I../../lib/oscpack $(LIBOSCPACK) -o ../ReceiveOSC

../libINScore.so.1 : 
	cd ../ && ln ../build/bin/libINScore.so.1.16.0 libINScore.so.1

clean:  
	rm -f $(tools)
