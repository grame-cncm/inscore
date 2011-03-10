version := 0.74

package:= INScore-$(version)
viewer := INScoreViewer
docsrc := ../doc
docdst := ./doc
icns   := ../rsrc/INScoreViewer.icns

striplist = $(shell find $(package)/$(viewer).app -name "*_debug*")

#########################
# this is for win32 only
bin    := ../cmake/release
#########################

.PHONY: doc rsrc

usage:
	@echo This makefile builds the Interlude prototype package.
	@echo It should be run on every supported platform.
	@echo usage:
	@echo "  make doc      # makes doc"
	@echo "  make src      # makes src package"
	@echo "  make macosx   # on Mac OS X"
	@echo "  make win32    # on Windows"
	@echo "  make linux    # on Linux (only build the rsrc)"

include makeBundle

macosx:
	[ -d $(package) ] || mkdir -p $(package)
	make -f makeINScoreBundle
	-[ -d $(package)/$(viewer).app ] && rm -rf $(package)/$(viewer).app
	mv $(viewer).app $(package)/$(viewer).app
	cp $(icns) $(package)/$(viewer).app/Contents/Resources
	make strip
	make rsrc
	chmod -x  $(shell find . -name "*.inscore")
	cp -f ../src/guido2.ttf $(package)
		
doc: 
	make -C $(docsrc)
	make copydoc
		
copydoc: 
	[ -d $(docdst)/html ] || mkdir -p $(docdst)/html
	cp -f $(docsrc)/OSCMsg.pdf $(docdst)
	make -C $(docsrc) htmlclean
	rm -f $(docdst)/html/*
	cp  $(docsrc)/OSCMsg/* $(docdst)/html
	cp -f $(docsrc)/presentation/INScore-fr.pdf $(docdst)
	cp -f $(docsrc)/presentation/INScore-en.pdf $(docdst)

rsrc:
	cp -rf Max $(package)/
	cp -rf PureData $(package)
	cp -rf python $(package)
	cp -rf lisp $(package)
	cp -rf StandAlone $(package)/
	cp readme.txt $(package)
	cp -r doc $(package)
	cp -f ../src/changelog.txt $(package)

src:
	[ -d $(package)-src/cmake ] || mkdir -p $(package)-src/cmake
	cp -rf ../src $(package)-src/
	cp -rf ../cmake/CMakeLists.txt $(package)-src/cmake
	cp -rf ../lib $(package)-src/
	cp readme.txt $(package)-src
	cp ../readme.txt $(package)-src/install
	cp -r doc $(package)-src
	tar czf $(package)-src.tgz $(package)-src


win32:
	[ -d $(package) ] || mkdir -p $(package)
	cp -f $(bin)/$(viewer).exe $(package)/$(viewer).exe
	cp -f $(bin)/*.dll $(package)
	cp -f ../src/guido2.ttf $(package)
	cp  -f DLLs/*.dll $(package)
	make rsrc
	cp  -r $(bin)/PlugIns $(package)

linux:
	[ -d $(package) ] || mkdir -p $(package)
	make rsrc
	chmod -x  $(shell find . -name "*.inscore")
	cd $(package) && tar czf ../$(package).tgz *

strip:
	rm -rf $(striplist)

