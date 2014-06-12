
system := $(shell uname -s)
ifeq ($(system), Darwin)
LIBINSCORE :=  -F../cmake/Release -framework INScore
LIBOSCPACK :=  -I../lib/oscpack -L../lib/oscpack/cmake/Release -loscpack
OSXFLAGS := -mmacosx-version-min=10.6
else
LIBINSCORE :=  -L../cmake -lINScore
LIBOSCPACK :=  -I../lib/oscpack -L../lib/oscpack/cmake -loscpack
endif

G++   := g++

ESendOSC: ESendOSC.cpp
	$(G++) ESendOSC.cpp $(OSXFLAGS) -I../../lib/oscpack $(LIBOSCPACK) -o ESendOSC
