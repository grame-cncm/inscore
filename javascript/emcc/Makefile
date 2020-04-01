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

JOBS ?= 6
ifeq ($(TARGET), windows)
	GENERATOR ?= "Visual Studio 15 2017 Win64"
	J ?= /maxcpucount:$(JOBS)
endif

ifeq ($(system), Darwin)
	PREFIX  ?= /usr/local
 	GENERATOR ?= "Xcode"
	J ?= -jobs $(JOBS)   # parallele jobs for xcode
endif

ifeq ($(system), MINGW)
	PREFIX  ?= "C:/Program Files"
endif

ifeq ($(system), Linux)
	PREFIX  ?= /usr/local
endif

GENERATOR ?= "Unix Makefiles"	# default generator
J  ?= -j $(JOBS)


all :
	$(MAKE) emcc

help :
	@echo "This makefile is intended to build the INScore wasm library."
	@echo "Available targets are : "
	@echo "  emcc   : to build the wasm (default)"
	@echo "  lib    : to build the inscore model as a library"
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
emcc: $(EMCCDIR)
	$(MAKE) -C $(EMCCDIR) emcc -j $(JOBS)

lib : $(LIBDIR)
	$(CMAKE) --build $(LIBDIR) --config Release -- $(J)

#===============================================================
# project management
#===============================================================
cmake : $(LIBDIR)  $(EMCCDIR) 
	cd  $(LIBDIR) && $(CMAKE) .. -DEMCC=off $(CMAKEOPT) -G $(GENERATOR)
	cd  $(EMCCDIR) && $(CMAKE) .. $(CMAKEOPT) -DEMCC=on

$(LIBDIR):
	mkdir $(LIBDIR)
	cd  $(LIBDIR) && $(CMAKE) .. -DEMCC=off $(CMAKEOPT) -G $(GENERATOR)

$(EMCCDIR):
	mkdir $(EMCCDIR)
	cd  $(EMCCDIR) && $(CMAKE) .. $(CMAKEOPT) -DEMCC=on

clean:
	rm -rf $(LIBDIR)  $(EMCCDIR) 
	rm -f ../libINScore.wasm ../libINScore.js
	
