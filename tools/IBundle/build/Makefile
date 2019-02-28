.PHONY : macos win32 win64 linux

QMAKE  ?= qmake
MAKE   ?= make
OUTDIR ?= ibundledir
TARGET  = undefined

system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))


ifeq ($(system), Darwin)
	TARGET  = macos
	PROJ    = IBundle.xcodeproj
	SPEC    = -spec macx-xcode
	PREFIX  ?= /usr/local
endif

ifeq ($(system), MINGW)
	TARGET = windows
	PROJ    = IBundle.vcxproj
	PREFIX  ?= "C:/Program Files"
endif

ifeq ($(system), Linux)
	TARGET  = linux
	PROJ    = Makefile
	PREFIX  ?= /usr/local
endif

ibundle:
	make $(TARGET)

#===============================================================
# building IBundle
#===============================================================
macos : $(OUTDIR)/$(PROJ)
	xcodebuild -jobs 8 -project $(OUTDIR)/IBundle.xcodeproj -target IBundle -configuration Release

linux : $(OUTDIR)/$(PROJ)
	$(MAKE) -C $(OUTDIR) -j 8

windows : $(OUTDIR)/$(PROJ)
	@echo Open your project and compile with your IDE or use the Make.bat script

#===============================================================
# project generation
#===============================================================
$(OUTDIR)/$(PROJ) : IBundle.pro
	[ -d $(OUTDIR) ] || mkdir $(OUTDIR)
	cd $(OUTDIR) && $(QMAKE) $(SPEC) ../IBundle.pro
	
install :
	cp -f IBundle $(HOME)/bin/IBundle

undefined:
	@echo Target is undefined, system $(system) not handled

