version := 1.32
system	:= $(shell uname -s)

package:= GFLib-$(version)
staticlib 	:= ../cmake/Release/libGFLib.a
framework 	:= ../cmake/Release/GFLib.framework
bundle	 	:= ../sample/bin/sampleqt.app

#########################

.PHONY: doc rsrc

usage:
	@echo This makefile builds the Gesture Follower package.
	@echo It should be run on every supported platform.
	@echo usage:
	@echo "  make macosx   # on Mac OS X"
	@echo "  make win32    # on Windows"
	@echo "  make linux    # on Linux"

macosx:
	[ -d $(package) ] || mkdir -p $(package)
	make common
	[ -d $(package)/lib ] || mkdir -p $(package)/lib
	-[ -f $(staticlib) ] && cp  $(staticlib) $(package)/lib
	-[ -d $(framework) ] && cp -R $(framework) $(package)/lib
	-[ -d $(bundle) ] && cp -R $(bundle) $(package)
	macdeployqt $(package)/sampleqt.app
	tar czf $(package).tgz $(package)
	
common:
	make doc
	make sample
	[ -d $(package)/include ] || mkdir -p $(package)/include
	cp ../src/GestureFollower.h $(package)/include
	
sample:
	[ -d $(package)/sample ] || mkdir -p $(package)/sample
	cp ../sample/gdrawarea.* $(package)/sample
	cp ../sample/gfollower.* $(package)/sample
	cp ../sample/mainwindow.* $(package)/sample
	cp ../sample/main.cpp $(package)/sample
	cp ../sample/sampleqt.pro $(package)/sample
	
doc:
	[ -d $(package)/doc ] || mkdir -p $(package)/doc
	cp -R ../doc/html $(package)/doc
	cp ../doc/latex/refman.pdf $(package)/doc/$(package).pdf
	
win32:
	@echo windows packaging still to be done

linux:
	@echo linux packaging still to be done
	