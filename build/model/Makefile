#
# 
#

.PHONY : 

MAKE    ?= make
CMAKE   ?= cmake
EMCCDIR ?= emccdir
LIBDIR  ?= libdir
CMAKEOPT ?= 

system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))

ifeq ($(TARGET), windows)
	GENERATOR ?= "Visual Studio 15 2017 Win64"
endif

ifeq ($(system), Darwin)
	PREFIX  ?= /usr/local
 	GENERATOR ?= "Xcode"
endif

ifeq ($(system), MINGW)
	PREFIX  ?= "C:/Program Files"
endif

ifeq ($(system), Linux)
	PREFIX  ?= /usr/local
endif

GENERATOR ?= "Unix Makefiles"	# default generator


all :
	$(MAKE) wasm

help :
	@echo "This makefile is intended to build the INScore model libraries."
	@echo "Available targets are : "
	@echo "  wasm   : to build the wasm library (default)"
	@echo "  lib    : to build the inscore model as a native library"
	@echo
	@echo "Project management: "
	@echo "  cmake     : to (re)generate the projects"
	@echo "  clean     : clean the projects"
	@echo
	@echo "Options:"
	@echo "  CMAKEOPT : options passed to cmake at project generation"


#===============================================================
# building inscore library
#===============================================================
wasm: $(EMCCDIR) $(EMCCDIR)/Makefile
	$(MAKE) -C $(EMCCDIR) wasm 

lib : $(LIBDIR) $(LIBDIR)/INScoreModel.xcodeproj
	$(CMAKE) --build $(LIBDIR) --config Release 

#===============================================================
# project management
#===============================================================
cmake : $(LIBDIR)  $(EMCCDIR) 
	cd  $(LIBDIR) && $(CMAKE) .. -DEMCC=off $(CMAKEOPT) -G $(GENERATOR)
	cd  $(EMCCDIR) && $(CMAKE) .. $(CMAKEOPT) -DEMCC=on

$(EMCCDIR)/Makefile: CMakeLists.txt
	cd  $(EMCCDIR) && $(CMAKE) .. $(CMAKEOPT) -DEMCC=on

$(LIBDIR)/INScoreModel.xcodeproj: CMakeLists.txt
	cd  $(LIBDIR) && $(CMAKE) .. -DEMCC=off $(CMAKEOPT) -G $(GENERATOR)

$(LIBDIR):
	mkdir $(LIBDIR)

$(EMCCDIR):
	mkdir $(EMCCDIR)

clean:
	rm -rf $(LIBDIR)  $(EMCCDIR) 
	rm -f ../lib/libINScore.wasm ../lib/libINScore.js
	
