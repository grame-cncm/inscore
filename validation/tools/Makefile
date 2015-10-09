
system := $(shell uname -s)

ifeq ($(system), Darwin)
LIBINSCORE :=  -F../../build/macos/Release -framework INScore
LIBOSCPACK :=  -L../../lib/oscpack -loscpack
OPT := -mmacosx-version-min=10.6
else
 ifeq ($(system), MINGW32_NT-6.1)
 LIBINSCORE :=  -L../../cmake/build/win32/Release -lINScore
 LIBOSCPACK :=  -L../../lib/oscpack/cmake/Release -loscpack
 else
 DEPLINUX := ../libINScore.so.1
 LIBINSCORE :=  -L../../build/linux -lINScore -lmicrohttpd
 LIBOSCPACK :=  -L../../lib/oscpack/cmake -loscpack
endif
endif

tools :=  ../forcepdfdate ../SendOSC ../INScoreVersion ../ReceiveOSC
G++   := g++

all : $(tools)

../forcepdfdate: forcepdfdate.cpp
	$(G++) forcepdfdate.cpp -o ../forcepdfdate

../INScoreVersion: INScoreVersion.cpp $(DEPLINUX)
	$(G++) INScoreVersion.cpp -I../../src/library/interface $(LIBINSCORE) -o ../INScoreVersion

../SendOSC: SendOSC.cpp
	$(G++) SendOSC.cpp  $(OPT) -I../../lib/oscpack $(LIBOSCPACK) -o ../SendOSC

../ReceiveOSC: ReceiveOSC.cpp
	$(G++) ReceiveOSC.cpp  $(OPT) -I../../lib/oscpack $(LIBOSCPACK) -o ../ReceiveOSC

../libINScore.so.1 : 
	cd ../ && ln ../build/linux/libINScore.so.1.16.0 libINScore.so.1

clean:  
	rm -f $(tools)
