#
# 
#

.PHONY : cmake

MAKE   ?= make
CMAKE  ?= cmake
TARGET := undefined
LIBDIR  ?= libdir
EMCCDIR ?= emccdir

CMAKEOPT ?= 


system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))


ifeq ($(TARGET), windows)
	GENERATOR ?= "Visual Studio 14 2015 Win64"
	J ?= /maxcpucount:4
endif


ifeq ($(system), Darwin)
	PREFIX  ?= /usr/local
 	GENERATOR ?= "Xcode"
	J ?= -jobs 8   # parallele jobs for xcode
endif

ifeq ($(system), MINGW)
	PREFIX  ?= "C:/Program Files"
endif

ifeq ($(system), Linux)
	PREFIX  ?= /usr/local
endif

GENERATOR ?= "Unix Makefiles"	# default generator
J  ?= -j 4


all :
	$(MAKE) library


help :
	@echo "This makefile is intended to build the INScore model library."
	@echo "Available targets are : "
	@echo "  library : to build the library (default)"
	@echo "  js      : to build the wasm library"
	@echo
	@echo "Project management: "
	@echo "  cmake    : to (re)generate the projects"
	@echo "  voidview : to regenerate the projects with no view inside a 'noview' folder"
	@echo
	@echo "Options:"
	@echo "  CMAKEOPT : options passed to cmake at project generation"

#===============================================================
# building inscore library
#===============================================================
cmake : $(LIBDIR)
	cd  $(LIBDIR) && $(CMAKE) .. -G $(GENERATOR)

library : $(LIBDIR)
	$(CMAKE) --build $(LIBDIR) --config Release -- $(J)

$(LIBDIR):
	mkdir $(LIBDIR)
	$(MAKE) cmake

#===============================================================
# building inscore wasm library
#===============================================================
cmakejs : $(EMCCDIR)
	cd  $(EMCCDIR) && $(CMAKE) .. -DEMCC=on

js: $(EMCCDIR)
	make -C $(EMCCDIR) wasmlib

$(EMCCDIR):
	mkdir $(EMCCDIR)
	$(MAKE) cmakejs

#===============================================================
# install target
#===============================================================

	
